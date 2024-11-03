/**
 * @file
 * @brief [跳跃游戏](https://leetcode.com/problems/jump-game/) 算法实现
 * @details
 *
 * 给定一个非负整数数组，您最初位于数组的第一个索引。数组中的每个元素表示您在该位置的最大跳跃长度。确定您是否能够到达最后一个索引。此解决方案将输入视为一个向量，并输出布尔值以检查您是否可以到达最后的位置。我们根据能否到达目标位置来命名索引为好（good）和坏（bad）。我们将最后一个索引初始化为 lastPos。
 * 在这里，我们从数组的末尾开始，检查是否可以到达第一个索引。我们检查当前索引加上给定的最大跳跃计数是否大于或等于 lastPos。如果是，那么从后面开始您可以到达的最后位置就是 lastPos。循环结束后，如果 lastPos 到达 0，则可以从起始位置到达目标。
 *
 * @author [Rakshaa Viswanathan](https://github.com/rakshaa2000)
 * @author [David Leal](https://github.com/Panquesito7)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for std::cout
#include <vector>    /// for std::vector

/**
 * @namespace
 * @brief 贪心算法
 */
namespace greedy_algorithms {
/**
 * @brief 检查给定元素（默认为 `1`）是否可以跳到最后索引。
 * @param nums 数组，包含从该索引的最大跳跃步数
 * @returns true 如果可以到达最后索引
 * @returns false 如果不能到达最后索引
 */
bool can_jump(const std::vector<int> &nums) {
    size_t lastPos = nums.size() - 1; // 初始化 lastPos 为数组最后一个索引
    // 从最后一个索引向前遍历
    for (size_t i = lastPos; i != static_cast<size_t>(-1); i--) {
        // 检查当前索引及其最大跳跃长度是否能够到达 lastPos
        if (i + nums[i] >= lastPos) {
            lastPos = i; // 更新 lastPos
        }
    }
    return lastPos == 0; // 如果 lastPos 为 0，则可以到达目标
}
}  // namespace greedy_algorithms

/**
 * @brief 测试上述算法的函数
 * @returns void
 */
static void test() {
    assert(greedy_algorithms::can_jump(std::vector<int>({4, 3, 1, 0, 5}))); // 应该返回 true
    assert(!greedy_algorithms::can_jump(std::vector<int>({3, 2, 1, 0, 4}))); // 应该返回 false
    assert(greedy_algorithms::can_jump(std::vector<int>({5, 9, 4, 7, 15, 3}))); // 应该返回 true
    assert(!greedy_algorithms::can_jump(std::vector<int>({1, 0, 5, 8, 12}))); // 应该返回 false
    assert(greedy_algorithms::can_jump(std::vector<int>({2, 1, 4, 7}))); // 应该返回 true

    std::cout << "所有测试均成功通过！\n";
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    test();  // 运行自测试实现
    return 0;
}
