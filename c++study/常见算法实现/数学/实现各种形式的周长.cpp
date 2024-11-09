/**
 * @file
 * @brief 实现各种形状的 [周长](https://en.wikipedia.org/wiki/Perimeter) 计算
 * @details 计算几何形状的周长。每种形状都有其计算周长的公式。
 * 这些实现支持多种返回类型。
 *
 * @author [OGscorpion](https://github.com/OGscorpion)
 */
#define _USE_MATH_DEFINES
#include <cassert>   /// 用于断言
#include <cmath>     /// 用于 M_PI 定义和 pow() 函数
#include <cstdint>   /// 用于 uint16_t 数据类型
#include <iostream>  /// 用于输入输出操作

/**
 * @namespace math
 * @brief 数学算法
 */
namespace math {
/**
 * @brief 计算正方形的周长 (4 * 边长)
 * @param length 正方形的边长
 * @returns 正方形的周长
 */
template <typename T>
T square_perimeter(T length) {
    return 4 * length;
}

/**
 * @brief 计算矩形的周长 (2 * (长 + 宽))
 * @param length 矩形的长
 * @param width 矩形的宽
 * @returns 矩形的周长
 */
template <typename T>
T rect_perimeter(T length, T width) {
    return 2 * (length + width);
}

/**
 * @brief 计算三角形的周长 (a + b + c)
 * @param base 三角形的底边长度
 * @param height 三角形的高度
 * @param hypotenuse 三角形的斜边长度
 * @returns 三角形的周长
 */
template <typename T>
T triangle_perimeter(T base, T height, T hypotenuse) {
    return base + height + hypotenuse;
}

/**
 * @brief 计算圆的周长 (2 * pi * 半径)
 * @param radius 圆的半径
 * @returns 圆的周长
 */
template <typename T>
T circle_perimeter(T radius) {
    return 2 * M_PI * radius;
}

/**
 * @brief 计算平行四边形的周长 (2 * (底边 + 高))
 * @param base 平行四边形的底边
 * @param height 平行四边形的高
 * @returns 平行四边形的周长
 */
template <typename T>
T parallelogram_perimeter(T base, T height) {
    return 2 * (base + height);
}

/**
 * @brief 计算立方体的表面周长 (12 * 边长)
 * @param length 立方体的边长
 * @returns 立方体的表面周长
 */
template <typename T>
T cube_surface_perimeter(T length) {
    return 12 * length;
}

/**
 * @brief 计算 n 边形的表面周长 (n * 边长)
 * @param sides n 边形的边数
 * @param length 每条边的长度
 * @returns n 边形的表面周长
 */
template <typename T>
T n_polygon_surface_perimeter(T sides, T length) {
    return sides * length;
}

/**
 * @brief 计算圆柱体的表面周长 (2 * 半径 + 2 * 高)
 * @param radius 圆柱体的半径
 * @param height 圆柱体的高度
 * @returns 圆柱体的表面周长
 */
template <typename T>
T cylinder_surface_perimeter(T radius, T height) {
    return (2 * radius) + (2 * height);
}
}  // namespace math

/**
 * @brief 自测函数
 * @returns void
 */
