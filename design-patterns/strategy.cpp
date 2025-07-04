#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

// 策略的抽象接口
class Strategy{
public:
    virtual void excute(const std::string& str) = 0;
    virtual ~Strategy() = default;
};

// 策略A
class ConcreteStrategyA : public Strategy{
public:
    void excute(const std::string &str){
        std::cout << "ConcreteStrategyA" << std::endl;
        std::string data = str;
        std::sort(data.begin(), data.end());
        std::cout << data << std::endl; 
    }
};

// 策略B
class ConcreteStrategyB : public Strategy{
public:
    void excute(const std::string &str){
        std::cout << "ConcreteStrategyB" << std::endl;
        std::string data = str;
        std::sort(data.begin(), data.end(), std::greater<char>()); 
        std::cout << data << std::endl; 
    }
};

// 设置上下文，来动态的切换接口
class Context{
public:
    // 设置策略函数
    void setStrategy(std::unique_ptr<Strategy> s){
        strategy = std::move(s);
    }


    void doAction(const std::string &str){
        if(strategy){
            strategy->excute(str);
        }else{
            std::cout << "没有策略" << std::endl;
        }
    }
private:
    std::unique_ptr<Strategy> strategy;
};


int main(){
    Context ctx;

    // 设置策略
    ctx.setStrategy(std::make_unique<ConcreteStrategyA>());
    ctx.doAction("helloworld");

    // 切换策略
    ctx.setStrategy(std::make_unique<ConcreteStrategyB>());
    ctx.doAction("helloworld");

    return 0;
}
