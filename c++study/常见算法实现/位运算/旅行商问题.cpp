/**
 * @file
 * @brief 实现[旅行商问题（使用位掩码）](https://www.geeksforgeeks.org/travelling-salesman-problem-set-1/)
 *
 * @details
 * 给定每个城市/节点之间的距离/成本（作为邻接矩阵），问题是找到访问每个城市恰好一次并返回起点的最短路径，或称为整个旅行的最小成本。
 *
 * 解释：
 * 输入 -> 提供一个邻接矩阵 A = {}，其中包含两个城市/节点之间的距离。
 *
 * 输出 -> 从起始点出发的整个旅行的最小成本
 *
 * 最坏情况下的时间复杂度：O(n^2 * 2^n)
 * 空间复杂度：O(n)
 *
 * @author [Utkarsh Yadav](https://github.com/Rytnix)
 */

#include <algorithm>  /// 引入标准最小值算法
#include <cassert>    /// 引入断言库
#include <iostream>   /// 引入输入输出库
#include <limits>     /// 引入整型的限制
#include <vector>     /// 引入向量库

/**
 * @namespace bit_manipulation
 * @brief 位操作算法
 */
namespace bit_manipulation {
/**
 * @namespace travellingSalesman_bitmanipulation
 * @brief [旅行商问题位掩码](https://www.geeksforgeeks.org/travelling-salesman-problem-set-1/)的实现函数
 */
namespace travelling_salesman_using_bit_manipulation {
/**
 * @brief 使用位掩码实现旅行商问题的函数
 * @param dist 是两个城市/节点之间的距离
 * @param setOfCities 用位表示城市的集合。
 * @param city 用于跟踪当前城市的移动
 * @param n 城市的数量
 * @param dp 向量用于记录状态以避免重复计算
 * @returns 从起点出发回到起点的整个节点/城市的最小成本
 */
std::uint64_t travelling_salesman_using_bit_manipulation(
    std::vector<std::vector<uint32_t>> dist,  // dist 是邻接矩阵，包含城市之间的距离
    std::uint64_t setOfCities,  // setOfCities 用位表示城市集合。例如，如果setOfCities = 2 => 0010（以二进制表示），
                                 // 则表示城市/节点B，如果城市/节点表示为D->C->B->A。
    std::uint64_t city,  // 当前城市/节点的位置，跟踪我们目前在何处
    std::uint64_t n,     // n 是城市的数量
    std::vector<std::vector<uint32_t>> &dp)  // dp 用于存储状态以避免重复计算
{
    // 基本情况；
    if (setOfCities == (1 << n) - 1) {  // 如果所有城市都已访问
        return dist[city][0];  // 返回从当前城市到原始城市的成本
    }

    if (dp[setOfCities][city] != -1) {
        return dp[setOfCities][city];  // 如果状态已经计算过，直接返回结果
    }

    // 否则尝试所有可能的选项
    uint64_t ans = 2147483647;  // 初始化为一个很大的值
    for (int choice = 0; choice < n; choice++) {
        // 检查城市是否已经访问
        if ((setOfCities & (1 << choice)) == 0) {  // 该城市尚未访问
            std::uint64_t subProb =
                dist[city][choice] +  // 当前城市到选择城市的距离
                travelling_salesman_using_bit_manipulation(
                    dist, setOfCities | (1 << choice), choice, n, dp);  // 递归调用，更新城市集合和当前城市
            ans = std::min(ans, subProb);  // 取最小值
        }
    }
    dp[setOfCities][city] = ans;  // 存储结果
    return ans;  // 返回最终结果
}
}  // namespace travelling_salesman_using_bit_manipulation
}  // namespace bit_manipulation

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    // 第一个测试用例
    std::vector<std::vector<uint32_t>> dist = {
        {0, 20, 42, 35}, {20, 0, 30, 34}, {42, 30, 0, 12}, {35, 34, 12, 0}};
    uint32_t V = dist.size();
    std::vector<std::vector<uint32_t>> dp(1 << V, std::vector<uint32_t>(V, -1));
    assert(bit_manipulation::travelling_salesman_using_bit_manipulation::
               travelling_salesman_using_bit_manipulation(dist, 1, 0, V, dp) ==
           97);
    std::cout << "第一个测试用例：通过！"
              << "\n";

    // 第二个测试用例
    dist = {{0, 5, 10, 15}, {5, 0, 20, 30}, {10, 20, 0, 35}, {15, 30, 35, 0}};
    V = dist.size();
    std::vector<std::vector<uint32_t>> dp1(1 << V,
                                           std::vector<uint32_t>(V, -1));
    assert(bit_manipulation::travelling_salesman_using_bit_manipulation::
               travelling_salesman_using_bit_manipulation(dist, 1, 0, V, dp1) ==
           75);
    std::cout << "第二个测试用例：通过！"
              << "\n";
    
    // 第三个测试用例
    dist = {{0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
    V = dist.size();
    std::vector<std::vector<uint32_t>> dp2(1 << V,
                                           std::vector<uint32_t>(V, -1));
    assert(bit_manipulation::travelling_salesman_using_bit_manipulation::
               travelling_salesman_using_bit_manipulation(dist, 1, 0, V, dp2) ==
           80);

    std::cout << "第三个测试用例：通过！"
              << "\n";
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    test();  // 运行自测实现
    return 0;
}
