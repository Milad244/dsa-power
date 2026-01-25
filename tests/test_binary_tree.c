#include "Unity/unity.h"
#include "binary_tree.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

/* When n = 7:
        0
       / \
      1   2
     / \ / \
    3  4 5  6
*/
// Helper that creates a binary tree with n items of value 0, 1, 2, ..., n - 1
static BinaryTree_t* make_tree_with_n(int n) {
    BinaryTree_t* tree = bt_create();
    if (n == 0) return tree;
    
    tree->root = node_create(0);
    if (n == 1) return tree;
    
    // Build a balanced tree for testing
    BTNode_t* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = tree->root;
    
    int value = 1;
    while (front < rear && value < n) {
        BTNode_t* curr = queue[front++];
        
        if (value < n) {
            curr->left = node_create(value++);
            curr->left->parent = curr;
            queue[rear++] = curr->left;
        }
        
        if (value < n) {
            curr->right = node_create(value++);
            curr->right->parent = curr;
            queue[rear++] = curr->right;
        }
    }
    
    return tree;
}

/* bt_create tests */

void test_bt_create(void) {
    BinaryTree_t* tree = bt_create();

    TEST_ASSERT_NOT_NULL(tree);
    TEST_ASSERT_NULL(tree->root);

    bt_free(tree);
}

/* node_create tests */

void test_node_create(void) {
    BTNode_t* node = node_create(42);

    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(42, node->data);
    TEST_ASSERT_NULL(node->parent);
    TEST_ASSERT_NULL(node->left);
    TEST_ASSERT_NULL(node->right);

    free(node);
}

/* node_free_subtree tests */

void test_node_free_subtree_null(void) {
    node_free_subtree(NULL);
}

void test_node_free_subtree_single(void) {
    BTNode_t* node = node_create(42);
    node_free_subtree(node);
}

void test_node_free_subtree_multiple(void) {
    BinaryTree_t* tree = make_tree_with_n(7);
    node_free_subtree(tree->root);
    tree->root = NULL;
    bt_free(tree);
}

/* bt_free tests */

void test_bt_free_null(void) {
    bt_free(NULL);
}

void test_bt_free_empty(void) {
    BinaryTree_t* tree = bt_create();
    bt_free(tree);
}

void test_bt_free_nonnull(void) {
    BinaryTree_t* tree = make_tree_with_n(5);
    bt_free(tree);
}

/* node_insert_left tests */

void test_node_insert_left_null_parent(void) {
    BTNode_t* child = node_create(5);
    node_insert_left(NULL, child);
    free(child);
}

void test_node_insert_left_null_child(void) {
    BTNode_t* parent = node_create(10);
    node_insert_left(parent, NULL);
    free(parent);
}

void test_node_insert_left_valid(void) {
    BTNode_t* parent = node_create(10);
    BTNode_t* child = node_create(5);
    node_insert_left(parent, child);

    TEST_ASSERT_EQUAL_PTR(child, parent->left);
    TEST_ASSERT_EQUAL_PTR(parent, child->parent);

    free(parent);
    free(child);
}

void test_node_insert_left_override(void) {
    BTNode_t* parent = node_create(10);
    BTNode_t* child1 = node_create(5);
    BTNode_t* child2 = node_create(3);
    
    node_insert_left(parent, child1);
    node_insert_left(parent, child2);

    TEST_ASSERT_EQUAL_PTR(child2, parent->left);
    TEST_ASSERT_EQUAL_PTR(parent, child2->parent);

    free(parent);
    free(child1);
    free(child2);
}

/* node_insert_right tests */

void test_node_insert_right_null_parent(void) {
    BTNode_t* child = node_create(15);
    node_insert_right(NULL, child);
    free(child);
}

void test_node_insert_right_null_child(void) {
    BTNode_t* parent = node_create(10);
    node_insert_right(parent, NULL);
    free(parent);
}

void test_node_insert_right_valid(void) {
    BTNode_t* parent = node_create(10);
    BTNode_t* child = node_create(15);
    node_insert_right(parent, child);

    TEST_ASSERT_EQUAL_PTR(child, parent->right);
    TEST_ASSERT_EQUAL_PTR(parent, child->parent);

    free(parent);
    free(child);
}

