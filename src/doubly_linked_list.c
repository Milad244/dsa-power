#include "../include/doubly_linked_list.h"
#include <stdlib.h>

// Creates a new empty doubly-linked list
DLL_t* create_DLL(void) {
    DLL_t* list = (DLL_t*) malloc(sizeof(DLL_t));
    if (list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Adds a new element at the front of the list
void add_to_front(DLL_t* list, int item) {
    if (list == NULL) return;

    dnode_t* node = (dnode_t*) malloc(sizeof(dnode_t));
    if (node == NULL) return;
    node->data = item;
    node->prev = NULL;

    // Handling empty list
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
        node->next = NULL;
    } else { // Handling non-empty
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
}

// Adds a new element at the end of the list
void add_to_end(DLL_t* list, int item) {
    if (list == NULL) return;

    dnode_t* node = (dnode_t*) malloc(sizeof(dnode_t));
    if (node == NULL) return;
    node->data = item;
    node->next = NULL;

    // Handling empty list
    if (list->tail == NULL) {
        list->head = node;
        list->tail = node;
        node->prev = NULL;
    } else { // Handling non-empty
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
}

// Removes the front element and returns its value (-1 if empty)
int remove_from_front(DLL_t* list) {
    if (list == NULL || list->head == NULL) return -1;
    
    dnode_t* node = list->head;
    int data = node->data;
    // Handling one element
    if (list->head->next == NULL) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }

    free(node);
    return data;
}

// Removes the end element and returns its value (-1 if empty)
int remove_from_end(DLL_t* list) {
    if (list == NULL || list->tail == NULL) return -1;
    
    dnode_t* node = list->tail;
    int data = node->data;
    // Handling one element
    if (list->tail->prev == NULL) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    free(node);
    return data;
}
