#include "gen_stack.h"
#include "vla.h"
#include <stdlib.h>
#include <stdbool.h>

gen_stack_t* gen_stack_create(void) {
    gen_stack_t* s = (gen_stack_t*) malloc(sizeof(gen_stack_t));
    if (s == NULL) return NULL;
    s->vla = VLA_create();
    if (s->vla == NULL) {
        free(s);
        return NULL;
    }
    return s;
}

void gen_stack_clear(gen_stack_t* s) {
    if (s == NULL) return;

    VLA_clear(s->vla);
}

void gen_stack_free(gen_stack_t* s) {
    if (s == NULL) return;

    VLA_free(s->vla);
    free(s);
}

void gen_stack_push(gen_stack_t* s, void* item) {
    if (s == NULL) return;
    VLA_push_back(s->vla, item);
}

void* gen_stack_pop(gen_stack_t* s) {
    if (s == NULL) return NULL;
    return VLA_pop_back(s->vla);
}

bool gen_stack_is_empty(const gen_stack_t* s) {
    if (s == NULL) return true;
    return VLA_is_empty(s->vla);
}
