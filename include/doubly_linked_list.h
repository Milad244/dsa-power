#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdbool.h>
#include "node.h"

// Extend node_t for doubly linked list
typedef struct dnode {
    int data;
    struct dnode* next;
    struct dnode* prev;
} dnode_t;

// Doubly linked list definition
typedef struct DLL {
    dnode_t* head;
    dnode_t* tail;
} DLL_t;

// Creates a new doubly-linked list
DLL_t* DLL_create(void);

// Adds a new element at the front of the list
void DLL_add_to_front(DLL_t* list, int item);

// Adds a new element at the end of the list
void DLL_add_to_end(DLL_t* list, int item);

// Removes the front element and returns its value (-1 if empty)
int DLL_remove_from_front(DLL_t* list);

// Removes the end element and returns its value (-1 if empty)
int DLL_remove_from_end(DLL_t* list);

// Frees the entire doubly linked list
void DLL_free(DLL_t* list);

#endif // DOUBLY_LINKED_LIST_H
