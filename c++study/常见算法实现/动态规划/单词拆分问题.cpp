/**
 * @file
 * @brief [单词拆分问题](https://leetcode.com/problems/word-break/)
 * @details
 * 给定一个非空字符串 s 和一个字典 wordDict，其中包含一个非空单词列表，确定 s 是否可以被拆分为一个或多个字典单词的空格分隔序列。
 *
 * 注意：
 * 字典中的相同单词可以在拆分中多次使用。你可以假设字典不包含重复的单词。
 *
 * 示例 1：
 * 输入：s = "leetcode"，wordDict = ["leet", "code"]
 * 输出：true
 * 解释：返回 true，因为 "leetcode" 可以拆分为 "leet code"。
 *
 * 示例 2：
 * 输入：s = "applepenapple"，wordDict = ["apple", "pen"]
 * 输出：true
 * 解释：返回 true，因为 "applepenapple" 可以拆分为 "apple pen apple"。注意，你可以重用字典中的单词。
 *
 * 示例 3：
 * 输入：s = "catsandog"，wordDict = ["cats", "dog", "sand", "and", "cat"]
 * 输出：false
 *
 * @author [Akshay Anand] (https://github.com/axayjha)
 */

#include <cassert>
#include <climits>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

/**
 * @namespace dynamic_programming
 * @brief 动态规划算法
 */
namespace dynamic_programming {

/**
 * @namespace word_break
 * @brief [单词拆分](https://leetcode.com/problems/word-break/)问题的函数
 */
namespace word_break {

/**
 * @brief 检查字符串是否存在于无序集合中
 *
 * @param str 要搜索的字符串
 * @param strSet 要查找的字符串无序集合
 * @returns 如果 str 在 strSet 中存在，则返回 `true`
 * @returns 如果 str 不在 strSet 中，则返回 `false`
 */
bool exists(const std::string &str,
            const std::unordered_set<std::string> &strSet) {
    return strSet.find(str) != strSet.end();
}

/**
 * @brief 检查从位置 'pos' 开始的字符串是否可以拆分，并继续正确拆分剩余字符串
 *
 * @param s 要拆分的完整字符串
 * @param strSet 用作参考字典的无序字符串集合
 * @param pos 当前检查的索引
 * @param dp 用于存储每个位置的解的向量
 * @returns 如果在位置 pos 拆分的有效解决方案/拆分可能，则返回 `true`
 * @returns 否则返回 `false`
 */
bool check(const std::string &s, const std::unordered_set<std::string> &strSet,
           int pos, std::vector<int> *dp) {
    if (pos == s.length()) {
        // 如果到达字符串末尾，表示整个字符串已正确拆分，返回 true
        return true;
    }

    if (dp->at(pos) != INT_MAX) {
        // 如果 dp[pos] 不是 INT_MAX，表示我们已经保存了该位置的解
        return dp->at(pos) == 1; // 返回该位置的解是否为 true
    }

    std::string wordTillNow = ""; // 用于存储到当前不同位置的前缀字符串

    for (int i = pos; i < s.length(); i++) {
        // 从 pos 到字符串末尾循环，检查是否存在有效的拆分
        wordTillNow += std::string(1, s[i]); // 保存到当前位置的前缀

        // 如果当前前缀在字典中存在，且剩余子串也可以合法拆分，则
        // 将位置 pos 的解设置为 true，并返回
        if (exists(wordTillNow, strSet) && check(s, strSet, i + 1, dp)) {
            dp->at(pos) = 1; // 标记该位置的解为 true
            return true;
        }
    }
    // 如果没有返回，表示该位置没有合法的拆分
    dp->at(pos) = 0; // 将该位置的解设置为 false
    return false;    // 返回该位置没有解
}

/**
 * @brief 检查字符串是否可以拆分为字典中的字符串
 *
 * @param s 要拆分的完整字符串
 * @param wordDict 用作字典的单词向量
 * @returns 如果 s 可以由 wordDict 中的字符串组合而成，则返回 `true`
 * @return 否则返回 `false`
 */
bool wordBreak(const std::string &s, const std::vector<std::string> &wordDict) {
    // 无序集合用于存储字典中的单词，便于常量时间搜索
    std::unordered_set<std::string> strSet;
    for (const auto &s : wordDict) {
        strSet.insert(s);
    }
    // 用于记忆化的向量，索引 i 的值将告诉 s 是否可以在位置 i 上正确拆分
    std::vector<int> dp(s.length(), INT_MAX); // 初始化为 INT_MAX（表示无解）

    // 从位置 0 开始检查字符串的拆分
    return check(s, strSet, 0, &dp);
}

}  // namespace word_break
}  // namespace dynamic_programming

/**
 * @brief 测试实现
 * @returns void
 */
static void test() {
    // 完整字符串
    const std::string s = "applepenapple";
    // 要使用的字典
    const std::vector<std::string> wordDict = {"apple", "pen"};

    assert(dynamic_programming::word_break::wordBreak(s, wordDict));

    // 应返回 true，因为 applepenapple 可以拆分为 apple + pen + apple
    std::cout << dynamic_programming::word_break::wordBreak(s, wordDict)
              << std::endl;
    std::cout << "测试实现通过！\n";
}

/**
 * @brief 主函数
 * @returns 0 退出时
 */
int main() {
    test();  // 调用测试函数 :)

    // 完整字符串
    const std::string s = "applepenapple";
    // 要使用的字典
    const std::vector<std::string> wordDict = {"apple", "pen"};

    // 应返回 true，因为 applepenapple 可以拆分为 apple + pen + apple
    std::cout << dynamic_programming::word_break::wordBreak(s, wordDict)
              << std::endl;
}
