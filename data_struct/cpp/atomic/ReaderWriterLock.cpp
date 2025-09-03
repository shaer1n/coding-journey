#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <string>

class ReaderWriterLock
{
private:
    std::atomic<int> reader_count;
    std::atomic<int> writer_flag;
    // 打印锁
    std::mutex mtx;
public:
    ReaderWriterLock(): reader_count(0), writer_flag(0){};

    // 获得读锁
    void read_lock(){
        while(true){
            // 使用acquire保证读取的顺序
            if(writer_flag.load(std::memory_order_acquire) == 0){
                reader_count.fetch_add(1, std::memory_order_acquire);
                return;
            }
            // 释放cpu，等待重试
            std::this_thread::yield();
        }
    }

    // 释放锁，使用release保证操作后的数据同步给所有线程
    void read_unlock(){
        reader_count.fetch_add(-1, std::memory_order_release);
    }

    // 获得写锁
    void write_lock(){
        while(true){
            if(reader_count.load(std::memory_order_acquire) == 0 && writer_flag.load(std::memory_order_acquire) == 0){
                writer_flag.fetch_add(1, std::memory_order_acq_rel);             
                return;
            }
            // 没有满足情况的话，释放CPU
            std::this_thread::yield();
        }
        
    }

    void write_unlock(){
        writer_flag.store(0, std::memory_order_release);
    }

    void print(const std::string &msg){
        std::lock_guard<std::mutex> lg(mtx);
        std::cout << msg << std::endl;
    }

    ~ReaderWriterLock(){};
};



// 模拟读取线程函数
void reader(ReaderWriterLock &rw_lock, int id){
    rw_lock.read_lock();
    // std::cout << "Reader " << id << " is reading\n"; 
    rw_lock.print( "reader " + std::to_string(id) + " is reading");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    rw_lock.read_unlock();
}

void writer(ReaderWriterLock &rw_lock, int id){
    rw_lock.write_lock();
    // std::cout << "Writer " << id << " is reading\n";
    rw_lock.print( "writer " + std::to_string(id) + " is writing");
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    rw_lock.write_unlock();
}

int main(){
    ReaderWriterLock rw;
    std::vector<std::thread> threads;
    
    for(int i = 0; i < 5; ++i){
        threads.emplace_back(std::bind(reader, std::ref(rw), i));
    }
    threads.emplace_back(std::bind(writer, std::ref(rw), 1));

    for(auto &t : threads){
        if(t.joinable()){
            t.join();
        }
    }
    return 0;
}
