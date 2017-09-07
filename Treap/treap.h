#ifndef TREAP_H
#define TREAP_H

struct item {
	int key, prior;
	struct item * l, * r;
};

typedef struct item * pitem;

pitem NewNode (int key);
pitem Lookup(pitem treap, int x);
void split (pitem t, int key, pitem *l, pitem *r);
pitem insert (pitem t, pitem it);
pitem merge (pitem t, pitem l, pitem r);
pitem erase (pitem t, int key);
void PrintInorder(pitem root);
void PrintNode(pitem t);

#endif
