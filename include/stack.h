#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>
#include "linked_list.h"

// Stack definition (using linked list)
typedef struct stack {
    LL_t* list;
} Stack_t;

/* Construction / Destruction */

// Creates a new empty stack
Stack_t* stack_create(void);
// Frees all items but keeps the stack
void stack_clear(Stack_t* s);
// Frees the entire stack
void stack_free(Stack_t* s);

/* Insertion / Removal */

// Pushes an item onto the stack
void stack_push(Stack_t* s, int item);
// Pops the top item off the stack and returns it (-1 if empty)
int stack_pop(Stack_t* s);

/* Inspection / Queries */

// Returns the number of items in stack (0 if NULL)
size_t stack_size(const Stack_t* s);
// Returns true if the stack is empty
bool stack_is_empty(const Stack_t* s);
// Checks if two stacks are equal
bool stack_equal(const Stack_t* s1, const Stack_t* s2);

#endif // STACK_H
