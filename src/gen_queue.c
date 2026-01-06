#include "gen_queue.h"
#include "vla.h"
#include <stdlib.h>
#include <stdbool.h>

gen_queue_t* gen_queue_create(void) {
    gen_queue_t* q = (gen_queue_t*) malloc(sizeof(gen_queue_t));
    if (q == NULL) return NULL;
    q->vla = VLA_create();
    if (q->vla == NULL) {
        free(q);
        return NULL;
    }
    return q;
}

void gen_queue_clear(gen_queue_t* q) {
    if (q == NULL) return;

    VLA_clear(q->vla);
}

void gen_queue_free(gen_queue_t* q) {
    if (q == NULL) return;
    
    VLA_clear(q->vla);
    free(q);
}

void gen_queue_enqueue(gen_queue_t* q, void* item) {
    if (q == NULL) return;
    VLA_push_back(q->vla, item);
}

void* gen_queue_dequeue(gen_queue_t* q) {
    if (q == NULL) return NULL;
    return VLA_pop_front(q->vla);
}

bool gen_queue_is_empty(const gen_queue_t* q) {
    if (q == NULL) return true;
    return VLA_is_empty(q->vla);
}
