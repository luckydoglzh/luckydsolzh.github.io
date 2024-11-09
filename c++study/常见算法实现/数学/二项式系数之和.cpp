/**
 * @file
 * @brief 算法计算给定正整数的二项式系数之和
 * @details
 * 给定一个正整数 n，任务是找到二项式系数的和，即：
 * nC0 + nC1 + nC2 + ... + nCn-1 + nCn
 * 通过数学归纳法可以证明，这个和等于 2^n
 * @see 了解更多：https://en.wikipedia.org/wiki/Binomial_coefficient#Sums_of_the_binomial_coefficients
 * @author [muskan0719](https://github.com/muskan0719)
 */
#include <cassert>   /// 用于断言
#include <iostream>  /// 用于 std::cin 和 std::cout

/**
 * @namespace math
 * @brief 数学算法
 */
namespace math {

/**
 * 计算二项式系数的和
 * @param n 输入的整数
 * @return 返回二项式系数的和，即 2^n
 */
uint64_t binomialCoeffSum(uint64_t n) {
    // 计算 2^n
    return (1 << n);  // 使用位移操作计算 2 的 n 次方
}
}  // namespace math

/**
 * 测试 binomialCoeffSum 函数的功能
 * 包含测试用例和断言语句
 * @returns `void` 
 */
static void test() {
    // 测试用例 1：当 n = 2 时，二项式系数的和应为 4 (2^2)
    int test_case_1 = math::binomialCoeffSum(2);
    assert(test_case_1 == 4);  // 断言测试结果为 4
    std::cout << "Test_case_1 Passed!" << std::endl;

    // 测试用例 2：当 n = 3 时，二项式系数的和应为 8 (2^3)
    int test_case_2 = math::binomialCoeffSum(3);
    assert(test_case_2 == 8);  // 断言测试结果为 8
    std::cout << "Test_case_2 Passed!" << std::endl;

    // 测试用例 3：当 n = 4 时，二项式系数的和应为 16 (2^4)
    int test_case_3 = math::binomialCoeffSum(4);
    assert(test_case_3 == 16);  // 断言测试结果为 16
    std::cout << "Test_case_3 Passed!" << std::endl;

    // 测试用例 4：当 n = 5 时，二项式系数的和应为 32 (2^5)
    int test_case_4 = math::binomialCoeffSum(5);
    assert(test_case_4 == 32);  // 断言测试结果为 32
    std::cout << "Test_case_4 Passed!" << std::endl;

    // 测试用例 5：当 n = 7 时，二项式系数的和应为 128 (2^7)
    int test_case_5 = math::binomialCoeffSum(7);
    assert(test_case_5 == 128);  // 断言测试结果为 128
    std::cout << "Test_case_5 Passed!" << std::endl;
}

/**
 * @brief 主函数
 * @returns 程序退出时返回 0
 */
int main() {
    test();  // 执行测试函数
    return 0;  // 程序正常退出
}
