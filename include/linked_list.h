#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include "node.h"

// Linked list definition
typedef struct LL {
    node_t* head;
    node_t* tail;
} LL_t;

/* Construction / Destruction */

// Creates a new Linked List
LL_t* LL_create(void);
// Frees all nodes but keeps the list
void LL_clear(LL_t* list);
// Frees the entire list
void LL_free(LL_t* list);

/* Insertion / Removal */

// Adds a new element at the head of the list
void LL_add_to_head(LL_t* list, int item);
// Adds a new element at the tail of the list
void LL_add_to_tail(LL_t* list, int item);
// Removes the head element and returns its value (-1 if empty)
int LL_remove_from_head(LL_t* list);
// Removes the tail element and returns its value (-1 if empty)
int LL_remove_from_tail(LL_t* list);

/* Inspection / Queries */

// Gets the size of the list (0 if null)
size_t LL_get_size(LL_t* list);
// Checks if the list is empty
bool LL_is_empty(LL_t* list);
// Checks if two lists are equal
bool LL_are_equal(LL_t* list1, LL_t* list2);
// Gets the index of the first occurrence of an item (-1 if not found)
int LL_index_of(LL_t* list, int item);
// Gets the element at the given index (NULL on invalid input)
node_t* LL_get_item(LL_t* list, size_t index);
// Gets the middle element; for even-sized lists, returns the right-middle
node_t* LL_get_middle(LL_t* list);

/* Transformations */

// Applies the given map on each item in the list
void LL_map(LL_t* list, int (*map)(int));
// Reverses the list
void LL_reverse(LL_t* list);

#endif // LINKED_LIST_H
