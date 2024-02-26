# Variables
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
TARGET := main

# Compiler
CXX := g++
CXXFLAGS := -Wall -g

# Find all .cpp files in SRC_DIR, including subdirectories
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
# Transform .cpp file paths into .o file paths
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
BIN := $(BIN_DIR)/$(TARGET)

# Default target
all: $(BIN)

# Linking all of the objects to create the final executable
$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compiling the source files into an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

# Phony targets
.PHONY: all clean

