CC := gcc
STD := -std=c99 -lm 
DEBUG := -g3
OBJ_PATH := ./obj
BIN_PATH := ./bin
SRC_PATH := .
INC_PATH := ./include
SOURCES=$(wildcard $(SRC_PATH)/*.c)
OBJECTS=$(patsubst $(SRC_PATH)%, $(OBJ_PATH)%, $(SOURCES:.c=.o))

.PHONY: all

all: DIRECTORY $(BIN_PATH)/main

$(BIN_PATH)/main: $(OBJECTS)
	$(CC) $(STD) $(DEBUG) $< -o $@

DIRECTORY: $(OBJ_PATH) $(BIN_PATH)

$(OBJ_PATH):
	$(if ifeq test -d "$(OBJ_PATH)" 0, @mkdir -p $(OBJ_PATH))

$(BIN_PATH):
	$(if ifeq test -d "$(BIN_PATH)" 0, @mkdir -p $(BIN_PATH))

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(STD) $(DEBUG) -c $< -o $@

clean:
	rm -rf $(OBJ_PATH)

restruct: clean all

run:
	$(BIN_PATH)/main 1>./log.dat 2>./log_origin.dat