/**
 * @file
 * @brief 使用*递归形式*的[欧几里得算法](https://en.wikipedia.org/wiki/Euclidean_algorithm)
 * 计算两个整数的最大公约数（GCD）
 *
 * @see gcd_iterative_euclidean.cpp, gcd_of_n_numbers.cpp
 */
#include <iostream>
#include <stdexcept>  // 用于处理异常

/**
 * @brief 使用递归计算两个整数的最大公约数（GCD）
 *
 * @param num1 第一个整数
 * @param num2 第二个整数
 * @returns 两个整数的最大公约数
 * @throws std::domain_error 如果输入的整数小于或等于 0，则抛出异常
 */
int gcd(int num1, int num2) {
    if (num1 <= 0 || num2 <= 0) {  // 确保输入的数大于 0
        throw std::domain_error("欧几里得算法只适用于正整数");
    }

    // 如果两个数相等，直接返回其中一个作为 GCD
    if (num1 == num2) {
        return num1;
    }

    // 基础情况：如果其中一个数为 0，则返回另一个数
    if (num1 == 0) {
        return num2;
    }
    if (num2 == 0) {
        return num1;
    }

    // 递归步骤：较大的数减去较小的数，递归调用 gcd
    if (num1 > num2) {
        return gcd(num1 - num2, num2);
    }
    return gcd(num1, num2 - num1);
}

/**
 * @brief 主函数
 * @returns 0 表示程序正常退出
 */
int main() {
    // 输出两个数 120 和 7 的 GCD
    std::cout << "120 和 7 的最大公约数是: " << (gcd(120, 7)) << std::endl;

    // 测试输入负数的异常处理
    try {
        std::cout << "-120 和 10 的最大公约数是: " << gcd(-120, 10) << std::endl;
    } catch (const std::domain_error &e) {
        std::cout << "错误处理成功：" << e.what() << std::endl;
    }

    // 输出其他测试用例的 GCD
    std::cout << "312 和 221 的最大公约数是: " << (gcd(312, 221)) << std::endl;
    std::cout << "289 和 204 的最大公约数是: " << (gcd(289, 204)) << std::endl;

    return 0;
}
