/*
有 n 个城市排成一行，从左到右依次编号为 1, 2, ..., n。

在第 1 个时间点，你征服了一个城市，称之为起始城市。 在第 2, 3, ..., n 个时间点，你可以选择征服当前已征服城市的相邻城市之一。 如果对每一个 i，你在不晚于 a[i]时间点征服了城市 i，那么你就算赢了。

是否存在一个获胜策略取决于你选择的起始城市。你需要计算有多少个起始城市能够让你赢得游戏。*/
#include <stdio.h>
#define M 200005
#define X 1000000000005LL
 
long long n, t, i, a[M], s, m1, m2;
 
void fastio() {
    setvbuf(stdin, NULL, _IOFBF, 1024);
    setvbuf(stdout, NULL, _IOFBF, 1024);
}
 
long long fun1() {
    s = 0;
    m1 = X;
    for (i = 1; i <= n; i++) {
        s += a[i];
        if (s / i < m1) {
            m1 = s / i;
        }
    }
    return m1;
}
 
long long fun2() {
    s = 0;
    m2 = -1;
    for (i = n; i >= 1; i--) {
        s += a[i];
        if ((s + n - i) / (n - i + 1) > m2) {
            m2 = (s + n - i) / (n - i + 1);
        }
    }   
    return m2;
}
 
int main() {
    fastio();    
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld", &n);
        for (i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
        }
        long long min_val = fun1();
        long long max_val = fun2();
        printf("%lld\n", max_val - min_val);
    }
    return 0;
}