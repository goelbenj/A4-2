#include <mutex>
#include "linked_list.h"

// Given a reference (pointer to pointer)
// to the head_ref of a list and an int,
// inserts a new node into the correct position
// in the ascending pattern.
void insert_sort(List* list, int new_value) {
    // 1. allocate node
    Node* new_node = new Node();
 
    // 2. put in the data
    new_node->value = new_value;
    
    // 3. acquire lock for entire list
    std::unique_lock<std::mutex> list_lock(list->lock_st, std::defer_lock);
    std::lock(list_lock);

    // 4. if linked list is empty
    Node* head_ref = list->head;
    if (head_ref == NULL || head_ref->value >= new_node->value) {
        new_node->next = head_ref;
        list->head = new_node;
        return;
    }

    // 5. locate the node before insertion
    Node *current = head_ref;
    while (current->next != NULL && current->next->value < new_node->value)
        current = current->next;

    new_node->next = current->next;
    current->next = new_node;
}

void print_list(List* list) {
    Node* curr = list->head;
    int i = 0;
    while (curr != NULL) {
        printf("Node %i: {%i}\n", i, curr->value);
        curr = curr->next;
        ++i;
    }
}