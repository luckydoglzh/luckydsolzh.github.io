//题目描述
//n个字符串数组，每个数组长度为m。 拼成Narek，得5分，剩下没用到的元素每个n,a,r,e,k扣1分，可以选或者不选字符串。求最大得分
//思路：贪心算法，每次过一个字符串，算一下得分率值不值，并保存起来。
#include<stdio.h>
char s[1003][1003];
int dp[2][5];
int in(char c)
{
	char t[8] = "narek";
	int i;
	for (i = 0; i < 5; i++)
		if (c == t[i])
			return 1;
	return -1;
}
void solve()
{
	int n, m;
	scanf("%d %d", &n, &m);
	int i, j, k;
	for (i = 0; i < n; i++)
		scanf("%s", s[i]);
	for (i = 1; i < 5; i++)
		dp[0][i] = dp[1][i] = -1e9;
	dp[0][0] = dp[1][0] = 0;
	char t[8] = "narek";
	long long int v, next;
	long long int ans = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < 5; j++)
		{
			next = j;
			v = dp[0][j];
			for (k = 0; k < m; k++)
			{
				if (in(s[i][k]) < 0)
					continue;
				if (s[i][k] == t[next])
				{
					v++;
					next = (next + 1) % 5;
				}
				else
					v--;
			}
			if (dp[1][next] < v)
			{
				dp[1][next] = v;
				if (ans < dp[1][next] - 2 * next)
					ans = dp[1][next] - 2 * next;
			}
		}
		for (j = 0; j < 5; j++)
			dp[0][j] = dp[1][j];
	}
	printf("%d\n",ans);
	return;
}
int main()
{
	int t;
	scanf("%d", &t);
	for (; t > 0; t--)
		solve();
	return 0;
}
