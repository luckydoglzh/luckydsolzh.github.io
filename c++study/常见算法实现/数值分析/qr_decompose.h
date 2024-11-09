/**
 * @file
 * \brief 提供计算矩阵的 [QR 分解](https://en.wikipedia.org/wiki/QR_decomposition) 的库函数
 * \author [Krishna Vedala](https://github.com/kvedala)
 */

#ifndef NUMERICAL_METHODS_QR_DECOMPOSE_H_
#define NUMERICAL_METHODS_QR_DECOMPOSE_H_

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <valarray>
#ifdef _OPENMP
#include <omp.h>
#endif

/** \namespace qr_algorithm
 * \brief 用于计算任意矩阵的 [QR 分解](https://en.wikipedia.org/wiki/QR_decomposition) 的函数
 */
namespace qr_algorithm {
/**
 * 操作符：打印矩阵
 * 用于输出矩阵，每个元素按给定的宽度格式化
 */
template <typename T>
std::ostream &operator<<(std::ostream &out,
                         std::valarray<std::valarray<T>> const &v) {
    const int width = 12;  // 每个元素的宽度
    const char separator = ' ';  // 分隔符

    out.precision(4);  // 设置输出精度
    for (size_t row = 0; row < v.size(); row++) {  // 遍历矩阵的每一行
        for (size_t col = 0; col < v[row].size(); col++)  // 遍历每一列
            out << std::right << std::setw(width) << std::setfill(separator)
                << v[row][col];  // 按格式输出每个元素
        out << std::endl;  // 换行
    }

    return out;
}

/**
 * 操作符：打印向量
 * 用于输出向量，每个元素按给定的宽度格式化
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, std::valarray<T> const &v) {
    const int width = 10;  // 每个元素的宽度
    const char separator = ' ';  // 分隔符

    out.precision(4);  // 设置输出精度
    for (size_t row = 0; row < v.size(); row++)  // 遍历向量的每个元素
        out << std::right << std::setw(width) << std::setfill(separator)
            << v[row];  // 按格式输出每个元素

    return out;
}

/**
 * 计算两个等长向量的点积
 *
 * 如果 \f$\vec{a}=\left[a_0,a_1,a_2,...,a_L\right]\f$ 和
 * \f$\vec{b}=\left[b_0,b_1,b_1,...,b_L\right]\f$，那么
 * \f$\vec{a}\cdot\vec{b}=\sum_{i=0}^L a_i \times b_i\f$
 *
 * \returns \f$\vec{a}\cdot\vec{b}\f$
 */
template <typename T>
inline double vector_dot(const std::valarray<T> &a, const std::valarray<T> &b) {
    return (a * b).sum();
    // 也可以使用如下方法计算点积
    // return std::inner_product(std::begin(a), std::end(a), std::begin(b), 0.f);
}

/**
 * 计算向量的大小（模长）
 *
 * 如果 \f$\vec{a}=\left[a_0,a_1,a_2,...,a_L\right]\f$，则
 * \f|\vec{a}\| = \sqrt{\sum_{i=0}^L a_i^2}\f
 *
 * \returns \f|\vec{a}\|
 */
template <typename T>
inline double vector_mag(const std::valarray<T> &a) {
    double dot = vector_dot(a, a);
    return std::sqrt(dot);
}

/**
 * 计算向量 \f$\vec{a}\f$ 在 \f$\vec{b}\f$ 上的投影
 * 定义为：
 * \f[\text{proj}_\vec{b}\vec{a}=\frac{\vec{a}\cdot\vec{b}}{\left|\vec{b}\right|^2}\vec{b}\f]
 *
 * \returns 如果发生错误返回 NULL，否则返回投影结果
 */
template <typename T>
std::valarray<T> vector_proj(const std::valarray<T> &a,
                             const std::valarray<T> &b) {
    double num = vector_dot(a, b);
    double deno = vector_dot(b, b);

    /*! 检查除零错误，使用机器精度进行判断 */
    if (deno <= std::numeric_limits<double>::epsilon()) {
        std::cerr << "[" << __func__ << "] 可能发生除零错误\n";
        return a;  // 返回向量 a
    }

    double scalar = num / deno;

    return b * scalar;
}

/**
 * 使用 [Gram-Schmidt 过程](https://en.wikipedia.org/wiki/QR_decomposition)
 * 对矩阵 A 进行 QR 分解
 *
 * 给定矩阵 \f$A\f$，其列向量为 \f$\mathbf{a}_i\f$，计算过程为：
 * \f{eqnarray*}{
 * \text{给定}\quad A &=& [\mathbf{a}_1, \mathbf{a}_2, \dots, \mathbf{a}_{N-1}] \\
 * \text{其中}\quad \mathbf{a}_i &=& [a_{0i}, a_{1i}, \dots, a_{(M-1)i}]^T \\
 * \text{然后}\quad \mathbf{u}_i &=& \mathbf{a}_i - \sum_{j=0}^{i-1} \text{proj}_{\mathbf{u}_j}\mathbf{a}_i \\
 * \mathbf{e}_i &=& \frac{\mathbf{u}_i}{|\mathbf{u}_i|} \\
 * Q &=& [\mathbf{e}_0, \mathbf{e}_1, \dots, \mathbf{e}_{N-1}] \\
 * R &=& \begin{bmatrix} \langle \mathbf{e}_0, \mathbf{a}_0 \rangle & \langle \mathbf{e}_1, \mathbf{a}_1 \rangle & \dots \\
 * 0 & \langle \mathbf{e}_1, \mathbf{a}_1 \rangle & \dots \\
 * \vdots & \vdots & \ddots \end{bmatrix} \\
 * \f}
 */
template <typename T>
void qr_decompose(
    const std::valarray<std::valarray<T>> &A, /**< 输入矩阵 A */
    std::valarray<std::valarray<T>> *Q,       /**< 输出矩阵 Q */
    std::valarray<std::valarray<T>> *R        /**< 输出矩阵 R */
) {
    std::size_t ROWS = A.size();        // 矩阵 A 的行数
    std::size_t COLUMNS = A[0].size();  // 矩阵 A 的列数
    std::valarray<T> col_vector(ROWS);  // 存储当前列的向量
    std::valarray<T> col_vector2(ROWS); // 存储投影向量
    std::valarray<T> tmp_vector(ROWS);  // 临时存储向量

    for (int i = 0; i < COLUMNS; i++) {
        /* 对每一列进行处理 => R 是一个上三角矩阵 */
        int j;
        R[0][i] = 0.; /* 使 R 矩阵上三角化 */

        /* 获取 Q 向量 */
#ifdef _OPENMP
// 使用 OpenMP 并行化处理
#pragma omp for
#endif
        for (j = 0; j < ROWS; j++) {
            tmp_vector[j] = A[j][i]; /* 初始化为列向量 a_i */
            col_vector[j] = A[j][i];
        }
        for (j = 0; j < i; j++) {
            for (int k = 0; k < ROWS; k++) {
                col_vector2[k] = Q[0][k][j];
            }
            col_vector2 = vector_proj(col_vector, col_vector2); // 计算投影
            tmp_vector -= col_vector2; // 更新临时向量
        }

        double mag = vector_mag(tmp_vector);  // 计算向量的模长

#ifdef _OPENMP
// 使用 OpenMP 并行化处理
#pragma omp for
#endif
        for (j = 0; j < ROWS; j++) Q[0][j][i] = tmp_vector[j] / mag;  // 归一化向量

        /* 计算上三角矩阵 R 的值 */
#ifdef _OPENMP
// 使用 OpenMP 并行化处理
#pragma omp for
#endif
        for (int kk = 0; kk < ROWS; kk++) {
            col_vector[kk] = Q[0][kk][i];  // 获取 Q 向量
        }

#ifdef _OPENMP
// 使用 OpenMP 并行化处理
#pragma omp for
#endif
        for (int k = i; k < COLUMNS; k++) {
            for (int kk = 0; kk < ROWS; kk++) {
                col_vector2[kk] = A[kk][k];
            }
            R[0][i][k] = (col_vector * col_vector2).sum();  // 计算 R 中的元素
        }
    }
}
}  // namespace qr_algorithm

#endif  // NUMERICAL_METHODS_QR_DECOMPOSE_H_
