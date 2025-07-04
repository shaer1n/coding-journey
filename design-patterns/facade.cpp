#include <iostream>

// BIOS
class BIOS{
public:
    void powerOn(){
        std::cout << "BIOS: Powering on..." << std::endl;
    }

    void powerOff(){
        std::cout << "BIOS: Powering off..." << std::endl;
    }
};

// CPU
class CPU{
public:
    void reset(){
        std::cout << "CPU: Resetting..." << std::endl;
    }

    void halt(){
        std::cout << "CPU: Halting..." << std::endl;
    }
};

// Disk
class HardDrive{
public:
    void readBootSector(){
        std::cout << "HardDrive: Reading boot sector..." << std::endl;
    }

    void parkHeads(){
        std::cout << "HardDrive: Parking heads..." << std::endl;
    }
};

// OS
class OperatingSystem{
public:
    void load(){
        std::cout << "OS: Loading operating system..." << std::endl;
    }

    void shutdown(){
        std::cout << "OS: Shutting down..." << std::endl;
    }
};

// 外观类（Facade）
class Computer{
public:
    void start(){
        bios.powerOn();
        cpu.reset();
        hardDrive.readBootSector();
        os.load();
        std::cout << "Computer has started successfully" << std::endl;
    }

    void shutdown(){
        os.shutdown();
        hardDrive.parkHeads();
        cpu.halt();
        bios.powerOff();
        std::cout << "Computer has shut down successfully" << std::endl;
    }
private:
    BIOS bios;
    CPU cpu;
    HardDrive hardDrive;
    OperatingSystem os;
};


int main(){
    Computer pc;

    std::cout << "------------ 开机 --------------" << std::endl;
    pc.start();
    
    std::cout << "\n------------ 关机 --------------" << std::endl;
    pc.shutdown();

    return 0;
}
