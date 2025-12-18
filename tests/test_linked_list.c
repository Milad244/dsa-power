#include "Unity/unity.h"
#include "../include/linked_list.h"

void setUp(void) {}
void tearDown(void) {}

// Helper that makes list with n items of value 0, 1, 2, ..., n - 1
static LL_t* make_list_with_n(int n) {
    LL_t* list = LL_create();
    for (int i = 0; i < n; i++) {
        LL_add_to_tail(list, i);
    }
    return list;
}

// Helper to assert the list matches an expected array
static void assert_list_equals(LL_t* list, int expected[], int n) {
    TEST_ASSERT_NOT_NULL(list);
    node_t* curr = list->head;
    for (int i = 0; i < n; i++) {
        TEST_ASSERT_NOT_NULL(curr);
        TEST_ASSERT_EQUAL(expected[i], curr->data);
        if (i == n - 1) {
            TEST_ASSERT_EQUAL_PTR(curr, list->tail);
            TEST_ASSERT_NULL(curr->next);
        }
        curr = curr->next;
    }
    TEST_ASSERT_NULL(curr); // needed for n = 0, list > 0 edge case
}

/* LL_Create tests */

void test_create(void) {
    LL_t* list = make_list_with_n(0);

    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);

    LL_free(list);
}

/* LL_clear tests */

void test_clear(void) {
    LL_t* list = make_list_with_n(5);
    LL_clear(list);

    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);

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
    int val = LL_remove_from_head(null_list);
    TEST_ASSERT_EQUAL(-1, val);
}

void test_remove_from_head_empty(void) {
    LL_t* empty = make_list_with_n(0);
    int val = LL_remove_from_head(empty);
    TEST_ASSERT_EQUAL(-1, val);

    int expected[] = {};
    assert_list_equals(empty, expected, 0);

    LL_free(empty);
}

void test_remove_from_head_single(void) {
    LL_t* list = make_list_with_n(1);
    int val = LL_remove_from_head(list);
    TEST_ASSERT_EQUAL(0, val);

    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);

    LL_free(list);
}

void test_remove_from_head_multiple(void) {
    LL_t* list = make_list_with_n(8);
    int val = LL_remove_from_head(list);
    TEST_ASSERT_EQUAL(0, val);

    int expected[] = {1, 2, 3, 4, 5, 6, 7};
    assert_list_equals(list, expected, 7);

    LL_free(list);
}

/* LL_remove_from_tail tests */

void test_remove_from_tail_null(void) {
    LL_t* null_list = NULL;
    int val = LL_remove_from_tail(null_list);
    TEST_ASSERT_EQUAL(-1, val);
}

void test_remove_from_tail_empty(void) {
    LL_t* empty = make_list_with_n(0);
    int val = LL_remove_from_tail(empty);
    TEST_ASSERT_EQUAL(-1, val);

    int expected[] = {};
    assert_list_equals(empty, expected, 0);

    LL_free(empty);
}

void test_remove_from_tail_single(void) {
    LL_t* list = make_list_with_n(1);
    int val = LL_remove_from_tail(list);
    TEST_ASSERT_EQUAL(0, val);

    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);

    LL_free(list);
}

void test_remove_from_tail_multiple(void) {
    LL_t* list = make_list_with_n(5);
    int val = LL_remove_from_tail(list);
    TEST_ASSERT_EQUAL(4, val);

    int expected[] = {0, 1, 2, 3};
    assert_list_equals(list, expected, 4);

    LL_free(list);
}

/* LL_get_size tests */

void test_get_size_null(void) {
    LL_t* null_list = NULL;
    TEST_ASSERT_EQUAL(0, LL_get_size(null_list));
}

void test_get_size_empty(void) {
    LL_t* empty = make_list_with_n(0);
    TEST_ASSERT_EQUAL(0, LL_get_size(empty));
    LL_free(empty);
}

void test_get_size_single(void) {
    LL_t* list = make_list_with_n(1);
    TEST_ASSERT_EQUAL(1, LL_get_size(list));
    LL_free(list);
}

void test_get_size_multiple(void) {
    LL_t* list = make_list_with_n(10);
    TEST_ASSERT_EQUAL(10, LL_get_size(list));
    LL_free(list);
}

/* LL_is_empty tests */

void test_is_empty_null(void) {
    LL_t* null_list = NULL;
    TEST_ASSERT_TRUE(LL_is_empty(null_list));
}

void test_is_empty_empty(void) {
    LL_t* empty = make_list_with_n(0);
    TEST_ASSERT_TRUE(LL_is_empty(empty));
    LL_free(empty);
}

void test_is_empty_single(void) {
    LL_t* list = make_list_with_n(1);
    TEST_ASSERT_FALSE(LL_is_empty(list));
    LL_free(list);
}

