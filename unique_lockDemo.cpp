#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock
 
std::mutex mtx;           // mutex for critical section
std::mutex mtx2; 
std::mutex mtx3; 
std::mutex mtx4; 
std::mutex mtx5; 
int gIntcout = 0;

void print_block (int n, char c) {
    // critical section (exclusive access to std::cout signaled by lifetime of lck):
    std::unique_lock<std::mutex> lck (mtx);
    gIntcout++;
    for (int i=0; i<n; ++i) {
        std::cout << gIntcout;
    }
    std::cout << '\n';
}

void print_block2 (int n, char c) {
    // critical section (exclusive access to std::cout signaled by lifetime of lck):
    std::unique_lock<std::mutex> lck (mtx2);
    gIntcout++;
    for (int i=0; i<n; ++i) {
        std::cout << gIntcout;
    }
    std::cout << '\n';
}
void print_block3(int n, char c) {
    // critical section (exclusive access to std::cout signaled by lifetime of lck):
    std::unique_lock<std::mutex> lck (mtx3);
    gIntcout++;
    for (int i=0; i<n; ++i) {
        std::cout << gIntcout;
    }
    std::cout << '\n';
}

void print_block4 (int n, char c) {
    // critical section (exclusive access to std::cout signaled by lifetime of lck):
    std::unique_lock<std::mutex> lck (mtx4);
    gIntcout++;
    for (int i=0; i<n; ++i) {
        std::cout << gIntcout;
    }
    std::cout << '\n';
}
void print_block5(int n, char c) {
    // critical section (exclusive access to std::cout signaled by lifetime of lck):
    std::unique_lock<std::mutex> lck (mtx5);
    gIntcout++;
    for (int i=0; i<n; ++i) {
        std::cout << gIntcout;
    }
    std::cout << '\n';
}

int main ()
{
    std::thread th1 (print_block,1000,'1');
    std::thread th2 (print_block2,1000,'2');
    std::thread th3 (print_block3,1000,'3');
    std::thread th4 (print_block4,1000,'4');
    std::thread th5(print_block5,1000,'5');
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
 
    return 0;
}