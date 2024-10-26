#include "core/engine.h"

#include <stdexcept>

#include <spdlog/spdlog.h>

namespace Core
{

const std::string_view vertShader =
R"(#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 2) in vec2 aTexCoord;

out vec4 ourColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
	ourColor = aCol;
	TexCoord = aTexCoord;
}
)";

const std::string_view fragShader =
R"(#version 330 core
in vec4 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture0;

void main()
{
	vec4 texCol = texture(texture0, TexCoord);
	if (texCol.a < 0.05)
	{
		discard;
	}
	FragColor = texCol * ourColor;
}
)";

Engine::Engine()
{
	using namespace Graphics;
	try
	{
		audioManager = std::make_unique<Audio::Manager>();
		window = std::make_unique<Window>("Project Cowboy Wizard", 1920, 1080, Window::PresentMode::WINDOWED);
		renderer = std::make_unique<Renderer>(*window, scene);
		inputManager = std::make_unique<Input::Manager>(*window);
		resourceManager = std::make_unique<Resources::Manager>();

		resourceManager->CreateDefaultShader("defaultShader", vertShader, fragShader);
	}
	catch (const std::runtime_error& e)
	{
		spdlog::error(e.what());
	}
}

void Engine::Run()
{
	frameBegin = frameEnd = glfwGetTime();
	while (!window->shouldClose)
	{
		window->PollEvents();
		inputManager->Process();

		scene.Update(frameBegin - frameEnd);
		renderer->Render();

		window->SwapBuffers();
		frameEnd = frameBegin;
		frameBegin = glfwGetTime();
	}
}

}