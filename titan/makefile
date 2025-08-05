CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c) main.c
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))

TARGET = titan

# Default rule
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile .c → .o into obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Special rule for main.c (since it's not in src/)
$(OBJ_DIR)/main.o: main.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c main.c -o $(OBJ_DIR)/main.o

clean:
	rm -rf $(OBJ_DIR) $(TARGET)