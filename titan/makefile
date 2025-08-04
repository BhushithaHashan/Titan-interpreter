# Compiler and Flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g

# Folders
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c) main.c
OBJS = $(SRCS:.c=.o)
TARGET = titan

# The Default Rule (What happens when you type 'make')
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule for .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the project
clean:
	rm -f $(SRC_DIR)/*.o *.o $(TARGET)