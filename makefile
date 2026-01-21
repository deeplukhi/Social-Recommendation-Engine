.PHONY: all run test build_tests clean

CXX = g++
CXXFLAGS = -std=c++17 -Wall
BUILD_DIR = build
MAIN_BIN = $(BUILD_DIR)/recommendation.exe
TEST_BIN = $(BUILD_DIR)/tests.exe

# Windows-compatible file detection (exclude main.cpp from SRC_FILES)
SRC_FILES = $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp)
SRC_FILES_NO_MAIN = $(filter-out src/main.cpp, $(SRC_FILES))

TEST_FILES = $(wildcard tests/*.cpp)

# Object files for main program
OBJ_DIR = $(BUILD_DIR)/obj
MAIN_OBJ = $(BUILD_DIR)/main.o
SRC_OBJ = $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES_NO_MAIN))

# Object files for tests
TEST_OBJ_DIR = $(BUILD_DIR)/test_obj
TEST_OBJ = $(patsubst tests/%.cpp,$(TEST_OBJ_DIR)/%.o,$(TEST_FILES))

# Include directories
INCLUDE_DIRS = -Isrc -IUtils

all: $(MAIN_BIN)

# ---- create build directories ----
$(BUILD_DIR):
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

$(OBJ_DIR): $(BUILD_DIR)
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	@if not exist "$(OBJ_DIR)\Algorithms" mkdir "$(OBJ_DIR)\Algorithms"
	@if not exist "$(OBJ_DIR)\Graph" mkdir "$(OBJ_DIR)\Graph"
	@if not exist "$(OBJ_DIR)\Models" mkdir "$(OBJ_DIR)\Models"
	@if not exist "$(OBJ_DIR)\Storage" mkdir "$(OBJ_DIR)\Storage"

$(TEST_OBJ_DIR): $(BUILD_DIR)
	@if not exist "$(TEST_OBJ_DIR)" mkdir "$(TEST_OBJ_DIR)"

# ---- compile source files (exclude main.cpp) ----
$(OBJ_DIR)/%.o: src/%.cpp
	@if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# ---- compile main.cpp separately to build/main.o ----
$(MAIN_OBJ): src/main.cpp
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# ---- compile test files ----
$(TEST_OBJ_DIR)/%.o: tests/%.cpp
	@if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# ---- main executable ----
$(MAIN_BIN): $(OBJ_DIR) $(MAIN_OBJ) $(SRC_OBJ)
	$(CXX) $(CXXFLAGS) $(MAIN_OBJ) $(SRC_OBJ) -o $(MAIN_BIN)

# ---- build test executable ----
build_tests: $(TEST_OBJ_DIR) $(TEST_OBJ) $(SRC_OBJ)
	$(CXX) $(CXXFLAGS) $(TEST_OBJ) $(SRC_OBJ) -o $(TEST_BIN)

# ---- run test ----
test: build_tests
	$(TEST_BIN)

# ---- run app ----
run: $(MAIN_BIN)
	$(MAIN_BIN)

# ---- clean ----
clean:
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"

# ---- Help ----
help:
	@echo "Available targets:"
	@echo "  make        - Build the main program"
	@echo "  make run    - Build and run the main program"
	@echo "  make test   - Build and run tests"
	@echo "  make clean  - Remove build files"
	@echo "  make help   - Show this help"