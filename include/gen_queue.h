#ifndef GEN_QUEUE_H
#define GEN_QUEUE_H

#include <stdbool.h>
#include "vla.h"

// General queue definition (using VLA)
typedef struct gen_queue {
    VLA_t* vla;
} gen_queue_t;

/* Construction / Destruction */

// Creates a new empty queue
gen_queue_t* gen_queue_create(void);
// Frees all items but keeps the queue
void gen_queue_clear(gen_queue_t* q);
// Frees the entire queue
void gen_queue_free(gen_queue_t* q);

/* Insertion / Removal */

// Enqueues an item to the back of the queue
void gen_queue_enqueue(gen_queue_t* q, void* item);
// Dequeues an item from the front of the queue and returns it (NULL if empty)
void* gen_queue_dequeue(gen_queue_t* q);

/* Inspection / Queries */

// Checks if the queue is empty
bool gen_queue_is_empty(const gen_queue_t* q);

#endif // GEN_QUEUE_H
