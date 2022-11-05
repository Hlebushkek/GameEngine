cmake_minimum_required(VERSION 3.24)

project(Engine)

enable_language(C)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${PROJECT_NAME}/include
    ${PROJECT_NAME}/vendors/SDL/build/FinalBuild/include/SDL2 ${PROJECT_NAME}/vendors/SDL_image
    ${PROJECT_NAME}/vendors/glad/include ${PROJECT_NAME}/vendors/glm
    ${PROJECT_NAME}/vendors/imgui
)
file(GLOB SOURCES "${PROJECT_NAME}/src/*.cpp" "${PROJECT_NAME}/include/*.hpp")
add_definitions(-DENGINE_BUILD_DLL)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

add_subdirectory(${PROJECT_NAME}/vendors/glad/)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(${PROJECT_NAME}/vendors/glm/)
target_link_libraries(${PROJECT_NAME} glm)

file(GLOB IMGUI_SOURCES "${PROJECT_NAME}/vendors/imgui/*.cpp" "${PROJECT_NAME}/vendors/imgui/*.h"
    "${PROJECT_NAME}/vendors/imgui/backends/imgui_impl_sdl.cpp" "${PROJECT_NAME}/vendors/imgui/backends/imgui_impl_sdl.h"
    "${PROJECT_NAME}/vendors/imgui/backends/imgui_impl_opengl3.cpp" "${PROJECT_NAME}/vendors/imgui/backends/imgui_impl_opengl3.h"
)
add_library(imgui STATIC ${IMGUI_SOURCES})

target_link_libraries(${PROJECT_NAME} -LC:/Users/hlebushkek/Documents/GameEngine/Engine/vendors/SDL/build/FinalBuild/lib)
target_link_libraries(${PROJECT_NAME} imgui -lSDL2maind -lSDL2d -lSDL2_image)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_BINARY_DIR}/libEngine.dll
                ../Sandbox/libEngine.dll)