/**
 * @file
 * @brief 实现 [回文划分](https://leetcode.com/problems/palindrome-partitioning-ii/) 算法，给出所需的最小划分数
 *
 * @details
 * 回文划分使用动态规划，遍历所有可能的划分以找到最小划分。给定一个字符串，返回将其划分为多个回文所需的最小划分数。
 * [回文划分](https://www.geeksforgeeks.org/palindrome-partitioning-dp-17/) 的总体时间复杂度为 O(n^2)。
 * 例如：
 * - 示例 1：字符串 "nitik" 输出：2 => "n | iti | k"
 * - 示例 2：字符串 "ababbbabbababa" 输出：3 => "aba | b | bbabb | ababa"
 * @author [Sujay Kaushik](https://github.com/sujaykaushik008)
 */

#include <algorithm>  // 用于 std::min
#include <cassert>    // 用于 assert
#include <climits>    // 用于 INT_MAX
#include <iostream>   // 用于输入输出操作
#include <vector>     // 用于 std::vector

/**
 * @namespace dynamic_programming
 * @brief 动态规划算法
 */
namespace dynamic_programming {

/**
 * @namespace palindrome_partitioning
 * @brief 实现 [回文划分](https://leetcode.com/problems/palindrome-partitioning-ii/) 算法的函数
 */
namespace palindrome_partitioning {

/**
 * 使用查找表方法实现回文划分算法
 * @param str 输入字符串
 * @returns 所需的最小划分数
 */
int pal_part(const std::string &str) {
    int n = str.size();

    // 创建查找表以存储最小划分数
    std::vector<std::vector<int> > cuts(n, std::vector<int>(n, 0));

    // 创建查找表以检查回文
    std::vector<std::vector<bool> > is_palindrome(n,
                                                  std::vector<bool>(n, false));

    // 初始化
    for (int i = 0; i < n; i++) {
        is_palindrome[i][i] = true;  // 单个字符是回文
        cuts[i][i] = 0;               // 单个字符不需要划分
    }

    // 计算所有可能的划分
    for (int len = 2; len <= n; len++) { // len 为当前考虑的子串长度
        for (int start_index = 0; start_index < n - len + 1; start_index++) {
            int end_index = start_index + len - 1; // 计算当前子串的结束索引

            // 判断当前子串是否为回文
            if (len == 2) {
                is_palindrome[start_index][end_index] =
                    (str[start_index] == str[end_index]);
            } else {
                is_palindrome[start_index][end_index] =
                    (str[start_index] == str[end_index]) &&
                    is_palindrome[start_index + 1][end_index - 1];
            }

            // 如果当前子串是回文，则无需划分
            if (is_palindrome[start_index][end_index]) {
                cuts[start_index][end_index] = 0;
            } else {
                cuts[start_index][end_index] = INT_MAX; // 初始化为最大值
                for (int partition = start_index; partition <= end_index - 1;
                     partition++) {
                    // 更新最小划分数
                    cuts[start_index][end_index] =
                        std::min(cuts[start_index][end_index],
                                 cuts[start_index][partition] +
                                     cuts[partition + 1][end_index] + 1);
                }
            }
        }
    }

    return cuts[0][n - 1]; // 返回整个字符串的最小划分数
}
}  // namespace palindrome_partitioning
}  // namespace dynamic_programming

/**
 * @brief 测试函数
 * @return void
 */
static void test() {
    // 自定义输入向量
    std::vector<std::string> custom_input{"nitik", "ababbbabbababa", "abdc"};

    // 通过 pal_part 函数计算的输出向量
    std::vector<int> calculated_output(3);

    for (int i = 0; i < 3; i++) {
        calculated_output[i] =
            dynamic_programming::palindrome_partitioning::pal_part(
                custom_input[i]);
    }

    // 预期输出向量
    std::vector<int> expected_output{2, 3, 3};

    // 使用 assert 函数测试实现
    // 如果任何预期测试失败，将引发错误
    // 否则将不输出任何内容
    for (int i = 0; i < 3; i++) {
        assert(expected_output[i] == calculated_output[i]);
    }

    std::cout << "所有测试均成功通过！\n";
}

/**
 * @brief 主函数
 * @returns 0 正常退出
 */
int main() {
    test();  // 执行测试
    return 0; // 正常退出
}
