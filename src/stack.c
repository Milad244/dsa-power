#include "../include/stack.h"
#include <stdlib.h>

Stack_t* stack_create(void) {
    Stack_t* s = (Stack_t*) malloc(sizeof(Stack_t));
    if (s == NULL) return NULL;
    s->list = LL_create();
    return s;
}

void stack_push(Stack_t* s, int item) {
    if (s == NULL) return;
    LL_add_to_head(s->list, item);
}

int stack_pop(Stack_t* s) {
    if (s == NULL) return -1;
    return LL_remove_from_head(s->list);
}

bool stack_is_empty(Stack_t* s) {
    if (s == NULL || s->list == NULL || s->list->head == NULL) return true;
    return false;
}

void stack_free(Stack_t* s) {
    if (s == NULL) return;

    while (stack_is_empty(s) == 0) {
        stack_pop(s);
    }

    free(s);
}
