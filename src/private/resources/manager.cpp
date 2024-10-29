#include "resources/manager.h"

#include <functional>
#include <memory>
#include <stdexcept>
#include <span>

#include <cassert>
#include <cstdio>

#include <AL/al.h>

#define DR_WAV_IMPLEMENTATION
#include <dr_wav.h>

#include <png.h>

#include <spdlog/spdlog.h>

#include "audio/manager.h"
#include "shader.h"
#include "sound.h"
#include "sprite.h"

namespace Resources
{

Manager::Manager()
{
	auto error = FT_Init_FreeType(&ftLibrary);
	if (error)
	{
		spdlog::error("Error initializing freetype library! Error code: {}", error);
		ftLibrary = { };
	}
}

Manager::~Manager()
{
	if (ftLibrary)
	{
		FT_Done_FreeType(ftLibrary);
	}
}

template<>
Font* Manager::CreateResource(const std::filesystem::path& fontPath)
{
	if (!ftLibrary)
	{
		spdlog::warn("FreeType library not loaded!");
		return nullptr;
	}

	if (!std::filesystem::exists(fontPath))
	{
		throw std::runtime_error("Font file does not exist!");
	}

	FT_Face face { };
	auto err = FT_New_Face(ftLibrary, fontPath.string().c_str(), 0, &face);
	if (err == FT_Err_Unknown_File_Format)
	{
		throw std::runtime_error("Font file format invalid!");
	}
	else if (err)
	{
		throw std::runtime_error("Could not load default font face!");
	}
}

template<>
Sprite* Manager::CreateResource(const std::filesystem::path& pngPath)
{
	if (!std::filesystem::exists(pngPath))
	{
		throw std::runtime_error("PNG file does not exist!");
	}

	std::unique_ptr<std::FILE, decltype(&fclose)> pngFile{
#ifdef _MSC_VER
	_wfopen(pngPath.c_str(), L"rb"),
#else
	std::fopen(pngPath.c_str(), "rb"),
#endif
	fclose
	};

	if (!pngFile)
	{
		throw std::runtime_error("PNG file couldn't be opened!");
	}

	constexpr auto HEADER_SIZE{ 4 };
	png_byte header[HEADER_SIZE]{ };
	if (std::fread(header, 1, HEADER_SIZE, pngFile.get()) != HEADER_SIZE)
	{
		throw std::runtime_error("Probably not a png file (header short)!");
	}

	if (png_sig_cmp(header, 0, HEADER_SIZE))
	{
		throw std::runtime_error("Probably not a png file (png file header mismatch)!");
	}

	png_structp pngData{ png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr) };
	if (!pngData)
	{
		throw std::runtime_error("Could not allocate png struct!");
	}

	png_infop pngInfo{ png_create_info_struct(pngData) };
	if (!pngInfo)
	{
		png_destroy_read_struct(&pngData, nullptr, nullptr);
		throw std::runtime_error("Could not allocate png info struct!");
	}

	png_infop pngEndInfo{ png_create_info_struct(pngData) };
	if (!pngEndInfo)
	{
		png_destroy_read_struct(&pngData, &pngInfo, nullptr);
		throw std::runtime_error("Could not allocate png end info struct!");
	}

	if (setjmp(png_jmpbuf(pngData)))
	{
		png_destroy_read_struct(&pngData, &pngInfo, &pngEndInfo);
		throw std::runtime_error("Problem reading png file!");
	}

	png_init_io(pngData, pngFile.get());
	png_set_sig_bytes(pngData, HEADER_SIZE);

	// TODO: Swap for low level API if needs come around. This outputs 8bit color data always.
	png_read_png(pngData, pngInfo, PNG_TRANSFORM_SCALE_16 | PNG_TRANSFORM_EXPAND, nullptr);

	auto width		{ png_get_image_width(pngData, pngInfo) };
	auto height		{ png_get_image_height(pngData, pngInfo) };
	auto bitDepth	{ png_get_bit_depth(pngData, pngInfo) };
	auto colorType	{ png_get_color_type(pngData, pngInfo) };

