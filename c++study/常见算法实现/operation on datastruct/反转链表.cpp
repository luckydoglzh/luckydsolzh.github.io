#include <iostream>
using namespace std;

// 定义链表节点结构体
struct node {
    int val;  // 节点的值
    node *next;  // 指向下一个节点的指针
};

// 定义链表的头指针
node *start;

// 插入新节点到链表的末尾
void insert(int x) {
    node *t = start;
    if (start != NULL) {  // 如果链表不为空
        // 遍历链表直到最后一个节点
        while (t->next != NULL) {
            t = t->next;
        }
        // 创建新节点并将其插入到链表的末尾
        node *n = new node;
        t->next = n;
        n->val = x;
        n->next = NULL;  // 新节点的下一个节点指针为空
    } else {  // 如果链表为空
        // 创建新节点并将其设置为链表的头节点
        node *n = new node;
        n->val = x;
        n->next = NULL;
        start = n;
    }
}

// 递归反转链表
void reverse(node *p, node *q) {
    if (q->next == NULL) {  // 如果 q 是链表的最后一个节点
        q->next = p;  // 将 p 连接到 q 后面
        p->next = NULL;  // 使得 p 成为链表的最后一个节点
        start = q;  // 更新链表的头节点
        return;
    } else {
        // 递归反转链表的其余部分
        reverse(q, q->next);
        q->next = p;  // 将 q 连接到 p 后面
        p->next = NULL;  // 使得 p 成为链表的最后一个节点
    }
}

// 显示链表的所有元素
void show() {
    node *t = start;
    // 遍历链表并打印每个节点的值
    while (t != NULL) {
        cout << t->val << "\t";
        t = t->next;  // 移动到下一个节点
    }
}

int main() {
    // 插入节点到链表中
    insert(1);
    insert(2);
    insert(3);
    insert(4);
    insert(5);
    insert(6);

    // 反转链表
    reverse(start, start->next);

    // 显示链表
    show();

    return 0;
}
