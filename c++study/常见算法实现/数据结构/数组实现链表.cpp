/**
 * \file
 * \brief 使用数组实现链表
 *
 * 指针实现的链表和数组实现的链表的区别：
 * 1. 用 -1 表示 NULL；
 * 2. 链表大小有限（在这里最多是 100 个节点）。但是我们可以通过将要删除的节点重新链接到列表中来重用它们。
 */

#include <iostream>

struct Node {
    int data; // 数据域
    int next; // 指向下一个节点的索引
};

Node AvailArray[100];  ///< 使用数组来模拟链表节点

int head = -1; // 链表的头节点索引，-1 表示空链表
int avail = 0; // 可用节点的起始索引
void initialise_list() {
    for (int i = 0; i <= 98; i++) {
        AvailArray[i].next = i + 1; // 初始化每个节点的 next 指针，形成链表
    }
    AvailArray[99].next = -1;  // 最后一个节点的 next 指针设为 -1，表示链表的结尾
}

/** 返回可用链表中第一个空闲节点的索引 */
int getnode() {
    int NodeIndexToBeReturned = avail; // 当前可用节点的索引
    avail = AvailArray[avail].next; // 更新可用节点列表的头节点
    return NodeIndexToBeReturned;
}

/** 删除指定索引的节点并将其放回可用列表中 */
void freeNode(int nodeToBeDeleted) {
    AvailArray[nodeToBeDeleted].next = avail; // 将删除节点的 next 指针指向当前可用节点列表
    avail = nodeToBeDeleted; // 更新可用节点列表头为删除节点
}

/** 在链表头部插入新节点 */
void insertAtTheBeginning(int data) {
    int newNode = getnode(); // 获取一个可用节点
    AvailArray[newNode].data = data; // 设置新节点的数据
    AvailArray[newNode].next = head; // 新节点的 next 指向当前链表的头节点
    head = newNode; // 更新头节点为新节点
}

/** 在链表尾部插入新节点 */
void insertAtTheEnd(int data) {
    int newNode = getnode(); // 获取一个可用节点
    int temp = head;
    while (AvailArray[temp].next != -1) { // 遍历到链表的最后一个节点
        temp = AvailArray[temp].next;
    }
    // temp 指向链表的最后一个节点
    AvailArray[newNode].data = data; // 设置新节点的数据
    AvailArray[newNode].next = -1; // 新节点的 next 指向 -1
    AvailArray[temp].next = newNode; // 将最后一个节点的 next 指向新节点
}

/** 显示链表中的所有元素 */
void display() {
    int temp = head;
    while (temp != -1) { // 遍历链表直到链表结尾
        std::cout << AvailArray[temp].data << "->"; // 打印当前节点的数据
        temp = AvailArray[temp].next; // 移动到下一个节点
    }
    std::cout << "-1" << std::endl; // 打印链表结尾标志
}

/** 主函数 */
int main() {
    initialise_list(); // 初始化链表
    int x, y, z;
    for (;;) {
        std::cout << "1. 在链表头插入" << std::endl;
        std::cout << "2. 在链表尾插入" << std::endl;
        std::cout << "3. 显示链表" << std::endl;
        std::cout << "4. 退出" << std::endl;
        std::cout << "输入您的选择：" << std::endl;
        std::cin >> z;
        switch (z) {
        case 1:
            std::cout << "输入要插入的数字：" << std::endl;
            std::cin >> x;
            insertAtTheBeginning(x); // 在链表头部插入元素
            break;
        case 2:
            std::cout << "输入要插入的数字：" << std::endl;
            std::cin >> y;
            insertAtTheEnd(y); // 在链表尾部插入元素
            break;
        case 3:
            std::cout << "链表中的元素按顺序如下：" << std::endl;
            display(); // 显示链表
            break;
        case 4:
            return 0; // 退出程序
        default:
            std::cout << "输入的选择不正确" << std::endl;
        }
    }

    return 0;
}
