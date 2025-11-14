#include "../include/stack.h"
#include <stdlib.h>

// Creates a new empty stack
Stack_t* create_stack(void) {
    Stack_t* s = (Stack_t*) malloc(sizeof(Stack_t));
    if (s == NULL) return NULL;
    s->list = create_linked_list();
    return s;
}

// Pushes an item onto the stack
void push(Stack_t* s, int item) {
    if (s == NULL) return;
    add_to_head(s->list, item);
}

// Pops an item from the stack and returns it (-1 if empty)
int pop(Stack_t* s) {
    if (s == NULL) return -1;
    return remove_from_head(s->list);
}

// Checks if the stack is empty
bool stack_isEmpty(Stack_t* s) {
    if (s == NULL || s->list == NULL || s->list->head == NULL) return true;
    return false;
}
