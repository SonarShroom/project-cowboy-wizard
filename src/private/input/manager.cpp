#include "manager.h"

namespace Input
{

void KeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// TODO: Implement a rudimentary actions system, where the input is not driven by key inputs, but by actions.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		auto* _window = (Graphics::Window*) glfwGetWindowUserPointer(window);
		_window->shouldClose = true;
	}
}

Manager::Manager(Graphics::Window& window) : window(window)
{
	glfwSetKeyCallback(window.GetRawWindow(), &KeyInputCallback);
}

void Manager::Process()
{
	// TODO
}

}