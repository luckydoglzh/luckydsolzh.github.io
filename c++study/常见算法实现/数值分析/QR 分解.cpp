/**
 * @file
 * \brief 程序用于计算给定矩阵的 [QR 分解](https://en.wikipedia.org/wiki/QR_decomposition)
 * \author [Krishna Vedala](https://github.com/kvedala)
 */

#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "./qr_decompose.h"  // 引入 QR 分解的头文件

using qr_algorithm::qr_decompose;  // 使用 qr_algorithm 命名空间中的 qr_decompose 函数
using qr_algorithm::operator<<;    // 使用 qr_algorithm 命名空间中的操作符重载

/**
 * main 函数，程序的入口
 */
int main(void) {
    unsigned int ROWS, COLUMNS;  // 定义矩阵的行数和列数

    // 提示用户输入矩阵的行数和列数
    std::cout << "Enter the number of rows and columns: ";
    std::cin >> ROWS >> COLUMNS;

    std::cout << "Enter matrix elements row-wise:\n";  // 提示用户输入矩阵元素

    // 创建矩阵 A（输入矩阵），Q（正交矩阵）和 R（上三角矩阵）
    std::valarray<std::valarray<double>> A(ROWS);
    std::valarray<std::valarray<double>> Q(ROWS);
    std::valarray<std::valarray<double>> R(COLUMNS);

    // 初始化矩阵 A、Q 和 R
    for (int i = 0; i < std::max(ROWS, COLUMNS); i++) {
        if (i < ROWS) {
            A[i] = std::valarray<double>(COLUMNS);  // 初始化 A 的行
            Q[i] = std::valarray<double>(COLUMNS);  // 初始化 Q 的行
        }
        if (i < COLUMNS) {
            R[i] = std::valarray<double>(COLUMNS);  // 初始化 R 的行
        }
    }

    // 输入矩阵 A 的元素
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLUMNS; j++) std::cin >> A[i][j];

    std::cout << "Input Matrix A:\n" << A << "\n";  // 输出输入的矩阵 A

    clock_t t1 = clock();  // 记录开始时间
    qr_decompose(A, &Q, &R);  // 执行 QR 分解
    double dtime = static_cast<double>(clock() - t1) / CLOCKS_PER_SEC;  // 计算 QR 分解所用时间

    std::cout << "Matrix Q (Orthogonal):\n" << Q << "\n";  // 输出正交矩阵 Q
    std::cout << "Matrix R (Upper Triangular):\n" << R << "\n";  // 输出上三角矩阵 R
    std::cout << "Time taken to compute: " << dtime << " sec\n ";  // 输出计算时间

    return 0;  // 程序结束
}
