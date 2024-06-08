# Set up variables
SRC_DIR = src
BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = play
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -L/opt/homebrew/Cellar/sdl2/2.30.3/lib/ -L/opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib
COMPILER_FLAGS = -std=c++17 -Wall -O0 -g #c++11 before
LINKER_FLAGS = -lsdl2

# Build command to build application
all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)

# To build type make into console