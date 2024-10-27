/**
 * @file
 * @brief 实现[0-1背包问题](https://en.wikipedia.org/wiki/Knapsack_problem)
 *
 * @details
 * 给定n个物品的重量和价值，将这些物品放入容量为`W`的背包中，以获得背包中的最大总价值。换句话说，
 * 给定两个整数数组`val[0..n-1]`和`wt[0..n-1]`，它们分别表示n个物品的价值和重量。同时给定一个整数W，
 * 表示背包容量，找到一个最大值子集`val[]`，使得该子集的重量之和小于或等于W。你不能拆分物品，必须
 * 完整选择物品或不选择（0-1特性）。
 *
 * ### 算法
 * 这个思路是考虑所有物品的子集，并计算所有子集的总重量和价值。仅考虑总重量小于`W`的子集。
 * 从所有这样的子集中选择最大值子集。
 *
 * @author [Anmol](https://github.com/Anmol3299)
 * @author [Pardeep](https://github.com/Pardeep009)
 */

#include <array>
#include <cassert>
#include <iostream>
#include <vector>

/**
 * @namespace dynamic_programming
 * @brief 动态规划算法
 */
namespace dynamic_programming {
/**
 * @namespace Knapsack
 * @brief 0-1背包问题的实现
 */
namespace knapsack {
/**
 * @brief 选择所有综合重量低于给定容量的物品，并计算所选物品的价值。尝试所有可能的组合将产生最大背包价值。
 * @tparam n 权重和价值数组的大小
 * @param capacity 背包的容量
 * @param weight 代表物品重量的数组
 * @param value 代表物品价值的数组
 * @return 可在给定容量下获得的最大值。
 */
template <size_t n>
int maxKnapsackValue(const int capacity, const std::array<int, n> &weight,
                     const std::array<int, n> &value) {
    std::vector<std::vector<int> > maxValue(n + 1,
                                            std::vector<int>(capacity + 1, 0));
    // 外层循环选择允许的物品数量
    // 内层循环选择背包的容量
    int items = sizeof(weight) / sizeof(weight[0]);
    for (size_t i = 0; i < items + 1; ++i) {
        for (size_t j = 0; j < capacity + 1; ++j) {
            if (i == 0 || j == 0) {
                // 如果物品数量为零或容量为零，则最大值将为零
                maxValue[i][j] = 0;
            } else if (weight[i - 1] <= j) {
                // 如果第i个物品的重量（在实际数组中是i-1）小于或等于允许的重量j，则可以选择该物品
                // maxValue将是通过选择当前物品或不选择当前物品获得的

                // 选择当前物品
                int profit1 = value[i - 1] + maxValue[i - 1][j - weight[i - 1]];

                // 不选择当前物品
                int profit2 = maxValue[i - 1][j];

                maxValue[i][j] = std::max(profit1, profit2);
            } else {
                // 当前物品的重量大于允许的重量，因此最大利润将是排除当前物品的利润。
                maxValue[i][j] = maxValue[i - 1][j];
            }
        }
    }

    // 返回最大值
    return maxValue[items][capacity];
}
}  // namespace knapsack
}  // namespace dynamic_programming

/**
 * @brief 测试上述算法的函数
 * @returns void
 */
static void test() {
    // 测试 1
    const int n1 = 3;                             // 物品数量
    std::array<int, n1> weight1 = {10, 20, 30};   // 每个物品的重量
    std::array<int, n1> value1 = {60, 100, 120};  // 每个物品的价值
    const int capacity1 = 50;                     // 背包的容量
    const int max_value1 = dynamic_programming::knapsack::maxKnapsackValue(
        capacity1, weight1, value1);
    const int expected_max_value1 = 220;  // 预期最大值
    assert(max_value1 == expected_max_value1);
    std::cout << "具有 " << n1 << " 个物品的最大背包价值是 "
              << max_value1 << std::endl;

    // 测试 2
    const int n2 = 4;                               // 物品数量
    std::array<int, n2> weight2 = {24, 10, 10, 7};  // 每个物品的重量
    std::array<int, n2> value2 = {24, 18, 18, 10};  // 每个物品的价值
    const int capacity2 = 25;                       // 背包的容量
    const int max_value2 = dynamic_programming::knapsack::maxKnapsackValue(
        capacity2, weight2, value2);
    const int expected_max_value2 = 36;  // 预期最大值
    assert(max_value2 == expected_max_value2);
    std::cout << "具有 " << n2 << " 个物品的最大背包价值是 "
              << max_value2 << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    // 测试
    test();
    return 0;
}
