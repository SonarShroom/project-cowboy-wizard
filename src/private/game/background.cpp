#include "background.h"

#include "graphics/window.h"
#include "graphics/spriterenderer.h"
#include "resources/shader.h"
#include "resources/sprite.h"
#include "world/scene.h"
#include "world/transform.h"

namespace Game
{

Background::Background(
	Graphics::Window& window,
	World::Scene& scene,
	Resources::Sprite& bgSprite,
	Resources::Shader& defaultShader) :
		scene(scene),
		bgSprite(bgSprite),
		entity(scene.registry.create()),
		bgTransform(scene.registry.emplace<World::Transform>(entity)),
		bgRenderer(scene.registry.emplace<Graphics::SpriteRenderer>(entity, *window.renderer))
{
	scene.registry.patch<Graphics::SpriteRenderer>(entity, [&window, &bgSprite, &defaultShader](auto& bgRenderer) {
		bgRenderer.shader = &defaultShader;
		bgRenderer.SetSprite(bgSprite);
		bgRenderer.width = window.width;
		bgRenderer.height = window.height;
	});
}

}