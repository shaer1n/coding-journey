#include <iostream>
#include <memory>
#include <string>
#include <cmath>

class Figure{
public:
    virtual std::string getName() = 0;
    virtual double getArea() = 0;
    virtual ~Figure() = default;
};


// 矩形
class Rectangle
:public Figure
{
public:
    Rectangle(double x, double y)
        :length(x), width(y){}

    std::string getName(){
        return "矩形";
    }

    double getArea(){
        return length * width;
    }
private:
    double length;
    double width;
};


// 圆
class Circle
:public Figure
{
public:
    Circle(double x):r(x){}

    std::string getName(){
        return "圆";
    }

    double getArea(){
        return (double)3.14 * r * r;
    }
private:
    double r;
};


// 三角形
class Triangle
:public Figure
{
public:
    Triangle(double x, double y, double z)
        :a(x),b(y),c(z){}

    std::string getName(){
        return "三角形";
    }

    double getArea(){
        double s = (a + b + c) / 2.0;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
private:
    double a;
    double b;
    double c;
};

// 函数对象工厂（使用函数默认参数）
class FigureFactory {
public:
    static std::unique_ptr<Figure> create(const std::string& name, int x = 1.0, int y = 1.0, int z = 1.0)  {
        if (name == "rectangle") {
            return std::make_unique<Rectangle>(x, y);
        } else if (name == "circle") {
            return std::make_unique<Circle>(x);
        }else if (name == "triangle"){
            return std::make_unique<Triangle>(x, y, z);
        }
        return nullptr;
    }
};

int main() {
    auto rect = FigureFactory::create("triangle", 3.0, 4.0, 5.0);
    std::cout << rect->getName() <<":" << rect->getArea() << std::endl;
    return 0;
}