void test_node_insert_right_override(void) {
    BTNode_t* parent = node_create(10);
    BTNode_t* child1 = node_create(15);
    BTNode_t* child2 = node_create(20);
    
    node_insert_right(parent, child1);
    node_insert_right(parent, child2);

    TEST_ASSERT_EQUAL_PTR(child2, parent->right);
    TEST_ASSERT_EQUAL_PTR(parent, child2->parent);

    free(parent);
    free(child1);
    free(child2);
}

/* bt_is_empty tests */

void test_bt_is_empty_null(void) {
    TEST_ASSERT_TRUE(bt_is_empty(NULL));
}

void test_bt_is_empty_empty(void) {
    BinaryTree_t* tree = bt_create();
    TEST_ASSERT_TRUE(bt_is_empty(tree));
    bt_free(tree);
}

void test_bt_is_empty_single(void) {
    BinaryTree_t* tree = make_tree_with_n(1);
    TEST_ASSERT_FALSE(bt_is_empty(tree));
    bt_free(tree);
}

void test_bt_is_empty_multiple(void) {
    BinaryTree_t* tree = make_tree_with_n(5);
    TEST_ASSERT_FALSE(bt_is_empty(tree));
    bt_free(tree);
}

/* node_is_leaf tests */

void test_node_is_leaf_null(void) {
    TEST_ASSERT_FALSE(node_is_leaf(NULL));
}

void test_node_is_leaf_single(void) {
    BTNode_t* node = node_create(42);
    TEST_ASSERT_TRUE(node_is_leaf(node));
    free(node);
}

void test_node_is_leaf_with_left_child(void) {
    BTNode_t* parent = node_create(10);
    BTNode_t* child = node_create(5);
    node_insert_left(parent, child);
    
    TEST_ASSERT_FALSE(node_is_leaf(parent));
    TEST_ASSERT_TRUE(node_is_leaf(child));
    
    free(parent);
    free(child);
}

void test_node_is_leaf_with_right_child(void) {
    BTNode_t* parent = node_create(10);
    BTNode_t* child = node_create(15);
    node_insert_right(parent, child);
    
    TEST_ASSERT_FALSE(node_is_leaf(parent));
    TEST_ASSERT_TRUE(node_is_leaf(child));
    
    free(parent);
    free(child);
}

void test_node_is_leaf_with_both_children(void) {
    BTNode_t* parent = node_create(10);
    BTNode_t* left = node_create(5);
    BTNode_t* right = node_create(15);
    node_insert_left(parent, left);
    node_insert_right(parent, right);
    
    TEST_ASSERT_FALSE(node_is_leaf(parent));
    TEST_ASSERT_TRUE(node_is_leaf(left));
    TEST_ASSERT_TRUE(node_is_leaf(right));
    
    free(parent);
    free(left);
    free(right);
}

/* node_are_equal tests */

void test_node_are_equal_both_null(void) {
    TEST_ASSERT_TRUE(node_are_equal(NULL, NULL));
}

void test_node_are_equal_one_null(void) {
    BTNode_t* node = node_create(42);
    TEST_ASSERT_FALSE(node_are_equal(node, NULL));
    TEST_ASSERT_FALSE(node_are_equal(NULL, node));
    free(node);
}

void test_node_are_equal_single_equal(void) {
    BTNode_t* node1 = node_create(42);
    BTNode_t* node2 = node_create(42);
    
    TEST_ASSERT_TRUE(node_are_equal(node1, node2));
    
    free(node1);
    free(node2);
}

void test_node_are_equal_single_not_equal(void) {
    BTNode_t* node1 = node_create(42);
    BTNode_t* node2 = node_create(99);
    
    TEST_ASSERT_FALSE(node_are_equal(node1, node2));
    
    free(node1);
    free(node2);
}

void test_node_are_equal_multiple_equal(void) {
    BinaryTree_t* tree1 = make_tree_with_n(5);
    BinaryTree_t* tree2 = make_tree_with_n(5);
    
    TEST_ASSERT_TRUE(node_are_equal(tree1->root, tree2->root));
    
    bt_free(tree1);
    bt_free(tree2);
}

