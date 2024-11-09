#include <iostream>

// 定义节点类
class Node {
 public:
    int val;      // 节点的值
    Node *next;   // 指向下一个节点的指针

    // 构造函数，用于初始化节点的值和指向下一个节点的指针
    Node(int v, Node *n) : val(v), next(n) {}
};

// 获取链表的大小
int getSize(Node *root) {
    // 如果链表为空，返回0
    if (root == NULL) {
        return 0;
    }
    // 递归调用，每次递归返回1，最终得到链表的大小
    return 1 + getSize(root->next);
}

/*
 * @brief 这个函数递归地删除链表的所有节点，并释放内存
 * @param root 链表的头指针
 * @warning 请确保每个节点的内存是通过 new 操作符分配的
 */
void deleteList(Node *const root) {
    // 如果链表不为空，继续递归删除下一个节点
    if (root != NULL) {
        deleteList(root->next);  // 删除下一个节点
        delete root;             // 删除当前节点
    }
}

int main() {
    // 初始化一个链表，链表大小为10，节点值从0到9
    Node *myList = new Node(0, NULL);  // 创建一个头节点
    Node *temp = myList;  // 临时指针用于遍历链表
    // 创建链表，总大小为10，节点值为1到9
    for (int i = 1; i < 10; i++) {
        temp->next = new Node(i, NULL);  // 创建一个新节点并连接到链表的末尾
        temp = temp->next;  // 更新临时指针
    }

    // 创建其他链表用于测试
    Node *secondList = new Node(0, NULL);  // 创建一个大小为1的链表
    Node *thirdList = NULL;                // 创建一个空链表，大小为0

    // 打印三个链表的大小
    std::cout << getSize(myList) << std::endl  // 打印 myList 的大小
              << getSize(secondList) << std::endl  // 打印 secondList 的大小
              << getSize(thirdList) << std::endl;  // 打印 thirdList 的大小

    // 删除所有创建的链表并释放内存
    deleteList(secondList);
    deleteList(myList);

    return 0;
}
