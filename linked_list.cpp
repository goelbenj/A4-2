#include <mutex>
#include "linked_list.h"

// Given a reference (pointer to pointer)
// to the head_ref of a list and an int,
// inserts a new node into the correct position
// in the ascending pattern.
void insert_glock_sort(List* list, int new_value) {
    // 1. allocate node
    Node* new_node = new Node();
 
    // 2. put in the data
    new_node->value = new_value;
    
    // 3. acquire lock for entire list
    list->m.lock();

    // 4. if linked list is empty
    Node* head_ref = list->head;
    if (head_ref == NULL || head_ref->value >= new_node->value) {
        new_node->next = head_ref;
        list->head = new_node;
        // release lock
        list->m.unlock();
        return;
    }

    // 5. locate the node before insertion
    Node *current = head_ref;
    while (current->next != NULL && current->next->value < new_node->value)
        current = current->next;

    new_node->next = current->next;
    current->next = new_node;

    // 6. release lock
    list->m.unlock();
}

void insert_flock_sort(List* list, int new_value) {
    // 1. allocate node
    Node* new_node = new Node();

    // 2. put in the data
    new_node->value = new_value;

    // 3. acquire lock for entire list
    list->m.lock();

    // 4. if linked list is empty
    Node* head_ref = list->head;
    if (head_ref == NULL || head_ref->value >= new_node->value) {
        new_node->next = head_ref;
        list->head = new_node;
        // release lock
        list->m.unlock();
        return;
    }
    list->m.unlock();

    // 5. acquire lock for head and next
    Node *current = list->head;
    current->m.lock();
    if (current->next != NULL) {
        current->next->m.lock();
    }

    // 6. locate the node before insertion
    while (current->next != NULL && current->next->value < new_node->value) {
        current = current->next;
        current->m.unlock();
        current->next->m.lock();
    }

    new_node->next = current->next;
    current->next = new_node;

    // 7. release lock
    current->next->m.unlock();
}

// void delete_glock(List* list, Node* del_node) {
//     // 0. return if node does not exist
//     if (del_node == NULL) return;

//     // 1. acquire lock for entire list
//     list->m.lock();

//     // 2. traverse list for node
//     Node* prev_node = NULL;
//     Node* curr_node = list->head;
//     while (curr_node != NULL) {
//         if (curr_node == del_node) {
//             // if (prev_node == )
//             // prev_node->next = curr_node->next;
//         }
//         prev_node = curr_node;
//         curr_node = curr_node->next;
//     }
    
//     // 3. node not found
//     if (curr_node)
    
// }

void print_list(List* list) {
    Node* curr = list->head;
    int i = 0;
    while (curr != NULL) {
        printf("Node %i: {%i}\n", i, curr->value);
        curr = curr->next;
        ++i;
    }
    printf("----------\n");
}