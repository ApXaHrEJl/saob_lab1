all: bin/ex1

bin/ex1: obj/main.o obj/avl.o obj/trie.o
	mkdir bin
	gcc -g -Wall obj/main.o obj/avl.o obj/trie.o -o bin/ex1

obj/avl.o: src/avl.c 
	gcc -g -I include -Wall -c src/avl.c -o obj/avl.o

obj/trie.o: src/trie.c 
	gcc -g -I include -Wall -c src/trie.c -o obj/trie.o

obj/main.o: src/main.c
	mkdir obj
	gcc -g -I include -Wall -c src/main.c -o obj/main.o
clean:
	rm -rf bin/ obj/

PHONY: all clean