void test_is_empty_multiple(void) {
    LL_t* list = make_list_with_n(6);
    TEST_ASSERT_FALSE(LL_is_empty(list));
    LL_free(list);
}

/* LL_are_equal tests */

void test_are_equal_both_null(void) {
    LL_t* list1 = NULL;
    LL_t* list2 = NULL;
    TEST_ASSERT_TRUE(LL_are_equal(list1, list2));
}

void test_are_equal_one_null(void) {
    LL_t* list1 = make_list_with_n(3);
    LL_t* list2 = NULL;
    TEST_ASSERT_FALSE(LL_are_equal(list1, list2));

    LL_free(list1);
    LL_free(list2);

    list1 = NULL;
    list2 = make_list_with_n(0);
    TEST_ASSERT_FALSE(LL_are_equal(list1, list2));

    LL_free(list1);
    LL_free(list2);
}

void test_are_equal_empty_lists(void) {
    LL_t* list1 = make_list_with_n(0);
    LL_t* list2 = make_list_with_n(0);
    TEST_ASSERT_TRUE(LL_are_equal(list1, list2));

    LL_free(list1);
    LL_free(list2);
}

void test_are_equal_same_elements(void) {
    LL_t* list1 = make_list_with_n(5);
    LL_t* list2 = make_list_with_n(5);
    TEST_ASSERT_TRUE(LL_are_equal(list1, list2));

    LL_free(list1);
    LL_free(list2);
}

void test_are_equal_different_sizes(void) {
    LL_t* list1 = make_list_with_n(5);
    LL_t* list2 = make_list_with_n(3);
    TEST_ASSERT_FALSE(LL_are_equal(list1, list2));

    LL_free(list1);
    LL_free(list2);
}

void test_are_equal_different_elements(void) {
    LL_t* list1 = make_list_with_n(5);
    LL_t* list2 = make_list_with_n(5);
    list2->head->data = 999;
    TEST_ASSERT_FALSE(LL_are_equal(list1, list2));

    LL_free(list1);
    LL_free(list2);
}

/* LL_index_of tests */

void test_index_of_null(void) {
    LL_t* null_list = NULL;
    TEST_ASSERT_EQUAL(-1, LL_index_of(null_list, 5));
}

void test_index_of_empty(void) {
    LL_t* empty = make_list_with_n(0);
    TEST_ASSERT_EQUAL(-1, LL_index_of(empty, 5));

    LL_free(empty);
}

void test_index_of_single_found(void) {
    LL_t* list = make_list_with_n(1);
    list->head->data = 42;
    TEST_ASSERT_EQUAL(0, LL_index_of(list, 42));

    LL_free(list);
}

void test_index_of_single_not_found(void) {
    LL_t* list = make_list_with_n(1);
    TEST_ASSERT_EQUAL(-1, LL_index_of(list, 99));

    LL_free(list);
}

void test_index_of_multiple_found(void) {
    LL_t* list = make_list_with_n(5);
    list->head->data = 99; // first element
    list->head->next->next->data = 99; // third element
    TEST_ASSERT_EQUAL(0, LL_index_of(list, 99)); // first occurrence

    LL_free(list);
}

void test_index_of_multiple_not_found(void) {
    LL_t* list = make_list_with_n(5);
    TEST_ASSERT_EQUAL(-1, LL_index_of(list, 1000));

    LL_free(list);
}

/* LL_get_item tests */
void test_get_item_null(void) {
    LL_t* null_list = NULL;
    TEST_ASSERT_NULL(LL_get_item(null_list, 0));
}

void test_get_item_empty(void) {
    LL_t* empty = make_list_with_n(0);
    TEST_ASSERT_NULL(LL_get_item(empty, 0));

    LL_free(empty);
}

void test_get_item_single_valid(void) {
    LL_t* list = make_list_with_n(1);
    list->head->data = 42;
    TEST_ASSERT_EQUAL(42, LL_get_item(list, 0)->data);

    LL_free(list);
}

void test_get_item_single_invalid(void) {
    LL_t* list = make_list_with_n(1);
    TEST_ASSERT_NULL(LL_get_item(list, 1));

    LL_free(list);
}

void test_get_item_multiple_valid(void) {
    LL_t* list = make_list_with_n(5);
    list->head->next->next->data = 99; // third element
    TEST_ASSERT_EQUAL(99, LL_get_item(list, 2)->data);

    LL_free(list);
}

void test_get_item_multiple_invalid(void) {
    LL_t* list = make_list_with_n(5);
    TEST_ASSERT_NULL(LL_get_item(list, 10));

    LL_free(list);
}

/* LL_get_middle tests */

