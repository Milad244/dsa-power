#include "Unity/unity.h"
#include "../include/doubly_linked_list.h"

void setUp(void) {}
void tearDown(void) {}

// Helper that makes list with n items of value 0, 1, 2, ..., n - 1
DLL_t* make_list_with_n(int n) {
    DLL_t* list = DLL_create();
    for (int i = 0; i < n; i++) {
        DLL_add_to_end(list, i);
    }
    return list;
}

// Helper to assert the list matches an expected array
void assert_list_equals(DLL_t* list, int expected[], int n) {
    TEST_ASSERT_NOT_NULL(list);
    dnode_t* curr = list->head;
    for (int i = 0; i < n; i++) {
        TEST_ASSERT_NOT_NULL(curr);
        TEST_ASSERT_EQUAL(curr->data, expected[i]);
        if (i == n - 1) {
            TEST_ASSERT_EQUAL_PTR(curr, list->tail);
        }
        curr = curr->next;
    }
    TEST_ASSERT_NULL(curr);
}

/* DLL_create tests */

void test_create(void) {
    DLL_t* list = make_list_with_n(0);

    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);

    DLL_free(list);
}

/* DLL_clear tests */

void test_clear_null(void) {
    DLL_clear(NULL);
}

void test_clear_nonnull(void) {
    DLL_t* list = make_list_with_n(4);
    DLL_clear(list);

    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);

    DLL_free(list);
}

/* DLL_free tests */

void test_free_null(void) {
    DLL_free(NULL);
}

void test_free_nonnull(void) {
    DLL_t* list = make_list_with_n(6);
    DLL_free(list);
}

/* DLL_add_to_front tests */

void test_add_to_front_null(void) {
    DLL_add_to_front(NULL, 6);
}

void test_add_to_front_empty(void) {
    DLL_t* list = make_list_with_n(0);
    DLL_add_to_front(list, -55);

    int expected[] = {-55};
    assert_list_equals(list, expected, 1);

    DLL_free(list);
}

void test_add_to_front_non_empty(void) {
    DLL_t* list = make_list_with_n(4);
    DLL_add_to_front(list, 88);

    int expected[] = {88, 0, 1, 2, 3};
    assert_list_equals(list, expected, 5);

    DLL_free(list);
}

/* DLL_add_to_end tests */

void test_add_to_end_null(void) {
    DLL_add_to_end(NULL, 6);
}

void test_add_to_end_empty(void) {
    DLL_t* list = make_list_with_n(0);
    DLL_add_to_end(list, 10);

    int expected[] = {10};
    assert_list_equals(list, expected, 1);

    DLL_free(list);
}

void test_add_to_end_non_empty(void) {
    DLL_t* list = make_list_with_n(6);
    DLL_add_to_end(list, -128);

    int expected[] = {0, 1, 2, 3, 4, 5, -128};
    assert_list_equals(list, expected, 7);

    DLL_free(list);
}

/* DLL_remove_from_front tests */

void test_remove_from_front_null(void) {
    int val = DLL_remove_from_front(NULL);
    TEST_ASSERT_EQUAL(-1, val);
}

void test_remove_from_front_empty(void) {
    DLL_t* list = make_list_with_n(0);
    int val = DLL_remove_from_front(list);
    TEST_ASSERT_EQUAL(-1, val);

    DLL_free(list);
}

void test_remove_from_front_single(void) {
    DLL_t* list = make_list_with_n(1);
    list->head->data = 67;
    int val = DLL_remove_from_front(list);
    TEST_ASSERT_EQUAL(67, val);

    int expected[] = {};
    assert_list_equals(list, expected, 0);

    DLL_free(list);
}

void test_remove_from_front_multiple(void) {
    DLL_t* list = make_list_with_n(6);
    list->head->data = 7777;
    int val = DLL_remove_from_front(list);
    TEST_ASSERT_EQUAL(7777, val);

    int expected[] = {1, 2, 3, 4, 5};
    assert_list_equals(list, expected, 5);

    DLL_free(list);
}

/* DLL_remove_from_end tests */

void test_remove_from_end_null(void) {
    int val = DLL_remove_from_end(NULL);
    TEST_ASSERT_EQUAL(-1, val);
}

void test_remove_from_end_empty(void) {
    DLL_t* list = make_list_with_n(0);
    int val = DLL_remove_from_end(list);
    TEST_ASSERT_EQUAL(-1, val);

    DLL_free(list);
}

void test_remove_from_end_single(void) {
    DLL_t* list = make_list_with_n(1);
    list->tail->data = 99;
    int val = DLL_remove_from_end(list);
    TEST_ASSERT_EQUAL(99, val);

    int expected[] = {};
    assert_list_equals(list, expected, 0);

    DLL_free(list);
}

void test_remove_from_end_multiple(void) {
    DLL_t* list = make_list_with_n(4);
    list->tail->data = 10;
    int val = DLL_remove_from_end(list);
    TEST_ASSERT_EQUAL(10, val);

    int expected[] = {0, 1, 2};
    assert_list_equals(list, expected, 3);

    DLL_free(list);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_create);
    RUN_TEST(test_clear_null);
    RUN_TEST(test_clear_nonnull);
    RUN_TEST(test_free_null);
    RUN_TEST(test_free_nonnull);

    RUN_TEST(test_add_to_front_null);
    RUN_TEST(test_add_to_front_empty);
    RUN_TEST(test_add_to_front_non_empty);

    RUN_TEST(test_add_to_end_null);
    RUN_TEST(test_add_to_end_empty);
    RUN_TEST(test_add_to_end_non_empty);

    RUN_TEST(test_remove_from_front_null);
    RUN_TEST(test_remove_from_front_empty);
    RUN_TEST(test_remove_from_front_single);
    RUN_TEST(test_remove_from_front_multiple);

    RUN_TEST(test_remove_from_end_null);
    RUN_TEST(test_remove_from_end_empty);
    RUN_TEST(test_remove_from_end_single);
    RUN_TEST(test_remove_from_end_multiple);
    
    return UNITY_END();
}
