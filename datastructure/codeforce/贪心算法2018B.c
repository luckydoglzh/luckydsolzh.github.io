
/*

有 n 个城市排成一行，从左到右依次编号为 1, 2, ..., n。

在第 1 个时间点，你征服了一个城市，称之为起始城市。 在第 2, 3, ..., n 个时间点，你可以选择征服当前已征服城市的相邻城市之一。 如果对每一个 
i，你在不晚于a[i]时间点征服了城市 i，那么你就算赢了。
是否存在一个获胜策略取决于你选择的起始城市。你需要计算有多少个起始城市能够让你赢得游戏。
*/
/*
3
6
6 3 3 3 5 5
6
5 6 4 1 4 5
9
8 6 4 2 1 3 5 7 9

*/
#include <stdio.h>
 
#define N	200000
 
int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }
 
int main() {
	int t;
 
	scanf("%d", &t);
	while (t--) {
		static int aa[N];
		int n, i, j, lower, upper;
 
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			scanf("%d", &aa[i]);
        i = 0;
        j = n - 1;
        while(i <= j){
            if(aa[i] >= j - i + 1){
                i++;
            }else if(aa[j] >= j-i+1){
                j--;
            }else{
                break;
            }
        }
        if(i<=j){
            printf("0\n");
        }else{
            int low = 0;
            int high = n- 1;
            for(int m = 0; m < n;m++){
                low = max(low, m - aa[m] + 1);
                high = min(high, m + aa[m] - 1);
            }
            int sum = high - low + 1;
            printf("%d\n", sum);
        }
	}
	return 0;
}