#include "taskqueue.h"
#include "threadpool.h"

#include <string>
#include <iostream>
#include <unistd.h>

void DoWork(int id, const std::string& msg) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lg(coutMtx);
    std::cout << "Task " << id << ": " << msg << std::endl;
}

int main() {
    ThreadPool pool(4, 10); // 4个工作线程，队列最大10个任务
    pool.start();

    for (int i = 0; i < 20; ++i) {
        pool.addTask(DoWork, i, "hello from task");
    }
    
    // sleep(3);

    pool.stop();
    return 0;
}