// 最长公共子序列 - 动态规划
#include <iostream>
using namespace std;

/**
 * @brief 递归打印 LCS 的字符
 * @param trace 用于追踪路径的数组
 * @param m 字符串 a 的长度
 * @param n 字符串 b 的长度
 * @param a 字符串 a
 */
void Print(int trace[20][20], int m, int n, string a) {
    // 如果任一字符串的长度为 0，则返回
    if (m == 0 || n == 0) {
        return;
    }
    // 根据追踪数组决定路径
    if (trace[m][n] == 1) {
        Print(trace, m - 1, n - 1, a);  // 对角线方向
        cout << a[m - 1];  // 打印公共字符
    } else if (trace[m][n] == 2) {
        Print(trace, m - 1, n, a);  // 向上方向
    } else if (trace[m][n] == 3) {
        Print(trace, m, n - 1, a);  // 向左方向
    }
}

/**
 * @brief 计算字符串 a 和 b 的最长公共子序列长度
 * @param a 字符串 a
 * @param b 字符串 b
 * @return 返回最长公共子序列的长度
 */
int lcs(string a, string b) {
    int m = a.length(), n = b.length();
    int res[m + 1][n + 1];  // 存储 LCS 的长度
    int trace[20][20];      // 追踪路径的数组

    // 初始化数组
    for (int i = 0; i < m + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            res[i][j] = 0;  // LCS 的长度初始化为 0
            trace[i][j] = 0;  // 追踪数组初始化为 0
        }
    }

    // 填充 LCS 长度和追踪数组
    for (int i = 0; i < m + 1; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            // 边界条件
            if (i == 0 || j == 0) {
                res[i][j] = 0;  // 边界上的 LCS 长度为 0
                trace[i][j] = 0;  // 追踪数组不更新
            }
            // 如果字符相等，更新 LCS 长度和追踪数组
            else if (a[i - 1] == b[j - 1]) {
                res[i][j] = 1 + res[i - 1][j - 1];  // 递增 LCS 长度
                trace[i][j] = 1;  // 追踪对角线方向
            } else {
                // 根据上下左右的 LCS 长度选择最大值
                if (res[i - 1][j] > res[i][j - 1]) {
                    res[i][j] = res[i - 1][j];  // 从上方取得值
                    trace[i][j] = 2;  // 追踪上方
                } else {
                    res[i][j] = res[i][j - 1];  // 从左方取得值
                    trace[i][j] = 3;  // 追踪左方
                }
            }
        }
    }
    Print(trace, m, n, a);  // 打印 LCS
    return res[m][n];  // 返回 LCS 的长度
}

/**
 * @brief 主函数
 * @return 0 表示正常退出
 */
int main() {
    string a, b;  // 声明字符串 a 和 b
    cin >> a >> b;  // 输入两个字符串
    cout << lcs(a, b);  // 调用 lcs 函数并输出结果
    return 0;  // 正常退出
}
