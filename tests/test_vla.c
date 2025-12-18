#include "Unity/unity.h"
#include "../include/vla.h"

void setUp(void) {}
void tearDown(void) {}

// Helper that makes VLA with n items of values
static VLA_t* make_vla_with_n(int* values, int n) {
    VLA_t* vla = VLA_create();
    if (values == NULL) return vla;

    for (int i = 0; i < n; i++) {
        VLA_push_back(vla, &values[i]);
    }
    return vla;
}

// Helper to assert the vla matches an expected array
static void assert_vla_equals(VLA_t* vla, int* expected, int n) {
    TEST_ASSERT_NOT_NULL(vla);
    TEST_ASSERT_EQUAL(n, vla->size);
    for (int i = 0; i < n; i++) {
        int* val = (int*) VLA_get(vla, i);
        TEST_ASSERT_NOT_NULL(val);
        TEST_ASSERT_EQUAL(expected[i], *val);
    }
}

/* VLA_create tests */

void test_create(void) {
    VLA_t* vla = make_vla_with_n(NULL, 0);
    TEST_ASSERT_NOT_NULL(vla);
    TEST_ASSERT_EQUAL_INT(0, vla->capacity);
    TEST_ASSERT_EQUAL_INT(0, vla->size);
    TEST_ASSERT_NULL(vla->data);

    VLA_free(vla);
}

/* VLA_clear tests */

void test_clear(void) {
    int vals[] = {0, 1, 2};
    VLA_t* vla = make_vla_with_n(vals, 3);
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
    int vals[] = {-1, 0};
    VLA_t* vla = make_vla_with_n(vals, 2);
    VLA_free(vla);
}

/* VLA_push_back tests */

void test_push_back_null(void) {
    VLA_t* vla = NULL;
    int val = 10;
    VLA_push_back(vla, &val);
}

void test_push_back_empty(void) {
    int vals[] = {-200};
    VLA_t* vla = make_vla_with_n(NULL, 0);
    VLA_push_back(vla, &vals[0]);
    assert_vla_equals(vla, vals, 1);
    VLA_free(vla);
}

void test_push_back_non_empty(void) {
    int vals[] = {3, 2, 1};
    VLA_t* vla = make_vla_with_n(NULL, 0);

    VLA_push_back(vla, &vals[0]);
    VLA_push_back(vla, &vals[1]);
    VLA_push_back(vla, &vals[2]);

    assert_vla_equals(vla, vals, 3);
    VLA_free(vla);
}

/* VLA_push_front tests */

void test_push_front_null(void) {
    VLA_t* vla = NULL;
    int val = 5;
    VLA_push_front(vla, &val);
}

void test_push_front_empty(void) {
    int vals[] = {42};
    VLA_t* vla = make_vla_with_n(NULL, 0);
    VLA_push_front(vla, &vals[0]);
    assert_vla_equals(vla, vals, 1);
    VLA_free(vla);
}

void test_push_front_non_empty(void) {
    int initial[] = {2, 3};
    int expected[] = {1, 2, 3};

    VLA_t* vla = make_vla_with_n(initial, 2);
    int val = 1;
    VLA_push_front(vla, &val);

    assert_vla_equals(vla, expected, 3);
    VLA_free(vla);
}

/* VLA_pop_back tests */

void test_pop_back_null(void) {
    VLA_t* vla = NULL;
    TEST_ASSERT_NULL(VLA_pop_back(vla));
}

void test_pop_back_empty(void) {
    VLA_t* vla = make_vla_with_n(NULL, 0);
    TEST_ASSERT_NULL(VLA_pop_back(vla));
    VLA_free(vla);
}

void test_pop_back_non_empty(void) {
    int vals[] = {1, 2, 3};
    VLA_t* vla = make_vla_with_n(vals, 3);

    int* popped = (int*) VLA_pop_back(vla);
    TEST_ASSERT_EQUAL(3, *popped);

    int expected[] = {1, 2};
    assert_vla_equals(vla, expected, 2);

    VLA_free(vla);
}

/* VLA_pop_front tests */

