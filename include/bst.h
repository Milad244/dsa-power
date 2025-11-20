#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include "binary_tree.h"

// Binary search tree definition
typedef struct BST {
    BTNode_t* root;
    int size;
} BST_t;

// Creates an empty BST
BST_t* create_BST(void);

// Inserts an item into the binary search tree
void insert_BST(BST_t* tree, int item);

// Searches for an item in the binary search tree
bool search_BST(BST_t* tree, int item);

// Finds minimum value in BST (returns -1 if tree is empty)
int find_min(BTNode_t* root);

// Finds maximum value in BST (returns -1 if tree is empty)
int find_max(BTNode_t* root);

// Deletes a node with the given value from the BST
void delete_BST(BST_t* tree, int item);

// Returns the number of nodes in BST
int bst_size(BST_t* tree);

// Reconstructs BST from a preorder array
BST_t* bst_from_preorder(int* preorder, int n);

// Frees all memory used by BST
void free_BST(BST_t* tree);

#endif // BST_H
