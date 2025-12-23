#include "../include/stack.h"
#include "../include/linked_list.h"
#include <stdlib.h>
#include <stdbool.h>

Stack_t* stack_create(void) {
    Stack_t* s = (Stack_t*) malloc(sizeof(Stack_t));
    if (s == NULL) return NULL;
    s->list = LL_create();
    if (s->list == NULL) {
        free(s);
        return NULL;
    }
    return s;
}

void stack_clear(Stack_t* s) {
    if (s == NULL) return;

    LL_clear(s->list);
}

void stack_free(Stack_t* s) {
    if (s == NULL) return;

    LL_free(s->list);
    free(s);
}

void stack_push(Stack_t* s, int item) {
    if (s == NULL) return;
    LL_add_to_head(s->list, item);
}

int stack_pop(Stack_t* s) {
    if (s == NULL) return -1;
    return LL_remove_from_head(s->list);
}

size_t stack_size(const Stack_t* s) {
    // DO NOT USE THIS VERSION BUT INSTEAD THE VERSION BELOW IT FOR ASSIGNMENTS/EXAMS
    if (s == NULL) return 0;
    return LL_get_size(s->list);
    /* IMPORTANT: The following is how it is done if implementation is abstracted away (so for assignments/exams)
    if (s == NULL) return 0;
    size_t size = 0;
    Stack_t* tmp = stack_create(); // Will create tmp stack for putting elements back
    while (stack_is_empty(s) == false) { // While stack is not empty fill tmp, empty stack, and increment size
        stack_push(tmp, stack_pop(s));
        size++;
    }
    while (stack_is_empty(s) == false) { // Filling back the stack
        stack_push(s, stack_pop(tmp));
    }
    stack_free(tmp);
    */
}

bool stack_is_empty(const Stack_t* s) {
    if (s == NULL) return true;
    return LL_is_empty(s->list);
}

bool stack_equal(const Stack_t* s1, const Stack_t* s2) {
    if (s1 == s2) return true;
    if (s1 == NULL || s2 == NULL) return false;
    return LL_are_equal(s1->list, s2->list);
    /* IMPORTANT: The following is how it is done if implementation is abstracted away (so for assignments/exams)
    if (s1 == s2) return true;
    if (s1 == NULL || s2 == NULL) return false;
    bool is_equal = true;
    // Will creates two tmps because if they differ then putting them back together requires separate stacks
    Stack_t* tmp1 = stack_create(); 
    Stack_t* tmp2 = stack_create(); 
    while(stack_is_empty(s1) == false && queue_is_empty(s2) == false) {
        int val1 = stack_pop(s1);
        int val2 = stack_pop(s2);
        stack_push(tmp1, val1);
        stack_push(tmp2, val2);
        if (val1 != val2) {
            is_equal = false;
            break;
        }
    }

    if (stack_is_empty(s1) != stack_is_empty(s2)) is_equal = false; // If one runs out first then not equal

    // Filling back the stacks
    while (queue_is_empty(tmp1) == false) {
        stack_push(s1, stack_pop(tmp1));
    }
    stack_free(tmp1);
    while (queue_is_empty(tmp2) == false) {
        stack_push(s2, stack_pop(tmp2));
    }
    stack_free(tmp2);

    return is_equal;
    */
}