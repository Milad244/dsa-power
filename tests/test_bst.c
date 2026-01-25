#include "Unity/unity.h"
#include "bst.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

// Helper that creates a BST with n items of value 0, 1, 2, ..., n - 1
static BST_t* make_bst_with_n(int n) {
    BST_t* bst = BST_create();
    for (int i = 0; i < n; i++) {
        BST_insert(bst, i);
    }
    return bst;
}

// Helper to assert the BST array matches expected sorted array
static void assert_bst_array_equals(BST_t* bst, int expected[], int n) {
    TEST_ASSERT_NOT_NULL(bst);
    int* arr = BST_to_array(bst);
    if (n == 0) {
        TEST_ASSERT_NULL(arr);
    } else {
        TEST_ASSERT_NOT_NULL(arr);
        for (int i = 0; i < n; i++) {
            TEST_ASSERT_EQUAL(expected[i], arr[i]);
        }
        free(arr);
    }
}

/* BST_create tests */

void test_bst_create(void) {
    BST_t* bst = BST_create();

    TEST_ASSERT_NOT_NULL(bst);
    TEST_ASSERT_NULL(bst->root);
    TEST_ASSERT_EQUAL(0, bst->size);

    BST_free(bst);
}

/* BST_free tests */

void test_bst_free_null(void) {
    BST_free(NULL);
}

void test_bst_free_nonnull(void) {
    BST_t* bst = make_bst_with_n(5);
    BST_free(bst);
}

/* BST_insert tests */

void test_bst_insert_null(void) {
    BST_insert(NULL, 5);
}

void test_bst_insert_empty(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 42);

    TEST_ASSERT_NOT_NULL(bst->root);
    TEST_ASSERT_EQUAL(42, bst->root->data);
    TEST_ASSERT_EQUAL(1, bst->size);

    BST_free(bst);
}

void test_bst_insert_single(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);

    TEST_ASSERT_EQUAL(50, bst->root->data);
    TEST_ASSERT_EQUAL(30, bst->root->left->data);
    TEST_ASSERT_EQUAL(2, bst->size);

    BST_free(bst);
}

void test_bst_insert_multiple(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);
    BST_insert(bst, 70);
    BST_insert(bst, 20);
    BST_insert(bst, 40);

    TEST_ASSERT_EQUAL(5, bst->size);
    TEST_ASSERT_EQUAL(50, bst->root->data);
    TEST_ASSERT_EQUAL(30, bst->root->left->data);
    TEST_ASSERT_EQUAL(70, bst->root->right->data);

    BST_free(bst);
}

void test_bst_insert_duplicate(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 42);
    BST_insert(bst, 42);

    TEST_ASSERT_EQUAL(1, bst->size);

    BST_free(bst);
}

void test_bst_insert_maintains_bst_property(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);
    BST_insert(bst, 70);
    BST_insert(bst, 20);
    BST_insert(bst, 40);
    BST_insert(bst, 60);
    BST_insert(bst, 80);

    TEST_ASSERT_TRUE(node_is_BST(bst->root));

    BST_free(bst);
}

/* BST_delete tests */

void test_bst_delete_null(void) {
    BST_delete(NULL, 5);
}

void test_bst_delete_empty(void) {
    BST_t* bst = BST_create();
    BST_delete(bst, 5);
    TEST_ASSERT_EQUAL(0, bst->size);

    BST_free(bst);
}

void test_bst_delete_not_found(void) {
    BST_t* bst = make_bst_with_n(3);
    BST_delete(bst, 99);
    TEST_ASSERT_EQUAL(3, bst->size);

    BST_free(bst);
}

void test_bst_delete_leaf(void) {
    BST_t* bst = make_bst_with_n(5);
    BST_delete(bst, 0);

    TEST_ASSERT_EQUAL(4, bst->size);
    TEST_ASSERT_NULL(BST_search(bst, 0));

    BST_free(bst);
}

void test_bst_delete_single_child_left(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);
    BST_insert(bst, 20);
    
    BST_delete(bst, 30);

    TEST_ASSERT_EQUAL(2, bst->size);
    TEST_ASSERT_EQUAL(20, bst->root->left->data);

    BST_free(bst);
}

