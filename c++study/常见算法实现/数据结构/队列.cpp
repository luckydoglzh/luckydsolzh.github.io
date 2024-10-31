#include <iostream>

// 定义节点结构体
struct node {
    int data;           // 节点数据
    struct node* next;  // 指向下一个节点的指针
};

// 定义队列类
class Queue {
    node* front = nullptr;  // 队列的前端指针
    node* rear = nullptr;   // 队列的后端指针

    // 禁用拷贝构造函数
    Queue(const Queue&) = delete;
    // 禁用赋值运算符
    Queue& operator=(const Queue&) = delete;

public:
    // 默认构造函数
    Queue() = default;
    
    // 析构函数，释放所有节点
    ~Queue() {
        while (front) {
            dequeue();
        }
    }

private:
    // 创建新节点
    void createNode(int val) {
        auto* nn = new node;  // 动态分配新节点
        nn->data = val;       // 设置节点数据
        nn->next = nullptr;   // 初始化指针为 nullptr
        front = nn;           // 前端指针指向新节点
        rear = nn;            // 后端指针也指向新节点
    }

public:
    // 入队操作
    void enqueue(int val) {
        if (front == nullptr || rear == nullptr) {  // 如果队列为空
            createNode(val);  // 创建新节点
        } else {
            node* nn = new node;  // 动态分配新节点
            nn->data = val;       // 设置节点数据
            rear->next = nn;      // 当前后端节点的下一个指向新节点
            nn->next = front;     // 新节点的下一个指向前端节点
            rear = nn;            // 后端指针指向新节点
        }
    }

    // 出队操作
    void dequeue() {
        if (front == nullptr) {  // 如果队列为空
            return;              // 无操作
        }
        const node* const n = front;  // 保存当前前端节点
        if (front == rear) {          // 如果队列中只有一个节点
            front = nullptr;          // 前端指针置为空
            rear = nullptr;           // 后端指针置为空
        } else {
            front = front->next;      // 前端指针指向下一个节点
            rear->next = front;       // 后端节点的下一个指向新的前端节点
        }
        delete n;                    // 删除旧的前端节点
    }

    // 遍历队列并打印节点数据
    void traverse() {
        if (front == nullptr) {  // 如果队列为空
            return;              // 无操作
        }
        const node* ptr = front;  // 指向前端节点
        do {
            std::cout << ptr->data << ' ';  // 打印节点数据
            ptr = ptr->next;       // 移动到下一个节点
        } while (ptr != front);   // 直到回到前端节点
        std::cout << '\n';        // 换行
    }
};

// 主函数
int main(void) {
    Queue q;                   // 创建队列实例
    q.enqueue(10);             // 入队 10
    q.enqueue(20);             // 入队 20
    q.enqueue(30);             // 入队 30
    q.enqueue(40);             // 入队 40
    q.enqueue(50);             // 入队 50
    q.enqueue(60);             // 入队 60
    q.enqueue(70);             // 入队 70
    q.traverse();              // 遍历并打印队列
    q.dequeue();               // 出队一个元素
    q.traverse();              // 遍历并打印队列
    return 0;                  // 正常退出
}
