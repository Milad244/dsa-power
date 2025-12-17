#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "linked_list.h"

// makes list with n items of value 0, 1, 2, ..., n - 1
static LL_t* make_list_with_n(int n) {
    LL_t* list = LL_create();
    for (int i = 0; i < n; i++) {
        LL_add_to_tail(list, i);
    }
    return list;
}

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

// Helper to assert the list matches an expected array
static void assert_list_equals(LL_t* list, int expected[], int n) {
    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    node_t* curr = list->head;
    for (int i = 0; i < n; i++) {
        CU_ASSERT_PTR_NOT_NULL_FATAL(curr);
        CU_ASSERT_EQUAL(curr->data, expected[i]);
        if (i == n - 1) { // last item
            CU_ASSERT_PTR_EQUAL(curr, list->tail);
            CU_ASSERT_PTR_NULL(curr->next);
        }
        curr = curr->next;
    }
    CU_ASSERT_PTR_NULL(curr); // needed for n = 0, list > 0 edge case
}

/* LL_Create tests */

void test_create(void) {
    LL_t* list = make_list_with_n(0);

    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT_PTR_NULL(list->head);
    CU_ASSERT_PTR_NULL(list->tail);

    LL_free(list);
}

/* LL_clear tests */

void test_clear(void) {
    LL_t* list = make_list_with_n(5);
    LL_clear(list);
    CU_ASSERT_PTR_NOT_NULL(list);
    CU_ASSERT_PTR_NULL(list->head);
    CU_ASSERT_PTR_NULL(list->tail);

    LL_free(list);
}

/* LL_free tests */

void test_free_null(void) {
    LL_free(NULL);
}

void test_free_nonnull(void) {
    LL_t* list = make_list_with_n(3);
    LL_free(list);
}

/* LL_add_to_head tests */

void test_add_to_head_null(void) {
    LL_t* null_list = NULL;
    LL_add_to_head(null_list, 5);

    LL_free(null_list);
}

void test_add_to_head_empty(void) {
    LL_t* list = make_list_with_n(0);
    LL_add_to_head(list, -8);

    int expected[] = {-8};
    assert_list_equals(list, expected, 1);

    LL_free(list);
}

void test_add_to_head_non_empty(void) {
    LL_t* three = make_list_with_n(0);
    LL_add_to_head(three, -3);
    LL_add_to_head(three, 0);
    LL_add_to_head(three, 3);

    int expected[] = {3, 0, -3};
    assert_list_equals(three, expected, 3);

    LL_free(three);
}

/* LL_add_to_tail tests */

void test_add_to_tail_null(void) {
    LL_t* null_list = NULL;
    LL_add_to_tail(null_list, 5);

    LL_free(null_list);
}

void test_add_to_tail_empty(void) {
    LL_t* list = make_list_with_n(0);
    LL_add_to_tail(list, 1234);

    int expected[] = {1234};
    assert_list_equals(list, expected, 1);

    LL_free(list);
}

void test_add_to_tail_non_empty(void) {
    LL_t* four = make_list_with_n(0);
    LL_add_to_tail(four, 0);
    LL_add_to_tail(four, 99);
    LL_add_to_tail(four, -123);
    LL_add_to_tail(four, 1);

    int expected[] = {0, 99, -123, 1};
    assert_list_equals(four, expected, 4);

    LL_free(four);
}

/* LL_remove_from_head tests */

void test_remove_from_head_null(void) {
    LL_t* null_list = NULL;
    LL_remove_from_head(null_list);

    LL_free(null_list);
}

void test_remove_from_head_empty(void) {
    LL_t* empty = make_list_with_n(0);
    LL_remove_from_head(empty);

    int expected[] = {};
    assert_list_equals(empty, expected, 0);

    LL_free(empty);
}

void test_remove_from_head_single(void) {
    LL_t* list = make_list_with_n(1);
    LL_remove_from_head(list);

    CU_ASSERT_PTR_NULL(list->head);
    CU_ASSERT_PTR_NULL(list->tail);

    LL_free(list);
}

