#include "sceneinspector.h"

#include <imgui.h>

namespace Tools
{

void SceneInspector::Draw()
{
	if (!scene)
	{
		return;
	}

	scene->registry.each([&](auto& ent) {
		char _id[50]{ };
		sprintf(_id, "Entity %d", ent);
		if (ImGui::Selectable(_id, ent == selectedEnt)) {
			selectedEnt = ent;
		}
	});
}

}