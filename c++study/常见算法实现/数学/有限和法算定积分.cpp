/**
 * @file
 * @brief 使用[Riemann和](https://en.wikipedia.org/wiki/Riemann_sum)计算函数的积分近似
 * @details 在数学中，Riemann和是一种通过有限和来近似积分的方法。
 * Riemann和通过将区域划分为小的形状（矩形、梯形等）并计算每个小形状的面积，
 * 然后将这些小面积相加得到近似的面积。
 * 通过逐步缩小这些形状的大小，可以使得和的值接近于Riemann积分。
 * \author [Benjamin Walton](https://github.com/bwalton24)
 * \author [Shiqi Sheng](https://github.com/shiqisheng00)
 */
#include <cassert>       // 用于断言
#include <cmath>         // 用于数学函数
#include <functional>    // 用于传入函数
#include <iostream>      // 用于输入输出操作

/**
 * @namespace math
 * @brief 数学函数命名空间
 */
namespace math {
/**
 * @brief 计算函数的积分近似值
 * @param lb 积分的下限
 * @param ub 积分的上限
 * @param func 要进行积分的函数
 * @param delta 每个分区的宽度
 * @returns 函数在 [lb, ub] 上的积分近似值
 */
double integral_approx(double lb, double ub,
                       const std::function<double(double)>& func,
                       double delta = .0001) {
    double result = 0;
    uint64_t numDeltas = static_cast<uint64_t>((ub - lb) / delta);  // 分区数量
    for (int i = 0; i < numDeltas; i++) {
        double begin = lb + i * delta;
        double end = lb + (i + 1) * delta;
        result += delta * (func(begin) + func(end)) / 2;  // 使用梯形面积
    }
    return result;
}

/**
 * @brief 测试结果是否在预设的误差范围内
 * @param approx 近似值
 * @param exact 预期的确切值
 * @param threshold 误差范围 [0, 1)
 */
void test_eval(double approx, double expected, double threshold) {
    assert(approx >= expected * (1 - threshold));  // 检查是否在误差范围内
    assert(approx <= expected * (1 + threshold));
}

/**
 * @brief 测试 `integral_approx` 函数的自测试实现
 * @returns `void`
 */
}  // namespace math

// 测试函数
static void test() {
    double test_1 = math::integral_approx(
        3.24, 7.56, [](const double x) { return log(x) + exp(x) + x; });
    std::cout << "测试案例 1" << std::endl;
    std::cout << "函数: log(x) + e^x + x" << std::endl;
    std::cout << "范围: [3.24, 7.56]" << std::endl;
    std::cout << "值: " << test_1 << std::endl;
    math::test_eval(test_1, 1924.80384023549, .001);
    std::cout << "测试 1 通过!" << std::endl;
    std::cout << "=====================" << std::endl;

    double test_2 = math::integral_approx(0.023, 3.69, [](const double x) {
        return x * x + cos(x) + exp(x) + log(x) * log(x);
    });
    std::cout << "测试案例 2" << std::endl;
    std::cout << "函数: x^2 + cos(x) + e^x + log^2(x)" << std::endl;
    std::cout << "范围: [.023, 3.69]" << std::endl;
    std::cout << "值: " << test_2 << std::endl;
    math::test_eval(test_2, 58.71291345202729, .001);
    std::cout << "测试 2 通过!" << std::endl;
    std::cout << "=====================" << std::endl;

    double test_3 = math::integral_approx(
        10.78, 24.899, [](const double x) { return x * x * x - x * x + 378; });
    std::cout << "测试案例 3" << std::endl;
    std::cout << "函数: x^3 - x^2 + 378" << std::endl;
    std::cout << "范围: [10.78, 24.899]" << std::endl;
    std::cout << "值: " << test_3 << std::endl;
    math::test_eval(test_3, 93320.65915078377, .001);
    std::cout << "测试 3 通过!" << std::endl;
    std::cout << "=====================" << std::endl;

    double test_4 = math::integral_approx(
        .101, .505,
        [](const double x) { return cos(x) * tan(x) * x * x + exp(x); },
        .00001);
    std::cout << "测试案例 4" << std::endl;
    std::cout << "函数: cos(x)*tan(x)*x^2 + e^x" << std::endl;
    std::cout << "范围: [.101, .505]" << std::endl;
    std::cout << "值: " << test_4 << std::endl;
    math::test_eval(test_4, 0.566485986311631, .001);
    std::cout << "测试 4 通过!" << std::endl;
    std::cout << "=====================" << std::endl;

    double test_5 = math::integral_approx(
        -1, 1, [](const double x) { return exp(-1 / (x * x)); });
    std::cout << "测试案例 5" << std::endl;
    std::cout << "函数: e^(-1/x^2)" << std::endl;
    std::cout << "范围: [-1, 1]" << std::endl;
    std::cout << "值: " << test_5 << std::endl;
    math::test_eval(test_5, 0.1781477117815607, .001);
    std::cout << "测试 5 通过!" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main() {
    test();  // 运行自测函数
    return 0;
}
