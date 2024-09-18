#include "resources/manager.h"

#include <functional>
#include <memory>
#include <stdexcept>

#include <cstdio>

#include <png.h>

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
	png_read_png(pngData, pngInfo, PNG_TRANSFORM_IDENTITY, nullptr);

	png_read_info(pngData, pngInfo);
	unsigned int width	{ };
	unsigned int height	{ };
	int bitDepth		{ };
	int colorType		{ };
	int interlaceType	{ };
	png_get_IHDR(pngData, pngInfo, &width, &height, &bitDepth, &colorType, &interlaceType, nullptr, nullptr);
}

}