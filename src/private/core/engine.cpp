#include "core/engine.h"

#include <stdexcept>

namespace Core
{

Engine::Engine()
{
	using namespace Graphics;
	try
	{
		window = std::make_unique<Window>("Project Cowboy Wizard", 1920, 1080, Window::PresentMode::WINDOWED);
		renderer = std::make_unique<Renderer>(*window);
		inputManager = std::make_unique<Input::Manager>(*window);
	}
	catch (const std::runtime_error& e)
	{
		throw e;
	}
}

void Engine::Run()
{
	while (!window->shouldClose)
	{
		inputManager->Process();

		renderer->Render();

		window->PollEvents();
		window->SwapBuffers();
	}
}

}