void test_pop_front_null(void) {
    VLA_t* vla = NULL;
    TEST_ASSERT_NULL(VLA_pop_front(vla));
}

void test_pop_front_empty(void) {
    VLA_t* vla = make_vla_with_n(NULL, 0);
    TEST_ASSERT_NULL(VLA_pop_front(vla));
    VLA_free(vla);
}

void test_pop_front_non_empty(void) {
    int vals[] = {1, 2, 3};
    VLA_t* vla = make_vla_with_n(vals, 3);

    int* popped = (int*) VLA_pop_front(vla);
    TEST_ASSERT_EQUAL(1, *popped);

    int expected[] = {2, 3};
    assert_vla_equals(vla, expected, 2);

    VLA_free(vla);
}

/* VLA_size tests */

void test_size_null(void) {
    TEST_ASSERT_EQUAL(0, VLA_size(NULL));
}

void test_size_empty(void) {
    VLA_t* vla = make_vla_with_n(NULL, 0);
    TEST_ASSERT_EQUAL(0, VLA_size(vla));
    VLA_free(vla);
}

void test_size_non_empty(void) {
    int vals[] = {1, 2, 3};
    VLA_t* vla = make_vla_with_n(vals, 3);
    TEST_ASSERT_EQUAL(3, VLA_size(vla));
    VLA_free(vla);
}

/* VLA_is_empty tests */

void test_is_empty_null(void) {
    TEST_ASSERT_TRUE(VLA_is_empty(NULL));
}

void test_is_empty_empty(void) {
    VLA_t* vla = make_vla_with_n(NULL, 0);
    TEST_ASSERT_TRUE(VLA_is_empty(vla));
    VLA_free(vla);
}

void test_is_empty_non_empty(void) {
    int vals[] = {7};
    VLA_t* vla = make_vla_with_n(vals, 1);
    TEST_ASSERT_FALSE(VLA_is_empty(vla));
    VLA_free(vla);
}

/* VLA_peek_back tests */

void test_peek_back_null(void) {
    TEST_ASSERT_NULL(VLA_peek_back(NULL));
}

void test_peek_back_empty(void) {
    VLA_t* vla = make_vla_with_n(NULL, 0);
    TEST_ASSERT_NULL(VLA_peek_back(vla));
    VLA_free(vla);
}

void test_peek_back_non_empty(void) {
    int vals[] = {4, 5, 6};
    VLA_t* vla = make_vla_with_n(vals, 3);

    int* peeked = (int*) VLA_peek_back(vla);
    TEST_ASSERT_NOT_NULL(peeked);
    TEST_ASSERT_EQUAL(6, *peeked);

    TEST_ASSERT_EQUAL(3, VLA_size(vla)); // ensure element not removed

    VLA_free(vla);
}

/* VLA_peek_front tests */

void test_peek_front_null(void) {
    TEST_ASSERT_NULL(VLA_peek_front(NULL));
}

void test_peek_front_empty(void) {
    VLA_t* vla = make_vla_with_n(NULL, 0);
    TEST_ASSERT_NULL(VLA_peek_front(vla));
    VLA_free(vla);
}

void test_peek_front_non_empty(void) {
    int vals[] = {7, 8, 9};
    VLA_t* vla = make_vla_with_n(vals, 3);

    int* peeked = (int*) VLA_peek_front(vla);
    TEST_ASSERT_NOT_NULL(peeked);
    TEST_ASSERT_EQUAL(7, *peeked);

    TEST_ASSERT_EQUAL(3, VLA_size(vla)); // ensure element not removed

    VLA_free(vla);
}

/* VLA_get tests */

void test_get_out_of_bounds(void) {
    int vals[] = {1, 2};
    VLA_t* vla = make_vla_with_n(vals, 2);

    TEST_ASSERT_NULL(VLA_get(vla, 2)); // index == size
    TEST_ASSERT_NULL(VLA_get(vla, 10)); // index > size
    VLA_free(vla);
}

void test_get_valid(void) {
    int vals[] = {5, 6, 7};
    VLA_t* vla = make_vla_with_n(vals, 3);

    for (size_t i = 0; i < 3; i++) {
        int* val = (int*) VLA_get(vla, i);
        TEST_ASSERT_NOT_NULL(val);
        TEST_ASSERT_EQUAL(vals[i], *val);
    }

    VLA_free(vla);
}

