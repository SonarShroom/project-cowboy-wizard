#include "window.h"

int main()
{
	auto window = Graphics::Window::CreateWindow("Hello from cowboy wizard!", 1920, 1080);
	window->Loop();
	return 0;
}