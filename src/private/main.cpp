#include "engine.h"

#include "shader.h"
#include "spriterenderer.h"
#include "renderer.h"

int main()
{
	Core::Engine engine;

	// TODO: Remove, replace with scene entities.
	auto& _spriteRend = engine.renderer->spriteRenderers.emplace_back(*engine.renderer);
	auto* defaultShader = engine.resourceManager->GetResource<Resources::Shader>("defaultShader");
	defaultShader->SetInt("texture0", 0);
	_spriteRend.shader = defaultShader;
	_spriteRend.SetSprite(*engine.resourceManager->GetOrCreateResource<Resources::Sprite>("assets/protect-sky-3.png"));

	engine.Run();
	return 0;
}