void test_remove_from_head_multiple(void) {
    LL_t* list = make_list_with_n(8);
    LL_remove_from_head(list);

    int expected[] = {1, 2, 3, 4, 5, 6, 7};
    assert_list_equals(list, expected, 7);

    LL_free(list);
}

/* LL_remove_from_tail tests */

void test_remove_from_tail_null(void) {
    LL_t* null_list = NULL;
    LL_remove_from_tail(null_list);

    LL_free(null_list);
}

void test_remove_from_tail_empty(void) {
    LL_t* empty = make_list_with_n(0);
    LL_remove_from_tail(empty);

    int expected[] = {};
    assert_list_equals(empty, expected, 0);

    LL_free(empty);
}

void test_remove_from_tail_single(void) {
    LL_t* list = make_list_with_n(1);
    LL_remove_from_tail(list);

    CU_ASSERT_PTR_NULL(list->head);
    CU_ASSERT_PTR_NULL(list->tail);

    LL_free(list);
}

void test_remove_from_tail_multiple(void) {
    LL_t* list = make_list_with_n(5);
    LL_remove_from_tail(list);

    int expected[] = {0, 1, 2, 3};
    assert_list_equals(list, expected, 4);

    LL_free(list);
}

/* LL_get_size tests */

void test_get_size_null(void) {
    LL_t* null_list = NULL;
    CU_ASSERT_EQUAL(LL_get_size(null_list), 0);

    LL_free(null_list);
}

void test_get_size_empty(void) {
    LL_t* empty = make_list_with_n(0);
    CU_ASSERT_EQUAL(LL_get_size(empty), 0);

    LL_free(empty);
}

void test_get_size_single(void) {
    LL_t* list = make_list_with_n(1);
    CU_ASSERT_EQUAL(LL_get_size(list), 1);

    LL_free(list);
}

void test_get_size_multiple(void) {
    LL_t* list = make_list_with_n(10);
    CU_ASSERT_EQUAL(LL_get_size(list), 10);

    LL_free(list);
}

/* LL_is_empty tests */

void test_is_empty_null(void) {
    LL_t* null_list = NULL;
    CU_ASSERT_TRUE(LL_is_empty(null_list));

    LL_free(null_list);
}

void test_is_empty_empty(void) {
    LL_t* empty = make_list_with_n(0);
    CU_ASSERT_TRUE(LL_is_empty(empty));

    LL_free(empty);
}

void test_is_empty_single(void) {
    LL_t* list = make_list_with_n(1);
    CU_ASSERT_FALSE(LL_is_empty(list));

    LL_free(list);
}

void test_is_empty_multiple(void) {
    LL_t* list = make_list_with_n(6);
    CU_ASSERT_FALSE(LL_is_empty(list));

    LL_free(list);
}

/* LL_are_equal tests */

void test_are_equal_both_null(void) {
    LL_t* list1 = NULL;
    LL_t* list2 = NULL;
    CU_ASSERT_TRUE(LL_are_equal(list1, list2));

    LL_free(list1);
    LL_free(list2);
}

void test_are_equal_one_null(void) {
    LL_t* list1 = make_list_with_n(3);
    LL_t* list2 = NULL;
    CU_ASSERT_FALSE(LL_are_equal(list1, list2));

    LL_free(list1);
    LL_free(list2);

    list1 = NULL;
    list2 = make_list_with_n(0);
    CU_ASSERT_FALSE(LL_are_equal(list1, list2));

    LL_free(list1);
    LL_free(list2);
}

void test_are_equal_empty_lists(void) {
    LL_t* list1 = make_list_with_n(0);
    LL_t* list2 = make_list_with_n(0);
    CU_ASSERT_TRUE(LL_are_equal(list1, list2));

    LL_free(list1);
    LL_free(list2);
}

