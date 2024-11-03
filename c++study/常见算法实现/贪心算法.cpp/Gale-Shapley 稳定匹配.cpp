/**
 * @file
 * @brief [Gale Shapley 算法](https://en.wikipedia.org/wiki/Gale%E2%80%93Shapley_algorithm)
 * @details
 * 此实现使用 Gale-Shapley 算法来找到稳定匹配。
 *
 * **Gale Shapley 算法** 旨在找到两个大小相同的元素集合之间的稳定匹配， 
 * 给定每个元素的序数偏好。该算法由 David Gale 和 Lloyd Shapley 于 1962 年提出。
 * 
 * 参考文献： 
 * [Wikipedia](https://en.wikipedia.org/wiki/Gale%E2%80%93Shapley_algorithm)
 * [Wikipedia](https://en.wikipedia.org/wiki/Stable_matching_problem)
 *
 * @author [B Karthik](https://github.com/BKarthik7)
 */

#include <iostream>   /// 用于 std::uint32_t
#include <vector>     /// 用于 std::vector
#include <algorithm>  /// 用于 std::find
#include <cassert>    /// 用于 assert

/**
 * @namespace
 * @brief 贪心算法
 */
namespace greedy_algorithms {
/**
 * @namespace
 * @brief Gale-Shapley 算法的函数
 */
namespace stable_matching {
/**
 * @brief 使用 Gale-Shapley 算法找到两个元素集合之间的稳定匹配
 * @note 此算法不适用于负偏好。偏好应为从 0 到偏好数量 - 1 的连续整数。
 * @param primary_preferences 主集合的偏好，应该是一个二维向量
 * @param secondary_preferences 辅集合的偏好，应该是一个二维向量
 * @returns matches 两个集合之间的稳定匹配
 */
std::vector<std::uint32_t> gale_shapley(const std::vector<std::vector<std::uint32_t>>& secondary_preferences, const std::vector<std::vector<std::uint32_t>>& primary_preferences) {
    std::uint32_t num_elements = secondary_preferences.size(); // 元素数量
    std::vector<std::uint32_t> matches(num_elements, -1); // 初始化匹配结果为 -1，表示未匹配
    std::vector<bool> is_free_primary(num_elements, true); // 记录主集合中的元素是否自由
    std::vector<std::uint32_t> proposal_index(num_elements, 0); // 跟踪每个主集合下一个提议的辅集合索引

    while (true) {
        int free_primary_index = -1;

        // 找到下一个自由的主集合元素
        for (std::uint32_t i = 0; i < num_elements; i++) {
            if (is_free_primary[i]) {
                free_primary_index = i;
                break;
            }
        }

        // 如果没有找到自由的主集合元素，则跳出循环
        if (free_primary_index == -1) break;

        // 获取下一个要提议的辅集合元素
        std::uint32_t secondary_to_propose = primary_preferences[free_primary_index][proposal_index[free_primary_index]];
        proposal_index[free_primary_index]++; // 提高提议索引

        // 获取该辅集合元素当前的匹配
        std::uint32_t current_match = matches[secondary_to_propose];

        // 如果该辅集合元素是自由的，则匹配
        if (current_match == -1) {
            matches[secondary_to_propose] = free_primary_index;
            is_free_primary[free_primary_index] = false;
        } else {
            // 确定当前匹配是否应被替换
            auto new_proposer_rank = std::find(secondary_preferences[secondary_to_propose].begin(),
                                                secondary_preferences[secondary_to_propose].end(),
                                                free_primary_index);
            auto current_match_rank = std::find(secondary_preferences[secondary_to_propose].begin(),
                                                 secondary_preferences[secondary_to_propose].end(),
                                                 current_match);

            // 如果新的提议者比当前匹配更受欢迎
            if (new_proposer_rank < current_match_rank) {
                matches[secondary_to_propose] = free_primary_index;
                is_free_primary[free_primary_index] = false;
                is_free_primary[current_match] = true; // 当前匹配现在变为自由
            }
        }
    }

    return matches; // 返回稳定匹配结果
}
}  // namespace stable_matching
}  // namespace greedy_algorithms

/**
 * @brief 自测实现
 * @returns void
 */
static void tests() {
    // 测试用例 1
    std::vector<std::vector<std::uint32_t>> primary_preferences = {{0, 1, 2, 3}, {2, 1, 3, 0}, {1, 2, 0, 3}, {3, 0, 1, 2}};
    std::vector<std::vector<std::uint32_t>> secondary_preferences = {{1, 0, 2, 3}, {3, 0, 1, 2}, {0, 2, 1, 3}, {1, 2, 0, 3}};
    assert(greedy_algorithms::stable_matching::gale_shapley(secondary_preferences, primary_preferences) == std::vector<std::uint32_t>({0, 2, 1, 3}));

    // 测试用例 2
    primary_preferences = {{0, 2, 1, 3}, {2, 3, 0, 1}, {3, 1, 2, 0}, {2, 1, 0, 3}};
    secondary_preferences = {{1, 0, 2, 3}, {3, 0, 1, 2}, {0, 2, 1, 3}, {1, 2, 0, 3}};
    assert(greedy_algorithms::stable_matching::gale_shapley(secondary_preferences, primary_preferences) == std::vector<std::uint32_t>({0, 3, 1, 2}));

    // 测试用例 3
    primary_preferences = {{0, 1, 2}, {2, 1, 0}, {1, 2, 0}};
    secondary_preferences = {{1, 0, 2}, {2, 0, 1}, {0, 2, 1}};
    assert(greedy_algorithms::stable_matching::gale_shapley(secondary_preferences, primary_preferences) == std::vector<std::uint32_t>({0, 2, 1}));

    // 测试用例 4
    primary_preferences = {};
    secondary_preferences = {};
    assert(greedy_algorithms::stable_matching::gale_shapley(secondary_preferences, primary_preferences) == std::vector<std::uint32_t>({}));
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    tests(); // 运行自测实现
    return 0;
}
