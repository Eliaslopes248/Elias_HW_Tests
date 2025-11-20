# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I../INCLUDES -MMD -MP

# Directories
SRC_DIRS = ../SRC ../TESTS
BIN_DIR = ../BIN
EXE = $(BIN_DIR)/main.exe

# Find all .cpp files recursively
CPP_FILES := $(shell find $(SRC_DIRS) -name '*.cpp')

# Convert .cpp filenames to just basename.o inside BIN
OBJ_FILES := $(patsubst %.cpp,$(BIN_DIR)/%.o,$(notdir $(CPP_FILES)))
DEP_FILES := $(OBJ_FILES:.o=.d)

# Default target
all: $(BIN_DIR) $(EXE)

# Link all objects into executable
$(EXE): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@

# Compile rule: ../BIN/foo.o depends on ../SRC/foo.cpp or ../TESTS/foo.cpp
$(BIN_DIR)/%.o:
	@SRC_FILE=$(firstword $(filter %/$*.cpp,$(CPP_FILES))); \
	echo "Compiling $$SRC_FILE"; \
	$(CXX) $(CXXFLAGS) -MT $@ -MF $(BIN_DIR)/$*.d -c "$$SRC_FILE" -o $@

# Include dependency files
-include $(DEP_FILES)

# Create BIN directory if missing
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean
clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/*.d $(EXE)

.PHONY: all clean
