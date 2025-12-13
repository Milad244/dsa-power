#include "../include/str.h"
#include <stdlib.h>

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

// TODO: Substrings, reverse, palindrome, substring palindrome