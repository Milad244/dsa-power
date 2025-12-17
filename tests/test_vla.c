#include "Unity/unity.h"
#include "../include/vla.h"

void setUp(void) {}
void tearDown(void) {}

// Helper that makes VLA with n items of value 0, 1, 2, ..., n - 1
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
    TEST_ASSERT_NOT_NULL(vla);
    TEST_ASSERT_EQUAL_INT(0, vla->capacity);
    TEST_ASSERT_EQUAL_INT(0, vla->size);
    TEST_ASSERT_NULL(vla->data);

    VLA_free(vla);
}

/* VLA_clear tests */

void test_clear(void) {
    VLA_t* vla = make_list_with_n(5);
    VLA_clear(vla);
    TEST_ASSERT_NOT_NULL(vla);
    TEST_ASSERT_EQUAL_INT(0, vla->capacity);
    TEST_ASSERT_EQUAL_INT(0, vla->size);
    TEST_ASSERT_NULL(vla->data);

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
    UNITY_BEGIN();

    RUN_TEST(test_create);
    RUN_TEST(test_clear);
    RUN_TEST(test_free_null);
    RUN_TEST(test_free_nonnull);

    return UNITY_END();
}
