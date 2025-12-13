#ifndef STR_H
#define STR_H

#include <stdlib.h>

// Returns the length of the string (0 if null)
size_t str_len(const char* s);

// Concatenates src onto the end of dest and returns dest (assumes dest has enough room to concat src)
char* str_cat(char* dest, const char* src);

// Copies src to dest (assumes dest has enough room to copy src)
char* str_cpy(char* dest, const char* src);

// Returns the difference between the first difference of the two characters
// (returns 0 if equal or both null, -1 if s1 is null and 1 if s2 is null)
int str_cmp(const char* s1, const char* s2);

#endif // STR_H