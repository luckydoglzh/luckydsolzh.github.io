/**
 * @file
 * @brief 实现 [N-bonacci](http://oeis.org/wiki/N-bonacci_numbers) 数列
 *
 * @details
 * 在一般的 N-bonacci 序列中，
 * 我们通过将前 N 个数的和来生成下一个数。
 *
 * 例如，3-bonacci 序列如下：
 * 0, 0, 1, 1, 2, 4, 7, 13, 24, 44, 81
 * 在此代码中，我们接收 N 和 M 作为输入，其中 M 是要打印的 N-bonacci 数列的项数。
 *
 * @author [Swastika Gupta](https://github.com/Swastyy)
 */

#include <cassert>   /// 用于 assert
#include <iostream>  /// 用于 std::cout
#include <vector>    /// 用于 std::vector

/**
 * @namespace math
 * @brief 数学算法
 */
namespace math {
/**
 * @namespace n_bonacci
 * @brief [N-bonacci](http://oeis.org/wiki/N-bonacci_numbers) 数列实现相关函数
 */
namespace n_bonacci {
/**
 * @brief 计算 N-bonacci 数列的前 m 项
 * @param n N-bonacci 中的 N 值
 * @param m 要打印的 N-bonacci 数列项数
 * @returns 返回 N-bonacci 数列（作为一个向量）
 */
std::vector<uint64_t> N_bonacci(const uint64_t &n, const uint64_t &m) {
    std::vector<uint64_t> a(
        m, 0);  // 创建一个大小为 m 的数组，初始值为 0
    if (m < n || n == 0) {
        return a;  // 如果 m 小于 n 或者 n 为 0，则返回全零的数组
    }

    a[n - 1] = 1;  /// 初始化 (n-1) 项为 1，这是前 N 项 0 的和
    if (n == m) {
        return a;  // 如果 n 等于 m，直接返回当前数组
    }
    a[n] = 1;  /// 同理，(N+1) 项为 1，这是前 N 项的和
    for (uint64_t i = n + 1; i < m; i++) {
        // 这是一个优化的解决方案，时间复杂度为 O(M)，并且额外空间复杂度为 O(M)
        // 在这里我们使用滑动窗口的概念，通过给定的公式计算当前项
        a[i] = 2 * a[i - 1] - a[i - 1 - n];  // 根据公式计算当前项
    }
    return a;
}
}  // namespace n_bonacci
}  // namespace math

/**
 * @brief 自测函数
 * 用于验证 N-bonacci 数列函数的正确性
 * @returns void
 */
static void test() {
    struct TestCase {
        const uint64_t n;  // N-bonacci 的 N 值
        const uint64_t m;  // 要打印的项数
        const std::vector<uint64_t> expected;  // 预期的输出结果
        TestCase(const uint64_t in_n, const uint64_t in_m,
                 std::initializer_list<uint64_t> data)
            : n(in_n), m(in_m), expected(data) {
            assert(data.size() == m);  // 确保预期结果的大小与 m 相等
        }
    };
    const std::vector<TestCase> test_cases = {
        TestCase(0, 0, {}),
        TestCase(0, 1, {0}),
        TestCase(0, 2, {0, 0}),
        TestCase(1, 0, {}),
        TestCase(1, 1, {1}),
        TestCase(1, 2, {1, 1}),
        TestCase(1, 3, {1, 1, 1}),
        TestCase(5, 15, {0, 0, 0, 0, 1, 1, 2, 4, 8, 16, 31, 61, 120, 236, 464}),
        TestCase(
            6, 17,
            {0, 0, 0, 0, 0, 1, 1, 2, 4, 8, 16, 32, 63, 125, 248, 492, 976}),
        TestCase(56, 15, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})};

    for (const auto &tc : test_cases) {
        assert(math::n_bonacci::N_bonacci(tc.n, tc.m) == tc.expected);  // 验证每个测试案例
    }
    std::cout << "测试通过！" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    test();  // 执行自测
    return 0;
}
