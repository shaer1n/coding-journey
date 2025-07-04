#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>

// 创建产品抽象类
class Figure{
public:
    virtual std::string getName() = 0;
    virtual double getArea() = 0;
    virtual ~Figure() = default;
};

class Rectangle : public Figure{
public:
    Rectangle(int x, int y)
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

class Circle : public Figure{
public:
    Circle(double x)
        :r(x){}

    std::string getName(){
        return "圆";
    }

    double getArea(){
        return (double)3.14 * r * r;
    }

private:
    double r;

};

class Triangle : public Figure{
public:
    Triangle(int x, int y, int z)
        :a(x), b(y), c(z){}

    std::string getName(){
        return "三角形";
    }

    double getArea(){
        double s = (a + b + c) / 2.0;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }

private:
    double a, b ,c;
};

// 定义工厂的抽象接口
class Factory{
public:
    virtual std::unique_ptr<Figure> create(double x = 1.0, double y = 1.0, double z = 1.0) = 0;
    virtual ~Factory() = default;

};

class RectangleFactory : public Factory{
public:
    std::unique_ptr<Figure> create(double x = 0, double y = 0, double z = 0){
        return std::make_unique<Rectangle>(x, y);
    }
};


class CircleFactory : public Factory{
public:
    std::unique_ptr<Figure> create(double x = 0, double y = 0 , double z = 0){
        return std::make_unique<Circle>(x);
    }
};


class TriangleFactory : public Factory{
public:
    std::unique_ptr<Figure> create(double x = 0, double y = 0, double z = 0){
        return std::make_unique<Triangle>(x, y, z);
    }
};

int main(){
    std::vector<std::unique_ptr<Figure>> vec;

    // 使用匿名工厂来创建对象
    vec.emplace_back(RectangleFactory().create(3.0, 4.5));
    vec.emplace_back(CircleFactory().create(3.0));
    vec.emplace_back(TriangleFactory().create(3.0, 4.0, 5.0));

    for(auto & f : vec){
        std::cout << f->getName() << ":" << f->getArea() << std::endl;
    }

    return 0;
}
