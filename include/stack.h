#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "linked_list.h"

// Stack definition (using linked list)
typedef struct stack {
    LL_t* list;
} Stack_t;

// Creates a new stack
Stack_t* stack_create(void);

// Pushes an item onto the stack
void stack_push(Stack_t* s, int item);

// Pops the top item off the stack and returns it (-1 if empty)
int stack_pop(Stack_t* s);

// Returns true if the stack is empty
bool stack_is_empty(Stack_t* s);

// Frees the entire stack
void stack_free(Stack_t* s);

#endif // STACK_H
