/**
 * @file
 * @brief 一个数值方法，用于方便地[近似积分](https://en.wikipedia.org/wiki/Midpoint_method)
 * @details 该方法的思路是将积分区间分成 N 个子区间，并使用插值点 xi，满足 xi = x0 + i*h，其中 h 为步长，定义为 h = (b-a)/N，a 和 b 分别是积分区间的起点和终点。
 *
 * 我们创建一个 xi 及其对应的 f(xi) 值的表格，并通过以下公式计算积分：I = h * {f(x0+h/2) + f(x1+h/2) + ... + f(xN-1+h/2)}
 *
 * 参数可以通过命令行传递：argv[1] = N，argv[2] = a，argv[3] = b。如果修改了默认值 N=16，a=1，b=3，则会禁用测试/断言。
 *
 * @author [ggkogkou](https://github.com/ggkogkou)
 */
#include <cassert>     /// 用于断言
#include <cmath>       /// 用于数学函数
#include <cstdint>     /// 用于整数分配
#include <cstdlib>     /// 用于 std::atof
#include <functional>  /// 用于 std::function
#include <iostream>    /// 用于 IO 操作
#include <map>         /// 用于 std::map 容器

/**
 * @namespace numerical_methods
 * @brief 数值算法/方法
 */
namespace numerical_methods {
/**
 * @namespace midpoint_rule
 * @brief 实现 [Midpoint 积分法](https://en.wikipedia.org/wiki/Midpoint_method) 的函数
 */
namespace midpoint_rule {
/**
 * @fn double midpoint(const std::int32_t N, const double h, const double a,
 * const std::function<double (double)>& func)
 * @brief Midpoint 积分法的主函数实现
 * @param N 子区间的数量
 * @param h 步长
 * @param a 起始点 x0
 * @param func 需要积分的函数
 * @returns 积分的结果
 */
double midpoint(const std::int32_t N, const double h, const double a,
                const std::function<double(double)>& func) {
    std::map<int, double>
        data_table;  // 存储数据点，键: i, 值: f(xi)
    double xi = a;   // 初始化 xi 为起始点 x0 = a

    // 创建数据表
    // 从 x0 到 xN-1 循环
    double temp = NAN;
    for (std::int32_t i = 0; i < N; i++) {
        temp = func(xi + h / 2);  // 计算 f(xi + h / 2)
        data_table.insert(
            std::pair<std::int32_t, double>(i, temp));  // 插入 i 和 f(xi)
        xi += h;  // 获取下一个点 xi 进行下次迭代
    }

    // 计算积分
    // 记住：{f(x0+h/2) + f(x1+h/2) + ... + f(xN-1+h/2)}
    double evaluate_integral = 0;
    for (std::int32_t i = 0; i < N; i++) evaluate_integral += data_table.at(i);

    // 乘以系数 h
    evaluate_integral *= h;

    // 如果计算结果是 nan，表示用户输入的区间无效
    assert(!std::isnan(evaluate_integral) &&
           "无法计算定积分。请检查输入区间的有效性。\n");
    // 否则返回结果
    return evaluate_integral;
}

/**
 * @brief 用于测试该方法的函数 f(x)
 * @param x 自变量 xi
 * @returns 因变量 yi = f(xi) = sqrt(xi) + ln(xi)
 */
double f(double x) { return std::sqrt(x) + std::log(x); }
/**
 * @brief 用于测试该方法的函数 g(x)
 * @param x 自变量 xi
 * @returns 因变量 yi = g(xi) = e^(-xi) * (4 - xi^2)
 */
double g(double x) { return std::exp(-x) * (4 - std::pow(x, 2)); }
/**
 * @brief 用于测试该方法的函数 k(x)
 * @param x 自变量 xi
 * @returns 因变量 yi = k(xi) = sqrt(2*xi^3 + 3)
 */
double k(double x) { return std::sqrt(2 * std::pow(x, 3) + 3); }
/**
 * @brief 用于测试该方法的函数 l(x)
 * @param x 自变量 xi
 * @returns 因变量 yi = l(xi) = xi + ln(2*xi + 1)
 */
double l(double x) { return x + std::log(2 * x + 1); }

}  // namespace midpoint_rule
}  // namespace numerical_methods

/**
 * @brief 自测试实现
 * @param N 子区间的数量
 * @param h 步长
 * @param a 起始点 x0
 * @param b 积分区间的结束点
 * @param used_argv_parameters 如果使用了 argv 参数，则为 'true'，否则为 'false'
 */
static void test(std::int32_t N, double h, double a, double b,
                 bool used_argv_parameters) {
    // 对每个测试函数 f、g、k、l 调用 midpoint()
    // 断言结果在两位小数的精度范围内
    double result_f = numerical_methods::midpoint_rule::midpoint(
        N, h, a, numerical_methods::midpoint_rule::f);
    assert((used_argv_parameters || (result_f >= 4.09 && result_f <= 4.10)) &&
           "f(x) 的结果错误");
    std::cout << "在区间 [" << a << ", " << b << "] 上，f(x) 的积分结果为: " << result_f << std::endl;

    double result_g = numerical_methods::midpoint_rule::midpoint(
        N, h, a, numerical_methods::midpoint_rule::g);
    assert((used_argv_parameters || (result_g >= 0.27 && result_g <= 0.28)) &&
           "g(x) 的结果错误");
    std::cout << "在区间 [" << a << ", " << b << "] 上，g(x) 的积分结果为: " << result_g << std::endl;

    double result_k = numerical_methods::midpoint_rule::midpoint(
        N, h, a, numerical_methods::midpoint_rule::k);
    assert((used_argv_parameters || (result_k >= 9.06 && result_k <= 9.07)) &&
           "k(x) 的结果错误");
    std::cout << "在区间 [" << a << ", " << b << "] 上，k(x) 的积分结果为: " << result_k << std::endl;

    double result_l = numerical_methods::midpoint_rule::midpoint(
        N, h, a, numerical_methods::midpoint_rule::l);
    assert((used_argv_parameters || (result_l >= 7.16 && result_l <= 7.17)) &&
           "l(x) 的结果错误");
    std::cout << "在区间 [" << a << ", " << b << "] 上，l(x) 的积分结果为: " << result_l << std::endl;
}

/**
 * @brief 主函数
 * @param argc 命令行参数个数（忽略）
 * @param argv 命令行参数数组（忽略）
 * @returns 程序退出时返回 0
 */
int main(int argc, char** argv) {
    std::int32_t N =
        16;  /// 要将积分区间分成的子区间数。必须为偶数
    double a = 1, b = 3;  /// 积分区间的起始和结束点
    double h = NAN;  /// 步长，通过 a、b 和 N 计算

    bool used_argv_parameters =
        false;  // 如果使用了 argv 参数，则禁用测试中的断言

    // 获取用户输入（通过命令行参数或控制台）
    if (argc == 4) {
        N = std::atoi(argv[1]);
        a = std::atof(argv[2]);
        b = std::atof(argv[3]);
        // 检查 a < b，否则中止
        assert(a < b && "a 必须小于 b");
        assert(N > 0 && "N 必须大于 0");
        if (N < 4 || a != 1 || b != 3) {
            used_argv_parameters = true;
        }
        std::cout << "您选择了 N=" << N << ", a=" << a << ", b=" << b << std::endl;
    } else {
        std::cout << "默认值为 N=" << N << ", a=" << a << ", b=" << b << std::endl;
    }

    // 计算步长
    h = (b - a) / N;

    test(N, h, a, b, used_argv_parameters);  // 运行自测试

    return 0;
}
