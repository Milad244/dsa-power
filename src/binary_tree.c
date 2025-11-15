#include "../include/binary_tree.h"
#include <stdlib.h>
#include <stdio.h>

// Creates a new empty binary tree
BinaryTree_t* create_binary_tree(void) {
    BinaryTree_t* tree = (BinaryTree_t*) malloc(sizeof(BinaryTree_t));
    if (tree == NULL) return NULL;

    tree->root = NULL;
    return tree;
}

// Creates a new node with given value
BTNode_t* create_node(int item) {
    BTNode_t* node = (BTNode_t*) malloc(sizeof(BTNode_t));
    if (node == NULL) return NULL;

    node->data = item;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Inorder traversal
void inorder_traversal(BTNode_t* root) {
    // left, root, right
    // base case
    if (root == NULL) return;
    // Recursive step
    inorder_traversal(root->left);
    printf("%d ", root->data);
    inorder_traversal(root->right);
}

// Preorder traversal
void preorder_traversal(BTNode_t* root) {
    // root, left, right
    // base case
    if (root == NULL) return;
    // Recursive step
    printf("%d ", root->data);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

// Postorder traversal
void postorder_traversal(BTNode_t* root) {
    // left, right,root
    // base case
    if (root == NULL) return;
    // Recursive step
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    printf("%d ", root->data);
}

// TODO but need general stacks and queues

// Depth-First Search traversal (preorder by default)
void dfs_traversal(BTNode_t* root) {
    
}

// Breadth-First Search / Level-order traversal
void bfs_traversal(BTNode_t* root) {

}

// Inserts a left child
void insert_left(BTNode_t* parent, BTNode_t* child) {
    if (parent == NULL || child == NULL) return;
    parent->left = child;
    child->parent = parent;
}

// Inserts a right child
void insert_right(BTNode_t* parent, BTNode_t* child) {
    if (parent == NULL || child == NULL) return;
    parent->right = child;
    child->parent = parent;
}

// Checks if tree is empty
bool tree_is_empty(BinaryTree_t* tree) {
    return tree == NULL || tree->root == NULL;
}

// Checks if node is a leaf
bool is_leaf(BTNode_t* node) {
    if (node == NULL) return false;
    return node->left == NULL && node->right == NULL;
}

static int max(int a, int b) {
    return (a > b) ? a : b;
}

// Computes height of tree
int tree_height(BTNode_t* root) {
    if (root == NULL) return -1;
    return 1 + max(tree_height(root->left), tree_height(root->right));
}

// Counts nodes in tree
int count_nodes(BTNode_t* root) {
    if (root == NULL) return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

// Computes depth of a node
int node_depth(BTNode_t* node) {
    if (node == NULL) return 0;
    int depth = 0;
    while (node->parent != NULL) {
        depth ++;
        node = node->parent;
    }
    return depth;
}

// Returns true if node is a descendant of ancestor
bool is_descendant(BTNode_t* ancestor, BTNode_t* node) {
    if (ancestor == NULL || node == NULL) return false;
    
    BTNode_t* curr = node->parent;
    while(curr != NULL) {
        if (curr == ancestor) return true;
        curr = curr->parent;
    }

    return false;
}

// Returns true if potential_ancestor is an ancestor of node
bool is_ancestor(BTNode_t* node, BTNode_t* potential_ancestor) {
    return is_descendant(potential_ancestor, node);
}

// Gets sibling of a node
BTNode_t* get_sibling(BTNode_t* node) {
    if (node == NULL || node->parent == NULL) return NULL;

    if (node->parent->left == node) return node->parent->right;
    else return node->parent->left;
}

// Gets uncle of a node
BTNode_t* get_uncle(BTNode_t* node) {
    if (node == NULL) return NULL;
    return get_sibling(node->parent);
}

// Searches tree for a value
BTNode_t* tree_search(BTNode_t* root, int target) {
    // Base case
    if (root == NULL) return NULL;
    if (root->data == target) return root;
    // Recursive step
    BTNode_t* left = tree_search(root->left, target);
    if (left != NULL) return left;
    else return tree_search(root->right, target);
}

// Computes distance between two nodes in the tree
int node_distance(BTNode_t* node1, BTNode_t* node2) {
    // TODO
    return 0;
}

// Reconstructs a binary tree from preorder and inorder arrays
BinaryTree_t* reconstruct_tree_from_pre_in(int* preorder, int* inorder, int n) {
    // TODO
    return NULL;
}

// Reconstructs a binary tree from postorder and inorder arrays
BinaryTree_t* reconstruct_tree_from_post_in(int* postorder, int* inorder, int n) {
    // TODO
    return NULL;
}

// Frees a subtree
void free_subtree(BTNode_t* root) {
    if (root == NULL) return;
    free_subtree(root->left);
    free_subtree(root->right);
    free(root);
}

// Frees an entire tree
void free_tree(BinaryTree_t* tree) {
    if (tree == NULL) return;
    free_subtree(tree->root);
    free(tree);
}
