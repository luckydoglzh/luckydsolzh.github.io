/**
 * @file
 * @brief 实现了多种 3D 形状的 [体积](https://en.wikipedia.org/wiki/Volume) 计算。
 * @details 3D 形状的体积是形状占据的 3D 空间的量。所有形状都有公式可以计算出其体积。
 * 这些实现支持多种返回类型。
 *
 * @author [Focusucof](https://github.com/Focusucof)
 */

#include <cassert>   /// 用于断言
#include <cmath>     /// 用于 std::pow
#include <cstdint>   /// 用于 std::uint32_t
#include <iostream>  /// 用于输入输出操作

/**
 * @namespace math
 * @brief 数学算法
 */
namespace math {
/**
 * @brief 计算 [立方体](https://en.wikipedia.org/wiki/Cube) 的体积
 * @param length 立方体的边长
 * @returns 立方体的体积
 */
template <typename T>
T cube_volume(T length) {
    return std::pow(length, 3);  // 立方体体积公式：边长的三次方
}

/**
 * @brief 计算 [长方体](https://en.wikipedia.org/wiki/Cuboid) 的体积
 * @param length 长方体的底面长
 * @param width 长方体的底面宽
 * @param height 长方体的高度
 * @returns 长方体的体积
 */
template <typename T>
T rect_prism_volume(T length, T width, T height) {
    return length * width * height;  // 长方体体积公式：长 * 宽 * 高
}

/**
 * @brief 计算 [圆锥](https://en.wikipedia.org/wiki/Cone) 的体积
 * @param radius 圆锥底面的半径
 * @param height 圆锥的高度
 * @param PI 圆周率，默认为 3.14
 * @returns 圆锥的体积
 */
template <typename T>
T cone_volume(T radius, T height, double PI = 3.14) {
    return std::pow(radius, 2) * PI * height / 3;  // 圆锥体积公式：π * 半径的平方 * 高 / 3
}

/**
 * @brief 计算 [三角柱体](https://en.wikipedia.org/wiki/Triangular_prism) 的体积
 * @param base 底面三角形的底边长
 * @param height 底面三角形的高
 * @param depth 三角柱体的深度（即整体高度）
 * @returns 三角柱体的体积
 */
template <typename T>
T triangle_prism_volume(T base, T height, T depth) {
    return base * height * depth / 2;  // 三角柱体体积公式：底边 * 高 * 深度 / 2
}

/**
 * @brief 计算 [金字塔](https://en.wikipedia.org/wiki/Pyramid_(geometry)) 的体积
 * @param length 基座的长度
 * @param width 基座的宽度
 * @param height 金字塔的高度
 * @returns 金字塔的体积
 */
template <typename T>
T pyramid_volume(T length, T width, T height) {
    return length * width * height / 3;  // 金字塔体积公式：长 * 宽 * 高 / 3
}

/**
 * @brief 计算 [球体](https://en.wikipedia.org/wiki/Sphere) 的体积
 * @param radius 球的半径
 * @param PI 圆周率，默认为 3.14
 * @returns 球体的体积
 */
template <typename T>
T sphere_volume(T radius, double PI = 3.14) {
    return PI * std::pow(radius, 3) * 4 / 3;  // 球体积公式：4/3 * π * 半径的三次方
}

/**
 * @brief 计算 [圆柱体](https://en.wikipedia.org/wiki/Cylinder) 的体积
 * @param radius 圆柱体底面圆的半径
 * @param height 圆柱体的高度
 * @param PI 圆周率，默认为 3.14
 * @returns 圆柱体的体积
 */
template <typename T>
T cylinder_volume(T radius, T height, double PI = 3.14) {
    return PI * std::pow(radius, 2) * height;  // 圆柱体体积公式：π * 半径的平方 * 高
}
}  // namespace math

/**
 * @brief 自我测试实现
 * @returns void
 */
