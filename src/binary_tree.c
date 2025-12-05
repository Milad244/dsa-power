#include "../include/binary_tree.h"
#include <stdlib.h>
#include <stdio.h>

BinaryTree_t* bt_create(void) {
    BinaryTree_t* tree = (BinaryTree_t*) malloc(sizeof(BinaryTree_t));
    if (tree == NULL) return NULL;

    tree->root = NULL;
    return tree;
}

BTNode_t* node_create(int item) {
    BTNode_t* node = (BTNode_t*) malloc(sizeof(BTNode_t));
    if (node == NULL) return NULL;

    node->data = item;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void node_inorder_traversal(BTNode_t* root) {
    // left, root, right
    // base case
    if (root == NULL) return;
    // Recursive step
    node_inorder_traversal(root->left);
    printf("%d ", root->data);
    node_inorder_traversal(root->right);
}

void node_preorder_traversal(BTNode_t* root) {
    // root, left, right
    // base case
    if (root == NULL) return;
    // Recursive step
    printf("%d ", root->data);
    node_preorder_traversal(root->left);
    node_preorder_traversal(root->right);
}

void node_postorder_traversal(BTNode_t* root) {
    // left, right,root
    // base case
    if (root == NULL) return;
    // Recursive step
    node_postorder_traversal(root->left);
    node_postorder_traversal(root->right);
    printf("%d ", root->data);
}

// TODO but need general stacks and queues

void node_dfs_traversal(BTNode_t* root) {
    
}

void node_bfs_traversal(BTNode_t* root) {

}

void node_insert_left(BTNode_t* parent, BTNode_t* child) {
    if (parent == NULL || child == NULL) return;
    parent->left = child;
    child->parent = parent;
}

void node_insert_right(BTNode_t* parent, BTNode_t* child) {
    if (parent == NULL || child == NULL) return;
    parent->right = child;
    child->parent = parent;
}

bool bt_is_empty(BinaryTree_t* tree) {
    return tree == NULL || tree->root == NULL;
}

bool node_is_leaf(BTNode_t* node) {
    if (node == NULL) return false;
    return node->left == NULL && node->right == NULL;
}

bool node_are_equal(BTNode_t* root1, BTNode_t* root2) {
    // Base cases
    if (root1 == NULL && root2 == NULL) return true;
    if (root1 == NULL || root2 == NULL) return false;
    if (root1->data != root2->data) return false;

    // Recursive step
    return node_are_equal(root1->left, root2->left) && node_are_equal(root1->right, root2->right);
}

static int max(int a, int b) {
    return (a > b) ? a : b;
}

int node_height(BTNode_t* root) {
    if (root == NULL) return -1;
    return 1 + max(node_height(root->left), node_height(root->right));
}

// returns 0 if NULL
int node_count(BTNode_t* root) {
    if (root == NULL) return 0;
    return 1 + node_count(root->left) + node_count(root->right);
}

// returns 0 if NULL and count starts at 0 (so node_depth(root) = 0)
int node_depth(BTNode_t* node) {
    if (node == NULL) return 0;
    int depth = 0;
    while (node->parent != NULL) {
        depth ++;
        node = node->parent;
    }
    return depth;
}

int node_leaves_count(BTNode_t* root) {
    if (root == NULL) return 0;

    if (node_is_leaf(root) == true) return 1; // Leaf so children won't be leaves

    return node_leaves_count(root->left) + node_leaves_count(root->right); // Not leaf so check children
}

// Returns true if node is a descendant of ancestor
bool node_is_descendant(BTNode_t* ancestor, BTNode_t* node) {
    if (ancestor == NULL || node == NULL) return false;
    
    BTNode_t* curr = node->parent;
    while(curr != NULL) {
        if (curr == ancestor) return true;
        curr = curr->parent;
    }

    return false;
}

// Returns true if potential_ancestor is an ancestor of node
bool node_is_ancestor(BTNode_t* node, BTNode_t* potential_ancestor) {
    return node_is_descendant(potential_ancestor, node);
}

BTNode_t* node_get_sibling(BTNode_t* node) {
    if (node == NULL || node->parent == NULL) return NULL;

    if (node->parent->left == node) return node->parent->right;
    else return node->parent->left;
}

BTNode_t* node_get_uncle(BTNode_t* node) {
    if (node == NULL) return NULL;
    return node_get_sibling(node->parent);
}

BTNode_t* bt_search(BTNode_t* root, int target) {
    // Base case
    if (root == NULL) return NULL;
    if (root->data == target) return root;
    // Recursive step
    BTNode_t* left = bt_search(root->left, target);
    if (left != NULL) return left;
    else return bt_search(root->right, target);
}

// Computes distance (number of edges) between two nodes
// Returns -1 if nodes are not in the same tree
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

        if (n1 == NULL || n2 == NULL) return -1; // Nodes are not in the same tree
    }
    BTNode_t* lca = n1;
    // Compute distance from each node to LCA
    BTNode_t* t = node1;
    int dist = 0;
    while (t != lca) {
        dist++;
        t = t->parent;
    }
    t = node2;
    while (t != lca) {
        dist++;
        t = t->parent;
    }
    return dist;
}

