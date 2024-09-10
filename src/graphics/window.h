#pragma once

#include <memory>
#include <string>

#include <GLFW/glfw3.h>

namespace Graphics
{

class Window
{
public:
	enum class CreationError {
		CouldNotInitGLFW,
		CouldNotCreateWindow,
		Other
	};

	static std::unique_ptr<Window> CreateWindow(
		const std::string& title,
		const int width, const int height
	);
	~Window();

	void Loop();

private:
	Window(const std::string& title, const int width, const int height, GLFWwindow* window) :
		windowTitle(title),
		width(width),
		height(height),
		window(window) { }

	std::string windowTitle;
	int width { }, height { };
	GLFWwindow* window { };
};

}