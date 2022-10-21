cmake_minimum_required(VERSION 3.24)

project(Engine)

enable_language(C)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_NAME}/include, ${PROJECT_NAME}/vendors/SDL/build/FinalBuild/include/SDL2 ${PROJECT_NAME}/vendors/glad/include ${PROJECT_NAME}/vendors/glm)
file(GLOB SOURCES "${PROJECT_NAME}/src/*.cpp" "${PROJECT_NAME}/include/*.h")
add_definitions(-DENGINE_BUILD_DLL)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} -LC:/Users/hlebushkek/Documents/GameEngine/Engine/vendors/SDL/build/FinalBuild/lib -lSDL2maind -lSDL2d)

add_subdirectory(${PROJECT_NAME}/vendors/glad/)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(${PROJECT_NAME}/vendors/glm/)
target_link_libraries(${PROJECT_NAME} glm)