void test_node_are_equal_multiple_not_equal(void) {
    BinaryTree_t* tree1 = make_tree_with_n(5);
    BinaryTree_t* tree2 = make_tree_with_n(5);
    tree2->root->data = 999;
    
    TEST_ASSERT_FALSE(node_are_equal(tree1->root, tree2->root));
    
    bt_free(tree1);
    bt_free(tree2);
}

/* node_height tests */

void test_node_height_null(void) {
    TEST_ASSERT_EQUAL(-1, node_height(NULL));
}

void test_node_height_single(void) {
    BTNode_t* node = node_create(42);
    TEST_ASSERT_EQUAL(0, node_height(node));
    free(node);
}

void test_node_height_two_levels(void) {
    BinaryTree_t* tree = make_tree_with_n(3);
    TEST_ASSERT_EQUAL(1, node_height(tree->root));
    bt_free(tree);
}

void test_node_height_multiple(void) {
    BinaryTree_t* tree = make_tree_with_n(7);
    TEST_ASSERT_EQUAL(2, node_height(tree->root));
    bt_free(tree);
}

/* node_count tests */

void test_node_count_null(void) {
    TEST_ASSERT_EQUAL(0, node_count(NULL));
}

void test_node_count_single(void) {
    BTNode_t* node = node_create(42);
    TEST_ASSERT_EQUAL(1, node_count(node));
    free(node);
}

void test_node_count_multiple(void) {
    BinaryTree_t* tree = make_tree_with_n(5);
    TEST_ASSERT_EQUAL(5, node_count(tree->root));
    bt_free(tree);
}

void test_node_count_full_tree(void) {
    BinaryTree_t* tree = make_tree_with_n(7);
    TEST_ASSERT_EQUAL(7, node_count(tree->root));
    bt_free(tree);
}

/* node_depth tests */

void test_node_depth_null(void) {
    TEST_ASSERT_EQUAL(0, node_depth(NULL));
}

void test_node_depth_root(void) {
    BinaryTree_t* tree = make_tree_with_n(1);
    TEST_ASSERT_EQUAL(0, node_depth(tree->root));
    bt_free(tree);
}

void test_node_depth_child(void) {
    BinaryTree_t* tree = make_tree_with_n(3);
    TEST_ASSERT_EQUAL(1, node_depth(tree->root->left));
    TEST_ASSERT_EQUAL(1, node_depth(tree->root->right));
    bt_free(tree);
}

void test_node_depth_grandchild(void) {
    BinaryTree_t* tree = make_tree_with_n(7);
    TEST_ASSERT_EQUAL(2, node_depth(tree->root->left->left));
    bt_free(tree);
}

/* node_leaves_count tests */

void test_node_leaves_count_null(void) {
    TEST_ASSERT_EQUAL(0, node_leaves_count(NULL));
}

void test_node_leaves_count_single(void) {
    BTNode_t* node = node_create(42);
    TEST_ASSERT_EQUAL(1, node_leaves_count(node));
    free(node);
}

void test_node_leaves_count_multiple(void) {
    BinaryTree_t* tree = make_tree_with_n(5);
    TEST_ASSERT_EQUAL(3, node_leaves_count(tree->root));
    bt_free(tree);
}

void test_node_leaves_count_full_tree(void) {
    BinaryTree_t* tree = make_tree_with_n(7);
    TEST_ASSERT_EQUAL(4, node_leaves_count(tree->root));
    bt_free(tree);
}

/* node_is_descendant tests */

void test_node_is_descendant_null(void) {
    BTNode_t* node = node_create(42);
    TEST_ASSERT_FALSE(node_is_descendant(NULL, node));
    TEST_ASSERT_FALSE(node_is_descendant(node, NULL));
    free(node);
}

void test_node_is_descendant_same_node(void) {
    BTNode_t* node = node_create(42);
    TEST_ASSERT_FALSE(node_is_descendant(node, node));
    free(node);
}

void test_node_is_descendant_direct_child(void) {
    BinaryTree_t* tree = make_tree_with_n(3);
    TEST_ASSERT_TRUE(node_is_descendant(tree->root, tree->root->left));
    bt_free(tree);
}

void test_node_is_descendant_grandchild(void) {
    BinaryTree_t* tree = make_tree_with_n(7);
    TEST_ASSERT_TRUE(node_is_descendant(tree->root, tree->root->left->left));
    bt_free(tree);
}

