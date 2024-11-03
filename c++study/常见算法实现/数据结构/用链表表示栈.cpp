#include <iostream>

// 节点结构体定义
struct node {
    int val;        // 节点存储的值
    node *next;    // 指向下一个节点的指针
};

node *top_var;  // 指向栈顶节点的指针

// 将新元素压入栈中
void push(int x) {
    node *n = new node;  // 创建新节点
    n->val = x;          // 设置节点的值
    n->next = top_var;   // 新节点的下一个指针指向当前栈顶
    top_var = n;         // 更新栈顶指针
}

// 从栈中弹出元素
void pop() {
    if (top_var == nullptr) {  // 检查栈是否为空
        std::cout << "\nUnderflow";  // 栈下溢
    } else {
        node *t = top_var;  // 临时指针保存当前栈顶节点
        std::cout << "\n" << t->val << " deleted";  // 输出删除的值
        top_var = top_var->next;  // 更新栈顶指针指向下一个节点
        delete t;  // 释放原栈顶节点的内存
    }
}

// 显示栈中所有元素
void show() {
    node *t = top_var;  // 临时指针从栈顶开始
    while (t != nullptr) {  // 遍历栈中的节点
        std::cout << t->val << "\n";  // 输出节点值
        t = t->next;  // 移动到下一个节点
    }
}

// 主函数
int main() {
    int ch = 0, x = 0;  // 初始化选择和输入值
    do {
        // 显示菜单
        std::cout << "\n0. Exit or Ctrl+C";  // 退出选项
        std::cout << "\n1. Push";             // 压入元素选项
        std::cout << "\n2. Pop";              // 弹出元素选项
        std::cout << "\n3. Print";            // 打印栈内容选项
        std::cout << "\nEnter Your Choice: "; // 输入选择提示
        std::cin >> ch;  // 读取用户输入的选择
        switch (ch) {
            case 0:
                break;  // 退出
            case 1:
                std::cout << "\nInsert : ";  // 输入要压入的值提示
                std::cin >> x;  // 读取要压入的值
                push(x);  // 调用压入函数
                break;
            case 2:
                pop();  // 调用弹出函数
                break;
            case 3:
                show();  // 调用显示函数
                break;
            default:
                std::cout << "Invalid option!\n";  // 无效选项提示
                break;
        }
    } while (ch != 0);  // 循环直到用户选择退出

    return 0;  // 程序正常结束
}
