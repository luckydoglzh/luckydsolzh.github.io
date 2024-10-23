//const 是 C++ 中非常重要的关键字，它用于指示某个值或对象不可修改
#include <iostream>
using namespace
// 1. 常量变量
// const 关键字可以用来声明常量，意味着该变量的值在初始化后不能再被修改。
const int a = 10;
a = 20; // 错误：a 是常量，不能修改


// 2. 指针中的 const
// 指针的 const 使用有四种常见情况：
// a) 指向常量的指针
const int* ptr = &a;
// ptr 是指向 int 类型常量的指针，意味着不能通过 ptr 修改指针所指向的值，但 ptr 本身可以指向其他变量。
*ptr = 5;   // 错误：不能修改指针所指向的值
ptr = &b;   // 合法：可以修改指针本身，使其指向其他地址

// b) 常量指针
int* const ptr = &a;
// ptr 是一个常量指针，意味着 ptr 本身不能改变，始终指向同一个地址，但可以通过 ptr 修改指向的值。
*ptr = 5;   // 合法：可以修改指针指向的值
ptr = &b;   // 错误：不能修改指针本身

// c) 指向常量的常量指针
const int* const ptr = &a;
// ptr 是一个指向常量的常量指针，意味着既不能修改指针指向的值，也不能修改指针本身。
*ptr = 5;   // 错误：不能修改指针指向的值
ptr = &b;   // 错误：不能修改指针本身

// d) 普通指针
*ptr = 5;   // 合法：可以修改指针指向的值
ptr = &b;   // 合法：可以修改指针本身

// 3. 函数参数中的 const
// const 可以用于函数参数，防止在函数体中修改传递的参数。
// a) 传递指针或引用参数
// 当传递指针或引用参数时，使用 const 可以防止函数修改参数。
void func1(const int* ptr) {
    // *ptr = 5;  // 错误：不能修改指针所指向的值
}
// 如果不希望在函数中修改传递的参数，特别是当传递大型对象时，使用 const 引用可以避免复制：
void func2(const string& str) {
    // str 是只读的
}
// 优点：避免对象拷贝的开销，同时防止函数修改该对象。

// 4. 返回值的 const
// a) const 返回值
// 当函数返回一个 const 值时，返回值不能被修改。
const int func() {
    return 10;
}

int a = func();
a = 20;  // 合法：a 是 func() 的返回值副本，可以修改
func() = 20;  // 错误：不能对函数返回值赋值，因为返回值是 const

// b) 返回常量引用
// 如果函数返回的是常量引用，调用者不能通过该引用修改返回值。
const int& func() {
    static int x = 10;
    return x;
}

func() = 20;  // 错误：不能修改返回的 const 引用

// 5. 成员函数中的 const
// const 成员函数保证该函数不会修改类的成员变量。通常用于访问器（getter）函数。
class MyClass {
public:
    int getValue() const {
        return value;
    }
    void setValue(int val) {
        value = val;
    }
private:
    int value;
};
// 在 getValue() 函数后面的 const 表示这个函数不会修改 value 或任何其他成员变量，保证了 const 对象可以安全调用该函数。

// 6. 类对象的 const
// const 类对象表示该对象不能修改其成员变量，只有 const 成员函数可以调用。
const MyClass obj;
obj.setValue(10);   // 错误：不能修改常量对象
obj.getValue();     // 合法：可以调用 const 成员函数

// 7. mutable 修饰符
// const 成员函数不能修改类成员变量，但如果你希望某些成员变量在 const 函数中依然可以修改，使用 mutable 关键字可以实现：
class MyClass {
public:
    void myFunc() const {
        mutableVar = 10;  // 在 const 函数中依然可以修改
    }
private:
    mutable int mutableVar;
};

// 8. 顶层 const 和底层 const
// 顶层 const：表示该对象本身是常量（如 const int a）。
// 底层 const：表示通过该对象不能修改其指向的内容（如 const int* p，指针指向的值不能修改）。
const int a = 10;    // 顶层 const
const int* p = &a;   // 底层 const
int* const p2 = &a;  // 顶层 const

// const 是 C++ 中一个非常灵活的关键字，主要用于确保程序的安全性和稳定性。理解 const 的不同用法有助于：

// 防止意外修改数据。
// 提高代码的可读性和可维护性。
// 优化性能，例如通过传递 const 引用来避免不必要的拷贝操作。
// 在实践中，尽量使用 const，特别是在函数参数、返回值和类成员函数中，这是编写健壮、安全代码的好习惯。