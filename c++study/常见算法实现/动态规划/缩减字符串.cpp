/**
 * @file
 * @brief 实现 [Abbreviation](https://www.hackerrank.com/challenges/abbr/problem)
 *
 * @details
 * 给定两个字符串 `a` 和 `b`，确定是否可以将 `a` 变为 `b`。可以对字符串 `a` 执行以下操作：
 * 1. 将 `a` 中的一个或多个小写字母大写。
 * 2. 删除 `a` 中所有剩余的小写字母。
 *
 * ### 算法
 * 算法思想在问题陈述中已阐明：迭代字符串 `a` 和 `b` 的字符（字符索引分别为 `i` 和 `j`）：
 * 1. 如果 `a[i]` 和 `b[j]` 相等，则移动到下一个位置。
 * 2. 如果 `a[i]` 是 `b[j]` 的小写形式，则探索两种可能性：
 * a. 将 `a[i]` 大写，或
 * b. 跳过 `a[i]`
 * 3. 如果 `a[i]` 不是大写，则丢弃该字符，否则返回 `false`。
 *
 * 时间复杂度：(O(|a|*|b|)) 其中 `|a|` => 字符串 `a` 的长度
 * @author [Ashish Daulatabad](https://github.com/AshishYUO)
 */

#include <cassert>   /// 用于 `assert`
#include <iostream>  /// 用于输入输出操作
#include <string>    /// 用于 `std::string` 库
#include <vector>    /// 用于 `std::vector` STL 库

/**
 * @namespace dynamic_programming
 * @brief 动态规划算法
 */
namespace dynamic_programming {
/**
 * @namespace abbreviation
 * @brief 实现 [Abbreviation](https://www.hackerrank.com/challenges/abbr/problem) 的函数
 */
namespace abbreviation {
/**
 * @brief
 * 递归动态规划函数
 * @details
 * 返回字符串 `s` 是否可以转换为 `t`，遵循以下规则：
 * a. 将字符串 `s` 中的一个或多个小写字母大写
 * b. 删除字符串 `s` 中的所有其他小写字母
 * @param memo 用于存储结果
 * @param visited 布尔值用于检查结果是否已经计算
 * @param str 给定字符串，可能未被缩写
 * @param result 结果缩写字符串
 * @param str_idx 字符串 `str` 的索引，有助于转换
 * @param result_idx 字符串 `result` 的索引，有助于转换
 * @returns 如果字符串 `str` 不能转换为 `result` 则返回 `false`
 * @returns 如果字符串 `str` 可以转换为 `result` 则返回 `true`
 */
bool abbreviation_recursion(std::vector<std::vector<bool>> *memo,
                            std::vector<std::vector<bool>> *visited,
                            const std::string &str, const std::string &result,
                            uint32_t str_idx = 0, uint32_t result_idx = 0) {
    bool ans = memo->at(str_idx).at(result_idx);
    if (str_idx == str.size() && result_idx == result.size()) {
        return true;
    } else if (str_idx == str.size() && result_idx != result.size()) {
        // 结果 `t` 未被转换，返回 false
        return false;
    } else if (!visited->at(str_idx).at(result_idx)) {
        /**
         * `(str[i] == result[j])`：如果字符串 `str` 中索引 `i` 的字符
         * 与 `result` 中索引 `j` 的字符相等，则该字符是大写的，继续
         * 转到下一个字符 `str[i] - 32 == result[j]`：
         * 如果 `str[i]` 的字符是 `result[j]` 的小写形式，则探索两种可能性：
         * 1. 将其转换为大写字母并移动到下一个指针 `(i + 1, j + 1)`
         * 2. 丢弃字符 `(str[i])`，移动到下一个字符 `(i + 1, j)`
         */
        if (str[str_idx] == result[result_idx]) {
            ans = abbreviation_recursion(memo, visited, str, result,
                                         str_idx + 1, result_idx + 1);
        } else if (str[str_idx] - 32 == result[result_idx]) {
            ans = abbreviation_recursion(memo, visited, str, result,
                                         str_idx + 1, result_idx + 1) ||
                  abbreviation_recursion(memo, visited, str, result,
                                         str_idx + 1, result_idx);
        } else {
            // 如果 `str[i]` 是大写字母，则无法转换，返回 false
            // 否则 `str[i]` 是小写字母，唯一选择是丢弃此字符
            if (str[str_idx] >= 'A' && str[str_idx] <= 'Z') {
                ans = false;
            } else {
                ans = abbreviation_recursion(memo, visited, str, result,
                                             str_idx + 1, result_idx);
            }
        }
    }
    (*memo)[str_idx][result_idx] = ans; // 记忆化存储答案
    (*visited)[str_idx][result_idx] = true; // 标记已访问
    return (*memo)[str_idx][result_idx];
}

/**
 * @brief
 * 迭代动态规划函数
 * @details
 * 返回字符串 `s` 是否可以转换为 `t`，遵循以下规则：
 * a. 将字符串 `s` 中的一个或多个小写字母大写
 * b. 删除字符串 `s` 中的所有其他小写字母
 * 注意：迭代的转移状态与递归相似
 * @param str 给定字符串，可能未被缩写
 * @param result 结果缩写字符串
 * @returns 如果字符串 `str` 不能转换为 `result` 则返回 `false`
 * @returns 如果字符串 `str` 可以转换为 `result` 则返回 `true`
 */
bool abbreviation(const std::string &str, const std::string &result) {
    // 创建一个 memo 表来存储计算结果
    std::vector<std::vector<bool>> memo(
        str.size() + 1, std::vector<bool>(result.size() + 1, false));

    for (uint32_t i = 0; i <= str.size(); ++i) {
        memo[i][0] = true; // 任何字符串都可以缩写为空字符串
    }
    for (uint32_t i = 1; i <= result.size(); ++i) {
        memo[0][i] = false; // 空字符串不能转换为非空字符串
    }
    for (uint32_t i = 1; i <= str.size(); ++i) {
        for (uint32_t j = 1; j <= result.size(); ++j) {
            if (str[i - 1] == result[j - 1]) {
                memo[i][j] = memo[i - 1][j - 1]; // 字符匹配
            } else if (str[i - 1] - 32 == result[j - 1]) {
                memo[i][j] = (memo[i - 1][j - 1] || memo[i - 1][j]); // 小写字母可以转为大写
            } else {
                if (str[i - 1] >= 'A' && str[i - 1] <= 'Z') {
                    memo[i][j] = false; // 大写字母无法转化
                } else {
                    memo[i][j] = memo[i - 1][j]; // 丢弃小写字母
                }
            }
        }
    }
    return memo.back().back(); // 返回最终结果
}
}  // namespace abbreviation
}  // namespace dynamic_programming

