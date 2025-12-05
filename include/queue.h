#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "linked_list.h"

// Queue definition (using linked list with head and tail)
typedef struct Queue {
    LL_t* list;
} queue_t;

// Creates a new queue
queue_t* queue_create(void);

// Enqueues an item to the back of the queue
void enqueue(queue_t* q, int item);

// Dequeues an item from the front of the queue and returns it (-1 if empty)
int dequeue(queue_t* q);

// Checks if the queue is empty
bool queue_is_empty(queue_t* q);

// Returns the number of items in queue (0 if NULL)
int queue_size(queue_t* q);

// Checks if two queues are equal
bool queue_equal(queue_t* q1, queue_t* q2);

// Frees the entire queue
void queue_free(queue_t* q);

#endif // QUEUE_H
