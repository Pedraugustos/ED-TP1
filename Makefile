CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -pedantic -g -I$(INCLUDE_DIR) -O0  # -O0 é importante para debug

# directories
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# sources
SOURCES = object scene utils main
OBJECTS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SOURCES)))

EXECUTABLE = $(BIN_DIR)/tp1.out

# executable
$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# compile objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# create directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# auxiliary rules
.PHONY: all run debug clean

all: $(BIN_DIR)/main

run: $(EXECUTABLE)
	./$(EXECUTABLE)

# debug with gdb
debug: $(BIN_DIR)/main
	gdb --args $(BIN_DIR)/main

# debug with arguments
debug-args: $(BIN_DIR)/main
	gdb --args $(BIN_DIR)/main $(ARGS)

# debug with tui
debug-tui: $(BIN_DIR)/main
	gdb -tui --args $(BIN_DIR)/main

# execute and load in gdb
debug-run: $(BIN_DIR)/main
	gdb -ex "run" -ex "bt" --args $(BIN_DIR)/main

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# clean and recompile in debug
rebuild: clean debug