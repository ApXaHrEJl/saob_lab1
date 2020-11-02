#ifndef H_AVL
#define H_AVL
#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

typedef struct avl {
    int key;
    int height;
    int deleted;
    struct avl* left;
    struct avl* right;
    struct prefix_tree* prefix;
} avltree;

double wtime();

int imax2(int a, int b);

void avltree_free(avltree* tree);

avltree* avltree_lookup(avltree* tree, int key, int isdeleted);

avltree* avltree_create(int key);

int avltree_height(avltree* tree);

int avltree_balance(avltree* tree);

avltree* avltree_add(avltree* tree, int key);

avltree* avltree_right_rotate(avltree* tree);

avltree* avltree_left_rotate(avltree* tree);

avltree* avltree_leftright_rotate(avltree* tree);

avltree* avltree_rightleft_rotate(avltree* tree);

void avltree_delete(avltree* tree, int key);

avltree* avltree_min(avltree* tree, avltree* parent);

avltree* avltree_max(avltree* tree, avltree* parent);

void avltree_print_dfs(avltree* tree, int level);

avltree* avltree_clear(avltree* tree, avltree* new_tree);

#endif
