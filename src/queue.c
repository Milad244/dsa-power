#include "../include/queue.h"
#include <stdlib.h>

queue_t* queue_create(void) {
    queue_t* q = (queue_t*) malloc(sizeof(queue_t));
    if (q == NULL) return NULL;
    q->list = LL_create();
    return q;
}

void enqueue(queue_t* q, int item) {
    if (q == NULL) return;
    LL_add_to_tail(q->list, item);
}

int dequeue(queue_t* q) {
    if (q == NULL) return -1;
    return LL_remove_from_head(q->list);
}

bool queue_is_empty(queue_t* q) {
    if (q == NULL || q->list == NULL || q->list->head == NULL) return true;
    return false;
}

int queue_size(queue_t* q) {
  if (q == NULL) return 0;
  // Will create tmp q for putting elements back
  int size = 0;
  queue_t* tmp = queue_create(); // Hopefully not null
  while (queue_is_empty(q) == false) { // While q is not empty fill tmp and empty q and increment size
    enqueue(tmp, dequeue(q));
    size++;
  }
  while (queue_is_empty(tmp) == false) { // Filling back the queue
    enqueue(q, dequeue(tmp));
  }
  free(tmp);

  return size;
}

bool queue_equal(queue_t* q1, queue_t* q2) {
  bool is_equal = true;
  // Will creates two tmps because if they differ then putting them back together requires separate queues
  queue_t* tmp1 = queue_create(); 
  queue_t* tmp2 = queue_create(); 
  while(queue_is_empty(q1) == false && queue_is_empty(q2) == false) {
    int val1 = dequeue(q1);
    int val2 = dequeue(q2);
    enqueue(tmp1, val1);
    enqueue(tmp2, val2);
    if (val1 != val2) {
      is_equal = false;
      break;
    }
  }

  if (queue_is_empty(q1) != queue_is_empty(q2)) is_equal = false; // If one runs out first then not equal

  // Filling back the queues
  while (queue_is_empty(tmp1) == false) {
    enqueue(q1, dequeue(tmp1));
  }
  free(tmp1);
  while (queue_is_empty(tmp2) == false) {
    enqueue(q2, dequeue(tmp2));
  }
  free(tmp2);

  return is_equal;
}

void queue_free(queue_t* q) {
    if (q == NULL) return;

    while (queue_is_empty(q) == 0) {
        dequeue(q);
    }
    
    free(q);
}
