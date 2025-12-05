#include "../include/bst.h"
#include "../include/binary_tree.h"
#include <stdlib.h>
#include <stdio.h>

BST_t* BST_create(void) {
    BST_t* tree = (BST_t*) malloc(sizeof(BST_t));
    if (tree == NULL) return NULL;

    tree->root = NULL;
    tree->size = 0;
    return tree;
}

void BST_insert(BST_t* tree, int item) {
    if (tree == NULL) return;
    BTNode_t* node = tree->root;
    while (node != NULL) { // We use binary search method to find the right spot to insert
        if (node->data == item) return; // We don't insert a duplicate
        else if (node->data > item) node = node->left; // If item is less then it goes left subtree
        else node = node->right; // If item is right then it goes right subtree
    }
    node = node_create(item);
    tree->size++;
}

BTNode_t* BST_search(BST_t* tree, int item) {
    if (tree == NULL) return NULL;
    BTNode_t* node = tree->root;
    while (node != NULL) { // We use binary search method to find the item
        if (node->data == item) return node;
        else if (node->data > item) node = node->left; // If item is less then it must be in left subtree
        else node = node->right; // If item is right then it must be in right subtree
    }
    return NULL; // item was not found
}

int BST_find_min(BTNode_t* root) {
    if (root == NULL) return -1;
    // Min will be furthest left node
    BTNode_t* prev = root;
    BTNode_t* curr = root->left;
    while (curr != NULL) {
        prev = curr;
        curr = curr->left;
    }
    return prev->data;
}

int BST_find_max(BTNode_t* root) {
    if (root == NULL) return -1;
    // Min will be furthest right node
    BTNode_t* prev = root;
    BTNode_t* curr = root->right;
    while (curr != NULL) {
        prev = curr;
        curr = curr->right;
    }
    return prev->data;
}

static void BST_delete_no_child(BTNode_t* to_delete) {
    BTNode_t* parent = to_delete->parent;
        if (parent != NULL) { // Need to update parent before deleting
            if (parent->left == to_delete) parent->left = NULL;
            else parent->right = NULL;
        }
        free(to_delete);
}

static void BST_delete_single_child(BST_t* tree, BTNode_t* to_delete) {
    BTNode_t* parent = to_delete->parent;
    BTNode_t* child;
    if (to_delete->left != NULL) child = to_delete->left;
    else child = to_delete->right;
    if (parent == NULL) { // Deleting root
        tree->root = child;
    } else {
        if (parent->left == to_delete) parent->left = child;
        else parent->right = child;
    }
    free(to_delete);
}

void BST_delete(BST_t* tree, int item) {
    if (tree == NULL) return;
    BTNode_t* to_delete = BST_search(tree, item);
    if (to_delete == false) return; // No item found to delete
    
    if (node_is_leaf(to_delete) == true) { // Has no children
        BST_delete_no_child(to_delete);
    } else if ((to_delete->left != NULL && to_delete->right == NULL) ||
        (to_delete->right != NULL && to_delete->left == NULL)) { // Has single child
        BST_delete_single_child(tree, to_delete);
    } else { // Has two children
        // We need to find the successor of to_delete, swap them, and delete that one because it will have < 2 children
        BTNode_t* successor = node_next_inorder(to_delete);
        int successor_value = successor->data;
        BST_delete(tree, successor_value);
        to_delete->data = successor_value;
    }
    tree->size--;
}

int BST_size(BST_t* tree) {
    if (tree == NULL) return 0;
    return tree->size;
}

// Helper function to recursively fill the array
static void fill_inorder(BTNode_t* root, int* arr, int* index) {
  // base case
  if (root == NULL) return;
  // recursive step
  fill_inorder(root->left, arr, index);
  arr[*index] = root->data;
  (*index)++;
  fill_inorder(root->right, arr, index);
}

int* BST_to_array(BST_t* bst) {
  int n = BST_size(bst);
  if (n == 0) return NULL;

  // inorder bst array
  int* res = (int*) malloc(sizeof(int) * n);
  if (res == NULL) return NULL;
  int index = 0;
  fill_inorder(bst->root, res, &index);
  return res;
}

// Helper function to reconstruct BST from a sorted array
static BTNode_t* reconstruct_BST_from_preorder(int* preorder, int start, int end) {
  if (start > end) return NULL;

  // We recursively make our root the start value and do the same for its children
  int root_value = preorder[start];
  BTNode_t* root =  node_create(root_value);
  if (root == NULL) return NULL;

  int pivot = start + 1; // Pivot will divide the left and right subtrees

  // Since preorder, pivot will be the first element that is greater than root
  while (pivot <= end && preorder[pivot] <= root_value) pivot++;

  BTNode_t* left = reconstruct_BST_from_preorder(preorder, start + 1, pivot - 1);
  root->left = left;
  if (left != NULL) left->parent = root;
  BTNode_t* right = reconstruct_BST_from_preorder(preorder, pivot, end);
  root->right = right;
  if (right != NULL) right->parent = root;

  return root;
}

BST_t* BST_from_preorder(int* preorder, int n) {
    BST_t* res = BST_create();
    if (res == NULL) return NULL;
    if (n == 0) return res;
    
    res->root = reconstruct_BST_from_preorder(preorder, 0, n - 1);
    res->size = n; // Size of BST will be n
    return res;
}

// Helper function to check if BST is valid. Assumes every value is unique
static bool is_BST_using_prev(BTNode_t* root, int* prev, bool* first) {
  if (root == NULL) return true;

  // Inorder traversal while keeping track of prev
  if (is_BST_using_prev(root->left, prev, first) == false) return false;

  if (*first == true) { 
    *first = false; // No longer first
  } else {
    if (root->data <= *prev) return false; // Check that current element is not smaller or equal to prev
  }
  (*prev) = root->data; // Updating prev

  return is_BST_using_prev(root->right, prev, first);
}

bool is_BST(BTNode_t* root) {
  if (root == NULL) return false;
  int prev = 0;
  bool first = true;
  return is_BST_using_prev(root, &prev, &first);
}

void BST_free(BST_t* tree) {
    if (tree == NULL) return;
    node_free_subtree(tree->root);
    free(tree);
}
