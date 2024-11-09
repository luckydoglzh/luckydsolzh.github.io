/**
 * @file
 * @brief 一个算法用于计算斐波那契数列的和: \f$\mathrm{F}(n) +
 * \mathrm{F}(n+1) + .. + \mathrm{F}(m)\f$
 * @details 使用矩阵快速幂计算斐波那契数列的和:
 * \f$\mathrm{F}(n) + \mathrm{F}(n+1) + .. + \mathrm{F}(m)\f$ ，
 * 其中 \f$\mathrm{F}(i)\f$ 表示第 i 个斐波那契数。注意 F(0) = 0, F(1) = 1。
 * 来源参考:
 * https://stackoverflow.com/questions/4357223/finding-the-sum-of-fibonacci-numbers
 * \author [Sarthak Sahu](https://github.com/SarthakSahu1009)
 */

#include <cassert>   /// 用于 assert
#include <iostream>  /// 用于 std::cin 和 std::cout
#include <vector>    /// 用于 std::vector

/**
 * @namespace math
 * @brief 数学算法命名空间
 */
namespace math {
/**
 * @namespace fibonacci_sum
 * @brief 用于计算斐波那契数列和的函数: \f$\mathrm{F}(n) +
 * \mathrm{F}(n+1) + .. + \mathrm{F}(m)\f$
 */
namespace fibonacci_sum {
using matrix = std::vector<std::vector<uint64_t> >;  // 定义矩阵类型

/**
 * 函数用于矩阵乘法
 * @param T 矩阵1
 * @param A 矩阵2
 * @returns 返回结果矩阵
 */
math::fibonacci_sum::matrix multiply(const math::fibonacci_sum::matrix &T,
                                     const math::fibonacci_sum::matrix &A) {
    math::fibonacci_sum::matrix result(2, std::vector<uint64_t>(2, 0));

    // 矩阵相乘
    result[0][0] = T[0][0] * A[0][0] + T[0][1] * A[1][0];
    result[0][1] = T[0][0] * A[0][1] + T[0][1] * A[1][1];
    result[1][0] = T[1][0] * A[0][0] + T[1][1] * A[1][0];
    result[1][1] = T[1][0] * A[0][1] + T[1][1] * A[1][1];

    return result;
}

/**
 * 函数用于计算矩阵 A 的幂 A^n。
 * @param T 矩阵
 * @param ex 幂指数
 * @returns 返回结果矩阵
 */
math::fibonacci_sum::matrix power(math::fibonacci_sum::matrix T, uint64_t ex) {
    math::fibonacci_sum::matrix A{{1, 1}, {1, 0}};
    if (ex == 0 || ex == 1) {
        return T;
    }

    T = power(T, ex / 2);
    T = multiply(T, T);
    if (ex & 1) {  // 如果指数是奇数，再乘一次 A
        T = multiply(T, A);
    }
    return T;
}

/**
 * 函数用于计算从 0 到 n 的斐波那契数列的和。
 * @param n 序列终点
 * @returns uint64_t ans, 序列和
 */
uint64_t result(uint64_t n) {
    math::fibonacci_sum::matrix T{{1, 1}, {1, 0}};
    T = power(T, n);
    uint64_t ans = T[0][1];
    ans = (ans - 1);  // 因为需要减去初始 F(0) 值
    return ans;
}

/**
 * 函数用于计算从 n 到 m 的斐波那契数列的和。
 * @param n 序列开始
 * @param m 序列终点
 * @returns uint64_t 序列和
 */
uint64_t fiboSum(uint64_t n, uint64_t m) {
    return (result(m + 2) - result(n + 1));
}
}  // namespace fibonacci_sum
}  // namespace math

/**
 * 测试 fiboSum 函数。
 * 包含测试用例和断言语句。
 * @returns `void`
 */
static void test() {
    uint64_t n = 0, m = 3;
    uint64_t test_1 = math::fibonacci_sum::fiboSum(n, m);
    assert(test_1 == 4);
    std::cout << "通过测试用例1!" << std::endl;

    n = 3;
    m = 5;
    uint64_t test_2 = math::fibonacci_sum::fiboSum(n, m);
    assert(test_2 == 10);
    std::cout << "通过测试用例2!" << std::endl;

    n = 5;
    m = 7;
    uint64_t test_3 = math::fibonacci_sum::fiboSum(n, m);
    assert(test_3 == 26);
    std::cout << "通过测试用例3!" << std::endl;

    n = 7;
    m = 10;
    uint64_t test_4 = math::fibonacci_sum::fiboSum(n, m);
    assert(test_4 == 123);
    std::cout << "通过测试用例4!" << std::endl;

    n = 9;
    m = 12;
    uint64_t test_5 = math::fibonacci_sum::fiboSum(n, m);
    assert(test_5 == 322);
    std::cout << "通过测试用例5!" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 表示程序正常退出
 */
int main() {
    test();  // 执行测试
    return 0;
}
