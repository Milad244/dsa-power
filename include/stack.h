#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "linked_list.h"

// Stack definition (using linked list)
typedef struct stack {
    LL_t* list;
} Stack_t;

// Creates a new empty stack
Stack_t* create_stack(void);

// Pushes an item onto the stack
void push(Stack_t* s, int item);

// Pops the top item off the stack and returns it (-1 if empty)
int pop(Stack_t* s);

// Returns true if the stack is empty
bool stack_isEmpty(Stack_t* s);

// Frees the entire stack
void free_stack(Stack_t* s);

#endif // STACK_H
