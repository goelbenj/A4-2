#include <atomic>

class Spinlock {
public:
    Spinlock() {
        flag.clear(); // Initialize the atomic_flag to clear (unlocked) state
    }

    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) {
            // Spin until we acquire the lock
        }
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }

private:
    std::atomic_flag flag;
};


// Example usage:

#include <iostream>
#include <thread>

Spinlock myLock;

void criticalSection(int id) {
    myLock.lock();

    // Critical section
    std::cout << "Thread " << id << " is in the critical section." << std::endl;

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