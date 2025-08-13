#include "threadpool.h"

extern std::mutex coutMtx;

void ThreadPool::start(){
    m_running = true;
    for(size_t i = 0; i < m_threadCount; ++i){
        m_threads.emplace_back([this]
        {
            Task task;
            while(!m_taskqueue.empty() || m_running){
                if(m_taskqueue.pop(task)){
                    {
                        std::lock_guard<std::mutex> ct_mtx(coutMtx);
                        std::cout << "Worker:[" << 1 << "]: running task" << std::endl;
                    }
                    task();
                    {
                        std::lock_guard<std::mutex> ct_mtx(coutMtx);
                        std::cout << "Worker:[" << 2 << "]: running task" << std::endl;
                    }
                }
            }
        });
    }
}

void ThreadPool::stop(){
    m_running = false;
    m_taskqueue.stop();
    for(auto &t : m_threads){
        if(t.joinable()){
            t.join();
        }
    }
}