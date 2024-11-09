/**
 * @file
 * @brief 实现简单的 [模乘逆元](https://en.wikipedia.org/wiki/Modular_multiplicative_inverse) 算法
 *
 * @details
 * 该算法计算 x^{-1} \mod y 的模逆元，使用迭代方式实现
 */

#include <cassert>   /// 用于 assert
#include <iostream>  /// 用于输入输出操作

/**
 * @brief imod 函数
 * 计算 x 在模 y 下的模逆元，即 x^{-1} \mod y
 * @param x 需要计算模逆元的数
 * @param y 模数
 * @returns 返回模逆元
 */
uint64_t imod(uint64_t x, uint64_t y) {
    uint64_t aux = 0;  // 辅助变量
    uint64_t itr = 0;  // 迭代计数器

    do {  // 当没有找到模逆元时，继续运行算法
        aux = y * itr + 1;  // 计算辅助值
        itr++;  // 迭代计数器递增
    } while (aux % x);  // 如果 aux % x 非零，则继续循环

    return aux / x;  // 返回模逆元
}

/**
 * @brief 自测函数
 * 用于测试 imod 函数的正确性
 * @returns void
 */
static void test() {
    std::cout << "第一个测试案例... \n";
    // 对于 a = 3 和 b = 11，返回 4
    assert(imod(3, 11) == 4);
    std::cout << "\n通过测试！\n";

    std::cout << "第二个测试案例... \n";
    // 对于 a = 3 和 b = 26，返回 9
    assert(imod(3, 26) == 9);
    std::cout << "\n通过测试！\n";

    std::cout << "第三个测试案例... \n";
    // 对于 a = 7 和 b = 26，返回 15
    assert(imod(7, 26) == 15);
    std::cout << "\n通过测试！\n";

    std::cout << "\n所有测试用例已成功通过！\n";
}

/**
 * @brief 主函数
 * 执行自测
 * @returns 0 退出
 */
int main() {
    test();  // 执行自测
};
