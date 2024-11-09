/**
 * \file
 * \brief [LU 分解](https://en.wikipedia.org/wiki/LU_decompositon)（矩阵的 LU 分解）
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#include <cassert>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "./lu_decomposition.h"

/**
 * 重载输出运算符，用于打印矩阵
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, matrix<T> const &v) {
    const int width = 10;  /// 设置每个矩阵元素的宽度
    const char separator = ' ';  /// 元素之间的分隔符

    for (size_t row = 0; row < v.size(); row++) {  /// 遍历矩阵的每一行
        for (size_t col = 0; col < v[row].size(); col++)  /// 遍历矩阵的每一列
            out << std::left << std::setw(width) << std::setfill(separator)
                << v[row][col];  /// 打印当前元素
        out << std::endl;  /// 打印换行
    }

    return out;  /// 返回输出流
}

/**
 * LU 分解测试
 * \todo 用更好的方法来检查矩阵输出结果
 */
void test1() {
    int mat_size = 3;  // 默认矩阵大小
    const int range = 50;
    const int range2 = range >> 1;

    /* 创建一个包含随机值的方阵 */
    matrix<double> A(mat_size, std::valarray<double>(mat_size));  // 输入矩阵 A
    matrix<double> L(mat_size, std::valarray<double>(mat_size));  // 输出矩阵 L
    matrix<double> U(mat_size, std::valarray<double>(mat_size));  // 输出矩阵 U

    // 填充矩阵 A，使用随机值，范围为 [-range2, range-1]
    for (int i = 0; i < mat_size; i++) {
        for (int j = 0; j < mat_size; j++)
            A[i][j] = static_cast<double>(std::rand() % range - range2);  /// 生成随机数并赋值给矩阵 A
    }

    std::clock_t start_t = std::clock();  // 记录开始时间
    lu_decomposition(A, &L, &U);  /// 执行 LU 分解
    std::clock_t end_t = std::clock();  // 记录结束时间
    std::cout << "时间消耗: "
              << static_cast<double>(end_t - start_t) / CLOCKS_PER_SEC << " 秒\n";  /// 输出执行时间

    // 打印矩阵 A、L 和 U
    std::cout << "A = \n" << A << "\n";
    std::cout << "L = \n" << L << "\n";
    std::cout << "U = \n" << U << "\n";
}

/**
 * 使用 LU 分解进行行列式计算的测试
 */
void test2() {
    std::cout << "行列式测试 1...";  /// 测试 1
    matrix<int> A1({{1, 2, 3}, {4, 9, 6}, {7, 8, 9}});
    assert(determinant_lu(A1) == -48);  /// 验证行列式是否正确
    std::cout << "通过\n";

    std::cout << "行列式测试 2...";  /// 测试 2
    matrix<int> A2({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    assert(determinant_lu(A2) == 0);  /// 验证行列式是否正确
    std::cout << "通过\n";

    std::cout << "行列式测试 3...";  /// 测试 3
    matrix<float> A3({{1.2, 2.3, 3.4}, {4.5, 5.6, 6.7}, {7.8, 8.9, 9.0}});
    assert(determinant_lu(A3) == 3.63);  /// 验证行列式是否正确
    std::cout << "通过\n";
}

/** 主函数 */
int main(int argc, char **argv) {
    std::srand(std::time(NULL));  // 随机数初始化

    test1();  // 执行 LU 分解测试
    test2();  // 执行行列式计算测试
    return 0;
}
