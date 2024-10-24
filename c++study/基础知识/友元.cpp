// C++ 中的 友元 是一种特殊的机制，它允许一个类授予另一个类或函数访问其私有（private）或受保护（protected）成员的权限。

// 1. 友元函数
// 友元函数可以访问类的私有和受保护成员，即使它不是该类的成员函数。友元函数可以是全局函数、类的成员函数，或者是某个类的静态成员函数。
#include <iostream>

class MyClass {
private:
    int value;

public:
    MyClass(int v) : value(v) {}

    // 声明 friend 函数
    friend void printValue(const MyClass& obj);
};

// 友元函数定义
void printValue(const MyClass& obj) {
    std::cout << "Value is: " << obj.value << std::endl;  // 访问私有成员
}

int main() {
    MyClass obj(10);
    printValue(obj);  // 调用友元函数
    return 0;
}
// 在这个例子中，printValue 不是 MyClass 的成员函数，但由于它被声明为友元函数，它可以访问 MyClass 的私有成员 value。

// 2. 友元类
// 友元类是一个类，它可以访问另一个类的私有和受保护成员。通过 friend class 关键字，一个类可以声明另一个类为友元，从而允许这个友元类访问其所有成员。
#include <iostream>

class A {
private:
    int secret;

public:
    A(int s) : secret(s) {}

    // 声明 class B 是 class A 的友元类
    friend class B;
};

class B {
public:
    void showSecret(A& obj) {
        // 访问 A 的私有成员
        std::cout << "Secret is: " << obj.secret << std::endl;
    }
};

int main() {
    A a(42);
    B b;
    b.showSecret(a);  // 访问 class A 的私有成员
    return 0;
}


// 3. 友元的作用和使用场景
// 友元主要用于解决某些类之间需要紧密协作的场景。例如，某些类可能需要直接访问另一个类的内部实现，但我们不希望公开这些实现细节。通过友元机制，这些类可以共享数据，而不会破坏封装。

// 常见的使用场景包括：

// 操作符重载：例如，通过友元函数实现某些全局运算符（如 << 和 >>）对私有数据的访问。
// 辅助类或函数：有时类可能需要与辅助类共享私有数据，友元机制可以实现这样的需求。
// 设计模式：例如在某些设计模式中，两个类之间的强关联需要共享私有信息，友元可以确保类之间的高效协作。
// 4. 友元不是继承
// 需要注意的是，友元不是继承机制。友元只是授予访问权限，它并不会继承其他类的行为或特性。友元的作用是帮助类之间的合作，而不是通过继承来实现多态或代码复用。

// 5. 友元的缺点
// 尽管友元提供了访问权限，但它可能会破坏类的封装性。一个类对外部世界暴露其私有实现，可能导致较高的耦合性。因此，友元应该被慎重使用，避免滥用导致代码维护困难。