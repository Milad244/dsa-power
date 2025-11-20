#ifndef VLA_H
#define VLA_H

#include <stddef.h>
#include <stdbool.h>

// Generic variable-length array (VLA) structure
typedef struct VLA {
    void** data;      // Pointer to array of elements
    size_t size;      // Current number of elements
    size_t capacity;  // Allocated capacity
} VLA_t;

// Creates a new empty VLA
VLA_t* vla_create(void);

// Adds an element to the end of the VLA
void vla_push_back(VLA_t* vla, void* value);

// Adds an element to the front of the VLA
void vla_push_front(VLA_t* vla, void* value);

// Removes and returns the last element (NULL if empty)
void* vla_pop_back(VLA_t* vla);

// Removes and returns the first element (NULL if empty)
void* vla_pop_front(VLA_t* vla);

// Returns the last element without removing it (NULL if empty)
void* vla_peek_back(VLA_t* vla);

// Returns the first element without removing it (NULL if empty)
void* vla_peek_front(VLA_t* vla);

// Gets element at a given index (NULL if out of bounds)
void* vla_get(VLA_t* vla, size_t index);

// Sets element at a given index (no-op if out of bounds)
void vla_set(VLA_t* vla, size_t index, void* value);

// Returns true if VLA is empty
bool vla_is_empty(VLA_t* vla);

// Returns current number of elements
size_t vla_size(VLA_t* vla);

// Frees the VLA structure (does not free the stored elements)
void vla_free(VLA_t* vla);

#endif // VLA_H
