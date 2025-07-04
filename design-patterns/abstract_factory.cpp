#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 先定义产品，CPU MainBoard

// CPU
class CPU{
public:
    virtual void show() = 0;
    virtual ~CPU() = default;
};

// MainBoard
class MainBoard{
public:
    virtual void show() = 0;
    virtual ~MainBoard() = default;
};

// 定义抽象工厂，生产两类产品 CPU MainBoard

class AbstractFacotry{
public:
    virtual std::unique_ptr<CPU> createCPU() = 0;
    virtual std::unique_ptr<MainBoard> createMainBoard() = 0;
};

// 定义两种CPU产品

// IntelCPU
class IntelCPU : public CPU{
public:
    void show(){
        std::cout << "Intel CPU" << std::endl;
    }
};

// AMDCPU
class AMDCPU : public CPU{
public:
    void show(){
        std::cout << "AMD CPU" << std::endl;
    }
};

// 定义两种MainBoard产品

// IntelMainBoard
class IntelMainBoard : public MainBoard{
public:
    void show(){
        std::cout << "Intel MainBoard" << std::endl;
    }
};

class AMDMainBoard : public MainBoard{
public:
    void show(){
        std::cout << "AMD MainBoard" << std::endl;
    }
};

// 定义两家工厂 Intel AMD

// Intel
class Intel : public AbstractFacotry{
public:
    std::unique_ptr<CPU> createCPU(){
        return std::make_unique<IntelCPU>();
    }

    std::unique_ptr<MainBoard> createMainBoard(){
        return std::make_unique<IntelMainBoard>();
    }
};

// AMD
class AMD : public AbstractFacotry{
public:
    std::unique_ptr<CPU> createCPU(){
        return std::make_unique<AMDCPU>();
    }

    std::unique_ptr<MainBoard> createMainBoard(){
        return std::make_unique<AMDMainBoard>();
    }
};

int main(){
    auto  cpu1 = Intel().createCPU();
    auto  cpu2 = AMD().createCPU();

    auto  mainboard1 = Intel().createMainBoard();
    auto  mainboard2 = AMD().createMainBoard();

    cpu1->show();
    cpu2->show();

    mainboard1->show();
    mainboard2->show();

    return 0;
}


