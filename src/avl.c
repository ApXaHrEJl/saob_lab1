#include "avl.h"
#include <sys/time.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int imax2(int a, int b)
{
    if (a >= b) {
        return a;
    }
    return b;
}

int avltree_height(avltree* tree)
{
    if (tree == NULL) {
        return -1;
    }
    return tree->height;
}

avltree* avltree_right_rotate(avltree* tree)
{
    avltree* left;
    left = tree->left;
    tree->left = left->right;
    left->right = tree;
    tree->height
            = imax2(avltree_height(tree->left), avltree_height(tree->right))
            + 1;
    left->height = imax2(avltree_height(left->left), tree->height) + 1;
    return left;
}

avltree* avltree_left_rotate(avltree* tree)
{
    avltree* right;
    right = tree->right;
    tree->right = right->left;
    right->left = tree;
    tree->height
            = imax2(avltree_height(tree->left), avltree_height(tree->right))
            + 1;
    right->height = imax2(avltree_height(right->right), tree->height) + 1;
    return right;
}

avltree* avltree_leftright_rotate(avltree* tree)
{
    tree->left = avltree_left_rotate(tree->left);
    return avltree_right_rotate(tree);
}

avltree* avltree_rightleft_rotate(avltree* tree)
{
    tree->right = avltree_right_rotate(tree->right);
    return avltree_left_rotate(tree);
}

void avltree_free(avltree* tree)
{
    if (tree == NULL)
        return;
    avltree_free(tree->left);
    avltree_free(tree->right);
    free(tree);
}

avltree* avltree_lookup(avltree* tree, int key, int isdeleted)
{
    while (tree != NULL) {
        if (key == tree->key) {
            if (tree->deleted != isdeleted) {
                return NULL;
            }
            return tree;
        } else if (key < tree->key) {
            tree = tree->left;
        } else {
            tree = tree->right;
        }
    }
    return tree;
}

avltree* avltree_create(int key)
{
    avltree* node;
    node = malloc(sizeof(*node));
    if (node != NULL) {
        node->key = key;
        node->prefix = trie_create();
        node->left = NULL;
        node->right = NULL;
        node->height = 0;
        node->deleted = 0;
    }
    return node;
}

int avltree_balance(avltree* tree)
{
    return (avltree_height(tree->left) - avltree_height(tree->right));
}

avltree* avltree_add(avltree* tree, int key)
{
    if (tree == NULL) {
        return avltree_create(key);
    }
    avltree* deleted_tree = avltree_lookup(tree, key, 1);
    if (deleted_tree != NULL) {
        deleted_tree->deleted = 0;
        return deleted_tree;
    }
    if (key < tree->key) {
        tree->left = avltree_add(tree->left, key);
        if (avltree_height(tree->left) - avltree_height(tree->right) == 2) {
            if (key < tree->left->key) {
                tree = avltree_right_rotate(tree);
            } else {
                tree = avltree_leftright_rotate(tree);
            }
        }
    } else if (key > tree->key) {
        tree->right = avltree_add(tree->right, key);
        if (avltree_height(tree->right) - avltree_height(tree->left) == 2) {
            if (key > tree->right->key) {
                tree = avltree_left_rotate(tree);
            } else {
                tree = avltree_rightleft_rotate(tree);
            }
        }
    }
    tree->height
            = imax2(avltree_height(tree->left), avltree_height(tree->right))
            + 1;
    return tree;
}

void avltree_delete(avltree* tree, int key)
{
    tree = avltree_lookup(tree, key, 0);
    if (tree == NULL) {
        return;
    }
    tree->deleted = 1;
}

/*avltree* avltree_min(avltree* tree)
{
    if (tree->left != NULL) {
        return avltree_min(tree->left);
    }
    return tree;

avltree* avltree_max(avltree* tree)
{
    if (tree->right != NULL) {
        return avltree_max(tree->right);
    }
    return tree;
}
}*/

avltree* avltree_clear(avltree* tree, avltree* new_tree)
{
    if (tree->deleted == 0) {
        new_tree = avltree_add(new_tree, tree->key);
    }
    if (tree->left != NULL) {
        new_tree = avltree_clear(tree->left, new_tree);
    }
    if (tree->right != NULL) {
        new_tree = avltree_clear(tree->right, new_tree);
    }
    return new_tree;
}

void avltree_print_dfs(avltree* tree, int level)
{
    level--;
    printf("%c",tree->key);
    if ((level >= 0) && (tree->left != NULL)) {
        avltree_print_dfs(tree->left, level);
    }
    if ((level >= 0) && (tree->right != NULL)) {
        avltree_print_dfs(tree->right, level);
    }
}
