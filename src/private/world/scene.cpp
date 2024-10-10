#include "scene.h"

#include <glm/gtc/matrix_transform.hpp>

#include "sprite.h"
#include "spriterenderer.h"
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
}

void Scene::Update(float dt)
{
	for (const auto _ent : spriteTransformObserver) {
		UpdateSpriteRendererMatrix(registry, _ent);
	}
	spriteTransformObserver.clear();
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
	_modelMat = glm::translate(_modelMat, glm::vec3(.5f * _sprite->width, .5f * _sprite->height, 0.0f));
	_modelMat = glm::rotate(_modelMat, transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	_modelMat = glm::rotate(_modelMat, transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	_modelMat = glm::rotate(_modelMat, transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	_modelMat = glm::translate(_modelMat, glm::vec3(-.5f * _sprite->width, -.5f * _sprite->height, 0.0f));

	_modelMat = glm::scale(_modelMat, glm::vec3(_sprite->width, _sprite->height, 1.0f));
	_modelMat = glm::scale(_modelMat, transform.scale);
}

}