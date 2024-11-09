/**
 * @file
 * @brief C++程序用于迭代和递归地进行二进制幂运算。
 *
 * 计算 \f$a^b\f$ 的时间复杂度为 \f$O(\log(b))\f$，通过将 \f$b\f$ 转换为二进制表示。
 * 二进制幂运算也称为平方求幂法。
 * @note 这是一种比朴素方法更优的方式，朴素方法的时间复杂度为 \f$O(b)\f$。
 *
 * 示例:
 * </br>10的二进制表示是1010。
 * \f{eqnarray*}{
 * 2^{10_d} &=& 2^{1010_b} = 2^8 * 2^2\\
 * 2^1 &=& 2\\
 * 2^2 &=& (2^1)^2 = 2^2 = 4\\
 * 2^4 &=& (2^2)^2 = 4^2 = 16\\
 * 2^8 &=& (2^4)^2 = 16^2 = 256\\
 * \f}
 * 因此要计算 2^10，只需相乘 \f$2^8\f$ 和 \f$2^2\f$，跳过 \f$2^1\f$ 和 \f$2^4\f$。
 */

#include <iostream>

/// 使用递归方法进行二进制幂运算，时间复杂度为 \f$O(\log(n))\f$
int binExpo(int a, int b) {
    // 如果指数为 0，则任何数的 0 次方都为 1
    if (b == 0) {
        return 1;
    }
    // 递归调用，求 a^(b/2)
    int res = binExpo(a, b / 2);
    // 如果 b 是奇数，则返回 res * res * a，否则返回 res * res
    if (b % 2) {
        return res * res * a;
    } else {
        return res * res;
    }
}

/// 使用迭代方法进行二进制幂运算，时间复杂度为 \f$O(\log(n))\f$
int binExpo_alt(int a, int b) {
    int res = 1;
    // 当 b 大于 0 时循环
    while (b > 0) {
        // 如果 b 是奇数，将当前结果乘以 a
        if (b % 2) {
            res = res * a;
        }
        // 更新 a 为 a 的平方，b 减半
        a = a * a;
        b /= 2;
    }
    return res;
}

/// 主函数
int main() {
    int a, b;
    // 输入两个整数 a 和 b
    std::cin >> a >> b;
    if (a == 0 && b == 0) {
        // 0 的 0 次方是未定义的
        std::cout << "数学错误" << std::endl;
    } else if (b < 0) {
        // 指数必须为正数
        std::cout << "指数必须为正数！" << std::endl;
    } else {
        int resRecurse = binExpo(a, b);
        // int resIterate = binExpo_alt(a, b);

        // 输出 a^b 的结果（'^' 表示幂运算）
        std::cout << resRecurse << std::endl;
        // std::cout << resIterate << std::endl;
    }
}
