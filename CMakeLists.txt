cmake_minimum_required(VERSION 3.24)

project(Engine)

enable_language(C)
enable_language(CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if(APPLE)
    enable_language(OBJC)
endif()

add_definitions(-DENGINE_BUILD_DLL)
add_definitions(-DIMGUI_IMPL_METAL_CPP)

add_subdirectory(vendors/glad/)
add_subdirectory(vendors/glm/)
add_subdirectory(vendors/SDL)
add_subdirectory(vendors/SDL_image)

include_directories(
    include/
    vendors/glad/include /vendors/glm
    vendors/imgui
)
include_directories(
    vendors/SDL/include vendors/SDL/src
    vendors/SDL_image/include
)
include_directories(
    vendors/metal-cpp/
)

file(GLOB SOURCES "src/*.cpp" "include/*.hpp" "include/*.h")
file(GLOB IMGUI_SOURCES "vendors/imgui/*.cpp" "vendors/imgui/*.h"
    "vendors/imgui/backends/imgui_impl_sdl3.cpp" "vendors/imgui/backends/imgui_impl_sdl3.h"
)

if (APPLE)
    add_compile_definitions(ENABLE_METAL)

    list(APPEND SOURCES 
        "src/RenderingBackends/RendererImplMetal.cpp"
        "src/RenderingBackends/ShaderImplMetal.cpp"
        "src/RenderingBackends/TextureImplMetal.cpp"
        "src/RenderingBackends/MeshMetal.cpp")
    list(APPEND IMGUI_SOURCES 
        "vendors/imgui/backends/imgui_impl_metal.mm"
        "vendors/imgui/backends/imgui_impl_metal.h")
else()
    list(APPEND SOURCES 
        "src/RenderingBackends/RendererImplGL.cpp"
        "src/RenderingBackends/ShaderImplGL.cpp"
        "src/RenderingBackends/TextureImplGL.cpp"
        "src/RenderingBackends/MeshGL.cpp")
    list(APPEND IMGUI_SOURCES 
        "vendors/imgui/backends/imgui_impl_opengl3.cpp"
        "vendors/imgui/backends/imgui_impl_opengl3.h")
endif()

link_directories(
    ${PROJECT_SOURCE_DIR}/../build/GameEngine/vendors/SDL/
    ${PROJECT_SOURCE_DIR}/../build/GameEngine/vendors/SDL_image/
)

add_library(imgui STATIC ${IMGUI_SOURCES})
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} SDL3 SDL3_image)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework Foundation")
    target_link_libraries(${PROJECT_NAME} "-framework QuartzCore")
    target_link_libraries(${PROJECT_NAME} "-framework Metal")
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:SDL3-shared> ${CMAKE_CURRENT_BINARY_DIR}

    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:SDL3_image> ${CMAKE_CURRENT_BINARY_DIR}
)