
// 3181. 执行操作可获得的最大总奖励 II

// 给你一个整数数组 rewardValues，长度为 n，代表奖励的值。

// 最初，你的总奖励 x 为 0，所有下标都是 未标记 的。你可以执行以下操作 任意次 ：

// 从区间 [0, n - 1] 中选择一个 未标记 的下标 i。
// 如果 rewardValues[i] 大于 你当前的总奖励 x，则将 rewardValues[i] 加到 x 上（即 x = x + rewardValues[i]），并 标记 下标 i。
// 以整数形式返回执行最优操作能够获得的 最大 总奖励。

//思路
#include <iostream>
#include <vector>

class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        int n = rewardValues.size();
        sort(rewardValues.begin(), rewardValues.end());
        if(n >= 2 && rewardValues[n-2] == rewardValues[n-1]-1){
            return rewardValues[n-2] * 2 + 1;
        }
        bitset<100000> dp0,dp1;
        dp0[0] = 1;
        for(int i =0, j = 0;i < n;i++){
            while(j < rewardValues[i]){
                dp1[j] = dp0[j];
                j++;
            }
            dp0 |= (dp1 << rewardValues[i]);
        }
        int ans = 0;
        for(int i = 0; i < 100000;i++){
            if(dp0[i]){
                ans = i;
            }
        }
        return ans;
    }
};
