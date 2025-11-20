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

// Checks if two nodes are equal
bool are_equal(BTNode_t* root1, BTNode_t* root2) {
    // Base cases
    if (root1 == NULL && root2 == NULL) return true;
    if (root1 == NULL || root2 == NULL) return false;
    if (root1->data != root2->data) return false;

    // Recursive step
    return are_equal(root1->left, root2->left) && are_equal(root1->right, root2->right);
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

// Counts leaves in tree
int count_leaves(BTNode_t* root) {
    if (root == NULL) return 0;

    if (is_leaf(root) == true) return 1; // Leaf so children won't be leaves

    return count_leaves(root->left) + count_leaves(root->right); // Not leaf so check children
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

// Computes distance (number of edges) from 'root' to 'target'
// Returns -1 if target not found in this subtree
int node_distance(BTNode_t* node1, BTNode_t* node2){
    if (node1 == NULL || node2 == NULL) return -1;

    BTNode_t* n1 = node1;
    BTNode_t* n2 = node2;
    int d1 = node_depth(node1);
    int d2 = node_depth(node2);

    // Traversing up until both nodes are at same depth
    while (d1 > d2) {
        n1 = n1->parent;
        d1--;
    }
    while (d2 > d1) {
        n2 = n2->parent;
        d2--;
    }

    // Go up until both parents are the same node, this is their lowest common ancestor (LCA)
    while (n1 != n2) {
        n1 = n1->parent;
        n2 = n2->parent;
    }
    BTNode_t* lca = n1;
    // Compute distance from each node to LCA
    int dist = 0;
    while (node1 != lca) {
        dist++;
        node1 = node1->parent;
    }
    while (node2 != lca) {
        dist++;
        node2 = node2->parent;
    }
    return dist;
}

/* Version without parent attribute in BT
// Finds the lowest common ancestor of two nodes in the tree
BTNode_t* bt_find_lca(BTNode_t* node1, BTNode_t* node2) {
    if (node1 == NULL || node2 == NULL) return NULL;

    int d1 = node_depth(node1);
    int d2 = node_depth(node2);

    // Traversing up until both nodes are at same depth
    while (d1 > d2) {
        node1 = node1->parent;
        d1--;
    }
    while (d2 > d1) {
        node2 = node2->parent;
        d2--;
    }

    // Go up until both parents are the same node
    while (node1 != node2) {
        node1 = node1->parent;
        node2 = node2->parent;
    }

    return node1;
}

// Finds the lowest common ancestor of two nodes in the tree (no parent pointers)
BTNode_t* bt_find_lca(BTNode_t* root, BTNode_t* node1, BTNode_t* node2) {
    if (root == NULL) return NULL;

    // If root is one of the nodes, it's the LCA
    if (root == node1 || root == node2) return root;

    // Recurse into left and right subtrees
    BTNode_t* left_lca = bt_find_lca(root->left, node1, node2);
    BTNode_t* right_lca = bt_find_lca(root->right, node1, node2);

    // If both sides returned non-NULL, root is LCA
    if (left_lca && right_lca) return root;

    // Otherwise return the non-NULL side (or NULL if neither)
    return (left_lca != NULL) ? left_lca : right_lca;
}

// Computes distance (number of edges) from 'root' to 'target'
// Returns -1 if target not found in this subtree
int bt_distance_from_root(BTNode_t* root, BTNode_t* target) {
    // Base case
    if (root == NULL) return -1;
    if (root == target) return 0;

    // Recursively searching both sides
    int left_dist = bt_distance_from_root(root->left, target);
    if (left_dist != -1) return left_dist + 1;

    int right_dist = bt_distance_from_root(root->right, target);
    if (right_dist != -1) return right_dist + 1;

    return -1; // Not found
}

// Computes distance between two nodes using LCA (no parent pointers)
int node_distance(BTNode_t* root, BTNode_t* node1, BTNode_t* node2) {
    if (root == NULL || node1 == NULL || node2 == NULL) return -1;

    BTNode_t* lca = bt_find_lca(root, node1, node2);
    if (lca == NULL) return -1;

    int dist1 = bt_distance_from_root(lca, node1);
    int dist2 = bt_distance_from_root(lca, node2);

    if (dist1 == -1 || dist2 == -1) return -1;

    return dist1 + dist2;
}

// Less standard way of doing it with parents

// Returns an array of pointers from the node itself up to the root (inclusive)
// res[0] = node, res[depth] = root
// Caller must free the returned array
static BTNode_t** bt_get_parents_arr(BTNode_t* node, int depth) {
    BTNode_t* curr = node;
    BTNode_t** res = (BTNode_t**) malloc(sizeof(BTNode_t*) * (depth + 1)); // +1 for itself
    if (res == NULL) return NULL;

    for (int i = 0; i <= depth; i++) {
        res[i] = curr;
        curr = curr->parent;
    }

    return res;
}

// Computes distance between two nodes in the tree
int node_distance(BTNode_t* node1, BTNode_t* node2) {
    if (node1 == NULL || node2 == NULL) return -1;
    // Get depth of both as array and then subtract 2*common nodes
    int depth_1 = get_depth(node1);
    int depth_2 = get_depth(node2);
    BTNode_t** parents_1 = bt_get_parents_arr(node1, depth_1);
    if (parents_1 == NULL) return -1;
    BTNode_t** parents_2 = bt_get_parents_arr(node2, depth_2);
    if (parents_2 == NULL) {
        free(parents_1);
        return -1;
    };

    int total_count = depth_1 + depth_2 + 2; // + 2 cause including themselves
    int common_count = 0;

    int ind_1 = depth_1;
    int ind_2 = depth_2;
    while (ind_1 >= 0 && ind_2 >= 0 && parents_1[ind_1] == parents_2[ind_2]) {
        common_count ++;
        ind_1 --;
        ind_2 --;
    }

    free(parents_1);
    free(parents_2);

    return total_count - (2 * common_count);
}
*/

// Helper to fill array recursively inorder
static void fill_inorder_array(BTNode_t* node, int* arr, int* index) {
    if (node == NULL) return;

    fill_inorder_array(node->left, arr, index);
    arr[*index] = node->data;
    (*index)++;
    fill_inorder_array(node->right, arr, index);
}

// Creates inorder array from binary tree
int* inorder_to_array(BTNode_t* root) {
    if (root == NULL) return NULL;

    int n = count_nodes(root);
    int* res = (int*) malloc(sizeof(int) * n);
    if (res == NULL) return NULL;

    int index = 0;
    fill_inorder_array(root, res, &index);
    return res;
}

// Helper function to build tree from preorder and inorder arrays
static BTNode_t* build_tree_from_pre_in(int* preorder, int* pre_index, int* inorder, int in_start, int in_end) {
    if (in_start > in_end) return NULL;

    int root_value = preorder[*pre_index];
    BTNode_t* root = create_node(root_value);
    (*pre_index)++;

    // We go through inorder until reaching the root value
    int node_index = in_start;
    while (node_index <= in_end && inorder[node_index] != root_value) node_index++;
    root->left = build_tree_from_pre_in(preorder, pre_index, inorder, in_start, node_index - 1);
    root->right = build_tree_from_pre_in(preorder, pre_index, inorder, node_index + 1, in_end);

    return root;
}

// Reconstructs a binary tree from preorder and inorder arrays
BinaryTree_t* reconstruct_tree_from_pre_in(int* preorder, int* inorder, int n) {
    int pre_index = 0;
    BTNode_t* root = build_tree_from_pre_in(preorder, &pre_index, inorder, 0, n - 1);
    BinaryTree_t* res = create_binary_tree();
    res->root = root;
    return res;
}

// Helper function to build tree from postorder and inorder arrays
static BTNode_t* build_tree_from_post_in(int* postorder, int* post_index, int* inorder, int in_start, int in_end) {
    if (in_start > in_end) return NULL;

    int root_value = postorder[*post_index];
    BTNode_t* root = create_node(root_value);
    (*post_index)--;

    // We go through inorder until reaching the root value
    int node_index = in_start;
    while (node_index <= in_end && inorder[node_index] != root_value) node_index++;
    root->right = build_tree_from_post_in(postorder, post_index, inorder, node_index + 1, in_end);
    root->left = build_tree_from_post_in(postorder, post_index, inorder, in_start, node_index - 1);

    return root;
}

// Reconstructs a binary tree from postorder and inorder arrays
BinaryTree_t* reconstruct_tree_from_post_in(int* postorder, int* inorder, int n) {
    int post_index = n - 1;
    BTNode_t* root = build_tree_from_post_in(postorder, &post_index, inorder, 0, n - 1);
    BinaryTree_t* res = create_binary_tree();
    res->root = root;
    return res;
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
