BUILD_DIR = build/debug
CC = g++

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) ../Engine/vendors/imgui/*.cpp ../Engine/vendors/imgui/backends/imgui_impl_sdl.cpp ../Engine/vendors/imgui/backends/imgui_impl_opengl3.cpp 

OBJS = $(SRC_FILES)
OBJ_NAME = main

INCLUDE_PATHS = -I include -I C:/Users/hlebushkek/Documents/GameEngine/Engine -I vendors/SDL/build/FinalBuild/include -I ../Engine/vendors/glad/include -I ../Engine/vendors/glm -I ../Engine/vendors/SDL_image -I ../Engine/vendors/SDL/build/FinalBuild/include/SDL2 -I ../Engine/vendors/imgui
LIBRARY_PATHS = -L C:/Users/hlebushkek/Documents/GameEngine/build -L ../Engine/vendors/SDL/build/FinalBuild/lib

COMPILER_FLAGS = -std=c++20 -Wall -O0 -g
LINKER_FLAGS = -llibEngine -lSDL2d

all:
	$(CC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(OBJS) -o $(OBJ_NAME) $(COMPILER_FLAGS) $(LINKER_FLAGS)