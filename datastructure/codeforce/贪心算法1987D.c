// Alice和Bob在玩轮流吃蛋糕的游戏，每个蛋糕有美味值，Alice只能吃美味值比之前高的蛋糕，Bob则随意。
// Alice想吃更多的蛋糕，但Bob不想Alice吃那么多蛋糕。
// 按照两个人共同的想法，求Alice理论能吃最多的蛋糕数量
//思路 贪心算法
//遍历美味值。 Bob阻拦的核心思想就是把size最小的蛋糕全他妈吃了
#include <stdio.h>
#include <stdlib.h>
 
// 解决每个测试用例的函数
void solve() {
    int n;
    scanf("%d", &n);  // 读取蛋糕的数量
    
    // 动态分配一个数组 cnt，用来统计每个美味值的出现次数
    int *cnt = (int *)calloc(n + 1, sizeof(int)); 
    
    // 读取每个蛋糕的美味值并统计其出现次数
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a); 
        cnt[a]++;  // 对应的美味值次数加1
    }
    
    // 动态分配一个队列 q，用来存放每种美味值的蛋糕数量加1（用于后续调整）
    int *q = (int *)malloc((n + 1) * sizeof(int)); 
    int q_size = 0;  // 记录当前队列的大小
    
    int sum = 0, valid = 0;  // sum 记录总的蛋糕数量，valid 记录不同的美味值数目
    for (int i = 0; i <= n; i++) {
        if (cnt[i]) {  // 如果美味值 i 有对应的蛋糕
            valid++;  // 统计有多少种不同的美味值
            sum += cnt[i] + 1;  // 累加蛋糕的数量（+1 是为了符合后续处理逻辑）
            q[q_size++] = cnt[i] + 1;  // 将每个美味值的蛋糕数量 +1 放入队列
            
            // 如果当前累加的蛋糕总数超过了不同美味值的数量（即蛋糕过多）
            while (sum > valid) {
                // 寻找队列中最大的蛋糕数量（通过遍历）
                int max_idx = 0;
                for (int j = 1; j < q_size; j++) {
                    if (q[j] > q[max_idx]) {
                        max_idx = j;  // 找到当前最大的蛋糕数量所在的索引
                    }
                }
                // 减去最大数量的蛋糕，并调整队列
                sum -= q[max_idx];  // 减去最大值
                q[max_idx] = q[--q_size];  // 将队列中最大值替换为队列末尾的值，并缩小队列大小
            }
        }
    }
    
    // 输出最终答案：有效的美味值数量减去队列的大小，表示 Alice 吃掉的蛋糕数量
    printf("%d\n", valid - q_size);
    
    // 释放动态分配的内存
    free(cnt);
    free(q);
}
 
int main() {
    int t;
    scanf("%d", &t);  // 读取测试用例的数量
    while (t--) solve();  // 逐个测试用例解决
    return 0;
}