static void test() {
    // 输入变量
    uint32_t int_length = 0; // 32 位整数边长输入
    uint32_t int_width = 0;  // 32 位整数宽度输入
    uint32_t int_base = 0;   // 32 位整数底边输入
    uint32_t int_height = 0; // 32 位整数高度输入
    uint32_t int_depth = 0;  // 32 位整数深度输入

    double double_radius = NAN; // 双精度半径输入
    double double_height = NAN; // 双精度高度输入

    // 输出变量
    uint32_t int_expected = 0; // 32 位整数预期输出
    uint32_t int_volume = 0;   // 32 位整数输出

    double double_expected = NAN; // 双精度预期输出
    double double_volume = NAN;   // 双精度输出

    // 1. 测试立方体体积
    int_length = 5;
    int_expected = 125;
    int_volume = math::cube_volume(int_length);

    std::cout << "立方体的体积" << std::endl;
    std::cout << "输入边长: " << int_length << std::endl;
    std::cout << "预期输出: " << int_expected << std::endl;
    std::cout << "输出: " << int_volume << std::endl;
    assert(int_volume == int_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 2. 测试长方体体积
    int_length = 4;
    int_width = 3;
    int_height = 5;
    int_expected = 60;
    int_volume = math::rect_prism_volume(int_length, int_width, int_height);

    std::cout << "长方体的体积" << std::endl;
    std::cout << "输入长: " << int_length << std::endl;
    std::cout << "输入宽: " << int_width << std::endl;
    std::cout << "输入高: " << int_height << std::endl;
    std::cout << "预期输出: " << int_expected << std::endl;
    std::cout << "输出: " << int_volume << std::endl;
    assert(int_volume == int_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 3. 测试圆锥体积
    double_radius = 5;
    double_height = 7;
    double_expected = 183.16666666666666;  // 保留 14 位小数
    double_volume = math::cone_volume(double_radius, double_height);

    std::cout << "圆锥的体积" << std::endl;
    std::cout << "输入半径: " << double_radius << std::endl;
    std::cout << "输入高度: " << double_height << std::endl;
    std::cout << "预期输出: " << double_expected << std::endl;
    std::cout << "输出: " << double_volume << std::endl;
    assert(double_volume == double_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 4. 测试三角柱体积
    int_base = 3;
    int_height = 4;
    int_depth = 5;
    int_expected = 30;
    int_volume = math::triangle_prism_volume(int_base, int_height, int_depth);

    std::cout << "三角柱体的体积" << std::endl;
    std::cout << "输入底边: " << int_base << std::endl;
    std::cout << "输入高: " << int_height << std::endl;
    std::cout << "输入深度: " << int_depth << std::endl;
    std::cout << "预期输出: " << int_expected << std::endl;
    std::cout << "输出: " << int_volume << std::endl;
    assert(int_volume == int_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 5. 测试金字塔体积
    int_length = 10;
    int_width = 3;
    int_height = 5;
    int_expected = 50;
    int_volume = math::pyramid_volume(int_length, int_width, int_height);

    std::cout << "金字塔的体积" << std::endl;
    std::cout << "输入长度: " << int_length << std::endl;
    std::cout << "输入宽度: " << int_width << std::endl;
    std::cout << "输入高度: " << int_height << std::endl;
    std::cout << "预期输出: " << int_expected << std::endl;
    std::cout << "输出: " << int_volume << std::endl;
    assert(int_volume == int_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 6. 测试球体体积
    double_radius = 3;
    double_expected = 113.04;
    double_volume = math::sphere_volume(double_radius);

    std::cout << "球体的体积" << std::endl;
    std::cout << "输入半径: " << double_radius << std::endl;
    std::cout << "预期输出: " << double_expected << std::endl;
    std::cout << "输出: " << double_volume << std::endl;
    assert(double_volume == double_expected);
    std::cout << "测试通过" << std::endl << std::endl;

    // 7. 测试圆柱体积
    double_radius = 5;
    double_height = 2;
    double_expected = 157;
    double_volume = math::cylinder_volume(double_radius, double_height);

    std::cout << "圆柱体的体积" << std::endl;
    std::cout << "输入半径: " << double_radius << std::endl;
    std::cout << "输入高度: " << double_height << std::endl;
    std::cout << "预期输出: " << double_expected << std::endl;
    std::cout << "输出: " << double_volume << std::endl;
    assert(double_volume == double_expected);
    std::cout << "测试通过" << std::endl << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 退出程序
 */
int main() {
    test();  // 执行自我测试
    return 0;
}
