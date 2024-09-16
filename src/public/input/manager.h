#pragma once

#include "graphics/window.h"

namespace Input
{

class Manager
{
public:
	Manager(Graphics::Window& window);

	void Process();

private:
	Graphics::Window& window;
};

}