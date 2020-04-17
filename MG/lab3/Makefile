CC := gcc
STD := -std=c99
DEBUG := -g3
OBJ_PATH := ./obj
SRC_PATH := ./src
BIN_PATH = ./bin
INC_PATH = ./include
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=hello

.PHONY: all

all: DIRECTORY MIP

FORMAT:
	clang-format -i $(INC_PATH)/*.h
	clang-format -i $(SRC_PATH)/*.c

DIRECTORY: $(OBJ_PATH) $(BIN_PATH) 

$(OBJ_PATH):
	$(if ifeq test -d "$(OBJ_PATH)" 0, @mkdir -p $(OBJ_PATH))

$(BIN_PATH):
	$(if ifeq test -d "$(BIN_PATH)" 0, @mkdir -p $(BIN_PATH))

MIP: $(OBJECTS) 
	$(CC) $(STD) $(DEBUG) $(OBJ_PATH)/$< -o $(BIN_PATH)/$@

main.o: 
	$(CC) $(STD) $(DEBUG) -c $(SRC_PATH)/$*.c -o $(OBJ_PATH)/$@

clean:
	rm -rf $(OBJ_PATH) $(BIN_PATH)

restruct:
	make clean
	make all
