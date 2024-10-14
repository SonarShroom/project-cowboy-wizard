#include "entityinspector.h"

#include <glm/gtc/type_ptr.hpp>

#include "sprite.h"
#include "spriterenderer.h"
#include "texture.h"
#include "transform.h"

namespace Tools
{

void EntityInspector::Draw()
{
	auto _ent = inspector.selectedEnt;
	if (_ent != entt::null)
	{
		auto& _reg = inspector.scene->registry;
		auto* _transform = _reg.try_get<World::Transform>(_ent);
		if (_transform)
		{
			InspectComponent(*_transform);
		}

		auto* _spriteRenderer = _reg.try_get<Graphics::SpriteRenderer>(_ent);
		if (_spriteRenderer)
		{
			InspectComponent(*_spriteRenderer);
		}
	}
}

template<>
void EntityInspector::InspectComponent(World::Transform& transform)
{
	if (!ImGui::CollapsingHeader("Transform"))
	{
		return;
	}

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

template<>
void EntityInspector::InspectComponent(Graphics::SpriteRenderer& spriteRenderer)
{
	if (!ImGui::CollapsingHeader("Sprite Renderer"))
	{
		return;
	}

	ImGui::Text("Image");
	const auto* texture = spriteRenderer.GetTexture();
	const auto* sprite = spriteRenderer.GetSprite();
	if (sprite && texture)
	{
		const auto id		{ (ImTextureID)texture->id };
		const ImVec2 size	{ (float)sprite->width, (float)sprite->height };
		ImGui::Image(id, size);
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
		ImGui::SameLine();
		ImGui::TextColored(ImColor(255, 0, 0, 255), "No sprite/texture assigned.");
	}
}

}