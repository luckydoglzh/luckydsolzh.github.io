/**
 * @file
 * @brief 实现线性队列 [使用数组]
 * (https://www.geeksforgeeks.org/array-implementation-of-queue-simple/)。
 * @details
 * 线性队列是一种用于保存一系列值的数据结构，可以将值添加到队列末尾（enqueue），
 * 从队列头部移除（dequeue）并显示队列中的内容。
 * ### 算法
 * 可以通过增加 `rear` 变量的值来添加值，`rear` 指向数组的末尾，然后将新值赋给数组中 `rear` 的位置。
 *
 * 可以通过增加 `front` 变量的值来移除值，`front` 指向数组的第一个元素，因此前面的元素将不再被访问。
 *
 * @作者 [Pooja](https://github.com/pooja-git11)
 * @作者 [Farbod Ahmadian](https://github.com/farbodahm)
 */

#include <array>     /// 用于 std::array
#include <iostream>  /// 用于输入输出操作

constexpr uint16_t max_size{10};  ///< 队列的最大容量

/**
 * @命名空间 data_structures
 * @brief 数据结构的算法实现
 */
namespace data_structures {

/**
 * @命名空间 queue_using_array
 * @brief [使用数组实现的队列] (https://www.geeksforgeeks.org/array-implementation-of-queue-simple/)
 * 的函数实现。
 */
namespace queue_using_array {

/**
 * @brief Queue_Array 类，包含队列的主要数据以及数组的头尾索引。
 */
class Queue_Array {
 public:
    void enqueue(const int16_t&);  ///< 将元素添加到队列的末尾
    int dequeue();                 ///< 从队列的头部删除元素
    void display() const;          ///< 显示所有保存的数据
 private:
    int8_t front{-1};                     ///< 队列头部的索引
    int8_t rear{-1};                      ///< 队列尾部的索引
    std::array<int16_t, max_size> arr{};  ///< 存储所有数据的数组
};

/**
 * @brief 将新元素添加到队列的末尾
 * @param ele 要添加到队列末尾的元素
 */
void Queue_Array::enqueue(const int16_t& ele) {
    if (rear == arr.size() - 1) {
        std::cout << "\n队列已满";
    } else if (front == -1 && rear == -1) {
        front = 0;
        rear = 0;
        arr[rear] = ele;
    } else if (rear < arr.size()) {
        ++rear;
        arr[rear] = ele;
    }
}

/**
 * @brief 移除位于队列头部的元素
 * @returns 如果队列非空，则返回被删除的数据
 */
int Queue_Array::dequeue() {
    int8_t d{0};
    if (front == -1) {
        std::cout << "\n队列为空";
        return 0;
    } else if (front == rear) {
        d = arr.at(front);
        front = rear = -1;
    } else {
        d = arr.at(front++);
    }

    return d;
}

/**
 * @brief 实用函数，显示队列中的所有元素
 */
void Queue_Array::display() const {
    if (front == -1) {
        std::cout << "\n队列为空";
    } else {
        for (int16_t i{front}; i <= rear; ++i) std::cout << arr.at(i) << " ";
    }
}

}  // namespace queue_using_array
}  // namespace data_structures

/**
 * @brief 主函数
 * @details
 * 允许用户向队列中添加和删除值。
 * 也允许用户显示队列中的值。
 * @returns 程序退出时返回 0
 */
int main() {
    int op{0}, data{0};
    data_structures::queue_using_array::Queue_Array ob;

    std::cout << "\n1. 入队 (Insertion) ";
    std::cout << "\n2. 出队 (Deletion)";
    std::cout << "\n3. 显示 (Display)";
    std::cout << "\n4. 退出 (Exit)";
    while (true) {
        std::cout << "\n输入你的选择: ";
        std::cin >> op;
        if (op == 1) {
            std::cout << "输入数据: ";
            std::cin >> data;
            ob.enqueue(data);
        } else if (op == 2) {
            data = ob.dequeue();
            std::cout << "\n出队元素为:\t" << data;
        } else if (op == 3) {
            ob.display();
        } else if (op == 4) {
            exit(0);
        } else {
            std::cout << "\n选择无效";
        }
    }

    return 0;
}