void test_are_equal_same_elements(void) {
    LL_t* list1 = make_list_with_n(5);
    LL_t* list2 = make_list_with_n(5);
    CU_ASSERT_TRUE(LL_are_equal(list1, list2));

    LL_free(list1);
    LL_free(list2);
}

void test_are_equal_different_sizes(void) {
    LL_t* list1 = make_list_with_n(5);
    LL_t* list2 = make_list_with_n(3);
    CU_ASSERT_FALSE(LL_are_equal(list1, list2));

    LL_free(list1);
    LL_free(list2);
}

void test_are_equal_different_elements(void) {
    LL_t* list1 = make_list_with_n(5);
    LL_t* list2 = make_list_with_n(5);
    list2->head->data = 999;
    CU_ASSERT_FALSE(LL_are_equal(list1, list2));

    LL_free(list1);
    LL_free(list2);
}

/* LL_index_of tests */

void test_index_of_null(void) {
    LL_t* null_list = NULL;
    CU_ASSERT_EQUAL(LL_index_of(null_list, 5), -1);

    LL_free(null_list);
}

void test_index_of_empty(void) {
    LL_t* empty = make_list_with_n(0);
    CU_ASSERT_EQUAL(LL_index_of(empty, 5), -1);

    LL_free(empty);
}

void test_index_of_single_found(void) {
    LL_t* list = make_list_with_n(1);
    list->head->data = 42;
    CU_ASSERT_EQUAL(LL_index_of(list, 42), 0);

    LL_free(list);
}

void test_index_of_single_not_found(void) {
    LL_t* list = make_list_with_n(1);
    CU_ASSERT_EQUAL(LL_index_of(list, 99), -1);

    LL_free(list);
}

void test_index_of_multiple_found(void) {
    LL_t* list = make_list_with_n(5);
    list->head->next->data = 99; // second element
    CU_ASSERT_EQUAL(LL_index_of(list, 99), 1);

    LL_free(list);
}

void test_index_of_multiple_not_found(void) {
    LL_t* list = make_list_with_n(5);
    CU_ASSERT_EQUAL(LL_index_of(list, 1000), -1);

    LL_free(list);
}

/* LL_get_item tests */
void test_get_item_null(void) {
    LL_t* null_list = NULL;
    CU_ASSERT_PTR_NULL(LL_get_item(null_list, 0));

    LL_free(null_list);
}

void test_get_item_empty(void) {
    LL_t* empty = make_list_with_n(0);
    CU_ASSERT_PTR_NULL(LL_get_item(empty, 0));

    LL_free(empty);
}

void test_get_item_single_valid(void) {
    LL_t* list = make_list_with_n(1);
    list->head->data = 42;
    CU_ASSERT_EQUAL(LL_get_item(list, 0)->data, 42);

    LL_free(list);
}

void test_get_item_single_invalid(void) {
    LL_t* list = make_list_with_n(1);
    CU_ASSERT_PTR_NULL(LL_get_item(list, 1));

    LL_free(list);
}

void test_get_item_multiple_valid(void) {
    LL_t* list = make_list_with_n(5);
    list->head->next->next->data = 99; // third element
    CU_ASSERT_EQUAL(LL_get_item(list, 2)->data, 99);

    LL_free(list);
}

void test_get_item_multiple_invalid(void) {
    LL_t* list = make_list_with_n(5);
    CU_ASSERT_PTR_NULL(LL_get_item(list, 10));

    LL_free(list);
}

/* LL_get_middle tests */

void test_get_middle_null(void) {
    LL_t* null_list = NULL;
    CU_ASSERT_PTR_NULL(LL_get_middle(null_list));

    LL_free(null_list);
}

void test_get_middle_empty(void) {
    LL_t* empty = make_list_with_n(0);
    CU_ASSERT_PTR_NULL(LL_get_middle(empty));

    LL_free(empty);
}

void test_get_middle_single(void) {
    LL_t* list = make_list_with_n(1);
    list->head->data = 42;
    CU_ASSERT_EQUAL(LL_get_middle(list)->data, 42);

    LL_free(list);
}

