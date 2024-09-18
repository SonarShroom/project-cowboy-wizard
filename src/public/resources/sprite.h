#pragma once

#include <filesystem>

#include "resource.h"

namespace Resources
{

class Sprite : public Resource
{
public:
	static constexpr auto type { Type::SPRITE };

	Sprite(const std::string ID, const std::filesystem::path pngPath);
	~Sprite() = default;
};
}