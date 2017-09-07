#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "treap.h"

int menu()
{
	int req;
	printf("...........Cartesian Tree (Treap)............\n");
	printf(" 1 - Insert Node\n");
	printf(" 2 - Insert n random keys\n");
	printf(" 3 - Delete node\n");
	printf(" 4 - Lookup Node\n");
	printf(" 5 - Print Treap Inorder\n");
	printf("______________________________________________\n");
	printf(" 0 - Exit\n");
	scanf("%d", &req);
	return req;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    pitem treap = NULL;
    pitem work;
    int req = -1;

    while (req)
	{
		printf("_______________________________________________\n");
		req = menu();
		switch(req)
		{
			int k, n;
			case 1:
			    printf("\033c");
			    printf("Insert key:  ");
			    scanf("%d", &k);
			    if (Lookup(treap, k)) {
			        printf("Insert: Duplicate key! Try again\n");
                    break;
			    }
			    treap = insert(treap, NewNode(k));
                printf("Node with priority %d was inserted\n", treap->key);
				break;

            case 2:
                printf("\033c");
                printf("Insert quantity of nodes:  ");
			    scanf("%d", &n);
			    for (int i = 0; i < n; i++)
                    treap = insert(treap, NewNode(rand()%100));
                printf("%d nodes was inserted\n", n);
                break;
            case 3:
                printf("\033c");
                printf("Insert key of node to delete:  ");
                scanf("%d", &n);
                if(Lookup(treap, n))
                    treap = erase(treap, n);
                else
                    printf("Key is not found in Treap!\n");

                break;
            case 4:
                printf("\033c");
                printf("Insert key of node to lookup:  ");
                scanf("%d", &n);
                work = Lookup(treap, n);
                if (work) {
                    printf("\nLookup: Item with key %d is found: \n", work->key);
                    PrintNode(work);
                } else
                    printf("\nLookup: Item with key %d is NOT found: \n", n);
                break;
            case 5:
                printf("\033c");
                printf("Inorder traversal of Treap:\n\n");
                if (!treap) printf("NULL\n");
                PrintInorder(treap);
        }

    }

    free(treap);
    return 0;
}

