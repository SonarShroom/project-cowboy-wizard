#pragma once

#include <string>

namespace Resources
{

class Resource
{
public:
	Resource(const std::string& ID);
	virtual ~Resource() = 0;

private:
	std::string ID;
};

}