void test_bst_delete_single_child_right(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 70);
    BST_insert(bst, 80);
    
    BST_delete(bst, 70);

    TEST_ASSERT_EQUAL(2, bst->size);
    TEST_ASSERT_EQUAL(80, bst->root->right->data);

    BST_free(bst);
}

void test_bst_delete_two_children(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);
    BST_insert(bst, 70);
    BST_insert(bst, 20);
    BST_insert(bst, 40);
    
    BST_delete(bst, 30);

    TEST_ASSERT_EQUAL(4, bst->size);
    TEST_ASSERT_NULL(BST_search(bst, 30));
    TEST_ASSERT_NOT_NULL(BST_search(bst, 20));
    TEST_ASSERT_NOT_NULL(BST_search(bst, 40));
    TEST_ASSERT_TRUE(node_is_BST(bst->root));

    BST_free(bst);
}

void test_bst_delete_root_no_child(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 42);
    BST_delete(bst, 42);

    TEST_ASSERT_EQUAL(0, bst->size);
    TEST_ASSERT_NULL(bst->root);

    BST_free(bst);
}

void test_bst_delete_root_single_child(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);
    
    BST_delete(bst, 50);

    TEST_ASSERT_EQUAL(1, bst->size);
    TEST_ASSERT_EQUAL(30, bst->root->data);
    TEST_ASSERT_NULL(bst->root->parent);

    BST_free(bst);
}

void test_bst_delete_root_two_children(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);
    BST_insert(bst, 70);
    BST_insert(bst, 20);
    BST_insert(bst, 40);
    
    BST_delete(bst, 50);

    TEST_ASSERT_EQUAL(4, bst->size);
    TEST_ASSERT_NULL(BST_search(bst, 50));
    TEST_ASSERT_TRUE(node_is_BST(bst->root));

    BST_free(bst);
}

void test_bst_delete_maintains_bst_property(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);
    BST_insert(bst, 70);
    BST_insert(bst, 20);
    BST_insert(bst, 40);
    BST_insert(bst, 60);
    BST_insert(bst, 80);
    
    BST_delete(bst, 30);
    BST_delete(bst, 70);

    TEST_ASSERT_TRUE(node_is_BST(bst->root));

    BST_free(bst);
}

/* BST_search tests */

void test_bst_search_null(void) {
    BTNode_t* result = BST_search(NULL, 5);
    TEST_ASSERT_NULL(result);
}

void test_bst_search_empty(void) {
    BST_t* bst = BST_create();
    BTNode_t* result = BST_search(bst, 5);
    TEST_ASSERT_NULL(result);

    BST_free(bst);
}

void test_bst_search_single_found(void) {
    BST_t* bst = make_bst_with_n(1);
    BTNode_t* result = BST_search(bst, 0);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(0, result->data);

    BST_free(bst);
}

void test_bst_search_single_not_found(void) {
    BST_t* bst = make_bst_with_n(1);
    BTNode_t* result = BST_search(bst, 99);
    TEST_ASSERT_NULL(result);

    BST_free(bst);
}

void test_bst_search_multiple_found(void) {
    BST_t* bst = make_bst_with_n(5);
    BTNode_t* result = BST_search(bst, 3);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(3, result->data);

    BST_free(bst);
}

void test_bst_search_multiple_not_found(void) {
    BST_t* bst = make_bst_with_n(5);
    BTNode_t* result = BST_search(bst, 100);
    TEST_ASSERT_NULL(result);

    BST_free(bst);
}

void test_bst_search_root(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);
    BST_insert(bst, 70);

    BTNode_t* result = BST_search(bst, 50);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(50, result->data);
    TEST_ASSERT_EQUAL_PTR(bst->root, result);

    BST_free(bst);
}

/* BST_find_min tests */

void test_bst_find_min_null(void) {
    int result = BST_find_min(NULL);
    TEST_ASSERT_EQUAL(-1, result);
}

