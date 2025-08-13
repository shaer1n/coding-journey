#include "taskqueue.h"

std::mutex coutMtx;

void TaskQueue::push(Task && task){
    // 使用unique_lock互斥锁，保护队列和相关条件变量的状态
    std::unique_lock<std::mutex> lock(m_mtx);

    // 判断队列是否满了, 使用带谓词的wait，避免虚假唤醒
    m_notFull.wait(lock, [this]{return m_queue.size() < m_capacity || m_stop;});

    // 如果队列已经停止，则丢弃该任务，直接返回
    if(m_stop) return;
    // 任务队列插入任务
    m_queue.push(std::move(task));

    // 解锁
    lock.unlock();
    // 唤醒等待
    m_notEmpty.notify_one();
}

bool TaskQueue::pop(Task & task){
    std::unique_lock<std::mutex> lock(m_mtx);
    m_notEmpty.wait(lock, [this]{return !m_queue.empty() || m_stop;});
    if(m_queue.empty() && m_stop) return false;
    if(!m_queue.empty()){
        task = std::move(m_queue.front());
        m_queue.pop();
        m_notFull.notify_one();
        return true;
    }
    return true;
}

bool TaskQueue::empty(){
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_queue.empty();
}

void TaskQueue::stop(){
    m_stop = true;
    m_notEmpty.notify_all();
    m_notFull.notify_all();
}