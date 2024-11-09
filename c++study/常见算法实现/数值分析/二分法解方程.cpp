/**
 * \file
 * \brief 使用 [二分法](https://en.wikipedia.org/wiki/Bisection_method) 求解方程 \f$f(x)=0\f$
 *
 * 给定两个点 \f$a\f$ 和 \f$b\f$，使得 \f$f(a)<0\f$ 且 \f$f(b)>0\f$，则 \f$(i+1)^\text{th}\f$ 近似值通过以下公式给出：
 * \f[
 * x_{i+1} = \frac{a_i + b_i}{2}
 * \f]
 * 对于下一次迭代，如果 \f$x>0\f$，则选择区间 \f$[a, x]\f$，如果 \f$x<0\f$，则选择区间 \f$[x, b]\f$。该过程会继续，直到得到足够精确的近似值。
 *
 * \see newton_raphson_method.cpp, false_position.cpp, secant_method.cpp
 */
#include <cmath>
#include <iostream>
#include <limits>

#define EPSILON \
    1e-6  // std::numeric_limits<double>::epsilon()  ///< 系统精度限制
#define MAX_ITERATIONS 50000  ///< 最大迭代次数

/** 定义函数 \f$f(x)\f$，用于求根 */
static double eq(double i) {
    return (std::pow(i, 3) - (4 * i) - 9);  // 原始方程
}

/** 获取给定数字的符号 */
template <typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

/** 主函数 */
int main() {
    double a = -1, b = 1, x, z;
    int i;

    // 循环查找初始区间 a, b
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        z = eq(a);  // 计算 a 处的函数值
        x = eq(b);  // 计算 b 处的函数值
        if (sgn(z) == sgn(x)) {  // 如果函数值符号相同，增大区间
            b++;  // 增大 b 的值
            a--;  // 减小 a 的值
        } else {  // 如果函数值符号不同，找到了区间
            break;
        }
    }

    std::cout << "\n第一次初始点: " << a;
    std::cout << "\n第二次初始点: " << b;

    // 开始迭代过程
    for (i = 0; i < MAX_ITERATIONS; i++) {
        x = (a + b) / 2;  // 计算区间中点
        z = eq(x);  // 计算中点处的函数值
        std::cout << "\n\nz: " << z << "\t[" << a << " , " << b
                  << " | Bisect: " << x << "]";

        if (z < 0) {  // 如果函数值小于0，更新 a
            a = x;
        } else {  // 如果函数值大于0，更新 b
            b = x;
        }

        if (std::abs(z) < EPSILON)  // 停止准则：如果函数值接近零，则停止
            break;
    }

    std::cout << "\n\n根: " << x << "\t\t步骤: " << i << std::endl;
    return 0;
}
