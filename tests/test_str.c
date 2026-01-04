#include "Unity/unity.h"
#include "str.h"

void setUp(void) {}
void tearDown(void) {}

// Helper to assert two strings are the same
static void assert_str_equal(const char* s1, const char* s2) {
    TEST_ASSERT_EQUAL(0, str_cmp(s1, s2));
}

/* str_len tests */

void test_len_null(void) {
    str_len(NULL);
}

void test_len_empty(void) {
    TEST_ASSERT_EQUAL(0, str_len(""));
}

void test_len_single(void) {
    TEST_ASSERT_EQUAL(1, str_len("h"));
}

void test_len_multiple(void) {
    TEST_ASSERT_EQUAL(8, str_len("12345678"));
}

/* str_cat tests */

void test_cat_null(void) {
    assert_str_equal(str_cat(NULL, NULL), NULL);
    assert_str_equal(str_cat("", NULL), "");
    assert_str_equal(str_cat(NULL, ""), NULL);
}

void test_cat_empty_dest(void) {
    char dest[5] = "\0";
    assert_str_equal(str_cat(dest, "hello"), "hello");
}

void test_cat_empty_src(void) {
    char dest[6] = "012abc";
    assert_str_equal(str_cat(dest, ""), "012abc");
}

void test_cat_single_dest(void) {
    char dest[4] = "x";
    assert_str_equal(str_cat(dest, "pop"), "xpop");
}

void test_cat_single_src(void) {
    char dest[3] = "zz";
    assert_str_equal(str_cat(dest, "z"), "zzz");
}

void test_cat_multiple(void) {
    char dest[10] = "hello";
    assert_str_equal(str_cat(dest, "world"), "helloworld");
}

/* str_cpy tests */

void test_cpy_null(void) {
    assert_str_equal(str_cpy(NULL, NULL), NULL);
    assert_str_equal(str_cpy("", NULL), "");
    assert_str_equal(str_cpy(NULL, ""), NULL);
}

void test_cpy_empty(void) {
    char dest[1];
    assert_str_equal(str_cpy(dest, ""), "");
}

void test_cpy_single(void) {
    char dest[2];
    assert_str_equal(str_cpy(dest, "a"), "a");
}

void test_cpy_multiple(void) {
    char dest[10];
    assert_str_equal(str_cpy(dest, "testing"), "testing");
}

/* str_cmp tests */

void test_cmp_both_null(void) {
    TEST_ASSERT_EQUAL(0, str_cmp(NULL, NULL));
}

void test_cmp_first_null(void) {
    TEST_ASSERT_EQUAL(-1, str_cmp(NULL, "a"));
}

void test_cmp_second_null(void) {
    TEST_ASSERT_EQUAL(1, str_cmp("a", NULL));
}

void test_cmp_equal(void) {
    TEST_ASSERT_EQUAL(0, str_cmp("hello", "hello"));
}

void test_cmp_less(void) {
    TEST_ASSERT_TRUE(str_cmp("abc", "abd") < 0);
}

void test_cmp_greater(void) {
    TEST_ASSERT_TRUE(str_cmp("abd", "abc") > 0);
}

/* str_to_upper tests */

void test_to_upper_null(void) {
    str_to_upper(NULL);
}

void test_to_upper_no_change(void) {
    char s[] = "ABC123";
    str_to_upper(s);
    assert_str_equal(s, "ABC123");
}

void test_to_upper_mixed(void) {
    char s[] = "AbcDe";
    str_to_upper(s);
    assert_str_equal(s, "ABCDE");
}

/* str_to_lower tests */

void test_to_lower_null(void) {
    str_to_lower(NULL);
}

void test_to_lower_no_change(void) {
    char s[] = "abc123";
    str_to_lower(s);
    assert_str_equal(s, "abc123");
}

void test_to_lower_mixed(void) {
    char s[] = "AbCDe";
    str_to_lower(s);
    assert_str_equal(s, "abcde");
}

/* str_substring tests */

void test_substring_null(void) {
    TEST_ASSERT_NULL(str_substring(NULL, 0, 1));
}

void test_substring_invalid_range(void) {
    TEST_ASSERT_NULL(str_substring("hello", 3, 1));
}

