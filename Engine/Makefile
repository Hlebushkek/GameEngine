BUILD_DIR = build/debug
CC = g++

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

OBJS = $(SRC_FILES)
OBJ_NAME = $(SRC_FILES:.cpp=.o)

INCLUDE_PATHS = -I include
LIBRARY_PATHS = -L C:\CPPLibs\SDL2-2.0.22\x86_64-w64-mingw32\lib

COMPILER_FLAGS = -std=c++20 -Wall -O0 -g
LINKER_FLAGS = 
DEFINES = -D ENGINE_BUILD_DLL

all: bin/engine.dll

bin/engine.dll: $(OBJ_NAME)
	$(CC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(OBJS) $(DEFINES) -shared -o engine.dll $(COMPILER_FLAGS) $(LINKER_FLAGS)
bin/%.o: SRC_FILES
	$(CC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(OBJS) $(DEFINES) -DBDLL -c -o $(OBJ_NAME) $(COMPILER_FLAGS) $(LINKER_FLAGS)