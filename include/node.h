#ifndef NODE_H
#define NODE_H

// Basic node for int data
typedef struct node {
    int data;
    struct node* next;
} node_t;

#endif // NODE_H