static void test() {
    // 测试时的输入输出变量
    uint16_t int_length = 0;      // 16 位整数边长输入
    uint16_t int_width = 0;       // 16 位整数宽度输入
    uint16_t int_base = 0;        // 16 位整数底边输入
    uint16_t int_height = 0;      // 16 位整数高度输入
    uint16_t int_hypotenuse = 0;  // 16 位整数斜边输入
    uint16_t int_sides = 0;       // 16 位整数边数输入
    uint16_t int_expected = 0;    // 16 位整数预期输出
    uint16_t int_perimeter = 0;   // 16 位整数输出

    float float_length = NAN;     // 浮动边长输入
    float float_expected = NAN;   // 浮动预期输出
    float float_perimeter = NAN;  // 浮动输出

    double double_length = NAN;     // 双精度浮动边长输入
    double double_width = NAN;      // 双精度浮动宽度输入
    double double_radius = NAN;     // 双精度浮动半径输入
    double double_height = NAN;     // 双精度浮动高度输入
    double double_expected = NAN;   // 双精度浮动预期输出
    double double_perimeter = NAN;  // 双精度浮动输出

    // 1st 测试
    int_length = 5;
    int_expected = 20;
    int_perimeter = math::square_perimeter(int_length);

    std::cout << "正方形的周长 (int)" << std::endl;
    std::cout << "输入边长: " << int_length << std::endl;
    std::cout << "预期输出: " << int_expected << std::endl;
    std::cout << "输出: " << int_perimeter << std::endl;
    assert(int_perimeter == int_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 2nd 测试
    float_length = 2.5;
    float_expected = 10;
    float_perimeter = math::square_perimeter(float_length);

    std::cout << "正方形的周长 (float)" << std::endl;
    std::cout << "输入边长: " << float_length << std::endl;
    std::cout << "预期输出: " << float_expected << std::endl;
    std::cout << "输出: " << float_perimeter << std::endl;
    assert(float_perimeter == float_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 3rd 测试
    int_length = 4;
    int_width = 7;
    int_expected = 22;
    int_perimeter = math::rect_perimeter(int_length, int_width);

    std::cout << "矩形的周长 (int)" << std::endl;
    std::cout << "输入边长: " << int_length << std::endl;
    std::cout << "输入宽度: " << int_width << std::endl;
    std::cout << "预期输出: " << int_expected << std::endl;
    std::cout << "输出: " << int_perimeter << std::endl;
    assert(int_perimeter == int_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 4th 测试
    double_length = 2.5;
    double_width = 5.7;
    double_expected = 16.4;
    double_perimeter = math::rect_perimeter(double_length, double_width);

    std::cout << "矩形的周长 (double)" << std::endl;
    std::cout << "输入边长: " << double_length << std::endl;
    std::cout << "输入宽度: " << double_width << std::endl;
    std::cout << "预期输出: " << double_expected << std::endl;
    std::cout << "输出: " << double_perimeter << std::endl;
    assert(double_perimeter == double_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 5th 测试
    int_base = 10;
    int_height = 3;
    int_hypotenuse = 5;
    int_expected = 18;
    int_perimeter =
        math::triangle_perimeter(int_base, int_height, int_hypotenuse);

    std::cout << "三角形的周长" << std::endl;
    std::cout << "输入底边: " << int_base << std::endl;
    std::cout << "输入高度: " << int_height << std::endl;
    std::cout << "预期输出: " << int_expected << std::endl;
    std::cout << "输出: " << int_perimeter << std::endl;
    assert(int_perimeter == int_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 6th 测试
    double_radius = 6;
    double_expected =
        37.69911184307752;  // 因为 double 数据类型会截断到 14 位小数
    double_perimeter = math::circle_perimeter(double_radius);

    std::cout << "圆的周长" << std::endl;
    std::cout << "输入半径: " << double_radius << std::endl;
    std::cout << "预期输出: " << double_expected << std::endl;
    std::cout << "输出: " << double_perimeter << std::endl;
    assert(double_perimeter == double_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 7th 测试
    int_sides = 6;
    int_length = 5;
    int_expected = 30;
    int_perimeter = math::n_polygon_surface_perimeter(int_sides, int_length);

    std::cout << "正六边形的周长" << std::endl;
    std::cout << "输入边数: " << int_sides << std::endl;
    std::cout << "输入边长: " << int_length << std::endl;
    std::cout << "预期输出: " << int_expected << std::endl;
    std::cout << "输出: " << int_perimeter << std::endl;
    assert(int_perimeter == int_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 8th 测试
    double_radius = 4.5;
    double_height = 8.2;
    double_expected = 24.4;
    double_perimeter = math::cylinder_surface_perimeter(double_radius, double_height);

    std::cout << "圆柱体的周长" << std::endl;
    std::cout << "输入半径: " << double_radius << std::endl;
    std::cout << "输入高度: " << double_height << std::endl;
    std::cout << "预期输出: " << double_expected << std::endl;
    std::cout << "输出: " << double_perimeter << std::endl;
    assert(double_perimeter == double_expected);
    std::cout << "测试通过" << std::endl;
}

/**
 * @brief 主程序入口
 * @param argc 参数个数
 * @param argv 参数数组
 * @returns 退出代码
 */
int main(int argc, char** argv) {
    test();
    return 0;
}
