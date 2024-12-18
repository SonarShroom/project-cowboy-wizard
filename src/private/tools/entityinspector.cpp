#include "entityinspector.h"

#include <glm/gtc/type_ptr.hpp>

#include "animationrenderer.h"
#include "source.h"
#include "sprite.h"
#include "spriterenderer.h"
#include "texture.h"
#include "transform.h"

namespace Tools
{

void EntityInspector::Draw()
{	
	const auto _inspectComps = [&]<typename ...CompTypes_t>(auto & reg, auto & ent) constexpr
	{
		const auto _inspectComp = [&]<typename CompType_t>(auto & reg, auto & ent) constexpr
		{
			auto* comp = reg.template try_get<CompType_t>(ent);
			if (comp)
			{
				if (!ImGui::CollapsingHeader(CompType_t::name))
				{
					return;
				}
				InspectComponent(*comp);
			}
		};
		(_inspectComp.template operator() < CompTypes_t > (reg, ent), ...);
	};

	auto ent = inspector.selectedEnt;
	if (ent != entt::null)
	{
		auto& reg = inspector.scene->registry;
		_inspectComps.template operator()<
			World::Transform,
			Graphics::AnimationRenderer,
			Graphics::SpriteRenderer,
			Audio::Source
		>(reg, ent);
	}
}

void EntityInspector::InspectComponent(World::Transform& transform)
{
	auto pos = transform.position;
	auto rot = transform.rotation;
	auto sca = transform.scale;
	bool changed { };

	ImGui::Text("Position");
	ImGui::SameLine();
	if (ImGui::InputFloat3("##pos", glm::value_ptr(pos)))
	{
		changed = true;
	}

	ImGui::Text("Rotation");
	ImGui::SameLine();
	if (ImGui::InputFloat3("##rot", glm::value_ptr(rot)))
	{
		changed = true;
	}

	ImGui::Text("Scale");
	ImGui::SameLine();
	if (ImGui::InputFloat3("##sca", glm::value_ptr(sca)))
	{
		changed = true;
	}

	if (changed)
	{
		inspector.scene->registry.patch<World::Transform>(inspector.selectedEnt,
			[&pos, &rot, &sca](auto& transform) {
				transform.position = pos;
				transform.rotation = rot;
				transform.scale = sca;
			}
		);
	}
}

void EntityInspector::InspectComponent(Graphics::AnimationRenderer& animationRenderer)
{
	const auto* atlas = animationRenderer.GetTextureAtlas();

	if (atlas)
	{
		ImGui::Text("Resource: %s", atlas->texture->sprite->id.c_str());
	}
	else
	{

	}
}

void EntityInspector::InspectComponent(Graphics::SpriteRenderer& spriteRenderer)
{
	const auto* texture = spriteRenderer.GetTexture();
	const auto* sprite = spriteRenderer.GetSprite();
	if (sprite && texture)
	{
		const auto id		{ (ImTextureID)texture->id };
		const ImVec2 size	{ (float)sprite->width, (float)sprite->height };
		//ImGui::Image(id, size);
		ImGui::Text("Resource: %s", sprite->id.c_str());
		auto width = spriteRenderer.width;
		ImGui::Text("Width");
		ImGui::SameLine();
		if (ImGui::InputScalar("##width", ImGuiDataType_U32, &width))
		{
			inspector.scene->registry.patch<Graphics::SpriteRenderer>(inspector.selectedEnt,
				[&width](Graphics::SpriteRenderer& renderer) {
					renderer.width = width;
				}
			);
		}
		ImGui::SameLine();
		if (ImGui::Button("Reset##weight"))
		{
			inspector.scene->registry.patch<Graphics::SpriteRenderer>(inspector.selectedEnt,
				[](Graphics::SpriteRenderer& renderer) {
					renderer.width = renderer.GetSprite()->width;
				}
			);
		}

		auto height = spriteRenderer.height;
		ImGui::Text("Height");
		ImGui::SameLine();
		if (ImGui::InputScalar("##height", ImGuiDataType_U32, &height))
		{
			inspector.scene->registry.patch<Graphics::SpriteRenderer>(inspector.selectedEnt,
				[&height](Graphics::SpriteRenderer& renderer) {
					renderer.height = height;
				}
			);
		}
		ImGui::SameLine();
		if (ImGui::Button("Reset##height"))
		{
			inspector.scene->registry.patch<Graphics::SpriteRenderer>(inspector.selectedEnt,
				[](Graphics::SpriteRenderer& renderer) {
					renderer.height = renderer.GetSprite()->height;
				}
			);
		}
	}
	else
	{
		ImGui::TextColored(ImColor(255, 0, 0, 255), "No sprite/texture assigned.");
	}
}

void EntityInspector::InspectComponent(Audio::Source& source)
{
	ImGui::Text("Source: %d", source.id);

	auto* sound = source.GetSound();
	ImGui::Text("Sound: %s", sound->id.c_str());
	ImGui::Text("Sound Buffer: %d", sound->bufferID);
}

}