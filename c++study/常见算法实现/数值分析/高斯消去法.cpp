/**
 * \file
 * \brief [高斯消去法](https://en.wikipedia.org/wiki/Gaussian_elimination) 计算线性方程组的解。
 */
#include <iostream>

/** 主函数 */
int main() {
    int mat_size, i, j, step;

    std::cout << "请输入矩阵的大小：";
    std::cin >> mat_size;  // 输入矩阵的大小

    // 动态分配二维矩阵
    double **mat = new double *[mat_size + 1], **x = new double *[mat_size];
    for (i = 0; i <= mat_size; i++) {
        mat[i] = new double[mat_size + 1];  // 为矩阵分配内存
        if (i < mat_size)
            x[i] = new double[mat_size + 1];  // 为解向量分配内存
    }

    // 从用户获取矩阵元素
    std::cout << std::endl << "请输入矩阵的值：" << std::endl;
    for (i = 0; i < mat_size; i++) {
        for (j = 0; j <= mat_size; j++) {
            std::cin >> mat[i][j];  // 输入矩阵的每个元素
        }
    }

    // 执行高斯消去法
    for (step = 0; step < mat_size - 1; step++) {  // 按照步骤进行消去
        for (i = step; i < mat_size - 1; i++) {  // 从当前行到最后一行
            double a = (mat[i + 1][step] / mat[step][step]);  // 计算消去系数

            for (j = step; j <= mat_size; j++)  // 更新矩阵元素
                mat[i + 1][j] = mat[i + 1][j] - (a * mat[step][j]);
        }
    }

    // 输出高斯消去法处理后的矩阵
    std::cout << std::endl
              << "使用高斯消去法得到的矩阵：" << std::endl;
    for (i = 0; i < mat_size; i++) {
        for (j = 0; j <= mat_size; j++) {
            x[i][j] = mat[i][j];  // 将消去后的矩阵保存到解向量 x
            std::cout << mat[i][j] << " ";  // 输出矩阵
        }
        std::cout << std::endl;
    }

    // 输出高斯消去法得到的解
    std::cout << std::endl
              << "高斯消去法的解：" << std::endl;
    for (i = mat_size - 1; i >= 0; i--) {  // 从最后一行开始回代求解
        double sum = 0;
        for (j = mat_size - 1; j > i; j--) {  // 计算当前变量的和
            x[i][j] = x[j][j] * x[i][j];
            sum = x[i][j] + sum;
        }
        if (x[i][i] == 0)
            x[i][i] = 0;  // 如果系数为零，则解为零
        else
            x[i][i] = (x[i][mat_size] - sum) / (x[i][i]);  // 计算当前未知数的值

        std::cout << "x" << i << "= " << x[i][i] << std::endl;  // 输出当前未知数的值
    }

    // 释放动态分配的内存
    for (i = 0; i <= mat_size; i++) {
        delete[] mat[i];  // 释放矩阵的内存
        if (i < mat_size)
            delete[] x[i];  // 释放解向量的内存
    }
    delete[] mat;  // 释放矩阵的内存
    delete[] x;    // 释放解向量的内存

    return 0;
}
