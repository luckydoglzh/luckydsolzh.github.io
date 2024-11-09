/**
 * @file
 * @brief 检查两个数是否为[亲和数对](https://en.wikipedia.org/wiki/Amicable_numbers)的C++程序
 *
 * @details
 * 亲和数对是指两个正整数，其中每个数的所有适当除数之和等于另一个数。
 *
 * @note 适当除数是指除选定的数字本身外，可以整除该数字且结果为正整数的任何正整数。例如，1、2 和 5 是 10 的适当除数。
 *
 * 作者：[iamnambiar](https://github.com/iamnambiar)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作

/**
 * @brief 数学算法
 * @namespace math
 */
namespace math {
/**
 * @brief 计算一个整数的所有适当除数之和的函数
 * @param num 被选定的数字
 * @return 数字的适当除数之和
 */
int sum_of_divisor(int num) {
    // 用于存储所有适当除数之和的变量
    int sum = 1;
    // 下面的循环条件通过减少到数字的平方根来降低时间复杂度
    for (int div = 2; div * div <= num; ++div) {
        // 检查 'div' 是否为 'num' 的除数
        if (num % div == 0) {
            // 如果两个除数相同，只添加一次到 'sum'
            if (div == (num / div)) {
                sum += div;
            } else {
                // 如果两个除数不同，则将两者都添加到 'sum'
                sum += (div + (num / div));
            }
        }
    }
    return sum;
}

/**
 * @brief 检查一对数字是否为亲和数对的函数
 * @param x 第一个数字
 * @param y 第二个数字
 * @return 如果是亲和数对，返回 `true`
 * @return 如果不是亲和数对，返回 `false`
 */
bool are_amicable(int x, int y) {
    return (sum_of_divisor(x) == y) && (sum_of_divisor(y) == x);
}
}  // namespace math

/**
 * @brief 自测函数
 * @returns void
 */
static void tests() {
    assert(math::are_amicable(220, 284) == true);
    assert(math::are_amicable(6368, 6232) == true);
    assert(math::are_amicable(458, 232) == false);
    assert(math::are_amicable(17296, 18416) == true);
    assert(math::are_amicable(18416, 17296) == true);

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
