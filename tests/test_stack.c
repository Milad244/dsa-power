#include "Unity/unity.h"
#include "../include/stack.h"

void setUp(void) {}
void tearDown(void) {}

// Helper that makes stack with n items of value 0, 1, 2, ..., n - 1
static Stack_t* make_stack_with_n(int n) {
    Stack_t* s = stack_create();
    if (s == NULL) return NULL;
    for (int i = 0; i < n; i++) {
        stack_push(s, i);
    }
    return s;
}

// Helper to assert the stack matches an expected array (top = first)
static void assert_stack_equals(Stack_t* s, int expected[], int n) {
    TEST_ASSERT_NOT_NULL(s);
    node_t* curr = s->list->head;
    for (int i = n - 1; i >= 0; i--) {
        TEST_ASSERT_NOT_NULL(curr);
        TEST_ASSERT_EQUAL(expected[i], curr->data);
        if (i == 0) {
            TEST_ASSERT_EQUAL_PTR(curr, s->list->tail);
        }
        curr = curr->next;
    }
    TEST_ASSERT_NULL(curr);
}

/* stack_create tests */

void test_stack_create(void) {
    Stack_t* s = stack_create();
    TEST_ASSERT_NOT_NULL(s);
    TEST_ASSERT_NOT_NULL(s->list);
    TEST_ASSERT_NULL(s->list->head);
    TEST_ASSERT_NULL(s->list->tail);
    stack_free(s);
}

/* stack_clear tests */

void test_stack_clear_null(void) {
    stack_clear(NULL);
}

void test_stack_clear_nonnull(void) {
    Stack_t* s = make_stack_with_n(7);
    stack_clear(s);

    TEST_ASSERT_NOT_NULL(s);
    TEST_ASSERT_NOT_NULL(s->list);
    TEST_ASSERT_NULL(s->list->head);
    TEST_ASSERT_NULL(s->list->tail);

    stack_free(s);
}

/* stack_free tests */

void test_stack_free_null(void) {
    stack_free(NULL);
}

void test_stack_free_nonnull(void) {
    Stack_t* s = make_stack_with_n(12);
    stack_free(s);
}

/* stack_push tests */

void test_push_null(void) {
    stack_push(NULL, 33);
}

void test_push_empty(void) {
    Stack_t* s = make_stack_with_n(0);
    stack_push(s, 85);

    int expected[] = {85};
    assert_stack_equals(s, expected, 1);

    stack_free(s);
}

void test_push_non_empty(void) {
    Stack_t* s = make_stack_with_n(3);
    stack_push(s, 77);

    int expected[] = {0, 1, 2, 77};
    assert_stack_equals(s, expected, 4);

    stack_free(s);
}

/* stack_pop tests */

void test_pop_null(void) {
    int val = stack_pop(NULL);
    TEST_ASSERT_EQUAL(-1, val);
}

void test_pop_empty(void) {
    Stack_t* s = make_stack_with_n(0);
    int val = stack_pop(s);
    TEST_ASSERT_EQUAL(-1, val);
    stack_free(s);
}

void test_pop_single(void) {
    Stack_t* s = make_stack_with_n(1);
    int val = stack_pop(s);
    TEST_ASSERT_EQUAL(0, val);

    int expected[] = {};
    assert_stack_equals(s, expected, 0);

    stack_free(s);
}

void test_pop_multiple(void) {
    Stack_t* s = make_stack_with_n(5);
    int val = stack_pop(s);
    TEST_ASSERT_EQUAL(4, val);

    int expected[] = {0, 1, 2, 3};
    assert_stack_equals(s, expected, 4);

    stack_free(s);
}

/* stack_size tests */

void test_stack_size_null(void) {
    TEST_ASSERT_EQUAL(0, stack_size(NULL));
}

void test_stack_size_empty(void) {
    Stack_t* s = make_stack_with_n(0);
    TEST_ASSERT_EQUAL(0, stack_size(s));
    stack_free(s);
}

void test_stack_size_non_empty(void) {
    Stack_t* s = make_stack_with_n(8);
    TEST_ASSERT_EQUAL(8, stack_size(s));
    stack_free(s);
}

/* stack_is_empty tests */

void test_stack_is_empty_null(void) {
    TEST_ASSERT_TRUE(stack_is_empty(NULL));
}

void test_stack_is_empty_empty(void) {
    Stack_t* s = make_stack_with_n(0);
    TEST_ASSERT_TRUE(stack_is_empty(s));
    stack_free(s);
}

void test_stack_is_empty_single(void) {
    Stack_t* s = make_stack_with_n(1);
    TEST_ASSERT_FALSE(stack_is_empty(s));
    stack_free(s);
}

void test_stack_is_empty_multiple(void) {
    Stack_t* s = make_stack_with_n(7);
    TEST_ASSERT_FALSE(stack_is_empty(s));
    stack_free(s);
}

/* stack_equal tests */

void test_stack_equal_null(void) {
    TEST_ASSERT_FALSE(stack_equal(NULL, make_stack_with_n(1)));
    TEST_ASSERT_FALSE(stack_equal(make_stack_with_n(1), NULL));
    TEST_ASSERT_TRUE(stack_equal(NULL, NULL));
}

void test_stack_equal_empty(void) {
    Stack_t* s1 = make_stack_with_n(0);
    Stack_t* s2 = make_stack_with_n(0);
    TEST_ASSERT_TRUE(stack_equal(s1, s2));
    stack_free(s1);
    stack_free(s2);
}

void test_stack_equal_non_empty(void) {
    Stack_t* s1 = make_stack_with_n(6);
    Stack_t* s2 = make_stack_with_n(6);
    TEST_ASSERT_TRUE(stack_equal(s1, s2));

    stack_push(s1, 999);
    TEST_ASSERT_FALSE(stack_equal(s1, s2));

    stack_free(s1);
    stack_free(s2);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_stack_create);
    RUN_TEST(test_stack_clear_null);
    RUN_TEST(test_stack_clear_nonnull);
    RUN_TEST(test_stack_free_null);
    RUN_TEST(test_stack_free_nonnull);

    RUN_TEST(test_push_null);
    RUN_TEST(test_push_empty);
    RUN_TEST(test_push_non_empty);

    RUN_TEST(test_pop_null);
    RUN_TEST(test_pop_empty);
    RUN_TEST(test_pop_single);
    RUN_TEST(test_pop_multiple);

    RUN_TEST(test_stack_size_null);
    RUN_TEST(test_stack_size_empty);
    RUN_TEST(test_stack_size_non_empty);

    RUN_TEST(test_stack_is_empty_null);
    RUN_TEST(test_stack_is_empty_empty);
    RUN_TEST(test_stack_is_empty_single);
    RUN_TEST(test_stack_is_empty_multiple);

    RUN_TEST(test_stack_equal_null);
    RUN_TEST(test_stack_equal_empty);
    RUN_TEST(test_stack_equal_non_empty);

    return UNITY_END();
}