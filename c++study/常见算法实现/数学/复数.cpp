/**
 * @author tjgurwara99
 * @file
 *
 * \brief 一个实现复数对象的类
 * \details 通过类来实现复数域，并重载运算符以实现（数学）域运算。
 */

#include <cassert>
#include <cmath>
#include <complex>
#include <ctime>
#include <iostream>
#include <stdexcept>

/**
 * \brief Complex 类用于表示复数
 */
class Complex {
    // 复数的实部
    double re;
    // 复数的虚部
    double im;

 public:
    /**
     * \brief Complex 构造函数，用于初始化复数
     * \details
     * Complex 构造函数初始化复数，可接受三个参数。
     * @param x 当第三个参数为 'true' 时，x 为复数的模；若为 'false'，则 x 为复数的实部（可选）。
     * @param y 当第三个参数为 'true' 时，y 为复数的辐角；若为 'false'，则 y 为复数的虚部（可选）。
     * @param is_polar 默认为 'false'。如果想用极坐标初始化复数，则设置为 true；
     * 否则设置为 false 以使用实部和虚部初始化复数（可选）。
     */
    explicit Complex(double x = 0.f, double y = 0.f, bool is_polar = false) {
        if (!is_polar) {
            re = x;
            im = y;
            return;
        }

        re = x * std::cos(y);
        im = x * std::sin(y);
    }

    /**
     * \brief 拷贝构造函数
     * @param other 另一个复数，用于复制当前复数的值
     */
    Complex(const Complex &other) : re(other.real()), im(other.imag()) {}

    /**
     * \brief 获取复数的实部
     */
    double real() const { return this->re; }

    /**
     * \brief 获取复数的虚部
     */
    double imag() const { return this->im; }

    /**
     * \brief 获取复数的模
     * @return \f$ \sqrt{z \bar{z}} \f$，其中 \f$ z \f$ 是当前复数
     */
    double abs() const {
        return std::sqrt(this->re * this->re + this->im * this->im);
    }

    /**
     * \brief 获取复数的辐角
     * @return 当前复数的辐角（以弧度表示）
     */
    double arg() const { return std::atan2(this->im, this->re); }

    /**
     * \brief '+' 运算符重载，用于复数相加
     */
    Complex operator+(const Complex &other) {
        Complex result(this->re + other.re, this->im + other.im);
        return result;
    }

    /**
     * \brief '-' 运算符重载，用于复数相减
     */
    Complex operator-(const Complex &other) {
        Complex result(this->re - other.re, this->im - other.im);
        return result;
    }

    /**
     * \brief '*' 运算符重载，用于复数相乘
     */
    Complex operator*(const Complex &other) {
        Complex result(this->re * other.re - this->im * other.im,
                       this->re * other.im + this->im * other.re);
        return result;
    }

    /**
     * \brief '~' 运算符重载，用于求复数的共轭
     * 注意：此处重载的是位运算符，但并不是位运算。
     */
    Complex operator~() const {
        Complex result(this->re, -(this->im));
        return result;
    }

    /**
     * \brief '/' 运算符重载，用于复数相除
     * 如果分母为零，将抛出异常。
     */
    Complex operator/(const Complex &other) {
        Complex result = *this * ~other;
        double denominator =
            other.real() * other.real() + other.imag() * other.imag();
        if (denominator != 0) {
            result = Complex(result.real() / denominator,
                             result.imag() / denominator);
            return result;
        } else {
            throw std::invalid_argument("Undefined Value");
        }
    }

    /**
     * \brief '=' 运算符重载，用于复制复数
     */
    const Complex &operator=(const Complex &other) {
        this->re = other.real();
        this->im = other.imag();
        return *this;
    }
};

/**
 * \brief '==' 运算符重载，用于复数比较
 */
bool operator==(const Complex &a, const Complex &b) {
    return a.real() == b.real() && a.imag() == b.imag();
}

/**
 * \brief '<<' 运算符重载，用于输出复数
 */
std::ostream &operator<<(std::ostream &os, const Complex &num) {
    os << "(" << num.real();
    if (num.imag() < 0) {
        os << " - " << -num.imag();
    } else {
        os << " + " << num.imag();
    }
    os << "i)";
    return os;
}

/**
 * \brief 生成随机数，用于生成复数进行测试
 */
double get_rand() { return (std::rand() % 100 - 50) / 100.f; }

/**
 * 测试函数
 */
void tests() {
    std::srand(std::time(nullptr));
    double x1 = get_rand(), y1 = get_rand(), x2 = get_rand(), y2 = get_rand();
    Complex num1(x1, y1), num2(x2, y2);
    std::complex<double> cnum1(x1, y1), cnum2(x2, y2);
    Complex result;
    std::complex<double> expected;
    // 测试加法
    result = num1 + num2;
    expected = cnum1 + cnum2;
    assert((result.real() == expected.real() && result.imag() == expected.imag()));
    std::cout << "第一个测试通过。" << std::endl;
    // 测试减法
    result = num1 - num2;
    expected = cnum1 - cnum2;
    assert((result.real() == expected.real() && result.imag() == expected.imag()));
    std::cout << "第二个测试通过。" << std::endl;
    // 测试乘法
    result = num1 * num2;
    expected = cnum1 * cnum2;
    assert((result.real() == expected.real() && result.imag() == expected.imag()));
    std::cout << "第三个测试通过。" << std::endl;
    // 测试除法
    result = num1 / num2;
    expected = cnum1 / cnum2;
    assert((result.real() == expected.real() && result.imag() == expected.imag()));
    std::cout << "第四个测试通过。" << std::endl;
    // 测试共轭
    result = ~num1;
    expected = std::conj(cnum1);
    assert((result.real() == expected.real() && result.imag() == expected.imag()));
    std::cout << "第五个测试通过。" << std::endl;
    // 测试复数的辐角
    assert((num1.arg() == std::arg(cnum1)));
    std::cout << "第六个测试通过。" << std::endl;
    // 测试复数的模
    assert((num1.abs() == std::abs(cnum1)));
    std::cout << "第七个测试通过。" << std::endl;
}

/**
 * 主函数
 */
int main() {
    tests();
    return 0;
}
