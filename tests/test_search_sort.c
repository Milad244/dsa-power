#include "Unity/unity.h"
#include "search_sort.h"

void setUp(void) {}
void tearDown(void) {}

// Helper to assert the array target is found correctly
static void assert_target_found(const int* arr, int n, int target, int target_found) {
    if (target_found == -1) {
        for (int i = 0; i < n; i++) {
            TEST_ASSERT_NOT_EQUAL(arr[i], target);
        }
    } else {
        TEST_ASSERT_TRUE(target_found >= 0 && target_found < n);
        TEST_ASSERT_EQUAL(target, arr[target_found]);
    }
}

typedef struct {
    int* arr;
    int len;
    int target;
} search_test_t;

// Helper to ensure search_func searches arrays properly (doesn't verify correct intended implementation, just that it works)
static void test_arr_search(int (*search_func)(const int*, int, int)) {
    int a1[]  = {1};
    int a2[]  = {13, 14};
    int a3[]  = {13, 14};
    int a4[]  = {-1, 0, 1};
    int a5[]  = {-33, -5, -3, -1, -1, 0, 0, 2, 9};
    int a6[]  = {5, 5, 5, 5, 5};
    int a7[]  = {1, 2, 3, 4, 5, 6};
    int a8[]  = {1, 2, 3, 4, 5, 6};
    int a9[]  = {1, 1, 2, 2, 2, 2};

    search_test_t tests[] = {
        {a1, 1, 1},
        {a2, 2, 14},
        {a3, 2, 13},
        {a4, 3, -1},
        {a4, 3, 1},
        {a5, 9, 9},
        {a5, 9, -33},
        {a6, 5, 5},
        {a7, 6, 4},
        {a8, 6, 6},
        {a9, 6, 1},
        {a9, 6, 2},
        {a1, 1, 0}, // not found
        {a5, 9, 15} // not found
    };

    int n = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < n; i++) {
        int result = search_func(tests[i].arr, tests[i].len, tests[i].target);
        assert_target_found(tests[i].arr, tests[i].len, tests[i].target, result);
    }
}

/* Search Tests */

void test_linear_search(void) {
    test_arr_search(linear_search);
}

void test_binary_search(void) {
    test_arr_search(binary_search);
}

// Helper to make recursive binary search call like the others
int rec_binary_search_caller(const int* arr, int n, int target) {
    return rec_binary_search(arr, 0, n - 1, target);
}

void test_rec_binary_search(void) {
    test_arr_search(rec_binary_search_caller);
}

void test_rec2_binary_search(void) {
    test_arr_search(rec2_binary_search);
}

// Helper to assert the array is sorted
static void assert_arr_sorted(const int* arr, int n) {
    for (int i = 1; i < n; i++) {
        TEST_ASSERT_TRUE(arr[i - 1] <= arr[i]);
    }
}

typedef struct {
    int* arr;
    int len;
} sort_test_t;

// Helper to ensure sort_func sorts arrays properly (doesn't verify correct intended implementation, just that it works)
static void test_arr_sort(void (*sort_func)(int*, int)) {
    int a1[] = {1};
    int a2[] = {13, 14};
    int a3[] = {14, 13};
    int a4[] = {0, 1, -1};
    int a5[] = {-1, -5, -3, -33, 0, 9, -1, 2, 0};
    int a6[] = {5, 5, 5, 5, 5};
    int a7[] = {1, 2, 3, 4, 5, 6};
    int a8[] = {6, 5, 4, 3, 2, 1};
    int a9[] = {2, 1, 2, 1, 2, 1};
    int a10[] = {0, 0, 0, 1, 0};
    int a11[] = {-10, -20, -30, -40};
    int a12[] = {1000000, -1000000, 0};
    int a13[] = {3, 1, 2};
    int a14[] = {42, 42};
    int a15[] = {1234, 321, 322, 322, 323, -9};

    sort_test_t tests[] = {
        {a1, 1},
        {a2, 2},
        {a3, 2},
        {a4, 3},
        {a5, 9},
        {a6, 5},
        {a7, 6},
        {a8, 6},
        {a9, 6},
        {a10, 5},
        {a11, 4},
        {a12, 3},
        {a13, 3},
        {a14, 2},
        {a15, 6}
    };

    int n = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < n; i++) {
        sort_func(tests[i].arr, tests[i].len);
        assert_arr_sorted(tests[i].arr, tests[i].len);
    }
}

/* Sorting Tests */

void test_selection_sort(void) {
    test_arr_sort(selection_sort);
}

void test_bubble_sort(void) {
    test_arr_sort(bubble_sort);
}

void test_merge_sort(void) {
    test_arr_sort(merge_sort);
}

// Helper to make quick sort call like the others
void end_quick_sort_caller(int* arr, int n) {
    end_quick_sort(arr, 0, n - 1);
}

void test_end_quick_sort(void) {
    test_arr_sort(end_quick_sort_caller);
}

// Helper to make quick sort call like the others
void start_quick_sort_caller(int* arr, int n) {
    start_quick_sort(arr, 0, n - 1);
}

void test_start_quick_sort(void) {
    test_arr_sort(start_quick_sort_caller);
}

void test_insertion_sort(void) {
    test_arr_sort(insertion_sort);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_linear_search);
    RUN_TEST(test_binary_search);
    RUN_TEST(test_rec_binary_search);
    RUN_TEST(test_rec2_binary_search);

    RUN_TEST(test_selection_sort);
    RUN_TEST(test_bubble_sort);
    RUN_TEST(test_merge_sort);
    RUN_TEST(test_end_quick_sort);
    RUN_TEST(test_start_quick_sort);
    RUN_TEST(test_insertion_sort);

    return UNITY_END();
}
