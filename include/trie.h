#ifndef H_TRIE
#define H_TRIE
#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

typedef struct prefix_tree {
    int value;
    struct avl* child;
} trie;

trie* trie_create();

void trie_insert(trie* root, char* string, int value);

trie* trie_lookup(trie* root, char* string);

int trie_delete(trie* root, char* string);

void trie_print(trie *root, int level);


#endif