void test_bst_find_min_single(void) {
    BST_t* bst = make_bst_with_n(1);
    int result = BST_find_min(bst->root);
    TEST_ASSERT_EQUAL(0, result);

    BST_free(bst);
}

void test_bst_find_min_multiple(void) {
    BST_t* bst = make_bst_with_n(5);
    int result = BST_find_min(bst->root);
    TEST_ASSERT_EQUAL(0, result);

    BST_free(bst);
}

void test_bst_find_min_unbalanced(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);
    BST_insert(bst, 70);
    BST_insert(bst, 20);
    BST_insert(bst, 10);

    int result = BST_find_min(bst->root);
    TEST_ASSERT_EQUAL(10, result);

    BST_free(bst);
}

/* BST_find_max tests */

void test_bst_find_max_null(void) {
    int result = BST_find_max(NULL);
    TEST_ASSERT_EQUAL(-1, result);
}

void test_bst_find_max_single(void) {
    BST_t* bst = make_bst_with_n(1);
    int result = BST_find_max(bst->root);
    TEST_ASSERT_EQUAL(0, result);

    BST_free(bst);
}

void test_bst_find_max_multiple(void) {
    BST_t* bst = make_bst_with_n(5);
    int result = BST_find_max(bst->root);
    TEST_ASSERT_EQUAL(4, result);

    BST_free(bst);
}

void test_bst_find_max_unbalanced(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);
    BST_insert(bst, 70);
    BST_insert(bst, 80);
    BST_insert(bst, 90);

    int result = BST_find_max(bst->root);
    TEST_ASSERT_EQUAL(90, result);

    BST_free(bst);
}

/* BST_size tests */

void test_bst_size_null(void) {
    TEST_ASSERT_EQUAL(0, BST_size(NULL));
}

void test_bst_size_empty(void) {
    BST_t* bst = BST_create();
    TEST_ASSERT_EQUAL(0, BST_size(bst));

    BST_free(bst);
}

void test_bst_size_single(void) {
    BST_t* bst = make_bst_with_n(1);
    TEST_ASSERT_EQUAL(1, BST_size(bst));

    BST_free(bst);
}

void test_bst_size_multiple(void) {
    BST_t* bst = make_bst_with_n(7);
    TEST_ASSERT_EQUAL(7, BST_size(bst));

    BST_free(bst);
}

void test_bst_size_after_insert(void) {
    BST_t* bst = BST_create();
    TEST_ASSERT_EQUAL(0, BST_size(bst));
    
    BST_insert(bst, 10);
    TEST_ASSERT_EQUAL(1, BST_size(bst));
    
    BST_insert(bst, 5);
    TEST_ASSERT_EQUAL(2, BST_size(bst));

    BST_free(bst);
}

void test_bst_size_after_delete(void) {
    BST_t* bst = make_bst_with_n(5);
    TEST_ASSERT_EQUAL(5, BST_size(bst));
    
    BST_delete(bst, 0);
    TEST_ASSERT_EQUAL(4, BST_size(bst));

    BST_free(bst);
}

/* node_is_BST tests */

void test_node_is_bst_null(void) {
    bool result = node_is_BST(NULL);
    TEST_ASSERT_FALSE(result);
}

void test_node_is_bst_single(void) {
    BST_t* bst = make_bst_with_n(1);
    bool result = node_is_BST(bst->root);
    TEST_ASSERT_TRUE(result);

    BST_free(bst);
}

void test_node_is_bst_valid_multiple(void) {
    BST_t* bst = make_bst_with_n(5);
    bool result = node_is_BST(bst->root);
    TEST_ASSERT_TRUE(result);

    BST_free(bst);
}

void test_node_is_bst_valid_complex(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);
    BST_insert(bst, 70);
    BST_insert(bst, 20);
    BST_insert(bst, 40);
    BST_insert(bst, 60);
    BST_insert(bst, 80);

    bool result = node_is_BST(bst->root);
    TEST_ASSERT_TRUE(result);

    BST_free(bst);
}

