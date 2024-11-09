/**
 * \file
 * \brief 使用 [牛顿-拉夫森方法](https://en.wikipedia.org/wiki/Newton%27s_method) 求解方程 \f$f(x)=0\f$ 的实数和复数解
 *
 * 牛顿-拉夫森方法的迭代公式为：
 * \f[
 * x_{i+1} = x_i - \frac{f(x_i)}{f'(x_i)}
 * \f]
 *
 * \author [Krishna Vedala](https://github.com/kvedala)
 * \see bisection_method.cpp, false_position.cpp
 */
#include <cmath>
#include <ctime>
#include <iostream>
#include <limits>

constexpr double EPSILON = 1e-10;              ///< 系统精度限制
constexpr int16_t MAX_ITERATIONS = INT16_MAX;  ///< 最大迭代次数

/** 定义需要求解根的方程 \f$f(x)\f$。
 * 当前定义为：
 * \f[
 * f(x) = x^3 - 4x - 9
 * \f]
 */
static double eq(double i) {
    return (std::pow(i, 3) - (4 * i) - 9);  // 原方程 f(x) = x^3 - 4x - 9
}

/** 定义方程的导数 \f$f'(x)\f$
 * 当前为：
 * \f[
 * f'(x) = 3x^2 - 4
 * \f]
 */
static double eq_der(double i) {
    return ((3 * std::pow(i, 2)) - 4);  // 方程的导数 f'(x) = 3x^2 - 4
}

/** 主函数 */
int main() {
    std::srand(std::time(nullptr));  // 初始化随机数生成器

    double z = NAN, c = std::rand() % 100, m = NAN, n = NAN;
    int i = 0;

    std::cout << "\n初始近似值: " << c;

    // 开始迭代计算
    for (i = 0; i < MAX_ITERATIONS; i++) {
        m = eq(c);         // 计算 f(c)
        n = eq_der(c);     // 计算 f'(c)

        z = c - (m / n);   // 计算新的近似值
        c = z;             // 更新近似值

        if (std::abs(m) < EPSILON) {  // 如果 |f(c)| 足够小，则停止迭代
            break;
        }
    }

    std::cout << "\n\n根值: " << z << "\t\t迭代步数: " << i << std::endl;
    return 0;
}
