#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdbool.h>

// Node for binary tree
typedef struct BTNode {
    int data;
    struct BTNode* left;
    struct BTNode* right;
} BTNode_t;

// Binary tree definition
typedef struct BinaryTree {
    BTNode_t* root;
} BinaryTree_t;

// Creates a new empty binary tree
BinaryTree_t* create_binary_tree(void);

// Creates a new node with given value
BTNode_t* create_node(int item);

// Traversal functions
void inorder_traversal(BTNode_t* root);
void preorder_traversal(BTNode_t* root);
void postorder_traversal(BTNode_t* root);

#endif // BINARY_TREE_H
