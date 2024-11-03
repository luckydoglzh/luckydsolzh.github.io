/**
 * @brief 使用队列数据结构实现堆栈数据结构
 * @details
 * 在 Stack 类中使用 2 个队列，我们可以轻松实现堆栈数据结构，
 * 但在 push 函数中会进行大量计算。
 *
 * 使用的参考文献:
 * [StudyTonight](https://www.studytonight.com/data-structures/stack-using-queue)
 * @author [tushar2407](https://github.com/tushar2407)
 */
#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作
#include <queue>     /// 用于队列数据结构

/**
 * @namespace data_structures
 * @brief 数据结构算法
 */
namespace data_structures {
/**
 * @namespace stack_using_queue
 * @brief [使用队列实现堆栈](https://www.studytonight.com/data-structures/stack-using-queue) 的函数
 */
namespace stack_using_queue {
/**
 * @brief 堆栈类实现基本的堆栈数据结构方法
 */
struct Stack {
    std::queue<int64_t> main_q;       ///< 存储堆栈当前状态的主队列
    std::queue<int64_t> auxiliary_q;  ///< 用于执行中间操作以实现堆栈的辅助队列
    uint32_t current_size = 0;        ///< 存储堆栈当前大小

    /**
     * 返回堆栈顶部元素
     * @returns 堆栈的顶部元素
     */
    int top() { return main_q.front(); }  // 返回主队列的队头元素

    /**
     * @brief 将元素插入堆栈顶部
     * @param val 将要插入堆栈的元素
     * @returns void
     */
    void push(int val) {
        auxiliary_q.push(val);  // 将元素推入辅助队列
        while (!main_q.empty()) {  // 将主队列中的所有元素转移到辅助队列
            auxiliary_q.push(main_q.front());
            main_q.pop();
        }
        swap(main_q, auxiliary_q);  // 交换主队列和辅助队列
        current_size++;  // 更新堆栈大小
    }

    /**
     * @brief 从堆栈中移除顶部元素
     * @returns void
     */
    void pop() {
        if (main_q.empty()) {  // 如果主队列为空，无法弹出元素
            return;
        }
        main_q.pop();  // 移除队头元素
        current_size--;  // 更新堆栈大小
    }

    /**
     * @brief 实用函数返回堆栈的当前大小
     * @returns 当前堆栈的大小
     */
    int size() { return current_size; }  // 返回堆栈当前大小
};
}  // namespace stack_using_queue
}  // namespace data_structures

/**
 * @brief 自测试实现
 * @returns void
 */
static void test() {
    data_structures::stack_using_queue::Stack s;  // 创建堆栈对象
    s.push(1);  /// 将元素插入堆栈
    s.push(2);  /// 将元素插入堆栈
    s.push(3);  /// 将元素插入堆栈

    assert(s.size() == 3);  /// 堆栈大小应为 3

    assert(s.top() == 3);  /// 堆栈顶部元素应为 3

    s.pop();               /// 移除堆栈顶部元素
    assert(s.top() == 2);  /// 现在堆栈顶部元素应为 2

    s.pop();  /// 移除堆栈顶部元素
    assert(s.top() == 1);  /// 现在堆栈顶部元素应为 1

    s.push(5);             /// 将元素插入堆栈
    assert(s.top() == 5);  /// 现在堆栈顶部元素应为 5

    s.pop();               /// 移除堆栈顶部元素
    assert(s.top() == 1);  /// 现在堆栈顶部元素应为 1

    assert(s.size() == 1);  /// 堆栈大小应为 1
}

/**
 * @brief 主函数
 * 创建一个堆栈并向其中推入一些值。
 * 通过一系列对堆栈的推送和弹出操作，
 * 演示上述自定义堆栈的功能。
 * @returns 0 正常退出
 */
int main() {
    test();  // 运行自测试实现
    return 0;  // 程序正常结束
}
