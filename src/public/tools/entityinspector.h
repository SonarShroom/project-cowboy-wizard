#pragma once

#include "window.h"

#include <concepts>

#include <entt/entt.hpp>
#include <imgui.h>

#include "sceneinspector.h"

namespace Audio
{
	class Source;
}

namespace Graphics
{
	class AnimationRenderer;
	class SpriteRenderer;
}

namespace World
{
	class Transform;
}

namespace Tools
{

class EntityInspector final : public IWindow
{
public:
	EntityInspector(const SceneInspector& inspector) : IWindow("Entity Inspector"), inspector(inspector) { }

	void Draw();

	template<typename T>
	void InspectComponent(T& comp)
	{
		ImGui::Text("Inspector for this component was not implemented.");
	}

	void InspectComponent(Graphics::AnimationRenderer& renderer);

	void InspectComponent(Graphics::SpriteRenderer& renderer);

	void InspectComponent(World::Transform& transform);

	void InspectComponent(Audio::Source& source);

	const SceneInspector& inspector;
};

}