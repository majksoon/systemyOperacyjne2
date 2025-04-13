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





Projekt Chat – Systemy Operacyjne 2
Opis projektu
Projekt polega na stworzeniu aplikacji czatu umożliwiającej komunikację między wieloma klientami. System składa się z następujących modułów:

server.py – serwer obsługujący połączenia, odbieranie wiadomości oraz rozsyłanie ich do wszystkich klientów.

client.py – klient łączący się z serwerem, odpowiedzialny za wysyłanie i odbieranie wiadomości.

clientGUI.py – graficzny interfejs użytkownika (Tkinter) umożliwiający logowanie oraz komunikację.

main.py – punkt wejścia, który uruchamia serwer.

Projekt realizowany jest w języku Python z wykorzystaniem wielowątkowości i mechanizmów synchronizacji w celu zapewnienia poprawnej współpracy przy równoczesnych połączeniach.

Instrukcje uruchomienia
Uruchomienie serwera
Otwórz terminal i przejdź do katalogu projektu.

Uruchom serwer poleceniem:
python main.py


Uruchomienie klienta:
W nowym terminalu (lub na innej maszynie) przejdź do katalogu projektu.

Uruchom klienta z interfejsem graficznym:
python client.py

Po uruchomieniu pojawi się ekran logowania – wpisz nazwę użytkownika, a następnie rozpocznij komunikację.


Opis problemów
Projekt rozwiązuje klasyczny problem komunikacji między procesami w środowisku wielowątkowym. Główne wyzwania to:

Synchronizacja dostępu do wspólnych zasobów: W obliczu wielu jednoczesnych połączeń konieczne jest zapewnienie spójności danych, takich jak lista aktywnych klientów czy historia czatu.

Obsługa wielowątkowości: Każde nowe połączenie klienta jest obsługiwane przez osobny wątek, co wymaga zastosowania mechanizmów synchronizacji, aby uniknąć błędów przy jednoczesnym dostępie do danych.

Zarządzanie rozłączaniem klientów: System musi poprawnie usuwać rozłączonych klientów, aby zapobiec wysyłaniu wiadomości do nieaktywnych połączeń.

Wątki i ich funkcje
Na serwerze:

Dla każdego klienta tworzony jest osobny wątek (funkcja receive_message w server.py), który obsługuje komunikację z danym klientem.

Na kliencie:

Połączenie z serwerem inicjuje wątek nasłuchujący wiadomości (funkcja talk_to_server w client.py), dzięki czemu klient może równocześnie odbierać wiadomości i wysyłać je przez GUI.

Sekcje krytyczne i rozwiązania
Aby zapewnić poprawne działanie aplikacji w środowisku wielowątkowym, zastosowano mechanizmy synchronizacji:

Lista klientów (client_sockets):

Krytyczna sekcja: Modyfikacja listy aktywnych połączeń.

Rozwiązanie: Użycie locka client_sockets_lock, który gwarantuje, że tylko jeden wątek na raz może modyfikować listę klientów.

Historia czatu (chat_history):

Krytyczna sekcja: Aktualizacja i odczyt historii wiadomości.

Rozwiązanie: Użycie locka chat_history_lock, który zabezpiecza operacje na historii czatu przed jednoczesnym dostępem wielu wątków.

Dzięki tym rozwiązaniom projekt unika problemów związanych z wyścigami (race conditions) i zapewnia spójność oraz poprawność przesyłanych danych.