void test_node_is_bst_subtree(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);
    BST_insert(bst, 70);

    bool result = node_is_BST(bst->root->left);
    TEST_ASSERT_TRUE(result);

    BST_free(bst);
}

/* BST_to_array tests */

void test_bst_to_array_null(void) {
    int* arr = BST_to_array(NULL);
    TEST_ASSERT_NULL(arr);
}

void test_bst_to_array_empty(void) {
    BST_t* bst = BST_create();
    int* arr = BST_to_array(bst);
    TEST_ASSERT_NULL(arr);

    BST_free(bst);
}

void test_bst_to_array_single(void) {
    BST_t* bst = make_bst_with_n(1);
    int expected[] = {0};
    assert_bst_array_equals(bst, expected, 1);

    BST_free(bst);
}

void test_bst_to_array_multiple(void) {
    BST_t* bst = make_bst_with_n(5);
    int expected[] = {0, 1, 2, 3, 4};
    assert_bst_array_equals(bst, expected, 5);

    BST_free(bst);
}

void test_bst_to_array_unbalanced(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);
    BST_insert(bst, 70);
    BST_insert(bst, 20);
    BST_insert(bst, 40);
    BST_insert(bst, 60);
    BST_insert(bst, 80);

    int expected[] = {20, 30, 40, 50, 60, 70, 80};
    assert_bst_array_equals(bst, expected, 7);

    BST_free(bst);
}

void test_bst_to_array_is_sorted(void) {
    BST_t* bst = BST_create();
    BST_insert(bst, 50);
    BST_insert(bst, 30);
    BST_insert(bst, 70);
    BST_insert(bst, 20);
    BST_insert(bst, 40);

    int* arr = BST_to_array(bst);
    for (int i = 0; i < 4; i++) {
        TEST_ASSERT_LESS_OR_EQUAL(arr[i+1], arr[i]);
    }
    free(arr);

    BST_free(bst);
}

/* BST_from_preorder tests */

void test_bst_from_preorder_empty(void) {
    int preorder[] = {};
    BST_t* bst = BST_from_preorder(preorder, 0);

    TEST_ASSERT_NOT_NULL(bst);
    TEST_ASSERT_EQUAL(0, bst->size);
    TEST_ASSERT_NULL(bst->root);

    BST_free(bst);
}

void test_bst_from_preorder_single(void) {
    int preorder[] = {42};
    BST_t* bst = BST_from_preorder(preorder, 1);

    TEST_ASSERT_NOT_NULL(bst);
    TEST_ASSERT_EQUAL(1, bst->size);
    TEST_ASSERT_EQUAL(42, bst->root->data);

    BST_free(bst);
}

void test_bst_from_preorder_multiple(void) {
    int preorder[] = {50, 30, 20, 40, 70};
    BST_t* bst = BST_from_preorder(preorder, 5);

    TEST_ASSERT_NOT_NULL(bst);
    TEST_ASSERT_EQUAL(5, bst->size);
    TEST_ASSERT_EQUAL(50, bst->root->data);
    TEST_ASSERT_EQUAL(30, bst->root->left->data);
    TEST_ASSERT_EQUAL(70, bst->root->right->data);

    BST_free(bst);
}

void test_bst_from_preorder_maintains_bst_property(void) {
    int preorder[] = {50, 30, 20, 40, 70, 60, 80};
    BST_t* bst = BST_from_preorder(preorder, 7);

    TEST_ASSERT_TRUE(node_is_BST(bst->root));

    BST_free(bst);
}

void test_bst_from_preorder_converts_to_sorted_array(void) {
    int preorder[] = {50, 30, 20, 40, 70, 60, 80};
    BST_t* bst = BST_from_preorder(preorder, 7);

    int* arr = BST_to_array(bst);
    int expected[] = {20, 30, 40, 50, 60, 70, 80};
    for (int i = 0; i < 7; i++) {
        TEST_ASSERT_EQUAL(expected[i], arr[i]);
    }
    free(arr);

    BST_free(bst);
}

