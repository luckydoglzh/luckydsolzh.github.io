/**
 * @file
 * \brief 使用 [QR 分解](https://en.wikipedia.org/wiki/QR_decomposition) 方法计算对称矩阵的实特征值和特征向量。
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#ifdef _OPENMP
#include <omp.h>  // 如果支持 OpenMP，包含 OpenMP 库
#endif

#include "./qr_decompose.h"  // 引入 QR 分解的头文件
using qr_algorithm::operator<<;

#define LIMS 9 /**< 矩阵元素值的范围限制 */

/**
 * 创建一个对称的方阵，并填充随机元素。对称矩阵 *总是* 具有实特征值。
 *
 * \param[out] A 创建的矩阵（必须预先分配内存）
 */
void create_matrix(std::valarray<std::valarray<double>> *A) {
    int i, j, tmp, lim2 = LIMS >> 1;
    int N = A->size();

#ifdef _OPENMP
#pragma omp for
#endif
    // 填充矩阵 A，保证其为对称矩阵
    for (i = 0; i < N; i++) {
        A[0][i][i] = (std::rand() % LIMS) - lim2;  // 对角元素随机生成
        for (j = i + 1; j < N; j++) {
            tmp = (std::rand() % LIMS) - lim2;  // 生成随机数
            A[0][i][j] = tmp;  // 确保对称填充
            A[0][j][i] = tmp;
        }
    }
}

/**
 * 执行两个矩阵的乘法运算。
 * * R2 必须等于 C1
 * * 结果矩阵的大小应为 R1xC2
 * \param[in] A 第一个矩阵
 * \param[in] B 第二个矩阵
 * \param[out] OUT 输出矩阵（必须预先分配）
 * \returns 返回结果矩阵的指针
 */
