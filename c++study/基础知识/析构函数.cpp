//析构函数用于释放类实例在其生命周期内分配的资源
//在对象的生命周期结束时自动调用
//1，定义
#include <iostream>
using namespace std;

class ClassName{
public:
    ~ClassName(){

    }
};
// 无参数
// 无返回值

//2 用途
//释放动态分配的内存： new分配的内存在析构函数应该用delete释放
//关闭文件句柄
//释放其他资源：网络连接，线程


//3，实例
#include <iostream>

class MyClass {
private:
    int* data; // 动态分配的内存

public:
    // 构造函数
    MyClass(int size) {
        data = new int[size]; // 分配内存
        std::cout << "Constructor: Memory allocated." << std::endl;
    }

    // 析构函数
    ~MyClass() {
        delete[] data; // 释放内存
        std::cout << "Destructor: Memory freed." << std::endl;
    }
};

int main() {
    MyClass obj(10); // 创建对象
    // 对象超出作用域后，析构函数会自动调用
    return 0;
}

//4,总结
//析构函数在对象生命周期结束后自动调用：1，栈（函数结束） 2，堆（delete）
//在一个类的析构函数中，如果存在基类，基类的析构函数会在派生类的析构函数之后被调用。用于保证派生类可以自己搞定自己的，基类也能清理自己的资源
//说白了就是创建一个派生类角色，删除时，先调用派生类的析构函数，再调用基类的析构函数
//不可重载，一个类只能有一个析构
//如果你有一个基类指针指向派生类对象，且可能会通过基类指针删除派生类对象，则基类的析构函数应该声明为虚拟的。这可以确保正确调用派生类的析构函数，避免内存泄漏。
class Base {
public:
    virtual ~Base() { /* ... */ }
};

class Derived : public Base {
public:
    ~Derived() { /* ... */ }
};
