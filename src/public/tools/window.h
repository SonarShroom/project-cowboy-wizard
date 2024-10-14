#pragma once

#include <string_view>

namespace Tools
{

class IWindow
{
public:
	IWindow(const std::string_view name) : name(name) { }
	virtual ~IWindow() = default;

	virtual void Draw() = 0;

	const std::string_view name;
};

}