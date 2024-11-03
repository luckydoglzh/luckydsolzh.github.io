/**
 * @file
 * @brief 包含函数 ::longest_common_string_length 的定义
 * @details
 * 函数 ::longest_common_string_length 计算通过移除字符从两个输入字符串中创建的最长公共字符串的长度。
 *
 * @author [Nikhil Arora](https://github.com/nikhilarora068)
 * @author [Piotr Idzik](https://github.com/vil02)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于 std::cout
#include <string>    /// 用于 std::string
#include <utility>   /// 用于 std::move
#include <vector>    /// 用于 std::vector

/**
 * @brief 计算从输入字符串中创建的最长公共字符串的长度
 * @details 时间和空间复杂度为 O(str_a.size()*str_b.size())
 * @param string_a 第一个输入字符串
 * @param string_b 第二个输入字符串
 * @returns 可以从 string_a 和 string_b 中构造的最长公共字符串的长度
 */
std::size_t longest_common_string_length(const std::string& string_a,
                                         const std::string& string_b) {
    const auto size_a = string_a.size();  // 获取字符串 a 的长度
    const auto size_b = string_b.size();  // 获取字符串 b 的长度
    // 创建一个二维数组来存储子解决方案
    std::vector<std::vector<std::size_t>> sub_sols(
        size_a + 1, std::vector<std::size_t>(size_b + 1, 0));

    const auto limit = static_cast<std::size_t>(-1);
    // 从后向前遍历字符串 a 和 b
    for (std::size_t pos_a = size_a - 1; pos_a != limit; --pos_a) {
        for (std::size_t pos_b = size_b - 1; pos_b != limit; --pos_b) {
            if (string_a[pos_a] == string_b[pos_b]) {  // 如果字符相同
                // 更新子解决方案的值
                sub_sols[pos_a][pos_b] = 1 + sub_sols[pos_a + 1][pos_b + 1];
            } else {
                // 取两个子解决方案中的最大值
                sub_sols[pos_a][pos_b] = std::max(sub_sols[pos_a + 1][pos_b],
                                                  sub_sols[pos_a][pos_b + 1]);
            }
        }
    }

    return sub_sols[0][0];  // 返回最终的最长公共字符串长度
}

/**
 * @brief 表示函数 ::longest_common_string_length 的单个示例输入和期望输出
 */
struct TestCase {
    const std::string string_a;  // 第一个字符串
    const std::string string_b;  // 第二个字符串
    const std::size_t common_string_len;  // 期望的最长公共字符串长度

    TestCase(std::string string_a, std::string string_b,
             const std::size_t in_common_string_len)
        : string_a(std::move(string_a)),  // 移动字符串 a
          string_b(std::move(string_b)),  // 移动字符串 b
          common_string_len(in_common_string_len) {}  // 初始化期望长度
};

/**
 * @return 用于测试 ::longest_common_string_length 的示例数据
 */
std::vector<TestCase> get_test_cases() {
    return {TestCase("", "", 0),           // 示例 1
            TestCase("ab", "ab", 2),     // 示例 2
            TestCase("ab", "ba", 1),     // 示例 3
            TestCase("", "xyz", 0),      // 示例 4
            TestCase("abcde", "ace", 3), // 示例 5
            TestCase("BADANA", "ANADA", 3), // 示例 6
            TestCase("BADANA", "CANADAS", 3), // 示例 7
            TestCase("a1a234a5aaaa6", "A1AAAA234AAA56AAAAA", 6), // 示例 8
            TestCase("123x", "123", 3),  // 示例 9
            TestCase("12x3x", "123", 3),  // 示例 10
            TestCase("1x2x3x", "123", 3),  // 示例 11
            TestCase("x1x2x3x", "123", 3),  // 示例 12
            TestCase("x12x3x", "123", 3)}; // 示例 13
}

/**
 * @brief 检查函数 ::longest_common_string_length 是否返回与示例数据一致的结果
 * @param test_cases 测试用例列表
 * @tparam type 表示测试用例的类型
 */
template <typename TestCases>
static void test_longest_common_string_length(const TestCases& test_cases) {
    for (const auto& cur_tc : test_cases) {
        // 断言函数返回值与期望值一致
        assert(longest_common_string_length(cur_tc.string_a, cur_tc.string_b) ==
               cur_tc.common_string_len);
    }
}

/**
 * @brief 检查函数 ::longest_common_string_length 是否对称
 * @param test_cases 测试用例列表
 * @tparam type 表示测试用例的类型
 */
template <typename TestCases>
static void test_longest_common_string_length_is_symmetric(
    const TestCases& test_cases) {
    for (const auto& cur_tc : test_cases) {
        // 检查参数翻转后结果是否一致
        assert(longest_common_string_length(cur_tc.string_b, cur_tc.string_a) ==
               cur_tc.common_string_len);
    }
}

/**
 * @brief 反转给定字符串
 * @param in_str 输入字符串
 * @return 字符串中字符的顺序反转后的字符串
 */
std::string reverse_str(const std::string& in_str) {
    return {in_str.rbegin(), in_str.rend()};  // 使用 rbegin 和 rend 反转字符串
}

/**
 * @brief 检查函数 ::longest_common_string_length 是否对反转输入返回一致的结果
 * @param test_cases 测试用例列表
 * @tparam type 表示测试用例的类型
 */
template <typename TestCases>
static void test_longest_common_string_length_for_reversed_inputs(
    const TestCases& test_cases) {
    for (const auto& cur_tc : test_cases) {
        // 检查反转输入后的结果
        assert(longest_common_string_length(reverse_str(cur_tc.string_a),
                                            reverse_str(cur_tc.string_b)) ==
               cur_tc.common_string_len);
    }
}

/**
 * @brief 运行所有测试以验证 ::longest_common_string_length 函数
 */
static void tests() {
    const auto test_cases = get_test_cases();  // 获取测试用例
    assert(test_cases.size() > 0);  // 确保有测试用例
    test_longest_common_string_length(test_cases);  // 测试函数
    test_longest_common_string_length_is_symmetric(test_cases);  // 测试对称性
    test_longest_common_string_length_for_reversed_inputs(test_cases);  // 测试反转输入

    std::cout << "所有测试成功通过！\n";  // 输出结果
}

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main() {
    tests();  // 运行所有测试
    return 0;  // 正常退出
}
