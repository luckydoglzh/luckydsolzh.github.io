/**
 * @file
 * @brief 实现 [Manacher 算法](https://en.wikipedia.org/wiki/Longest_palindromic_substring) 用于在字符串中查找最长回文子串
 * @details
 * Manacher 算法用于在 O(n) 时间内找到字符串中的最长回文子串。它利用了回文串的特性，即回文串的前半部分与后半部分对称，因此如果前半部分是回文串，那么后半部分也是回文串。
 * @author [Riti Kumari](https://github.com/riti2409)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于 std::vector 容器
#ifdef _MSC_VER
#include <string>  /// 对于 MS Visual C++，需要包含 <string>
#else
#include <cstring>  /// 对于其他编译器，使用 <cstring>
#endif

/**
 * @namespace strings
 * @brief 字符串相关算法
 */
namespace strings {
/**
 * @namespace manacher
 * @brief 实现 [Manacher 算法](https://en.wikipedia.org/wiki/Longest_palindromic_substring) 的函数
 */
namespace manacher {
/**
 * @brief 实现 Manacher 算法
 * @param prototype 输入字符串，在该字符串中查找回文子串
 * @returns 返回最长的回文子串
 */
std::string manacher(const std::string &prototype) {
    if (prototype.size() > 0) {
        // 在输入字符串之间插入特殊字符（#），以处理偶数长度回文的情况
        std::string stuffed_string = "";
        for (auto str : prototype) {
            stuffed_string += str;
            stuffed_string += "#";
        }
        stuffed_string = "@#" + stuffed_string + "&";  // 在字符串两端添加特殊字符以方便边界处理

        std::vector<uint64_t> palindrome_max_half_length(
            stuffed_string.size(),
            0);  // 用于存储每个字符为中心的最大回文半长度

        uint64_t bigger_center =
            0;  // 用于记录回文的中心位置（最右侧的回文中心）

        uint64_t right = 0;  // 用于记录回文从 center 到最右边的最远距离

        // i 是考虑作为回文中心的字符索引
        for (uint64_t i = 1; i < stuffed_string.size() - 1; i++) {
            if (i < right) {  // 如果 i 在当前最大回文范围内，利用对称性
                uint64_t opposite_to_i =
                    2 * bigger_center - i;  // 对称位置

                // 选择当前回文中心和对称位置的回文半长度中的较小者作为 i 的最初半长度
                palindrome_max_half_length[i] = std::min(
                    palindrome_max_half_length[opposite_to_i], right - i);
            }

            // 尝试扩展回文串，直到不再匹配
            while (stuffed_string[i + (palindrome_max_half_length[i] + 1)] == 
                   stuffed_string[i - (palindrome_max_half_length[i] + 1)]) {
                palindrome_max_half_length[i]++;
            }

            // 如果当前回文串超出了 right 位置，更新 center 和 right
            if (i + palindrome_max_half_length[i] > right) {
                bigger_center = i;
                right = i + palindrome_max_half_length[i];
            }
        }

        // 提取最长回文子串
        uint64_t half_length = 0;   // 最长回文的半长度
        uint64_t center_index = 0;  // 最长回文中心的索引

        for (uint64_t i = 1; i < stuffed_string.size() - 1; i++) {
            if (palindrome_max_half_length[i] > half_length) {
                half_length = palindrome_max_half_length[i];
                center_index = i;
            }
        }

        std::string palindromic_substring =
            "";  // 用于存储最终的回文子串

        if (half_length > 0) {
            // 通过中心索引和半长度计算回文串的起始和结束位置
            uint64_t start = center_index - half_length + 1;
            uint64_t end = center_index + half_length - 1;
            for (uint64_t index = start; index <= end; index += 2) {  // 每两个字符之间跳一步
                palindromic_substring += stuffed_string[index];
            }
        } else {
            // 如果没有回文子串，返回任意一个字符作为回文子串
            palindromic_substring = prototype[0];
        }
        return palindromic_substring;

    } else {
        // 处理空字符串的情况
        return "";
    }
}

}  // namespace manacher
}  // namespace strings

/**
 * @brief 自测试函数
 * @returns void
 */
static void test() {
    assert(strings::manacher::manacher("") == "");  // 空字符串
    assert(strings::manacher::manacher("abababc") == "ababa");  // 示例测试
    assert(strings::manacher::manacher("cbaabd") == "baab");  // 示例测试
    assert(strings::manacher::manacher("DedzefDeD") == "DeD");  // 示例测试
    assert(strings::manacher::manacher("XZYYXXYZXX") == "YXXY");  // 示例测试
    assert(strings::manacher::manacher("1sm222m10abc") == "m222m");  // 示例测试
    assert(strings::manacher::manacher("798989591") == "98989");  // 示例测试
    assert(strings::manacher::manacher("xacdedcax") == "xacdedcax");  // 示例测试
    assert(strings::manacher::manacher("xaccax") == "xaccax");  // 示例测试
    assert(strings::manacher::manacher("a") == "a");  // 单字符
    assert(strings::manacher::manacher("xy") == "x");  // 无回文
    assert(strings::manacher::manacher("abced") == "a");  // 无回文

    std::cout << "所有测试已通过！" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 程序退出时返回 0
 */
int main() {
    test();  // 运行自测试
    return 0;
}
