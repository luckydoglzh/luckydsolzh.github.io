//什么是构造函数呢?
//构造函数是C++中的成员函数，用来在创建对象时初始化对象的状态，给对象赋初值
//构造函数是类的一部分，他的名字跟类名相同，没有返回类型

//构造函数有以下几种类型:
//1，默认构造函数 ： 不带参数的构造函数。若程序员不定义，编译器会自动生成
class Myclass{
public:
    Myclass(){
        //默认构造函数
        cout << "default constructor" << endl;
    }
};

//2,参数化构造函数 ： 带有参数的构造函数，用于根据参数的不同值初始化对象
class Myclass{
public:
    int x;
    Myclass(int a){
        x = a;
        cout << "parameter constructor" << endl;
    }
};

//3, 拷贝构造函数：用于通过另一个对象来初始化新对象
class Myclass{
    public:
    int x;
    Myclass(const Myclass &obj){
        x = obj.x;
    }
};
//实际调用
#include <iostream>
using namespace std;

class MyClass {
public:
    int a;

    // 默认构造函数
    MyClass() {
        a = 0;
        cout << "Default Constructor called" << endl;
    }

    // 参数化构造函数
    MyClass(int x) {
        a = x;
        cout << "Parameterized Constructor called with value: " << a << endl;
    }

    // 拷贝构造函数
    MyClass(const MyClass &obj) {
        a = obj.a;
        cout << "Copy Constructor called" << endl;
    }
};

int main() {
    MyClass obj1;         // 调用默认构造函数
    MyClass obj2(10);     // 调用参数化构造函数
    MyClass obj3 = obj2;  // 调用拷贝构造函数
    return 0;
}

// 当你创建派生类对象时，首先会调用基类的构造函数，然后再调用派生类的构造函数。这是因为派生类需要依赖基类的部分进行初始化
// 为什么构造函数不能被继承？
// 构造函数的作用是初始化类的成员，因此每个类都有其自己的初始化需求。如果派生类直接继承基类的构造函数，那么派生类无法正确初始化自己新增的成员。
// 当派生类对象被创建时，它会首先调用基类的构造函数来初始化继承的部分，之后再执行派生类自己的构造函数以完成对象的完整初始化。
