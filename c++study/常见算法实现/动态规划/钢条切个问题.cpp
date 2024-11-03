/**
 * @file
 * @brief 实现钢条切割问题
 *
 * @details
 * 给定长度为 n 英寸的一根钢条和包含各段长度对应价格的数组，
 * 通过将钢条切割成不同小段并出售来获取最大收益。
 *
 * ### 算法
 * 通过尽可能将钢条分割成更小的片段，计算每个片段的收益，
 * 以自底向上的方式构建更大片段的解决方案，从而得到最大收益。
 *
 * @author [Anmol](https://github.com/Anmol3299)
 * @author [Pardeep](https://github.com/Pardeep009)
 */

#include <array>
#include <cassert>
#include <climits>
#include <iostream>

/**
 * @namespace dynamic_programming
 * @brief 动态规划算法
 */
namespace dynamic_programming {
/**
 * @namespace cut_rod
 * @brief 钢条切割问题的实现
 */
namespace cut_rod {

/**
 * @brief 将钢条切割成不同长度的片段，并为每个长度存储最大收益。
 * @tparam T 价格数组的大小
 * @param n 钢条的长度（单位：英寸）
 * @param price 包含各长度对应价格的数组
 * @return 对于长度为 n 的钢条可获得的最大收益
 */
template <size_t T>
int maxProfitByCuttingRod(const std::array<int, T> &price, const uint64_t &n) {
    int *profit = new int[n + 1];  // profit[i] 保存长度为 i 的钢条的最大收益

    profit[0] = 0;  // 钢条长度为 0 时无收益

    // 外层循环选择钢条长度，从 1 英寸到 n 英寸
    // 内层循环计算 i 英寸钢条的最大收益
    for (size_t i = 1; i <= n; i++) {
        int q = INT_MIN;
        for (size_t j = 1; j <= i; j++) {
            q = std::max(q, price[j - 1] + profit[i - j]);
        }
        profit[i] = q;
    }
    const int16_t ans = profit[n];
    delete[] profit;
    return ans;  // 返回最大收益
}
}  // namespace cut_rod
}  // namespace dynamic_programming

/**
 * @brief 测试函数
 * @returns void
 */
static void test() {
    // 测试 1
    const int16_t n1 = 8;                                        // 钢条长度
    std::array<int32_t, n1> price1 = {1, 2, 4, 6, 8, 45, 21, 9};  // 价格数组
    const int64_t max_profit1 =
        dynamic_programming::cut_rod::maxProfitByCuttingRod(price1, n1);
    const int64_t expected_max_profit1 = 47;
    assert(max_profit1 == expected_max_profit1);
    std::cout << "长度为 " << n1 << " 英寸的钢条的最大收益为 " << max_profit1
              << std::endl;

    // 测试 2
    const int16_t n2 = 30;  // 钢条长度
    std::array<int32_t, n2> price2 = {
        1,  5,  8,  9,  10, 17, 17, 20, 24, 30,  // 价格数组
        31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50};

    const int64_t max_profit2 =
        dynamic_programming::cut_rod::maxProfitByCuttingRod(price2, n2);
    const int32_t expected_max_profit2 = 90;
    assert(max_profit2 == expected_max_profit2);
    std::cout << "长度为 " << n2 << " 英寸的钢条的最大收益为 " << max_profit2
              << std::endl;

    // 测试 3
    const int16_t n3 = 5;  // 钢条长度
    std::array<int32_t, n3> price3 = {2, 9, 17, 23, 45};  // 价格数组
    const int64_t max_profit3 =
        dynamic_programming::cut_rod::maxProfitByCuttingRod(price3, n3);
    const int64_t expected_max_profit3 = 45;
    assert(max_profit3 == expected_max_profit3);
    std::cout << "长度为 " << n3 << " 英寸的钢条的最大收益为 " << max_profit3
              << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main() {
    // 执行测试
    test();
    return 0;
}
