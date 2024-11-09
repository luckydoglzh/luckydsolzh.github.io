/**
 * @{
 * \file
 * \brief [Runge Kutta 四阶法](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods) 的实现
 *
 * \author [Rudra Prasad Das](http://github.com/rudra697)
 *
 * \details
 * 该方法用于求解已知 x 值时 y 的值
 * 仅支持求解一阶常微分方程
 * \example
 * 它可以求解方程 \(\frac{\mathrm{d} y}{\mathrm{d} x} = \frac{(x - y)}{2}\)
 * 给定 x 和初始条件时的解
 * 可以有多种类似的方程
 */
#include <cassert>   /// 用于断言测试函数
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于使用 vector 容器

/**
 * @brief change() 函数用于返回对应函数给定 x, y 值的更新后的迭代值
 * @param x 对应 x 坐标的值
 * @param y 对应 y 坐标的值
 * @returns 该次调用中计算的函数值
 */
static double change(double x, double y) { return ((x - y) / 2.0); }

/**
 * @namespace numerical_methods
 * @brief 数值方法
 */
namespace numerical_methods {
/**
 * @namespace runge_kutta
 * @brief [Runge Kutta 四阶法](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods) 的相关函数
 */
namespace runge_kutta {
/**
 * @brief Runge Kutta 方法通过给定的上下限，找到积分函数在给定 x 值的结果
 * 初始值作为积分下限，x 为积分上限
 * @param init_x 初始值 x，每次调用后都会更新
 * @param init_y 初始值 y，每次调用后都会更新
 * @param x 当前迭代需要计算的 x 值
 * @param h 步长
 * @returns 从初始条件计算得到的 y 在给定 x 值时的结果
 */
double rungeKutta(double init_x, const double &init_y, const double &x,
                  const double &h) {
    // 计算迭代次数，使用步长 h
    // n 计算迭代的次数
    // k1, k2, k3, k4 是 Runge Kutta 算法中的变量，用于每次迭代计算 y 的值

    auto n = static_cast<uint64_t>((x - init_x) / h);
    // 使用 vector 容器存储变量 k
    std::vector<double> k(4, 0.0);

    // 初始化 y 为初始值
    double y = init_y;
    // 迭代计算 y 的值
    for (int i = 1; i <= n; ++i) {
        // 应用 Runge Kutta 公式计算下一个 y 值
        k[0] = h * change(init_x, y);
        k[1] = h * change(init_x + 0.5 * h, y + 0.5 * k[0]);
        k[2] = h * change(init_x + 0.5 * h, y + 0.5 * k[1]);
        k[3] = h * change(init_x + h, y + k[2]);

        // 更新 y 的值
        y += (1.0 / 6.0) * (k[0] + 2 * k[1] + 2 * k[2] + k[3]);

        // 更新 x 的值
        init_x += h;
    }

    // 返回最终计算出的 y 值
    return y;
}
}  // namespace runge_kutta
}  // namespace numerical_methods

/**
 * @brief 测试函数，用于检查算法实现
 * @returns void
 */
static void test() {
    std::cout << "Runge Kutta 函数将根据预计算值进行测试\n";

    std::cout << "测试 1...."
              << "\n";
    double valfirst = numerical_methods::runge_kutta::rungeKutta(
        2, 3, 4, 0.2);  // 使用预计算值测试该函数
    assert(valfirst == 3.10363932323749570);  // 判断计算结果是否符合预期
    std::cout << "通过 测试 1\n";

    std::cout << "测试 2...."
              << "\n";
    double valsec = numerical_methods::runge_kutta::rungeKutta(
        1, 2, 5, 0.1);  // 修改步长进行测试
    assert(valsec == 3.40600589380261409);  // 判断计算结果是否符合预期
    std::cout << "通过 测试 2\n";

    std::cout << "测试 3...."
              << "\n";
    double valthird = numerical_methods::runge_kutta::rungeKutta(
        -1, 3, 4, 0.1);  // 测试负值
    assert(valthird == 2.49251005860244268);  // 判断计算结果是否符合预期
    std::cout << "通过 测试 3\n";
}

/**
 * @brief 主函数
 * @returns 0 正常退出
 */
int main() {
    test();  // 执行测试
    return 0;
}
