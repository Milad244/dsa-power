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
    LL_t* ll = create_linked_list();
    add_to_head(ll, 10);
    add_to_tail(ll, 20);
    printf("Removed from head: %d\n", remove_from_head(ll));
    printf("Removed from tail: %d\n", remove_from_tail(ll));

    // ----------------------------
    // Doubly Linked List
    // ----------------------------
    DLL_t* dll = create_DLL();
    add_to_front(dll, 30);
    add_to_end(dll, 40);
    printf("Removed from front: %d\n", remove_from_front(dll));
    printf("Removed from end: %d\n", remove_from_end(dll));

    // ----------------------------
    // Stack
    // ----------------------------
    Stack_t* s = create_stack();
    push(s, 1);
    push(s, 2);
    printf("Popped from stack: %d\n", pop(s));
    printf("Stack empty? %s\n", stack_isEmpty(s) ? "Yes" : "No");

    // ----------------------------
    // Queue
    // ----------------------------
    queue_t* q = create_queue();
    enqueue(q, 100);
    enqueue(q, 200);
    printf("Dequeued from queue: %d\n", dequeue(q));
    printf("Queue empty? %s\n", queue_isEmpty(q) ? "Yes" : "No");

    // ----------------------------
    // Binary Tree
    // ----------------------------
    BinaryTree_t* tree = create_binary_tree();
    BTNode_t* root = create_node(10);
    tree->root = root;

    BTNode_t* left = create_node(5);
    BTNode_t* right = create_node(15);

    insert_left(root, left);
    insert_right(root, right);

    printf("Inorder traversal: ");
    inorder_traversal(tree->root);
    printf("\n");

    printf("Preorder traversal: ");
    preorder_traversal(tree->root);
    printf("\n");

    printf("Postorder traversal: ");
    postorder_traversal(tree->root);
    printf("\n");

    // Free all structures
    free_linked_list(ll);
    free_DLL(dll);
    free_stack(s);
    free_queue(q);
    free_tree(tree);

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

    // Searching example
    int target = 8;
    int index = linear_search(arr, n, target);
    printf("Linear search for %d: %d\n", target, index);

    return 0;
}
