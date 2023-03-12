cmake_minimum_required(VERSION 3.24)

project(Engine)

enable_language(C)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    /include
    vendors/glad/include /vendors/glm
    vendors/imgui
)
file(GLOB SOURCES "src/*.cpp" "include/*.hpp")
add_definitions(-DENGINE_BUILD_DLL)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

file(GLOB IMGUI_SOURCES "vendors/imgui/*.cpp" "vendors/imgui/*.h"
    "vendors/imgui/backends/imgui_impl_sdl3.cpp" "vendors/imgui/backends/imgui_impl_sdl3.h"
    "vendors/imgui/backends/imgui_impl_opengl3.cpp" "vendors/imgui/backends/imgui_impl_opengl3.h"
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_link_libraries(${PROJECT_NAME} imgui)

add_subdirectory(vendors/SDL)
add_subdirectory(vendors/SDL_image)
include_directories("vendors/SDL/include" "vendors/SDL/src" "vendors/SDL_image" "vendors/SDL_image/include")
target_link_libraries(${PROJECT_NAME} -LC:/Users/hlebushkek/Documents/GameEngine/build/vendors/SDL -LC:/Users/hlebushkek/Documents/GameEngine/build/vendors/SDL_image SDL3 SDL3_image)

include(CMakePrintHelpers)
cmake_print_variables(SDL2_IMAGE_INCLUDE_DIRS)
cmake_print_variables(SDL2_LIBRARIES)

add_subdirectory(vendors/glad/)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(vendors/glm/)
target_link_libraries(${PROJECT_NAME} glm)