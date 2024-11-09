/**
 * @file
 * @brief          字符串模式匹配 - 暴力法
 */
#include <iostream>
#ifdef _MSC_VER
#include <string>  // 对于 MS Visual C++ 使用此库
#else
#include <cstring> // 对于其他编译器使用此库
#endif
#include <vector>

namespace string_search {
/**
 * 通过将模式与每个子字符串进行比较来查找模式。
 * @param text     可能包含模式的任意字符串
 * @param pattern  要搜索的模式字符串
 * @return         返回模式在文本中开始的位置索引
 * @return         如果未找到模式，返回 -1
 */
int brute_force(const std::string &text, const std::string &pattern) {
    size_t pat_l = pattern.length();  // 获取模式的长度
    size_t txt_l = text.length();     // 获取文本的长度
    int index = -1;                   // 初始值设为 -1，表示未找到
    if (pat_l <= txt_l) {  // 如果模式的长度小于等于文本长度
        // 遍历文本的每一个子字符串，查找匹配的模式
        for (size_t i = 0; i < txt_l - pat_l + 1; i++) {
            std::string s = text.substr(i, pat_l);  // 获取文本中的子字符串
            if (s == pattern) {  // 如果子字符串匹配模式
                index = i;       // 记录匹配的位置
                break;           // 找到第一个匹配后退出循环
            }
        }
    }
    return index;  // 返回找到的索引，未找到返回 -1
}
}  // namespace string_search

using string_search::brute_force;

/** 测试集 */
const std::vector<std::vector<std::string>> test_set = {
    // {文本, 模式, 预期输出}
    {"a", "aa", "-1"},  {"a", "a", "0"},    {"ba", "b", "0"},
    {"bba", "bb", "0"}, {"bbca", "c", "2"}, {"ab", "b", "1"}};

/** 主函数 */
int main() {
    for (const auto &i : test_set) {  // 遍历每个测试用例
        int output = brute_force(i[0], i[1]);  // 执行暴力匹配

        // 如果输出与预期结果匹配，打印 "success"，否则打印 "failure"
        if (std::to_string(output) == i[2]) {
            std::cout << "success\n";
        } else {
            std::cout << "failure\n";
        }
    }
    return 0;
}
