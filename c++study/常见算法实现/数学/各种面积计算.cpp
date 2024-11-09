/**
 * @file
 * @brief 各种形状的[面积](https://en.wikipedia.org/wiki/Area)实现
 * @details 形状的面积是它占用的二维空间。每种形状都有一个公式来计算其面积。
 * 这些实现支持多种返回类型。
 *
 * @author [Focusucof](https://github.com/Focusucof)
 */
#define _USE_MATH_DEFINES
#include <cassert>  /// 用于 assert 断言
#include <cmath>    /// 用于 M_PI 常量和 pow() 函数
#include <cmath>
#include <cstdint>  /// 用于 uint16_t 数据类型
#include <iostream> /// 用于 IO 操作

/**
 * @namespace math
 * @brief 数学算法命名空间
 */
namespace math {
/**
 * @brief 计算[正方形](https://en.wikipedia.org/wiki/Square)的面积 (l * l)
 * @param length 正方形的边长
 * @returns 正方形的面积
 */
template <typename T>
T square_area(T length) {
    return length * length;
}

/**
 * @brief 计算[矩形](https://en.wikipedia.org/wiki/Rectangle)的面积 (l * w)
 * @param length 矩形的长
 * @param width 矩形的宽
 * @returns 矩形的面积
 */
template <typename T>
T rect_area(T length, T width) {
    return length * width;
}

/**
 * @brief 计算[三角形](https://en.wikipedia.org/wiki/Triangle)的面积 (b * h / 2)
 * @param base 三角形的底边长度
 * @param height 三角形的高
 * @returns 三角形的面积
 */
template <typename T>
T triangle_area(T base, T height) {
    return base * height / 2;
}

/**
 * @brief 计算[圆](https://en.wikipedia.org/wiki/Area_of_a_circle)的面积 (pi * r^2)
 * @param radius 圆的半径
 * @returns 圆的面积
 */
template <typename T>
T circle_area(T radius) {
    return M_PI * pow(radius, 2);
}

/**
 * @brief 计算[平行四边形](https://en.wikipedia.org/wiki/Parallelogram)的面积 (b * h)
 * @param base 平行四边形的底边长度
 * @param height 平行四边形的高
 * @returns 平行四边形的面积
 */
template <typename T>
T parallelogram_area(T base, T height) {
    return base * height;
}

/**
 * @brief 计算[立方体](https://en.wikipedia.org/wiki/Cube)的表面积 (6 * (l * l))
 * @param length 立方体的边长
 * @returns 立方体的表面积
 */
template <typename T>
T cube_surface_area(T length) {
    return 6 * length * length;
}

/**
 * @brief 计算[球体](https://en.wikipedia.org/wiki/Sphere)的表面积 (4 * pi * r^2)
 * @param radius 球体的半径
 * @returns 球体的表面积
 */
template <typename T>
T sphere_surface_area(T radius) {
    return 4 * M_PI * pow(radius, 2);
}

/**
 * @brief 计算[圆柱体](https://en.wikipedia.org/wiki/Cylinder)的表面积 (2 * pi * r * h + 2 * pi * r^2)
 * @param radius 圆柱体的半径
 * @param height 圆柱体的高
 * @returns 圆柱体的表面积
 */
template <typename T>
T cylinder_surface_area(T radius, T height) {
    return 2 * M_PI * radius * height + 2 * M_PI * pow(radius, 2);
}

/**
 * @brief 计算[半球体](https://en.wikipedia.org/wiki/Surface_area)的表面积 (3 * pi * r^2)
 * @param radius 半球体的半径
 * @tparam T 半径的数据类型
 * @returns 半球体的表面积
 */
template <typename T>
T hemi_sphere_surface_area(T radius) {
    return 3 * M_PI * pow(radius, 2);
}
}  // namespace math

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    // 测试所需的 I/O 变量
    uint16_t int_length = 0;    // 16 位整数长度输入
    uint16_t int_width = 0;     // 16 位整数宽度输入
    uint16_t int_base = 0;      // 16 位整数底边输入
    uint16_t int_height = 0;    // 16 位整数高输入
    uint16_t int_expected = 0;  // 16 位整数预期输出
    uint16_t int_area = 0;      // 16 位整数实际输出

    float float_length = NAN;    // 浮点型长度输入
    float float_expected = NAN;  // 浮点型预期输出
    float float_area = NAN;      // 浮点型实际输出

    double double_length = NAN;    // 双精度型长度输入
    double double_width = NAN;     // 双精度型宽度输入
    double double_radius = NAN;    // 双精度型半径输入
    double double_height = NAN;    // 双精度型高输入
    double double_expected = NAN;  // 双精度型预期输出
    double double_area = NAN;      // 双精度型实际输出

    // 测试各个函数并验证结果是否正确
    // 1st test: 正方形面积 (int)
    int_length = 5;
    int_expected = 25;
    int_area = math::square_area(int_length);
    std::cout << "正方形面积 (int)" << std::endl;
    std::cout << "输入边长: " << int_length << std::endl;
    std::cout << "预期输出: " << int_expected << std::endl;
    std::cout << "实际输出: " << int_area << std::endl;
    assert(int_area == int_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 2nd test: 正方形面积 (float)
    float_length = 2.5;
    float_expected = 6.25;
    float_area = math::square_area(float_length);
    std::cout << "正方形面积 (float)" << std::endl;
    std::cout << "输入边长: " << float_length << std::endl;
    std::cout << "预期输出: " << float_expected << std::endl;
    std::cout << "实际输出: " << float_area << std::endl;
    assert(float_area == float_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 更多测试代码...

    // 11th test: 半球体表面积
    double_radius = 10.0;
    double_expected = 942.4777960769379;
    double_area = math::hemi_sphere_surface_area(double_radius);
    std::cout << "半球体表面积" << std::endl;
    std::cout << "输入半径: " << double_radius << std::endl;
    std::cout << "预期输出: " << double_expected << std::endl;
    std::cout << "实际输出: " << double_area << std::endl;
    assert(double_area == double_expected);
    std::cout << "测试通过" << std::endl << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 正常退出
 */
int main() {
    test();  // 运行自测实现
    return 0;
}
