/**
 * @file
 * @brief 程序用于检查一个数字是否为[阿姆斯特朗/水仙花数](https://en.wikipedia.org/wiki/Narcissistic_number)
 * 
 * @details
 * 阿姆斯特朗数或[水仙花数](https://en.wikipedia.org/wiki/Narcissistic_number)
 * 是一个数，该数的每个位上的数字的 k 次方之和等于该数本身，其中 k 为该数的位数。
 * 
 * 假设 n 是水仙花数，公式如下：
 * \f[F_b(n) = \sum_{i=0}^{k-1}d_{i}^{k}\f]，
 * 其中 \f$ b > 1 \f$，\f$ F_b : \N \to \N \f$，
 * \f$ k = \lfloor log_b n\rfloor\f$ 是该数在基数 b 下的位数，
 * \f$ d_i = \frac{n mod b^{i+1} - n mod b^{i}}{b^{i}} \f$ 表示数的每一位。
 * 
 * @author [Neeraj Cherkara](https://github.com/iamnambiar)
 */
#include <cassert>   /// 用于断言
#include <cmath>     /// 用于 std::pow
#include <iostream>  /// 用于输入输出操作

/**
 * @brief 计算数字的位数
 * @param num 数字
 * @return 位数
 */
int number_of_digits(int num) {
    int total_digits = 0;
    while (num > 0) {
        num = num / 10;
        ++total_digits;
    }
    return total_digits;
}

/**
 * @brief 检查数字是否为阿姆斯特朗数
 * @param number 要检查的数字
 * @return 如果数字是阿姆斯特朗数，则返回 `true`
 * @return 如果数字不是阿姆斯特朗数，则返回 `false`
 */
bool is_armstrong(int number) {
    // 如果数字小于 0，则不是阿姆斯特朗数
    if (number < 0) {
        return false;
    }

    int sum = 0;
    int temp = number;
    // 找到数字的位数
    int total_digits = number_of_digits(number);
    while (temp > 0) {
        int rem = temp % 10;
        // 将每个位上的数字的 total_digits 次方相加
        sum += static_cast<int>(std::pow(rem, total_digits));
        temp = temp / 10;
    }
    return number == sum;
}

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    // is_armstrong(370) 返回 true。
    assert(is_armstrong(370) == true);
    // is_armstrong(225) 返回 false。
    assert(is_armstrong(225) == false);
    // is_armstrong(-23) 返回 false。
    assert(is_armstrong(-23) == false);
    // is_armstrong(153) 返回 true。
    assert(is_armstrong(153) == true);
    // is_armstrong(0) 返回 true。
    assert(is_armstrong(0) == true);
    // is_armstrong(12) 返回 false。
    assert(is_armstrong(12) == false);

    std::cout << "所有测试均已成功通过！\n";
}

/**
 * @brief 主函数
 * @returns 退出时返回 0
 */
int main() {
    test();  // 运行自测实现
    return 0;
}
