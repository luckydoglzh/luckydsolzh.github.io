/**
 * @file
 * @brief 计算具有复数根的二次方程， 即 b^2 - 4ac < 0 时的情况。
 *
 * @author [Renjian-buchai](https://github.com/Renjian-buchai)
 *
 * @description 计算任何二次方程的解，方程形式为 ax^2 + bx + c。
 *
 * 二次方程：
 * x = (-b +/- sqrt(b^2 - 4ac)) / 2a
 *
 * @example
 * int main() {
 *   using std::array;
 *   using std::complex;
 *   using std::cout;
 *
 *   array<complex<long double, 2> solutions = quadraticEquation(1, 2, 1);
 *   cout << solutions[0] << " " << solutions[1] << "\n";
 *
 *   solutions = quadraticEquation(1, 1, 1);  // 重用解
 *   cout << solutions[0] << " " << solutions[1] << "\n";
 *   return 0;
 * }
 *
 * 输出：
 * (-1, 0) (-1, 0)
 * (-0.5,0.866025) (-0.5,0.866025)
 */

#include <array>      /// std::array
#include <cassert>    /// assert
#include <cmath>      /// std::sqrt, std::trunc, std::pow
#include <complex>    /// std::complex
#include <exception>  /// std::invalid_argument
#include <iomanip>    /// std::setprecision
#include <iostream>   /// std::cout

/**
 * @namespace
 * @brief 数学算法
 */
namespace math {

/**
 * @brief 计算二次方程的根
 * @param a 二次项系数。
 * @param b 一次项系数。
 * @param c 常数项。
 * @return 包含方程根的数组，可能是复数根。
 */
std::array<std::complex<long double>, 2> quadraticEquation(long double a,
                                                           long double b,
                                                           long double c) {
    if (a == 0) {  // 如果 a 为 0，不是二次方程
        throw std::invalid_argument("quadratic coefficient cannot be 0");
    }

    long double discriminant = b * b - 4 * a * c;  // 计算判别式
    std::array<std::complex<long double>, 2> solutions{0, 0};  // 初始化解数组

    if (discriminant == 0) {  // 判别式为 0，方程有两个相等的实数根
        solutions[0] = -b * 0.5 / a;
        solutions[1] = -b * 0.5 / a;
        return solutions;
    }
    
    // 判别式大于 0，表示方程有两个不同的实数根
    if (discriminant > 0) {
        // 计算两个实数根
        solutions[0] = std::complex<long double>{
            (-b - std::sqrt(discriminant)) * 0.5 / a, 0};
        solutions[1] = std::complex<long double>{
            (-b + std::sqrt(discriminant)) * 0.5 / a, 0};
        return solutions;
    }
    
    // 判别式小于 0，表示方程有两个不同的复数根
    // 计算复数根时，判别式取负值，并计算虚部
    solutions[0] = std::complex<long double> {
        -b * 0.5 / a, -std::sqrt(-discriminant) * 0.5 / a};
    solutions[1] = std::complex<long double> {
        -b * 0.5 / a, std::sqrt(-discriminant) * 0.5 / a};

    return solutions;
}

}  // namespace math

/**
 * @brief 断言复数数组是否正确
 * @param input 输入的复数数组。
 * @param expected 预期的复数数组。
 * @param precision 精度，默认值为 10。
 */
void assertArray(std::array<std::complex<long double>, 2> input,
                 std::array<std::complex<long double>, 2> expected,
                 size_t precision = 10) {
    long double exponent = std::pow(10, precision);
    // 对输入和预期的实部和虚部四舍五入到指定精度
    input[0].real(std::round(input[0].real() * exponent));
    input[1].real(std::round(input[1].real() * exponent));
    input[0].imag(std::round(input[0].imag() * exponent));
    input[1].imag(std::round(input[1].imag() * exponent));

    expected[0].real(std::round(expected[0].real() * exponent));
    expected[1].real(std::round(expected[1].real() * exponent));
    expected[0].imag(std::round(expected[0].imag() * exponent));
    expected[1].imag(std::round(expected[1].imag() * exponent));

    // 断言输入的复数数组等于预期的复数数组
    assert(input == expected);
}

/**
 * @brief 自我测试，用于测试 quadraticEquation 函数
 * @note 有四种不同的解类型：实数且相等，实数，不同复数，复数且相等。
 */
static void test() {
    // 实数且相等的解
    std::cout << "输入: \n"
                 "a=1 \n"
                 "b=-2 \n"
                 "c=1 \n"
                 "预期输出: \n"
                 "(1, 0), (1, 0)\n\n";
    std::array<std::complex<long double>, 2> equalCase{
        std::complex<long double>{1, 0}, std::complex<long double>{1, 0}};
    assert(math::quadraticEquation(1, -2, 1) == equalCase);

    // 实数解
    std::cout << "输入: \n"
                 "a=1 \n"
                 "b=5 \n"
                 "c=1 \n"
                 "预期输出: \n"
                 "(-4.7912878475, 0), (-0.2087121525, 0)\n\n";
    std::array<std::complex<long double>, 2> floatCase{
        std::complex<long double>{-4.7912878475, 0},
        std::complex<long double>{-0.2087121525, 0}};
    assertArray(math::quadraticEquation(1, 5, 1), floatCase);

    // 复数解
    std::cout << "输入: \n"
                 "a=1 \n"
                 "b=1 \n"
                 "c=1 \n"
                 "预期输出: \n"
                 "(-0.5, -0.8660254038), (-0.5, 0.8660254038)\n\n";
    std::array<std::complex<long double>, 2> complexCase{
        std::complex<long double>{-0.5, -0.8660254038},
        std::complex<long double>{-0.5, 0.8660254038}};
    assertArray(math::quadraticEquation(1, 1, 1), complexCase);

    // 异常测试：a 为 0 时，应该抛出异常
    std::cout << "异常测试: \n"
                 "输入: \n"
                 "a=0 \n"
                 "b=0 \n"
                 "c=0\n"
                 "预期输出: 异常抛出 \n";
    try {
        math::quadraticEquation(0, 0, 0);
    } catch (std::invalid_argument& e) {
        std::cout << "异常抛出成功 \n";
    }
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    test();  // 运行自我测试
    return 0;
}
