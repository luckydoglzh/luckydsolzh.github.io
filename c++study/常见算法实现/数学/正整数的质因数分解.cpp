/**
 * @file
 * @brief 正整数的质因数分解
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

/** 声明变量用于存储素数以及检查一个数是否为素数 */
bool isprime[1000006];

/** 素数列表 */
std::vector<int> prime_numbers;

/** 质因数对的列表 */
std::vector<std::pair<int, int>> factors;

/** 计算一个给定范围内的所有素数（埃拉托斯特尼筛法） */
void SieveOfEratosthenes(int N) {
    // 初始化 isprime 数组
    memset(isprime, true, sizeof isprime);

    // 使用埃拉托斯特尼筛法标记素数
    for (int i = 2; i <= N; i++) {
        if (isprime[i]) {
            // 标记 i 的倍数为非素数
            for (int j = 2 * i; j <= N; j += i) isprime[j] = false;
        }
    }

    // 将所有素数加入 prime_numbers 列表
    for (int i = 2; i <= N; i++) {
        if (isprime[i])
            prime_numbers.push_back(i);
    }
}

/** 计算一个数的质因数分解 */
void prime_factorization(int num) {
    int number = num;

    // 对每个素数进行质因数分解
    for (int i = 0; prime_numbers[i] <= num; i++) {
        int count = 0;

        // 终止条件，如果 num 已经被分解到 1，则停止
        if (number == 1) {
            break;
        }

        // 统计每个素数能整除 num 的次数
        while (number % prime_numbers[i] == 0) {
            count++;
            number = number / prime_numbers[i];
        }

        // 如果 count > 0，说明该素数是 num 的因数
        if (count)
            factors.push_back(std::make_pair(prime_numbers[i], count));
    }
}

/** 主程序 */
int main() {
    int num;
    std::cout << "\t\t计算质因数分解\n\n";
    std::cout << "请输入一个数字: ";
    std::cin >> num;

    // 通过埃拉托斯特尼筛法找到所有小于等于 num 的素数
    SieveOfEratosthenes(num);

    // 对输入的数字进行质因数分解
    prime_factorization(num);

    // 输出质因数及其指数（幂）
    for (auto it : factors) {
        std::cout << it.first << " " << it.second << std::endl;
    }

    return 0;
}
