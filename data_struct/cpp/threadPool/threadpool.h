#pragma once

#include "taskqueue.h"

#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>

class ThreadPool{
public:
    using Task = std::function<void()>;
    ThreadPool(size_t threadCount, size_t queue_capacity)
        :m_taskqueue(queue_capacity), m_threadCount(threadCount){}

    ~ThreadPool(){
        if(m_running){
            stop();
        }
    }

    void start();

    void stop();

    template<class F, class ...Args>
    void addTask(F && f, Args&& ...args){
        Task task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        m_taskqueue.push(std::move(task));
    }
private:
    TaskQueue m_taskqueue;
    size_t m_threadCount;
    std::vector<std::thread> m_threads;
    std::atomic<bool> m_running;
};

