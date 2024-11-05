/**
 * @file
 * \brief 使用 [普通最小二乘法](https://en.wikipedia.org/wiki/Ordinary_least_squares) 的线性回归示例
 *
 * 程序获取数据样本的数量和每个样本的特征数量，以及每个样本的输出。
 * 它应用OLS回归来计算额外测试数据样本的回归输出。
 *
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#include <cassert>
#include <cmath>    // 用于 std::abs
#include <iomanip>  // 用于打印格式
#include <iostream>
#include <vector>

/**
 * 打印矩阵的操作符
 */
template <typename T>
std::ostream &operator<<(std::ostream &out,
                         std::vector<std::vector<T>> const &v) {
    const int width = 10; // 每个元素的宽度
    const char separator = ' '; // 分隔符

    for (size_t row = 0; row < v.size(); row++) {
        for (size_t col = 0; col < v[row].size(); col++) {
            out << std::left << std::setw(width) << std::setfill(separator)
                << v[row][col]; // 打印每个元素
        }
        out << std::endl; // 换行
    }

    return out;
}

/**
 * 打印向量的操作符
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, std::vector<T> const &v) {
    const int width = 15; // 每个元素的宽度
    const char separator = ' '; // 分隔符

    for (size_t row = 0; row < v.size(); row++) {
        out << std::left << std::setw(width) << std::setfill(separator)
            << v[row]; // 打印每个元素
    }

    return out;
}

/**
 * 检查给定矩阵是否为方阵的函数
 * \returns 1 如果是方阵，0 如果不是
 */
template <typename T>
inline bool is_square(std::vector<std::vector<T>> const &A) {
    // 假设 A 是方阵
    size_t N = A.size();
    for (size_t i = 0; i < N; i++) {
        if (A[i].size() != N) {
            return false; // 如果行的大小与列的大小不相等，则返回 false
        }
    }
    return true; // 如果所有行的大小相等，则返回 true
}

/**
 * 矩阵乘法，若 A 的大小为 (mxn) 且 B 的大小为 (pxq)，则
 * 乘法定义仅当 n = p 且结果矩阵大小为 (mxq)
 *
 * \returns 结果矩阵
 **/
template <typename T>
std::vector<std::vector<T>> operator*(std::vector<std::vector<T>> const &A,
                                      std::vector<std::vector<T>> const &B) {
    // A 的行数
    size_t N_A = A.size();
    // B 的列数
    size_t N_B = B[0].size();

    std::vector<std::vector<T>> result(N_A);

    if (A[0].size() != B.size()) {
        std::cerr << "A 的列数不等于 B 的行数 ("
                  << A[0].size() << ", " << B.size() << ")" << std::endl;
        return result; // 如果维度不匹配，返回空结果
    }

    for (size_t row = 0; row < N_A; row++) {
        std::vector<T> v(N_B);
        for (size_t col = 0; col < N_B; col++) {
            v[col] = static_cast<T>(0); // 初始化结果向量
            for (size_t j = 0; j < B.size(); j++) {
                v[col] += A[row][j] * B[j][col]; // 矩阵乘法逻辑
            }
        }
        result[row] = v; // 将计算结果存入结果矩阵
    }

    return result; // 返回结果矩阵
}

/**
 * 将矩阵与列向量相乘
 * \returns 结果向量
 */
template <typename T>
std::vector<T> operator*(std::vector<std::vector<T>> const &A,
                         std::vector<T> const &B) {
    // A 的行数
    size_t N_A = A.size();

    std::vector<T> result(N_A);

    if (A[0].size() != B.size()) {
        std::cerr << "A 的列数不等于 B 的行数 ("
                  << A[0].size() << ", " << B.size() << ")" << std::endl;
        return result; // 如果维度不匹配，返回空结果
    }

    for (size_t row = 0; row < N_A; row++) {
        result[row] = static_cast<T>(0); // 初始化结果
        for (size_t j = 0; j < B.size(); j++) result[row] += A[row][j] * B[j]; // 矩阵乘法
    }

    return result; // 返回结果向量
}

/**
 * 矢量乘以标量的前乘
 * \returns 结果向量
 */
template <typename T>
std::vector<float> operator*(float const scalar, std::vector<T> const &A) {
    // A 的行数
    size_t N_A = A.size();

    std::vector<float> result(N_A);

    for (size_t row = 0; row < N_A; row++) {
        result[row] += A[row] * static_cast<float>(scalar); // 乘法运算
    }

    return result; // 返回结果向量
}

/**
 * 矢量乘以标量的后乘
 * \returns 结果向量
 */
template <typename T>
std::vector<float> operator*(std::vector<T> const &A, float const scalar) {
    // A 的行数
    size_t N_A = A.size();

    std::vector<float> result(N_A);

    for (size_t row = 0; row < N_A; row++) {
        result[row] = A[row] * static_cast<float>(scalar); // 乘法运算
    }

    return result; // 返回结果向量
}

/**
 * 矢量除以标量
 * \returns 结果向量
 */
template <typename T>
std::vector<float> operator/(std::vector<T> const &A, float const scalar) {
    return (1.f / scalar) * A; // 通过标量的倒数与向量相乘实现除法
}

