/**
 * @file
 * @brief
 * [Boyer–Moore](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm)
 * 算法通过在不同的对齐方式下执行显式字符比较来搜索文本 T 中模式 P 的出现。
 * 与对所有对齐进行暴力搜索（共有 n - m + 1 种）不同，Boyer–Moore 使用预处理 P 时获得的信息来跳过尽可能多的对齐。
 *
 * @details
 * 此算法的关键见解是，如果比较模式的末尾与文本的字符，则可以沿着文本跳跃，而无需检查文本的每个字符。
 * 之所以这样做是因为在将模式与文本对齐时，模式的最后一个字符与文本中的字符进行比较。
 *
 * 如果字符不匹配，则无需继续向文本后面搜索。这使我们得到两种情况。
 *
 * 情况 1：
 * 如果文本中的字符与模式中的任何字符都不匹配，则下一个要检查的文本字符位于文本中 m 个字符的位置，
 * 其中 m 是模式的长度。
 *
 * 情况 2：
 * 如果文本中的字符在模式中，则模式沿着文本部分移动以对齐匹配的字符，并重复此过程。
 *
 * 有两个移位规则：
 *
 * [坏字符规则](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm#The_bad_character_rule)
 *
 * [好后缀规则](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm#The_good_suffix_rule)
 *
 * 移位规则作为常数时间表查找实现，使用在预处理 P 时生成的表。
 * @author [Stoycho Kyosev](https://github.com/stoychoX)
 */

#include <cassert>   /// 用于 assert
#include <climits>   /// 用于 CHAR_MAX 宏
#include <cstring>   /// 用于 strlen
#include <iostream>  /// 用于输入输出操作
#include <string>    /// 用于 std::string
#include <vector>    /// 用于 std::vector

#define APLHABET_SIZE CHAR_MAX  ///< 我们使用的字母表中的符号数量

/**
 * @namespace
 * @brief 字符串算法
 */
namespace strings {
/**
 * @namespace
 * @brief [Boyer-Moore](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm)
 * 算法实现的函数
 */
namespace boyer_moore {
/**
 * @brief 表示搜索文本中预处理模式所需的所有数据的结构。
 */
struct pattern {
    std::string pat;  // 模式字符串

    std::vector<size_t>
        bad_char;  ///< 坏字符表，用于 [坏字符启发式](https://www.geeksforgeeks.org/boyer-moore-algorithm-for-pattern-searching/)

