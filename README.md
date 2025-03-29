Dining Philosophers Problem - projekt 1

This project implements a classical concurrency problem known as the Dining Philosophers Problem using C++11 with std::thread and custom synchronization mechanisms.
The purpose of this exercise is to demonstrate thread creation, handling critical sections, and preventing deadlocks without using any ready-made synchronization modules (e.g., std::mutex).
Each philosopher (thread) alternates between thinking and eating, while competing for access to shared resources (forks).
The program guarantees that no deadlock occurs by enforcing a locking order on the forks.



Compilation and Execution:
Requirements:
Compiler supporting C++11 (e.g., g++, clang++) – only if you want to compile the source manually
Or just use the provided filozofowie.exe on Windows

Option 1 – Using Provided Executable which should work (Windows only)
filozofowie.exe <number_of_philosophers>

Option 2 – Manual Compilation
g++ -std=c++11 -pthread -o filozofowie filozofowie.cpp
./filozofowie <number_of_philosophers>


Problem Description
In the Dining Philosophers Problem, n philosophers sit around a round table with one fork placed between each pair.
To eat, a philosopher needs two forks — the one on their left and the one on their right.
Philosophers alternate between thinking and eating, and must never deadlock by indefinitely waiting for forks.


Threads and Their Roles
The program creates n threads, one for each philosopher.
Each thread runs a loop where the philosopher:
Thinks (simulated with a random delay).
Tries to acquire both forks (using custom spinlocks).
Eats (simulated with another delay).
Releases both forks.
A separate global SpinLock is used to protect std::cout output from concurrent access.


Critical Sections and Their Handling
1. Fork Acquisition
Shared resources (forks) are protected using a custom SpinLock implementation.
Each fork is an instance of SpinLock, stored in a vector.
To avoid deadlock, philosophers always acquire the lower-indexed fork first:

if (leftFork > rightFork) {
    swap(leftFork, rightFork);
}

2. Console Output
Writing to the console (std::cout) is a critical section.
A global SpinLock named coutLock ensures that messages from different threads do not interleave.
Protected using a ScopedLock wrapper for RAII-style lock management.
