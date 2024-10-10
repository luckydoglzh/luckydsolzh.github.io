#include <stdio.h>
#include <stdlib.h>

// 定义栈节点结构
typedef struct StackNode {
    int data;                    // 存储数据
    struct StackNode* next;      // 指向下一个节点的指针
} StackNode;

// 定义栈结构
typedef struct Stack {
    StackNode* top;              // 栈顶节点
} Stack;

// 函数声明
Stack* createStack();
void push(Stack* stack, int data);
int pop(Stack* stack);
int peek(Stack* stack);
int isEmpty(Stack* stack);
void destroyStack(Stack* stack);

// 创建栈
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL; // 初始化栈顶指针为NULL
    return stack;
}

// 入栈
void push(Stack* stack, int data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = stack->top; // 新节点指向原来的栈顶
    stack->top = newNode;        // 更新栈顶为新节点
}

// 出栈
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow: cannot pop from an empty stack.\n");
        return -1; // 返回-1表示出栈失败
    }
    StackNode* temp = stack->top; // 保存当前栈顶节点
    int poppedData = temp->data;   // 获取栈顶数据
    stack->top = stack->top->next; // 更新栈顶为下一个节点
    free(temp);                    // 释放旧的栈顶节点
    return poppedData;             // 返回被弹出的数据
}

// 查看栈顶元素
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty: cannot peek.\n");
        return -1; // 返回-1表示栈为空
    }
    return stack->top->data; // 返回栈顶元素
}

// 检查栈是否为空
int isEmpty(Stack* stack) {
    return stack->top == NULL; // 栈顶指针为NULL则表示栈为空
}

// 销毁栈
void destroyStack(Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack); // 逐个出栈并释放内存
    }
    free(stack); // 释放栈结构本身
}

// 测试栈的功能
int main() {
    Stack* stack = createStack(); // 创建栈

    // 入栈操作
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    printf("Top element is: %d\n", peek(stack)); // 查看栈顶元素

    printf("Popped element: %d\n", pop(stack)); // 出栈操作
    printf("Popped element: %d\n", pop(stack)); // 出栈操作

    printf("Top element is: %d\n", peek(stack)); // 再次查看栈顶元素

    destroyStack(stack); // 销毁栈

    return 0;
}
