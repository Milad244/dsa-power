#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <linked_list.h>

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

void test_create(void) {
    LL_t* list = make_list_with_n(0);

    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT_PTR_NULL(list->head);
    CU_ASSERT_PTR_NULL(list->tail);

    LL_free(list);
}

void test_add_to_head_null(void) {
    LL_t* null_list = NULL;
    LL_add_to_head(null_list, 5);
    CU_ASSERT_TRUE(1);
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

void test_add_to_tail_null(void) {
    LL_t* null_list = NULL;
    LL_add_to_tail(null_list, 5);
    CU_ASSERT_TRUE(1);
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

void test_remove_from_head_null(void) {
    LL_t* null_list = NULL;
    LL_remove_from_head(null_list);
    CU_ASSERT_TRUE(1);
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

    /* Run the tests */
    CU_basic_run_tests();

    /* Clean up the registry */
    CU_cleanup_registry();
    return CU_get_error();
}