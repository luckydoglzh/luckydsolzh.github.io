/**
 * @file lu_decomposition.h
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief 与 [LU 分解](https://en.wikipedia.org/wiki/LU_decomposition)
 * 相关的函数，用于对方阵进行 LU 分解。
 */
#pragma once

#include <iostream>
#include <valarray>
#include <vector>
#ifdef _OPENMP
#include <omp.h>  // OpenMP 支持并行化计算
#endif

/** 定义矩阵类型为 `std::vector` 的 `std::valarray` */
template <typename T>
using matrix = std::vector<std::valarray<T>>;

/** 执行 LU 分解
 * \param[in] A 需要分解的矩阵
 * \param[out] L 输出的 L 矩阵（下三角矩阵）
 * \param[out] U 输出的 U 矩阵（上三角矩阵）
 * \returns 0 如果没有错误
 * \returns 负数 如果发生错误
 */
template <typename T>
int lu_decomposition(const matrix<T> &A, matrix<double> *L, matrix<double> *U) {
    int row, col, j;
    int mat_size = A.size();  // 获取矩阵的大小

    if (mat_size != A[0].size()) {
        // 如果矩阵不是方阵，输出错误信息并返回 -1
        std::cerr << "不是一个方阵！\n";
        return -1;
    }

    // 对每一行进行常规化
    for (row = 0; row < mat_size; row++) {
        // 上三角矩阵
#ifdef _OPENMP
#pragma omp for  // 使用 OpenMP 对外循环并行化
#endif
        for (col = row; col < mat_size; col++) {
            // 计算 L[i,j] * U[j,k] 的和
            double lu_sum = 0.;
            for (j = 0; j < row; j++) {
                lu_sum += L[0][row][j] * U[0][j][col];
            }

            // 计算 U[i,k]
            U[0][row][col] = A[row][col] - lu_sum;
        }

        // 下三角矩阵
#ifdef _OPENMP
#pragma omp for  // 使用 OpenMP 对外循环并行化
#endif
        for (col = row; col < mat_size; col++) {
            if (row == col) {
                // 对角线元素 L[i,i] 设置为 1
                L[0][row][col] = 1.;
                continue;
            }

            // 计算 L[i,j] * U[j,k] 的和
            double lu_sum = 0.;
            for (j = 0; j < row; j++) {
                lu_sum += L[0][col][j] * U[0][j][row];
            }

            // 计算 L[i,k]
            L[0][col][row] = (A[col][row] - lu_sum) / U[0][row][row];
        }
    }

    return 0;
}

/**
 * 使用 LU 分解计算 NxN 方阵的行列式。
 * 通过 LU 分解，行列式等于 L 和 U 矩阵的对角元素之积。
 *
 * @tparam T 输入矩阵的数据类型 - int、unsigned int、double 等
 * @param A 输入的方阵
 * @return 返回矩阵 A 的行列式
 */
template <typename T>
double determinant_lu(const matrix<T> &A) {
    matrix<double> L(A.size(), std::valarray<double>(A.size()));  // 初始化 L 矩阵
    matrix<double> U(A.size(), std::valarray<double>(A.size()));  // 初始化 U 矩阵

    if (lu_decomposition(A, &L, &U) < 0)
        return 0;  // 如果 LU 分解出错，返回 0

    double result = 1.f;
    // 计算行列式：L 和 U 矩阵的对角元素的积
    for (size_t i = 0; i < A.size(); i++) {
        result *= L[i][i] * U[i][i];
    }
    return result;  // 返回行列式的值
}
