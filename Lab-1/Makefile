CC = gcc
QUIET = @
CFLAGS = -g3 -O0 -Wall
OFLAGS = -c -Wall
LIB = -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDES = -I $(SRC_DIR)
DIRS = $(BIN_DIR) $(OBJ_DIR)
OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/extralib.o

.PHONY: all bins objs clean
all: bins

bins: $(DIRS) objs
	$(CC) $(OBJ) $(CFLAGS) -o $(BIN_DIR)/cmpl $(LIB)

$(DIRS):
	mkdir $(DIRS)

objs:
	$(CC) $(OFLAGS) $(SRC_DIR)/extralib.c -o $(OBJ_DIR)/extralib.o $(INCLUDES)
	$(CC) $(OFLAGS) $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o $(INCLUDES)

clean:
	$(QUIET)rm -rfv $(DIRS)/
