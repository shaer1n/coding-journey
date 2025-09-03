#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

std::atomic<int> atomic_counter(1);

void func(){
    for(int i = 0; i < 1000000; i++){
        ++atomic_counter;
    }
}

int main(){
    std::vector<std::thread> threads;
    for(int i = 0; i < 10; ++i){
        threads.emplace_back(func);
    }

    for(auto &t : threads){
        if(t.joinable()){
            t.join();
        }
    }

    std::cout << atomic_counter << std::endl;
    return 0;
}