#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "rbtree.h"

#define COLOR_RED 0
#define COLOR_BLACK 1

struct RBTree
{
    int key;
    int color;

    struct RBTree *parent;
    struct RBTree *left;
    struct RBTree *right;
};

struct RBTree EmptyNode = {0, 1, NULL, NULL, NULL};
struct RBTree *NullNode = &EmptyNode;

struct RBTree *RBTree_add(struct RBTree *root, int key)
{
    struct RBTree *node, *parent = NullNode;
    /* Search leaf for new element */
    for (node = root; node != NullNode && node != NULL; )
    {
        parent = node;
        if (key < node->key)
            node = node->left;
        else if (key > node->key)
            node = node->right;
        else
            return root;
    }

    node = malloc(sizeof(*node));

    if (node == NULL || node == NullNode)
        return NULL;

    node->key = key;
    node->color = COLOR_RED;
    node->parent = parent;
    node->left = NullNode;
    node->right = NullNode;

    if (parent != NullNode)
    {
        if (key < parent->key)
            parent->left = node;
        else
            parent->right = node;
    }
    else
    {
        root = node;
    }

    /* Тестовый вывод
    printf("\nadd key=%d\n", node->key);
    */

    return RBTree_fixup_add(root, node);
};

struct RBTree *RBTree_fixup_add (struct RBTree *root, struct RBTree *node)
{
    printf("ADDFIXUP: key = %d\n", node->key);
    struct RBTree *uncle;
    /* Current node is RED */
    while (node != root && node->parent->color == COLOR_RED)
    {
        if (node->parent == node->parent->parent->left)
        {
            /* Node in left tree of grandfather */
            uncle = node->parent->parent->right;
            if (uncle->color == COLOR_RED)
            {
                /* Case 1 - uncle is RED */
                node->parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                node = node->parent->parent;
            }
            else
            {
                /* Cases 2 & 3 - uncle is BLACK */
                if (node == node->parent->right)
                {
                    /* Reduce case 2 to case 3 */
                    node = node->parent;
                    root = RBTree_left_rotate(root, node);
                }
                /* Case 3 */
                node->parent->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                root = RBTree_right_rotate(root, node->parent->parent);
            }
        }
        else
        {
            /*
               * Node in right tree of grandfather
               *
               * Cases 4, 5, 6 - node in right tree
               * of grandfather
               */
            uncle = node->parent->parent->left;
            if (uncle->color == COLOR_RED)
            {
                /* Uncle is RED – case 4 */
                node->parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                node = node->parent->parent;
            }
            else
            {
                /* Uncle is BLACK */
                if (node == node->parent->left)
                {
                    node = node->parent;
                    root = RBTree_right_rotate(root, node);
                }
                node->parent->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                root = RBTree_left_rotate(root, node->parent->parent);
            }
        }
    }
    root->color = COLOR_BLACK;

    /* Тестовый вывод
    printf("\nfix key=%d\n", root->key);
    */

    return root;
};

struct RBTree *RBTree_delete(struct RBTree *tree, int key)
{
    printf("\nKey = %d was deleted:\n", key);
    struct RBTree *node = RBTree_lookup(tree, key);

    if ((node == NULL) || (node == NullNode))
        return tree;

