#include <cassert>    /// 用于 std::assert
#include <iostream>   /// 用于 std::cout
#include <memory>     /// 用于 std::unique_ptr
#include <stdexcept>  /// 用于 std::out_of_range

/**
 * @namespace
 * @brief data_structures
 */
namespace data_structures {
/**
 * @brief 堆栈的类表示
 * @tparam T 堆栈中元素的类型
 */
template <typename T>
class Stack {
 private:
    std::unique_ptr<T[]> stack;  ///< 智能指针指向堆栈数组
    int stackSize;               ///< 堆栈的最大大小
    int stackIndex;  ///< 指向堆栈顶元素的索引

 public:
    /**
     * @brief 构造新的 Stack 对象
     *
     * @param size 堆栈的最大大小
     */
    Stack(int size) : stackSize(size), stackIndex(-1), stack(new T[size]) {}

    /**
     * @brief 检查堆栈是否已满
     *
     * @return true 如果堆栈已满，false 否则
     */
    bool full() const { return stackIndex == stackSize - 1; }

    /**
     * @brief 检查堆栈是否为空
     * @return true 如果堆栈为空，false 否则
     */
    bool empty() const { return stackIndex == -1; }

    /**
     * @brief 将元素压入堆栈
     *
     * @param element 要压入堆栈的元素
     */
    void push(T element) {
        if (full()) {
            throw std::out_of_range("Stack overflow");  // 堆栈溢出异常
        } else {
            stack[++stackIndex] = element;  // 将元素放入堆栈
        }
    }

    /**
     * @brief 从堆栈弹出一个元素
     *
     * @return 弹出的元素
     * @throws std::out_of_range 如果堆栈为空
     */
    T pop() {
        if (empty()) {
            throw std::out_of_range("Stack underflow");  // 堆栈下溢异常
        }
        return stack[stackIndex--];  // 返回顶部元素并减少索引
    }

    /**
     * @brief 显示堆栈中的所有元素
     */
    void show() const {
        for (int i = 0; i <= stackIndex; i++) {
            std::cout << stack[i] << "\n";  // 输出堆栈中的元素
        }
    }

    /**
     * @brief 显示堆栈的顶元素
     *
     * @return 堆栈的顶元素
     * @throws std::out_of_range 如果堆栈为空
     */
    T topmost() const {
        if (empty()) {
            throw std::out_of_range("Stack underflow");  // 堆栈下溢异常
        }
        return stack[stackIndex];  // 返回顶部元素
    }

    /**
     * @brief 显示堆栈的底元素
     *
     * @return 堆栈的底元素
     * @throws std::out_of_range 如果堆栈为空
     */
    T bottom() const {
        if (empty()) {
            throw std::out_of_range("Stack underflow");  // 堆栈下溢异常
        }
        return stack[0];  // 返回底部元素
    }
};
}  // namespace data_structures

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    data_structures::Stack<int> stack(5);  // 创建大小为5的堆栈

    // 测试空堆栈和满堆栈的操作
    assert(stack.empty());
    assert(!stack.full());

    // 测试压入元素和检查顶元素
    stack.push(10);
    assert(stack.topmost() == 10);

    stack.push(20);
    assert(stack.topmost() == 20);

    stack.push(30);
    stack.push(40);
    stack.push(50);
    assert(stack.full());  // 堆栈已满

    // 测试堆栈溢出
    try {
        stack.push(60);
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack overflow");  // 确保抛出正确的异常
    }

    // 测试弹出元素
    assert(stack.pop() == 50);
    assert(stack.pop() == 40);
    assert(stack.pop() == 30);

    // 检查顶元素和底元素
    assert(stack.topmost() == 20);
    assert(stack.bottom() == 10);

    assert(stack.pop() == 20);
    assert(stack.pop() == 10);

    assert(stack.empty());
    assert(!stack.full());

    // 测试堆栈下溢
    try {
        stack.pop();
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack underflow");  // 确保抛出正确的异常
    }

    try {
        stack.topmost();
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack underflow");  // 确保抛出正确的异常
    }

    try {
        stack.bottom();
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack underflow");  // 确保抛出正确的异常
    }
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    test();  // 运行自测实现
    std::cout << "所有测试通过！" << std::endl;
    return 0;
}
