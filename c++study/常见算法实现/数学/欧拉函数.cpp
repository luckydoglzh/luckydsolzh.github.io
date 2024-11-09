/**
 * @file
 * @brief 欧拉的 φ 函数（欧拉函数）实现
 * @description
 * 欧拉函数也被称为 φ 函数。
 * \f[\phi(n) =
 * \phi\left({p_1}^{a_1}\right)\cdot\phi\left({p_2}^{a_2}\right)\ldots\f] 
 * 其中 \f$p_1\f$, \f$p_2\f$, \f$\ldots\f$ 是 n 的质因数。
 * <br/>欧拉函数的三个性质：
 * 1. \f$\phi(n) = n-1\f$
 * 2. \f$\phi(n^k) = n^k - n^{k-1}\f$
 * 3. \f$\phi(a,b) = \phi(a)\cdot\phi(b)\f$，其中 a 和 b 是互质的。
 *
 * 应用这三个性质到第一个公式中：
 * \f[\phi(n) =
 * n\cdot\left(1-\frac{1}{p_1}\right)\cdot\left(1-\frac{1}{p_2}\right)\cdots\f]
 * 其中 \f$p_1\f$, \f$p_2\f$... 是质因数。
 * 因此，时间复杂度为 \f$O\left(\sqrt{n}\right)\f$。
 * <br/>一些已知的值有：
 * * \f$\phi(100) = 40\f$
 * * \f$\phi(1) = 1\f$
 * * \f$\phi(17501) = 15120\f$
 * * \f$\phi(1420) = 560\f$
 * @author [Mann Mehta](https://github.com/mann2108)
 */

#include <iostream> /// 用于输入输出操作
#include <cassert> /// 用于断言

/**
 * @brief 数学算法
 * @namespace
 */
namespace math {
/**
 * @brief 计算欧拉的 φ 函数
 * @param n 要计算欧拉函数的数字
 */
uint64_t phiFunction(uint64_t n) {
    uint64_t result = n;  // 初始化结果为 n
    for (uint64_t i = 2; i * i <= n; i++) {  // 从 2 到 sqrt(n) 进行遍历
        if (n % i != 0) continue;  // 如果 i 不是 n 的因数，则跳过
        while (n % i == 0) n /= i;  // 去掉所有 i 的因子

        result -= result / i;  // 根据欧拉函数公式减少对应的值
    }
    if (n > 1) result -= result / n;  // 如果剩下的 n 是大于 1 的质数，则需要做处理

    return result;  // 返回最终计算出的结果
}
}  // namespace math

/**
 * @brief 自测试实现
 * @returns void
 */
static void test() {
    assert(math::phiFunction(1) == 1);  // φ(1) = 1
    assert(math::phiFunction(2) == 1);  // φ(2) = 1
    assert(math::phiFunction(10) == 4);  // φ(10) = 4
    assert(math::phiFunction(123456) == 41088);  // φ(123456) = 41088
    assert(math::phiFunction(808017424794) == 263582333856);  // φ(808017424794) = 263582333856
    assert(math::phiFunction(3141592) == 1570792);  // φ(3141592) = 1570792
    assert(math::phiFunction(27182818) == 12545904);  // φ(27182818) = 12545904

    std::cout << "所有测试均已通过！\n";
}

/**
 * @brief 主函数
 * @param argc 命令行参数的数量（忽略）
 * @param argv 命令行参数的数组（忽略）
 * @returns 0 表示正常退出
 */
int main(int argc, char *argv[]) {
    test();  // 运行自测实现
    return 0;
}
