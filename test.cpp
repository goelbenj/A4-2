#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include "linked_list.h"


int main(int argc, char* argv[]) {
    List* list = new List();
    insert_glock_sort(list, 40);
    insert_glock_sort(list, 50);
    insert_glock_sort(list, 100);
    insert_glock_sort(list, 120);
    insert_glock_sort(list, 160);
    insert_glock_sort(list, 180);
    print_list(list);

    // perform simultaneous insertions
    constexpr int num_insertions = 2;
    std::thread threads[num_insertions];
    int values[num_insertions] = {65, 77};
    for (int i = 0; i < num_insertions; i++) {
        threads[i] = std::thread(insert_glock_sort, list, values[i]);
    }

    for (auto& th : threads) th.join();
    print_list(list);

    return 0;
}
