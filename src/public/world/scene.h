#pragma once

#include <entt/entt.hpp>

namespace World
{
	
class Scene
{
public:
	Scene();

	void Update(float dt);

	void UpdateSpriteRendererMatrix(entt::registry& registry, entt::entity ent);

	entt::registry registry;
	entt::observer spriteTransformObserver;
};

}