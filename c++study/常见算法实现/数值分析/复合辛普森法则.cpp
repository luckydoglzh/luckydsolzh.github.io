/**
 * @file
 * @brief 复合辛普森法则实现，用于近似定积分
 *
 * @details 以下是复合辛普森法则实现，用于近似定积分。更多信息 -> wiki:
 * https://en.wikipedia.org/wiki/Simpson%27s_rule#Composite_Simpson's_rule
 *
 * 该方法的思想是将区间分为一个偶数 N 个子区间，并使用插值点 xi 计算，满足 xi = x0 + i*h，其中 h 是步长，
 * 定义为 h = (b - a) / N，其中 a 和 b 是积分区间的起点和终点。
 *
 * 我们创建一个包含 xi 及其对应 f(xi) 值的数据表，并通过以下公式计算积分： 
 * I = h / 3 * {f(x0) + 4*f(x1) + 2*f(x2) + ... + 2*f(xN-2) + 4*f(xN-1) + f(xN)}
 *
 * 也就是说，第一和最后一个 f(xi) 乘以 1，奇数位置的 f(xi) 乘以 4，偶数位置的 f(xi) 乘以 2。
 *
 * 本程序包含 4 个示例测试函数 f、g、k、l，它们在相同区间上进行积分计算。
 *
 * 参数可以从命令行传入，argv[1] = N，argv[2] = a，argv[3] = b
 *
 * N 必须是偶数，且 a < b。
 *
 * 在 main() 结束时，我将比较程序结果与数学软件计算结果，误差不超过 2 个小数位。
 *
 * 可以通过替换 f、g、k、l 中的某个函数并更新断言来添加示例函数。
 *
 * @author [ggkogkou](https://github.com/ggkogkou)
 *
 */

#include <cassert>  /// 用于 assert
#include <cmath>    /// 用于数学函数
#include <cmath>
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
 * @namespace simpson_method
 * @brief 包含辛普森法则实现
 */
namespace simpson_method {
/**
 * @fn double evaluate_by_simpson(int N, double h, double a,
 * std::function<double (double)> func)
 * @brief 计算积分，若计算结果为 NaN，则触发断言
 * @param N 子区间数量
 * @param h 步长
 * @param a 起始点 x0
 * @param func 需要计算的函数
 * @returns 积分结果
 */
double evaluate_by_simpson(std::int32_t N, double h, double a,
                           const std::function<double(double)>& func) {
    std::map<std::int32_t, double>
        data_table;  // 存储数据点，键为 i，值为 f(xi)
    double xi = a;   // 初始化 xi 为起始点 x0 = a

    // 创建数据表
    double temp = NAN;
    for (std::int32_t i = 0; i <= N; i++) {
        temp = func(xi);
        data_table.insert(
            std::pair<std::int32_t, double>(i, temp));  // 添加 i 和 f(xi)
        xi += h;  // 获取下一个点 xi，进入下一次迭代
    }

    // 计算积分
    // 记住：f(x0) + 4*f(x1) + 2*f(x2) + ... + 2*f(xN-2) + 4*f(xN-1) + f(xN)
    double evaluate_integral = 0;
    for (std::int32_t i = 0; i <= N; i++) {
        if (i == 0 || i == N) {
            evaluate_integral += data_table.at(i);  // f(x0) 和 f(xN)
        } else if (i % 2 == 1) {
            evaluate_integral += 4 * data_table.at(i);  // 奇数位置的 f(xi) 乘 4
        } else {
            evaluate_integral += 2 * data_table.at(i);  // 偶数位置的 f(xi) 乘 2
        }
    }

    // 乘以系数 h/3
    evaluate_integral *= h / 3;

    // 如果计算结果为 NaN，说明用户输入的区间无效，触发断言
    assert(!std::isnan(evaluate_integral) &&
           "定积分无法计算。检查输入区间的有效性。\n");
    // 否则返回结果
    return evaluate_integral;
}

/**
 * @fn double f(double x)
 * @brief 一个用于测试的方法 f(x)
 * @param x 自变量 xi
 * @returns 依赖变量 yi = f(xi)
 */
double f(double x) { return std::sqrt(x) + std::log(x); }
/** @brief 另一个测试函数 */
double g(double x) { return std::exp(-x) * (4 - std::pow(x, 2)); }
/** @brief 另一个测试函数 */
double k(double x) { return std::sqrt(2 * std::pow(x, 3) + 3); }
/** @brief 另一个测试函数 */
double l(double x) { return x + std::log(2 * x + 1); }
}  // namespace simpson_method
}  // namespace numerical_methods