void test_node_is_descendant_not_descendant(void) {
    BinaryTree_t* tree = make_tree_with_n(7);
    TEST_ASSERT_FALSE(node_is_descendant(tree->root->left, tree->root->right));
    bt_free(tree);
}

/* node_is_ancestor tests */

void test_node_is_ancestor_null(void) {
    BTNode_t* node = node_create(42);
    TEST_ASSERT_FALSE(node_is_ancestor(node, NULL));
    TEST_ASSERT_FALSE(node_is_ancestor(NULL, node));
    free(node);
}

void test_node_is_ancestor_direct_parent(void) {
    BinaryTree_t* tree = make_tree_with_n(3);
    TEST_ASSERT_TRUE(node_is_ancestor(tree->root->left, tree->root));
    bt_free(tree);
}

void test_node_is_ancestor_grandparent(void) {
    BinaryTree_t* tree = make_tree_with_n(7);
    TEST_ASSERT_TRUE(node_is_ancestor(tree->root->left->left, tree->root));
    bt_free(tree);
}

void test_node_is_ancestor_not_ancestor(void) {
    BinaryTree_t* tree = make_tree_with_n(7);
    TEST_ASSERT_FALSE(node_is_ancestor(tree->root->left, tree->root->right));
    bt_free(tree);
}

/* node_get_sibling tests */

void test_node_get_sibling_null(void) {
    TEST_ASSERT_NULL(node_get_sibling(NULL));
}

void test_node_get_sibling_root(void) {
    BinaryTree_t* tree = make_tree_with_n(1);
    TEST_ASSERT_NULL(node_get_sibling(tree->root));
    bt_free(tree);
}

void test_node_get_sibling_left_child(void) {
    BinaryTree_t* tree = make_tree_with_n(3);
    BTNode_t* sibling = node_get_sibling(tree->root->left);
    TEST_ASSERT_EQUAL_PTR(tree->root->right, sibling);
    bt_free(tree);
}

void test_node_get_sibling_right_child(void) {
    BinaryTree_t* tree = make_tree_with_n(3);
    BTNode_t* sibling = node_get_sibling(tree->root->right);
    TEST_ASSERT_EQUAL_PTR(tree->root->left, sibling);
    bt_free(tree);
}

void test_node_get_sibling_only_left_child(void) {
    BTNode_t* parent = node_create(10);
    BTNode_t* left = node_create(5);
    node_insert_left(parent, left);
    
    TEST_ASSERT_NULL(node_get_sibling(left));
    
    free(parent);
    free(left);
}

/* node_get_uncle tests */

void test_node_get_uncle_null(void) {
    TEST_ASSERT_NULL(node_get_uncle(NULL));
}

void test_node_get_uncle_root(void) {
    BinaryTree_t* tree = make_tree_with_n(1);
    TEST_ASSERT_NULL(node_get_uncle(tree->root));
    bt_free(tree);
}

void test_node_get_uncle_child(void) {
    BinaryTree_t* tree = make_tree_with_n(3);
    TEST_ASSERT_NULL(node_get_uncle(tree->root->left));
    bt_free(tree);
}

void test_node_get_uncle_grandchild(void) {
    BinaryTree_t* tree = make_tree_with_n(7);
    BTNode_t* uncle = node_get_uncle(tree->root->left->left);
    TEST_ASSERT_EQUAL_PTR(tree->root->right, uncle);
    bt_free(tree);
}

/* node_search tests */

void test_node_search_null(void) {
    TEST_ASSERT_NULL(node_search(NULL, 42));
}

void test_node_search_single_found(void) {
    BTNode_t* node = node_create(42);
    BTNode_t* result = node_search(node, 42);
    TEST_ASSERT_EQUAL_PTR(node, result);
    free(node);
}

void test_node_search_single_not_found(void) {
    BTNode_t* node = node_create(42);
    BTNode_t* result = node_search(node, 99);
    TEST_ASSERT_NULL(result);
    free(node);
}

void test_node_search_multiple_found(void) {
    BinaryTree_t* tree = make_tree_with_n(7);
    BTNode_t* result = node_search(tree->root, 3);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(3, result->data);
    bt_free(tree);
}

