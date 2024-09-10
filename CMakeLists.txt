cmake_minimum_required(VERSION 3.19)
project(ProjectCowboyWizard
	VERSION 0.0.0.1
	DESCRIPTION "Small game about a wizard that likes revolvers and cowboy hats. Made from scratch."
	LANGUAGES C CXX
)

add_executable(cowboy_wizard_game
	src/main.cpp
	src/graphics/private/window.cpp
)

target_include_directories(cowboy_wizard_game PUBLIC src/graphics)
target_include_directories(cowboy_wizard_game PRIVATE src/graphics/private)

set_target_properties(cowboy_wizard_game PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED TRUE)

find_package(EnTT CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

target_link_libraries(cowboy_wizard_game PRIVATE
	EnTT::EnTT
	glfw
	spdlog::spdlog
)

install(TARGETS cowboy_wizard_game)