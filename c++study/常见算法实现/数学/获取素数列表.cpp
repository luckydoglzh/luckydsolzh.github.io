/**
 * @file
 * @brief 获取素数列表
 * @see primes_up_to_billion.cpp sieve_of_eratosthenes.cpp
 */
#include <iostream>
#include <vector>

/** 生成越来越大的素数并将其存储在列表中 */
std::vector<int> primes(size_t max) {
    std::vector<int> res;  // 用于存储素数的结果列表
    std::vector<bool> is_not_prime(max + 1, false);  // 用于标记是否为素数的布尔数组，初始化为false

    // 遍历 2 到 max 之间的每个数
    for (size_t i = 2; i <= max; i++) {
        if (!is_not_prime[i]) {  // 如果 i 不是被标记为非素数
            res.emplace_back(i);  // 将 i 添加到素数列表中
        }
        
        // 对素数列表中的每个素数 p，检查是否能将 i 标记为非素数
        for (int p : res) {
            size_t k = i * p;  // 计算 i 和 p 的积
            if (k > max) {  // 如果积大于 max，则跳出循环
                break;
            }
            is_not_prime[k] = true;  // 标记 k 为非素数
            if (i % p == 0) {  // 如果 i 能被 p 整除，则跳出循环
                break;
            }
        }
    }
    return res;  // 返回素数列表
}

/** 主函数 */
int main() {
    std::cout << "计算素数直到：\n>> ";
    int n = 0;  // 用户输入的最大值
    std::cin >> n;

    // 获取直到 n 的所有素数
    std::vector<int> ans = primes(n);

    // 输出所有素数
    for (int p : ans) std::cout << p << ' ';
    std::cout << std::endl;
}
