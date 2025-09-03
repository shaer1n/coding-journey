#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> data(0);
std::atomic<bool> ready(false);

void producer(){
    data.store(42, std::memory_order_relaxed);
    ready.store(true, std::memory_order_release);
}

void consumer(){
    // 等待数据准备完成
    while (!ready.load(std::memory_order_acquire));{
        std::this_thread::yield();
    }

    // 打印数据
    std::cout << data.load(std::memory_order_relaxed);
}

int main(){
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
    return 0;
}