void mat_mul(const std::valarray<std::valarray<double>> &A,
             const std::valarray<std::valarray<double>> &B,
             std::valarray<std::valarray<double>> *OUT) {
    int R1 = A.size();
    int C1 = A[0].size();
    int R2 = B.size();
    int C2 = B[0].size();
    
    if (C1 != R2) {  // 矩阵维度不匹配，无法进行乘法运算
        perror("Matrix dimensions mismatch!");
        return;
    }

    // 计算矩阵乘法
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            OUT[0][i][j] = 0.f;
            for (int k = 0; k < C1; k++) {
                OUT[0][i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

namespace qr_algorithm {
/** 使用迭代的 shifted QR 分解算法计算特征值，如下所示：
 * 1. 使用矩阵 A 的最后一个对角元素作为特征值的初始近似值 \f$c\f$
 * 2. 计算移位后的矩阵 \f$A' = A - cI\f$
 * 3. 分解矩阵 \f$A'=QR\f$
 * 4. 计算新的近似值 \f$A'_1 = RQ \f$
 * 5. 将对角元素恢复 \f$A_1 = A'_1 + cI\f$
 * 6. 终止条件检查：如果最后一个非对角元素几乎为 0
 *    1. 如果不为 0，回到步骤 1，使用新的近似矩阵 \f$A_1\f$
 *    2. 如果为 0，继续到步骤 7
 * 7. 将最后已知的 \f$c\f$ 保存为特征值。
 * 8. 是否找到所有特征值？
 *    1. 如果没有，去掉最后一行和最后一列的矩阵，然后回到步骤 1。
 *    2. 如果所有特征值已找到，则停止。
 *
 * \note 矩阵 \f$A\f$ 会被修改
 *
 * \param[in,out] A 要计算特征值的矩阵
 * \param[in] print_intermediates （可选）是否打印中间的 A, Q 和 R 矩阵（默认 = `false`）
 */
std::valarray<double> eigen_values(std::valarray<std::valarray<double>> *A,
                                   bool print_intermediates = false) {
    int rows = A->size();
    int columns = rows;
    int counter = 0, num_eigs = rows - 1;
    double last_eig = 0;

    std::valarray<std::valarray<double>> Q(rows);
    std::valarray<std::valarray<double>> R(columns);

    // 初始化特征值数组
    std::valarray<double> eigen_vals(rows);
    for (int i = 0; i < rows; i++) {
        Q[i] = std::valarray<double>(columns);
        R[i] = std::valarray<double>(columns);
    }

    // 继续直到找到所有特征值
    while (num_eigs > 0) {
        // 迭代 QR 分解
        while (std::abs(A[0][num_eigs][num_eigs - 1]) >
               std::numeric_limits<double>::epsilon()) {
            // 初始近似值 = 最后一个对角元素
            last_eig = A[0][num_eigs][num_eigs];
            for (int i = 0; i < rows; i++) {
                A[0][i][i] -= last_eig; /* A - cI */
            }

            // QR 分解
            qr_decompose(*A, &Q, &R);

            if (print_intermediates) {
                std::cout << *A << "\n";
                std::cout << Q << "\n";
                std::cout << R << "\n";
                printf("-------------------- %d ---------------------\n",
                       ++counter);
            }

            // 计算新的近似矩阵 A' = R * Q
            mat_mul(R, Q, A);

            for (int i = 0; i < rows; i++) {
                A[0][i][i] += last_eig; /* A + cI */
            }
        }

        // 存储已收敛的特征值
        eigen_vals[num_eigs] = last_eig;

        if (print_intermediates) {
            std::cout << "========================\n";
            std::cout << "Eigen value: " << last_eig << ",\n";
            std::cout << "========================\n";
        }

        num_eigs--;
        rows--;
        columns--;
    }
    eigen_vals[0] = A[0][0][0];

    if (print_intermediates) {
        std::cout << Q << "\n";
        std::cout << R << "\n";
    }

    return eigen_vals;
}

}  // namespace qr_algorithm

/**
 * 测试函数，计算 2x2 矩阵的特征值
 * \f[\begin{bmatrix}
 * 5 & 7\\
 * 7 & 11
 * \end{bmatrix}\f]
 * 其特征值约为 {15.56158, 0.384227}
 */
void test1() {
    std::valarray<std::valarray<double>> X = {{5, 7}, {7, 11}};
    double y[] = {15.56158, 0.384227};  // 对应的期望特征值

    std::cout << "------- Test 1 -------" << std::endl;
    std::valarray<double> eig_vals = qr_algorithm::eigen_values(&X);

    for (int i = 0; i < 2; i++) {
        std::cout << i + 1 << "/2 Checking for " << y[i] << " --> ";
        bool result = false;
        for (int j = 0; j < 2 && !result; j++) {
            if (std::abs(y[i] - eig_vals[j]) < 0.1) {
                result = true;
                std::cout << "(" << eig_vals[j] << ") ";
            }
        }
        assert(result);  // 确保计算出的第 i 个特征值正确
        std::cout << "found\n";
    }
    std::cout << "Test 1 Passed\n\n";
}

/**
 * 测试函数，计算 5x5 矩阵的特征值
 * \f[\begin{bmatrix}
 * -4& 4& 2& 0& -3\\
 * 4& -4& 4& -3& -1\\
 * 2& 4& 4& 3& -3\\
 * 0& -3& 3& -1&-1\\
 * -3& -1& -3& -3& 0
 * \end{bmatrix}\f]
 * 其特征值约为 {9.27648, -9.26948, 2.0181, -1.03516, -5.98994}
 */
void test2() {
    std::valarray<std::valarray<double>> X = {{-4, 4, 2, 0, -3},
                                              {4, -4, 4, -3, -1},
                                              {2, 4, 4, 3, -3},
                                              {0, -3, 3, -1, -3},
                                              {-3, -1, -3, -3, 0}};
    double y[] = {9.27648, -9.26948, 2.0181, -1.03516,
                  -5.98994};  // 对应的期望特征值

    std::cout << "------- Test 2 -------" << std::endl;
    std::valarray<double> eig_vals = qr_algorithm::eigen_values(&X);

    std::cout << X << "\n"
              << "Eigen values: " << eig_vals << "\n";

    for (int i = 0; i < 5; i++) {
        std::cout << i + 1 << "/5 Checking for " << y[i] << " --> ";
        bool result = false;
        for (int j = 0; j < 5 && !result; j++) {
            if (std::abs(y[i] - eig_vals[j]) < 0.1) {
                result = true;
                std::cout << "(" << eig_vals[j] << ") ";
            }
        }
        assert(result);  // 确保计算出的第 i 个特征值正确
        std::cout << "found\n";
    }
    std::cout << "Test 2 Passed\n\n";
}

/**
 * 主函数
 */
int main(int argc, char **argv) {
    int mat_size = 5;
    if (argc == 2) {
        mat_size = atoi(argv[1]);  // 获取矩阵大小
    } else {  // 如果没有提供输入参数，则运行测试
        test1();
        test2();
        std::cout << "Usage: ./qr_eigen_values [mat_size]\n";
        return 0;
    }

    if (mat_size < 2) {
        fprintf(stderr, "Matrix size should be > 2\n");
        return -1;
    }

    // 初始化随机数生成器
    std::srand(std::time(nullptr));

    int i, rows = mat_size, columns = mat_size;

    std::valarray<std::valarray<double>> A(rows);

    for (int i = 0; i < rows; i++) {
        A[i] = std::valarray<double>(columns);
    }

    /* 创建一个随机矩阵 */
    create_matrix(&A);

    std::cout << A << "\n";

    clock_t t1 = clock();
    std::valarray<double> eigen_vals = qr_algorithm::eigen_values(&A);
    double dtime = static_cast<double>(clock() - t1) / CLOCKS_PER_SEC;

    std::cout << "Eigen vals: ";
    for (i = 0; i < mat_size; i++) std::cout << eigen_vals[i] << "\t";
    std::cout << "\nTime taken to compute: " << dtime << " sec\n";

    return 0;
}
