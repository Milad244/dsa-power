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

size_t LL_get_size(LL_t* list) {
    if (list == NULL) return 0;

    size_t size = 0;
    node_t* curr = list->head;
    while (curr != NULL) {
        size++;
        curr = curr->next;
    }
    
    return size;
}

bool LL_are_equal(LL_t* list1, LL_t* list2) {
    if (list1 == list2) return true;
    if (list1 == NULL || list2 == NULL) return false;

    node_t* curr1 = list1->head, *curr2 = list2->head;
    while (curr1 != NULL && curr2 != NULL) {
        if (curr1->data != curr2->data) return false;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    
    if (curr1 != NULL || curr2 != NULL) return false; // one isn't empty
    return true; // both empty so equal
}

void LL_reverse(LL_t* list) {
    if (list == NULL) return;

    node_t* prev = NULL;
    node_t* curr = list->head;
    node_t* next = NULL;

    list->tail = curr;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list->head = prev;
}

void LL_map(LL_t* list, int (*map)(int)) {
    if (list == NULL) return;

    node_t* curr = list->head;
    while (curr != NULL) {
        curr->data = map(curr->data);
        curr = curr->next;
    }
}

node_t* LL_get_item(LL_t* list, int index) {
    if (list == NULL || index < 0) return NULL;

    int count = 0;
    node_t* curr = list->head;
    while (curr != NULL && count < index) {
        curr = curr->next;
        count++;
    }
    return curr;
}

node_t* LL_get_middle(LL_t* list) {
    if (list == NULL || list->head == NULL) return NULL;

    int count = 0;
    node_t* curr = list->head;
    while (curr != NULL) {
        curr = curr->next;
        count++;
    }

    int mid = count / 2;
    curr = list->head;
    count = 0;
    while (count < mid) {
        curr = curr->next;
        count++;
    }

    return curr;
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
