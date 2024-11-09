/**
 * @file
 * @brief 计算给定数字的 [阶乘](https://en.wikipedia.org/wiki/Factorial)
 * @details 通过递归计算阶乘
 * \f[n! = n \times (n-1) \times (n-2) \times (n-3) \times \ldots \times 3 \times 2 \times 1
 *       = n \times (n-1)!\f]
 * 例如：
 * \f$5! = 5 \times 4! = 5 \times 4 \times 3 \times 2 \times 1 = 120\f$
 *
 * @author [Akshay Gupta](https://github.com/Akshay1910)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作

/**
 * @namespace
 * @brief 数学算法
 */
namespace math {

/**
 * @brief 计算给定数字的阶乘
 * @param n 需要计算阶乘的数字
 * @warning 参数的最大值为 20，因为 21! 无法用 64 位无符号整数表示
 */
uint64_t factorial(uint8_t n) {
    if (n > 20) {  // 如果 n 大于 20，抛出异常
        throw std::invalid_argument("maximum value is 20\n");
    }
    if (n == 0) {  // 阶乘的递归基准情况
        return 1;
    }
    return n * factorial(n - 1);  // 递归调用
}
}  // 数学算法命名空间

/**
 * @brief 自我测试函数
 * @returns void
 */
static void tests() {
    // 进行一系列的测试用例
    assert(math::factorial(1) == 1);  // 1! = 1
    assert(math::factorial(0) == 1);  // 0! = 1
    assert(math::factorial(5) == 120);  // 5! = 120
    assert(math::factorial(10) == 3628800);  // 10! = 3628800
    assert(math::factorial(20) == 2432902008176640000);  // 20! = 2432902008176640000
    std::cout << "所有测试已成功通过！\n";
}

/**
 * @brief 主函数
 * @returns 程序退出时返回 0
 */
int main() {
    tests();  // 运行自我测试函数
    return 0;
}
