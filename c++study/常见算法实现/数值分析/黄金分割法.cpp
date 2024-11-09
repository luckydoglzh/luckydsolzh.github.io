/**
 * \file
 * \brief 使用 [黄金分割法](https://en.wikipedia.org/wiki/Golden-section_search) 在给定区间内寻找单变量实值函数的极值。
 * 
 * \see brent_method_extrema.cpp
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#define _USE_MATH_DEFINES  //< Visual C++ 所需的宏定义
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>

#define EPSILON 1e-7  ///< 解的精度限制

/**
 * @brief 在给定区间内寻找函数的最小值。若要寻找最大值，可以简单地将函数取负值。
 * 这里使用的黄金比例是：\f[
 * k=\frac{3-\sqrt{5}}{2} \approx 0.381966\ldots\f]
 *
 * @param f 要寻找最小值的函数
 * @param lim_a 搜索区间的下限
 * @param lim_b 搜索区间的上限
 * @return 在区间内找到的局部最小值
 */
double get_minima(const std::function<double(double)> &f, double lim_a,
                  double lim_b) {
    uint32_t iters = 0;  // 迭代次数
    double c, d;  // 黄金分割法中的两个分割点
    double prev_mean, mean = std::numeric_limits<double>::infinity();  // 当前区间的均值

    // 黄金比例常数
    const double M_GOLDEN_RATIO = (1.f + std::sqrt(5.f)) / 2.f;

    // 确保 lim_a < lim_b
    if (lim_a > lim_b) {
        std::swap(lim_a, lim_b);  // 如果 lim_a > lim_b, 则交换
    } else if (std::abs(lim_a - lim_b) <= EPSILON) {
        std::cerr << "搜索区间必须大于 " << EPSILON << "\n";
        return lim_a;  // 如果区间长度过小，直接返回
    }

    do {
        prev_mean = mean;  // 保存前一个均值

        // 计算黄金分割点
        double ratio = (lim_b - lim_a) / M_GOLDEN_RATIO;
        c = lim_b - ratio;  // 右侧分割点
        d = lim_a + ratio;  // 左侧分割点

        if (f(c) < f(d)) {
            // 如果 f(c) 小于 f(d)，选择左侧区间
            lim_b = d;
        } else {
            // 否则选择右侧区间
            lim_a = c;
        }

        mean = (lim_a + lim_b) / 2.f;  // 更新当前区间的均值
        iters++;  // 迭代次数加1

        // 当区间宽度小于系统精度时停止
    } while (std::abs(lim_a - lim_b) > EPSILON);

    std::cout << " (迭代次数: " << iters << ") ";
    return prev_mean;  // 返回前一个均值，作为最小值
}

/**
 * @brief 测试函数1，寻找函数 \f$f(x)= (x-2)^2\f$ 在区间 \f$[1,5]\f$ 内的最小值
 * \n 期望结果 = 2
 */
void test1() {
    // 定义待优化的函数作为 lambda 函数
    std::function<double(double)> f1 = [](double x) {
        return (x - 2) * (x - 2);
    };

    std::cout << "测试 1.... ";

    double minima = get_minima(f1, 1, 5);  // 调用黄金分割法寻找最小值

    std::cout << minima << "...";

    // 检查最小值是否符合期望值
    assert(std::abs(minima - 2) < EPSILON);
    std::cout << "测试通过\n";
}

/**
 * @brief 测试函数2，寻找函数 \f$f(x)= x^{\frac{1}{x}}\f$ 在区间 \f$[-2,10]\f$ 内的最大值
 * \n 期望结果: \f$e\approx 2.71828182845904509\f$
 */
void test2() {
    // 定义待优化的函数作为 lambda 函数
    // 由于我们在寻找最大值，因此将函数返回值取负值
    std::function<double(double)> func = [](double x) {
        return -std::pow(x, 1.f / x);
    };

    std::cout << "测试 2.... ";

    double minima = get_minima(func, -2, 10);  // 调用黄金分割法寻找最小值

    std::cout << minima << " (" << M_E << ")...";

    // 检查最小值是否符合期望值
    assert(std::abs(minima - M_E) < EPSILON);
    std::cout << "测试通过\n";
}

/**
 * @brief 测试函数3，寻找函数 \f$f(x)= \cos x\f$ 在区间 \f$[0,12]\f$ 内的最大值
 * \n 期望结果: \f$\pi\approx 3.14159265358979312\f$
 */
void test3() {
    // 定义待优化的函数作为 lambda 函数
    // 由于我们在寻找最大值，因此将函数返回值取负值
    std::function<double(double)> func = [](double x) { return std::cos(x); };

    std::cout << "测试 3.... ";

    double minima = get_minima(func, -4, 12);  // 调用黄金分割法寻找最小值

    std::cout << minima << " (" << M_PI << ")...";

    // 检查最小值是否符合期望值
    assert(std::abs(minima - M_PI) < EPSILON);
    std::cout << "测试通过\n";
}

/** 主函数 */
int main() {
    std::cout.precision(9);  // 设置输出精度

    std::cout << "计算使用的机器精度为: " << EPSILON << "\n";

    // 执行三个测试用例
    test1();
    test2();
    test3();

    return 0;
}
