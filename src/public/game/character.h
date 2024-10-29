#pragma once

#include <entt/entt.hpp>

#include "textureatlas.h"

namespace Core
{
	class Engine;
}

namespace Graphics
{
	class AnimationRenderer;
	class Window;
}

namespace Resources
{
	class Shader;
	class Sprite;
}

namespace World
{
	class Scene;
	class Transform;
}

namespace Game
{

class Character
{
public:
	enum class CurrentState
	{
		IDLE = 0,
		WALK,
		ATTACK,
		HURT,
		DEAD,
		COUNT
	} currentState { CurrentState::IDLE };

	Character(Core::Engine& engine, World::Scene& scene);

	World::Scene& scene;

	entt::entity entity { };
	Graphics::TextureAtlas animAtlas[(std::size_t)CurrentState::COUNT] { };
	World::Transform& transform;
	Graphics::AnimationRenderer& animRenderer;
};

}