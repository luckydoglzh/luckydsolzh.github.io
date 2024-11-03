#include <climits>  // 用于 INT_MAX
#include <iostream> // 用于输入输出操作
using namespace std;

#define MAX 10  // 最大矩阵数

// dp 表用于存储已计算子问题的解决方案
int dp[MAX][MAX];

// 函数用于找到给定矩阵序列的最有效乘法方式
int MatrixChainMultiplication(int dim[], int i, int j) {
    // 基本情况：只有一个矩阵
    if (j <= i + 1)
        return 0;

    // 存储计算矩阵 M[i+1]...M[j] = M[i..j] 所需的最小标量乘法次数（即成本）
    int min = INT_MAX;

    // 如果 dp[i][j] 尚未计算（进行计算）
    if (dp[i][j] == 0) {
        // 在可能的每个拆分位置上取最小值

        for (int k = i + 1; k <= j - 1; k++) {
            // 对 M[i+1]..M[k] 递归计算以获取一个 i x k 矩阵
            int cost = MatrixChainMultiplication(dim, i, k);

            // 对 M[k+1]..M[j] 递归计算以获取一个 k x j 矩阵
            cost += MatrixChainMultiplication(dim, k, j);

            // 计算乘法两个矩阵（i x k）和（k x j）的成本
            cost += dim[i] * dim[k] * dim[j];

            // 如果成本小于当前最小值，则更新最小值
            if (cost < min)
                min = cost;  // 存储最小成本
        }
        dp[i][j] = min;  // 将计算结果存储在 dp 表中
    }

    // 返回乘法 M[j+1]..M[j] 的最小成本
    return dp[i][j];
}

// 主函数
int main() {
    // 矩阵 i 的维度为 dim[i-1] & dim[i]，对于 i=1..n
    // 输入为 10 x 30 矩阵、30 x 5 矩阵、5 x 60 矩阵
    int dim[] = {10, 30, 5, 60};
    int n = sizeof(dim) / sizeof(dim[0]);

    // 函数调用：MatrixChainMultiplications(维度数组, 起始, 结束);

    cout << "最小成本为 " << MatrixChainMultiplication(dim, 0, n - 1)
         << "\n";  // 输出最小成本

    return 0;  // 正常退出
}
