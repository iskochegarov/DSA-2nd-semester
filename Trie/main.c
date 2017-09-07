#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "trie.h"
int main()
{
    struct trie *root;
    root = trie_insert(NULL,"ilya", "60");
    root = trie_insert(root,"ivan", "3000");
    root = trie_insert(root,"evgeniy", "100");
    root = trie_insert(root,"evpatiy", "500");
    root = trie_insert(root,"egor", "70");
    trie_print(root, 0);

    return 0;
}
