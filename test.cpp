#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include "linked_list.h"


int main(int argc, char* argv[]) {
    List* list = new List();
    insert_sort(list, 40);
    insert_sort(list, 50);
    insert_sort(list, 100);
    insert_sort(list, 120);
    insert_sort(list, 160);
    insert_sort(list, 180);
    print_list(list);

}