/**
 * 两个相同长度的向量相减
 * \returns 结果向量
 */
template <typename T>
std::vector<T> operator-(std::vector<T> const &A, std::vector<T> const &B) {
    // A 的行数
    size_t N = A.size();

    std::vector<T> result(N);

    if (B.size() != N) {
        std::cerr << "向量维度应该相同!" << std::endl;
        return A; // 如果维度不匹配，返回第一个向量
    }

    for (size_t row = 0; row < N; row++) result[row] = A[row] - B[row]; // 相减逻辑

    return result; // 返回结果向量
}

/**
 * 两个相同长度的向量相加
 * \returns 结果向量
 */
template <typename T>
std::vector<T> operator+(std::vector<T> const &A, std::vector<T> const &B) {
    // A 的行数
    size_t N = A.size();

    std::vector<T> result(N);

    if (B.size() != N) {
        std::cerr << "向量维度应该相同!" << std::endl;
        return A; // 如果维度不匹配，返回第一个向量
    }

    for (size_t row = 0; row < N; row++) result[row] = A[row] + B[row]; // 相加逻辑

    return result; // 返回结果向量
}

/**
 * 使用行变换获取矩阵的逆。给定的矩阵必须是方阵且非奇异。
 * \returns 逆矩阵
 **/
template <typename T>
std::vector<std::vector<float>> get_inverse(
    std::vector<std::vector<T>> const &A) {
    // 假设 A 是方阵
    size_t N = A.size();

    std::vector<std::vector<float>> inverse(N);
    for (size_t row = 0; row < N; row++) {
        // 预分配一个单位矩阵
        inverse[row] = std::vector<float>(N);
        for (size_t col = 0; col < N; col++) {
            inverse[row][col] = (row == col) ? 1.f : 0.f; // 形成单位矩阵
        }
    }

    // 使用行变换获得逆矩阵
    for (size_t row = 0; row < N; row++) {
        // 如果对角元素为零，寻找非零行并交换
        if (A[row][row] == 0) {
            for (size_t i = row + 1; i < N; i++) {
                if (A[i][row] != 0) {
                    std::swap(A[row], A[i]); // 交换行
                    std::swap(inverse[row], inverse[i]); // 交换逆矩阵的相应行
                    break; // 找到后停止
                }
            }
        }

        float factor = A[row][row]; // 获取对角元素
        for (size_t col = 0; col < N; col++) {
            A[row][col] /= factor; // 归一化行
            inverse[row][col] /= factor; // 归一化逆矩阵
        }

        for (size_t i = 0; i < N; i++) {
            if (i != row) {
                factor = A[i][row]; // 获取非对角元素
                for (size_t col = 0; col < N; col++) {
                    A[i][col] -= factor * A[row][col]; // 行变换
                    inverse[i][col] -= factor * inverse[row][col]; // 变换逆矩阵
                }
            }
        }
    }

    return inverse; // 返回逆矩阵
}

/**
 * 使用普通最小二乘法 (OLS) 进行线性回归
 * \param X 输入特征 (n_samples, n_features)
 * \param y 输出 (n_samples,)
 * \returns 权重 (n_features,)
 */
std::vector<float> linear_regression(std::vector<std::vector<float>> const &X,
                                      std::vector<float> const &y) {
    // 样本数量
    size_t n_samples = X.size();
    // 特征数量
    size_t n_features = X[0].size();

    // 创建一个 (n_features, n_features) 的矩阵
    std::vector<std::vector<float>> XtX(n_features,
                                         std::vector<float>(n_features));
    // 计算 XtX = X^T * X
    for (size_t i = 0; i < n_features; i++) {
        for (size_t j = 0; j < n_features; j++) {
            XtX[i][j] = 0; // 初始化
            for (size_t k = 0; k < n_samples; k++) {
                XtX[i][j] += X[k][i] * X[k][j]; // 矩阵乘法
            }
        }
    }

    // 计算 XtY = X^T * y
    std::vector<float> XtY(n_features, 0);
    for (size_t i = 0; i < n_features; i++) {
        for (size_t k = 0; k < n_samples; k++) {
            XtY[i] += X[k][i] * y[k]; // 矩阵乘法
        }
    }

    // 计算逆矩阵
    std::vector<std::vector<float>> XtX_inv = get_inverse(XtX);

    // 计算权重 = XtX^-1 * XtY
    std::vector<float> weights(n_features);
    for (size_t i = 0; i < n_features; i++) {
        weights[i] = 0; // 初始化
        for (size_t j = 0; j < n_features; j++) {
            weights[i] += XtX_inv[i][j] * XtY[j]; // 矩阵乘法
        }
    }

    return weights; // 返回计算出的权重
}

int main() {
    // 输入特征样本 (n_samples, n_features)
    std::vector<std::vector<float>> X = {
        {1.0, 1.0},
        {2.0, 2.0},
        {3.0, 3.0},
    };

    // 输出 (n_samples,)
    std::vector<float> y = {1.0, 2.0, 3.0};

    // 执行线性回归
    auto weights = linear_regression(X, y);

    // 打印结果
    std::cout << "Calculated weights:\n" << weights << std::endl;

    return 0;
}
