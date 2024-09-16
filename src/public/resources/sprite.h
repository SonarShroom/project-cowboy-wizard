#pragma once

#include <filesystem>

#include "resource.h"

namespace Resources
{

class Sprite : public Resource
{
public:
	Sprite(const std::string ID, const std::filesystem::path pngPath);
	~Sprite() = default;

	unsigned int width	{ };
	unsigned int height	{ };
	int bitDepth		{ };
	int colorType		{ };
	int interlaceType	{ };
};
}