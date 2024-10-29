#include "character.h"

#include <string_view>

#include "animationrenderer.h"
#include "engine.h"
#include "resources/manager.h"
#include "shader.h"
#include "sprite.h"
#include "transform.h"

namespace Game
{

Character::Character(Core::Engine& engine, World::Scene& scene) :
	scene(scene),
	entity(scene.registry.create()),
	transform(scene.registry.emplace<World::Transform>(entity)),
	animRenderer(scene.registry.emplace<Graphics::AnimationRenderer>(entity, *engine.renderer))
{
	constexpr std::string_view spritePaths[(std::size_t)CurrentState::COUNT]{
		"assets/Samurai/Idle.png",
		"assets/Samurai/Walk.png",
		"assets/Samurai/Attack_1.png",
		"assets/Samurai/Hurt.png",
		"assets/Samurai/Dead.png"
	};
	constexpr unsigned int spriteDivs[(std::size_t)CurrentState::COUNT * 2] {
		6, 1, // h, v
		8, 1,
		6, 1,
		2, 1,
		3, 1
	};

	for (int currState = 0; currState < (int)CurrentState::COUNT; currState++) {
		auto* sprite = engine.resourceManager->GetOrCreateResource<Resources::Sprite>(
			spritePaths[currState].data()
		);
		animAtlas[currState] = Graphics::TextureAtlas(
			*sprite,
			spriteDivs[currState * 2],
			spriteDivs[currState * 2 + 1]
		);
	}

	scene.registry.patch<World::Transform>(entity, [&](auto& transform) {
		transform.position = { 500.f, 655.f, 0.f };
		transform.scale = { 1.5f, 1.5f, 1.f };
	});
	scene.registry.patch<Graphics::AnimationRenderer>(entity, [&](auto& renderer) {
		renderer.SetTextureAtlas(&animAtlas[(std::size_t)currentState]);
		renderer.fps = 10;
		renderer.shader = engine.resourceManager->GetResource<Resources::Shader>("defaultShader");
	});
}

}