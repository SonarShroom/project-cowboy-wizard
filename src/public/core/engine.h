#pragma once

#include <memory>

#include "graphics/renderer.h"
#include "graphics/window.h"

#include "input/manager.h"

#include "resources/manager.h"

#include "world/scene.h"

namespace Core
{

class Engine
{
public:
	Engine();

	void Run();

	std::unique_ptr<Graphics::Window> window;
	World::Scene scene;
	std::unique_ptr<Graphics::Renderer> renderer;
	std::unique_ptr<Input::Manager> inputManager;
	std::unique_ptr<Resources::Manager> resourceManager;

	float frameBegin	{ };
	float frameEnd		{ };
};

}