#ifndef STR_H
#define STR_H

#include <stdlib.h>
#include <stdbool.h>

// Returns the length of the string (0 if null)
size_t str_len(const char* s);

// Concatenates src onto the end of dest and returns dest (assumes dest has enough room to concat src)
char* str_cat(char* dest, const char* src);

// Copies src to dest (assumes dest has enough room to copy src)
char* str_cpy(char* dest, const char* src);

// Returns the difference between the first difference of the two characters
// (returns 0 if equal or both null, -1 if s1 is null and 1 if s2 is null)
int str_cmp(const char* s1, const char* s2);

// Turns all lowercase ASCII letters uppercase, in-place
void str_to_upper(char* s);

// Turns all uppercase ASCII letters lowercase, in-place
void str_to_lower(char* s);

// Returns a substring of the given string inclusive to start and end (returns NULL on invalid input)
char* str_substring(const char* s, int start, int end);

// Reverses the given string, in-place
void str_reverse(char* s);

// Checks if the given string is a palindrome
bool str_is_palindrome(const char* s);

// Returns the longest substring of the given string that is a palindrome
char* str_longest_substring_palindrome(const char* s);

#endif // STR_H