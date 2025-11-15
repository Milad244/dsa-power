#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "linked_list.h"

// Queue definition (using linked list with head and tail)
typedef struct Queue {
    LL_t* list;
} queue_t;

// Creates a new empty queue
queue_t* create_queue(void);

// Enqueues an item to the back of the queue
void enqueue(queue_t* q, int item);

// Dequeues an item from the front of the queue and returns it (-1 if empty)
int dequeue(queue_t* q);

// Checks if the queue is empty
bool queue_isEmpty(queue_t* q);

// Frees the entire queue
void free_queue(queue_t* q);

#endif // QUEUE_H
