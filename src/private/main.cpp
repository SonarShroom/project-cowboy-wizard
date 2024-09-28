#include "engine.h"

#include "shader.h"
#include "spriterenderer.h"
#include "renderer.h"

int main()
{
	Core::Engine engine;

	// TODO: Remove, replace with scene entities.
	auto& _spriteRend = engine.renderer->spriteRenderers.emplace_back();
	const std::string defaultShader = "defaultShader";
	_spriteRend.shader = engine.resourceManager->GetResource<Resources::Shader>(defaultShader);
	engine.Run();
	return 0;
}