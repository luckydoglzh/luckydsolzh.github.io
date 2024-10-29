/**
 * @file
 * @brief [计算阶乘中尾随零的数量](https://www.tutorialspoint.com/count-trailing-zeros-in-factorial-of-a-number-in-cplusplus) 的实现。
 * @details
 * 给定一个整数作为输入，目标是找到该数阶乘中尾随零的数量。
 * 一个数 N 的阶乘是 [1, N] 范围内所有数的乘积。
 *
 * 我们知道，只有当一个数是 10 的倍数或包含因子对 (2,5) 时才会有尾随零。
 * 对于任意大于 5 的数的阶乘，在其素因数分解中，2 的数量多于 5 的数量。
 * 将一个数除以 5 的幂数会给出其因数中 5 的数量。因此，5 的个数决定了尾随零的数量。
 * 
 * @author [Swastika Gupta](https://github.com/Swastyy)
 */

#include <cassert>   /// 用于断言（assert）
#include <iostream>  /// 用于输入输出操作

/**
 * @namespace bit_manipulation
 * @brief 位操作算法的命名空间
 */
namespace bit_manipulation {
/**
 * @namespace count_of_trailing_ciphers_in_factorial_n
 * @brief [计算阶乘中尾随零的数量](https://www.tutorialspoint.com/count-trailing-zeros-in-factorial-of-a-number-in-cplusplus) 的实现
 */
namespace count_of_trailing_ciphers_in_factorial_n {
/**
 * @brief 计算阶乘中尾随零的数量
 * @param n 要计算 `n!` 尾随零的数
 * @return count，`n!` 中的尾随零数量。
 */
uint64_t numberOfCiphersInFactorialN(uint64_t n) {
    // count 用于存储阶乘(n)中 5 的个数
    uint64_t count = 0;

    // 不断将 n 除以 5 的幂并更新 count
    for (uint64_t i = 5; n / i >= 1; i *= 5) {
        count += static_cast<uint64_t>(n) / i;
    }

    return count;
}
}  // namespace count_of_trailing_ciphers_in_factorial_n
}  // namespace bit_manipulation

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    // 第一个测试
    std::cout << "第一个测试 ";
    assert(bit_manipulation::count_of_trailing_ciphers_in_factorial_n::
               numberOfCiphersInFactorialN(395) == 97);
    std::cout << "通过" << std::endl;

    // 第二个测试
    std::cout << "第二个测试 ";
    assert(bit_manipulation::count_of_trailing_ciphers_in_factorial_n::
               numberOfCiphersInFactorialN(977) == 242);
    std::cout << "通过" << std::endl;

    // 第三个测试
    std::cout << "第三个测试 ";
    assert(bit_manipulation::count_of_trailing_ciphers_in_factorial_n::
               numberOfCiphersInFactorialN(871) == 215);
    std::cout << "通过" << std::endl;

    // 第四个测试
    std::cout << "第四个测试 ";
    assert(bit_manipulation::count_of_trailing_ciphers_in_factorial_n::
               numberOfCiphersInFactorialN(239) == 57);
    std::cout << "通过" << std::endl;

    // 第五个测试
    std::cout << "第五个测试 ";
    assert(bit_manipulation::count_of_trailing_ciphers_in_factorial_n::
               numberOfCiphersInFactorialN(0) == 0);
    std::cout << "通过" << std::endl;
}

/**
 * @brief 主函数
 * @returns 程序正常结束时返回 0
 */
int main() {
    test();  // 运行自测实现
    return 0;
}