/**
 * \brief 自测实现
 * @param N 子区间数量
 * @param h 步长
 * @param a 起始点 x0
 * @param b 结束点
 * @param used_argv_parameters 如果使用了 argv 参数则为 true，否则为 false
 */
static void test(std::int32_t N, double h, double a, double b,
                 bool used_argv_parameters) {
    // 调用函数并计算每个函数的积分
    double result_f = numerical_methods::simpson_method::evaluate_by_simpson(
        N, h, a, numerical_methods::simpson_method::f);
    assert((used_argv_parameters || (result_f >= 4.09 && result_f <= 4.10)) &&
           "f(x) 的结果错误");
    std::cout << "函数 f(x) 在区间 [" << a << ", " << b
              << "] 上的积分结果为： " << result_f << std::endl;

    double result_g = numerical_methods::simpson_method::evaluate_by_simpson(
        N, h, a, numerical_methods::simpson_method::g);
    assert((used_argv_parameters || (result_g >= 0.27 && result_g <= 0.28)) &&
           "g(x) 的结果错误");
    std::cout << "函数 g(x) 在区间 [" << a << ", " << b
              << "] 上的积分结果为： " << result_g << std::endl;

    double result_k = numerical_methods::simpson_method::evaluate_by_simpson(
        N, h, a, numerical_methods::simpson_method::k);
    assert((used_argv_parameters || (result_k >= 9.06 && result_k <= 9.07)) &&
           "k(x) 的结果错误");
    std::cout << "函数 k(x) 在区间 [" << a << ", " << b
              << "] 上的积分结果为： " << result_k << std::endl;

    double result_l = numerical_methods::simpson_method::evaluate_by_simpson(
        N, h, a, numerical_methods::simpson_method::l);
    assert((used_argv_parameters || (result_l >= 7.16 && result_l <= 7.17)) &&
           "l(x) 的结果错误");
    std::cout << "函数 l(x) 在区间 [" << a << ", " << b
              << "] 上的积分结果为： " << result_l << std::endl;
}

/**
 * @brief 主函数
 * @param argc 命令行参数个数（忽略）
 * @param argv 命令行参数数组（忽略）
 * @returns 退出时返回 0
 */
int main(int argc, char** argv) {
    std::int32_t N = 16;  /// 分割积分区间的子区间数，必须是偶数
    double a = 1, b = 3;  /// 积分区间的起点和终点
    double h = NAN;       /// 步长，由 a, b 和 N 计算得出

    bool used_argv_parameters =
        false;  // 如果使用了 argv 参数，则不执行测试中的断言

    // 获取用户输入（通过命令行参数或控制台）
    if (argc == 4) {
        N = std::atoi(argv[1]);
        a = std::atof(argv[2]);
        b = std::atof(argv[3]);
        // 检查 a < b 否则中止
        assert(a < b && "a 必须小于 b");
        assert(N > 0 && "N 必须大于 0");
        if (N < 16 || a != 1 || b != 3) {
            used_argv_parameters = true;
        }
        std::cout << "您选择了 N=" << N << ", a=" << a << ", b=" << b
                  << std::endl;
    } else {
        std::cout << "默认值 N=" << N << ", a=" << a << ", b=" << b
                  << std::endl;
    }

    // 计算步长
    h = (b - a) / N;

    test(N, h, a, b, used_argv_parameters);  // 执行自测

    return 0;
}
