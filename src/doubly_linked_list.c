#include "../include/doubly_linked_list.h"
#include <stdlib.h>

DLL_t* DLL_create(void) {
    DLL_t* list = (DLL_t*) malloc(sizeof(DLL_t));
    if (list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    return list;
}

void DLL_clear(DLL_t* list) {
    if (list == NULL) return;

    dnode_t* node = list->head;
    while (node != NULL) {
        dnode_t* tmp = node;
        node = node->next;
        free(tmp);
    }

    list->head = NULL;
    list->tail = NULL;
}

void DLL_free(DLL_t* list) {
    if (list == NULL) return;
    
    DLL_clear(list);
    free(list);
}

void DLL_add_to_front(DLL_t* list, int item) {
    if (list == NULL) return;

    dnode_t* node = (dnode_t*) malloc(sizeof(dnode_t));
    if (node == NULL) return;
    node->data = item;
    node->prev = NULL;

    if (list->head == NULL) { // Handling empty list
        list->head = node;
        list->tail = node;
        node->next = NULL;
    } else { // Handling non-empty list
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
}

void DLL_add_to_end(DLL_t* list, int item) {
    if (list == NULL) return;

    dnode_t* node = (dnode_t*) malloc(sizeof(dnode_t));
    if (node == NULL) return;
    node->data = item;
    node->next = NULL;

    if (list->tail == NULL) { // Handling empty list
        list->head = node;
        list->tail = node;
        node->prev = NULL;
    } else { // Handling non-empty list
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
}

int DLL_remove_from_front(DLL_t* list) {
    if (list == NULL || list->head == NULL) return -1;
    
    dnode_t* node = list->head;
    int data = node->data;

    if (list->head->next == NULL) { // Handling one element
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }

    free(node);
    return data;
}

int DLL_remove_from_end(DLL_t* list) {
    if (list == NULL || list->tail == NULL) return -1;
    
    dnode_t* node = list->tail;
    int data = node->data;
    
    if (list->tail->prev == NULL) { // Handling one element
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    free(node);
    return data;
}
