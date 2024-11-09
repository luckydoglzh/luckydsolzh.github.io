/**
 * @file
 * @brief 实现 [Knuth-Morris-Pratt (KMP) 算法](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm) 用于在文本中查找模式，复杂度为 O(n + m)
 * @details
 * 1. 对模式进行预处理，识别出任何与前缀相同的后缀。这样可以在模式与文本不匹配时，知道应该从哪里继续匹配。
 * 2. 一次比较文本中的字符与模式中的字符，在必要时更新在模式中的位置。
 * @author [Yancey](https://github.com/Yancey2023)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作
#include <string>    /// 用于 std::string
#include <vector>    /// 用于 std::vector

/**
 * @namespace string_search
 * @brief 字符串搜索算法
 */
namespace string_search {
/**
 * @brief 生成模式字符串的部分匹配表（即失败函数）。
 * @param pattern 用于创建部分匹配表的模式字符串
 * @returns 返回部分匹配表作为一个向量数组
 */
std::vector<size_t> getFailureArray(const std::string &pattern) {
    size_t pattern_length = pattern.size();
    std::vector<size_t> failure(pattern_length + 1);  // 初始化部分匹配表
    failure[0] = std::string::npos;  // 失败函数的第一个位置设置为无效
    size_t j = std::string::npos;  // 初始化 j 为无效值
    for (int i = 0; i < pattern_length; i++) {  // 遍历模式字符串的每个字符
        while (j != std::string::npos && pattern[j] != pattern[i]) {  // 如果字符不匹配，则回退到失败函数表中的位置
            j = failure[j];  // 跳转到上一个匹配的前缀位置
        }
        failure[i + 1] = ++j;  // 记录当前字符的位置
    }
    return failure;  // 返回计算好的失败函数
}

/**
 * @brief KMP 算法用于在文本中查找模式字符串
 * @param pattern 要查找的模式字符串
 * @param text 要搜索的文本
 * @returns 如果找到匹配，返回模式字符串在文本中的起始索引
 * @returns 如果未找到匹配，返回 `std::string::npos`
 */
size_t kmp(const std::string &pattern, const std::string &text) {
    if (pattern.empty()) {  // 如果模式字符串为空，则从索引 0 开始
        return 0;
    }
    std::vector<size_t> failure = getFailureArray(pattern);  // 获取模式字符串的部分匹配表
    size_t text_length = text.size();  // 文本的长度
    size_t pattern_length = pattern.size();  // 模式字符串的长度
    size_t k = 0;  // 当前模式字符串的位置
    for (size_t j = 0; j < text_length; j++) {  // 遍历文本的每个字符
        while (k != std::string::npos && pattern[k] != text[j]) {  // 如果字符不匹配，则通过失败函数回退
            k = failure[k];  // 回退到部分匹配表中的位置
        }
        if (++k == pattern_length) {  // 如果找到完整的匹配
            return j - k + 1;  // 返回匹配开始的位置
        }
    }
    return std::string::npos;  // 如果未找到匹配，返回无效值
}
}  // namespace string_search

using string_search::kmp;

/**
 * @brief KMP 算法的自测试函数
 * @returns void
 */
static void tests() {
    assert(kmp("abc1abc12l", "alskfjaldsabc1abc1abc12k2") == std::string::npos);  // 测试不存在的情况
    assert(kmp("bca", "abcabc") == 1);  // 测试匹配从索引 1 开始
    assert(kmp("World", "helloWorld") == 5);  // 测试匹配从索引 5 开始
    assert(kmp("c++", "his_is_c++") == 7);  // 测试匹配从索引 7 开始
    assert(kmp("happy", "happy_coding") == 0);  // 测试匹配从索引 0 开始
    assert(kmp("", "pattern is empty") == 0);  // 测试空模式字符串，匹配从索引 0 开始

    // 如果所有测试通过，输出成功信息
    std::cout << "All KMP algorithm tests have successfully passed!\n";
}

/*
 * @brief 主函数
 * @returns 0 程序退出时返回 0
 */
int main() {
    tests();  // 运行测试函数
    return 0;
}