    struct RBTree *x;
    struct RBTree *y = node;
    int y_origin_color = y->color;
    if (node->left == NullNode || node->left == NULL)
    {
        x = node->right;
        tree = RBTree_swap(tree, node, node->right);
    }
    else if (node->right == NullNode || node->right == NULL)
    {
        x = node->left;
        tree = RBTree_swap(tree, node, node->left);
    }
    else
    {
        y = RBTree_min(node->right); //right?
        y_origin_color = y->color;
        x = y->right;
        if (y->parent == node)
            x->parent = y;
        else
        {
            tree = RBTree_swap(tree, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        tree = RBTree_swap(tree, node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }
    if (y_origin_color == COLOR_BLACK)
        return RBTree_fixup_delete(tree, x);
    else return tree;
}

struct RBTree *RBTree_swap(struct RBTree *tree, struct RBTree *Xnode, struct RBTree *Ynode)
{
    if ((Xnode->parent == NullNode) || (Xnode->parent == NULL))
        tree = Ynode;
    else if (Xnode == Xnode->parent->left)
        Xnode->parent->left = Ynode;
    else
        Xnode->parent->right = Ynode;
    Ynode->parent = Xnode->parent;			// Меняем родителя
    return tree;
}

struct RBTree *RBTree_fixup_delete(struct RBTree *root, struct RBTree *node)
{
    struct RBTree *w;
    while ((node != root) && (node->color == COLOR_BLACK))
    {
        if (node == node->parent->left)
        {
            w = node->parent->right;

            if (w->color == COLOR_RED)
            {
                w->color = COLOR_BLACK;
                node->parent->color = COLOR_RED;
                root = RBTree_left_rotate(root, node->parent);
                w = node->parent->right;
            }

            if ((w->left->color == COLOR_BLACK) && (w->right->color == COLOR_BLACK))
            {
                w->color = COLOR_RED;
                node = node->parent;
            }
            else
            {
                if (w->right->color == COLOR_BLACK)
                {
                    w->left->color = COLOR_BLACK;
                    w->color = COLOR_RED;
                    root = RBTree_right_rotate(root, w);
                    w = node->parent->right;
                }
                w->color = node->parent->color;
                node->parent->color = COLOR_BLACK;
                w->right->color = COLOR_BLACK;
                root = RBTree_left_rotate(root, node->parent);
                node = root;
            }
        }
        else
        {
            w = node->parent->left;
            if (w->color == COLOR_RED)
            {
                w->color = COLOR_BLACK;
                node->parent->color = COLOR_RED;
                root = RBTree_right_rotate(root, node->parent);
                w = node->parent->left;
            }
            if ((w->right->color == COLOR_BLACK) && (w->left->color == COLOR_BLACK))
            {
                w->color = COLOR_RED;
                node = node->parent;
            }
            else
            {
                if (w->left->color == COLOR_BLACK)
                {
                    w->right->color = COLOR_BLACK;
                    w->color = COLOR_RED;
                    root = RBTree_left_rotate(root, w);
                    w = node->parent->left;
                }
                w->color = node->parent->color;
                node->parent->color = COLOR_BLACK;
                w->left->color = COLOR_BLACK;
                root = RBTree_right_rotate(root, node->parent);
                node = root;
            }
        }
    }
    node->color = COLOR_BLACK;

    return root;
}

struct RBTree *RBTree_left_rotate (struct RBTree *root, struct RBTree *node)
{
    printf("Left ROT: key= %d\n", node->key);
    struct RBTree *right = node->right;
    /* Create node->right link */
    node->right = right->left;
    if (right->left != NullNode)
        right->left->parent = node;
    /* Create right->parent link */

    if (right != NullNode)
        right->parent = node->parent;

    if (node->parent != NullNode)
    {
        if (node == node->parent->left)
            node->parent->left = right;
        else
            node->parent->right = right;
    }
    else
    {
        root = right;
    }

    right->left = node;

    if (node != NullNode)
        node->parent = right;

    return root;
};


struct RBTree *RBTree_right_rotate (struct RBTree *root, struct RBTree *node)
{
    printf("RIGHT ROT: key= %d\n", node->key);
    struct RBTree *left = node->left;
    /* Create node->left link */
    node->left = left->right;

    if (left->right != NullNode)
        left->right->parent = node;
    /* Create left->parent link */
    if (left != NullNode)
        left->parent = node->parent;

    if (node->parent != NullNode)
    {
        if (node == node->parent->right)
            node->parent->right = left;
        else
            node->parent->left = left;
    }
    else
    {
        root = left;
    }
    left->right = node;

    if (node != NullNode)
        node->parent = left;

    return root;
};

struct RBTree *RBTree_lookup (struct RBTree *tree, int key)
{
    while(tree != NullNode)
    {
        if (key == tree->key)
        {
            return tree;
        }
        else if (key < tree->key)
        {
            tree = tree->left;
        }
        else
        {
            tree = tree->right;
        }
    }
    return tree;
};

struct RBTree *RBTree_min (struct RBTree *tree)
{
    if (tree == NullNode)
        return NULL;
    while (tree->left != NullNode)
        tree = tree->left;
    printf("\nMin key: %d\n", tree->key);
    return tree;
};

struct RBTree *RBTree_max (struct RBTree *tree)
{
    if (tree == NullNode)
        return NULL;
    while (tree->right != NullNode)
        tree = tree->right;
    printf("\nMax key: %d\n", tree->key);
    return tree;
};

void _print_node(struct RBTree *n)
{
    if(n->parent)
    {
        printf(" parent=%d ", n->parent->key);
    }
    else
    {
        printf(" parent=nil ");
    }
    if(n->left)
    {
        printf(" left=%d ", n->left->key);
    }
    else
    {
        printf(" left=nil ");
    }
    if(n->right)
    {
        printf(" right=%d ", n->right->key);
    }
    else
    {
        printf(" right=nil ");
    }
}


void color_print(struct RBTree *n)
{
    if (!n)
    {
        return;
    }
    if ((n->parent)&&(n->left)&&(n->right))
    {
        if(n->color==COLOR_RED)
        {
            printf("\033[31m%d (red)\033[0m", n->key);
            _print_node(n);
        }
        else
        {
            printf("\033[34m%d (black)\033[0m", n->key);
            _print_node(n);
        }
        printf("\n");
        color_print(n->left);
        color_print(n->right);
    }

}

void RBtreeprint (struct RBTree *root)
{
    printf("Root is %d\n\n", root->key);
    color_print(root);
}

void RBTree_free(struct RBTree *tree)
{
    if (tree->left != NullNode)  RBTree_free(tree->left);
    if (tree->right != NullNode) RBTree_free(tree->right);
    free(tree);
}



