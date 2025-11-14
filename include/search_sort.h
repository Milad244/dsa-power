#ifndef SEARCH_SORT_H
#define SEARCH_SORT_H

#include <stdbool.h>

// Utility
void print_ar(const int* ar, int n);

// Searching
int linear_search(const int* arr, int n, int target);
int binary_search(const int* arr, int n, int target);
int rec_binary_search(const int* arr, int start, int end, int target);
int rec2_binary_search(const int* arr, int n, int target);

// Sorting
void selection_sort(int* arr, int n);
void bubble_sort(int* arr, int n);
void merge_sort(int* arr, int n);
void quick_sort(int* arr, int start, int end);
void start_quick_sort(int* arr, int start, int end);
void insertion_sort(int* arr, int n);

// Helpers
void swap(int* a, int* b);
int partition(int* arr, int start, int end);
int start_partition(int* arr, int start, int end);

#endif // SEARCH_SORT_H
