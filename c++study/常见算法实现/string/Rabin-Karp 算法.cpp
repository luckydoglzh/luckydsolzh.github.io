/**
 * \file
 * \brief [Rabin-Karp 算法](https://en.wikipedia.org/wiki/Rabin–Karp_algorithm)，用于在文本中查找模式，时间复杂度为 O(n + m)
 */
#include <cassert>
#include <cmath>
#include <iostream>
#ifdef _MSC_VER
#include <string>  // 对于 MS Visual C++ 使用此头文件
#else
#include <cstring>  // 对于其他编译器使用 <cstring>
#endif

#define PRIME 5  ///< 哈希函数使用的质数模数

namespace string_search {
/**
 * 将字符串转换为整数 - 用作哈希函数
 * \param[in] s 要哈希的字符串
 * \param[in] n 要哈希的子字符串的长度
 * \returns 返回哈希值（整数）
 */
int64_t create_hash(const std::string& s, int n) {
    int64_t result = 0;
    for (int i = 0; i < n; ++i) {
        result += (int64_t)(s[i] * (int64_t)pow(PRIME, i));  // 将字符按权重加到哈希值中
    }
    return result;
}

/**
 * 通过已知的现有哈希重新计算字符串的哈希值
 * \param[in] s 要哈希的字符串
 * \param[in] old_index 字符串中的旧索引
 * \param[in] new_index 字符串中的新索引
 * \param[in] old_hash 之前的哈希值
 * \param[in] patLength 要哈希的子字符串的长度
 * \returns 返回新的哈希值（整数）
 */
int64_t recalculate_hash(const std::string& s, int old_index, int new_index,
                         int64_t old_hash, int patLength) {
    int64_t new_hash = old_hash - s[old_index];  // 移除旧字符的哈希影响
    new_hash /= PRIME;  // 除以质数，准备移除字符的权重
    new_hash += (int64_t)(s[new_index] * (int64_t)pow(PRIME, patLength - 1));  // 加上新字符的哈希影响
    return new_hash;
}

/**
 * 比较两个子字符串是否相等
 * \param[in] str1 要检查的第一个字符串（模式）
 * \param[in] str2 要检查的第二个字符串（文本）
 * \param[in] start1,str1_end1 第一个字符串中的起始和结束索引
 * \param[in] start2,end2 第二个字符串中的起始和结束索引
 * \returns 如果两个子字符串相等则返回 `true`
 * \returns 如果两个子字符串不相等则返回 `false`
 * @note 可以考虑用 std::string::compare 来替换此函数
 */
bool check_if_equal(const std::string& str1, const std::string& str2,
                    int start1, int end1, int start2, int end2) {
    if (end1 - start1 != end2 - start2) {
        return false;  // 长度不同直接返回 false
    }
    while (start1 <= end1 && start2 <= end2) {
        if (str1[start1] != str2[start2]) {
            return false;  // 如果某个字符不相同，返回 false
        }
        start1++;
        start2++;
    }
    return true;  // 如果遍历完毕都没有不相等的字符，返回 true
}

/**
 * 使用 Rabin-Karp 算法进行字符串模式匹配
 * @param[in] str 需要搜索的文本
 * @param[in] pat 需要查找的模式
 * @return 模式第一次出现的位置索引
 * @return 如果未找到模式则返回 -1
 */
int rabin_karp(const std::string& str, const std::string& pat) {
    int64_t pat_hash = create_hash(pat, pat.size());  // 计算模式的哈希值
    int64_t str_hash = create_hash(str, pat.size());  // 计算文本的前 pat.size() 长度的哈希值
    for (int i = 0; i <= str.size() - pat.size(); ++i) {
        if (pat_hash == str_hash &&  // 如果哈希值相同，再比较具体的子字符串
            check_if_equal(str, pat, i, i + pat.size() - 1, 0, pat.size() - 1)) {
            return i;  // 找到匹配，返回匹配位置
        }
        if (i < str.size() - pat.size()) {
            // 否则，重新计算下一个子字符串的哈希值
            str_hash = recalculate_hash(str, i, i + pat.size(), str_hash, pat.size());
        }
    }
    return -1;  // 如果没有找到模式，返回 -1
}

}  // namespace string_search

using string_search::rabin_karp;

/** 主函数 */
int main(void) {
    // 一些示例测试
    assert(rabin_karp("helloWorld", "world") == -1);  // 未找到匹配
    assert(rabin_karp("helloWorld", "World") == 5);   // 找到匹配，从位置 5 开始
    assert(rabin_karp("this_is_c++", "c++") == 8);     // 找到匹配，从位置 8 开始
    assert(rabin_karp("happy_coding", "happy") == 0);  // 找到匹配，从位置 0 开始
    return 0;
}
