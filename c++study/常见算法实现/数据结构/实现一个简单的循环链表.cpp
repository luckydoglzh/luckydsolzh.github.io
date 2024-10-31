/*
    A simple class for Circular Linear Linked List (循环线性链表的简单类)
*/
#include "cll.h"
using namespace std;

/* 构造函数 */
cll::cll() {
    head = NULL;  // 初始化头指针为空
    total = 0;    // 初始化链表节点总数为 0
}

/* 析构函数，无需实现 */
cll::~cll() { 
}

/* 显示链表的内容及元素总数 */
void cll::display() {
    if (head == NULL)  // 如果头指针为空，链表为空
        cout << "List is empty !" << endl;
    else {
        cout << "CLL list: ";
        node *current = head;
        for (int i = 0; i < total; i++) {  // 遍历整个链表
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << head->data << endl;  // 输出循环到头结点的数据
        cout << "Total element: " << total << endl;  // 输出元素总数
    }
}

/* 在链表头部插入一个新值 */
void cll::insert_front(int new_data) {
    node *newNode;
    newNode = new node;
    newNode->data = new_data;  // 将新节点的数据设置为 new_data
    newNode->next = NULL;
    if (head == NULL) {  // 如果链表为空，设置新节点为唯一节点
        head = newNode;
        head->next = head;  // 自引用形成循环
    } else {  // 如果链表非空
        node *current = head;
        while (current->next != head) {  // 找到尾节点
            current = current->next;
        }
        newNode->next = head;  // 新节点指向原头节点
        current->next = newNode;  // 尾节点指向新节点
        head = newNode;  // 更新头节点为新节点
    }
    total++;  // 增加节点总数
}

/* 在链表尾部插入一个新值 */
void cll::insert_tail(int new_data) {
    node *newNode;
    newNode = new node;
    newNode->data = new_data;  // 将新节点的数据设置为 new_data
    newNode->next = NULL;
    if (head == NULL) {  // 如果链表为空
        head = newNode;
        head->next = head;  // 自引用形成循环
    } else {  // 如果链表非空
        node *current = head;
        while (current->next != head) {  // 找到尾节点
            current = current->next;
        }
        current->next = newNode;  // 尾节点指向新节点
        newNode->next = head;  // 新节点指向头节点形成循环
    }
    total++;  // 增加节点总数
}

/* 获取链表中的元素总数 */
int cll::get_size() { return total; }

/* 如果找到指定元素则返回 true，否则返回 false */
bool cll::find_item(int item_to_find) {
    if (head == NULL) {  // 如果链表为空
        cout << "List is empty !" << endl;
        return false;
    } else {
        node *current = head;
        while (current->next != head) {  // 遍历链表查找元素
            if (current->data == item_to_find)  // 找到指定元素
                return true;
            current = current->next;
        }
        return false;  // 遍历完成未找到元素
    }
}

/* 重载解引用运算符，返回头节点的数据 */
int cll::operator*() { return head->data; }

/* 重载前置自增运算符，迭代器移至下一个节点 */
void cll::operator++() {
    if (head == NULL) {  // 如果链表为空
        cout << "List is empty !" << endl;
    } else {
        node *current = head;
        while (current->next != head) {  // 找到尾节点
            current = current->next;
        }
        current->next = head->next;  // 尾节点指向头节点的下一个节点
        head = head->next;  // 更新头节点
    }
    total--;  // 节点总数减一
}
