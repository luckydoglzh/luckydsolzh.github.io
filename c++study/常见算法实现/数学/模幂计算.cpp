/**
 * @file
 * @brief C++ 程序实现模幂运算（迭代方式）。
 * @details 该任务是计算一个整数 a 的 b 次幂，在模 c 下的值。
 * @note 本方法的时间复杂度为 O(log b)。
 *
 * 示例：
 * (4^3) % 5 （其中 ^ 表示指数运算，% 表示模运算）
 * (4*4*4) % 5
 * (4 % 5) * ( (4*4) % 5 )
 * 4 * (16 % 5)
 * 4 * 1
 * 4
 * 我们可以验证结果：4^3 等于 64，而 64 模 5 等于 4。
 *
 * @author [Shri2206](https://github.com/Shri2206)
 */
#include <cassert>   /// 用于 assert 断言
#include <iostream>  /// 用于输入输出操作

/**
 * @namespace math
 * @brief 数学算法相关函数
 */
namespace math {
/**
 * @brief 该函数使用模幂运算计算 a 的 b 次幂模 c 的结果
 * @param a 整数底数
 * @param b 无符号整数指数
 * @param c 整数模数
 * @return a 的 b 次幂模 c 的结果
 */
uint64_t power(uint64_t a, uint64_t b, uint64_t c) {
    uint64_t ans = 1;  /// 初始化返回的结果为1
    a = a % c;         /// 如果 a 大于等于 c，更新 a
    if (a == 0) {
        return 0;  /// 如果 a 能被 c 整除，返回 0
    }
    while (b > 0) {
        /// 如果 b 是奇数，乘上 a
        if (b & 1) {
            ans = ((ans % c) * (a % c)) % c;
        }
        /// b 现在是偶数
        b = b >> 1;  /// b = b / 2
        a = ((a % c) * (a % c)) % c;  /// a 更新为 a 的平方模 c
    }
    return ans;
}

}  // namespace math

/**
 * @brief 测试 power 函数的功能
 * 包含测试用例和断言
 * @returns `void`
 */
static void test() {
    uint32_t test_case_1 = math::power(2, 5, 13);  /// 测试案例1：2^5 % 13
    assert(test_case_1 == 6);  /// 结果应该是6
    std::cout << "Test 1 Passed!" << std::endl;

    uint32_t test_case_2 = math::power(14, 7, 15);  /// 测试案例2：14^7 % 15
    assert(test_case_2 == 14);  /// 结果应该是14
    std::cout << "Test 2 Passed!" << std::endl;

    uint64_t test_case_3 = math::power(8, 15, 41);  /// 测试案例3：8^15 % 41
    assert(test_case_3 == 32);  /// 结果应该是32
    std::cout << "Test 3 Passed!" << std::endl;

    uint64_t test_case_4 = math::power(27, 2, 5);  /// 测试案例4：27^2 % 5
    assert(test_case_4 == 4);  /// 结果应该是4
    std::cout << "Test 4 Passed!" << std::endl;

    uint16_t test_case_5 = math::power(7, 3, 6);  /// 测试案例5：7^3 % 6
    assert(test_case_5 == 1);  /// 结果应该是1
    std::cout << "Test 5 Passed!" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main() {
    test();  // 执行测试
    return 0;
}
