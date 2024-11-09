/**
 * @file
 * @brief C++ Program to calculate the number of positive divisors
 *
 * 该算法使用了质因数分解的方法。
 * 任何正整数都可以写成其质因数的积。
 * <br/>假设 \f$N = p_1^{e_1} \times p_2^{e_2} \times\cdots\times p_k^{e_k}\f$
 * 其中 \f$p_1,\, p_2,\, \dots,\, p_k\f$ 是 \f$N\f$ 的不同质因数，
 * \f$e_1,\, e_2,\, \dots,\, e_k\f$ 是相应的正整数指数。
 * <br/>每个 \f$N\f$ 的正约数都可以表示为
 * \f$p_1^{g_1}\times p_2^{g_2}\times\cdots\times p_k^{g_k}\f$
 * 其中 \f$0 \le g_i \le e_i\f$ 是整数，适用于所有 \f$1 \le i \le k\f$。
 * <br/>最终，\f$N\f$ 的正约数的个数为 \f$(e_1+1) \times (e_2+1)\times\cdots\times (e_k+1)\f$
 * 因为我们可以独立地选择每个 \f$g_i\f$。
 *
 * 例如：
 * <br/>\f$N = 36 = (3^2 \cdot 2^2)\f$
 * <br/>\f$\mbox{number_of_positive_divisors}(36) = (2+1) \cdot (2+1) = 9\f$。
 * <br/>36的正约数列表 = 1, 2, 3, 4, 6, 9, 12, 18, 36。
 *
 * 同样，对于 N = -36，正约数的个数保持不变。
 **/

#include <cassert>
#include <iostream>

/**
 * 函数用于计算正约数的个数
 * @param n 需要计算约数的数字
 * @returns n 的正约数个数 (如果 n = 0 返回 1)
 */
int number_of_positive_divisors(int n) {
    if (n < 0) {
        n = -n; // 如果 n 为负数，取其绝对值
    }

    int number_of_divisors = 1;

    // 从 2 开始到 sqrt(n) 检查是否能整除 n
    for (int i = 2; i * i <= n; i++) {
        // 这一部分是进行质因数分解。
        // 注意，除非我们已经找到相应的质因数并将其从 n 中除去，
        // 否则无法找到 n 的合成约数。因此，这里找到的所有约数实际上都是质数。
        int prime_exponent = 0;
        while (n % i == 0) {
            // 反复除以质因数 i 来计算指数 (e_i)，即质因数的次数
            prime_exponent++;
            n /= i;
        }
        number_of_divisors *= prime_exponent + 1;
    }

    if (n > 1) {
        // 如果 n 仍大于 1，说明它是一个质数
        // 这时我们要乘以 (e_k + 1) 来得到其正约数的个数。
        number_of_divisors *= 2;
    }

    return number_of_divisors;
}

/**
 * 测试函数
 */
void tests() {
    // 测试各种情况，验证正约数的个数是否正确
    assert(number_of_positive_divisors(36) == 9);  // 36 = 2^2 * 3^2，约数有 9 个
    assert(number_of_positive_divisors(-36) == 9); // 负数的正约数个数与正数相同
    assert(number_of_positive_divisors(1) == 1);   // 1 只有一个约数：1
    assert(number_of_positive_divisors(2011) == 2); // 2011 是质数，约数有 2 个：1 和 2011
    assert(number_of_positive_divisors(756) == 24); // 756 = 2^2 * 3^3 * 7，约数有 24 个
}

/**
 * 主函数
 */
int main() {
    tests(); // 执行测试

    int n;
    std::cin >> n; // 输入一个整数 n

    if (n == 0) {
        // 如果输入是 0，输出提示信息
        std::cout << "All non-zero numbers are divisors of 0 !" << std::endl;
    } else {
        // 输出正约数的个数
        std::cout << "Number of positive divisors is : ";
        std::cout << number_of_positive_divisors(n) << std::endl;
    }

    return 0;
}
