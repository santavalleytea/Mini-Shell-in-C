# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -I./src

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN = myshell

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default rule
all: $(BIN)

# Link object files into final executable
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c files to .o files in obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN)
