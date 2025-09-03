#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

std::atomic<int> counter(0);

void increment(){
    for(int i = 0; i < 1000000; ++i){
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main(){
    std::vector<std::thread> threads;
    for(int i = 0; i < 10; ++i){
        threads.emplace_back(increment);
    }

    for(auto &t : threads){
        if(t.joinable()){
            t.join();
        }
    }

    std::cout << counter << std::endl;
    return 0;
}