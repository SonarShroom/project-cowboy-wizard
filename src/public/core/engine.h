#pragma once

#include <memory>

#include "graphics/renderer.h"
#include "graphics/window.h"

#include "input/manager.h"

namespace Core
{

class Engine
{
public:
	Engine();

	void Run();

	std::unique_ptr<Graphics::Window> window;
	std::unique_ptr<Graphics::Renderer> renderer;
	std::unique_ptr<Input::Manager> inputManager;
};

}