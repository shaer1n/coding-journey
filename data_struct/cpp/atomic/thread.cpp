#include <iostream>
#include <vector>
#include <thread>

static int counter = 1;

void func(){
    for(int i = 0; i < 1000000; ++i){
        // 非原子操作 
        ++counter;
    }
}

int main(){
    std::vector<std::thread> threads;
    for(int i = 0; i < 10; ++i){
        threads.emplace_back(func);
    }

    for(std::thread &t : threads){
        if(t.joinable()){
            t.join();
        }
    }

    std::cout << counter << std::endl;
    return 0;
}