/**
 * @file
 * @brief 程序查找字符串的 [最长回文子序列](https://www.geeksforgeeks.org/longest-palindromic-subsequence-dp-12/)
 *
 * @details
 * [回文](https://en.wikipedia.org/wiki/Palindrome) 字符串是前后读起来相同的字符序列。
 * [子序列](https://en.wikipedia.org/wiki/Subsequence) 是可以通过删除某些或没有元素而不改变剩余元素顺序而从另一个序列派生出的序列。
 *
 * @author [Anjali Jha](https://github.com/anjali1903)
 */

#include <cassert>  /// 用于 assert
#include <string>   /// 用于 std::string
#include <vector>   /// 用于 std::vector

/**
 * @namespace
 * @brief 动态规划算法
 */
namespace dynamic_programming {
/**
 * @brief 函数返回字符串的最长回文子序列
 * @param a 要查找最长回文子序列的字符串
 * @returns 字符串的最长回文子序列
 */
std::string lps(const std::string& a) {
    const auto b = std::string(a.rbegin(), a.rend());  // 获取字符串 a 的反向字符串
    const auto m = a.length();  // 字符串 a 的长度
    using ind_type = std::string::size_type;  // 定义索引类型
    std::vector<std::vector<ind_type> > res(m + 1,
                                            std::vector<ind_type>(m + 1));  // 2D 数组用于存储结果

    // 计算最长回文子序列的长度，并以自底向上的方式存储在 2D 数组中
    for (ind_type i = 0; i <= m; i++) {
        for (ind_type j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                res[i][j] = 0;  // 如果任一索引为 0，长度为 0
            } else if (a[i - 1] == b[j - 1]) {
                res[i][j] = res[i - 1][j - 1] + 1;  // 当前字符相同，增加长度
            } else {
                res[i][j] = std::max(res[i - 1][j], res[i][j - 1]);  // 取最大值
            }
        }
    }
    // 最长回文子序列的长度
    auto idx = res[m][m];
    // 创建长度为 idx 的空字符串
    std::string ans(idx, '\0');
    ind_type i = m, j = m;

    // 从右下角开始，逐个存储字符到 ans 中
    while (i > 0 && j > 0) {
        // 如果当前字符相同，则为 ans 的一部分
        if (a[i - 1] == b[j - 1]) {
            ans[idx - 1] = a[i - 1];  // 存储字符
            i--;
            j--;
            idx--;
        }
        // 如果不相同，选择较大的方向
        else if (res[i - 1][j] > res[i][j - 1]) {
            i--;  // 移动到上方
        } else {
            j--;  // 移动到左侧
        }
    }

    return ans;  // 返回最长回文子序列
}
}  // namespace dynamic_programming

/**
 * @brief 自我测试实现
 * @returns void
 */
static void test() {
    assert(dynamic_programming::lps("radar") == "radar");  // 测试案例
    assert(dynamic_programming::lps("abbcbaa") == "abcba"); // 测试案例
    assert(dynamic_programming::lps("bbbab") == "bbbb");    // 测试案例
    assert(dynamic_programming::lps("") == "");             // 测试空字符串
}

/**
 * @brief 主函数
 * @returns 0 正常退出
 */
int main() {
    test();  // 执行测试
    return 0;  // 正常退出
}
