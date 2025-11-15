#include "../include/linked_list.h"
#include <stdlib.h>

// Creates a new empty linked list
LL_t* create_linked_list(void) {
    LL_t* list = (LL_t*) malloc(sizeof(LL_t));
    if (list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Adds a new element at the head of the list
void add_to_head(LL_t* list, int item) {
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

// Adds a new element at the tail of the list
void add_to_tail(LL_t* list, int item) {
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

// Removes the head element and returns its value (-1 if empty)
int remove_from_head(LL_t* list) {
    if (list == NULL || list->head == NULL) return -1;
    
    node_t* node = list->head;
    list->head = list->head->next;
    if (list->head == NULL) list->tail = NULL; // Handling edge case where list becomes empty
    int data = node->data;
    free(node);
    return data;
}

// Removes the tail element and returns its value (-1 if empty)
int remove_from_tail(LL_t* list) {
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

// Frees the entire linked list
void free_linked_list(LL_t* list) {
    if (list == NULL) return;

    node_t* node = list->head;
    while (node != NULL) {
        node_t* tmp = node;
        node = node->next;
        free(tmp);
    }
    free(list);
}

/* This was code for linked_list without tail
LL_t* create_linked_list(void) {
    LL_t* list = (LL_t*) malloc(sizeof(LL_t));
    if (list == NULL) return NULL;

    list->head = NULL;
    return list;
}

void add_to_head(LL_t* list, int item) {
    if (list == NULL) return;

    node_t* node = (node_t*) malloc(sizeof(node_t));
    if (node == NULL) return;

    node->data = item;
    node->next = list->head; // New node points to old head
    list->head = node; // New node becomes head
}

void add_to_tail(LL_t* list, int item) {
    if (list == NULL) return;

    node_t* node = (node_t*) malloc(sizeof(node_t));
    if (node == NULL) return;
    node->data = item;
    node->next = NULL;

    node_t* curr = list->head;
    if (curr == NULL) {
        list->head = node;
        return;
    }
    while (curr->next != NULL) curr = curr->next;
    curr->next = node;
}

int remove_from_head(LL_t* list) {
    if (list == NULL || list->head == NULL) return -1;

    node_t* tmp = list->head;
    list->head = list->head->next;
    int data = tmp->data;
    free(tmp);
    return data;
}

int remove_from_tail(LL_t* list) {
    if (list == NULL || list->head == NULL) return -1;

    // If only 1 element
    if (list->head->next == NULL) {
        node_t* node = list->head;
        int data = node->data;
        list->head = NULL;
        free(node);
        return data;
    }

    // Otherwise going to the last element
    node_t* prev = list->head;
    node_t* curr = prev->next;
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = NULL;
    int data = curr->data;
    free(curr);
    return data;
}
*/