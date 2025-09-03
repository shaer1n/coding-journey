#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> flag(0);
std::atomic<int> data(0);

void writer(){
    data.store(42, std::memory_order_relaxed);
    flag.store(1, std::memory_order_relaxed);
}

void reader(){
    while(flag.load(std::memory_order_relaxed)  == 0){
        // std::this_thread::yield();
    }

    std::cout << data.load(std::memory_order_relaxed) << std::endl;
}

int main(){
    std::thread t1(writer);
    std::thread t2(reader);

    t1.join();
    t2.join();
    return 0;
}