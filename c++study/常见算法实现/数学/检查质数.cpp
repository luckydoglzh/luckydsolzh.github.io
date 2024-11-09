/**
 * @file
 * @brief 一个简单的程序，用于检查给定的数字是否为[质数](https://en.wikipedia.org/wiki/Primality_test)。
 * @details 质数是只能被 1 和它本身整除的正整数。质数必须是正整数且属于自然数集合。
 * 大多数质数是奇数，2 是唯一的偶质数。该算法利用这些信息来查找质数。
 * 其他质数检查方法可以参考：https://cp-algorithms.com/algebra/primality_tests.html#practice-problems
 *
 * 作者：[Omkar Langhe](https://github.com/omkarlanghe)
 * 作者：[ewd00010](https://github.com/ewd00010)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作

/**
 * @namespace
 * @brief 数学算法
 */
namespace math {
/**
 * @brief 检查给定的数字是否为质数。
 * @param num 待检查的数字。
 * @return 如果数字是质数，返回 true。
 * @return 如果数字不是质数，返回 false。
 */
bool is_prime(int64_t num) {
    /*!
     * 使用前三个条件判断来排除所有不可能为质数的数字。例如：除了 2 以外，没有其他偶数可以是质数。
     * 通过这些条件的检查后，从 5 开始检查潜在因数，每次循环增加 i 为 6，然后检查 i 和 i+2 是否为 num 的因数。
     * 如果 num 有任何因数，则返回 false。否则，如果循环结束且未找到因数，则返回 true。
     */
    if (num <= 1) {
        return false;
    } else if (num == 2 || num == 3) {
        return true;
    } else if (num % 2 == 0 || num % 3 == 0) {
        return false;
    } else {
        for (int64_t i = 5; i * i <= num; i = i + 6) {
            if (num % i == 0 || num % (i + 2) == 0) {
                return false;
            }
        }
    }
    return true;
}
}  // namespace math

/**
 * @brief 自测函数
 * @returns void
 */
static void tests() {
    assert(math::is_prime(1) == false);   // 1 不是质数
    assert(math::is_prime(2) == true);    // 2 是质数
    assert(math::is_prime(3) == true);    // 3 是质数
    assert(math::is_prime(4) == false);   // 4 不是质数
    assert(math::is_prime(-4) == false);  // -4 不是质数
    assert(math::is_prime(7) == true);    // 7 是质数
    assert(math::is_prime(-7) == false);  // -7 不是质数
    assert(math::is_prime(19) == true);   // 19 是质数
    assert(math::is_prime(50) == false);  // 50 不是质数
    assert(math::is_prime(115249) == true); // 115249 是质数

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
