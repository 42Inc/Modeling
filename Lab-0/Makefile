CC = gcc
CFLAGS = -g3 -O0 
LIB = -lm
INCLUDES = -I src/
dirs = ./bin ./obj
main_obj = ./obj/main.o

all: ./bin/main

./bin/main: $(dirs) $(main_obj)
	$(CC) $(main_obj) $(CFLAGS) -o ./bin/cmpl $(LIB)

$(dirs):
	mkdir obj
	mkdir bin

./obj/main.o: ./src/main.c
	gcc -c ./src/main.c -Wall -o ./obj/main.o $(INCLUDES) $(CFLAGS)

.PHONY: clean exec
clean:
	rm -r -f bin/
	rm -r -f obj/
	rm result.*

exec:
	make ; ./bin/cmpl ; ./mkgraph.sh
