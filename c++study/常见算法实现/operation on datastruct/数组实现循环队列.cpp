#include <iostream>
using namespace std;

// 定义队列大小为 10
int queue[10];
int front = 0;  // 队列的前端，指向队列的第一个元素
int rear = 0;   // 队列的尾端，指向队列的最后一个元素
int count = 0;  // 当前队列中元素的个数

// 入队操作，将元素插入队列
void Enque(int x) {
    // 判断队列是否已满
    if (count == 10) {
        cout << "\nOverflow";  // 如果队列满了，输出溢出信息
    } else {
        // 将元素 x 插入队列尾部
        queue[rear] = x;
        // 更新尾指针，队列是循环的，所以使用取余操作
        rear = (rear + 1) % 10;
        // 增加元素个数
        count++;
    }
}

// 出队操作，删除队列头部的元素
void Deque() {
    // 判断队列是否为空
    if (front == rear) {
        cout << "\nUnderflow";  // 如果队列为空，输出下溢信息
    } else {
        // 输出被删除的元素
        cout << "\n" << queue[front] << " deleted";
        // 更新头指针，队列是循环的，所以使用取余操作
        front = (front + 1) % 10;
        // 减少元素个数
        count--;
    }
}

// 打印队列中的所有元素
void show() {
    // 遍历队列，输出从头指针到尾指针之间的所有元素
    for (int i = 0; i < count; i++) {
        // 使用循环队列的方式输出元素
        cout << queue[(i + front) % 10] << "\t";
    }
}

// 主函数，提供一个菜单与用户交互
int main() {
    int ch, x;
    do {
        // 显示菜单
        cout << "\n1. Enque";  // 入队
        cout << "\n2. Deque";  // 出队
        cout << "\n3. Print";  // 打印队列
        cout << "\nEnter Your Choice : ";  // 提示输入
        cin >> ch;  // 读取用户输入
        if (ch == 1) {
            cout << "\nInsert : ";  // 提示输入插入的值
            cin >> x;  // 读取要插入的元素
            Enque(x);  // 调用入队函数
        } else if (ch == 2) {
            Deque();  // 调用出队函数
        } else if (ch == 3) {
            show();  // 调用打印队列函数
        }
    } while (ch != 0);  // 当用户选择退出时结束

    return 0;
}
