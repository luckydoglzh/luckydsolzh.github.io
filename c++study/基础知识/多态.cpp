// c++多态分为两种：静态多态和运行时多态：
// 多态是一种允许不同类的对象以相同的方式进行操作的特性
//统一的方式处理不同的对象
//静态多态：
//函数重载
#include <iostream>

class Print {
public:
    void show(int i) {
        std::cout << "Integer: " << i << std::endl;
    }
    
    void show(double d) {
        std::cout << "Double: " << d << std::endl;
    }
    
    void show(const std::string& s) {
        std::cout << "String: " << s << std::endl;
    }
};

int main() {
    Print print;
    print.show(10);
    print.show(10.5);
    print.show("Hello");
    return 0;
}

//运算符重载
class Complex{
public:
    float real, imag;
    Complex(float r= 0, float i = 0):real(r), imag(i){} //语法

    Complex operator + (const Complex& c){
        return  Complex(real + c.real, imag + c.imag);
    }
};

int main(){
    Complex c1(1.5,2.6), c2(3.2,3.2);
    Complex c3 = c1 + c2;
    return 0;
}

//运行时多态
#include <iostream>

class Base {
public:
    virtual void show() { // 虚函数
        std::cout << "Base class show function." << std::endl;
    }
    virtual ~Base() {} // 虚析构函数
};

class Derived : public Base {
public:
    void show() override { // 重写虚函数
        std::cout << "Derived class show function." << std::endl;
    }
};

int main() {
    Base* b; // 基类指针
    Derived d; // 派生类对象
    b = &d; // 指向派生类对象

    b->show(); // 调用派生类的 show() 函数

    return 0;
}

