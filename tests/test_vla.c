#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <vla.h>

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

// Helper that makes vla with n items of value 0, 1, 2, ..., n - 1
static VLA_t* make_list_with_n(int n) {
    VLA_t* vla = VLA_create();
    for (int i = n - 1; i >= 0; i--) { // Doing it backwards since push_front is O(n)
        VLA_push_back(vla, &i);
    }
    return vla;
}

/* VLA_create tests */

void test_create(void) {
    VLA_t* vla = make_list_with_n(0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(vla);
    CU_ASSERT_EQUAL(vla->capacity, 0);
    CU_ASSERT_EQUAL(vla->size, 0);
    CU_ASSERT_PTR_NULL(vla->data);

    VLA_free(vla);
}

/* VLA_clear tests */

void test_clear(void) {
    VLA_t* vla = make_list_with_n(5);
    VLA_clear(vla);
    CU_ASSERT_PTR_NOT_NULL(vla);
    CU_ASSERT_EQUAL(vla->capacity, 0);
    CU_ASSERT_EQUAL(vla->size, 0);
    CU_ASSERT_PTR_NULL(vla->data);

    VLA_free(vla);
}

/* VLA_free tests */

void test_free_null(void) {
    VLA_free(NULL);
}

void test_free_nonnull(void) {
    VLA_t* vla = make_list_with_n(3);
    VLA_free(vla);
}

/* VLA_push_back tests */

int main(void) {
    /* Initialize CUnit test registry */
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    /* Add a suite to the registry */
    CU_pSuite suite = CU_add_suite("VLA_Suite", init_suite, clean_suite);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add tests to the suite */
    CU_add_test(suite, "test_create", test_create);
    CU_add_test(suite, "test_clear", test_clear);
    CU_add_test(suite, "test_free_null", test_free_null);
    CU_add_test(suite, "test_free_nonnull", test_free_nonnull);

    /* Run the tests */
    CU_basic_run_tests();

    /* Clean up the registry */
    CU_cleanup_registry();
    return CU_get_error();
}
