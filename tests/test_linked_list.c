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

void assert_list_equals(LL_t* list, int expected[], int n); // TODO

void test_create(void) {
    LL_t* list = make_list_with_n(0);

    CU_ASSERT_PTR_NOT_NULL_FATAL(list);
    CU_ASSERT_PTR_NULL(list->head);
    CU_ASSERT_PTR_NULL(list->tail);

    LL_free(list);
}

void test_add_to_head(void) { // TODO: Separate tests more and make equals using assert_list_equals
    // Adding into empty
    LL_t* empty = make_list_with_n(0);
    LL_add_to_head(empty, -8);
    node_t* added = empty->head;
    CU_ASSERT_PTR_NOT_NULL_FATAL(added);
    CU_ASSERT_EQUAL(added->data, -8);
    CU_ASSERT_PTR_EQUAL(added, empty->tail); // First element should be both the head and tail
    LL_free(empty);

    // Adding into non-empty
    LL_t* three = make_list_with_n(0);
    LL_add_to_head(three, -3);
    LL_add_to_head(three, 0);
    LL_add_to_head(three, 3);
    // List should be 3 -> 0 -> -3
    added = three->head;
    CU_ASSERT_PTR_NOT_NULL_FATAL(added);
    CU_ASSERT_EQUAL(added->data, 3);
    CU_ASSERT_EQUAL(added->next->data, 0);
    CU_ASSERT_EQUAL(added->next->next->data, -3);
    CU_ASSERT_PTR_EQUAL(added->next->next, three->tail);
    LL_free(three);
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
    CU_add_test(suite, "test_add_to_head", test_add_to_head);

    /* Run the tests */
    CU_basic_run_tests();

    /* Clean up the registry */
    CU_cleanup_registry();
    return CU_get_error();
}