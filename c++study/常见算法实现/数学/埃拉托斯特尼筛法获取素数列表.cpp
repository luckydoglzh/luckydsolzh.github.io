/**
 * @file
 * @brief 使用埃拉托斯特尼筛法获取素数列表
 * @details
 * 埃拉托斯特尼筛法是一种用于查找2到N之间所有素数的算法。
 *
 * 时间复杂度  : \f$O(N \cdot\log \log N)\f$
 * <br/>空间复杂度 : \f$O(N)\f$
 *
 * @see primes_up_to_billion.cpp prime_numbers.cpp
 */

#include <cassert>
#include <iostream>
#include <vector>

/**
 * 该函数通过筛选法查找素数并消除它们的倍数。
 * 包含了一个常见的优化，从 `p * p` 开始消除素数 p 的倍数，因为所有小于 p * p 的倍数已经被消除。
 * @param N 需要检查的素数范围（N）
 * @return is_prime 一个大小为 `N + 1` 的布尔向量，标识 `i`^th 数字是否是素数
 */
std::vector<bool> sieve(uint32_t N) {
    std::vector<bool> is_prime(N + 1, true);  // 默认所有数字都是素数
    is_prime[0] = is_prime[1] = false;  // 0 和 1 不是素数
    for (uint32_t i = 2; i * i <= N; i++) {  // 从2开始遍历到 sqrt(N)
        if (is_prime[i]) {  // 如果 i 是素数
            for (uint32_t j = i * i; j <= N; j += i) {  // 从 i^2 开始标记所有倍数为非素数
                is_prime[j] = false;
            }
        }
    }
    return is_prime;  // 返回包含所有素数信息的布尔向量
}

/**
 * 该函数打印出所有的素数到标准输出（STDOUT）
 * @param N 需要检查的素数范围（N）
 * @param is_prime 一个大小为 `N + 1` 的布尔向量，标识 `i`^th 数字是否是素数
 */
void print(uint32_t N, const std::vector<bool> &is_prime) {
    for (uint32_t i = 2; i <= N; i++) {  // 从2开始遍历到N
        if (is_prime[i]) {  // 如果 i 是素数
            std::cout << i << ' ';  // 打印素数
        }
    }
    std::cout << std::endl;  // 换行
}

/**
 * 测试函数
 */
void tests() {
  //                    0      1      2     3     4      5     6      7     8      9      10
  std::vector<bool> ans{false, false, true, true, false, true, false, true, false, false, false};
  assert(sieve(10) == ans);  // 断言结果正确
}

/**
 * 主函数
 */
int main() {
    tests();  // 执行测试

    uint32_t N = 100;  // 查找素数的范围是100
    std::vector<bool> is_prime = sieve(N);  // 获取素数标记数组
    print(N, is_prime);  // 打印所有素数
    return 0;
}
