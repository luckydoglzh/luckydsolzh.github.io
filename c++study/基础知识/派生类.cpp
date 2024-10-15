/*
    大家都听说过C++的继承吧，顾名思义，你有的东西，我也要有。
    而派生类是就是继承原有的类，并允许添加自己的私料
*/

#include <iostream>
using namespace std;
//look look code
//创建一个基类Animal
//给基类添加一个eat函数
class Animal {  // 基类
public:
    void eat() {
        cout << "I can eat!" << endl;
    }
};
//创建一个派生类Dog
//给派生类增加属于自己的feature
class Dog : public Animal {  // 派生类
public:
    void bark() {
        cout << "I can bark!" << endl;
    }
    void eat(){
        cout << "i can eat meat!" << endl;
    }
};

//从这个例子我们发现派生类有以下几个特点：
//1，继承基类的成员函数/成员变量
//2，重写基类的成员函数
//3，extern新的feature
//同时注意以下特性：
//基类的 public 成员在派生类中保持 public，基类的 protected 成员在派生类中保持 protected
//构造函数、析构函数、拷贝构造函数和赋值运算符无法继承

int main() {
    Dog d;
    d.eat();  // 调用基类的函数
    d.bark(); // 调用派生类的函数
    return 0;
}

