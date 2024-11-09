/**
 * @file
 * @brief 更快的计算 \f$a^b\f$ 的方法
 *
 * 该程序使用 \f$O(\log N)\f$ 时间计算 \f$a^b\f$。
 * 它基于以下公式：
 * 1. 如果 \f$b\f$ 是偶数：
 *    \f$a^b = a^{\frac{b}{2}} \cdot a^{\frac{b}{2}} = \left(a^{\frac{b}{2}}\right)^2\f$
 * 2. 如果 \f$b\f$ 是奇数：
 *    \f$a^b = a^{\frac{b-1}{2}} \cdot a^{\frac{b-1}{2}} \cdot a = \left(a^{\frac{b-1}{2}}\right)^2 \cdot a\f$
 *
 * 我们可以使用递归方法根据上述算法来计算 \f$a^b\f$。
 */

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>

/**
 * 计算 \f$a^b\f$ 的递归算法
 */
template <typename T>
double fast_power_recursive(T a, T b) {
    // 负数指数的情况：a^b = 1 / (a^-b)
    if (b < 0)
        return 1.0 / fast_power_recursive(a, -b);

    if (b == 0)
        return 1;  // 基础情况：任何数的 0 次方是 1
    
    T bottom = fast_power_recursive(a, b >> 1);  // b / 2
    
    double result;
    if ((b & 1) == 0) {  // 如果 b 是偶数，使用公式 1
        result = bottom * bottom;
    } else {  // 如果 b 是奇数，使用公式 2
        result = bottom * bottom * a;
    }
    return result;
}

/**
 * 另一种略有不同的计算方法，仍然是 \f$O(\log N)\f$ 时间复杂度
 */
template <typename T>
double fast_power_linear(T a, T b) {
    // 负数指数的情况：a^b = 1 / (a^-b)
    if (b < 0)
        return 1.0 / fast_power_linear(a, -b);

    double result = 1;
    while (b) {
        if (b & 1)  // 如果 b 是奇数
            result = result * a;
        a = a * a;  // 将 a 的平方
        b = b >> 1;  // b 除以 2
    }
    return result;
}

/**
 * 主函数
 */
int main() {
    std::srand(std::time(nullptr));  // 设置随机数种子
    std::ios_base::sync_with_stdio(false);  // 提高 IO 效率

    std::cout << "正在测试..." << std::endl;
    // 进行 20 次随机测试
    for (int i = 0; i < 20; i++) {
        int a = std::rand() % 20 - 10;  // 随机生成 -10 到 9 之间的整数
        int b = std::rand() % 20 - 10;  // 随机生成 -10 到 9 之间的整数
        std::cout << std::endl << "计算 " << a << "^" << b << std::endl;
        // 使用断言检查递归和线性计算结果是否与标准库的 pow 函数一致
        assert(fast_power_recursive(a, b) == std::pow(a, b));
        assert(fast_power_linear(a, b) == std::pow(a, b));

        std::cout << "------ " << a << "^" << b << " = "
                  << fast_power_recursive(a, b) << std::endl;
    }

    int64_t a, b;
    std::cin >> a >> b;  // 输入两个整数 a 和 b

    // 使用递归方法和线性方法计算并输出结果
    std::cout << a << "^" << b << " = " << fast_power_recursive(a, b)
              << std::endl;

    std::cout << a << "^" << b << " = " << fast_power_linear(a, b) << std::endl;

    return 0;
}