void test_node_search_multiple_not_found(void) {
    BinaryTree_t* tree = make_tree_with_n(7);
    BTNode_t* result = node_search(tree->root, 100);
    TEST_ASSERT_NULL(result);
    bt_free(tree);
}

/* node_distance tests */

void test_node_distance_null(void) {
    BTNode_t* node = node_create(42);
    TEST_ASSERT_EQUAL(-1, node_distance(NULL, node));
    TEST_ASSERT_EQUAL(-1, node_distance(node, NULL));
    free(node);
}

void test_node_distance_same_node(void) {
    BTNode_t* node = node_create(42);
    TEST_ASSERT_EQUAL(0, node_distance(node, node));
    free(node);
}

void test_node_distance_parent_child(void) {
    BinaryTree_t* tree = make_tree_with_n(3);
    TEST_ASSERT_EQUAL(1, node_distance(tree->root, tree->root->left));
    bt_free(tree);
}

void test_node_distance_siblings(void) {
    BinaryTree_t* tree = make_tree_with_n(3);
    TEST_ASSERT_EQUAL(2, node_distance(tree->root->left, tree->root->right));
    bt_free(tree);
}

void test_node_distance_grandparent_grandchild(void) {
    BinaryTree_t* tree = make_tree_with_n(7);
    TEST_ASSERT_EQUAL(2, node_distance(tree->root, tree->root->left->left));
    bt_free(tree);
}

/* node_next_inorder tests */

void test_node_next_inorder_null(void) {
    TEST_ASSERT_NULL(node_next_inorder(NULL));
}

void test_node_next_inorder_single(void) {
    BTNode_t* node = node_create(42);
    TEST_ASSERT_NULL(node_next_inorder(node));
    free(node);
}

void test_node_next_inorder_multiple(void) {
    BinaryTree_t* tree = make_tree_with_n(5);
    BTNode_t* next = node_next_inorder(tree->root->left);
    TEST_ASSERT_NOT_NULL(next);
    bt_free(tree);
}

/* node_next_preorder tests */

void test_node_next_preorder_null(void) {
    TEST_ASSERT_NULL(node_next_preorder(NULL));
}

void test_node_next_preorder_single(void) {
    BTNode_t* node = node_create(42);
    TEST_ASSERT_NULL(node_next_preorder(node));
    free(node);
}

void test_node_next_preorder_with_left_child(void) {
    BinaryTree_t* tree = make_tree_with_n(3);
    BTNode_t* next = node_next_preorder(tree->root);
    TEST_ASSERT_EQUAL_PTR(tree->root->left, next);
    bt_free(tree);
}

void test_node_next_preorder_leaf(void) {
    BinaryTree_t* tree = make_tree_with_n(5);
    BTNode_t* next = node_next_preorder(tree->root->left->left);
    TEST_ASSERT_NOT_NULL(next);
    bt_free(tree);
}

/* node_next_postorder tests */

void test_node_next_postorder_null(void) {
    TEST_ASSERT_NULL(node_next_postorder(NULL));
}

void test_node_next_postorder_root(void) {
    BinaryTree_t* tree = make_tree_with_n(1);
    TEST_ASSERT_NULL(node_next_postorder(tree->root));
    bt_free(tree);
}

void test_node_next_postorder_leaf(void) {
    BinaryTree_t* tree = make_tree_with_n(3);
    BTNode_t* next = node_next_postorder(tree->root->left);
    TEST_ASSERT_NOT_NULL(next);
    bt_free(tree);
}

/* node_inorder_to_array tests */

void test_node_inorder_to_array_null(void) {
    int* arr = node_inorder_to_array(NULL);
    TEST_ASSERT_NULL(arr);
}

void test_node_inorder_to_array_single(void) {
    BTNode_t* node = node_create(42);
    int* arr = node_inorder_to_array(node);
    
    TEST_ASSERT_NOT_NULL(arr);
    TEST_ASSERT_EQUAL(42, arr[0]);
    
    free(arr);
    free(node);
}

void test_node_inorder_to_array_multiple(void) {
    BinaryTree_t* tree = make_tree_with_n(7);
    int* arr = node_inorder_to_array(tree->root);
    
    TEST_ASSERT_NOT_NULL(arr);
    TEST_ASSERT_EQUAL(7, node_count(tree->root));
    
    free(arr);
    bt_free(tree);
}

