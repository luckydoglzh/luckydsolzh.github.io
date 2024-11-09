/**
 * @file
 * @brief [Z 函数](https://cp-algorithms.com/string/z-function.html)用于查找模式在文本中的出现位置，时间和空间复杂度为 O(n + m)
 * @details
 * 1. 字符串的 Z 函数是一个长度为 n 的数组，其中第 i 个元素表示从位置 i 开始的最大前缀长度，这个前缀与字符串的前几个字符相同。
 * 2. 示例：字符串 "ababb" 的 Z 函数为 [5, 0, 2, 1, 0]，即 z[2] = 2，因为 s[2] = s[0]，s[3] = s[1]，而 s[4] != s[2]。
 * @author [Ritika Gupta](https://github.com/RitikaGupta8734)
 */

#include <iostream>  /// 用于 IO 操作
#ifdef _MSC_VER
#include <string>  /// 对于 MS Visual C++ 使用此头文件
#else
#include <cstring>  /// 对于其他编译器使用 <cstring>
#endif
#include <cassert>  /// 用于断言操作
#include <vector>   /// 用于 std::vector

/**
 * @brief 生成输入字符串的 Z 函数。
 * \param[in] pattern 需要计算 Z 函数的字符串
 * \returns 返回 Z 函数的输出结果，类型为 vector 数组
 */
std::vector<uint64_t> Z_function(const std::string &pattern) {
    uint64_t pattern_length = pattern.size();  // 获取模式的长度
    std::vector<uint64_t> z(pattern_length, 0);  // 初始化 Z 函数数组

    // 通过滑动窗口计算 Z 函数值
    for (uint64_t i = 1, l = 0, r = 0; i < pattern_length; i++) {
        if (i <= r) {
            // 如果当前索引 i 在区间 [l, r] 内，使用已经计算的 Z 函数值进行优化
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        // 通过逐个字符比较扩展 Z 函数值
        while (i + z[i] < pattern_length && pattern[z[i]] == pattern[i + z[i]]) {
            z[i]++;
        }
        // 更新右边界 r
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
        }
    }
    return z;  // 返回计算得到的 Z 函数
}

/**
 * @brief 使用 Z 函数在文本中查找模式。
 * \param[in] pattern 要搜索的模式字符串
 * \param[in] text 要搜索的文本字符串
 * \returns 返回一个 vector 数组，包含模式在文本中出现的位置索引
 */
std::vector<uint64_t> find_pat_in_text(const std::string &pattern,
                                       const std::string &text) {
    uint64_t text_length = text.size(), pattern_length = pattern.size();
    // 计算模式和文本合并后的 Z 函数，注意中间加入了一个特殊字符 '#'
    std::vector<uint64_t> z = Z_function(pattern + '#' + text);
    std::vector<uint64_t> matching_indexes;  // 存储匹配的位置

    // 遍历 Z 函数，查找所有模式匹配的位置
    for (uint64_t i = 0; i < text_length; i++) {
        if (z[i + pattern_length + 1] == pattern_length) {
            matching_indexes.push_back(i);  // 如果 Z 值等于模式的长度，说明找到了匹配
        }
    }
    return matching_indexes;  // 返回匹配的位置索引
}

/**
 * @brief 自我测试实现
 * @returns void
 */
static void test() {
    // 常规案例
    std::string text1 = "alskfjaldsabc1abc1abcbksbcdnsdabcabc";  // 测试文本
    std::string pattern1 = "abc";  // 要查找的模式

    // matching_indexes1 存储模式在文本中的位置
    std::vector<uint64_t> matching_indexes1 = find_pat_in_text(pattern1, text1);
    // 断言检查匹配的位置是否正确
    assert((matching_indexes1 == std::vector<uint64_t>{10, 14, 18, 30, 33}));

    // 极限案例
    std::string text2 = "greengrass";  // 测试文本
    std::string pattern2 = "abc";  // 要查找的模式

    // matching_indexes2 存储模式在文本中的位置
    std::vector<uint64_t> matching_indexes2 = find_pat_in_text(pattern2, text2);
    // 断言检查未找到匹配
    assert((matching_indexes2 == std::vector<uint64_t>{}));
}

/**
 * @brief 主函数
 * @returns 0 作为程序退出的状态
 */
int main() {
    test();  // 运行自我测试
    return 0;
}
