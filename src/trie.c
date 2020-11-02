#include "trie.h"

trie* trie_create()
{
    trie* node;
    if ((node = malloc(sizeof(*node))) == NULL) {
        return NULL;
    }
    node->value = 0;
    node->child = NULL;
    return node;
}

void trie_insert(trie* root, char* string, int value)
{
    if (*string == '\0') {
        root->value = value;
        return;
    }
    if (root->child != NULL) {
        avltree* child_node = avltree_lookup(root->child, *string, 0);
        if (child_node == NULL) {
            root->child = avltree_add(root->child, *string);
            child_node = avltree_lookup(root->child, *string, 0);
        }
        trie_insert(child_node->prefix, string + 1, value);
    } else {
        root->child = avltree_add(root->child, *string);
        trie_insert(root->child->prefix, string + 1, value);
    }
}

trie* trie_lookup(trie* root, char* string)
{
    if (root->child != NULL) {
        avltree* child_tree = avltree_lookup(root->child, *string, 0);
        if (child_tree != NULL) {
            return trie_lookup(child_tree->prefix, string + 1);
        } else {
            return NULL;
        }
    }
    if (*string == 0) {
        return root;
    }
    return NULL;
}

int trie_delete(trie* root, char* string)
{
    if (*(string) != '\0') {
        avltree* next = avltree_lookup(root->child, *string, 0);
        if (next == NULL) {
            return 1;
        }
        int alarm = trie_delete(next->prefix, string + 1);
        if (alarm == 0) {
            if ((root->child->left == NULL) && (root->child->right = NULL)) {
                free(root->child->prefix); //
                avltree_free(root->child); //
                return 0;
            } else {
                avltree_delete(root->child, *string);
                free(next->prefix);
                root->child = avltree_clear(root->child, NULL); //
                return 1;
            }
        }
    }
    return 0;
}

void trie_print(trie* root, int level)
{
    level--;
    if (level > 0) {
        if (root->child != NULL) {
            if (root->child->prefix != NULL) {
                trie_print(root->child->prefix, level);
            }
            if (root->child->left != NULL) {
                if (root->child->left->prefix != NULL) {
                    trie_print(root->child->left->prefix, level);
                }
            }
            if (root->child->right != NULL) {
                if (root->child->right->prefix != NULL) {
                    trie_print(root->child->right->prefix, level);
                }
            }
        }
    }
    if (root->value != 0) {
        printf("%d\n", root->value);
    }
}
