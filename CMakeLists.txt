cmake_minimum_required(VERSION 3.24)

project(Engine)

enable_language(C)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DENGINE_BUILD_DLL)

add_subdirectory(vendors/glad/)
add_subdirectory(vendors/glm/)
add_subdirectory(vendors/SDL)
add_subdirectory(vendors/SDL_image)

include_directories(
    /include
    vendors/glad/include /vendors/glm
    vendors/imgui
)
include_directories(
    vendors/SDL/include vendors/SDL/src
    vendors/SDL_image/include
)

#imgui
file(GLOB IMGUI_SOURCES "vendors/imgui/*.cpp" "vendors/imgui/*.h"
    "vendors/imgui/backends/imgui_impl_sdl3.cpp" "vendors/imgui/backends/imgui_impl_sdl3.h"
    "vendors/imgui/backends/imgui_impl_opengl3.cpp" "vendors/imgui/backends/imgui_impl_opengl3.h"
)
add_library(imgui STATIC ${IMGUI_SOURCES})
#

file(GLOB SOURCES "src/*.cpp" "include/*.hpp")
link_directories(
    ${PROJECT_SOURCE_DIR}/../build/GameEngine/vendors/SDL/
    ${PROJECT_SOURCE_DIR}/../build/GameEngine/vendors/SDL_image/
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} SDL3 SDL3_image)
