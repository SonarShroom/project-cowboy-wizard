#pragma once

#include <filesystem>
#include <vector>

#include "resource.h"

namespace Resources
{

class Sprite : public Resource
{
public:
	static constexpr auto type { Type::SPRITE };

	Sprite(
		const std::filesystem::path path,
		const unsigned int width, const unsigned int height,
		const unsigned int colorType,
		std::vector<unsigned char>& pngData) :
			Resource(path.string(), type),
			width(width), height(height),
			colorType(colorType),
			pngData(pngData) { }

	unsigned int width		{ };
	unsigned int height		{ };
	unsigned int colorType	{ };
	std::vector<unsigned char> pngData;
};

}