#include "../include/queue.h"
#include <stdlib.h>

// Creates a new empty queue
queue_t* create_queue(void) {
    queue_t* q = (queue_t*) malloc(sizeof(queue_t));
    if (q == NULL) return NULL;
    q->list = create_linked_list();
    return q;
}

// Enqueues an item to the back of the queue
void enqueue(queue_t* q, int item) {
    if (q == NULL) return;
    add_to_tail(q->list, item);
}

// Dequeues an item from the front of the queue and returns it (-1 if empty)
int dequeue(queue_t* q) {
    if (q == NULL) return -1;
    return remove_from_head(q->list);
}

// Checks if the queue is empty
bool queue_isEmpty(queue_t* q) {
    if (q == NULL || q->list == NULL || q->list->head == NULL) return true;
    return false;
}
