#include "Unity/unity.h"
#include "../include/queue.h"

void setUp(void) {}
void tearDown(void) {}

// Helper that makes queue with n items of value 0, 1, 2, ..., n - 1
static queue_t* make_queue_with_n(int n) {
    queue_t* q = queue_create();
    if (q == NULL) return NULL;
    for (int i = 0; i < n; i++) {
        queue_enqueue(q, i);
    }
    return q;
}

// Helper to assert the queue matches an expected array
static void assert_queue_equals(queue_t* q, int expected[], int n) {
    TEST_ASSERT_NOT_NULL(q);
    node_t* curr = q->list->head;
    for (int i = 0; i < n; i++) {
        TEST_ASSERT_NOT_NULL(curr);
        TEST_ASSERT_EQUAL(expected[i], curr->data);
        if (i == n - 1) {
            TEST_ASSERT_EQUAL_PTR(curr, q->list->tail);
        }
        curr = curr->next;
    }
    TEST_ASSERT_NULL(curr);
}

/* queue_create tests */

void test_queue_create(void) {
    queue_t* q = queue_create();
    TEST_ASSERT_NOT_NULL(q);
    TEST_ASSERT_NOT_NULL(q->list);
    TEST_ASSERT_NULL(q->list->head);
    TEST_ASSERT_NULL(q->list->tail);
    queue_free(q);
}

/* queue_clear tests */

void test_queue_clear_null(void) {
    queue_clear(NULL);
}

void test_queue_clear_nonnull(void) {
    queue_t* q = make_queue_with_n(4);
    queue_clear(q);

    TEST_ASSERT_NOT_NULL(q);
    TEST_ASSERT_NOT_NULL(q->list);
    TEST_ASSERT_NULL(q->list->head);
    TEST_ASSERT_NULL(q->list->tail);

    queue_free(q);
}

/* queue_free tests */

void test_queue_free_null(void) {
    queue_free(NULL);
}

void test_queue_free_nonnull(void) {
    queue_t* q = make_queue_with_n(6);
    queue_free(q);
}

/* queue_enqueue tests */

void test_enqueue_null(void) {
    queue_enqueue(NULL, 42);
}

void test_enqueue_empty(void) {
    queue_t* q = make_queue_with_n(0);
    queue_enqueue(q, 99);

    int expected[] = {99};
    assert_queue_equals(q, expected, 1);

    queue_free(q);
}

void test_enqueue_non_empty(void) {
    queue_t* q = make_queue_with_n(3);
    queue_enqueue(q, 77);

    int expected[] = {0, 1, 2, 77};
    assert_queue_equals(q, expected, 4);

    queue_free(q);
}

/* queue_dequeue tests */

void test_dequeue_null(void) {
    int val = queue_dequeue(NULL);
    TEST_ASSERT_EQUAL(-1, val);
}

void test_dequeue_empty(void) {
    queue_t* q = make_queue_with_n(0);
    int val = queue_dequeue(q);
    TEST_ASSERT_EQUAL(-1, val);
    queue_free(q);
}

void test_dequeue_single(void) {
    queue_t* q = make_queue_with_n(1);
    int val = queue_dequeue(q);
    TEST_ASSERT_EQUAL(0, val);

    int expected[] = {};
    assert_queue_equals(q, expected, 0);

    queue_free(q);
}

void test_dequeue_multiple(void) {
    queue_t* q = make_queue_with_n(4);
    int val = queue_dequeue(q);
    TEST_ASSERT_EQUAL(0, val);

    int expected[] = {1, 2, 3};
    assert_queue_equals(q, expected, 3);

    queue_free(q);
}

/* queue_size tests */

void test_queue_size_null(void) {
    TEST_ASSERT_EQUAL(0, queue_size(NULL));
}

void test_queue_size_empty(void) {
    queue_t* q = make_queue_with_n(0);
    TEST_ASSERT_EQUAL(0, queue_size(q));
    queue_free(q);
}

void test_queue_size_non_empty(void) {
    queue_t* q = make_queue_with_n(5);
    TEST_ASSERT_EQUAL(5, queue_size(q));
    queue_free(q);
}

/* queue_is_empty tests */

void test_queue_is_empty_null(void) {
    TEST_ASSERT_TRUE(queue_is_empty(NULL));
}

void test_queue_is_empty_empty(void) {
    queue_t* q = make_queue_with_n(0);
    TEST_ASSERT_TRUE(queue_is_empty(q));
    queue_free(q);
}

void test_queue_is_empty_single(void) {
    queue_t* q = make_queue_with_n(1);
    TEST_ASSERT_FALSE(queue_is_empty(q));
    queue_free(q);
}

void test_queue_is_empty_multiple(void) {
    queue_t* q = make_queue_with_n(3);
    TEST_ASSERT_FALSE(queue_is_empty(q));
    queue_free(q);
}

/* queue_equal tests */

void test_queue_equal_null(void) {
    TEST_ASSERT_FALSE(queue_equal(NULL, make_queue_with_n(1)));
    TEST_ASSERT_FALSE(queue_equal(make_queue_with_n(1), NULL));
    TEST_ASSERT_TRUE(queue_equal(NULL, NULL));
}

void test_queue_equal_empty(void) {
    queue_t* q1 = make_queue_with_n(0);
    queue_t* q2 = make_queue_with_n(0);
    TEST_ASSERT_TRUE(queue_equal(q1, q2));
    queue_free(q1);
    queue_free(q2);
}

void test_queue_equal_non_empty(void) {
    queue_t* q1 = make_queue_with_n(3);
    queue_t* q2 = make_queue_with_n(3);
    TEST_ASSERT_TRUE(queue_equal(q1, q2));

    queue_enqueue(q2, 99);
    TEST_ASSERT_FALSE(queue_equal(q1, q2));

    queue_free(q1);
    queue_free(q2);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_queue_create);
    RUN_TEST(test_queue_clear_null);
    RUN_TEST(test_queue_clear_nonnull);
    RUN_TEST(test_queue_free_null);
    RUN_TEST(test_queue_free_nonnull);

    RUN_TEST(test_enqueue_null);
    RUN_TEST(test_enqueue_empty);
    RUN_TEST(test_enqueue_non_empty);

    RUN_TEST(test_dequeue_null);
    RUN_TEST(test_dequeue_empty);
    RUN_TEST(test_dequeue_single);
    RUN_TEST(test_dequeue_multiple);

    RUN_TEST(test_queue_size_null);
    RUN_TEST(test_queue_size_empty);
    RUN_TEST(test_queue_size_non_empty);

    RUN_TEST(test_queue_is_empty_null);
    RUN_TEST(test_queue_is_empty_empty);
    RUN_TEST(test_queue_is_empty_single);
    RUN_TEST(test_queue_is_empty_multiple);

    RUN_TEST(test_queue_equal_null);
    RUN_TEST(test_queue_equal_empty);
    RUN_TEST(test_queue_equal_non_empty);

    return UNITY_END();
}