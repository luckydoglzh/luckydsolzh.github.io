/**
 * @file
 * @brief 计算 LCM 总和的算法：\f$\mathrm{LCM}(1,n) + \mathrm{LCM}(2,n) + \ldots + \mathrm{LCM}(n,n)\f$
 * @details 计算 LCM 总和：\f$\mathrm{LCM}(1,n) + \mathrm{LCM}(2,n) + \ldots + \mathrm{LCM}(n,n)\f$，其中
 * \f$\mathrm{LCM}(i,n)\f$ 表示整数 i 和 n 的最小公倍数。对于 n 大于或等于 1，使用以下公式计算该和：
 * \f[ \sum\mathrm{LCM}(i, n) = \frac{1}{2} \left[\left(\sum (d * \mathrm{ETF}(d)) + 1\right) * n\right] \f]
 * 其中 \mathrm{ETF}(i) 表示 i 的欧拉函数（Euler Totient Function）。
 * @author [Chesta Mittal](https://github.com/chestamittal)
 */

#include <cassert>   /// 用于 assert
#include <iostream>  /// 用于 std::cin 和 std::cout
#include <vector>    /// 用于 std::vector

/**
 * @namespace math
 * @brief 数学算法
 */
namespace math {

/**
 * 计算欧拉函数总和的函数，存储在 sumOfEulerTotient 向量中
 * @param num 输入的数字
 * @returns int LCM 总和，即从 i = 1 到 num 的 ∑LCM(i, num)
 */
uint64_t lcmSum(const uint16_t& num) {
    uint64_t i = 0, j = 0;
    std::vector<uint64_t> eulerTotient(num + 1);  // 用于存储每个数的欧拉函数值
    std::vector<uint64_t> sumOfEulerTotient(num + 1);  // 用于存储欧拉函数和

    // 将初始值存储到 eulerTotient 向量中
    for (i = 1; i <= num; i++) {
        eulerTotient[i] = i;
    }

    // 应用欧拉函数筛法（Euler's Totient Sieve）
    for (i = 2; i <= num; i++) {
        if (eulerTotient[i] == i) {  // 如果 eulerTotient[i] 为 i，说明 i 是质数
            for (j = i; j <= num; j += i) {
                eulerTotient[j] = eulerTotient[j] / i;  // 更新 eulerTotient[j]
                eulerTotient[j] = eulerTotient[j] * (i - 1);  // 计算欧拉函数
            }
        }
    }

    // 计算欧拉函数的总和
    for (i = 1; i <= num; i++) {
        for (j = i; j <= num; j += i) {
            sumOfEulerTotient[j] += eulerTotient[i] * i;
        }
    }

    // 计算 LCM 总和并返回结果
    return ((sumOfEulerTotient[num] + 1) * num) / 2;
}
}  // namespace math

/**
 * @brief 用于测试 lcmSum 函数的测试用例。
 * 包含多个测试案例和 assert 语句。
 * @returns `void`
 */
static void test() {
    uint64_t n = 2;
    uint64_t test_1 = math::lcmSum(n);
    assert(test_1 == 4);  // 测试1：LCM(1,2) + LCM(2,2) = 4
    std::cout << "Passed Test 1!" << std::endl;

    n = 5;
    uint64_t test_2 = math::lcmSum(n);
    assert(test_2 == 55);  // 测试2：LCM(1,5) + LCM(2,5) + LCM(3,5) + LCM(4,5) + LCM(5,5) = 55
    std::cout << "Passed Test 2!" << std::endl;

    n = 10;
    uint64_t test_3 = math::lcmSum(n);
    assert(test_3 == 320);  // 测试3：LCM 总和为 320
    std::cout << "Passed Test 3!" << std::endl;

    n = 11;
    uint64_t test_4 = math::lcmSum(n);
    assert(test_4 == 616);  // 测试4：LCM 总和为 616
    std::cout << "Passed Test 4!" << std::endl;

    n = 15;
    uint64_t test_5 = math::lcmSum(n);
    assert(test_5 == 1110);  // 测试5：LCM 总和为 1110
    std::cout << "Passed Test 5!" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 程序结束时返回 0
 */
int main() {
    test();  // 执行测试
    return 0;
}  
