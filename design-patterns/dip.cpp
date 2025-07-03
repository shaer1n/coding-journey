#include <iostream>
#include <string>
#include <memory>

/* 
**  依赖倒置原则，SOLID中的D，Dependency Inversion Principle，DIP
*/

// 抽象接口
class BankWork{
public:
    virtual void dowork() = 0;
    virtual ~BankWork() = default;
};

// 具体接口
class SaveWork
:public  BankWork{
public:
    void dowork(){
        std::cout << "savework" << std::endl;
    }
};

class PayWork
:public BankWork{
public:
    void dowork(){
        std::cout << "payword" << std::endl;
    }

};

// 高层模块(业务逻辑)依赖与抽象，而非具体实现
class Worker{
private:
    std::unique_ptr<BankWork> bk;

public:
    // 使用右值引用，使用移动语义，转移所有权
    Worker(std::unique_ptr<BankWork> && bankwork):bk(std::move(bankwork)){}

    void work(){
        bk->dowork();
    }
};

int main(){
    // 使用智能指针来管理 依赖关系的抽象对象
    Worker work1 = Worker(std::make_unique<SaveWork>());
    Worker work2 = Worker(std::make_unique<PayWork>());

    work1.work();
    work2.work();

    return 0;
}
