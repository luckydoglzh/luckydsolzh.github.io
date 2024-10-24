// explicit 是 C++ 中的关键字，主要用于构造函数和类型转换运算符，防止隐式转换的发生。它的主要作用是避免意外的自动类型转换，增加代码的可读性和安全性。

// 当一个构造函数标记为 explicit 时，它只能通过直接调用构造函数的方式进行类型转换，而不能使用隐式转换。例如：

// 没有 explicit 的情况（允许隐式转换）：
#include <iostream>

class MyClass {
public:
    MyClass(int x) {
        std::cout << "Constructor called with " << x << std::endl;
    }
};

int main() {
    MyClass obj1 = 10;  // 隐式转换：int 转 MyClass
    MyClass obj2(20);   // 显式调用构造函数
}

// 在上述代码中，MyClass obj1 = 10; 通过隐式转换调用了 MyClass 的构造函数。

// 使用 explicit 的情况（禁止隐式转换）：
#include <iostream>

class MyClass {
public:
    explicit MyClass(int x) {
        std::cout << "Constructor called with " << x << std::endl;
    }
};

int main() {
    // MyClass obj1 = 10;  // 错误：隐式转换被禁止
    MyClass obj2(20);      // 只能通过显式调用
}

// 2. 隐式转换与 explicit
// 隐式转换的行为可能会带来一些意外的问题，比如程序员意图不清的情况下发生了不必要的转换。使用 explicit 关键字可以防止这些问题发生。
#include <iostream>

class MyClass {
public:
    MyClass(int x) {
        std::cout << "Constructor called with " << x << std::endl;
    }
};

void printMyClass(const MyClass& obj) {
    std::cout << "Function called" << std::endl;
}

int main() {
    printMyClass(10);  // 隐式将 int 转换为 MyClass
}
// 在上面的代码中，printMyClass(10) 会隐式调用 MyClass 的构造函数，将 int 类型转换为 MyClass 对象。这种转换是隐式的，可能导致程序的行为不符合预期。

// 如果我们希望避免这种意外的隐式转换，可以将构造函数标记为 explicit：
#include <iostream>

class MyClass {
public:
    explicit MyClass(int x) {
        std::cout << "Constructor called with " << x << std::endl;
    }
};

void printMyClass(const MyClass& obj) {
    std::cout << "Function called" << std::endl;
}

int main() {
    // printMyClass(10);  // 错误：不能进行隐式转换
    printMyClass(MyClass(10));  // 正确：必须显式创建 MyClass 对象
}

// explicit 和模板
// 在 C++20 中，explicit 可以与模板参数结合使用，根据模板的条件来控制构造函数或转换运算符是否为显式的。示例：
#include <iostream>

template <typename T>
class MyClass {
public:
    explicit(sizeof(T) > 4) MyClass(T x) {
        std::cout << "Constructor called with " << x << std::endl;
    }
};

int main() {
    MyClass<int> obj1(10);  // 不是显式，因为 sizeof(int) <= 4
    // MyClass<double> obj2 = 3.14;  // 错误：显式构造函数禁止隐式转换
    MyClass<double> obj2(3.14);  // 正确：显式调用
}
