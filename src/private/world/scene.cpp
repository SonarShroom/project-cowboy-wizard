#include "scene.h"

#include <glm/gtc/matrix_transform.hpp>

#include "animationrenderer.h"
#include "sprite.h"
#include "spriterenderer.h"
#include "texture.h"
#include "textureatlas.h"
#include "transform.h"

namespace World
{

Scene::Scene()
{
	spriteTransformObserver.connect(
		registry,
		entt::collector.update<Transform>().where<Graphics::SpriteRenderer>()
	);

	registry.on_update<Graphics::SpriteRenderer>().connect<&Scene::UpdateSpriteRendererMatrix>(this);

	animTransformObserver.connect(
		registry,
		entt::collector.update<Transform>().where<Graphics::AnimationRenderer>()
	);

	registry.on_update<Graphics::AnimationRenderer>().connect<&Scene::UpdateAnimationRendererMatrix>(this);
}

void Scene::Update(float dt)
{
	for (const auto _ent : spriteTransformObserver) {
		UpdateSpriteRendererMatrix(registry, _ent);
	}
	spriteTransformObserver.clear();

	for (const auto _ent : animTransformObserver) {
		UpdateSpriteRendererMatrix(registry, _ent);
	}
	spriteTransformObserver.clear();

	auto animRendererView = registry.view<Graphics::AnimationRenderer>();
	for (auto [ent, renderer] : animRendererView.each())
	{
		renderer.Update(dt);
	}
}

void Scene::UpdateSpriteRendererMatrix(entt::registry& registry, entt::entity ent)
{
	auto [transform, spriteRenderer] = registry.get<Transform, Graphics::SpriteRenderer>(ent);

	const auto* _sprite = spriteRenderer.GetSprite();
	if (!_sprite)
	{
		return;
	}

	auto& _modelMat = spriteRenderer.modelMatrix;
	_modelMat = glm::mat4(1.0f);
	_modelMat = glm::translate(_modelMat, transform.position);

	// Rotate around the center
	_modelMat = glm::translate(_modelMat, glm::vec3(.5f * spriteRenderer.width, .5f * spriteRenderer.width, 0.0f));
	_modelMat = glm::rotate(_modelMat, transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	_modelMat = glm::rotate(_modelMat, transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	_modelMat = glm::rotate(_modelMat, transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	_modelMat = glm::translate(_modelMat, glm::vec3(-.5f * spriteRenderer.width, -.5f * spriteRenderer.height, 0.0f));

	_modelMat = glm::scale(_modelMat, glm::vec3(spriteRenderer.width, spriteRenderer.height, 1.0f));
	_modelMat = glm::scale(_modelMat, transform.scale);
}

void Scene::UpdateAnimationRendererMatrix(entt::registry& registry, entt::entity ent)
{
	auto [transform, animRenderer] = registry.get<Transform, Graphics::AnimationRenderer>(ent);

	const auto* atlas = animRenderer.GetTextureAtlas();
	if (!atlas)
	{
		return;
	}

	const auto* sprite = atlas->texture->sprite;

	auto& _modelMat = animRenderer.modelMatrix;
	_modelMat = glm::mat4(1.0f);
	_modelMat = glm::translate(_modelMat, transform.position);

	// Rotate around the center
	_modelMat = glm::translate(_modelMat, glm::vec3(.5f * atlas->frameWidth, .5f * atlas->frameHeight, 0.0f));
	_modelMat = glm::rotate(_modelMat, transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	_modelMat = glm::rotate(_modelMat, transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	_modelMat = glm::rotate(_modelMat, transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	_modelMat = glm::translate(_modelMat, glm::vec3(-.5f * atlas->frameWidth, -.5f * atlas->frameHeight, 0.0f));

	_modelMat = glm::scale(_modelMat, glm::vec3(atlas->frameWidth, atlas->frameHeight, 1.0f));
	_modelMat = glm::scale(_modelMat, transform.scale);
}

}