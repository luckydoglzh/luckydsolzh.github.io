#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
typedef struct Node {
    int data;            // 节点中的数据
    struct Node* next;   // 指向下一个节点的指针
} Node;

// 定义链表结构，包含头指针、尾指针以及节点计数
typedef struct LinkedList {
    Node* head;          // 指向链表的头节点
    Node* tail;          // 指向链表的尾节点
    int size;            // 链表的节点数量
} LinkedList;
// 创建链表
LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}
// 增加头节点
void addAtHead(LinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head; // 新节点的下一个指向当前头节点
    list->head = newNode;       // 更新头指针

    if (list->tail == NULL) {   // 如果链表为空，尾指针也指向新节点
        list->tail = newNode;
    }

    list->size++; // 更新链表大小
}
// 添加尾节点
void addAtTail(LinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;       // 尾节点的下一个指向NULL

    if (list->tail != NULL) {   // 如果链表不为空
        list->tail->next = newNode; // 将当前尾节点的next指向新节点
    }
    
    list->tail = newNode;       // 更新尾指针

    if (list->head == NULL) {   // 如果链表为空，头指针也指向新节点
        list->head = newNode;
    }

    list->size++; // 更新链表大小
}
// 获取头节点数据
int getHead(LinkedList* list) {
    if (list->head != NULL) {
        return list->head->data;
    }
    return -1; // 如果链表为空，返回-1表示没有数据
}
// 获取尾节点数据
int getTail(LinkedList* list) {
    if (list->tail != NULL) {
        return list->tail->data;
    }
    return -1; // 如果链表为空，返回-1表示没有数据
}
// 获取链表节点数量
int getSize(LinkedList* list) {
    return list->size;
}
// 删除链表，释放内存
void deleteLinkedList(LinkedList* list) {
    Node* current = list->head;
    Node* next;

    // 逐个节点释放内存
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    // 释放链表结构
    free(list);
}
// 打印链表中的数据
void printList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
int main() {
    // 创建链表
    LinkedList* list = createLinkedList();

    // 添加节点
    addAtHead(list, 10);
    addAtHead(list, 20);
    addAtTail(list, 30);
    addAtTail(list, 40);

    // 打印链表
    printf("Linked List: ");
    printList(list);

    // 获取头节点和尾节点数据
    printf("Head: %d\n", getHead(list));
    printf("Tail: %d\n", getTail(list));

    // 获取链表节点数量
    printf("Size: %d\n", getSize(list));

    // 删除链表
    deleteLinkedList(list);

    return 0;
}
