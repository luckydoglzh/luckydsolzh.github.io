/**
 * \file
 * \brief 使用 [Brent 方法](https://en.wikipedia.org/wiki/Brent%27s_method) 在给定区间内寻找一元实函数的真实极值。
 *
 * 参考算法发现者的论文 [在线](https://maths-people.anu.edu.au/~brent/pd/rpb011i.pdf)，以及
 * 相关书籍：
 * > R. P. Brent, 《无导数最小化算法》,
 * > Prentice-Hall, Englewood Cliffs, New Jersey, 1973
 *
 * \see golden_search_extrema.cpp
 *
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#define _USE_MATH_DEFINES  ///< 需要 MS Visual C++ 时使用
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>

#define EPSILON \
    std::sqrt(  \
        std::numeric_limits<double>::epsilon())  ///< 系统精度限制

/**
 * @brief 获取给定区间内函数的最小值。
 *
 * @param f 需要求最小值的函数
 * @param lim_a 搜索区间的下限
 * @param lim_b 搜索区间的上限
 * @return 返回区间内找到的最小值
 */
double get_minima(const std::function<double(double)> &f, double lim_a,
                  double lim_b) {
    uint32_t iters = 0;

    // 如果区间的下限大于上限，交换它们
    if (lim_a > lim_b) {
        std::swap(lim_a, lim_b);
    } else if (std::abs(lim_a - lim_b) <= EPSILON) {
        std::cerr << "搜索区间必须大于 " << EPSILON << "\n";
        return lim_a;
    }

    // 黄金比例常数
    const double M_GOLDEN_RATIO = (3.f - std::sqrt(5.f)) / 2.f;

    double v = lim_a + M_GOLDEN_RATIO * (lim_b - lim_a);  // 计算黄金分割点
    double u, w = v, x = v;
    double fu, fv = f(v);
    double fw = fv, fx = fv;

    double mid_point = (lim_a + lim_b) / 2.f;
    double p = 0, q = 0, r = 0;

    double d, e = 0;
    double tolerance, tolerance2;

    do {
        mid_point = (lim_a + lim_b) / 2.f;  // 更新中点
        tolerance = EPSILON * std::abs(x);  // 计算精度
        tolerance2 = 2 * tolerance;  // 双倍的精度

        // 如果 e 的绝对值大于容差，进行抛物线拟合
        if (std::abs(e) > tolerance2) {
            r = (x - w) * (fx - fv);
            q = (x - v) * (fx - fw);
            p = (x - v) * q - (x - w) * r;
            q = 2.f * (q - r);
            if (q > 0)
                p = -p;
            else
                q = -q;
            r = e;
            e = d;
        }

        // 如果拟合的抛物线更好，则执行抛物线插值步
        if (std::abs(p) < std::abs(0.5 * q * r) && p < q * (lim_b - x)) {
            d = p / q;
            u = x + d;
            if (u - lim_a < tolerance2 || lim_b - u < tolerance2)
                d = x < mid_point ? tolerance : -tolerance;
        } else {
            // 否则执行黄金分割插值步
            e = (x < mid_point ? lim_b : lim_a) - x;
            d = M_GOLDEN_RATIO * e;
        }

        // 不要太靠近 x 计算
        if (std::abs(d) >= tolerance)
            u = d;
        else if (d > 0)
            u = tolerance;
        else
            u = -tolerance;
        u += x;
        fu = f(u);

        // 更新变量
        if (fu <= fx) {
            if (u < x)
                lim_b = x;
            else
                lim_a = x;
            v = w;
            fv = fw;
            w = x;
            fw = fx;
            x = u;
            fx = fu;
        } else {
            if (u < x)
                lim_a = u;
            else
                lim_b = u;
            if (fu <= fw || x == w) {
                v = w;
                fv = fw;
                w = u;
                fw = fu;
            } else if (fu <= fv || v == x || v == w) {
                v = u;
                fv = fu;
            }
        }

        iters++;  // 迭代计数
    } while (std::abs(x - mid_point) > (tolerance - (lim_b - lim_a) / 2.f));

    std::cout << " (迭代次数: " << iters << ") ";

    return x;  // 返回最小值
}

/**
 * @brief 测试函数：在区间 \f$[1,5]\f$ 中寻找方程 \f$f(x)= (x-2)^2\f$ 的最小值
 * 预期结果为 2
 */
void test1() {
    // 使用 lambda 函数定义最小化的目标函数
    std::function<double(double)> f1 = [](double x) {
        return (x - 2) * (x - 2);
    };

    std::cout << "测试 1.... ";

    double minima = get_minima(f1, -1, 5);

    std::cout << minima << "...";

    assert(std::abs(minima - 2) < EPSILON);  // 检查结果
    std::cout << "通过\n";
}

/**
 * @brief 测试函数：在区间 \f$[-2,10]\f$ 中寻找方程 \f$f(x)= x^{\frac{1}{x}}\f$ 的最小值
 * 预期结果为：\f$e\approx 2.71828182845904509\f$
 */
void test2() {
    // 使用 lambda 函数定义最大化目标函数
    // 因为我们要最大化，所以返回值取负
    std::function<double(double)> func = [](double x) {
        return -std::pow(x, 1.f / x);
    };

    std::cout << "测试 2.... ";

    double minima = get_minima(func, -2, 5);

    std::cout << minima << " (" << M_E << ")...";

    assert(std::abs(minima - M_E) < EPSILON);  // 检查结果
    std::cout << "通过\n";
}

/**
 * @brief 测试函数：在区间 \f$[0,12]\f$ 中寻找方程 \f$f(x)= \cos x\f$ 的最大值
 * 预期结果为：\f$\pi\approx 3.14159265358979312\f$
 */
void test3() {
    // 使用 lambda 函数定义最大化目标函数
    // 因为我们要最大化，所以返回值取负
    std::function<double(double)> func = [](double x) { return std::cos(x); };

    std::cout << "测试 3.... ";

    double minima = get_minima(func, -4, 12);

    std::cout << minima << " (" << M_PI << ")...";

    assert(std::abs(minima - M_PI) < EPSILON);  // 检查结果
    std::cout << "通过\n";
}

/** 主函数 */
int main() {
    std::cout.precision(18);  // 设置输出精度

    std::cout << "计算使用的机器精度为: " << EPSILON << "\n";

    test1();  // 测试 1
    test2();  // 测试 2
    test3();  // 测试 3

    return 0;
}
