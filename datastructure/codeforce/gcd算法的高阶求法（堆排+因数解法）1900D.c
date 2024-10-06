/*
    题目：给你一个数组 f(a,b,c)三元组，用最小的两个求gcd。然后相加，返回结果。
*/

//思路：从小到大排序，堆排，快排都可以
//统计每个因数的贡献值
//求和
#include<stdio.h>
long long int h[100005], l;
long long int comp_h(long long int a, long long int b)
{
	if (h[a] > h[b])
		return 1;
	else
		return -1;
}
void swap_h(long long int a, long long int b)
{
	long long int f = h[a];
	h[a] = h[b];
	h[b] = f;
	return;
}
void push(long long int ne)
{
	h[l] = ne;
	long long int p = l;
	l++;
	for (; p > 0; p = (p - 1) / 2)
		if (comp_h((p - 1) / 2, p) > 0)
			swap_h((p - 1) / 2, p);
	return;
}
long long int pop()
{
	l--;
	swap_h(0, l);
	long long int p = 0;
	for (;;)
	{
		if (2 * p + 2 < l)
		{
			if (comp_h(2 * p + 1, 2 * p + 2) > 0)
			{
				if (comp_h(p, 2 * p + 2) > 0)
					swap_h(p, 2 * p + 2);
				p = 2 * p + 2;
			}
			else
			{
				if (comp_h(p, 2 * p + 1) > 0)
					swap_h(p, 2 * p + 1);
				p = 2 * p + 1;
			}
		}
		else if (2 * p + 1 < l)
		{
			if (comp_h(p, 2 * p + 1) > 0)
				swap_h(p, 2 * p + 1);
			p = 2 * p + 1;
		}
		else
			break;
	}
	return h[l];
}
long long int a[100005];
long long int cnt1[100005];
long long int dp[100005];
void solve()
{
	long long int n;
	scanf("%lld", &n);
	long long int i, j;
	for (i = 0; i < n; i++)
		scanf("%lld", &a[i]);
	l = 0;
	for (i = 0; i < n; i++)
		push(a[i]);
	for (i = 0; i < n; i++)
		a[i] = pop();
	for (i = 0; i < 100005; i++)
		cnt1[i] = dp[i] = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 1; j * j <= a[i]; j++)
		{
			if (a[i] % j > 0)
				continue;
			dp[j] += cnt1[j] * (n - i - 1);
			if (j * j < a[i])
			{
				j = a[i] / j;
				dp[j] += cnt1[j] * (n - i - 1);
				j = a[i] / j;
			}
		}
		for (j = 1; j * j <= a[i]; j++)
		{
			if (a[i] % j > 0)
				continue;
			cnt1[j]++;
			if (j * j < a[i])
				cnt1[a[i] / j]++;
		}
	}
	for (i = 100004; i > 0; i--)
	{
		for (j = 2 * i; j < 100005; j += i)
			dp[i] -= dp[j];
	}
	long long int ans = 0;
	for (i = 0; i < 100005; i++)
		ans += i * dp[i];
	printf("%lld\n", ans);
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