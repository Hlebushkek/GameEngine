BUILD_DIR = build/debug
CC = g++

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

OBJS = $(SRC_FILES)
OBJ_NAME = main

INCLUDE_PATHS = -I include -I C:/Users/hlebushkek/Documents/GameEngine/Engine -I vendors/SDL/build/FinalBuild/include -I ../Engine/vendors/glad/include
LIBRARY_PATHS = -L C:/Users/hlebushkek/Documents/GameEngine/build -L vendors/SDL/build/FinalBuild/lib -L vendors/glad/build

COMPILER_FLAGS = -std=c++20 -Wall -O0 -g
LINKER_FLAGS = -llibEngine -lSDL2

all:
	$(CC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(OBJS) -o $(OBJ_NAME) $(COMPILER_FLAGS) $(LINKER_FLAGS)