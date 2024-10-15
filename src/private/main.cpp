#include "engine.h"

#include "shader.h"
#include "sprite.h"
#include "spriterenderer.h"
#include "renderer.h"
#include "transform.h"

int main()
{
	Core::Engine engine;

	// TODO: Remove, replace with scene entities.
	auto* defaultShader = engine.resourceManager->GetResource<Resources::Shader>("defaultShader");
	auto* testSprite = engine.resourceManager->GetOrCreateResource<Resources::Sprite>("assets/protect-sky-3.png");
	auto* testSound = engine.resourceManager->GetOrCreateResource<Resources::Sound>("assets/sfx_wpn_cannon1.wav");
	defaultShader->SetInt("texture0", 0);

	auto& _registry = engine.scene.registry;
	auto _ent = _registry.create();
	auto& _transform = _registry.emplace<World::Transform>(_ent);
	_transform.position = { .5f * (engine.window->width - testSprite->width), .5f * (engine.window->height - testSprite->height), 0.f };
	auto& _spriteRend = _registry.emplace<Graphics::SpriteRenderer>(_ent, *engine.renderer);

	_registry.patch<Graphics::SpriteRenderer>(_ent, [defaultShader, testSprite](auto& spriteRenderer) {
		spriteRenderer.shader = defaultShader;
		spriteRenderer.SetSprite(*testSprite);
	});

	engine.Run();
	return 0;
}