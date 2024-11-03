/* 函数用于计算在最坏情况下，当有 n 个鸡蛋和 k 层楼时，
 * 需要的最少尝试次数。
 */

#include <climits>
#include <iostream>
using namespace std;

// 函数 eggDrop 计算最坏情况下的最少尝试次数
int eggDrop(int n, int k) {
    // eggFloor[i][j] 表示使用 i 个鸡蛋和 j 层楼时所需的最小尝试次数
    int eggFloor[n + 1][k + 1];
    int result;

    // 初始化 n 个鸡蛋和 1 层楼以及 0 层楼的情况
    for (int i = 1; i <= n; i++) {
        eggFloor[i][1] = 1;  // 有 n 个鸡蛋和 1 层楼时，尝试次数为 1
        eggFloor[i][0] = 0;  // 有 n 个鸡蛋和 0 层楼时，尝试次数为 0
    }

    // 初始化当只有 1 个鸡蛋时的情况
    for (int j = 1; j <= k; j++) {
        eggFloor[1][j] = j;  // 只有 1 个鸡蛋时，需要从第 1 层到第 j 层逐层尝试
    }

    // 计算当有更多鸡蛋和楼层时的情况
    for (int i = 2; i <= n; i++) {        // 遍历鸡蛋数量
        for (int j = 2; j <= k; j++) {    // 遍历楼层数量
            eggFloor[i][j] = INT_MAX;     // 初始化当前状态的尝试次数为最大值
            for (int x = 1; x <= j; x++) {
                // 尝试从第 x 层扔鸡蛋，并计算最坏情况下的尝试次数：
                // 如果鸡蛋碎了，检查 x 楼以下 (i-1 个鸡蛋和 x-1 层楼)
                // 如果鸡蛋没碎，检查 x 楼以上 (i 个鸡蛋和 j-x 层楼)
                result = 1 + max(eggFloor[i - 1][x - 1], eggFloor[i][j - x]);

                // 选择最少的尝试次数
                if (result < eggFloor[i][j])
                    eggFloor[i][j] = result;
            }
        }
    }

    return eggFloor[n][k];  // 返回最少尝试次数
}

int main() {
    int n, k;
    cout << "请输入鸡蛋数量和楼层数：";
    cin >> n >> k;
    cout << "在最坏情况下最少的尝试次数：" << eggDrop(n, k) << endl;
    return 0;
}
