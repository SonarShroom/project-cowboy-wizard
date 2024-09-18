#pragma once

#include <string>

namespace Resources
{

class Resource
{
public:
	enum class Type
	{
		INVALID,
		SPRITE,
	} resType = Type::INVALID;
	static constexpr Type type = Type::INVALID;

	Resource(const std::string& path) : path(path) { }
	virtual ~Resource() = default;

	const std::string path;
};

}