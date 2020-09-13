all: bin/ex1

bin/ex1: obj/main.o obj/avl.o include/avl.h
	mkdir bin
	gcc -Wall obj/main.o obj/avl.o -o bin/ex1

obj/avl.o: src/avl.c 
	gcc -I include -Wall -c src/avl.c -o obj/avl.o

obj/main.o: src/main.c
	mkdir obj
	gcc -I include -Wall -c src/main.c -o obj/main.o
clean:
	rm -rf bin/ obj/

PHONY: all clean