void test_substring_single(void) {
    char* s = str_substring("hello", 1, 1);
    assert_str_equal(s, "e");
    free(s);
}

void test_substring_multiple(void) {
    char* s = str_substring("hello", 1, 3);
    assert_str_equal(s, "ell");
    free(s);
}

/* str_reverse tests */

void test_reverse_null(void) {
    str_reverse(NULL);
}

void test_reverse_empty(void) {
    char s[] = "";
    str_reverse(s);
    assert_str_equal(s, "");
}

void test_reverse_single(void) {
    char s[] = "a";
    str_reverse(s);
    assert_str_equal(s, "a");
}

void test_reverse_multiple(void) {
    char s[] = "abcd";
    str_reverse(s);
    assert_str_equal(s, "dcba");
}


/* str_is_palindrome tests */

void test_is_palindrome_null(void) {
    TEST_ASSERT_FALSE(str_is_palindrome(NULL));
}

void test_is_palindrome_empty(void) {
    TEST_ASSERT_TRUE(str_is_palindrome(""));
}

void test_is_palindrome_single(void) {
    TEST_ASSERT_TRUE(str_is_palindrome("a"));
}

void test_is_palindrome_true(void) {
    TEST_ASSERT_TRUE(str_is_palindrome("abba"));
}

void test_is_palindrome_false(void) {
    TEST_ASSERT_FALSE(str_is_palindrome("hello"));
}

/* str_longest_substring_palindrome tests */

void test_longest_palindrome_null(void) {
    TEST_ASSERT_NULL(str_longest_substring_palindrome(NULL));
}

void test_longest_palindrome_single(void) {
    char* s = str_longest_substring_palindrome("a");
    assert_str_equal(s, "a");
    free(s);
}

void test_longest_palindrome_full(void) {
    char* s = str_longest_substring_palindrome("abba");
    assert_str_equal(s, "abba");
    free(s);
}

void test_longest_palindrome_middle(void) {
    char* s = str_longest_substring_palindrome("babad");
    TEST_ASSERT_TRUE(
        str_cmp(s, "bab") == 0 ||
        str_cmp(s, "aba") == 0
    );
    free(s);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_len_null);
    RUN_TEST(test_len_empty);
    RUN_TEST(test_len_single);
    RUN_TEST(test_len_multiple);

    RUN_TEST(test_cat_null);
    RUN_TEST(test_cat_empty_dest);
    RUN_TEST(test_cat_empty_src);
    RUN_TEST(test_cat_single_dest);
    RUN_TEST(test_cat_single_src);
    RUN_TEST(test_cat_multiple);

    RUN_TEST(test_cpy_null);
    RUN_TEST(test_cpy_empty);
    RUN_TEST(test_cpy_single);
    RUN_TEST(test_cpy_multiple);

    RUN_TEST(test_cmp_both_null);
    RUN_TEST(test_cmp_first_null);
    RUN_TEST(test_cmp_second_null);
    RUN_TEST(test_cmp_equal);
    RUN_TEST(test_cmp_less);
    RUN_TEST(test_cmp_greater);

    RUN_TEST(test_to_upper_null);
    RUN_TEST(test_to_upper_no_change);
    RUN_TEST(test_to_upper_mixed);

    RUN_TEST(test_to_lower_null);
    RUN_TEST(test_to_lower_no_change);
    RUN_TEST(test_to_lower_mixed);

    RUN_TEST(test_substring_null);
    RUN_TEST(test_substring_invalid_range);
    RUN_TEST(test_substring_single);
    RUN_TEST(test_substring_multiple);

    RUN_TEST(test_reverse_null);
    RUN_TEST(test_reverse_empty);
    RUN_TEST(test_reverse_single);
    RUN_TEST(test_reverse_multiple);

    RUN_TEST(test_is_palindrome_null);
    RUN_TEST(test_is_palindrome_empty);
    RUN_TEST(test_is_palindrome_single);
    RUN_TEST(test_is_palindrome_true);
    RUN_TEST(test_is_palindrome_false);

    RUN_TEST(test_longest_palindrome_null);
    RUN_TEST(test_longest_palindrome_single);
    RUN_TEST(test_longest_palindrome_full);
    RUN_TEST(test_longest_palindrome_middle);
    
    return UNITY_END();
}
