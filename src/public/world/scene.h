#pragma once

#include <entt/entt.hpp>

namespace World
{
	
class Scene
{
public:
	void Update(float dt);

	entt::registry registry;
};

}