/* 给定两个字符串 str1 和 str2，以及以下可以对 str1 执行的操作：
 * 找出将 'str1' 转换为 'str2' 所需的最小编辑次数。
 * a. 插入
 * b. 删除
 * c. 替换
 * 以上所有操作的成本相同。
 */

#include <iostream>
#include <string>
using namespace std;

// 函数返回三个值中的最小值
int min(int x, int y, int z) { return min(min(x, y), z); }

/* 一个递归的 C++ 程序，用于找到将 str1 转换为 str2 所需的最小操作数。
 * 时间复杂度：O(3^m)
 */
int editDist(string str1, string str2, int m, int n) {
    // 如果 str1 为空，则将 str2 的所有字符插入到 str1 中
    if (m == 0)
        return n;
    // 如果 str2 为空，则从 str1 中删除所有字符
    if (n == 0)
        return m;

    // 如果最后一个字符相同，则继续比较剩余的字符
    if (str1[m - 1] == str2[n - 1])
        return editDist(str1, str2, m - 1, n - 1);

    // 如果最后一个字符不同，则有三种可能的操作：
    // a. 插入 b. 删除 c. 替换
    // 取这三种操作中的最小值，并继续递归处理剩余的字符
    return 1 + min(editDist(str1, str2, m, n - 1),   // 插入
                   editDist(str1, str2, m - 1, n),   // 删除
                   editDist(str1, str2, m - 1, n - 1));  // 替换
}

/* 一个基于动态规划的程序
 * 时间复杂度：O(m x n)
 */
int editDistDP(string str1, string str2, int m, int n) {
    // 创建一个表来存储子问题的解
    int dp[m + 1][n + 1];

    // 使用自底向上的方式填充 dp 表
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // 如果 str1 为空，则需要插入所有 str2 的字符
            if (i == 0)
                dp[i][j] = j;

            // 如果 str2 为空，则需要删除所有 str1 的字符
            else if (j == 0)
                dp[i][j] = i;

            // 如果字符相同，则递归处理剩余字符
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];

            // 否则，取插入、删除和替换操作中的最小值，加上 1
            else
                dp[i][j] = 1 + min(dp[i][j - 1],     // 插入
                                   dp[i - 1][j],     // 删除
                                   dp[i - 1][j - 1]  // 替换
                               );
        }
    }

    return dp[m][n];
}

int main() {
    string str1 = "sunday";
    string str2 = "saturday";

    // 输出递归方法的结果
    cout << editDist(str1, str2, str1.length(), str2.length()) << endl;

    // 输出动态规划方法的结果
    cout << editDistDP(str1, str2, str1.length(), str2.length()) << endl;

    return 0;
}