/* bt_reconstruct_from_pre_in tests */

void test_bt_reconstruct_from_pre_in_empty(void) {
    int preorder[] = {};
    int inorder[] = {};
    BinaryTree_t* tree = bt_reconstruct_from_pre_in(preorder, inorder, 0);
    
    TEST_ASSERT_NOT_NULL(tree);
    TEST_ASSERT_NULL(tree->root);
    
    bt_free(tree);
}

void test_bt_reconstruct_from_pre_in_single(void) {
    int preorder[] = {42};
    int inorder[] = {42};
    BinaryTree_t* tree = bt_reconstruct_from_pre_in(preorder, inorder, 1);
    
    TEST_ASSERT_NOT_NULL(tree);
    TEST_ASSERT_NOT_NULL(tree->root);
    TEST_ASSERT_EQUAL(42, tree->root->data);
    
    bt_free(tree);
}

void test_bt_reconstruct_from_pre_in_multiple(void) {
    int preorder[] = {0, 1, 3, 4, 2, 5, 6};
    int inorder[] = {3, 1, 4, 0, 5, 2, 6};
    BinaryTree_t* tree = bt_reconstruct_from_pre_in(preorder, inorder, 7);
    
    TEST_ASSERT_NOT_NULL(tree);
    TEST_ASSERT_EQUAL(0, tree->root->data);
    TEST_ASSERT_EQUAL(7, node_count(tree->root));
    
    bt_free(tree);
}

/* bt_reconstruct_from_post_in tests */

void test_bt_reconstruct_from_post_in_empty(void) {
    int postorder[] = {};
    int inorder[] = {};
    BinaryTree_t* tree = bt_reconstruct_from_post_in(postorder, inorder, 0);
    
    TEST_ASSERT_NOT_NULL(tree);
    TEST_ASSERT_NULL(tree->root);
    
    bt_free(tree);
}

void test_bt_reconstruct_from_post_in_single(void) {
    int postorder[] = {42};
    int inorder[] = {42};
    BinaryTree_t* tree = bt_reconstruct_from_post_in(postorder, inorder, 1);
    
    TEST_ASSERT_NOT_NULL(tree);
    TEST_ASSERT_NOT_NULL(tree->root);
    TEST_ASSERT_EQUAL(42, tree->root->data);
    
    bt_free(tree);
}

