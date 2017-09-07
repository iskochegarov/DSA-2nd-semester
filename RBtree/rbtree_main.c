#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "rbtree.h"

int main(int argc, char **argv)
{
    struct RBTree *tree = NULL;
    tree = RBTree_add (tree, 10);
    tree = RBTree_add (tree, 5);
    tree = RBTree_add (tree, 3);
    tree = RBTree_add (tree, 11);
    tree = RBTree_add (tree, 12);
    tree = RBTree_add (tree, 6);
    tree = RBTree_add (tree, 8);
    tree = RBTree_add (tree, 9);
    printf("Source RED-BLACK tree:\n");
    RBtreeprint (tree);
    tree = RBTree_delete (tree, 8);
    RBtreeprint (tree);
    RBTree_free(tree);
    return 0;
}
