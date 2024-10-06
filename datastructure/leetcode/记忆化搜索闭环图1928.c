/*
一个国家有 n 个城市，城市编号为 0 到 n - 1 ，题目保证 所有城市 都由双向道路 连接在一起 。道路由二维整数数组 edges 表示，其中 edges[i] = [xi, yi, timei] 表示城市 xi 和 yi 之间有一条双向道路，耗费时间为 timei 分钟。两个城市之间可能会有多条耗费时间不同的道路，但是不会有道路两头连接着同一座城市。

每次经过一个城市时，你需要付通行费。通行费用一个长度为 n 且下标从 0 开始的整数数组 passingFees 表示，其中 passingFees[j] 是你经过城市 j 需要支付的费用。

一开始，你在城市 0 ，你想要在 maxTime 分钟以内 （包含 maxTime 分钟）到达城市 n - 1 。旅行的 费用 为你经过的所有城市 通行费之和 （包括 起点和终点城市的通行费）。

给你 maxTime，edges 和 passingFees ，请你返回完成旅行的 最小费用 ，如果无法在 maxTime 分钟以内完成旅行，请你返回 -1 。
*/
//思路很简单  dp[i][j]表示花费i时间到j位置需要花费的最小钱
//dp[0][0]表示参观位置0 花费多少钱
//遍历maxtime，然后迭代dp[i][j]的值即可
int minCost(int maxTime, int** edges, int edgesSize, int* edgesColSize, int* passingFees, int passingFeesSize) {
    int ans = INT_MAX;
    int n = passingFeesSize;
    int dp[maxTime+1][n+1];
    for(int i = 0; i < maxTime+1;i++){
        for(int j = 0; j < n+1;j++){
            dp[i][j] = INT_MAX;
        }
    }
    dp[0][0] = passingFees[0];
    for(int i = 1;i <= maxTime;i++){
        for(int j = 0; j < edgesSize;j++){
            int start = edges[j][0];
            int end = edges[j][1];
            int cost = edges[j][2];
            if(i >= cost){
                if(dp[i - cost][start] != INT_MAX){
                    dp[i][end] = fmin(dp[i][end] , dp[i-cost][start] + passingFees[end]);
                }
                if(dp[i - cost][end] != INT_MAX){
                    dp[i][start] = fmin(dp[i][start] , dp[i-cost][end] + passingFees[start]);
                }
            }
            
        }
    }
    for(int i = 1;i <= maxTime;i++){
        ans = fmin(ans , dp[i][n-1]);
    }
    return ans == INT_MAX?-1:ans;
}