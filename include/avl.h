#ifndef H_AVL
#define H_AVL
#include <stdio.h>
#include <stdlib.h>

typedef struct avl {
    int key;
    char* value;
    int height;
    int deleted;
    struct avl* left;
    struct avl* right;
} avltree;

int imax2(int a, int b);

void avltree_free(avltree* tree);

avltree* avltree_lookup(avltree* tree, int key, int isdeleted);

avltree* avltree_create(int key, char* value);

int avltree_height(avltree* tree);

int avltree_balance(avltree* tree);

avltree* avltree_add(avltree* tree, int key, char* value);

avltree* avltree_right_rotate(avltree* tree);

avltree* avltree_left_rotate(avltree* tree);

avltree* avltree_leftright_rotate(avltree* tree);

avltree* avltree_rightleft_rotate(avltree* tree);

avltree *avltree_min(avltree *tree);

avltree *avltree_max(avltree *tree);

void avltree_print_dfs(avltree* tree, int level);

#endif
