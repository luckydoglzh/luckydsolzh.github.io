/**
 * @file
 * @brief [逆快速傅里叶变换 (IFFT)](https://www.geeksforgeeks.org/python-inverse-fast-fourier-transformation/)
 * 是一种计算逆傅里叶变换的算法。
 * @details
 * 该算法用于在给定通过离散傅里叶变换 (DFT) 生成的点的情况下，
 * 通过快速计算逆傅里叶变换来找到函数的系数。与传统的 O(n^2) 时间复杂度算法相比，
 * 此算法的时间复杂度为 O(nlogn)。
 * @author [Ameya Chawla](https://github.com/ameyachawlaggsipu)
 */

#include <cassert>   /// 用于 assert 检查
#include <cmath>     /// 用于数学相关函数
#include <complex>   /// 用于存储复数（点和系数）
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于 std::vector 容器

/**
 * @namespace numerical_methods
 * @brief 数值算法/方法
 */
namespace numerical_methods {
/**
 * @brief 逆快速傅里叶变换（Inverse Fast Fourier Transform）是一个递归函数，
 * 用于返回复数形式的系数列表。
 * @param p 存储系数的复数数组
 * @param n 数组 p 中元素的数量
 * @returns 如果 n == 1，返回 p
 * @returns 如果 n != 1，返回 y
 */
std::complex<double> *InverseFastFourierTransform(std::complex<double> *p,
                                                  uint8_t n) {
    if (n == 1) {
        return p;  /// 基本情况，直接返回输入数组 p
    }

    double pi = 2 * asin(1.0);  /// 计算 pi 值

    std::complex<double> om = std::complex<double>(
        cos(2 * pi / n), sin(2 * pi / n));  /// 计算 omega（旋转因子）

    om.real(om.real() / n);  /// 与 DFT 的不同之处：对 omega 的实部进行缩放
    om.imag(om.imag() / n);  /// 与 DFT 的不同之处：对 omega 的虚部进行缩放

    auto *pe = new std::complex<double>[n / 2];  /// 存储偶数次幂的系数

    auto *po = new std::complex<double>[n / 2];  /// 存储奇数次幂的系数

    int k1 = 0, k2 = 0;
    for (int j = 0; j < n; j++) {
        if (j % 2 == 0) {
            pe[k1++] = p[j];  /// 将偶数次幂的系数存入 pe 数组
        } else {
            po[k2++] = p[j];  /// 将奇数次幂的系数存入 po 数组
        }
    }

    std::complex<double> *ye =
        InverseFastFourierTransform(pe, n / 2);  /// 对偶数部分递归调用 IFFT

    std::complex<double> *yo =
        InverseFastFourierTransform(po, n / 2);  /// 对奇数部分递归调用 IFFT

    auto *y = new std::complex<double>[n];  /// 存储最终结果的数组

    k1 = 0, k2 = 0;

    for (int i = 0; i < n / 2; i++) {
        y[i] =
            ye[k1] + pow(om, i) * yo[k2];  /// 更新前半部分元素
        y[i + n / 2] =
            ye[k1] - pow(om, i) * yo[k2];  /// 更新后半部分元素

        k1++;
        k2++;
    }

    if (n != 2) {
        delete[] pe;  /// 删除临时存储偶数次幂系数的数组
        delete[] po;  /// 删除临时存储奇数次幂系数的数组
    }

    delete[] ye;  /// 删除递归调用返回的偶数部分数组
    delete[] yo;  /// 删除递归调用返回的奇数部分数组
    return y;      /// 返回最终计算得到的系数数组
}

}  // namespace numerical_methods

/**
 * @brief 自我测试实现
 * @details
 * 定义了两个测试案例并检查预测值与实际值之间的误差是否小于 0.000000000001。
 * @returns 无返回值
 */
static void test() {
    /* 以下是测试案例的描述 */

    auto *t1 = new std::complex<double>[2];  /// 测试案例 1
    auto *t2 = new std::complex<double>[4];  /// 测试案例 2

    t1[0] = {3, 0};
    t1[1] = {-1, 0};
    t2[0] = {10, 0};
    t2[1] = {-2, -2};
    t2[2] = {-2, 0};
    t2[3] = {-2, 2};

    uint8_t n1 = 2;
    uint8_t n2 = 4;
    std::vector<std::complex<double>> r1 = {
        {1, 0}, {2, 0}};  /// 测试案例 1 的正确答案

    std::vector<std::complex<double>> r2 = {
        {1, 0}, {2, 0}, {3, 0}, {4, 0}};  /// 测试案例 2 的正确答案

    std::complex<double> *o1 =
        numerical_methods::InverseFastFourierTransform(t1, n1);

    std::complex<double> *o2 =
        numerical_methods::InverseFastFourierTransform(t2, n2);

    for (uint8_t i = 0; i < n1; i++) {
        assert((r1[i].real() - o1[i].real() < 0.000000000001) &&
               (r1[i].imag() - o1[i].imag() <
                0.000000000001));  /// 检查测试案例 1 的实部和虚部
    }

    for (uint8_t i = 0; i < n2; i++) {
        assert((r2[i].real() - o2[i].real() < 0.000000000001) &&
               (r2[i].imag() - o2[i].imag() <
                0.000000000001));  /// 检查测试案例 2 的实部和虚部
    }

    delete[] t1;
    delete[] t2;
    delete[] o1;
    delete[] o2;
    std::cout << "所有测试已成功通过！\n";
}

/**
 * @brief 主函数
 * @param argc 命令行参数数量（忽略）
 * @param argv 命令行参数数组（忽略）
 * 调用自动化测试函数，测试快速傅里叶变换的工作原理。
 * @returns 0 退出程序
 */
int main(int argc, char const *argv[]) {
    test();  // 执行自我测试，实现了 2 个测试案例
    return 0;
}
