#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdbool.h>

// Node for binary tree
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

// Creates a new empty binary tree
BinaryTree_t* create_binary_tree(void);

// Creates a new node with given value
BTNode_t* create_node(int item);

// Traversal functions
void inorder_traversal(BTNode_t* root);
void preorder_traversal(BTNode_t* root);
void postorder_traversal(BTNode_t* root);
void dfs_traversal(BTNode_t* root); // general DFS (preorder by default)
void bfs_traversal(BTNode_t* root);

// Insert child nodes
void insert_left(BTNode_t* parent, BTNode_t* child);
void insert_right(BTNode_t* parent, BTNode_t* child);

// Tree checks
bool tree_is_empty(BinaryTree_t* tree);
bool is_leaf(BTNode_t* node);
bool are_equal(BTNode_t* root1, BTNode_t* root2);

// Tree metrics
int tree_height(BTNode_t* root);
int count_nodes(BTNode_t* root);
int node_depth(BTNode_t* node);
int count_leaves(BTNode_t* root);

// Relationship helpers
bool is_descendant(BTNode_t* ancestor, BTNode_t* node);
bool is_ancestor(BTNode_t* node, BTNode_t* potential_ancestor);
BTNode_t* get_sibling(BTNode_t* node);
BTNode_t* get_uncle(BTNode_t* node);

// Search
BTNode_t* tree_search(BTNode_t* root, int target);

// Computes distance between two nodes in the tree
int node_distance(BTNode_t* node1, BTNode_t* node2);

// Create array from binary tree
int* inorder_to_array(BTNode_t* root); // Not doing others because same logic

// Reconstructs a binary tree from given traversal arrays
BinaryTree_t* reconstruct_tree_from_pre_in(int* preorder, int* inorder, int n);
BinaryTree_t* reconstruct_tree_from_post_in(int* postorder, int* inorder, int n);

// Freeing memory
void free_subtree(BTNode_t* root);
void free_tree(BinaryTree_t* tree);

#endif // BINARY_TREE_H
