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

// Creates a new binary tree
BinaryTree_t* bt_create(void);

// Creates a new node with given value
BTNode_t* node_create(int item);

// Traversal functions

void node_inorder_traversal(BTNode_t* root);
void node_preorder_traversal(BTNode_t* root);
void node_postorder_traversal(BTNode_t* root);
void node_dfs_traversal(BTNode_t* root); // DFS (preorder)
void node_bfs_traversal(BTNode_t* root); // BFS (level-order)

// Insert child nodes

void node_insert_left(BTNode_t* parent, BTNode_t* child);
void node_insert_right(BTNode_t* parent, BTNode_t* child);

// Checks

bool bt_is_empty(BinaryTree_t* tree);
bool node_is_leaf(BTNode_t* node);
bool node_are_equal(BTNode_t* root1, BTNode_t* root2);

// Metrics

int node_height(BTNode_t* root);
int node_count(BTNode_t* root);
int node_depth(BTNode_t* node);
int node_leaves_count(BTNode_t* root);

// Relationship helpers

bool node_is_descendant(BTNode_t* ancestor, BTNode_t* node);
bool node_is_ancestor(BTNode_t* node, BTNode_t* potential_ancestor);
BTNode_t* node_get_sibling(BTNode_t* node);
BTNode_t* node_get_uncle(BTNode_t* node);

// Searching and distances

BTNode_t* bt_search(BTNode_t* root, int target);
int node_distance(BTNode_t* node1, BTNode_t* node2);
BTNode_t* node_next_inorder(BTNode_t* node);

// Creates inorder array from binary tree
int* node_inorder_to_array(BTNode_t* root);
// Not doing others because same logic

// Reconstructs a binary tree from given traversal arrays

BinaryTree_t* bt_reconstruct_from_pre_in(int* preorder, int* inorder, int n);
BinaryTree_t* bt_reconstruct_from_post_in(int* postorder, int* inorder, int n);

// Freeing memory

void node_free_subtree(BTNode_t* root);
void bt_free(BinaryTree_t* tree);

#endif // BINARY_TREE_H
