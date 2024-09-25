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

	Sprite(const std::filesystem::path path, std::vector<unsigned char>& pngData) :
		Resource(path.string()), pngData(pngData) { }

	std::vector<unsigned char> pngData;
};

}