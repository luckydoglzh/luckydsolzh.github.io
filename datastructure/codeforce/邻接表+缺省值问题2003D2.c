/*
    第i个序列长度li   a1,a2....al
    一共有n个序列
    一开始有一个非负整数x。 每次操作第i序列，x = mex(x, a1,a2....ai);
    目的是操作任意次，找到x的最大值
    初始值为k，f(k) = 目的结果
    返回从0，1，...k的f(k)求和
*/
//思路
// 1，找到每个序列的最小两个缺省值，做成邻接表
// 2，遍历邻接表用dp[i]表示，输入i返回的最大值
// 3，当输入k大于邻接表最大值时，返回k
#include <stdio.h>
#include <stdlib.h>

#define N 200002 // 定义常量N，表示最大可能的元素数

// 求最大值的宏定义
int max(int a, int b) { return a > b ? a : b; }

// 邻接表的数组，用于存储图的边
int *ej[N]; // ej[i]是与节点i相连的节点数组
int eo[N]; // eo[i]是节点i的边数

// 向邻接表中添加边
void append(int i, int j) {
    int o = eo[i]++; // 获取当前节点i的边数并自增

    // 如果是第一次添加边，分配内存
    if (o == 0)
        ej[i] = (int *) malloc(2 * sizeof *ej[i]);
    // 如果边数达到了当前容量的上限，重新分配内存
    else if (o >= 2 && (o & o - 1) == 0)
        ej[i] = (int *) realloc(ej[i], o * 2 * sizeof *ej[i]);
    
    ej[i][o] = j; // 将新边j添加到节点i的邻接表中
}

int main() {
    int t; // 测试用例数量

    scanf("%d", &t); // 读取测试用例数量
    while (t--) { // 遍历每个测试用例
        static int ii[N], dp[N]; // ii数组存储输入的数字，dp数组用于动态规划
        static char used[N]; // used数组用于标记数字是否被使用
        int n = 0; // 记录当前最大数字的大小
        int m, l, k, h, i, j, o, x; // 声明多个变量
        long long ans; // 最终结果

        // 读取m和k
        scanf("%d%d", &m, &k);
        // 处理每个序列
        while (m--) {
            scanf("%d", &l); // 读取序列的长度
            for (h = 0; h < l; h++)
                scanf("%d", &ii[h]); // 读取序列元素
            // 标记当前序列中出现的数字
            for (h = 0; h < l; h++)
                if (ii[h] < N)
                    used[ii[h]] = 1;

            // 找到第一个不在used中的最小数字i
            i = 0;
            while (used[i])
                i++;
            // 找到第二个不在used中的最小数字j
            j = i + 1;
            while (used[j])
                j++;
            n = max(n, j + 1); // 更新最大数字的大小
            append(i, j); // 将i和j之间的边添加到邻接表中
            // 清除used标记
            for (h = 0; h < l; h++)
                if (ii[h] < N)
                    used[ii[h]] = 0;
        }

        x = 0; // x用于存储最大的dp值
        // 从n-1到0遍历，更新dp数组
        //遍历每个边  dp[i]表示值i能变成的最大值 很妙！！
        for (i = n - 1; i >= 0; i--) {
            dp[i] = i; // 初始化dp[i]为i
            // 遍历与i相连的节点，更新dp[i]
            for (o = eo[i]; o--; ) {
                j = ej[i][o];
                dp[i] = max(dp[i], dp[j]); // 更新dp[i]为与j连接的最大dp值
            }
            // 根据边数更新x
            if (eo[i] == 1)
                x = max(x, i);
            else if (eo[i] >= 2)
                x = max(x, dp[i]);
        }

        ans = 0; // 初始化答案
        // 根据k的值计算答案
        if (k >= n)
            ans += (long long) (n + k) * (k - n + 1) / 2, k = n - 1; // k大于等于n的情况
        for (i = 0; i <= k; i++)
            ans += max(dp[i], x); // 更新答案

        printf("%lld\n", ans); // 输出答案

        // 释放邻接表分配的内存
        for (i = 0; i < n; i++)
            if (ej[i])
                free(ej[i]), ej[i] = NULL, eo[i] = 0; // 释放内存并重置边数
    }
    return 0; // 返回0，结束程序
}
