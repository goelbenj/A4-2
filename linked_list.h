#include <iostream>
#include <thread>
#include <mutex>


struct Node {
    int value;
    Node* next;
    std::mutex m;  // lock for node
};

struct List {
    Node* head;  // point to head-node of the whole linked-list
    bool lock_st;  // lock status field for the whole linked-list
    std::mutex m;  // lock for whole linked-list
};

void insert_glock_sort(List* head_ref, int new_value);
void insert_flock_sort(List* head_ref, int new_value);

void print_list(List* head_ref);
