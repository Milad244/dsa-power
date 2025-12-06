#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <linked_list.h>

LL_t* shared_list;

static LL_t* make_list_with_n(int n) {
    LL_t* list = LL_create();
    for (int i = 0; i < n; i++) {
        LL_add_to_head(list, i);
    }
    return list;
}

int init_suite(void) {
    shared_list = make_list_with_n(5);
    if (shared_list == NULL) return -1;
    return 0;
}

int clean_suite(void) {
    LL_free(shared_list);
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

void test_add_to_head_empty(void) {
    LL_t* empty = make_list_with_n(0);
    LL_add_to_head(empty, -8);

    int expected[] = {-8};
    assert_list_equals(empty, expected, 1);

    LL_free(empty);
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

void test_add_to_tail_empty(void) {
    LL_t* empty = make_list_with_n(0);
    LL_add_to_tail(empty, 1234);

    int expected[] = {1234};
    assert_list_equals(empty, expected, 1);

    LL_free(empty);
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
    CU_add_test(suite, "test_add_to_head_empty", test_add_to_head_empty);
    CU_add_test(suite, "test_add_to_head_non_empty", test_add_to_head_non_empty);
    CU_add_test(suite, "test_add_to_tail_empty", test_add_to_tail_empty);
    CU_add_test(suite, "test_add_to_tail_non_empty", test_add_to_tail_non_empty);

    /* Run the tests */
    CU_basic_run_tests();

    /* Clean up the registry */
    CU_cleanup_registry();
    return CU_get_error();
}