#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include "linked_list.h"


void coarse_vs_fine_test(void (*insertion_func)(List *, int), int num_insertions, int *values) {
    List* list = new List();
    insertion_func(list, 40);
    insertion_func(list, 50);
    insertion_func(list, 100);
    insertion_func(list, 120);
    insertion_func(list, 160);
    insertion_func(list, 180);

    // perform simultaneous insertions using global lock
    std::thread threads[num_insertions];
    for (int i = 0; i < num_insertions; i++) {
        threads[i] = std::thread(insertion_func, list, values[i]);
    }

    for (auto& th : threads) th.join();
    print_list(list);
}

int main(int argc, char* argv[]) {
    // perform simultaneous insertions using global lock
    constexpr int num_insertions = 2;
    int values[num_insertions] = {65, 77};
    coarse_vs_fine_test(insert_glock_sort, num_insertions, values);

    // perform simultaneous insertions using fine-grained lock
    coarse_vs_fine_test(insert_flock_sort, num_insertions, values);
    return 0;
}
