//有一个长度为n的字符串，每个字符要么为'<',要么为'>'，小球如果走到字符'<',下一步向左走，字符反转为'>'；反之亦然。
//求，起始位置位于每一个字符i，走出这个字符串需要多少步。
#include<stdio.h>
//思路还是模拟
//可以这样理解，加入位于 i，看哪边障碍少，就往哪边走。如果往左边走，左边'<'的字符是不必理会的，为什么呢？
//很简单，'<'即使反转后，如果遇到障碍，还是会回来的，不会阻碍你往右边走；如果没障碍，那更好了
//因此，只需要注意'>'的字符。怎么处理呢，假设障碍在k处，会多跑(i-k)*2的距离，因此用2(i - (i-k))的思想即可，但是不止这一个障碍呢，用前缀和处理吧，详细看代码
//用该思想从左往右和从右往左分别遍历一把，该问题即可解决。
// 定义字符数组，用于存储输入的字符串
char s[500005]; // 存储每个测试用例的字符序列
long long int leftPart[500005], rightPart[500005]; // 分别记录左边和右边的移动次数
long long int ind[500005], sum[500005]; // `ind`记录当前位置，`sum`用于前缀和的计算
long long int ans[500005]; // 存储每个位置的结果，即弹珠离开网格所需的步数
char t[50000007]; // 用于输出结果的缓冲区

// 解决单个测试用例
void solution(){
    long long int n;
    // 读取当前测试用例的长度 n
    scanf("%lld", &n);
    long long int i, j, k;
    // 读取字符串 s
    scanf("%s", s);
    
    // 初始化第一项的 `leftPart` 和 `rightPart`
    leftPart[0] = rightPart[0] = 0;
    
    // 计算左边和右边的移动次数
    // leftPart[i]：表示从第 0 个位置到第 i 个位置出现 '>' 的次数
    // rightPart[i]：表示从第 0 个位置到第 i 个位置出现 '<' 的次数
    for (i = 0; i < n; i++)
    {
        leftPart[i + 1] = leftPart[i];
        rightPart[i + 1] = rightPart[i];
        if (s[i] == '>')
            leftPart[i + 1]++;
        else
            rightPart[i + 1]++;
    }

    // 初始化答案数组为 0
    for (i = 0; i < n; i++)
        ans[i] = 0;

    // 初始化前缀和数组
    sum[0] = 0;
    j = 0; // 用于记录前缀和数组的索引

    // 从左到右扫描
    for (i = 0; i < n; i++)
    {
        if (s[i] == '<')
        {
            // 如果当前位置为 '<'，计算从右边离开所需的步数
            if (leftPart[i] > rightPart[n] - rightPart[i + 1])
                k = rightPart[n] - rightPart[i + 1] + 1;
            else
            {
                k = leftPart[i];
                ans[i] += i + 1; // 弹珠需要额外步数到边界
            }
        }
        else
        {
            // 如果当前位置为 '>'，计算从左边离开所需的步数
            if (leftPart[i] < rightPart[n] - rightPart[i + 1])
            {
                k = leftPart[i];
                ans[i] += i + 1; // 弹珠需要额外步数到边界
            }
            else
            {
                k = rightPart[n] - rightPart[i + 1];
            }
        }

        // 计算当前的前缀和
        ans[i] += 2 * (k * i - (sum[j] - sum[j - k]));
        
        if (s[i] == '>')
        {
            ind[j] = i;
            sum[j + 1] = sum[j] + ind[j];
            j++;
        }
    }

    sum[0] = 0;
    j = 0;

    // 从右到左扫描
    for (i = n - 1; i >= 0; i--)
    {
        if (s[i] == '<')
        {
            if (leftPart[i] > rightPart[n] - rightPart[i + 1])
            {
                k = rightPart[n] - rightPart[i + 1];
                ans[i] += n - i; // 额外步数到边界
            }
            else
                k = leftPart[i];
        }
        else
        {
            if (leftPart[i] < rightPart[n] - rightPart[i + 1])
                k = leftPart[i] + 1;
            else
            {
                k = rightPart[n] - rightPart[i + 1];
                ans[i] += n - i; // 额外步数到边界
            }
        }

        ans[i] += 2 * (sum[j] - sum[j - k] - k * i);
        
        if (s[i] == '<')
        {
            ind[j] = i;
            sum[j + 1] = sum[j] + ind[j];
            j++;
        }
    }

    j = 0;

    // 将结果数组 `ans` 转换为字符串并存入缓冲区 `t` 中
    for (i = 0; i < n; i++)
    {
        for (k = 1; k <= ans[i]; k *= 10); // 找到适合的位数
        for (k /= 10; k > 0; k /= 10)
        {
            t[j] = ans[i] / k + '0'; // 将数字转换为字符
            ans[i] %= k; // 去除最高位
            j++;
        }

        if (i < n - 1)
            t[j] = ' '; // 两个数字之间加空格
        else
            t[j] = '\0'; // 最后一个字符加上终止符
        j++;
    }

    // 输出结果
    printf("%s\n", t);
    return;
}

int main(){
    int t;
    // 读取测试用例的数量
    scanf("%d", &t);

    // 对每个测试用例调用 `solution` 函数
    for (; t > 0; t--)
        solution();

    return 0;
}
