/**
 * @file
 * @brief 本程序旨在计算 [nCr 模 p](https://cp-algorithms.com/combinatorics/binomial-coefficients.html)。
 * @details nCr 的定义为 n! / (r! * (n-r)!)，其中 n! 代表 n 的阶乘。在很多情况下，nCr 的值太大，无法存储在一个 64 位整数中。因此，在竞赛编程中，有许多问题或子问题要求计算 nCr 模 p，其中 p 是给定的一个数。
 * @author [Kaustubh Damania](https://github.com/KaustubhDamania)
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
 * @namespace ncr_modulo_p
 * @brief 用于 [nCr 模 p](https://cp-algorithms.com/combinatorics/binomial-coefficients.html) 计算的函数实现。
 */
namespace ncr_modulo_p {

/**
 * @namespace utils
 * @brief 该命名空间包含 math::ncr_modulo_p::NCRModuloP 类调用的函数定义。
 */
namespace utils {
/**
 * @brief 寻找 x 和 y，使得 a*x + b*y = gcd(a,b)
 *
 * @param[in] a 求 gcd 的第一个输入
 * @param[in] b 求 gcd 的第二个输入
 * @param[out] x a 的 Bézout 系数
 * @param[out] y b 的 Bézout 系数
 * @return 返回 a 和 b 的 gcd
 */
int64_t gcdExtended(const int64_t& a, const int64_t& b, int64_t& x,
                    int64_t& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    int64_t x1 = 0, y1 = 0;
    const int64_t gcd = gcdExtended(b % a, a, x1, y1);

    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

/** 
 * @brief 计算 a 对 m 的模反元素，即找到一个数 x 使得 (a * x) % m = 1
 *
 * @param[in] a 需要求模反元素的数
 * @param[in] m 模数
 * @return 如果存在反元素，返回 a 对 m 的反元素，否则返回 -1
 */
int64_t modInverse(const int64_t& a, const int64_t& m) {
    int64_t x = 0, y = 0;
    const int64_t g = gcdExtended(a, m, x, y);
    if (g != 1) {  // 如果模反元素不存在
        return -1;
    } else {
        return ((x + m) % m);  // 返回模反元素
    }
}
}  // namespace utils

/**
 * @brief 计算 nCr 模 p 的类
 */
class NCRModuloP {
 private:
    const int64_t p = 0;  /// 计算 nCr 模 p 中的 p
    const std::vector<int64_t>
        fac;  /// 存储预先计算的阶乘值 (i! % p)

    /**
     * @brief 计算阶乘数组并对 mod 取模
     * @param max_arg_val 需要计算到的最大阶乘值
     * @param mod 用于取模的值
     * @return 存储从 0 到 max_arg_val 计算出的阶乘值并取模后的数组
     */
    static std::vector<int64_t> computeFactorialsMod(const int64_t& max_arg_val,
                                                     const int64_t& mod) {
        auto res = std::vector<int64_t>(max_arg_val + 1);
        res[0] = 1;  // 0! = 1
        for (int64_t i = 1; i <= max_arg_val; i++) {
            res[i] = (res[i - 1] * i) % mod;  // 递归计算阶乘并取模
        }
        return res;
    }

 public:
    /**
     * @brief 构造 NCRModuloP 对象，允许计算 0 到 size 范围内的 nCr % p
     */
    NCRModuloP(const int64_t& size, const int64_t& p)
        : p(p), fac(computeFactorialsMod(size, p)) {}

    /**
     * @brief 计算 nCr % p
     * @param[in] n 从 n 个对象中选择
     * @param[in] r 从中选择 r 个
     * @return 返回 nCr % p 的值
     */
    int64_t ncr(const int64_t& n, const int64_t& r) const {
        // 基础情况处理
        if (r > n) {
            return 0;  // r 大于 n 时，返回 0
        }
        if (r == 1) {
            return n % p;  // 计算 nC1 时直接返回 n % p
        }
        if (r == 0 || r == n) {
            return 1;  // 计算 nCn 或 nC0 时返回 1
        }
        // fac 是预先计算的阶乘数组，fac[r] 存储 (r! % p)
        const auto denominator = (fac[r] * fac[n - r]) % p;  // 计算分母
        const auto denominator_inv = utils::modInverse(denominator, p);  // 计算分母的模反元素
        if (denominator_inv < 0) {  // 如果模反元素不存在
            return -1;
        }
        return (fac[n] * denominator_inv) % p;  // 计算 nCr % p 并返回结果
    }
};

}  // namespace ncr_modulo_p
}  // namespace math

/**
 * @brief 测试 math::ncr_modulo_p::NCRModuloP 类
 */
static void tests() {
    struct TestCase {
        const int64_t size;
        const int64_t p;
        const int64_t n;
        const int64_t r;
        const int64_t expected;

        TestCase(const int64_t size, const int64_t p, const int64_t n,
                 const int64_t r, const int64_t expected)
            : size(size), p(p), n(n), r(r), expected(expected) {}
    };
    const std::vector<TestCase> test_cases = {
        TestCase(60000, 1000000007, 52323, 26161, 224944353),
        TestCase(20, 5, 6, 2, 30 % 5),
        TestCase(100, 29, 7, 3, 35 % 29),
        TestCase(1000, 13, 10, 3, 120 % 13),
        TestCase(20, 17, 1, 10, 0),
        TestCase(45, 19, 23, 1, 23 % 19),
        TestCase(45, 19, 23, 0, 1),
        TestCase(45, 19, 23, 23, 1),
        TestCase(20, 9, 10, 2, -1)};  // 测试用例，涵盖了多种情况
    for (const auto& tc : test_cases) {
        assert(math::ncr_modulo_p::NCRModuloP(tc.size, tc.p).ncr(tc.n, tc.r) == tc.expected);  // 验证每个测试用例
    }

    std::cout << "\n\n所有测试成功通过！\n";
}

/**
 * @brief 示例展示如何使用 math::ncr_modulo_p::NCRModuloP 类
 */
void example() {
    const int64_t size = 1e6 + 1;  // 设置计算范围上限
    const int64_t p = 1e9 + 7;  // 设置模数

    // 创建 ncrObj 对象，计算 0 到 size 范围内的阶乘模 p 的值
    const auto ncrObj = math::ncr_modulo_p::NCRModuloP(size, p);

    // 使用 ncrObj 对象查询 (nCr) % p 的值
    // 计算的时间与 size 无关
    for (int i = 0; i <= 7; i++) {
        std::cout << 6 << "C" << i << " mod " << p << " = " << ncrObj.ncr(6, i) << "\n";
    }
}

int main() {
    tests();  // 执行所有测试
    example();  // 展示示例
    return 0;
}
