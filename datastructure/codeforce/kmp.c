//解决前缀和类问题的优秀操作

// 在伯兰国立大学，服务器之间的局域网并不总是无错误地运行。当连续传输两条相同的消息时，可能会发生错误，导致这两条消息合并为一条。在这种合并中，第一条消息的结尾与第二条消息的开头重合。当然，合并只能发生在相同的字符处。合并的长度必须是一个正数，且小于消息文本的长度。

// 例如，当连续传输两条消息 "abrakadabra" 时，可能会发生合并错误，导致接收到的消息像是 "abrakadabrabrakadabra" 或 "abrakadabrakadabra"（在第一个例子中，合并发生在一个字符处，第二个例子中合并发生在四个字符处）。

// 现在给定接收到的消息字符串 t，判断它是否有可能是上述类型错误的结果。如果是，请找出可能的原始消息 s。

// 需要注意的是，完全重叠的情况不应视为错误。例如，如果接收到的消息是 "abcd"，则应该认为这不是错误。同样地，简单地将一条消息附加在另一条消息之后也不应视为错误。例如，如果接收到的消息是 "abcabc"，这也不应被视为错误。

// 输入：
// 输入包含一个非空字符串 t，由小写拉丁字母组成。字符串 t 的长度不超过 4·10^5 个字符。

// 输出：
// 如果消息 t 不可能包含错误，输出 "NO"（不带引号）。

// 否则，在第一行输出 "YES"（不带引号），在下一行输出可能的原始消息字符串 s。若有多个可能的答案，输出任意一个即可。

//KMP的核心思想就是不要重复匹配
#include <stdio.h>
#include <string.h>
 
#define MAXN 1000010  
 
int main() {
    char s[MAXN];
    scanf("%s", s);
    
    int n = strlen(s);
    int f[MAXN] = {0};
    int i  = 1 , j = 0;
    for (; i < n; i++) {
        while (j > 0 && s[i] != s[j]) {
            j = f[j];
        }
        if (s[i] == s[j]) {
            j++;
        }
        f[i + 1] = j;
    }
    
    if (f[n] > n / 2) {
        printf("YES\n");
        s[f[n]] = '\0';  
        printf("%s\n", s);
    } else {
        printf("NO\n");
    }
    
    return 0;
}