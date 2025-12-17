#ifndef VLA_H
#define VLA_H

#include <stdbool.h>
#include <stddef.h>
#define VLA_MIN_CAPACITY 4

// Generic variable-length array (VLA) structure
typedef struct VLA {
    void** data;      // Pointer to array of elements
    size_t size;      // Current number of elements
    size_t capacity;  // Allocated capacity
} VLA_t;

/* Construction / Destruction */

// Creates a new empty VLA
VLA_t* VLA_create(void);
// Clears all elements but keeps the VLA
void VLA_clear(VLA_t* vla);
// Frees the entire VLA structure
void VLA_free(VLA_t* vla);

/* Insertion / Removal */

// Adds a new element at the end
void VLA_push_back(VLA_t* vla, void* value);
// Adds a new element at the front
void VLA_push_front(VLA_t* vla, void* value);
// Removes and returns the last element (NULL if empty)
void* VLA_pop_back(VLA_t* vla);
// Removes and returns the first element (NULL if empty)
void* VLA_pop_front(VLA_t* vla);

/* Inspection / Queries */

// Gets the current number of elements (0 if NULL)
size_t VLA_size(VLA_t* vla);
// Checks if the VLA is empty
bool VLA_is_empty(VLA_t* vla);
// Returns the last element without removing it (NULL if empty)
void* VLA_peek_back(VLA_t* vla);
// Returns the first element without removing it (NULL if empty)
void* VLA_peek_front(VLA_t* vla);
// Gets element at a given index (NULL if out of bounds)
void* VLA_get(VLA_t* vla, size_t index);
// Sets element at a given index (no-op if out of bounds)
void VLA_set(VLA_t* vla, size_t index, void* value);

#endif // VLA_H
