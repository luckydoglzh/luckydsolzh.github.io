/**
 * @file
 * @brief 更高效的计算斐波那契数列
 *
 * 这个算法比使用矩阵幂的 \f$O(n \log n)\f$ 方法更快、更简单。它结合了递归和动态规划的优点。由于第93个斐波那契数会超过19位数字，无法存储在一个 `long long` 类型的变量中，因此我们只能计算到第92个斐波那契数。如果我们实现大整数（bigint）类型，可以继续计算更大的斐波那契数，例如第10000个斐波那契数。此算法的关键在于，如果我们已经找到了第 \f$n/2\f$ 或 \f$(n+1)/2\f$ 个斐波那契数，就可以很容易地计算出第 \f$n\f$ 个斐波那契数。这是斐波那契数列的一个性质，类似于矩阵幂。
 *
 * \author [Krishna Vedala](https://github.com/kvedala)
 * @see fibonacci_large.cpp, fibonacci.cpp, string_fibonacci.cpp
 */

#include <cinttypes>
#include <cstdio>
#include <iostream>

/**
 * 最大计算限制 - 因为第93个斐波那契数无法存储在 `uint64_t` 数据类型中，
 * 所以最大计算值为92。
 */

#define MAX 93

/** 计算斐波那契数的算法 */
uint64_t fib(uint64_t n) {
    static uint64_t f1 = 1, f2 = 1;  // 使用 static 关键字，f1 和 f2 的值会在下一次调用时保留。

    if (n <= 2)
        return f2;  // 如果 n 是1或2，返回第二个斐波那契数，即 1。
    if (n >= 93) {
        std::cerr
            << "由于64位整数的限制，无法计算n>93的斐波那契数\n";
        return 0;  // 超出计算范围，返回0
    }

    uint64_t temp = f2;  // 临时变量，用于交换 f1 和 f2
    f2 += f1;  // f2 变成 f1 + f2，即当前斐波那契数
    f1 = temp;  // f1 变成之前的 f2，即上一个斐波那契数

    return f2;  // 返回当前计算的斐波那契数
}

/** 主函数 */
int main() {
    // 主函数
    for (uint64_t i = 1; i < 93; i++) {
        std::cout << i << " th 斐波那契数是 " << fib(i) << std::endl;
    }
    return 0;
}