void test_get_middle_even(void) {
    LL_t* list = make_list_with_n(4);
    list->head->next->next->data = 99; // index 2
    CU_ASSERT_EQUAL(LL_get_middle(list)->data, 99);

    LL_free(list);
}

void test_get_middle_odd(void) {
    LL_t* list = make_list_with_n(5);
    list->head->next->next->data = 77; // index 2
    CU_ASSERT_EQUAL(LL_get_middle(list)->data, 77);

    LL_free(list);
}

/* LL_map tests */

// Helper function to test map
static int square(int x) {
    return x * x;
}

void test_map_null(void) {
    LL_t* null_list = NULL;
    LL_map(null_list, square);
    CU_ASSERT_PTR_NULL(null_list);

    LL_free(null_list);
}

void test_map_null_function(void) {
    LL_t* list = make_list_with_n(3);
    LL_map(list, NULL);
    int expected[] = {0, 1, 2};
    assert_list_equals(list, expected, 3);

    LL_free(list);
}

void test_map_empty(void) {
    LL_t* empty = make_list_with_n(0);
    LL_map(empty, square);
    int expected[] = {};
    assert_list_equals(empty, expected, 0);

    LL_free(empty);
}

void test_map_single(void) {
    LL_t* list = make_list_with_n(1);
    LL_map(list, square);
    int expected[] = {0};
    assert_list_equals(list, expected, 1);

    LL_free(list);
}

void test_map_multiple(void) {
    int n = 5;
    LL_t* list = make_list_with_n(n);
    LL_map(list, square);
    int expected[] = {0, 1, 4, 9, 16};
    assert_list_equals(list, expected, n);

    LL_free(list);
}

/* LL_reverse tests */

void test_reverse_null(void) {
    LL_t* null_list = NULL;
    LL_reverse(null_list);
    CU_ASSERT_PTR_NULL(null_list);

    LL_free(null_list);
}

void test_reverse_empty(void) {
    LL_t* empty = make_list_with_n(0);
    LL_reverse(empty);
    int expected[] = {};
    assert_list_equals(empty, expected, 0);

    LL_free(empty);
}

void test_reverse_single(void) {
    LL_t* list = make_list_with_n(1);
    LL_reverse(list);
    int expected[] = {0};
    assert_list_equals(list, expected, 1);

    LL_free(list);
}

void test_reverse_multiple(void) {
    int n = 5;
    LL_t* list = make_list_with_n(n);
    LL_reverse(list);
    int expected[] = {4, 3, 2, 1, 0};
    assert_list_equals(list, expected, n);

    LL_free(list);
}