void test_bst_from_preorder_left_skewed(void) {
    int preorder[] = {50, 40, 30, 20, 10};
    BST_t* bst = BST_from_preorder(preorder, 5);

    TEST_ASSERT_NOT_NULL(bst);
    TEST_ASSERT_EQUAL(5, bst->size);
    TEST_ASSERT_TRUE(node_is_BST(bst->root));

    BST_free(bst);
}

void test_bst_from_preorder_right_skewed(void) {
    int preorder[] = {10, 20, 30, 40, 50};
    BST_t* bst = BST_from_preorder(preorder, 5);

    TEST_ASSERT_NOT_NULL(bst);
    TEST_ASSERT_EQUAL(5, bst->size);
    TEST_ASSERT_TRUE(node_is_BST(bst->root));

    BST_free(bst);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_bst_create);

    RUN_TEST(test_bst_free_null);
    RUN_TEST(test_bst_free_nonnull);

    RUN_TEST(test_bst_insert_null);
    RUN_TEST(test_bst_insert_empty);
    RUN_TEST(test_bst_insert_single);
    RUN_TEST(test_bst_insert_multiple);
    RUN_TEST(test_bst_insert_duplicate);
    RUN_TEST(test_bst_insert_maintains_bst_property);

    RUN_TEST(test_bst_delete_null);
    RUN_TEST(test_bst_delete_empty);
    RUN_TEST(test_bst_delete_not_found);
    RUN_TEST(test_bst_delete_leaf);
    RUN_TEST(test_bst_delete_single_child_left);
    RUN_TEST(test_bst_delete_single_child_right);
    RUN_TEST(test_bst_delete_two_children);
    RUN_TEST(test_bst_delete_root_no_child);
    RUN_TEST(test_bst_delete_root_single_child);
    RUN_TEST(test_bst_delete_root_two_children);
    RUN_TEST(test_bst_delete_maintains_bst_property);

    RUN_TEST(test_bst_search_null);
    RUN_TEST(test_bst_search_empty);
    RUN_TEST(test_bst_search_single_found);
    RUN_TEST(test_bst_search_single_not_found);
    RUN_TEST(test_bst_search_multiple_found);
    RUN_TEST(test_bst_search_multiple_not_found);
    RUN_TEST(test_bst_search_root);

    RUN_TEST(test_bst_find_min_null);
    RUN_TEST(test_bst_find_min_single);
    RUN_TEST(test_bst_find_min_multiple);
    RUN_TEST(test_bst_find_min_unbalanced);

    RUN_TEST(test_bst_find_max_null);
    RUN_TEST(test_bst_find_max_single);
    RUN_TEST(test_bst_find_max_multiple);
    RUN_TEST(test_bst_find_max_unbalanced);

    RUN_TEST(test_bst_size_null);
    RUN_TEST(test_bst_size_empty);
    RUN_TEST(test_bst_size_single);
    RUN_TEST(test_bst_size_multiple);
    RUN_TEST(test_bst_size_after_insert);
    RUN_TEST(test_bst_size_after_delete);

    RUN_TEST(test_node_is_bst_null);
    RUN_TEST(test_node_is_bst_single);
    RUN_TEST(test_node_is_bst_valid_multiple);
    RUN_TEST(test_node_is_bst_valid_complex);
    RUN_TEST(test_node_is_bst_subtree);

    RUN_TEST(test_bst_to_array_null);
    RUN_TEST(test_bst_to_array_empty);
    RUN_TEST(test_bst_to_array_single);
    RUN_TEST(test_bst_to_array_multiple);
    RUN_TEST(test_bst_to_array_unbalanced);
    RUN_TEST(test_bst_to_array_is_sorted);

    RUN_TEST(test_bst_from_preorder_empty);
    RUN_TEST(test_bst_from_preorder_single);
    RUN_TEST(test_bst_from_preorder_multiple);
    RUN_TEST(test_bst_from_preorder_maintains_bst_property);
    RUN_TEST(test_bst_from_preorder_converts_to_sorted_array);
    RUN_TEST(test_bst_from_preorder_left_skewed);
    RUN_TEST(test_bst_from_preorder_right_skewed);

    return UNITY_END();
}
