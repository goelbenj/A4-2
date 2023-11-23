#include <atomic>
#include <chrono>         // std::chrono
#include <iomanip>
#include <iostream>       // std::cout

class Spinlock {
public:
    Spinlock() {
        flag.clear(); // Initialize the atomic_flag to clear (unlocked) state
    }

    int lock() {
        // record time spend spinning
        bool status = flag.test_and_set(std::memory_order_acquire);
        if (status == true) {
            int counter = 0;
            // start timer
            auto start = std::chrono::high_resolution_clock::now();
            while (status) {
                counter++;
                status = flag.test_and_set(std::memory_order_acquire);
                // Spin until we acquire the lock
            }
            auto stop = std::chrono::high_resolution_clock::now();
            double diff = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
            diff *= 1e-9;
            std::cout << "Total spin duration: " << std::setw(9) << diff << " seconds\n";
            return counter;
        } else {
            return 0;
        }
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }

    bool value() {
        return flag.test();
    }

private:
    std::atomic_flag flag;
};


// Example usage:

#include <chrono>
#include <iostream>
#include <thread>

Spinlock myLock;

void Task(bool lock_status, int id) {
    // Critical section
    assert(lock_status == true);
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
}

void criticalSection(int id) {
    // Acquire lock before performing Task
    int spincount = myLock.lock();
    std::cout << "Thread " << id << " is in the critical section." << std::endl;
    std::cout << "Spincount of thread " << id << ": " << spincount << " spins" << std::endl;

    Task(myLock.value(), id);

    myLock.unlock();
}

int main() {
    const int numThreads = 5;
    std::thread threads[numThreads];

    for (int i = 0; i < numThreads; ++i) {
        threads[i] = std::thread(criticalSection, i);
    }

    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    return 0;
}