/* VLA_set tests */

void test_set_out_of_bounds(void) {
    int vals[] = {1, 2};
    VLA_t* vla = make_vla_with_n(vals, 2);

    int val = 99;
    VLA_set(vla, 2, &val); // should do nothing
    VLA_set(vla, 10, &val); // should do nothing

    int expected[] = {1, 2};
    assert_vla_equals(vla, expected, 2);

    VLA_free(vla);
}

void test_set_valid(void) {
    int vals[] = {3, 4, 5};
    VLA_t* vla = make_vla_with_n(vals, 3);

    int val = 99;
    VLA_set(vla, 1, &val);

    int expected[] = {3, 99, 5};
    assert_vla_equals(vla, expected, 3);

    VLA_free(vla);
}

/* VLA capacity growth tests */
void test_push_back_capacity_growth(void) {
    VLA_t* vla = VLA_create();
    TEST_ASSERT_NOT_NULL(vla);

    int n = 100;
    int values[n];
    for (int i = 0; i < n; i++) {
        values[i] = i;
        VLA_push_back(vla, &values[i]);
    }

    TEST_ASSERT_EQUAL(n, VLA_size(vla));
    assert_vla_equals(vla, values, n);

    VLA_free(vla);
}

/* VLA mixed front/back order preservation tests */
void test_push_front_back_order_preservation(void) {
    int a = 1, b = 2, c = 3, d = 4;
    int expected_after_push[] = {d, b, a, c}; // expected order after pushes

    VLA_t* vla = VLA_create();
    TEST_ASSERT_NOT_NULL(vla);

    VLA_push_back(vla, &a);    // [1]
    VLA_push_front(vla, &b);   // [2,1]
    VLA_push_back(vla, &c);    // [2,1,3]
    VLA_push_front(vla, &d);   // [4,2,1,3]

    assert_vla_equals(vla, expected_after_push, 4);

    // Pop front and back to check order
    int* front = (int*) VLA_pop_front(vla);
    int* back  = (int*) VLA_pop_back(vla);
    TEST_ASSERT_EQUAL(4, *front);
    TEST_ASSERT_EQUAL(3, *back);

    int expected_remaining[] = {2, 1};
    assert_vla_equals(vla, expected_remaining, 2);

    VLA_free(vla);
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_create);
    RUN_TEST(test_clear);
    RUN_TEST(test_free_null);
    RUN_TEST(test_free_nonnull);

    RUN_TEST(test_push_back_null);
    RUN_TEST(test_push_back_empty);
    RUN_TEST(test_push_back_non_empty);

    RUN_TEST(test_push_front_null);
    RUN_TEST(test_push_front_empty);
    RUN_TEST(test_push_front_non_empty);

    RUN_TEST(test_pop_back_null);
    RUN_TEST(test_pop_back_empty);
    RUN_TEST(test_pop_back_non_empty);

    RUN_TEST(test_pop_front_null);
    RUN_TEST(test_pop_front_empty);
    RUN_TEST(test_pop_front_non_empty);

    RUN_TEST(test_size_null);
    RUN_TEST(test_size_empty);
    RUN_TEST(test_size_non_empty);

    RUN_TEST(test_is_empty_null);
    RUN_TEST(test_is_empty_empty);
    RUN_TEST(test_is_empty_non_empty);

    RUN_TEST(test_peek_back_null);
    RUN_TEST(test_peek_back_empty);
    RUN_TEST(test_peek_back_non_empty);

    RUN_TEST(test_peek_front_null);
    RUN_TEST(test_peek_front_empty);
    RUN_TEST(test_peek_front_non_empty);

    RUN_TEST(test_get_out_of_bounds);
    RUN_TEST(test_get_valid);

    RUN_TEST(test_set_out_of_bounds);
    RUN_TEST(test_set_valid);

    RUN_TEST(test_push_back_capacity_growth);
    RUN_TEST(test_push_front_back_order_preservation);

    return UNITY_END();
}