    std::vector<size_t>
        good_suffix;  ///< 好后缀表，用于 [好后缀启发式](https://www.geeksforgeeks.org/boyer-moore-algorithm-good-suffix-heuristic/?ref=rp)
};

/**
 * @brief 预处理好后缀表的函数
 *
 * @param str 被预处理的字符串
 * @param arg 好后缀表
 * @returns void
 */
void init_good_suffix(const std::string& str, std::vector<size_t>& arg) {
    arg.resize(str.size() + 1, 0);

    // border_pos[i] - str[i..] 的最长真后缀的索引，同时也是一个真前缀。
    std::vector<size_t> border_pos(str.size() + 1, 0);

    size_t current_char = str.length();

    size_t border_index = str.length() + 1;

    border_pos[current_char] = border_index;

    while (current_char > 0) {
        while (border_index <= str.length() &&
               str[current_char - 1] != str[border_index - 1]) {
            if (arg[border_index] == 0) {
                arg[border_index] = border_index - current_char;  // 更新好后缀表
            }

            border_index = border_pos[border_index];  // 回退
        }

        current_char--;
        border_index--;
        border_pos[current_char] = border_index;  // 设置边界
    }

    size_t largest_border_index = border_pos[0];

    for (size_t i = 0; i < str.size(); i++) {
        if (arg[i] == 0) {
            arg[i] = largest_border_index;  // 更新好后缀表
        }

        // 如果超过了最大边界，则在遍历时找到下一个
        if (i == largest_border_index) {
            largest_border_index = border_pos[largest_border_index];
        }
    }
}

/**
 * @brief 预处理坏字符表的函数
 *
 * @param str 被预处理的字符串
 * @param arg 坏字符表
 * @returns void
 */
void init_bad_char(const std::string& str, std::vector<size_t>& arg) {
    arg.resize(APLHABET_SIZE, str.length());  // 初始化为字符串长度

    for (size_t i = 0; i < str.length(); i++) {
        arg[str[i]] = str.length() - i - 1;  // 更新坏字符表
    }
}

/**
 * @brief 初始化模式的函数
 *
 * @param str 用于初始化的文本
 * @param arg 初始化后的结构
 * @returns void
 */
void init_pattern(const std::string& str, pattern& arg) {
    arg.pat = str;  // 设置模式
    init_bad_char(str, arg.bad_char);  // 预处理坏字符
    init_good_suffix(str, arg.good_suffix);  // 预处理好后缀
}

/**
 * @brief 实现 Boyer-Moore 算法的函数。
 *
 * @param str 我们要搜索的文本。
 * @param arg 包含预处理模式的结构
 * @return 找到模式在文本中的出现索引的向量
 */
std::vector<size_t> search(const std::string& str, const pattern& arg) {
    size_t index_position = arg.pat.size() - 1;  // 当前索引位置
    std::vector<size_t> index_storage;  // 存储找到的索引

    while (index_position < str.length()) {
        size_t index_string = index_position;  // 当前文本索引
        int index_pattern = static_cast<int>(arg.pat.size()) - 1;  // 当前模式索引

        // 逐个字符比较模式与文本
        while (index_pattern >= 0 &&
               str[index_string] == arg.pat[index_pattern]) {
            --index_pattern;  // 移动模式索引
            --index_string;   // 移动文本索引
        }

        if (index_pattern < 0) {
            // 找到匹配
            index_storage.push_back(index_position - arg.pat.length() + 1);
            index_position += arg.good_suffix[0];  // 移动文本索引
        } else {
            // 根据坏字符和好后缀表进行索引调整
            index_position += std::max(arg.bad_char[str[index_string]], arg.good_suffix[index_pattern + 1]);
        }
    }

    return index_storage;  // 返回匹配索引
}

/**
 * @brief 检查 pat 是否为 str 的前缀。
 *
 * @param str 指向输入文本某部分的指针。
 * @param pat 被搜索的模式。
 * @param len 被搜索模式的长度
 * @returns `true` 如果 pat 是 str 的前缀。
 * @returns `false` 如果 pat 不是 str 的前缀。
 */
bool is_prefix(const char* str, const char* pat, size_t len) {
    if (strlen(str) < len) {
        return false;  // 长度不足
    }

    for (size_t i = 0; i < len; i++) {
        if (str[i] != pat[i]) {
            return false;  // 不匹配
        }
    }

    return true;  // 是前缀
}

/**
 * @brief 测试用例，搜索每个出现的单词 'and'
 * @param text 要搜索单词 'and' 的文本
 * @returns void
 */
void and_test(const char* text) {
    strings::boyer_moore::pattern ands;
    strings::boyer_moore::init_pattern("and", ands);  // 初始化模式
    std::vector<size_t> indexes = strings::boyer_moore::search(text, ands);  // 执行搜索

    assert(indexes.size() == 2);  // 断言出现次数为2
    assert(strings::boyer_moore::is_prefix(text + indexes[0], "and", 3));  // 检查前缀
    assert(strings::boyer_moore::is_prefix(text + indexes[1], "and", 3));  // 检查前缀
}

/**
 * @brief 测试用例，搜索每个出现的单词 'pat'
 * @param text 要搜索单词 'pat' 的文本
 * @returns void
 */
void pat_test(const char* text) {
    strings::boyer_moore::pattern pat;
    strings::boyer_moore::init_pattern("pat", pat);  // 初始化模式
    std::vector<size_t> indexes = strings::boyer_moore::search(text, pat);  // 执行搜索

    assert(indexes.size() == 6);  // 断言出现次数为6

    for (const auto& currentIndex : indexes) {
        assert(strings::boyer_moore::is_prefix(text + currentIndex, "pat", 3));  // 检查前缀
    }
}

/**
 * @brief 自测实现
 * @returns void
 */
static void tests() {
    const char* text =
        "When pat Mr. and Mrs. pat Dursley woke up on the dull, gray  \
                            Tuesday our story starts, \
                there was nothing about pat the cloudy sky outside to pat suggest that\
                        strange and \
                    mysterious things would pat soon be happening all pat over the \
                        country.";

    and_test(text);  // 测试 'and'
    pat_test(text);  // 测试 'pat'

    std::cout << "所有测试成功通过！\n";  // 输出结果
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    tests();  // 运行自测实现
    return 0;  // 退出程序
}
