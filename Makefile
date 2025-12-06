# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude $(EXTRA_CFLAGS) -g
LDFLAGS = $(EXTRA_LDFLAGS)

# Detect OS and set macOS Homebrew CUnit paths
UNAME_S := $(shell uname)
ifeq ($(UNAME_S),Darwin)
    EXTRA_CFLAGS ?= -I/opt/homebrew/include
    EXTRA_LDFLAGS ?= -L/opt/homebrew/lib
endif

# Directories
SRC_DIR = src
APP_DIR = app
TEST_DIR = tests
BUILD_DIR = build

# Targets
APP_TARGET = main
TEST_TARGET = tests

# Source files
LIB_SRCS := $(wildcard $(SRC_DIR)/*.c)
APP_SRCS := $(wildcard $(APP_DIR)/*.c)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)

# Object files
LIB_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(LIB_SRCS))
APP_OBJS := $(patsubst $(APP_DIR)/%.c,$(BUILD_DIR)/%.app.o,$(APP_SRCS))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%.test.o,$(TEST_SRCS))

# Default rule: build the app
all: $(BUILD_DIR)/$(APP_TARGET)

# Create build directory if it doesn't exist
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

# Link main program
$(BUILD_DIR)/$(APP_TARGET): $(LIB_OBJS) $(APP_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Link test program (exclude main app objects)
$(BUILD_DIR)/$(TEST_TARGET): $(LIB_OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -lcunit -o $@

# Run tests
test: $(BUILD_DIR)/$(TEST_TARGET)
	./$(BUILD_DIR)/$(TEST_TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all test clean help

# Info for users
help:
	@echo "Available targets:"
	@echo "  make        - build the main program"
	@echo "  make test   - build & run tests (requires CUnit)"
	@echo "  make clean  - remove build artifacts"