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

// Function signatures
DLL_t* create_DLL(void);
void add_to_front(DLL_t* list, int item);
void add_to_end(DLL_t* list, int item);
int remove_from_front(DLL_t* list);
int remove_from_end(DLL_t* list);

#endif // DOUBLY_LINKED_LIST_H
