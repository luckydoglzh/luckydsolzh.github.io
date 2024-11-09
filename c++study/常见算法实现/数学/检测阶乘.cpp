/**
 * @file
 * @brief 一个简单的程序，用于检查给定的数字是否为某个数字的[阶乘](https://en.wikipedia.org/wiki/Factorial)。
 *
 * @details 阶乘数是 k! 的和，其中 k 是任何正整数。https://www.mathsisfun.com/numbers/factorial.html
 *
 * 作者：[Divyajyoti Ukirde](https://github.com/divyajyotiuk)
 * 作者：[ewd00010](https://github.com/ewd00010)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输出

/**
 * @namespace
 * @brief 数学算法
 */
namespace math {
/**
 * @brief 检查给定的数字是否为某个数字的阶乘。
 * @param n 需要检查的数字。
 * @return 如果数字是阶乘，返回 true。
 * @return 如果数字不是阶乘，返回 false。
 */
bool is_factorial(uint64_t n) {
    if (n <= 0) {  // 阶乘数只能是正整数
        return false;
    }

    /*!
     * 这个循环实际上是反向计算阶乘的过程，和普通阶乘相反，我们不是在乘，而是在除。
     * 我们从 i = 2 开始，因为 i = 1 对除法没有影响。
     */
    int i = 2;
    while (n % i == 0) {
        n = n / i;
        i++;
    }

    /*!
     * 如果 n 是某个阶乘的和，它应该一直被除到变成 1
     */
    return (n == 1);
}
}  // namespace math

/**
 * @brief 自测函数
 * @returns void
 */
static void tests() {
    assert(math::is_factorial(50) == false);   // 50 不是阶乘
    assert(math::is_factorial(720) == true);   // 720 是 6! (6 阶乘)
    assert(math::is_factorial(0) == false);    // 0 不是阶乘
    assert(math::is_factorial(1) == true);     // 1 是 0! 和 1!（两者的阶乘都是 1）
    assert(math::is_factorial(479001600) == true); // 479001600 是 12! (12 阶乘)
    assert(math::is_factorial(-24) == false);  // -24 不是阶乘

    std::cout << "所有测试已成功通过！" << std::endl;
}

/**
 * @brief 主函数
 * @returns 程序退出状态，0 表示正常退出
 */
int main() {
    tests();  // 运行自测函数
    return 0;
}
