/**
 * @file
 * @brief [最小硬币找零问题](https://leetcode.com/problems/coin-change/) 是一个用于找到达到目标金额所需的最小硬币数量的问题。
 *
 * @details
 * 这个问题可以通过两种方法来解决：
 * 1. 自顶向下方法
 * 2. 自底向上方法
 * 自顶向下方法使用一个初始化为 0 的向量。它基于最优子结构和重叠子问题。
 * 硬币找零问题的整体时间复杂度为 O(n*t)。
 * 例如：
 * 示例 1:
 * 硬币: {1, 7, 10}
 * 目标金额: 15
 * 因此所需的最小硬币数量 = 3，面额分别为 1, 7 和 7。
 */

#include <cassert>   // 用于 assert
#include <climits>   // 用于 INT_MAX
#include <iostream>  // 用于输入输出操作
#include <vector>    // 用于 std::vector

/**
 * @namespace dynamic_programming
 * @brief 动态规划算法
 */
namespace dynamic_programming {
/**
 * @namespace mincoins_topdown
 * @brief [最小硬币找零](https://leetcode.com/problems/coin-change/)问题的函数
 */
namespace mincoins_topdown {
/**
 * @brief 该实现用于查找最少的硬币数量。
 * @param T 模板类型以支持任意类型的值
 * @param n 需要达到的金额
 * @param coins 硬币的向量
 * @param t 硬币的数量
 * @param dp 初始化为 0 的向量
 * @returns 所需的最少硬币数量
 */
template <typename T>
int64_t mincoins(const T &n, const std::vector<T> &coins, const int16_t &t,
                 std::vector<T> dp) {
    if (n == 0) {  // 如果金额为 0，返回 0
        return 0;
    }
    if (dp[n] != 0) {  // 如果 dp 中已经存储了当前金额的最小硬币数量，直接返回
        return dp[n];
    }
    int ans = INT_MAX;  // 用于存储最少硬币数量的变量
    for (int i = 0; i < t; i++) {  // 遍历每种硬币面额
        if (n - coins[i] >= 0) {  // 如果当前面额减去金额后大于或等于 0
            int sub = mincoins(n - coins[i], coins, t, dp);  // 递归计算子问题
            ans = std::min(ans, sub + 1);  // 更新最小硬币数量
        }
    }
    dp[n] = ans;  // 将计算结果存储到 dp 中
    return dp[n];  // 返回最少的硬币数量
}

}  // namespace mincoins_topdown
}  // namespace dynamic_programming

/**
 * @brief 测试实现
 * @returns void
 */
static void test() {
    // 示例 1: 硬币数量=3，所需的最小硬币数量=3(7,7,1)
    const int64_t n1 = 15;
    const int8_t t1 = 3, a1 = 0;
    std::cout << "\n测试 1...";
    std::vector<int64_t> arr1{1, 7, 10};
    std::vector<int64_t> dp1(n1 + 1);
    fill(dp1.begin(), dp1.end(), a1);  // 初始化 dp 向量为 0
    assert(dynamic_programming::mincoins_topdown::mincoins(n1, arr1, t1, dp1) ==
           3);  // 验证结果是否等于 3
    std::cout << "通过\n";
}

/**
 * @brief 主函数
 * @returns 退出时返回 0
 */
int main() {
    test();  // 执行测试
    return 0;
}
