#include <stdio.h>
#include <stdlib.h>

// 定义队列节点结构
typedef struct Node {
    int data;                // 节点中的数据
    struct Node* next;       // 指向下一个节点的指针
} Node;

// 定义队列结构
typedef struct Queue {
    Node* front;            // 指向队列的头节点
    Node* rear;             // 指向队列的尾节点
} Queue;

// 创建队列
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}
// 入队操作
void enqueue(Queue* queue, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL; // 新节点的next指向NULL

    if (queue->rear != NULL) { // 如果队列不为空
        queue->rear->next = newNode; // 将当前尾节点的next指向新节点
    }
    
    queue->rear = newNode; // 更新队列的尾指针

    if (queue->front == NULL) { // 如果队列为空，更新头指针
        queue->front = newNode;
    }
}
// 出队操作
int dequeue(Queue* queue) {
    if (queue->front == NULL) { // 检查队列是否为空
        printf("Queue is empty!\n");
        return -1; // 返回-1表示队列为空
    }

    Node* temp = queue->front; // 临时保存头节点
    int data = temp->data; // 获取头节点的数据
    queue->front = queue->front->next; // 更新头指针

    // 如果队列变为空，更新尾指针
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp); // 释放被移除节点的内存
    return data; // 返回出队的数据
}
// 查看队列头元素
int peek(Queue* queue) {
    if (queue->front == NULL) { // 检查队列是否为空
        printf("Queue is empty!\n");
        return -1; // 返回-1表示队列为空
    }
    return queue->front->data; // 返回头节点的数据
}
// 检查队列是否为空
int isEmpty(Queue* queue) {
    return queue->front == NULL; // 如果头指针为NULL，队列为空
}
// 删除队列
void deleteQueue(Queue* queue) {
    while (!isEmpty(queue)) {
        dequeue(queue); // 逐个出队并释放内存
    }
    free(queue); // 最后释放队列结构体
}
int main() {
    Queue* queue = createQueue();

    // 入队操作
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    // 查看队列头元素
    printf("Front element: %d\n", peek(queue));

    // 出队操作
    printf("Dequeued: %d\n", dequeue(queue));
    printf("Dequeued: %d\n", dequeue(queue));

    // 查看队列头元素
    printf("Front element: %d\n", peek(queue));

    // 检查队列是否为空
    printf("Is queue empty? %s\n", isEmpty(queue) ? "Yes" : "No");

    // 删除队列
    deleteQueue(queue);

    return 0;
}