int main(void) {
    /* Initialize CUnit test registry */
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    /* Add a suite to the registry */
    CU_pSuite suite = CU_add_suite("Linked_List_Suite", init_suite, clean_suite);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add tests to the suite */
    CU_add_test(suite, "test_create", test_create);
    CU_add_test(suite, "test_clear", test_clear);
    CU_add_test(suite, "test_free_null", test_free_null);
    CU_add_test(suite, "test_free_nonnull", test_free_nonnull);

    CU_add_test(suite, "test_add_to_head_null", test_add_to_head_null);
    CU_add_test(suite, "test_add_to_head_empty", test_add_to_head_empty);
    CU_add_test(suite, "test_add_to_head_non_empty", test_add_to_head_non_empty);

    CU_add_test(suite, "test_add_to_tail_null", test_add_to_tail_null);
    CU_add_test(suite, "test_add_to_tail_empty", test_add_to_tail_empty);
    CU_add_test(suite, "test_add_to_tail_non_empty", test_add_to_tail_non_empty);

    CU_add_test(suite, "test_remove_from_head_null", test_remove_from_head_null);
    CU_add_test(suite, "test_remove_from_head_empty", test_remove_from_head_empty);
    CU_add_test(suite, "test_remove_from_head_single", test_remove_from_head_single);
    CU_add_test(suite, "test_remove_from_head_multiple", test_remove_from_head_multiple);

    CU_add_test(suite, "test_remove_from_tail_null", test_remove_from_tail_null);
    CU_add_test(suite, "test_remove_from_tail_empty", test_remove_from_tail_empty);
    CU_add_test(suite, "test_remove_from_tail_single", test_remove_from_tail_single);
    CU_add_test(suite, "test_remove_from_tail_multiple", test_remove_from_tail_multiple);

    CU_add_test(suite, "test_get_size_null", test_get_size_null);
    CU_add_test(suite, "test_get_size_empty", test_get_size_empty);
    CU_add_test(suite, "test_get_size_single", test_get_size_single);
    CU_add_test(suite, "test_get_size_multiple", test_get_size_multiple);

    CU_add_test(suite, "test_is_empty_null", test_is_empty_null);
    CU_add_test(suite, "test_is_empty_empty", test_is_empty_empty);
    CU_add_test(suite, "test_is_empty_single", test_is_empty_single);
    CU_add_test(suite, "test_is_empty_multiple", test_is_empty_multiple);

    CU_add_test(suite, "test_are_equal_both_null", test_are_equal_both_null);
    CU_add_test(suite, "test_are_equal_one_null", test_are_equal_one_null);
    CU_add_test(suite, "test_are_equal_empty_lists", test_are_equal_empty_lists);
    CU_add_test(suite, "test_are_equal_same_elements", test_are_equal_same_elements);
    CU_add_test(suite, "test_are_equal_different_sizes", test_are_equal_different_sizes);
    CU_add_test(suite, "test_are_equal_different_elements", test_are_equal_different_elements);

    CU_add_test(suite, "test_index_of_null", test_index_of_null);
    CU_add_test(suite, "test_index_of_empty", test_index_of_empty);
    CU_add_test(suite, "test_index_of_single_found", test_index_of_single_found);
    CU_add_test(suite, "test_index_of_single_not_found", test_index_of_single_not_found);
    CU_add_test(suite, "test_index_of_multiple_found", test_index_of_multiple_found);
    CU_add_test(suite, "test_index_of_multiple_not_found", test_index_of_multiple_not_found);

    CU_add_test(suite, "test_get_item_null", test_get_item_null);
    CU_add_test(suite, "test_get_item_empty", test_get_item_empty);
    CU_add_test(suite, "test_get_item_single_valid", test_get_item_single_valid);
    CU_add_test(suite, "test_get_item_single_invalid", test_get_item_single_invalid);
    CU_add_test(suite, "test_get_item_multiple_valid", test_get_item_multiple_valid);
    CU_add_test(suite, "test_get_item_multiple_invalid", test_get_item_multiple_invalid);

    CU_add_test(suite, "test_get_middle_null", test_get_middle_null);
    CU_add_test(suite, "test_get_middle_empty", test_get_middle_empty);
    CU_add_test(suite, "test_get_middle_single", test_get_middle_single);
    CU_add_test(suite, "test_get_middle_even", test_get_middle_even);
    CU_add_test(suite, "test_get_middle_odd", test_get_middle_odd);

    CU_add_test(suite, "test_map_null", test_map_null);
    CU_add_test(suite, "test_map_null_function", test_map_null_function);
    CU_add_test(suite, "test_map_empty", test_map_empty);
    CU_add_test(suite, "test_map_single", test_map_single);
    CU_add_test(suite, "test_map_multiple", test_map_multiple);

    CU_add_test(suite, "test_reverse_null", test_reverse_null);
    CU_add_test(suite, "test_reverse_empty", test_reverse_empty);
    CU_add_test(suite, "test_reverse_single", test_reverse_single);
    CU_add_test(suite, "test_reverse_multiple", test_reverse_multiple);

    /* Run the tests */
    CU_basic_run_tests();

    /* Clean up the registry */
    CU_cleanup_registry();
    return CU_get_error();
}