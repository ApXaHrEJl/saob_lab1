#include "avl.h"
#define N 100
#define HEX 65536

int main()
{
    char* names[N];
    for (int i = 0; i < N; i++) {
        names[i] = malloc(sizeof(char) * 5);
        int seed = rand() % HEX;
        snprintf(names[i], 5, "%x", seed);
    }
    avltree* tree = avltree_create(1, names[0]);
    for (int i = 2; i <= N; i++) {
        avltree_add(tree, i, names[i - 1]);
    }
    avltree* found = avltree_lookup(tree, 2, 0); //здесь можно найти только 1 или N, иначе segmentation fault
    printf("%d %s", found->key, found->value);
    return 0;
}
