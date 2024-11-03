/**
 * @file
 * @brief 使用动态规划实现的 [最小编辑距离](https://en.wikipedia.org/wiki/Edit_distance)
 *
 * @details
 *
 * 给定两个字符串 str1 和 str2，我们需要计算将 str1 转换为 str2 所需的最少操作次数（插入、删除、替换）。
 *
 * ### 算法
 *
 * 我们将使用朴素递归来解决此问题。但由于我们采用动态规划解决方案，因此我们将使用 DP 数组来存储所有子问题的解决方案，以便我们不必重复递归。为了求解该问题，我们可以从字符串的右侧或左侧遍历所有字符。假设我们从右侧开始遍历，那么对于每对正在遍历的字符，有两种可能性：
 * 1. 如果两个字符串的最后一个字符相同，则忽略这些字符并获取剩余字符串的计数。
 *    这样，我们可以在 DP 数组中获得长度为 m-1 和 n-1 的解决方案。
 *
 * 2. 否则（如果最后一个字符不同），我们将考虑在第一个字符串的最后一个字符上进行所有三种操作（插入、删除、替换），并计算这三种操作的最小成本，并在 DP 数组中取最小值。
 *    对于插入：递归 m 和 n-1
 *    对于删除：递归 m-1 和 n
 *    对于替换：递归 m-1 和 n-1
 *
 * @author [Nirjas Jakilim](github.com/nirzak)
 */

#include <cassert>     /// 用于 assert
#include <iostream>    /// 用于输入输出操作
#include <vector>      /// 用于 std::vector

/**
 * @namespace dynamic_programming
 * @brief 动态规划算法
 */

namespace dynamic_programming {

/**
 * @namespace Minimum Edit Distance
 * @brief 实现 [最小编辑距离](https://en.wikipedia.org/wiki/Edit_distance) 算法
 */

namespace minimum_edit_distance {

/**
 * @brief 获取三个操作（插入、替换和删除）的成本并返回其中的最小值。
 * @param x 插入操作的最小成本
 * @param y 替换操作的最小成本
 * @param z 删除操作的最小成本
 * @returns x 如果 `x` 是最小值
 * @returns y 如果 `y` 是最小值
 * @returns z 如果 `z` 是最小值
 */
uint64_t min(uint64_t x, uint64_t y, uint64_t z) {
  if (x <= y && x <= z) {
    return x; /// 如果 x 是最小值，则返回 x
  }
  if (y <= x && y <= z) {
    return y; /// 如果 y 是最小值，则返回 y
  }
  else {
    return z; /// 如果 z 是最小值，则返回 z
  }
}

/**
 * @brief 计算并存储所有子问题的结果，以便我们不必再次递归计算特定操作的最小成本。
 * @param dp 存储计算出的最小成本的向量
 * @param str1 传入第一个字符串
 * @param str2 传入第二个字符串
 * @param m str1 的长度
 * @param n str2 的长度
 * @returns dp[m][n] 将 str1 转换为 str2 所需的最小操作成本
 */
uint64_t editDistDP(std::string str1, std::string str2, uint64_t m, uint64_t n) {
  /// 创建一个表来存储子问题的结果
  std::vector<std::vector<uint64_t>> dp(m + 1, std::vector<uint64_t>(n + 1)); /// 创建二维向量 dp 来存储子问题的结果

  /// 以自底向上的方式填充 dp[][] 
  for (uint64_t i = 0; i <= m; i++) {
    for (uint64_t j = 0; j <= n; j++) {
      /// 如果第一个字符串为空，唯一的选择是插入第二个字符串的所有字符
      if (i == 0) {
        dp[i][j] = j; /// 最小操作 = j
      }

      /// 如果第二个字符串为空，唯一的选择是删除第一个字符串的所有字符
      else if (j == 0) {
        dp[i][j] = i; /// 最小操作 = i
      }

      /// 如果最后一个字符相同，则忽略最后一个字符并递归处理剩余字符串
      else if (str1[i - 1] == str2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      }

      /// 如果最后一个字符不同，考虑所有可能性并找到最小值
      else {
        dp[i][j] = 1 + min(dp[i][j - 1],      // 插入
                           dp[i - 1][j],      // 删除
                           dp[i - 1][j - 1]); // 替换
      }
    }
  }

  return dp[m][n]; /// 返回将 str1 转换为 str2 所需的最小操作成本
}
}  // namespace minimum_edit_distance
}  // namespace dynamic_programming

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
  // 第一个测试
  std::string str1 = "INTENTION"; // 第一个字符串的示例输入
  std::string str2 = "EXECUTION"; // 第二个字符串的示例输入
  uint64_t expected_output1 = 5; // 期望的最小成本
  uint64_t output1 = dynamic_programming::minimum_edit_distance::editDistDP(
      str1, str2, str1.length(), str2.length()); // 调用 editDistDP 函数并将结果存储在 output1 中
  assert(output1 == expected_output1); // 比较输出与期望输出
  std::cout << "所需的最小操作数: " << output1
            << std::endl;

  // 第二个测试
  std::string str3 = "SATURDAY";
  std::string str4 = "SUNDAY";
  uint64_t expected_output2 = 3;
  uint64_t output2 = dynamic_programming::minimum_edit_distance::editDistDP(
      str3, str4, str3.length(), str4.length());
  assert(output2 == expected_output2);
  std::cout << "所需的最小操作数: " << output2
            << std::endl;
}

/**
 * @brief 主函数
 * @param argc 命令行参数计数（忽略）
 * @param argv 命令行参数数组（忽略）
 * @returns 0 正常退出
 */
int main(int argc, char *argv[]) {
  test();  // 运行自测实现
  return 0; // 正常退出
}
