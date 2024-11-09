/**
 * @file
 * @brief [快速傅里叶变换（FFT）](https://medium.com/@aiswaryamathur/understanding-fast-fouriertransform-from-scratch-to-solve-polynomial-multiplication-8018d511162f) 是一种算法，
 * 计算序列的离散傅里叶变换（DFT）或其反变换（IDFT）。
 * @details
 * 这个算法在需要通过多项式函数的系数快速找到函数的多个点时非常有用。
 * 它也可以通过仅切换欧米伽的值来计算反傅里叶变换。
 * 该算法的时间复杂度为 O(nlogn)，相比传统的 O(n^2) 时间复杂度，效率大大提高。
 * @author [Ameya Chawla](https://github.com/ameyachawlaggsipu)
 */

#include <cassert>   /// 包含assert库，用于断言操作
#include <cmath>     /// 包含数学相关的函数
#include <complex>   /// 包含复数相关的类和函数
#include <iostream>  /// 包含输入输出相关的库
#include <vector>    /// 包含std::vector类，用于存储动态数组

/**
 * @namespace numerical_methods
 * @brief 数值算法/方法的命名空间
 */
namespace numerical_methods {
/**
 * @brief FastFourierTransform 是一个递归函数，返回复数列表
 * @param p 复数形式的系数列表
 * @param n 列表 p 的元素个数
 * @returns n==1 时返回 p
 * @returns n!=1 时返回 y
 */
std::complex<double> *FastFourierTransform(std::complex<double> *p, uint8_t n) {
    if (n == 1) {
        return p;  /// 基本情况，直接返回
    }

    double pi = 2 * asin(1.0);  /// 定义 pi 的值

    std::complex<double> om = std::complex<double>(  /// 计算欧米伽值
        cos(2 * pi / n), sin(2 * pi / n));

    auto *pe = new std::complex<double>[n / 2];  /// 存储偶数幂系数的数组

    auto *po = new std::complex<double>[n / 2];  /// 存储奇数幂系数的数组

    int k1 = 0, k2 = 0;
    for (int j = 0; j < n; j++) {
        if (j % 2 == 0) {
            pe[k1++] = p[j];  /// 将偶数位置的系数赋值给 pe 数组
        } else {
            po[k2++] = p[j];  /// 将奇数位置的系数赋值给 po 数组
        }
    }

    std::complex<double> *ye = FastFourierTransform(pe, n / 2);  /// 对偶数幂系数进行递归调用
    std::complex<double> *yo = FastFourierTransform(po, n / 2);  /// 对奇数幂系数进行递归调用

    auto *y = new std::complex<double>[n];  /// 存储最终结果的数组

    k1 = 0, k2 = 0;
    for (int i = 0; i < n / 2; i++) {
        y[i] = ye[k1] + pow(om, i) * yo[k2];  /// 更新前半部分元素
        y[i + n / 2] = ye[k1] - pow(om, i) * yo[k2];  /// 更新后半部分元素

        k1++;
        k2++;
    }

    if (n != 2) {
        delete[] pe;  /// 删除动态分配的 pe 数组
        delete[] po;  /// 删除动态分配的 po 数组
    }

    delete[] ye;  /// 删除动态分配的 ye 数组
    delete[] yo;  /// 删除动态分配的 yo 数组
    return y;
}

}  // namespace numerical_methods

/**
 * @brief 自测实现
 * @details
 * 声明了两个测试用例，并检查预测值和真实值之间的误差是否小于 0.000000000001。
 * @returns void
 */
static void test() {
    /* 以下是两个测试用例的描述 */

    auto *t1 = new std::complex<double>[2];  /// 测试用例1
    auto *t2 = new std::complex<double>[4];  /// 测试用例2

    t1[0] = {1, 0};
    t1[1] = {2, 0};
    t2[0] = {1, 0};
    t2[1] = {2, 0};
    t2[2] = {3, 0};
    t2[3] = {4, 0};

    uint8_t n1 = 2;
    uint8_t n2 = 4;
    std::vector<std::complex<double>> r1 = {
        {3, 0}, {-1, 0}};  /// 测试用例1的真实答案

    std::vector<std::complex<double>> r2 = {
        {10, 0}, {-2, -2}, {-2, 0}, {-2, 2}};  /// 测试用例2的真实答案

    std::complex<double> *o1 = numerical_methods::FastFourierTransform(t1, n1);
    std::complex<double> *t3 = o1;  /// 临时变量，用于删除 o1 的内存位置
    std::complex<double> *o2 = numerical_methods::FastFourierTransform(t2, n2);
    std::complex<double> *t4 = o2;  /// 临时变量，用于删除 o2 的内存位置

    // 对测试用例1的预测值和真实值进行比较
    for (uint8_t i = 0; i < n1; i++) {
        assert((r1[i].real() - o1->real() < 0.000000000001) &&
               (r1[i].imag() - o1->imag() <
                0.000000000001));  /// 比较实部和虚部
        o1++;
    }

    // 对测试用例2的预测值和真实值进行比较
    for (uint8_t i = 0; i < n2; i++) {
        assert((r2[i].real() - o2->real() < 0.000000000001) &&
               (r2[i].imag() - o2->imag() <
                0.000000000001));  /// 比较实部和虚部
        o2++;
    }

    delete[] t1;  /// 删除动态分配的 t1 数组
    delete[] t2;  /// 删除动态分配的 t2 数组
    delete[] t3;  /// 删除动态分配的 t3 数组
    delete[] t4;  /// 删除动态分配的 t4 数组
    std::cout << "所有测试已成功通过！\n";
}

/**
 * @brief 主函数
 * @param argc 命令行参数个数（忽略）
 * @param argv 命令行参数数组（忽略）
 * 调用自动化测试函数来测试快速傅里叶变换的工作情况。
 * @returns 0 表示正常退出
 */
int main(int argc, char const *argv[]) {
    test();  // 运行自测实现，包含2个定义好的测试用例
    return 0;
}
