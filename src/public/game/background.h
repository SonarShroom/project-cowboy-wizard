#pragma once

#include <entt/entt.hpp>

namespace Graphics
{
	class SpriteRenderer;
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

class Background
{
public:
	Background(Graphics::Window& window, World::Scene& scene, Resources::Sprite& bgSprite, Resources::Shader& defaultShader);

	World::Scene& scene;
	Resources::Sprite& bgSprite;

	entt::entity entity { };
	World::Transform& bgTransform;
	Graphics::SpriteRenderer& bgRenderer;
};

}