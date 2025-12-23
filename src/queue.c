#include "../include/queue.h"
#include "../include/linked_list.h"
#include <stdlib.h>
#include <stdbool.h>

queue_t* queue_create(void) {
    queue_t* q = (queue_t*) malloc(sizeof(queue_t));
    if (q == NULL) return NULL;
    q->list = LL_create();
    if (q->list == NULL) {
        free(q);
        return NULL;
    }
    return q;
}

void queue_clear(queue_t* q) {
    if (q == NULL) return;

    LL_clear(q->list);
}

void queue_free(queue_t* q) {
    if (q == NULL) return;
    
    LL_free(q->list);
    free(q);
}

void queue_enqueue(queue_t* q, int item) {
    if (q == NULL) return;
    LL_add_to_tail(q->list, item);
}

int queue_dequeue(queue_t* q) {
    if (q == NULL || LL_is_empty(q->list)) return -1;
    return LL_remove_from_head(q->list);
}

size_t queue_size(const queue_t* q) {
    // DO NOT USE THIS VERSION BUT INSTEAD THE VERSION BELOW IT FOR ASSIGNMENTS/EXAMS
    if (q == NULL) return 0;
    return LL_get_size(q->list);
    /* IMPORTANT: The following is how it is done if implementation is abstracted away (so for assignments/exams)
    if (q == NULL) return 0;
    size_t size = 0;
    queue_t* tmp = queue_create(); // Will create tmp q for putting elements back
    while (queue_is_empty(q) == false) { // While q is not empty fill tmp, empty q, and increment size
        queue_enqueue(tmp, queue_dequeue(q));
        size++;
    }
    while (queue_is_empty(tmp) == false) { // Filling back the queue
        queue_enqueue(q, queue_dequeue(tmp));
    }
    queue_free(tmp);
    */
}

bool queue_is_empty(const queue_t* q) {
    if (q == NULL) return true;
    return LL_is_empty(q->list);
}

bool queue_equal(const queue_t* q1, const queue_t* q2) {
    // DO NOT USE THIS VERSION BUT INSTEAD THE VERSION BELOW IT FOR ASSIGNMENTS/EXAMS
    if (q1 == q2) return true;
    if (q1 == NULL || q2 == NULL) return false;
    return LL_are_equal(q1->list, q2->list);
    /* IMPORTANT: The following is how it is done if implementation is abstracted away (so for assignments/exams)
    if (q1 == q2) return true;
    if (q1 == NULL || q2 == NULL) return false;
    bool is_equal = true;
    // Will creates two tmps because if they differ then putting them back together requires separate queues
    queue_t* tmp1 = queue_create(); 
    queue_t* tmp2 = queue_create(); 
    while(queue_is_empty(q1) == false && queue_is_empty(q2) == false) {
        int val1 = queue_dequeue(q1);
        int val2 = queue_dequeue(q2);
        queue_enqueue(tmp1, val1);
        queue_enqueue(tmp2, val2);
        if (val1 != val2) {
            is_equal = false;
            break;
        }
    }

    if (queue_is_empty(q1) != queue_is_empty(q2)) is_equal = false; // If one runs out first then not equal

    // Filling back the queues
    while (queue_is_empty(tmp1) == false) {
        queue_enqueue(q1, queue_dequeue(tmp1));
    }
    queue_free(tmp1);
    while (queue_is_empty(tmp2) == false) {
        queue_enqueue(q2, queue_dequeue(tmp2));
    }
    queue_free(tmp2);

    return is_equal;
    */
}
