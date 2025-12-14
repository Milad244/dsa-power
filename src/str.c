#include "../include/str.h"
#include <stdlib.h>
#include <stdbool.h>

size_t str_len(const char* s) {
    if (s == NULL) return 0;

    size_t count = 0;
    while (s[count] != '\0') count++;

    return count;
}

char* str_cat(char* dest, const char* src) {
    if (dest == NULL || src == NULL) return dest;

    size_t i = 0, j = 0;
    while (dest[i] != '\0') i++; // Going until end of str
    // We assume dest has enough space for str
    while (src[j] != '\0') {
        dest[i++] = src[j++];
    }
    dest[i] = '\0';
    
    return dest;
}

char* str_cpy(char* dest, const char* src) {
    if (dest == NULL || src == NULL) return dest;

    size_t i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    
    return dest;
}

int str_cmp(const char* s1, const char* s2) {
    if (s1 == NULL && s2 == NULL) return 0;
    if (s1 == NULL) return -1;
    if (s2 == NULL) return 1;

    size_t i = 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) i++;
    // needs to be casted as unsigned since some systems have char values as negative
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

void str_to_upper(char* s) {
    if (s == NULL) return;

    int i = 0;
    while (s[i] != '\0') {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = 'A' + s[i] - 'a';
        }
        i++;
    }
}

void str_to_lower(char* s) {
    if (s == NULL) return;

    int i = 0;
    while (s[i] != '\0') {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = 'a' + s[i] - 'A';
        }
        i++;
    }
}

char* str_substring(const char* s, int start, int end) {
    if (s == NULL || start > end || start < 0 || end >= (int) str_len(s)) return NULL;

    int i = 0, j = start;
    char* res = (char*) malloc(sizeof(char) * (end - start + 2)); // + 1 for inclusive and + 1 for null-term
    if (res == NULL) return NULL;
    while(j <= end) {
        res[i++] = s[j++];
    }
    res[i] = '\0';
    return res;
}

void str_reverse(char* s) {
    if (s == NULL) return;

    int left = 0, right = str_len(s) - 1;
    char tmp;
    while (left < right) {
        tmp = s[left];
        s[left++] = s[right];
        s[right--] = tmp;
    }
}

bool str_is_palindrome(const char* s) {
    if (s == NULL) return false;

    int left = 0, right = str_len(s) - 1;
    while (left < right) {
        if (s[left++] != s[right--]) return false;
    }

    return true;
}

// Helper function for str_longest_substring_palindrome
static int expand_around_center(const char* s, int left, int right, int n) {
    while (left >= 0 && right < n && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1; // length = (right - left + 1) - 2. The -2 is for the overshoot of while loop
}

char* str_longest_substring_palindrome(const char* s) {
    int n = str_len(s);
    if (n == 0) {
        char* res = (char*) malloc(sizeof(char));
        if (res == NULL) return NULL; 
        res[0] = '\0';
        return res;
    }

    int start = 0, end = 0;
    for (int i = 0; i < n; i++) {
        // odd length palindrome
        int len1 = expand_around_center(s, i, i, n);

        // even length palindrome
        int len2 = expand_around_center(s, i, i+1, n);

        // the max len
        int len = (len1 > len2) ? len1 : len2;
        if (len > end - start + 1) { // new biggest substring palindrome
            start = i - (len - 1) / 2;
            end = i + len / 2;
        }
    }

    char* res = (char*) malloc(sizeof(char) * (end - start + 2));
    if (res == NULL) return NULL;

    for (int i = 0; i < end - start + 1; i++) {
        res[i] = s[start + i];
    }
    res[end - start + 1] = '\0';

    return res;
}
