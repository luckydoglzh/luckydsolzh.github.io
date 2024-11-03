/**
 * @author [shoniavika](https://github.com/shoniavika)
 * @file
 *
 * 使用两个栈实现队列。
 */

#include <cassert>
#include <iostream>
#include <stack>

namespace {
/**
 * @brief 队列数据结构，以 FIFO (先进先出) 的方式存储元素。
 * @tparam T 队列中存储的数据类型
 */
template <typename T>
class MyQueue {
 private:
    std::stack<T> s1, s2;  // 两个栈，用于实现队列的操作

 public:
    /**
     * 队列的构造函数
     */
    MyQueue() = default;

    /**
     * 将元素 x 插入到队列的末尾
     */
    void push(T x);

    /**
     * 从队列的头部移除一个元素
     */
    const T& pop();

    /**
     * 返回队列的第一个元素，但不移除它
     */
    const T& peek() const;

    /**
     * 判断队列是否为空
     */
    bool empty() const;
};

/**
 * 将元素添加到队列末尾
 */
template <typename T>
void MyQueue<T>::push(T x) {
    while (!s2.empty()) {
        s1.push(s2.top());  // 将 s2 中的元素移到 s1 中
        s2.pop();
    }
    s2.push(x);              // 将新元素插入到 s2 中
    while (!s1.empty()) {
        s2.push(s1.top());   // 将 s1 中的元素移回到 s2 中
        s1.pop();
    }
}

/**
 * 从队列的头部移除元素
 */
template <typename T>
const T& MyQueue<T>::pop() {
    const T& temp = MyQueue::peek();  // 获取队首元素
    s2.pop();                         // 从 s2 中移除队首元素
    return temp;
}

/**
 * 返回队列的头部元素，不移除它
 */
template <typename T>
const T& MyQueue<T>::peek() const {
    if (!empty()) {
        return s2.top();  // 返回 s2 的顶部元素，即队列的头部元素
    }
    std::cerr << "队列为空" << std::endl;
    exit(0);
}

/**
 * 检查队列是否为空
 */
template <typename T>
bool MyQueue<T>::empty() const {
    return s2.empty() && s1.empty();  // 如果 s1 和 s2 都为空，则队列为空
}
}  // namespace

/**
 * 测试函数
 */
void queue_test() {
    MyQueue<int> que;
    std::cout << "测试 #1\n";
    que.push(2);
    que.push(5);
    que.push(0);
    assert(que.peek() == 2);
    assert(que.pop() == 2);
    assert(que.peek() == 5);
    assert(que.pop() == 5);
    assert(que.peek() == 0);
    assert(que.pop() == 0);
    assert(que.empty() == true);
    std::cout << "通过\n";

    std::cout << "测试 #2\n";
    que.push(-1);
    assert(que.empty() == false);
    assert(que.peek() == -1);
    assert(que.pop() == -1);
    std::cout << "通过\n";

    MyQueue<double> que2;
    std::cout << "测试 #3\n";
    que2.push(2.31223);
    que2.push(3.1415926);
    que2.push(2.92);

    assert(que2.peek() == 2.31223);
    assert(que2.pop() == 2.31223);
    assert(que2.peek() == 3.1415926);
    assert(que2.pop() == 3.1415926);
    assert(que2.peek() == 2.92);
    assert(que2.pop() == 2.92);
    std::cout << "通过\n";
}

/**
 * 主函数，调用测试函数
 */
int main() {
    queue_test();
    return 0;
}
