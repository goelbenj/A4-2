#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include "linked_list.h"


int main(int argc, char* argv[]) {
    printf("JOE MAMA\n");

    List list = {NULL, 0};
    insert_sort(&list, 3);
    insert_sort(&list, 2);
    print_list(&list);

}
