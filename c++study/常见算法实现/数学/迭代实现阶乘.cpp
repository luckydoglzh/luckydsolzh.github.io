/**
 * @file
 * @brief 迭代实现[阶乘](https://en.wikipedia.org/wiki/Factorial)
 *
 * @author
 * [Renjian-buchai](https://github.com/Renjian-buchai)
 *
 * @details 通过迭代方法计算阶乘。
 * \f[n! = n\times(n-1)\times(n-2)\times(n-3)\times\ldots\times3\times2\times1
 *       = n\times(n-1)!\f]
 * 例如：
 * \f$4! = 4\times3! = 4\times3\times2\times1 = 24\f$
 *
 * @example
 *
 * 5! = 5 * 4 * 3 * 2 * 1
 *
 * 递归实现阶乘的伪代码：
 *
 * function factorial(n):
 *     if n == 1:
 *         return 1
 *     else:
 *         return factorial(n-1)
 *
 */

#include <cassert>    // 用于断言
#include <cstdint>    // 用于整数类型
#include <exception>  // 用于 std::invalid_argument
#include <iostream>   // 用于 std::cout

/**
 * @namespace
 * @brief 数学算法命名空间
 */
namespace math {

/**
 * @brief 迭代方法计算阶乘。
 * @param n 要计算的阶乘的数值。
 * @return 阶乘结果。
 * @note 0! = 1。
 * @warning 最大支持20，因为 C++ 中没有 128 位整数。21! 的结果为 1.419e+19，
 * 并非 21!，而是 (21! % UINT64_MAX)。
 */
uint64_t iterativeFactorial(uint8_t n) {
    if (n > 20) {
        throw std::invalid_argument("最大支持的 n 值为 20");
    }

    // 1 是乘法的单位元。
    uint64_t accumulator = 1;

    while (n > 1) {
        accumulator *= n;
        --n;
    }

    return accumulator;
}

}  // namespace math

/**
 * @brief 自测试函数，用于测试 iterativeFactorial 函数。
 * @note 其中有一个特殊情况：0! = 1。
 */
static void test() {
    // 特殊情况测试
    std::cout << "异常情况测试 \n"
                 "输入: 0 \n"
                 "期望输出: 1 \n\n";
    assert(math::iterativeFactorial(0) == 1);

    // 基本情况
    std::cout << "基本情况测试 \n"
                 "输入: 1 \n"
                 "期望输出: 1 \n\n";
    assert(math::iterativeFactorial(1) == 1);

    // 小数测试
    std::cout << "小数测试 \n"
                 "输入: 5 \n"
                 "期望输出: 120 \n\n";
    assert(math::iterativeFactorial(5) == 120);

    // 中等数测试
    std::cout << "中等数测试 \n"
                 "输入: 10 \n"
                 "期望输出: 3628800 \n\n";
    assert(math::iterativeFactorial(10) == 3628800);

    // 最大值测试
    std::cout << "最大值测试 \n"
                 "输入: 20 \n"
                 "期望输出: 2432902008176640000\n\n";
    assert(math::iterativeFactorial(20) == 2432902008176640000);

    // 异常测试
    std::cout << "异常测试 \n"
                 "输入: 21 \n"
                 "期望输出: 抛出异常 \n";

    bool wasExceptionThrown = false;
    try {
        math::iterativeFactorial(21);
    } catch (const std::invalid_argument&) {
        wasExceptionThrown = true;
    }
    assert(wasExceptionThrown);

    std::cout << "所有测试都已成功通过。\n";
}

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main() {
    test();  // 运行自测试函数
    return 0;
}
