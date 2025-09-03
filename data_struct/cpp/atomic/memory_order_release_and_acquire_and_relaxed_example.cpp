#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> data(0);      // 数据
std::atomic<bool> ready(false); // 标志

// 生产者线程：写入数据并设置 ready 标志
void producer() {
    data.store(42, std::memory_order_release);     // 设置数据，release 保证在 ready 之前写入
    ready.store(true, std::memory_order_release);  // 设置 ready 标志
}

// 消费者线程：等待 ready 标志，并读取数据
void consumer() {
    while (!ready.load(std::memory_order_acquire)) {  // acquire 保证 ready 之后的写入可见
        std::this_thread::yield(); // 等待其他线程
    }

    // 错误！使用 memory_order_relaxed 读取，可能会读取到旧值。
    int value = data.load(std::memory_order_relaxed); 
    std::cout << "Data: " << value << std::endl;  // 可能输出 0，而不是 42
}

int main() {
    std::thread t1(producer);  // 生产者线程
    std::thread t2(consumer);  // 消费者线程

    t1.join();  // 等待生产者线程完成
    t2.join();  // 等待消费者线程完成
    return 0;
}
