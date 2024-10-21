#pragma once

#include "window.h"

#include <entt/entt.hpp>
#include <imgui.h>

#include "sceneinspector.h"

namespace Audio
{
	class Source;
}

namespace Graphics
{
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
		if (!ImGui::CollapsingHeader("Unknown Component"))
		{
			return;
		}
		ImGui::Text("Breakpoint this function to find out which type it then implement it.");
	}

	template<>
	void InspectComponent(Graphics::SpriteRenderer& renderer);

	template<>
	void InspectComponent(World::Transform& transform);

	template<>
	void InspectComponent(Audio::Source& source);

	const SceneInspector& inspector;
};

}