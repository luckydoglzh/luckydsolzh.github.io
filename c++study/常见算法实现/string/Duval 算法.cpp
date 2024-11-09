/**
 * @file duval.cpp
 * @brief 实现 [Duval 算法](https://en.wikipedia.org/wiki/Lyndon_word)
 *
 * @details
 * Duval 算法是用于寻找字符串的字典序最小旋转的算法。它基于 Lyndon 字的概念。
 * Lyndon 字定义为在旋转等价类中字典序最小的字符串。旋转等价类是通过旋转字符串得到的所有字符串的集合。
 * 例如，"abc" 的旋转等价类是 {"abc", "bca", "cab"}，其中字典序最小的字符串是 "abc"。
 *
 * Duval 算法通过遍历字符串并找到一个字典序最小的旋转，确保其是一个 Lyndon 字。
 * 这个过程通过比较字符串与其后缀并找到字典序小于字符串的最小后缀来实现。
 * 然后将该后缀添加到结果中，继续对剩余的字符串进行同样的操作。
 * 该算法的时间复杂度是 O(n)，其中 n 是字符串的长度。
 *
 * @note 虽然 Lyndon 字是描述字符串的概念，Duval 算法也可以用于找到任何可比较元素序列的字典序最小循环移位。
 *
 * @author [Amine Ghoussaini](https://github.com/aminegh20)
*/

#include <array>    /// 用于 std::array
#include <cassert>  /// 用于 assert
#include <cstddef>  /// 用于 std::size_t
#include <deque>    /// 用于 std::deque
#include <iostream> /// 用于 std::cout 和 std::endl
#include <string>   /// 用于 std::string
#include <vector>   /// 用于 std::vector

/**
 * @brief 字符串操作算法
 * @namespace
 */
namespace string {
/**
 * @brief 查找序列的字典序最小循环移位
 * @tparam T 序列的类型
 * @param s 序列
 * @returns 序列的字典序最小循环移位的 0 索引位置
 */
template <typename T>
size_t duval(const T& s) {
    size_t n = s.size();  // 获取序列的长度
    size_t i = 0, ans = 0;  // 初始化 i 和 ans 为 0
    while (i < n) {  // 遍历序列
        ans = i;  // 设置当前最小循环移位的位置
        size_t j = i + 1, k = i;
        while (j < (n + n) && s[j % n] >= s[k % n]) {  // 比较序列中的后缀
            if (s[k % n] < s[j % n]) {  // 如果当前字符小于下一个字符，更新 k
                k = i;
            } else {
                k++;  // 否则，k 向后移动
            }
            j++;  // 移动 j
        }
        while (i <= k) {  // 更新 i 的值
            i += j - k;  // 通过 j 和 k 的差值调整 i
        }
    }
    return ans;  // 返回字典序最小的循环移位的索引
}

}  // namespace string

/**
 * @brief 自测函数实现
 * 返回 void
 */
static void test() {
    using namespace string;

    // 测试 1
    std::string s1 = "abcab";
    assert(duval(s1) == 3);  // 检查最小循环移位位置是否为 3

    // 测试 2
    std::string s2 = "011100";
    assert(duval(s2) == 4);  // 检查最小循环移位位置是否为 4

    // 测试 3
    std::vector<int> v = {5, 2, 1, 3, 4};
    assert(duval(v) == 2);  // 检查最小循环移位位置是否为 2

    // 测试 4
    std::array<int, 5> a = {1, 2, 3, 4, 5};
    assert(duval(a) == 0);  // 检查最小循环移位位置是否为 0

    // 测试 5
    std::deque<char> d = {'a', 'z', 'c', 'a', 'b'};
    assert(duval(d) == 3);  // 检查最小循环移位位置是否为 3

    // 测试 6
    std::string s3;
    assert(duval(s3) == 0);  // 空字符串，最小循环移位位置为 0

    // 测试 7
    std::vector<int> v2 = {5, 2, 1, 3, -4};
    assert(duval(v2) == 4);  // 检查最小循环移位位置是否为 4

    std::cout << "所有测试都通过了!" << std::endl;  // 所有测试通过后的输出
}

/**
 * @brief 主函数
 * @returns 0 程序退出时返回 0
 */
int main() {
    test();  // 运行自测函数
    return 0;
}
