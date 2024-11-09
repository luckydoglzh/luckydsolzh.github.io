/**
 * @file
 * @brief 计算[二项系数](https://en.wikipedia.org/wiki/Binomial_coefficient)的程序
 * 
 * 该程序通过函数计算组合数，即二项系数。
 * 
 * 作者：[astronmax](https://github.com/astronmax)
 */

#include <cassert>   /// 用于断言
#include <cstdint>   /// 用于 int32_t 类型
#include <cstdlib>   /// 用于 atoi
#include <iostream>  /// 用于输入输出操作

/**
 * @namespace math
 * @brief 数学算法命名空间
 */
namespace math {
/**
 * @namespace binomial
 * @brief 实现二项系数的函数命名空间
 */
namespace binomial {
/**
 * @brief 计算二项系数的函数
 * @param n 第一个值
 * @param k 第二个值
 * @return 返回二项系数
 */
size_t calculate(int32_t n, int32_t k) {
    // 基本情况
    if (k > (n / 2))
        k = n - k; // 对称性减少计算次数
    if (k == 1)
        return n;
    if (k == 0)
        return 1;

    size_t result = 1;
    // 计算组合数 C(n, k) 的迭代方式
    for (int32_t i = 1; i <= k; ++i) {
        result *= n - k + i;
        result /= i;
    }

    return result;
}
}  // namespace binomial
}  // namespace math

/**
 * @brief 测试函数
 * @returns void
 */
static void tests() {
    // 测试 calculate 函数
    assert(math::binomial::calculate(1, 1) == 1);
    assert(math::binomial::calculate(57, 57) == 1);
    assert(math::binomial::calculate(6, 3) == 20);
    assert(math::binomial::calculate(10, 5) == 252);
    assert(math::binomial::calculate(20, 10) == 184756);
    assert(math::binomial::calculate(30, 15) == 155117520);
    assert(math::binomial::calculate(40, 20) == 137846528820);
    assert(math::binomial::calculate(50, 25) == 126410606437752);
    assert(math::binomial::calculate(60, 30) == 118264581564861424);
    assert(math::binomial::calculate(62, 31) == 465428353255261088);

    std::cout << "[+] 二项系数计算测试完成" << std::endl;
}

/**
 * @brief 主函数
 * @param argc 命令行参数计数
 * @param argv 命令行参数数组
 * @returns 0 表示程序正常退出
 */
int main(int argc, const char* argv[]) {
    tests();  // 运行测试函数

    if (argc < 3) {
        std::cout << "用法: ./binomial_calculate {n} {k}" << std::endl;
        return 0;
    }

    int32_t n = atoi(argv[1]);
    int32_t k = atoi(argv[2]);

    std::cout << math::binomial::calculate(n, k) << std::endl;
    return 0;
}
