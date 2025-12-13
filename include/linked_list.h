#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include "node.h"

// Linked list definition
typedef struct LL {
    node_t* head;
    node_t* tail;
} LL_t;

// Creates a new Linked List
LL_t* LL_create(void);

// Adds a new element at the head of the list
void LL_add_to_head(LL_t* list, int item);

// Adds a new element at the tail of the list
void LL_add_to_tail(LL_t* list, int item);

// Removes the head element and returns its value (-1 if empty)
int LL_remove_from_head(LL_t* list);

// Removes the tail element and returns its value (-1 if empty)
int LL_remove_from_tail(LL_t* list);

// Gets the size of the list (0 if null)
int LL_get_size(LL_t* list);

// Checks if two lists are equal
bool LL_are_equal(LL_t* list1, LL_t* list2);

// Frees the entire linked list
void LL_free(LL_t* list);

#endif // LINKED_LIST_H
