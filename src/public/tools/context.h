#pragma once

#include "graphics/window.h"

#include "tools/window.h"
#include "entityinspector.h"
#include "sceneinspector.h"

namespace Tools
{

class Context
{
public:
	Context() = default;
	Context(const Graphics::Window& window, World::Scene& scene);
	~Context();

	void Render();

	bool isInitialized { };

	SceneInspector sceneInspector;
	EntityInspector entInspector;

	std::array<IWindow*, 2> toolWindows {
		&sceneInspector,
		&entInspector,
	};
};

}