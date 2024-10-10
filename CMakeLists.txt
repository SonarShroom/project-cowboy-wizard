cmake_minimum_required(VERSION 3.19)
project(ProjectCowboyWizard
	VERSION 0.0.0.1
	DESCRIPTION "Small game about a wizard that likes revolvers and cowboy hats. Made from scratch."
	LANGUAGES C CXX
)

add_executable(cowboy_wizard_game
	src/private/core/engine.cpp

	src/private/graphics/renderer.cpp
	src/private/graphics/spriterenderer.cpp
	src/private/graphics/texture.cpp
	src/private/graphics/window.cpp

	src/private/input/manager.cpp

	src/private/resources/manager.cpp
	src/private/resources/shader.cpp
	src/private/resources/sprite.cpp

	src/private/world/scene.cpp

	src/private/main.cpp
)

target_include_directories(cowboy_wizard_game PUBLIC src/public)

target_include_directories(cowboy_wizard_game PRIVATE src/public/core)
target_include_directories(cowboy_wizard_game PRIVATE src/private/core)

target_include_directories(cowboy_wizard_game PRIVATE src/public/graphics)
target_include_directories(cowboy_wizard_game PRIVATE src/private/graphics)

target_include_directories(cowboy_wizard_game PRIVATE src/public/input)
target_include_directories(cowboy_wizard_game PRIVATE src/private/input)

target_include_directories(cowboy_wizard_game PRIVATE src/public/resources)
target_include_directories(cowboy_wizard_game PRIVATE src/private/resources)

target_include_directories(cowboy_wizard_game PRIVATE src/public/world)
target_include_directories(cowboy_wizard_game PRIVATE src/private/world)

set_target_properties(cowboy_wizard_game PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED TRUE
)

find_package(EnTT CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(PNG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

target_link_libraries(cowboy_wizard_game PRIVATE
	EnTT::EnTT
	glad::glad
	glfw
	glm::glm
	PNG::PNG
	spdlog::spdlog
)

install(TARGETS cowboy_wizard_game
	CONFIGURATIONS Debug
	RUNTIME DESTINATION ${CMAKE_CURRENT_LIST_DIR}/build
	LIBRARY DESTINATION ${CMAKE_CURRENT_LIST_DIR}/build
)

install(TARGETS cowboy_wizard_game
	CONFIGURATIONS Release
	RUNTIME DESTINATION ${CMAKE_CURRENT_LIST_DIR}/build
	LIBRARY DESTINATION ${CMAKE_CURRENT_LIST_DIR}/build
)

install(FILES
	$<TARGET_RUNTIME_DLLS:cowboy_wizard_game>
	DESTINATION ${CMAKE_CURRENT_LIST_DIR}/build
	COMPONENT cowboy_wizard_game
)

install(IMPORTED_RUNTIME_ARTIFACTS cowboy_wizard_game DESTINATION ${CMAKE_CURRENT_LIST_DIR}/build)

install(DIRECTORY assets DESTINATION ${CMAKE_CURRENT_LIST_DIR}/build)

install(
	DIRECTORY $<PATH:GET_PARENT_PATH,$<TARGET_FILE:cowboy_wizard_game>>/
	CONFIGURATIONS Debug
	DESTINATION ${CMAKE_CURRENT_LIST_DIR}/build
	FILES_MATCHING PATTERN "*.dll"
)

install(
	DIRECTORY $<PATH:GET_PARENT_PATH,$<TARGET_FILE:cowboy_wizard_game>>/
	CONFIGURATIONS Release
	DESTINATION ${CMAKE_CURRENT_LIST_DIR}/build
	FILES_MATCHING PATTERN "*.dll"
)