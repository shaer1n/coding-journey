#include <iostream>
#include <memory>

// 新的接口抽象类
class Printable{
public:
    virtual void print() = 0;
    virtual ~Printable() = default;
};

// 旧的接口
class OldPrinter{
public:
    void legacyPrint(){
        std::cout << "old print function" << std::endl;
    }
};

class Adapter : public Printable{
public:
    Adapter(std::unique_ptr<OldPrinter> OP)
        :op(std::move(OP)){}

    void print(){
        op->legacyPrint();
    }
private:
    std::unique_ptr<OldPrinter> op;
};


int main(){
    auto ap = std::make_unique<Adapter>(std::make_unique<OldPrinter>());

    ap->print();

    return 0;
}
