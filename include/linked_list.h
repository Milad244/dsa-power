#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include "node.h"

// Linked list definition
typedef struct LL {
    node_t* head;
    node_t* tail;
} LL_t;

// Function signatures
LL_t* create_linked_list(void);
void add_to_head(LL_t* list, int item);
void add_to_tail(LL_t* list, int item);
int remove_from_head(LL_t* list);
int remove_from_tail(LL_t* list);

#endif // LINKED_LIST_H
