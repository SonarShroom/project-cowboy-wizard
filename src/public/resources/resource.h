#pragma once

#include <string>

namespace Resources
{

class Resource
{
public:
	Resource(const std::string& ID) : ID(ID) { }
	virtual ~Resource() = default;

private:
	std::string ID;
};

}