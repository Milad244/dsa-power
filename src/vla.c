#include "../include/vla.h"
#include <stdlib.h>
#include <stdbool.h>

VLA_t* VLA_create(void) {
    VLA_t* vla = (VLA_t*) malloc(sizeof(VLA_t));
    if (vla == NULL) return NULL;

    vla->capacity = 0;
    vla->size = 0;
    vla->data = NULL;

    return vla;
}

void VLA_clear(VLA_t* vla) {
    if (vla == NULL) return;
    
    free(vla->data);
    vla->data = NULL;
    vla->capacity = 0;
    vla->size = 0;
}

void VLA_free(VLA_t* vla) {
    if (vla == NULL) return;
    
    VLA_clear(vla);
    free(vla);
}

// Helper function that returns true if it made sure VLA has enough capacity
static bool VLA_handle_capacity(VLA_t* vla) {
    if (vla == NULL) return false;

    if (vla->data == NULL) { // dealing with empty case
        vla->capacity = VLA_MIN_CAPACITY;
        vla->data = (void**) malloc(sizeof(void*) * vla->capacity);
        if (vla->data == NULL) return false;
    }

    if (vla->size >= vla->capacity) { // size at capacity handling
        vla->capacity = vla->capacity * 2;
        void** tmp = (void**) realloc(vla->data, sizeof(void*) * vla->capacity);
        if (tmp == NULL) return false;
        vla->data = tmp;
    }

    return true;
}

void VLA_push_back(VLA_t* vla, void* value) {
    if (VLA_handle_capacity(vla) == false) return;

    vla->data[vla->size] = value;
    vla->size++;
}

void VLA_push_front(VLA_t* vla, void* value) {
    if (VLA_handle_capacity(vla) == false) return;

    for (size_t i = vla->size; i > 0; i--) { // shifting all elements up 1
        vla->data[i] = vla->data[i - 1];
    }
    vla->data[0] = value;
    vla->size++;
}

void* VLA_pop_back(VLA_t* vla) {
    if (vla == NULL || vla->size == 0) return NULL;

    void* res = vla->data[vla->size - 1];
    vla->size--;
    return res;
}

void* VLA_pop_front(VLA_t* vla) {
    if (vla == NULL || vla->size == 0) return NULL;

    void* res = vla->data[0];
    for (size_t i = 0; i < vla->size - 1; i++) { // shifting all elements down 1
        vla->data[i] = vla->data[i + 1];
    }
    vla->size--;
    return res;
}

size_t VLA_size(const VLA_t* vla) {
    if (vla == NULL) return 0;
    else return vla->size;
}

bool VLA_is_empty(const VLA_t* vla) {
    if (vla == NULL || vla->size == 0) return true;
    else return false;
}

void* VLA_peek_back(const VLA_t* vla) {
    if (vla == NULL || vla->size == 0) return NULL;

    return vla->data[vla->size - 1];
}

void* VLA_peek_front(const VLA_t* vla) {
    if (vla == NULL || vla->size == 0) return NULL;

    return vla->data[0];
}

void* VLA_get(const VLA_t* vla, size_t index) {
    if (vla == NULL || index >= vla->size) return NULL;
    
    return vla->data[index];
}

void VLA_set(VLA_t* vla, size_t index, void* value) {
    if (vla == NULL || index >= vla->size) return;
    
    vla->data[index] = value;
}
