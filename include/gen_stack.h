#ifndef GEN_STACK_H
#define GEN_STACK_H

#include <stdbool.h>
#include "vla.h"

// General stack definition (using VLA)
typedef struct gen_stack {
    VLA_t* vla;
} gen_stack_t;

/* Construction / Destruction */

// Creates a new empty stack
gen_stack_t* gen_stack_create(void);
// Frees all items but keeps the stack
void gen_stack_clear(gen_stack_t* s);
// Frees the entire stack
void gen_stack_free(gen_stack_t* s);

/* Insertion / Removal */

// Pushes an item onto the stack
void gen_stack_push(gen_stack_t* s, void* item);
// Pops the top item off the stack and returns it (NULL if empty)
void* gen_stack_pop(gen_stack_t* s);

/* Inspection / Queries */

// Returns true if the stack is empty
bool gen_stack_is_empty(const gen_stack_t* s);

#endif // GEN_STACK_H
