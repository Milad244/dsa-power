#include "../include/search_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://piazza.com/class/mc1b0dusddf1xw/post/39#

// Utility

void print_ar(const int* ar, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", ar[i]);
    }
    printf("\n");
}

// Searching

int linear_search(const int* ar, int n, int target) {
    for (int i = 0; i < n; i++) {
        if (ar[i] == target) return i;
    }
    return -1;
}

int binary_search(const int* ar, int n, int target) {
    int l = 0, r = n - 1, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (ar[mid] == target) {
            return mid;
        } else if(ar[mid] > target) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

int rec_binary_search(const int* arr, int start, int end, int item) {
    if (start>end) return -1;
    
    int mid = (start+end)/2;
    
    if (arr[mid] == item)
        return mid;
    else if (arr[mid] > item)
        return rec_binary_search(arr, start, mid - 1, item);
    else 
        return rec_binary_search(arr, mid + 1, end, item);
}

int rec2_binary_search(const int* arr, int n, int item) {
    // We send A+start, n=end-start+1
    if (n == 0) return -1;
    
    int mid = n / 2;
    
    if (arr[mid] == item)
        return mid;
        
    if (arr[mid] > item) {
        return rec2_binary_search(arr, mid, item);
    }
    else {
        int i = rec2_binary_search(arr + mid + 1, n - mid - 1, item);
        if (i == -1)
            return -1;
        else
            return mid + 1 + i;
    }
}

// Sorting

void selection_sort(int* nums, int n) {
    // We find the smallest and swap it with i
    for (int i = 0; i < n - 1; i++) {
        int smallest_i = i;
        for (int j = i + 1; j < n; j++) {
            if (nums[j] < nums[smallest_i]) {
                smallest_i = j;
            }
        }
        // Swap them
        int tmp = nums[i];
        nums[i] = nums[smallest_i];
        nums[smallest_i] = tmp;
    }
}

void bubble_sort(int* ar, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ar[j] > ar[j+1]) {
                int tmp = ar[j];
                ar[j] = ar[j+1];
                ar[j+1] = tmp;
            }
        }
    }
}

void merge(int* ar, int n, int mid) {
    int* sorted = malloc(sizeof(int) * n);
    int i = 0, left = 0, right = mid;
    while(left < mid && right < n) { // While both sides have elements, we put the smallest of each iteration into sorted
        if (ar[left] <= ar[right]) {
            sorted[i] = ar[left];
            left++;
        } else {
            sorted[i] = ar[right];
            right++;
        }
    i++;
  }
  
    // If remaining side, it needs to be added
    while (left < mid) {
        sorted[i] = ar[left];
        left++;
        i++;
    } 
    
    while (right < n) {
        sorted[i] = ar[right];
        right++;
        i++;
    }
    
  
    for (int k = 0; k < n; k++) { // Copying sorted to original
        ar[k] = sorted[k];
    }
    
    free(sorted);
}

void merge_sort(int* ar, int n) {
    if (n <= 1) return; // Base case

    // Recursive step of splitting into subarrays and then merging (while sorting) them back
    int mid = n / 2;
    merge_sort(ar, mid);
    merge_sort(ar + mid, n - mid);
    merge(ar, n, mid);
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int* arr, int start, int end) {
    int pivot = arr[end];
    int i = start - 1;
    
    for (int j = start; j < end; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    swap(&arr[i + 1], &arr[end]);
    return i + 1;
}

void quick_sort(int* arr, int start, int end) {
    if (start < end) {
        int pivot = partition(arr, start, end);
        quick_sort(arr, start, pivot - 1);
        quick_sort(arr, pivot + 1, end);
    }
}

int start_partition(int* arr, int start, int end) {
  int pivot = arr[start];
  int i = start + 1, j = end;
  
  while(1) {
    while (i <= end && arr[i] <= pivot) i++;
    while (j >= start + 1 && arr[j] > pivot) j--;
    
    if (i >= j) break;
    
    swap(&arr[i], &arr[j]);
  }
  
  swap(&arr[start], &arr[j]);
  return j;
}

void start_quick_sort(int* arr, int start, int end) {
    if (start < end) {
        int pivot = start_partition(arr, start, end);
        start_quick_sort(arr, start, pivot - 1);
        start_quick_sort(arr, pivot + 1, end);
    }
}

void insertion_sort(int* arr, int n) {
    int i, curr, j;
    for (i = 1; i < n; i++) {
        curr = arr[i];
        j = i - 1;
        
        while (j >= 0 && arr[j] > curr) {
            arr[j + 1] = arr[j];
            j --;
        }
        arr[j + 1] = curr;
    }
}
