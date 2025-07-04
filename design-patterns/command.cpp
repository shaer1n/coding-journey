#include <iostream>
#include <memory>

class Light{
public:
    void on(){
        if(status == 0){
            std::cout << "turn on the light" << std::endl; 
            status = 1;
        }else{
            std::cout << "light already run" << std::endl;
        }
    }

    void off(){
        if(status == 1 ){
            std::cout << "turn off the light" << std::endl;
            status = 0;
        }else{
            std::cout <<"light is shut" << std::endl;
        }
    }
private:
    int status = 0;
};

class Command{
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class LightOnCommand : public Command{
public:
    LightOnCommand(std::shared_ptr<Light> l)
        :_light(l){}

    void execute(){
        _light->on();
    }
private:
    std::shared_ptr<Light> _light;
};

class LightOffCommand : public Command{
public:
    LightOffCommand(std::shared_ptr<Light> l)
        :_light(l){}

    void execute(){
        _light->off();
    }
private:
    std::shared_ptr<Light> _light;
};

class Remote{
public:
    void setCommand(std::unique_ptr<Command> command){
        _command = std::move(command);
    }

    void pressButton(){
        _command->execute();
    }

private:
    std::unique_ptr<Command> _command;
};


int main(){
    auto light = std::make_shared<Light>();
    auto remote = std::make_unique<Remote>();

    remote->setCommand(std::make_unique<LightOnCommand>(light));
    remote->pressButton();

    /* remote->setCommand(std::make_unique<LightOffCommand>(light)); */
    /* remote->pressButton(); */

    remote->setCommand(std::make_unique<LightOnCommand>(light));
    remote->pressButton();

    remote->setCommand(std::make_unique<LightOffCommand>(light));
    remote->pressButton();

    return 0;
}











