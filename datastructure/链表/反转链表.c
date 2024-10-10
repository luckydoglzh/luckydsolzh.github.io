#include <stdio.h>
#include <stdlib.h>
//反转链表本质就是反转指针指向顺序
//伪代码如下
//next = cur->next;
//cur->next = per;
//per = cur;
//cur = next;
// 定义链表节点结构
typedef struct Node {
    int data;            // 节点中的数据
    struct Node* next;   // 指向下一个节点的指针
} Node;

// 反转链表
Node* reverseList(Node* head) {
    Node* prev = NULL;   // 前一个节点
    Node* current = head; // 当前节点
    Node* next = NULL;   // 下一个节点

    while (current != NULL) {
        next = current->next; // 保存下一个节点
        current->next = prev; // 反转当前节点的指针

        prev = current;       // 将 prev 指向当前节点
        current = next;       // 移动到下一个节点
    }
    
    return prev; // 新的头节点
}