BTNode_t* node_next_inorder(BTNode_t* node) {
  BTNode_t* parent = node->parent;
  if (parent == NULL) { // Root so we go right then left until null
    if (node->right == NULL) return NULL; // nothing on the right so inorder is finished
    node = node->right;
    while(node->left != NULL) {
      node = node->left;
    }
    return node;
  }

  if (node->right != NULL) { // Since not root, if has right child then right side next inorder
    node = node->right;
    // We need to go as left as possible
    while (node->left != NULL) {
      node = node->left;
    }
    return node;
  }

  // If no right children then we need to find the parent who's node is left and return it
  while(parent != NULL) {
    if (parent->left == node) { // Parent with left child found and returned
      return parent;
    }
    // Othewise increment both
    node = parent;
    parent = parent->parent;
  }
  // Must be last element
  return NULL;
}


// Helper to fill array recursively inorder
static void fill_inorder_array(BTNode_t* node, int* arr, int* index) {
    if (node == NULL) return;

    fill_inorder_array(node->left, arr, index);
    arr[*index] = node->data;
    (*index)++;
    fill_inorder_array(node->right, arr, index);
}

int* node_inorder_to_array(BTNode_t* root) {
    if (root == NULL) return NULL;

    int n = node_count(root);
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
    BTNode_t* root = node_create(root_value);
    (*pre_index)++;

    // We go through inorder until reaching the root value
    int node_index = in_start;
    while (node_index <= in_end && inorder[node_index] != root_value) node_index++;
    root->left = build_tree_from_pre_in(preorder, pre_index, inorder, in_start, node_index - 1);
    root->right = build_tree_from_pre_in(preorder, pre_index, inorder, node_index + 1, in_end);

    return root;
}

BinaryTree_t* bt_reconstruct_from_pre_in(int* preorder, int* inorder, int n) {
    int pre_index = 0;
    BTNode_t* root = build_tree_from_pre_in(preorder, &pre_index, inorder, 0, n - 1);
    BinaryTree_t* res = bt_create();
    res->root = root;
    return res;
}

// Helper function to build tree from postorder and inorder arrays
static BTNode_t* build_tree_from_post_in(int* postorder, int* post_index, int* inorder, int in_start, int in_end) {
    if (in_start > in_end) return NULL;

    int root_value = postorder[*post_index];
    BTNode_t* root = node_create(root_value);
    (*post_index)--;

    // We go through inorder until reaching the root value
    int node_index = in_start;
    while (node_index <= in_end && inorder[node_index] != root_value) node_index++;
    root->right = build_tree_from_post_in(postorder, post_index, inorder, node_index + 1, in_end);
    root->left = build_tree_from_post_in(postorder, post_index, inorder, in_start, node_index - 1);

    return root;
}

BinaryTree_t* bt_reconstruct_from_post_in(int* postorder, int* inorder, int n) {
    int post_index = n - 1;
    BTNode_t* root = build_tree_from_post_in(postorder, &post_index, inorder, 0, n - 1);
    BinaryTree_t* res = bt_create();
    res->root = root;
    return res;
}

void node_free_subtree(BTNode_t* root) {
    if (root == NULL) return;
    node_free_subtree(root->left);
    node_free_subtree(root->right);
    free(root);
}

void bt_free(BinaryTree_t* tree) {
    if (tree == NULL) return;
    node_free_subtree(tree->root);
    free(tree);
}
