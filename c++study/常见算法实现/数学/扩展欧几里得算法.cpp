/**
 * @file
 * @brief 使用 [扩展欧几里得算法](https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm) 计算 GCD
 *
 * 计算 Bézout 恒等式中的系数，即求解 a 和 b 的系数 x 和 y
 * \f[\text{gcd}(a, b) = a \times x + b \times y \f]
 * 此方法也用于计算数的模逆元 (Modular Multiplicative Inverse)。
 * 即通过扩展欧几里得算法，若 (A * B) % M == 1，那么 B 是 A 关于 M 的模逆元，因此调用 extendedEuclid(A, M) 可以得到 B。
 */
#include <algorithm>  // 用于交换函数
#include <iostream>
#include <cstdint>

/**
 * 更新每一步的系数
 * \f[r_0,\,r = r,\, r_0 - \text{quotient} \times r\f]
 *
 * @param[in,out] r 有符号或无符号数
 * @param[in,out] r0 有符号或无符号数
 * @param[in] quotient 无符号数
 */
template <typename T, typename T2>
inline void update_step(T *r, T *r0, const T2 quotient) {
    T temp = *r;
    *r = *r0 - (quotient * temp);  // 更新 r
    *r0 = temp;  // 更新 r0
}

/**
 * 使用迭代算法实现扩展欧几里得算法
 * 来自 [Wikipedia](https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Pseudocode)
 *
 * @param[in] A 无符号数
 * @param[in] B 无符号数
 * @param[out] GCD 无符号数，存储计算得到的最大公约数
 * @param[out] x 有符号数，存储 x 系数
 * @param[out] y 有符号数，存储 y 系数
 */
template <typename T1, typename T2>
void extendedEuclid_1(T1 A, T1 B, T1 *GCD, T2 *x, T2 *y) {
    if (B > A)
        std::swap(A, B);  // 确保 A >= B

    T2 s = 0, s0 = 1;
    T2 t = 1, t0 = 0;
    T1 r = B, r0 = A;

    while (r != 0) {  // 迭代直到余数为 0
        T1 quotient = r0 / r;
        update_step(&r, &r0, quotient);  // 更新 r 和 r0
        update_step(&s, &s0, quotient);  // 更新 s 和 s0
        update_step(&t, &t0, quotient);  // 更新 t 和 t0
    }
    *GCD = r0;  // 最终最大公约数
    *x = s0;  // x 系数
    *y = t0;  // y 系数
}

/**
 * 使用递归算法实现扩展欧几里得算法
 *
 * @param[in] A 无符号数
 * @param[in] B 无符号数
 * @param[out] GCD 无符号数，存储计算得到的最大公约数
 * @param[in,out] x 有符号数，存储 x 系数
 * @param[in,out] y 有符号数，存储 y 系数
 */
template <typename T, typename T2>
void extendedEuclid(T A, T B, T *GCD, T2 *x, T2 *y) {
    if (B > A)
        std::swap(A, B);  // 确保 A >= B

    if (B == 0) {  // 递归基准情况
        *GCD = A;
        *x = 1;
        *y = 0;
    } else {
        extendedEuclid(B, A % B, GCD, x, y);  // 递归调用
        T2 temp = *x;
        *x = *y;
        *y = temp - (A / B) * (*y);  // 更新 x 和 y 系数
    }
}

/// 主函数
int main() {
    uint32_t a, b, gcd;
    int32_t x, y;
    std::cin >> a >> b;  // 输入两个无符号数 A 和 B
    extendedEuclid(a, b, &gcd, &x, &y);  // 使用递归算法计算 GCD 和系数
    std::cout << gcd << " " << x << " " << y << std::endl;  // 输出结果
    extendedEuclid_1(a, b, &gcd, &x, &y);  // 使用迭代算法计算 GCD 和系数
    std::cout << gcd << " " << x << " " << y << std::endl;  // 输出结果
    return 0;
}
