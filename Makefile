# Compiler
CC = g++
# Compiler flags
CFLAGS = -Wall -ldl
# Source directory
SRC_DIR = src
# Build directory
BUILD_DIR = build
# Target executable
TARGET = JavalessMC

# Find all source files
SRCS := $(shell find $(SRC_DIR) -name '*.c' -or -name '*.cpp')
# Generate object file names
OBJS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRCS:.c=.o))
OBJS := $(OBJS:.cpp=.o)

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Phony targets
.PHONY: all clean

