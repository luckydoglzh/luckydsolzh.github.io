/**
 * @file
 * @brief 实现[快速逆平方根](https://medium.com/hard-mode/the-legendary-fast-inverse-square-root-e51fee3b49d9)算法
 * @details
 * 包含两种方法来计算逆平方根，一个是来自 Quake III Arena 的实现（C++ 版本），
 * 另一个是标准库实现（使用 `cmath`）。
 * 这个算法在 Quake III Arena 中用于计算阴影效果。
 */

#include <cassert>   // 用于断言
#include <cmath>     // 用于 `std::sqrt`
#include <iostream>  // 用于输入输出操作
#include <limits>    // 用于 numeric_limits

/**
 * @brief 计算快速逆平方根的函数。
 * 这是 Quake III Arena 的快速逆平方根实现（适配为 C++）。
 * 更多信息可以参考[维基百科](https://en.wikipedia.org/wiki/Fast_inverse_square_root)
 * @tparam T 浮点类型
 * @tparam iterations 迭代次数，迭代次数越多，结果越精确（1 或 2 次）
 * @param x 需要计算的值
 * @return 逆平方根的计算结果
 */
template <typename T = double, char iterations = 2>
inline T Fast_InvSqrt(T x) {
    using Tint = typename std::conditional<sizeof(T) == 8, std::int64_t,
                                           std::int32_t>::type;
    T y = x;
    T x2 = y * 0.5;

    Tint i =
        *reinterpret_cast<Tint *>(&y);  // 将浮点数的位模式存储到整数中

    i = (sizeof(T) == 8 ? 0x5fe6eb50c7b537a9 : 0x5f3759df) -
        (i >> 1);  // 使用牛顿迭代法的初始猜测

    y = *reinterpret_cast<T *>(&i);  // 将新位模式转换回浮点数

    y = y * (1.5 - (x2 * y * y));  // 牛顿迭代法第1次迭代
    if (iterations == 2) {
        y = y * (1.5 - (x2 * y * y));  // 牛顿迭代法第2次迭代，使结果更精确
    }
    return y;
}

/**
 * @brief 使用标准库实现的快速逆平方根计算函数。
 * 这个实现使用了标准库中的 `sqrt` 函数。
 * 更多信息可以参考[LinkedIn](https://www.linkedin.com/pulse/fast-inverse-square-root-still-armin-kassemi-langroodi)
 * @tparam T 浮点类型
 * @param number 需要计算的值
 * @return 逆平方根的计算结果
 */
template <typename T = double>
T Standard_InvSqrt(T number) {
    T squareRoot = sqrt(number);
    return 1.0f / squareRoot;
}

/**
 * @brief 自测试实现
 * @returns void
 */
static void test() {
    const float epsilon = 1e-3f;  // 允许的误差范围

    /* 多个测试值 */
    assert(std::fabs(Standard_InvSqrt<float>(100.0f) - 0.0998449f) < epsilon);
    assert(std::fabs(Standard_InvSqrt<double>(36.0f) - 0.166667f) < epsilon);
    assert(std::fabs(Standard_InvSqrt(12.0f) - 0.288423f) < epsilon);
    assert(std::fabs(Standard_InvSqrt<double>(5.0f) - 0.447141f) < epsilon);

    assert(std::fabs(Fast_InvSqrt<float, 1>(100.0f) - 0.0998449f) < epsilon);
    assert(std::fabs(Fast_InvSqrt<double, 1>(36.0f) - 0.166667f) < epsilon);
    assert(std::fabs(Fast_InvSqrt(12.0f) - 0.288423) < epsilon);
    assert(std::fabs(Fast_InvSqrt<double>(5.0f) - 0.447141) < epsilon);
}

/**
 * @brief 主函数
 * @returns 0 表示程序正常退出
 */
int main() {
    test();  // 运行自测试函数
    std::cout << "36 的快速逆平方根（1 次迭代）: "
              << Fast_InvSqrt<float, 1>(36.0f) << std::endl;
    std::cout << "36 的快速逆平方根（2 次迭代）: "
              << Fast_InvSqrt<double, 2>(36.0f) << " (2 次迭代)"
              << std::endl;
    std::cout << "100 的快速逆平方根: "
              << Fast_InvSqrt(100.0f)
              << " (默认模板类型和迭代次数: double, 2)"
              << std::endl;
    std::cout << "36 的标准逆平方根: "
              << Standard_InvSqrt<float>(36.0f) << std::endl;
    std::cout << "100 的标准逆平方根: "
              << Standard_InvSqrt(100.0f)
              << " (默认模板类型: double)" << std::endl;
}
