#include <iostream>
using namespace std;
//纯虚函数很有意思，
//1，定义接口。纯虚函数使得类成为抽象类，意味着这个类不能被实例化。
//抽象类提供了一个接口，定义了子类必须实现的功能。
class Shape {
public:
    virtual void draw() = 0; // 纯虚函数
    virtual double area() = 0; // 纯虚函数
};

class Circle : public Shape {
public:
    void draw() {
        cout << "Drawing a circle" << endl;
    }
    double area() {
        return 3.14 * radius * radius; // 具体实现
    }
};

class Square : public Shape {
public:
    void draw() {
        cout << "Drawing a square" << endl;
    }
    double area() {
        return side * side; // 具体实现
    }
};

//2，强制子类实现某些功能
//派生类必须实现纯虚函数
//这样可以确保一致性和代码规范


//3，提供多态性
//运行时多态：通过纯虚函数，基类指针/引用可以指向任何派生类的对象。  使得运行时选择调用哪个派生类来实现
void renderShape(Shape& shape) {
    shape.draw(); // 调用派生类的 draw() 方法
}

int main() {
    Circle c;
    Square s;
    renderShape(c); // 输出 "Drawing a circle"
    renderShape(s); // 输出 "Drawing a square"
}

//4,隐藏实现细节
// 封装：抽象类可以隐藏具体实现的细节，用户只需要关注接口而不需要关心具体的实现。这样可以降低代码耦合，提高代码的可维护性。
// 示例：用户可以使用 Shape 接口来绘制图形，而不需要了解 Circle 和 Square 的具体实现细节。

// 5，支持多种实现
// 灵活性：通过定义抽象类和纯虚函数，可以根据需求实现不同的派生类。这使得代码可以更容易地扩展和修改，而无需更改已有的代码。
// 示例：未来可以添加一个 Triangle 类，只需实现 draw() 和 area() 方法，而不需要修改现有的 Shape 类或其他派生类。