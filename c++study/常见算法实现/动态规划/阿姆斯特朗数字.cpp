/**
 * @file
 * @brief 检查一个数字是否是 [阿姆斯特朗数字](https://en.wikipedia.org/wiki/Narcissistic_number)。
 *
 * @details
 * 阿姆斯特朗数字是一个数字，它是自身每个数字的和，每个数字都要提升到数字的位数。例如：153 是阿姆斯特朗数字，
 * 因为 153 = 1^3 + 5^3 + 3^3。
 *
 * 一些有效的阿姆斯特朗数字示例：
 * 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 153, 370, 371, 407, 1634, 8208, 9474, 54748,
 * 92727, 93084。
 *
 * 阿姆斯特朗数字也被称为自恋数字，如维基百科所述。
 *
 * @author [Shivam Singhal](https://github.com/shivhek25)
 * @author [David Leal](https://github.com/Panquesito7)
 */

#include <cassert>   /// 用于断言
#include <cmath>     /// 用于 std::pow
#include <iostream>  /// 用于输入输出操作

/**
 * @namespace
 * @brief 动态规划算法
 */
namespace dynamic_programming {

/**
 * @brief 检查给定的数字是否为阿姆斯特朗数字。
 * @param number 要检查的数字
 * @returns 如果给定的数字不是阿姆斯特朗数字则返回 false
 * @returns 如果给定的数字是阿姆斯特朗数字则返回 true
 */
template <typename T>
bool is_armstrong(const T &number) {
    int count = 0, temp = number, result = 0, rem = 0;

    // 计算给定数字的位数。
    // 例如：153 的位数为 3。
    while (temp != 0) {
        temp /= 10;
        count++;
    }

    // 检查阿姆斯特朗数字的计算，即在一个 n 位数字中，
    // 数字的和的每一位数提升到 n 次方等于原始数字。
    temp = number;
    while (temp != 0) {
        rem = temp % 10;  // 获取最后一位数字
        result += static_cast<T>(std::pow(rem, count));  // 计算每位的 n 次方并累加
        temp /= 10;  // 去掉最后一位数字
    }

    // 检查计算结果是否等于原始数字
    if (result == number) {
        return true;  // 如果相等，返回 true
    } else {
        return false; // 否则返回 false
    }
}
}  // namespace dynamic_programming

/**
 * @brief 自测实现
 * @returns void
 */
static void tests() {
    assert(dynamic_programming::is_armstrong(153) == true);   // 153 是阿姆斯特朗数字
    assert(dynamic_programming::is_armstrong(1) == true);     // 1 是阿姆斯特朗数字
    assert(dynamic_programming::is_armstrong(0) == true);     // 0 是阿姆斯特朗数字
    assert(dynamic_programming::is_armstrong(370) == true);   // 370 是阿姆斯特朗数字
    assert(dynamic_programming::is_armstrong(1634) == true);  // 1634 是阿姆斯特朗数字
    assert(dynamic_programming::is_armstrong(580) == false);  // 580 不是阿姆斯特朗数字
    assert(dynamic_programming::is_armstrong(15) == false);   // 15 不是阿姆斯特朗数字
    assert(dynamic_programming::is_armstrong(1024) == false); // 1024 不是阿姆斯特朗数字
    assert(dynamic_programming::is_armstrong(989) == false);  // 989 不是阿姆斯特朗数字
    assert(dynamic_programming::is_armstrong(103) == false);  // 103 不是阿姆斯特朗数字

    std::cout << "所有测试都已成功通过！\n"; // 输出测试成功信息
}

/**
 * @brief 主函数
 * @returns 0 退出时返回
 */
int main() {
    tests();  // 运行自测实现
    return 0;
}
