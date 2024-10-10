#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace Graphics
{

class Renderer;

class Window
{
public:
	enum class PresentMode
	{
		WINDOWED,
		BORDERLESS_FULLSCREEN, // Ignores window dimensions requested.
		FULLSCREEN
	};

	bool shouldClose { };
	int width { }, height { };
	Renderer* renderer { };

	Window(
		const std::string& title,
		const int width,
		const int height,
		const PresentMode initialMode = PresentMode::WINDOWED
	);
	~Window();

	inline auto GetRawWindow() const { return window; }

	void SwapBuffers();
	void PollEvents();

private:
	std::string windowTitle;
	PresentMode presentMode	{ PresentMode::WINDOWED };
	GLFWwindow* window { };
};

}