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
		FONT,
		SPRITE,
		SHADER,
		SOUND,
	} const resType = Type::INVALID;
	static constexpr Type type = Type::INVALID;

	Resource(const std::string& id, const Type&& type) : id(id), resType(type) { }
	virtual ~Resource() = default;

	const std::string id;
};

}