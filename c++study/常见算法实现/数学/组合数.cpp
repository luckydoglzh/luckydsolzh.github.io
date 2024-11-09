/**
 * @file
 * @brief [组合数](https://en.wikipedia.org/wiki/Combination) n 选 r
 * 函数实现
 * @details
 * 这是一个基本且高效的计算从 n 个不同的选项中选择 r 个的组合数的方法。
 * 组合数的公式为：
 * \f$ \binom{n}{r} = \frac{n!}{r! (n-r)!} \f$
 *
 * @author [Tajmeet Singh](https://github.com/tjgurwara99)
 */

#include <cassert>   /// 用于 assert
#include <iostream>  /// 用于输入输出操作

/**
 * @namespace math
 * @brief 数学算法
 */
namespace math {
/**
 * @brief 这是 \f$ \binom{n}{r} \f$ 的函数实现
 * @details
 * 我们通过迭代的方式计算答案，而不是分别计算三个不同的阶乘。
 * 另外，我们利用公式：
 * \f$ \frac{n!}{r! (n-r)!} = \frac{(n - r + 1) \times \cdots \times n}{1 \times
 * \cdots \times r} \f$
 * 来优化计算。
 * @tparam T 仅适用于整数类型（如 long、int_64 等）
 * @param n \f$ n \f$ 在 \f$ \binom{n}{r} \f$ 中的值
 * @param r \f$ r \f$ 在 \f$ \binom{n}{r} \f$ 中的值
 * @returns 返回组合数 \f$ \binom{n}{r} \f$
 */
template <class T>
T n_choose_r(T n, T r) {
    if (r > n / 2) {
        r = n - r;  // 因为有公式 nCr(n, r) == nCr(n, n - r)，可以通过选择较小的 r 来优化
    }
    T ans = 1;
    for (int i = 1; i <= r; i++) {
        ans *= n - r + i;  // 计算分子部分
        ans /= i;  // 计算分母部分
    }
    return ans;  // 返回最终结果
}
}  // namespace math

/**
 * @brief 测试函数
 * @returns void
 */
static void test() {
    // 第一个测试：计算 5 选 2
    uint8_t t = math::n_choose_r(5, 2);
    assert(((void)"答案是 10，但函数返回了其他值。\n", t == 10));  // 验证结果
    std::cout << "第一个测试通过。" << std::endl;

    // 第二个测试：计算 5 选 3
    t = math::n_choose_r(5, 3);
    assert(((void)"答案是 10，但函数返回了其他值。\n", t == 10));  // 验证结果
    std::cout << "第二个测试通过。" << std::endl;

    // 第三个测试：计算 3 选 2
    t = math::n_choose_r(3, 2);
    assert(((void)"答案是 3，但函数返回了其他值。\n", t == 3));  // 验证结果
    std::cout << "第三个测试通过。" << std::endl;

    // 第四个测试：计算 10 选 4
    t = math::n_choose_r(10, 4);
    assert(((void)"答案是 210，但函数返回了其他值。\n", t == 210));  // 验证结果
    std::cout << "第四个测试通过。" << std::endl;
}

/**
 * @brief 主函数
 * @param argc 命令行参数数量（忽略）
 * @param argv 命令行参数数组（忽略）
 * @returns 0 退出
 */
int main(int argc, char *argv[]) {
    test();  // 执行测试
    return 0;  // 程序正常退出
}
