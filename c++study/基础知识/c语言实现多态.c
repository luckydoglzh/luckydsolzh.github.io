#include <stdio.h>
#include <stdlib.h>

// 定义一个结构体表示形状
typedef struct Shape {
    // 函数指针
    double (*area)(struct Shape* self); 
} Shape;

// 定义圆形结构体
typedef struct {
    Shape base; // 继承 Shape
    double radius;
} Circle;

// 定义矩形结构体
typedef struct {
    Shape base; // 继承 Shape
    double width;
    double height;
} Rectangle;

// 圆形面积计算
double circle_area(Shape* self) {
    Circle* circle = (Circle*)self; // 转换为 Circle 类型
    return 3.14159 * circle->radius * circle->radius;
}

// 矩形面积计算
double rectangle_area(Shape* self) {
    Rectangle* rect = (Rectangle*)self; // 转换为 Rectangle 类型
    return rect->width * rect->height;
}

int main() {
    // 创建圆形对象
    Circle* c = (Circle*)malloc(sizeof(Circle));
    c->base.area = circle_area; // 设置函数指针
    c->radius = 5.0;

    // 创建矩形对象
    Rectangle* r = (Rectangle*)malloc(sizeof(Rectangle));
    r->base.area = rectangle_area; // 设置函数指针
    r->width = 4.0;
    r->height = 6.0;

    // 计算并输出面积
    printf("Circle area: %.2f\n", c->base.area((Shape*)c)); // 使用基类指针调用
    printf("Rectangle area: %.2f\n", r->base.area((Shape*)r)); // 使用基类指针调用

    // 释放内存
    free(c);
    free(r);

    return 0;
}
