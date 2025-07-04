#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#define MILETEA 1
#define FRUITTEA 2

// ---------- 抽象组件(饮品) ----------
class Drink{
public:
    virtual std::string getDescription() = 0;
    virtual double cost() = 0;
    virtual ~Drink() = default;
};

class MilkTea : public Drink{
public:
    std::string getDescription(){
        return "MilkTea";
    }
    
    double cost(){
        return 15;
    }
};

class FruitTea : public Drink{
public:
    std::string getDescription(){
        return "FruitTea";
    }

    double cost(){
        return 18;
    }
};

// ---------------- 装饰器模式(小料) ---------------

class ToppingDecorator : public Drink{
public:
    ToppingDecorator(std::unique_ptr<Drink> && d)
        :drink(std::move(d)){}

    virtual ~ToppingDecorator() = default;
protected:
    // 装饰器来管理饮品
    std::unique_ptr<Drink> drink;
};

class Boda : public ToppingDecorator{
public:
    Boda(std::unique_ptr<Drink> && d)
        :ToppingDecorator(std::move(d)){}

    std::string getDescription(){
        return drink->getDescription() + ", Boda";
    }

    double cost(){
        return drink->cost() + 2;
    }
};

class Pudding : public ToppingDecorator{
public:
    Pudding(std::unique_ptr<Drink> && d)
        :ToppingDecorator(std::move(d)){}

    std::string getDescription(){
        return drink->getDescription() + ", Pudding";
    }

    double cost(){
        return drink->cost() + 3;
    }
};

std::unique_ptr<Drink> addBobaN(std::unique_ptr<Drink>  base, int n){
    for(int i = 0; i < n; ++i){
        base = std::make_unique<Boda>(std::move(base));
    }
    return base;
}

std::unique_ptr<Drink> addPuddingN(std::unique_ptr<Drink>  base, int n){
    for(int i = 0; i < n; ++i){
        base = std::make_unique<Pudding>(std::move(base));
    }
    return base;
}

int main(){
    auto pmt = std::make_unique<MilkTea>();
    std::cout << pmt->getDescription() << " cost $" << pmt->cost() << std::endl;

    auto BodawithMilk = std::make_unique<Boda>(std::move(pmt));
    std::cout << BodawithMilk->getDescription() << " cost $" << BodawithMilk->cost() << std::endl;

    /*   输出结果：
     *   MilkTea cost $15
     *   MilkTea, Boda cost $17
     */

    return 0;
}

