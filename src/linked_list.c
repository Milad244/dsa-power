#include "../include/linked_list.h"
#include <stdlib.h>

LL_t* LL_create(void) {
    LL_t* list = (LL_t*) malloc(sizeof(LL_t));
    if (list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    return list;
}

void LL_add_to_head(LL_t* list, int item) {
    if (list == NULL) return;

    node_t* node = (node_t*) malloc(sizeof(node_t));
    if (node == NULL) return;
    node->data = item;
    if (list->head == NULL) { // If no items
        list->head = node;
        list->tail = node;
        node->next = NULL;
    } else {
        node->next = list->head; // New points to old head
        list->head = node; // New becomes head
    }
}

void LL_add_to_tail(LL_t* list, int item) {
    if (list == NULL) return;

    node_t* node = (node_t*) malloc(sizeof(node_t));
    if (node == NULL) return;
    node->data = item;
    node->next = NULL;
    if (list->tail == NULL) { // If no items
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node; // Old tail points to new tail
        list->tail = node; // New becomes tail
    }
}

int LL_remove_from_head(LL_t* list) {
    if (list == NULL || list->head == NULL) return -1;
    
    node_t* node = list->head;
    list->head = list->head->next;
    if (list->head == NULL) list->tail = NULL; // Handling edge case where list becomes empty
    int data = node->data;
    free(node);
    return data;
}

int LL_remove_from_tail(LL_t* list) {
    if (list == NULL || list->tail == NULL) return -1;

    // Handling 1 item edge case
    if (list->head->next == NULL) {
        node_t* node = list->head;
        int data = node->data;
        list->head = NULL;
        list->tail = NULL;
        free(node);
        return data;
    }

    node_t* prev = list->head;
    node_t* curr = prev->next;
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }
    list->tail = prev;
    prev->next = NULL;
    int data = curr->data;
    free(curr);
    return data;
}

void LL_free(LL_t* list) {
    if (list == NULL) return;

    node_t* node = list->head;
    while (node != NULL) {
        node_t* tmp = node;
        node = node->next;
        free(tmp);
    }
    free(list);
}
