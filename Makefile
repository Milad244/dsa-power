# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -Ilibs -g

# Directories
SRC_DIR = src
APP_DIR = app
TEST_DIR = tests
BUILD_DIR = build
UNITY_DIR = libs/Unity

# Targets
APP_TARGET = main

# Source files
LIB_SRCS := $(wildcard $(SRC_DIR)/*.c)
APP_SRCS := $(wildcard $(APP_DIR)/*.c)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
UNITY_SRC := $(UNITY_DIR)/unity.c

# Object files
LIB_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(LIB_SRCS))
APP_OBJS := $(patsubst $(APP_DIR)/%.c,$(BUILD_DIR)/%.app.o,$(APP_SRCS))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%.test.o,$(TEST_SRCS))
UNITY_OBJ := $(BUILD_DIR)/unity.o

# Default rule: build the app
all: $(BUILD_DIR)/$(APP_TARGET)

# Build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile library objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile app objects
$(BUILD_DIR)/%.app.o: $(APP_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test objects
$(BUILD_DIR)/%.test.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Unity
$(UNITY_OBJ): $(UNITY_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link main program
$(BUILD_DIR)/$(APP_TARGET): $(LIB_OBJS) $(APP_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Link each test executable
$(BUILD_DIR)/%: $(LIB_OBJS) $(BUILD_DIR)/%.test.o $(UNITY_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Build all test executables
tests: $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%,$(TEST_SRCS))

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all tests clean help

# Info for users
help:
	@echo "Available targets:"
	@echo "  make        - build the main program"
	@echo "  make tests  - build all test executables"
	@echo "  ./build/<testname> - run a specific test executable"
	@echo "  make clean  - remove build artifacts"
