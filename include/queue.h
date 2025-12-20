#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include "../include/linked_list.h"

// Queue definition (using linked list with head and tail)
typedef struct Queue {
    LL_t* list;
} queue_t;

/* Construction / Destruction */

// Creates a new empty queue
queue_t* queue_create(void);
// Frees all items but keeps the queue
void queue_clear(queue_t* q);
// Frees the entire queue
void queue_free(queue_t* q);

/* Insertion / Removal */

// Enqueues an item to the back of the queue
void queue_enqueue(queue_t* q, int item);
// Dequeues an item from the front of the queue and returns it (-1 if empty)
int queue_dequeue(queue_t* q);

/* Inspection / Queries */

// Returns the number of items in queue (0 if NULL)
size_t queue_size(const queue_t* q);
// Checks if the queue is empty
bool queue_is_empty(const queue_t* q);
// Checks if two queues are equal
bool queue_equal(const queue_t* q1, const queue_t* q2);

#endif // QUEUE_H
