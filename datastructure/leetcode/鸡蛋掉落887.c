// 给你 k 枚相同的鸡蛋，并可以使用一栋从第 1 层到第 n 层共有 n 层楼的建筑。

// 已知存在楼层 f ，满足 0 <= f <= n ，任何从 高于 f 的楼层落下的鸡蛋都会碎，从 f 楼层或比它低的楼层落下的鸡蛋都不会破。

// 每次操作，你可以取一枚没有碎的鸡蛋并把它从任一楼层 x 扔下（满足 1 <= x <= n）。如果鸡蛋碎了，你就不能再次使用它。如果某枚鸡蛋扔下后没有摔碎，则可以在之后的操作中 重复使用 这枚鸡蛋。

// 请你计算并返回要确定 f 确切的值 的 最小操作次数 是多少？

int superEggDrop(int k, int n) {
    //建立dp数组  dp[i][j]前n层，存在j个鸡蛋最大操作次数
    int dp[k+1][n+1];
    //初始化dp数组
    for(int i = 0; i <= k;i++){
        for(int j = 0; j <= n ;j++){
            if(j == 0){
                dp[i][j] = 0;
            }else if(i == 1){
                dp[i][j] = j;
            }else{
                dp[i][j] = INT_MAX;
            }
        }
    }
    
    //dp[i][j] = fmax(dp[i-1][j-1], dp[i][i - 当前层数])
    //本质上分为摔烂/没摔烂两种情况讨论即可
    //用二分法降低时间复杂度
    for(int i = 2; i<=k;i++){
        for(int j = 1;j <= n;j++){
            int left = 1;
            int right = j;
            while(left <= right){
                int mid = (left + right)/2;
                int die = dp[i-1][mid-1];
                int nodie = dp[i][j-mid];
                if(die > nodie){
                    right = mid - 1;
                    dp[i][j] = fmin(dp[i][j], die+1);
                }else{
                    left = mid+1;
                    dp[i][j] = fmin(dp[i][j], nodie+1);
                }
            }
        }
    }
    return dp[k][n];
}