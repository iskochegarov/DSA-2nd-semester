#ifndef RBTREE
#define RBTREE

//struct RBTree;
struct RBTree *RBTree_add (struct RBTree *tree, int key);
struct RBTree *RBTree_create (int key);
struct RBTree *RBTree_lookup (struct RBTree *tree, int key);
struct RBTree *RBTree_min (struct RBTree *tree);
struct RBTree *RBTree_max (struct RBTree *tree);
struct RBTree *RBTree_fixup_add (struct RBTree *root, struct RBTree *node);
struct RBTree *RBTree_delete(struct RBTree *tree, int key);
struct RBTree *RBTree_swap(struct RBTree *root, struct RBTree *Xnode, struct RBTree *Ynode);
struct RBTree *RBTree_fixup_delete(struct RBTree *root, struct RBTree *node);
void RBTree_print(struct RBTree *tree, char *dir, int level); //fuck
void RBTree_free(struct RBTree *tree);
struct RBTree *RBTree_left_rotate (struct RBTree *root, struct RBTree *node);
struct RBTree *RBTree_right_rotate (struct RBTree *root, struct RBTree *node);
void RBtreeprint (struct RBTree *tree);
#endif
