#include "core/engine.h"

#include <stdexcept>

namespace Core
{

const std::string_view vertShader =
R"(#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTexCoord;

out vec4 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 0.0f, 1.0);
	
}
)";

const std::string_view fragShader =
R"(#version 330 core
in vec4 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
	FragColor = texture(ourTexture, TexCoord) * ourColor;
}
)";

Engine::Engine()
{
	using namespace Graphics;
	try
	{
		window = std::make_unique<Window>("Project Cowboy Wizard", 1920, 1080, Window::PresentMode::WINDOWED);
		renderer = std::make_unique<Renderer>(*window);
		inputManager = std::make_unique<Input::Manager>(*window);
		resourceManager = std::make_unique<Resources::Manager>();

		resourceManager->CreateDefaultShader("defaultShader", vertShader, fragShader);
	}
	catch (const std::runtime_error& e)
	{
		throw e;
	}
}

void Engine::Run()
{
	while (!window->shouldClose)
	{
		inputManager->Process();

		renderer->Render();

		window->PollEvents();
		window->SwapBuffers();
	}
}

}