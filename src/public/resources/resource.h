#pragma once

#include <filesystem>

namespace Resources
{

class Resource
{
public:
	enum class Type
	{
		INVALID,
		SPRITE
	} resType = Type::INVALID;
	static constexpr Type type = Type::INVALID;

	Resource(const std::filesystem::path& path) : path(path) { }
	virtual ~Resource() = default;

	const std::filesystem::path path;
};

}