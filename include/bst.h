#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include "binary_tree.h"

// Unique binary search tree definition
typedef struct BST {
    BTNode_t* root;
    int size;
} BST_t;

// Creates a new BST
BST_t* BST_create(void);

// Inserts an item into the BST
void BST_insert(BST_t* tree, int item);

// Searches for an item in the BST (returns NULL if not found)
BTNode_t* BST_search(BST_t* tree, int item);

// Finds minimum value in BST (returns -1 if tree is empty or NULL)
int BST_find_min(BTNode_t* root);

// Finds maximum value in BST (returns -1 if tree is empty or NULL)
int BST_find_max(BTNode_t* root);

// Deletes a node with the given value from the BST
void BST_delete(BST_t* tree, int item);

// Returns the number of nodes in BST (0 if tree is empty or NULL)
int BST_size(BST_t* tree);

// Constructs an array that contains all values from the BST (sorted in ascending order)
int* BST_to_array(BST_t* bst);

// Reconstructs BST from a preorder array
BST_t* BST_from_preorder(int* preorder, int n);

// Determines if tree is a unique BST (returns false if tree is NULL)
bool is_BST(BTNode_t* root);

// Frees all memory used by BST
void BST_free(BST_t* tree);

#endif // BST_H
