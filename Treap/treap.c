#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "treap.h"

pitem NewNode (int key) {
    pitem temp;
    temp = malloc(sizeof(*temp));
    temp->key = key;
    temp->prior = rand()%100;
    temp->l = temp->r = NULL;
    return temp;
}

pitem Lookup(pitem treap, int x) {
    while (treap) {
        if (x == treap->key)
            return treap;
        else if (x < treap->key)
            treap = treap->l;
        else
            treap = treap->r;
    }
    pitem nil = NULL;
    return nil;
}

void split (pitem t, int key, pitem *l, pitem *r) {
	if (!t)
		l[0] = r[0] = NULL;
	else if (key < t->key)
		split (t->l, key, &l[0], &(t->l)),  r[0] = t;
	else
		split (t->r, key, &(t->r), &r[0]),  l[0] = t;
}

pitem insert (pitem t, pitem it) {
	if (!t)
		t = it;
	else if (it->prior < t->prior)    //MINHEAP
        split (t, it->key, &(it->l), &(it->r)),  t = it;
	else {
		if (it->key < t->key)
            t->l = insert (t->l, it);
        else
            t->r = insert (t->r, it);
    }
    return t;
}

pitem merge (pitem t, pitem l, pitem r) {
	if (!l || !r)
		t = l ? l : r;
	else if (l->prior < r->prior)
		l->r = merge (l->r, l->r, r),  t = l;
	else
		r->l = merge (r->l, l, r->l),  t = r;
    return t;
}

pitem erase (pitem t, int key) {
	if (t->key == key) {
		t = merge (t, t->l, t->r);
		printf("\nErase : item with key = %d was deleted\n\n", key);

	} else
	    if (key < t->key)
	        t->l = erase(t->l, key);
	    else
	        t->r = erase(t->r, key);
		    //erase (key < t->key ? t->l : t->r, key);
    return t;
}

void PrintInorder(pitem root)
{
    if (root)
    {
        PrintInorder(root->l);
        printf("key: %d | priority: %d ", root->key, root->prior);
        if (root->l)
            printf(" | left child: %d", root->l->key);
        if (root->r)
            printf(" | right child: %d", root->r->key);
        printf("\n");
        PrintInorder(root->r);
    }
}

void PrintNode(pitem t)
{
    printf("key: %d | priority: %d ", t->key, t->prior);
    if (t->l)
        printf(" | left child: %d", t->l->key);
    if (t->r)
        printf(" | right child: %d", t->r->key);
    printf("\n");
}

