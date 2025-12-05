#include <stdio.h>
#include "../include/linked_list.h"
#include "../include/doubly_linked_list.h"
#include "../include/stack.h"
#include "../include/queue.h"
#include "../include/search_sort.h"
#include "../include/binary_tree.h"

int main() {
    // ----------------------------
    // Linked List
    // ----------------------------
    LL_t* ll = LL_create();
    LL_add_to_head(ll, 10);
    LL_add_to_tail(ll, 20);
    printf("Removed from head: %d\n", LL_remove_from_head(ll));
    printf("Removed from tail: %d\n", LL_remove_from_tail(ll));

    // ----------------------------
    // Doubly Linked List
    // ----------------------------
    DLL_t* dll = DLL_create();
    DLL_add_to_front(dll, 30);
    DLL_add_to_end(dll, 40);
    printf("Removed from front: %d\n", DLL_remove_from_front(dll));
    printf("Removed from end: %d\n", DLL_remove_from_end(dll));

    // ----------------------------
    // Stack
    // ----------------------------
    Stack_t* s = stack_create();
    stack_push(s, 1);
    stack_push(s, 2);
    printf("Popped from stack: %d\n", stack_pop(s));
    printf("Stack empty? %s\n", stack_is_empty(s) ? "Yes" : "No");

    // ----------------------------
    // Queue
    // ----------------------------
    queue_t* q = queue_create();
    enqueue(q, 100);
    enqueue(q, 200);
    printf("Dequeued from queue: %d\n", dequeue(q));
    printf("Queue empty? %s\n", queue_is_empty(q) ? "Yes" : "No");

    // ----------------------------
    // Binary Tree
    // ----------------------------
    BinaryTree_t* tree = bt_create();
    BTNode_t* root = node_create(10);
    tree->root = root;

    BTNode_t* left = node_create(5);
    BTNode_t* right = node_create(15);

    node_insert_left(root, left);
    node_insert_right(root, right);

    printf("Inorder traversal: ");
    node_inorder_traversal(tree->root);
    printf("\n");

    printf("Preorder traversal: ");
    node_preorder_traversal(tree->root);
    printf("\n");

    printf("Postorder traversal: ");
    node_postorder_traversal(tree->root);
    printf("\n");

    // Free all structures
    LL_free(ll);
    DLL_free(dll);
    stack_free(s);
    queue_free(q);
    bt_free(tree);

    // ----------------------------
    // Sorting / Algorithms
    // ----------------------------
    int arr[] = {5, 2, 8, 1, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array before sorting: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    insertion_sort(arr, n);

    printf("Array after sorting: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    int target = 8;
    int index = linear_search(arr, n, target);
    printf("Linear search for %d: %d\n", target, index);

    return 0;
}
