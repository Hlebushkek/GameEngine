cmake_minimum_required(VERSION 3.24)

project(Sandbox)

enable_language(C)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    /include ../Engine
    ../Engine/vendors/SDL/build/FinalBuild/include/SDL2 ../Engine/vendors/SDL_image
    ../Engine/vendors/glad/include ../Engine/vendors/glm
    ../Engine/vendors/imgui
)
file(GLOB SOURCES "src/*.cpp" "include/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} -LC:/Users/hlebushkek/Documents/GameEngine/Engine/vendors/SDL/build/FinalBuild/lib -L ../)
target_link_libraries(${PROJECT_NAME} imgui -lSDL2maind -lSDL2d -lSDL2_image -l../libEngine)