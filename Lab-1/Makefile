CC=gcc
CFLAGS=-O0 -g3 -lm
BIN=./bin/main

all: MAIN

run: MAIN
	$(BIN)
	sort results.dat > result.dat
	./mkgraph.sh

MAIN: ./obj/main.o
	$(CC) ./obj/main.o -o $(BIN) $(CFLAGS)

./obj/main.o: ./src/main.c
	$(CC) -c ./src/main.c -o ./obj/main.o $(CFLAGS)

clean:
	rm -rf ./obj/*.o

restruct: clean all