void test_bt_reconstruct_from_post_in_multiple(void) {
    int postorder[] = {3, 4, 1, 5, 6, 2, 0};
    int inorder[] = {3, 1, 4, 0, 5, 2, 6};
    BinaryTree_t* tree = bt_reconstruct_from_post_in(postorder, inorder, 7);
    
    TEST_ASSERT_NOT_NULL(tree);
    TEST_ASSERT_EQUAL(0, tree->root->data);
    TEST_ASSERT_EQUAL(7, node_count(tree->root));
    
    bt_free(tree);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_bt_create);
    RUN_TEST(test_node_create);

    RUN_TEST(test_node_free_subtree_null);
    RUN_TEST(test_node_free_subtree_single);
    RUN_TEST(test_node_free_subtree_multiple);

    RUN_TEST(test_bt_free_null);
    RUN_TEST(test_bt_free_empty);
    RUN_TEST(test_bt_free_nonnull);

    RUN_TEST(test_node_insert_left_null_parent);
    RUN_TEST(test_node_insert_left_null_child);
    RUN_TEST(test_node_insert_left_valid);
    RUN_TEST(test_node_insert_left_override);

    RUN_TEST(test_node_insert_right_null_parent);
    RUN_TEST(test_node_insert_right_null_child);
    RUN_TEST(test_node_insert_right_valid);
    RUN_TEST(test_node_insert_right_override);

    RUN_TEST(test_bt_is_empty_null);
    RUN_TEST(test_bt_is_empty_empty);
    RUN_TEST(test_bt_is_empty_single);
    RUN_TEST(test_bt_is_empty_multiple);

    RUN_TEST(test_node_is_leaf_null);
    RUN_TEST(test_node_is_leaf_single);
    RUN_TEST(test_node_is_leaf_with_left_child);
    RUN_TEST(test_node_is_leaf_with_right_child);
    RUN_TEST(test_node_is_leaf_with_both_children);

    RUN_TEST(test_node_are_equal_both_null);
    RUN_TEST(test_node_are_equal_one_null);
    RUN_TEST(test_node_are_equal_single_equal);
    RUN_TEST(test_node_are_equal_single_not_equal);
    RUN_TEST(test_node_are_equal_multiple_equal);
    RUN_TEST(test_node_are_equal_multiple_not_equal);

    RUN_TEST(test_node_height_null);
    RUN_TEST(test_node_height_single);
    RUN_TEST(test_node_height_two_levels);
    RUN_TEST(test_node_height_multiple);

    RUN_TEST(test_node_count_null);
    RUN_TEST(test_node_count_single);
    RUN_TEST(test_node_count_multiple);
    RUN_TEST(test_node_count_full_tree);

    RUN_TEST(test_node_depth_null);
    RUN_TEST(test_node_depth_root);
    RUN_TEST(test_node_depth_child);
    RUN_TEST(test_node_depth_grandchild);

    RUN_TEST(test_node_leaves_count_null);
    RUN_TEST(test_node_leaves_count_single);
    RUN_TEST(test_node_leaves_count_multiple);
    RUN_TEST(test_node_leaves_count_full_tree);

    RUN_TEST(test_node_is_descendant_null);
    RUN_TEST(test_node_is_descendant_same_node);
    RUN_TEST(test_node_is_descendant_direct_child);
    RUN_TEST(test_node_is_descendant_grandchild);
    RUN_TEST(test_node_is_descendant_not_descendant);

    RUN_TEST(test_node_is_ancestor_null);
    RUN_TEST(test_node_is_ancestor_direct_parent);
    RUN_TEST(test_node_is_ancestor_grandparent);
    RUN_TEST(test_node_is_ancestor_not_ancestor);

    RUN_TEST(test_node_get_sibling_null);
    RUN_TEST(test_node_get_sibling_root);
    RUN_TEST(test_node_get_sibling_left_child);
    RUN_TEST(test_node_get_sibling_right_child);
    RUN_TEST(test_node_get_sibling_only_left_child);

    RUN_TEST(test_node_get_uncle_null);
    RUN_TEST(test_node_get_uncle_root);
    RUN_TEST(test_node_get_uncle_child);
    RUN_TEST(test_node_get_uncle_grandchild);

    RUN_TEST(test_node_search_null);
    RUN_TEST(test_node_search_single_found);
    RUN_TEST(test_node_search_single_not_found);
    RUN_TEST(test_node_search_multiple_found);
    RUN_TEST(test_node_search_multiple_not_found);

    RUN_TEST(test_node_distance_null);
    RUN_TEST(test_node_distance_same_node);
    RUN_TEST(test_node_distance_parent_child);
    RUN_TEST(test_node_distance_siblings);
    RUN_TEST(test_node_distance_grandparent_grandchild);

    RUN_TEST(test_node_next_inorder_null);
    RUN_TEST(test_node_next_inorder_single);
    RUN_TEST(test_node_next_inorder_multiple);

    RUN_TEST(test_node_next_preorder_null);
    RUN_TEST(test_node_next_preorder_single);
    RUN_TEST(test_node_next_preorder_with_left_child);
    RUN_TEST(test_node_next_preorder_leaf);

    RUN_TEST(test_node_next_postorder_null);
    RUN_TEST(test_node_next_postorder_root);
    RUN_TEST(test_node_next_postorder_leaf);

    RUN_TEST(test_node_inorder_to_array_null);
    RUN_TEST(test_node_inorder_to_array_single);
    RUN_TEST(test_node_inorder_to_array_multiple);

    RUN_TEST(test_bt_reconstruct_from_pre_in_empty);
    RUN_TEST(test_bt_reconstruct_from_pre_in_single);
    RUN_TEST(test_bt_reconstruct_from_pre_in_multiple);

    RUN_TEST(test_bt_reconstruct_from_post_in_empty);
    RUN_TEST(test_bt_reconstruct_from_post_in_single);
    RUN_TEST(test_bt_reconstruct_from_post_in_multiple);

    return UNITY_END();
}
