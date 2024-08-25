# Compiler
CXX = g++

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Executable
TARGET = game

# Compiler flags
CXXFLAGS = -std=c++17 -I$(INCLUDE_DIR) -I/usr/include/jsoncpp

# Linker flags for SFML and JSONCPP
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -ljsoncpp

# Find all .cpp source files recursively
SRC_FILES = $(shell find $(SRC_DIR) -name '*.cpp')

# Create corresponding .o files in the build directory
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(TARGET) $(LDFLAGS)

# Compile source files and maintain directory structure
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | create_build_dir
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
create_build_dir:
	mkdir -p $(BUILD_DIR)

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run create_build_dir
