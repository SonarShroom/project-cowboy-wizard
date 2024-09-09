cmake_minimum_required(VERSION 3.19)
project(ProjectCowboyWizard
	VERSION 0.0.0.1
	DESCRIPTION "Small game about a wizard that likes revolvers and cowboy hats. Made from scratch."
	LANGUAGES C CXX
)

add_executable(cowboy_wizard_game
	src/main.cpp
)

set_target_properties(cowboy_wizard_game PROPERTIES CXX_STANDARD 20)

install(TARGETS cowboy_wizard_game)