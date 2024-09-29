#include "resources/manager.h"

#include <functional>
#include <memory>
#include <stdexcept>
#include <span>

#include <cassert>
#include <cstdio>

#include <png.h>

#include "shader.h"
#include "sprite.h"

namespace Resources
{

template<>
Sprite* Manager::CreateResource<Sprite>(const std::filesystem::path& pngPath)
{
	std::unique_ptr<std::FILE, decltype(&fclose)> pngFile{
#ifdef _MSC_VER
	_wfopen(pngPath.c_str(), L"rb"),
#else
	std::fopen(pngPath.c_str(), L"rb"),
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
	for (auto _currRow = rowsSpan.rbegin(); _currRow != rowsSpan.rend(); _currRow++)
	{
		std::span<const png_byte> rowSpan(*_currRow, rowBytes);
		for (const auto byte : rowSpan)
		{
			pngDataVector.push_back(byte);
		}
	}

	auto* _retVal = new Sprite(pngPath, width, height, colorType, pngDataVector);
	resources[pngPath.string()] = std::unique_ptr<Resource>(_retVal);

	return _retVal;
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