/**
 * @file
 * @brief 计算[双阶乘](https://en.wikipedia.org/wiki/Double_factorial): \f$n!!\f$
 *
 * 双阶乘是非负整数 `n` 的双阶乘，定义为与 `n` 奇偶性相同的所有整数的乘积。
 * <br/>双阶乘也称为一个数的半阶乘，记为 \f$n!!\f$
 */

#include <cassert>
#include <iostream>

/** 使用迭代方法计算双阶乘
 * @param n 输入的非负整数
 * @return 返回双阶乘的结果
 */
uint64_t double_factorial_iterative(uint64_t n) {
    uint64_t res = 1;
    for (uint64_t i = n;; i -= 2) {
        if (i == 0 || i == 1)
            return res;
        res *= i;
    }
    return res;
}

/** 使用递归方法计算双阶乘
 * <br/>对于较大的数字，递归可能会较为耗时。
 * @param n 输入的非负整数
 * @return 返回双阶乘的结果
 */
uint64_t double_factorial_recursive(uint64_t n) {
    if (n <= 1)
        return 1;
    return n * double_factorial_recursive(n - 2);
}

/** 测试函数，通过递归和迭代实现来检查双阶乘的正确性
 * 检查仅在调试构建中有效，因为使用了 `assert()` 语句。
 * @param [in] n 要检查双阶乘的数
 * @param [in] expected 期望的结果
 */
void test(uint64_t n, uint64_t expected) {
    assert(double_factorial_iterative(n) == expected);
    assert(double_factorial_recursive(n) == expected);
}

/**
 * 测试实现
 */
void tests() {
    std::cout << "测试 1:\t n=5\t...";
    test(5, 15);
    std::cout << "通过\n";

    std::cout << "测试 2:\t n=15\t...";
    test(15, 2027025);
    std::cout << "通过\n";

    std::cout << "测试 3:\t n=0\t...";
    test(0, 1);
    std::cout << "通过\n";
}

/**
 * 主函数
 */
int main() {
    tests();
    return 0;
}
