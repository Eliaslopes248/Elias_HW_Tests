# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I../INCLUDES

# Directories
SRC_DIRS = ../SRC ../TESTS
BIN_DIR = ../BIN
EXE = $(BIN_DIR)/main.exe

# Find all .cpp files recursively
CPP_FILES := $(shell find $(SRC_DIRS) -name '*.cpp')

# Convert .cpp filenames to just basename.o inside BIN
OBJ_FILES := $(patsubst %.cpp,$(BIN_DIR)/%.o,$(notdir $(CPP_FILES)))

# Default target
all: $(BIN_DIR) $(EXE)

# Link all objects into executable
$(EXE): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@

# Compile rule: ../BIN/foo.o depends on ../SRC/foo.cpp or ../TESTS/foo.cpp
$(BIN_DIR)/%.o: 
	$(CXX) $(CXXFLAGS) -c $(firstword $(filter %/$*.cpp,$(CPP_FILES))) -o $@

# Create BIN directory if missing
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean
clean:
	rm -f $(BIN_DIR)/*.o $(EXE)

.PHONY: all clean
