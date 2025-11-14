#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include "binary_tree.h"

// Inserts an item into the binary search tree
void insert_BST(BinaryTree_t* tree, int item);

// Searches for an item in the binary search tree
bool search_BST(BinaryTree_t* tree, int item);

// Finds minimum and maximum in BST
int find_min(BTNode_t* root);
int find_max(BTNode_t* root);

// Deletes a node from BST
void delete_BST(BinaryTree_t* tree, int item);

#endif // BST_H
