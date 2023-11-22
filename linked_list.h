#include <iostream>
#include <thread>
#include <mutex>


struct Node {
    int value;
    Node* next;
};

struct List {
    Node* head;  // point to head-node of the whole linked-list
    std::mutex lock_st;  // lock status field for the whole linked-list
};

void insert_sort(List* head_ref, int new_value);

void print_list(List* head_ref);