void test_get_middle_null(void) {
    LL_t* null_list = NULL;
    TEST_ASSERT_NULL(LL_get_middle(null_list));
}

void test_get_middle_empty(void) {
    LL_t* empty = make_list_with_n(0);
    TEST_ASSERT_NULL(LL_get_middle(empty));

    LL_free(empty);
}

void test_get_middle_single(void) {
    LL_t* list = make_list_with_n(1);
    list->head->data = 42;
    TEST_ASSERT_EQUAL(42, LL_get_middle(list)->data);

    LL_free(list);
}

void test_get_middle_even(void) {
    LL_t* list = make_list_with_n(4);
    list->head->next->next->data = 99; // index 2
    TEST_ASSERT_EQUAL(99, LL_get_middle(list)->data);

    LL_free(list);
}

void test_get_middle_odd(void) {
    LL_t* list = make_list_with_n(5);
    list->head->next->next->data = 77; // index 2
    TEST_ASSERT_EQUAL(77, LL_get_middle(list)->data);

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
    TEST_ASSERT_NULL(null_list);
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
    list->head->data = 3;
    LL_map(list, square);
    int expected[] = {9};
    assert_list_equals(list, expected, 1);

    LL_free(list);
}

void test_map_multiple(void) {
    LL_t* list = make_list_with_n(5);
    LL_map(list, square);
    int expected[] = {0, 1, 4, 9, 16};
    assert_list_equals(list, expected, 5);

    LL_free(list);
}

/* LL_reverse tests */

void test_reverse_null(void) {
    LL_t* null_list = NULL;
    LL_reverse(null_list);
    TEST_ASSERT_NULL(null_list);
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
    LL_t* list = make_list_with_n(5);
    LL_reverse(list);
    int expected[] = {4, 3, 2, 1, 0};
    assert_list_equals(list, expected, 5);

    LL_free(list);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_create);
    RUN_TEST(test_clear);
    RUN_TEST(test_free_null);
    RUN_TEST(test_free_nonnull);

    RUN_TEST(test_add_to_head_null);
    RUN_TEST(test_add_to_head_empty);
    RUN_TEST(test_add_to_head_non_empty);

    RUN_TEST(test_add_to_tail_null);
    RUN_TEST(test_add_to_tail_empty);
    RUN_TEST(test_add_to_tail_non_empty);

    RUN_TEST(test_remove_from_head_null);
    RUN_TEST(test_remove_from_head_empty);
    RUN_TEST(test_remove_from_head_single);
    RUN_TEST(test_remove_from_head_multiple);

    RUN_TEST(test_remove_from_tail_null);
    RUN_TEST(test_remove_from_tail_empty);
    RUN_TEST(test_remove_from_tail_single);
    RUN_TEST(test_remove_from_tail_multiple);

    RUN_TEST(test_get_size_null);
    RUN_TEST(test_get_size_empty);
    RUN_TEST(test_get_size_single);
    RUN_TEST(test_get_size_multiple);

    RUN_TEST(test_is_empty_null);
    RUN_TEST(test_is_empty_empty);
    RUN_TEST(test_is_empty_single);
    RUN_TEST(test_is_empty_multiple);

    RUN_TEST(test_are_equal_both_null);
    RUN_TEST(test_are_equal_one_null);
    RUN_TEST(test_are_equal_empty_lists);
    RUN_TEST(test_are_equal_same_elements);
    RUN_TEST(test_are_equal_different_sizes);
    RUN_TEST(test_are_equal_different_elements);

    RUN_TEST(test_index_of_null);
    RUN_TEST(test_index_of_empty);
    RUN_TEST(test_index_of_single_found);
    RUN_TEST(test_index_of_single_not_found);
    RUN_TEST(test_index_of_multiple_found);
    RUN_TEST(test_index_of_multiple_not_found);

    RUN_TEST(test_get_item_null);
    RUN_TEST(test_get_item_empty);
    RUN_TEST(test_get_item_single_valid);
    RUN_TEST(test_get_item_single_invalid);
    RUN_TEST(test_get_item_multiple_valid);
    RUN_TEST(test_get_item_multiple_invalid);

    RUN_TEST(test_get_middle_null);
    RUN_TEST(test_get_middle_empty);
    RUN_TEST(test_get_middle_single);
    RUN_TEST(test_get_middle_even);
    RUN_TEST(test_get_middle_odd);

    RUN_TEST(test_map_null);
    RUN_TEST(test_map_null_function);
    RUN_TEST(test_map_empty);
    RUN_TEST(test_map_single);
    RUN_TEST(test_map_multiple);

    RUN_TEST(test_reverse_null);
    RUN_TEST(test_reverse_empty);
    RUN_TEST(test_reverse_single);
    RUN_TEST(test_reverse_multiple);

    return UNITY_END();
}