	auto rowBytes { width };
	switch (colorType)
	{
		case PNG_COLOR_TYPE_RGB:
		{
			rowBytes *= 3;
		} break;
		case PNG_COLOR_TYPE_RGBA:
		{
			rowBytes *= 4;
		} break;
		default: break;
	}
	switch (bitDepth)
	{
		case 8: { } break;
		case 16: {
			rowBytes *= 2;
		} break;
		case 1:
		case 2:
		case 4:
		default: {
			assert(false && "Bit depths less than 8 aren't supported yet!");
		};
	}
	assert(png_get_rowbytes(pngData, pngInfo) == rowBytes && "Row bytes incorrectly calculated!");

	const auto pngRawData = png_get_rows(pngData, pngInfo);
	std::vector<unsigned char> pngDataVector;
	pngDataVector.reserve(rowBytes * height);
	std::span<const png_bytep> rowsSpan(pngRawData, height);
	for (const auto& _currRow : rowsSpan)
	{
		std::span<const png_byte> rowSpan(_currRow, rowBytes);
		for (const auto& byte : rowSpan)
		{
			pngDataVector.push_back(byte);
		}
	}

	auto* retVal = new Sprite(pngPath, width, height, colorType, pngDataVector);
	resources[pngPath.string()] = std::unique_ptr<Resource>(retVal);

	png_destroy_read_struct(&pngData, &pngInfo, &pngEndInfo);
	return retVal;
}

template<>
Sound* Manager::CreateResource(const std::filesystem::path& soundPath)
{
	if (!std::filesystem::exists(soundPath))
	{
		throw std::runtime_error("Sound file does not exist!");
	}
	
	drwav wav;
	if (!drwav_init_file(&wav, soundPath.string().c_str(), nullptr))
	{
		drwav_uninit(&wav);
		throw std::runtime_error("WAV sound file could not be opened!");
	}

	auto expectedSamples = wav.totalPCMFrameCount * wav.channels;
	std::vector<unsigned int> decodedInterleavedPCMFrames(expectedSamples);
	auto samplesDecoded = drwav_read_pcm_frames(&wav, wav.totalPCMFrameCount, decodedInterleavedPCMFrames.data());

	if (samplesDecoded != expectedSamples)
	{
		spdlog::warn(
			"Expected samples decoded from file {} differ from actually decoded samples ({}/{})",
			soundPath.string(), samplesDecoded, expectedSamples
		);
	}
	
	unsigned int bufferID { };
	alGenBuffers(1, &bufferID);
	if (Audio::Manager::CheckOpenALErr())
	{
		throw std::runtime_error("Could not allocate OpenAL sound buffer!");
	}

	auto sizeInBytes = samplesDecoded * sizeof(unsigned int);
	if (wav.bitsPerSample == 8)
	{
		if (wav.channels == 1)
		{
			alBufferData(bufferID, AL_FORMAT_MONO8, decodedInterleavedPCMFrames.data(), sizeInBytes, wav.sampleRate);
		}
		else
		{
			alBufferData(bufferID, AL_FORMAT_STEREO8, decodedInterleavedPCMFrames.data(), sizeInBytes, wav.sampleRate);
		}
	}
	else if (wav.bitsPerSample == 16)
	{
		if (wav.channels == 1)
		{
			alBufferData(bufferID, AL_FORMAT_MONO16, decodedInterleavedPCMFrames.data(), sizeInBytes, wav.sampleRate);
		}
		else
		{
			alBufferData(bufferID, AL_FORMAT_STEREO16, decodedInterleavedPCMFrames.data(), sizeInBytes, wav.sampleRate);
		}
	}
	if (Audio::Manager::CheckOpenALErr())
	{
		throw std::runtime_error("Could not buffer data to OpenAL sound buffer!");
	}

	auto* retVal = new Sound(soundPath, wav.channels, decodedInterleavedPCMFrames, bufferID);
	resources[soundPath.string()] = std::unique_ptr<Sound>(retVal);

	drwav_uninit(&wav);
	return retVal;
}

Shader* Manager::CreateDefaultShader(
	const std::string& id,
	const std::string_view& vertexShader, const std::string_view& fragShader
)
{
	resources[id] = std::unique_ptr<Resource>(new Shader(id, vertexShader, fragShader));
	return static_cast<Shader*>(resources[id].get());
}

}