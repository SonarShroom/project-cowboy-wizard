#pragma once

#include "tools/window.h"

#include <entt/entt.hpp>

#include "scene.h"

namespace Tools
{

class SceneInspector final : public IWindow
{
public:
	SceneInspector(World::Scene* scene = {}) : IWindow("Scene Inspector"), scene(scene) { }

	void Draw();

	World::Scene* scene { };
	entt::entity selectedEnt { entt::null };
};

}