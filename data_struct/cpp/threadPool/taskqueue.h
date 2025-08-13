#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

extern std::mutex coutMtx;

class TaskQueue{
public:
    using Task = std::function<void()>;
    TaskQueue(size_t capacity):m_capacity(capacity), m_stop(false){}
    void push(Task && task);
    bool pop(Task &task);
    bool empty();
    void stop();
private:
    size_t m_capacity; // 任务队列的最大容量
    std::queue<Task> m_queue; // 任务队列
    std::mutex m_mtx;  // 线程锁
    std::condition_variable m_notEmpty;  // 空队列的条件变量
    std::condition_variable m_notFull;   // 满队列的条件变量
    std::atomic<bool> m_stop;   // 退出队列的控制位
};