/**
 * @brief 自我测试实现
 * @returns void
 */
static void test() {
    std::string s = "daBcd", t = "ABC";
    std::vector<std::vector<bool>> memo(s.size() + 1,
                                        std::vector<bool>(t.size() + 1, false)),
        visited(s.size() + 1, std::vector<bool>(t.size() + 1, false));

    // 测试递归实现
    assert(dynamic_programming::abbreviation::abbreviation_recursion(
               &memo, &visited, s, t) == true);
    // 测试迭代实现
    assert(dynamic_programming::abbreviation::abbreviation(s, t) == true);

    s = "XXVVnDEFYgYeMXzWINQYHAQKKOZEYgSRCzLZAmUYGUGILjMDET";
    t = "XXVVDEFYYMXWINQYHAQKKOZEYSRCLZAUYGUGILMDETQVWU";
    memo = std::vector<std::vector<bool>>(
        s.size() + 1, std::vector<bool>(t.size() + 1, false));
    visited = std::vector<std::vector<bool>>(
        s.size() + 1, std::vector<bool>(t.size() + 1, false));

    // 测试失败情况
    assert(dynamic_programming::abbreviation::abbreviation_recursion(
               &memo, &visited, s, t) == false);
    assert(dynamic_programming::abbreviation::abbreviation(s, t) == false);

    s = "DRFNLZZVHLPZWIupjwdmqafmgkg";
    t = "DRFNLZZVHLPZWI";

    memo = std::vector<std::vector<bool>>(
        s.size() + 1, std::vector<bool>(t.size() + 1, false));
    visited = std::vector<std::vector<bool>>(
        s.size() + 1, std::vector<bool>(t.size() + 1, false));

    // 测试成功情况
    assert(dynamic_programming::abbreviation::abbreviation_recursion(
               &memo, &visited, s, t) == true);
    assert(dynamic_programming::abbreviation::abbreviation(s, t) == true);
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    test();  // 运行自我测试
    return 0;
}
