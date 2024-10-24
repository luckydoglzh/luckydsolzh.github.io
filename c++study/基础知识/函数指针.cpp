// C++ 中的函数指针是指向函数的指针，可以通过它来调用某个函数。函数指针使得函数可以像普通变量一样被传递、返回或者存储在数据结构中，从而提供了一种灵活的方式来进行回调和实现多态行为。
// 函数指针在实现回调机制、策略模式以及某些动态操作时非常有用。

// 1. 基本语法
// 函数指针的声明和使用涉及函数的返回类型、参数类型和指针符号。
#include <iostream>

// 一个简单的函数
int add(int a, int b) {
    return a + b;
}

int main() {
    // 声明一个指向返回类型为 int，参数为两个 int 的函数的指针
    int (*funcPtr)(int, int);

    // 将函数 add 的地址赋值给函数指针
    funcPtr = &add;  // & 可省略

    // 通过函数指针调用函数
    int result = funcPtr(3, 4);  // 等同于 add(3, 4)
    std::cout << "Result: " << result << std::endl;

    return 0;
}

// 2. 函数指针的分解
int (*funcPtr)(int, int);
// 分解这个声明：

// int 表示函数的返回类型。
// (*funcPtr) 表示这是一个指针，指向一个函数。
// (int, int) 表示函数的参数列表，该函数有两个 int 参数。
// 因此，funcPtr 是一个指向具有两个 int 参数并返回 int 类型的函数的指针。

// 3. 函数指针作为参数
// 函数指针可以作为参数传递给其他函数。这样可以实现某种回调机制，即把一个函数传递给另一个函数执行。

// 示例：函数指针作为参数
#include <iostream>

// 定义两个简单的函数
int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

// 定义一个函数，该函数接受函数指针作为参数
void compute(int (*operation)(int, int), int x, int y) {
    std::cout << "Result: " << operation(x, y) << std::endl;
}

int main() {
    // 传递函数指针，使用不同的运算函数
    compute(add, 5, 3);       // 输出 8
    compute(multiply, 5, 3);  // 输出 15

    return 0;
}


// 4. 函数指针的返回类型
// 函数指针还可以作为函数的返回类型。这样可以通过某个函数动态地返回不同的函数指针，以实现不同的逻辑。
#include <iostream>

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

// 函数返回函数指针
int (*getOperation(char op))(int, int) {
    if (op == '+') {
        return add;
    } else if (op == '*') {
        return multiply;
    }
    return nullptr;
}

int main() {
    // 获取一个运算函数
    int (*operation)(int, int) = getOperation('+');
    
    if (operation) {
        std::cout << "Result: " << operation(5, 3) << std::endl;  // 输出 8
    }

    operation = getOperation('*');
    if (operation) {
        std::cout << "Result: " << operation(5, 3) << std::endl;  // 输出 15
    }

    return 0;
}


// 5. 指向类成员函数的指针
#include <iostream>

class MyClass {
public:
    int add(int a, int b) {
        return a + b;
    }
};

int main() {
    MyClass obj;

    // 声明一个指向 MyClass 的成员函数的指针
    int (MyClass::*funcPtr)(int, int) = &MyClass::add;

    // 通过对象和成员函数指针调用函数
    int result = (obj.*funcPtr)(3, 4);
    std::cout << "Result: " << result << std::endl;

    return 0;
}

// 6. 指向静态成员函数的指针
// 由于静态成员函数不依赖于对象，因此静态成员函数指针和普通函数指针类似，可以直接调用。
#include <iostream>

class MyClass {
public:
    static int add(int a, int b) {
        return a + b;
    }
};

int main() {
    // 指向静态成员函数的指针
    int (*funcPtr)(int, int) = &MyClass::add;

    // 调用静态成员函数
    int result = funcPtr(3, 4);
    std::cout << "Result: " << result << std::endl;

    return 0;
}


// 函数指针是一种指向函数的指针，允许通过该指针调用函数。
// 可以将函数指针作为参数传递，实现回调函数的机制。
// 函数也可以返回函数指针，从而实现动态函数选择。
// 类的成员函数和静态成员函数也可以通过函数指针来调用，但成员函数指针的使用方式与普通函数略有不同。