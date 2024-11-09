/**
 * @file
 * @brief 计算最大到十亿的素数
 * @see prime_numbers.cpp sieve_of_eratosthenes.cpp
 */
#include <cstring>
#include <iostream>

/** 存储素数的数组 */
char prime[100000000];

/** 执行筛法算法 */
void Sieve(int64_t n) {
    memset(prime, '1', sizeof(prime));  // 初始化数组，每个元素都设置为 '1'，表示假设所有数都是素数
    prime[0] = '0';                     // 0 不是素数
    prime[1] = '0';                     // 1 不是素数
    // 从 2 开始，检查每个数的平方是否小于等于 n
    for (int64_t p = 2; p * p <= n; p++) {
        if (prime[p] == '1') {  // 如果 p 是素数
            // 将 p 的所有倍数标记为非素数
            for (int64_t i = p * p; i <= n; i += p)
                prime[i] = '0';  // 将 p 的倍数设为 '0'，表示不是素数
        }
    }
}

/** 主函数 */
int main() {
    Sieve(100000000);  // 执行筛法，计算 1 到 10 亿之间的素数
    int64_t n;
    std::cin >> n;  // 用户输入一个整数 n

    // 如果 prime[n] 为 '1'，说明 n 是素数
    if (prime[n] == '1')
        std::cout << "YES\n";  // 输出 "YES"
    else
        std::cout << "NO\n";  // 否则输出 "NO"

    return 0;
}
