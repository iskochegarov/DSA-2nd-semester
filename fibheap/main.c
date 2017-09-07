#include <stdio.h>
#include "fibheap.h"
#include <ctype.h>

int menu()
{
    int req;
    printf("...........FibHeap 1............\n");
    printf(" 1 - Insert Node\n");
    printf(" 2 - Get Min Node\n");
    printf(" 3 - Delete Min Node\n");
    printf(" 4 - Print FibHeap\n");
    printf("...........FibHeap 2............\n");
    printf(" 5 - Insert Node\n");
    printf(" 6 - Get Min Node\n");
    printf(" 7 - Delete Min Node\n");
    printf(" 8 - Print FibHeap\n");
    printf("_________________________________\n");
    printf(" 9 - FibHeaps Union\n");
    printf(" 0 - Exit\n");
    scanf("%d", &req);
    return req;
}

int main(int argc, char **argv)
{
    struct node* x;
    struct heap* Heap1 = CreateFibHeap();
    struct heap* Heap2 = CreateFibHeap();
    int req = -1;
    x = NULL;
    while (req)
    {
        printf("_________________________________\n");
        req = menu();
        switch(req)
        {
            int k;

        case 1:
            printf("\033c");
            k = InputAndCheck();
            if (k == 0)
                break;
            if (k == -1)
                k = 0;
            x = CreateFibHeapNode(k);
            FibHeapInsert(Heap1, x);
            printf(" Node with priority %d was inserted\n", x->key);
            break;
        case 2:
            printf("\033c");
            x = FibHeapMin(Heap1);
            if (x)
                printf(" Min Node have priority %d\n", x->key);
            else
                printf(" FibHeap is empty!\n");
            break;
        case 3:
            printf("\033c");
            x = DeleteMin(Heap1);
            if (x)
            {
                printf(" Node with priority %d is deleted\n", x->key);
            }
            else
            {
                printf(" FibHeap is already empty!\n");
            }
            break;
        case 4:
            printf("\033c");
            if (Heap1->min == NULL)
                printf(" FibHeap is empty!\n");
            else
            {
                Print_Fib_Heap (Heap1, Heap1->min);
            }
            break;


        case 5:
            printf("\033c");
            k = InputAndCheck();
            if (k == 0)
                break;
            if (k == -1)
                k = 0;
            x = CreateFibHeapNode(k);
            FibHeapInsert(Heap2, x);
            printf(" Node with priority %d was inserted\n", x->key);
            break;
        case 6:
            printf("\033c");
            x = FibHeapMin(Heap2);
            if (x)
                printf(" Min Node have priority %d\n", x->key);
            else
                printf(" FibHeap is empty!\n");
            break;
        case 7:
            printf("\033c");
            x = DeleteMin(Heap2);
            if (x)
            {
                printf(" Node with priority %d is deleted\n", x->key);
            }
            else
            {
                printf(" FibHeap is already empty!\n");
            }
            break;
        case 8:
            printf("\033c");
            if (Heap2->min == NULL)
                printf(" FibHeap is empty!\n");
            else
            {
                Print_Fib_Heap (Heap2, Heap2->min);
            }
            break;
        case 9:
            printf("\033c");
            Heap1 = FibHeapUnion(Heap1, Heap2);
            Heap2 = CreateFibHeap();				// FIXME
            break;
        }
    }
    free(Heap1);	// FIXME
    free(Heap2);	// FIXME
    return 0;
}

//http://www.cs.yorku.ca/~aaw/Jason/FibonacciHeapAnimation.html
