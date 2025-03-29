#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <random>
#include <memory>

using namespace std;

class SpinLock {
    atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    void lock() {
        while (flag.test_and_set(memory_order_acquire)) {
            ; // spin
        }
    }
    void unlock() {
        flag.clear(memory_order_release);
    }
};

class ScopedLock {
    SpinLock &lockRef;
public:
    explicit ScopedLock(SpinLock &l) : lockRef(l) {
        lockRef.lock();
    }
    ~ScopedLock() {
        lockRef.unlock();
    }
};

SpinLock coutLock;

void philosopher(int id, int n, const vector<unique_ptr<SpinLock>>& forks) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(100, 1000); 

    while (true) {
        {
            ScopedLock lock(coutLock);
            cout << "Philosopher " << id << " is thinking." << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(dist(gen)));

        int leftFork = id;
        int rightFork = (id + 1) % n;

        if (leftFork > rightFork) {
            swap(leftFork, rightFork);
        }

        forks[leftFork]->lock();
        forks[rightFork]->lock();

        {
            ScopedLock lock(coutLock);
            cout << "Philosopher " << id << " is eating." << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(dist(gen)));

        forks[rightFork]->unlock();
        forks[leftFork]->unlock();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " number_of_philosophers" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        cout << "Number of philosophers must be positive." << endl;
        return 1;
    }

    vector<unique_ptr<SpinLock>> forks;
    forks.reserve(n);
    for (int i = 0; i < n; ++i) {
        forks.push_back(make_unique<SpinLock>());
    }

    vector<thread> philosophers;
    for (int i = 0; i < n; ++i) {
        philosophers.push_back(thread(philosopher, i, n, cref(forks)));
    }

    for (auto &t : philosophers) {
        t.join();
    }

    return 0;
}