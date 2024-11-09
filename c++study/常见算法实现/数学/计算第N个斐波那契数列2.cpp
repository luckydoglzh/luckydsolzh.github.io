/**
 * @file 
 * @brief 此程序计算第 N 个斐波那契数，并取模 mod。
 * 输入参数。
 *
 * 采用 O(logn) 时间复杂度来计算第 n 个斐波那契数
 *
 * \author [villayatali123](https://github.com/villayatali123)
 * \author [unknown author]()
 * @see fibonacci.cpp, fibonacci_fast.cpp, string_fibonacci.cpp, fibonacci_large.cpp
 */

#include <iostream>
#include <vector>
#include <cassert>

/**
 * 此函数计算模 mod 下的第 n 个斐波那契数
 * @param n 第 n 个斐波那契数
 * @param mod 模数
 */
uint64_t fibo(uint64_t n, uint64_t mod) {
    std::vector<uint64_t> result(2, 0);  // 存储结果向量
    std::vector<std::vector<uint64_t>> transition(2, std::vector<uint64_t>(2, 0));  // 转移矩阵
    std::vector<std::vector<uint64_t>> Identity(2, std::vector<uint64_t>(2, 0));  // 单位矩阵
    n--;
    result[0] = 1, result[1] = 1;
    Identity[0][0] = 1; Identity[0][1] = 0;
    Identity[1][0] = 0; Identity[1][1] = 1;
    
    transition[0][0] = 0;
    transition[1][0] = transition[1][1] = transition[0][1] = 1;
    
    while (n) {
        if (n % 2) {  // 如果 n 是奇数
            std::vector<std::vector<uint64_t>> res(2, std::vector<uint64_t>(2, 0));
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    for (int k = 0; k < 2; k++) {
                        res[i][j] = (res[i][j] % mod + ((Identity[i][k] % mod * transition[k][j] % mod)) % mod) % mod;
                    }
                }
            }
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    Identity[i][j] = res[i][j];  // 更新单位矩阵
                }
            }
            n--;
        } else {  // 如果 n 是偶数
            std::vector<std::vector<uint64_t>> res1(2, std::vector<uint64_t>(2, 0));
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    for (int k = 0; k < 2; k++) {
                        res1[i][j] = (res1[i][j] % mod + ((transition[i][k] % mod * transition[k][j] % mod)) % mod) % mod;
                    }
                }
            }
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    transition[i][j] = res1[i][j];  // 更新转移矩阵
                }
            }
            n = n / 2;
        }
    }
    return ((result[0] % mod * Identity[0][0] % mod) % mod + (result[1] % mod * Identity[1][0] % mod) % mod) % mod;
}

/**
 * 测试函数，用于验证算法正确性
 */
void test() {
    assert(fibo(6, 1000000007) == 8);
    std::cout << "测试用例1通过\n";
    assert(fibo(5, 1000000007) == 5);
    std::cout << "测试用例2通过\n";
    assert(fibo(10, 1000000007) == 55);
    std::cout << "测试用例3通过\n";
    assert(fibo(500, 100) == 25);
    std::cout << "测试用例4通过\n";
    assert(fibo(500, 10000) == 4125);
    std::cout << "测试用例5通过\n";
    std::cout << "--所有测试用例通过--\n";
}

/**
 * 主函数
 */
int main() {
    test();
    uint64_t mod = 1000000007;
    std::cout << "请输入 N 的值: ";
    uint64_t n = 0;
    std::cin >> n;
    std::cout << n << " 斐波那契数取模 " << mod << " 的结果是: " << fibo(n, mod) << std::endl;
}
