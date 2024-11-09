/**
 * Copyright 2020 @author tjgurwara99
 * @file
 *
 * 一个简单的 Miller-Rabin 素数测试实现。
 */

#include <cassert>
#include <iostream>
#include <random>
#include <vector>

/**
 * 将数字转换为二进制的逆序表示
 * @param num 要转换的整数
 * @return result 返回逆序的二进制表示（使用向量）
 */
template <typename T>
std::vector<T> reverse_binary(T num) {
    std::vector<T> result;
    T temp = num;
    while (temp > 0) {
        result.push_back(temp % 2);  // 计算当前最低位，并存入结果
        temp = temp / 2;  // 将 num 除以 2
    }
    return result;
}

/**
 * 模幂运算的函数实现。这个函数是高效的模幂算法。
 * 它可以与任何大整数库（如 Boost Multiprecision）一起使用，快速解决模幂问题。
 * @param base 被求幂的底数
 * @param rev_binary_exponent 指数的逆序二进制表示
 * @param mod 模数
 * @return r 模幂结果，计算 \f$a^{n} \equiv r \mod{m}\f$，其中 \f$n\f$ 是 rev_binary_exponent 的十进制表示，\f$m\f$ 是 mod
 */
template <typename T>
T modular_exponentiation(T base, const std::vector<T> &rev_binary_exponent, T mod) {
    if (mod == 1)
        return 0;
    T b = 1;  // 初始化结果
    if (rev_binary_exponent.size() == 0)
        return b;  // 如果没有二进制位，返回 1
    T A = base;
    if (rev_binary_exponent[0] == 1)
        b = base;  // 如果二进制的最低位是1，则 b = base

    // 从第二位开始，依次处理逆序二进制
    for (typename std::vector<T>::const_iterator it = rev_binary_exponent.cbegin() + 1; it != rev_binary_exponent.cend(); ++it) {
        A = A * A % mod;  // A^2 % mod
        if (*it == 1)
            b = A * b % mod;  // 如果该位是1，则 b = A * b % mod
    }
    return b;
}

/**
 * Miller-Rabin 素数测试中的核心条件测试函数。
 * @param d 使得 \f$d \cdot 2^r = n - 1\f$，其中 \f$n\f$ 为输入数字
 * @param num 需要检测是否为素数的数字
 * @return 'false' 如果 num 是合数
 * @return 'true' 如果 num 是（可能的）素数
 */
template <typename T>
bool miller_test(T d, T num) {
    // 随机数生成器种子
    std::random_device rd_seed;
    // 随机数生成器
    std::mt19937 gen(rd_seed());
    // 在 [2, num - 2] 范围内生成一个均匀分布的随机数
    std::uniform_int_distribution<> distribution(2, num - 2);
    T random = distribution(gen);  // 生成随机数
    // 获取指数 d 的逆序二进制表示
    std::vector<T> power = reverse_binary(d);
    // 计算 x = random^d % num
    T x = modular_exponentiation(random, power, num);

    // 检查 Miller-Rabin 的条件
    if (x == 1 || x == num - 1) {
        return true;
    }

    // 如果 d 不等于 num - 1，则继续平方
    while (d != num - 1) {
        x = (x * x) % num;  // x = x^2 % num
        d *= 2;  // d = d * 2
        if (x == 1) {
            return false;  // 如果 x = 1，则不是素数
        }
        if (x == num - 1) {
            return true;  // 如果 x = num - 1，则是素数
        }
    }
    return false;
}

/**
 * Miller-Rabin 素数测试的主函数，通过多次迭代来概率性判断一个数字是否是素数。
 * @param num 要检查的数字
 * @param repeats 测试的重复次数，以提高结果的准确性
 * @return 'false' 如果 num 是合数
 * @return 'true' 如果 num 是（可能的）素数
 *
 * 详细过程：
 * 1. 如果 num 小于等于4，直接判断是否是2或3，若是则返回真，否则返回假。
 * 2. 如果 num 是偶数，则返回假，因为大于2的素数都为奇数。
 * 3. 将 num 表示为 \f$num = 2^r \cdot d + 1\f$，其中 \f$r \geq 1\f$。
 * 4. 使用 for 循环执行多次 Miller-Rabin 测试，若任一次返回假，则 num 为合数。
 * 5. 如果多次测试都通过，则认为 num 是（可能的）素数。
 */
template <typename T>
bool miller_rabin_primality_test(T num, T repeats) {
    if (num <= 4) {
        // 如果 num 等于 2 或 3，则是素数
        if (num == 2 || num == 3) {
            return true;
        } else {
            return false;  // 其他小于4的数不是素数
        }
    }
    // 如果 num 是偶数，则返回假（大于2的素数都是奇数）
    if (num % 2 == 0) {
        return false;
    }
    
    // 找到 d 和 r，使得 num = 2^r * d + 1
    T d = num - 1, r = 0;
    while (d % 2 == 0) {
        d = d / 2;  // 不断将 d 除以 2
        r++;
    }

    // 执行 Miller-Rabin 测试多次
    for (T i = 0; i < repeats; ++i) {
        if (!miller_test(d, num)) {
            return false;  // 如果任一次测试失败，返回 false
        }
    }
    return true;  // 多次测试通过，认为 num 是（可能的）素数
}

/**
 * 测试 Miller-Rabin 素数测试函数的函数，包括一些断言语句。
 */
void tests() {
    // 第一个测试：测试 2
    assert(((void)"2 应该是素数，但函数返回错误。\n",
            miller_rabin_primality_test(2, 1) == true));
    std::cout << "第一个测试通过。" << std::endl;
    
    // 第二个测试：测试 5
    assert(((void)"5 应该是素数，但函数返回错误。\n",
            miller_rabin_primality_test(5, 3) == true));
    std::cout << "第二个测试通过。" << std::endl;
    
    // 第三个测试：测试 23
    assert(((void)"23 应该是素数，但函数返回错误。\n",
            miller_rabin_primality_test(23, 3) == true));
    std::cout << "第三个测试通过。" << std::endl;
    
    // 第四个测试：测试 16
    assert(((void)"16 不是素数，但函数返回错误。\n",
            miller_rabin_primality_test(16, 3) == false));
    std::cout << "第四个测试通过。" << std::endl;
    
    // 第五个测试：测试 27
    assert(((void)"27 不是素数，但函数返回错误。\n",
            miller_rabin_primality_test(27, 3) == false));
    std::cout << "第五个测试通过。" << std::endl;
}

/**
 * 主函数
 */
int main() {
    tests();  // 执行测试
    return 0;  // 返回 0，表示程序正常结束
}
