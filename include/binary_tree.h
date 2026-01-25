#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdbool.h>

// Node for binary trees
typedef struct BTNode {
    int data;
    struct BTNode* parent;
    struct BTNode* left;
    struct BTNode* right;
} BTNode_t;

// Binary tree definition
typedef struct BinaryTree {
    BTNode_t* root;
} BinaryTree_t;

/* Construction / Destruction */

// Creates a new empty binary tree
BinaryTree_t* bt_create(void);
// Creates a new node with given value
BTNode_t* node_create(int item);
// Frees root and its subtree
void node_free_subtree(BTNode_t* root);
// Frees the entire binary tree
void bt_free(BinaryTree_t* tree);

/* Insertion */

// Inserts child as the left child of parent (does nothing if either is NULL and will override prev child)
void node_insert_left(BTNode_t* parent, BTNode_t* child);
// Inserts child as the right child of parent (does nothing if either is NULL and will override prev child)
void node_insert_right(BTNode_t* parent, BTNode_t* child);

/* Traversals */

// Recursively traverses root tree using inorder (left, root, right)
void node_inorder_traversal(BTNode_t* root);
// Recursively traverses root tree using preorder (root, left, right)
void node_preorder_traversal(BTNode_t* root);
// Recursively traverses root tree using postorder (left, right, root)
void node_postorder_traversal(BTNode_t* root);
// Uses a generic stack to traverse root tree using DFS (preorder - root, left, right)
void node_dfs_traversal(BTNode_t* root);
// Uses a generic queue to traverse root tree using BFS (level-order)
void node_bfs_traversal(BTNode_t* root);

/* Inspection / Queries */

// Checks if the binary tree is empty
bool bt_is_empty(BinaryTree_t* tree);
// Checks if the node is a leaf (has no children, returns false if NULL)
bool node_is_leaf(BTNode_t* node);
// Checks if the two subtrees are equal
bool node_are_equal(BTNode_t* root1, BTNode_t* root2);
// Gets the height of the subtree (the longest path from root to leaf)
// Returns -1 if root is NULL and 0 if root is a leaf
int node_height(BTNode_t* root);
// Gets the total number of nodes in the subtree (0 if NULL)
int node_count(BTNode_t* root);
// Gets the depth of the tree (how many nodes up until root)
// Returns 0 if root is NULL and depth(root) = 0
int node_depth(BTNode_t* node);
// Counts how many leaves in the subtree (0 if NULL)
int node_leaves_count(BTNode_t* root);
// Returns true if node is a descendant of ancestor
bool node_is_descendant(BTNode_t* ancestor, BTNode_t* node);
// Returns true if potential_ancestor is an ancestor of node
bool node_is_ancestor(BTNode_t* node, BTNode_t* potential_ancestor);
// Gets sibling of node (returns NULL if node is NULL or no sibling or no parent)
BTNode_t* node_get_sibling(BTNode_t* node);
// Gets uncle of node (returns NULL if node is NULL or no uncle or no parent)
BTNode_t* node_get_uncle(BTNode_t* node);

/* Searching and Distances */

// Searches for node in subtree with data equal to target (returns NULL if not found)
BTNode_t* node_search(BTNode_t* root, int target);
// Computes distance (number of edges) between two nodes
// Returns -1 if nodes are not in the same tree
int node_distance(BTNode_t* node1, BTNode_t* node2);
// Gets the next node from the inorder traversal of the tree (returns NULL if node is last in the traversal order)
BTNode_t* node_next_inorder(BTNode_t* node);
// Gets the next node from the preorder traversal of the tree (returns NULL if node is last in the traversal order)
BTNode_t* node_next_preorder(BTNode_t* node);
// Gets the next node from the postorder traversal of the tree (returns NULL if node is last in the traversal order)
BTNode_t* node_next_postorder(BTNode_t* node);

/* Reconstruction */

// Creates inorder traversal array of the subtree
int* node_inorder_to_array(BTNode_t* root);
// Reconstructs a binary tree from its preorder and inorder traversal arrays
BinaryTree_t* bt_reconstruct_from_pre_in(int* preorder, int* inorder, int n);
// Reconstructs a binary tree from its postorder and inorder traversal arrays
BinaryTree_t* bt_reconstruct_from_post_in(int* postorder, int* inorder, int n);

#endif // BINARY_TREE_H
