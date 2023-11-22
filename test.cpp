#include <chrono>         // std::chrono
#include <iomanip>
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include "linked_list.h"


double coarse_vs_fine_test(void (*insertion_func)(List *, int), int num_insertions, int *values) {
    List* list = new List();
    insertion_func(list, 40);
    insertion_func(list, 50);
    insertion_func(list, 100);
    insertion_func(list, 120);
    insertion_func(list, 160);
    insertion_func(list, 180);

    // perform simultaneous insertions using global lock
    std::thread threads[num_insertions];
    // start timer
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_insertions; i++) {
        threads[i] = std::thread(insertion_func, list, values[i]);
    }

    for (auto& th : threads) th.join();
    auto stop = std::chrono::high_resolution_clock::now();
    print_list(list);
    double diff = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
    diff *= 1e-9;
    return diff;
}

int main(int argc, char* argv[]) {
    // perform simultaneous insertions using global lock
    constexpr int num_insertions = 2;
    int values[num_insertions] = {65, 77};
    double duration = coarse_vs_fine_test(insert_glock_sort, num_insertions, values);
    std::cout << "Total duration: " << std::setw(9)
                  << duration << " seconds\n";

    // perform simultaneous insertions using fine-grained lock
    duration = coarse_vs_fine_test(insert_flock_sort, num_insertions, values);
    std::cout << "Total duration: " << std::setw(9)
                  << duration << " seconds\n";
    return 0;
}
