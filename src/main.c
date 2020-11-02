#include "avl.h"
#include "trie.h"
#include <sys/time.h>

int main()
{
    char string[] = "Testaaaa";
    char string2[] = "Word";
    char string3[] = "A";
    trie* node = trie_create();
    trie_insert(node, string, 100);
    trie_insert(node, string2, 200);
    trie_insert(node, string3, 300);
   trie_print(node, 9);
    return 0;
}
