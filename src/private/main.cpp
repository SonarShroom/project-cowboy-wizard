#include "engine.h"

#include "animationrenderer.h"
#include "source.h"
#include "shader.h"
#include "sprite.h"
#include "spriterenderer.h"
#include "renderer.h"
#include "texture.h"
#include "textureatlas.h"
#include "transform.h"

int main()
{
	Core::Engine engine;

	// TODO: Remove, replace with scene entities.
	auto* defaultShader = engine.resourceManager->GetResource<Resources::Shader>("defaultShader");
	auto* testSprite = engine.resourceManager->GetOrCreateResource<Resources::Sprite>("assets/Samurai/Attack_1.png");
	auto* testSound = engine.resourceManager->GetOrCreateResource<Resources::Sound>("assets/sfx_wpn_cannon1.wav");
	defaultShader->SetInt("texture0", 0);

	auto& registry = engine.scene.registry;
	auto ent = registry.create();
	auto& transform = registry.emplace<World::Transform>(ent);
	transform.position = { .5f * (engine.window->width - testSprite->width), .5f * (engine.window->height - testSprite->height), 0.f };
	auto& spriteRend = registry.emplace<Graphics::AnimationRenderer>(ent, *engine.renderer);

	auto& source = registry.emplace<Audio::Source>(ent);

	registry.patch<Graphics::AnimationRenderer>(ent, [defaultShader, testSprite](auto& animRenderer) {
		animRenderer.shader = defaultShader;
		animRenderer.fps = 10;
		auto* atlas = new Graphics::TextureAtlas(*testSprite, 6, 1);
		animRenderer.SetTextureAtlas(atlas);
	});
	source.SetSound(testSound);
	source.Play();

	engine.Run();
	return 0;
}