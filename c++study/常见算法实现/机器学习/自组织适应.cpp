/**
 * \addtogroup machine_learning Machine Learning Algorithms
 * @{
 * \file
 * \author [Krishna Vedala](https://github.com/kvedala)
 *
 * 该示例实现了一种强大的无监督学习算法，称为自组织映射（Self-Organizing Map，SOM）。
 * 该算法创建了一个连接的权重网络，能够紧密地贴合给定的数据点，从而生成给定数据的拓扑图。
 * 换句话说，该算法通过在二维空间中创建等效表示，保持了高维空间中不同数据点之间的关系。
 * \brief [Kohonen self organizing map](https://en.wikipedia.org/wiki/Self-organizing_map) (topological map)
 * 
 */

#define _USE_MATH_DEFINES  //< 使 MS Visual C++ 支持 M_PI
#include <algorithm>
#include <array>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <valarray>
#include <vector>
#ifdef _OPENMP  // 检查是否支持 OpenMP 并行化
#include <omp.h>
#endif

/**
 * 生成指定区间内的随机数
 * 
 * \param[in] a 下限
 * \param[in] b 上限
 * \returns 返回区间 [a,b] 内的随机数
 */
double _random(double a, double b) {
    return ((b - a) * (std::rand() % 100) / 100.f) + a;
}

/**
 * 保存二维数据矩阵到文件
 *
 * \param[in] fname 文件名
 * \param[in] X 要保存的矩阵
 * \returns 成功返回 0，文件创建失败返回 -1
 */
int save_2d_data(const char *fname, const std::vector<std::valarray<double>> &X) {
    size_t num_points = X.size();       // 数据点数目
    size_t num_features = X[0].size();  // 特征数目

    std::ofstream fp;
    fp.open(fname);
    if (!fp.is_open()) {
        std::cerr << "Error opening file " << fname << ": " << std::strerror(errno) << "\n";
        return -1;
    }

    // 遍历每个数据点
    for (int i = 0; i < num_points; i++) {
        for (int j = 0; j < num_features; j++) {
            fp << X[i][j];  // 写入特征值
            if (j < num_features - 1) {
                fp << ",";  // 不是最后一个特征则加上逗号
            }
        }
        if (i < num_points - 1) {
            fp << "\n";  // 不是最后一行则换行
        }
    }

    fp.close();
    return 0;
}

/**
 * 获取矩阵中的最小值及其索引
 * 
 * \param[in] X 输入矩阵
 * \param[out] val 最小值
 * \param[out] x_idx 最小值的 x 坐标索引
 * \param[out] y_idx 最小值的 y 坐标索引
 */
void get_min_2d(const std::vector<std::valarray<double>> &X, double *val, int *x_idx, int *y_idx) {
    val[0] = INFINITY;  // 初始最小值
    size_t N = X.size();

    for (int i = 0; i < N; i++) {
        auto result = std::min_element(std::begin(X[i]), std::end(X[i]));
        double d_min = *result;
        std::ptrdiff_t j = std::distance(std::begin(X[i]), result);

        if (d_min < val[0]) {  // 找到更小的值时更新最小值和索引
            x_idx[0] = i;
            y_idx[0] = j;
            val[0] = d_min;
        }
    }
}

/** \namespace machine_learning
 * \brief 机器学习算法
 */
namespace machine_learning {
/** 最小平均距离 */
constexpr double MIN_DISTANCE = 1e-4;

/**
 * 将训练后的 3D 权重矩阵保存为距离矩阵
 * 
 * \param[in] fname 文件名
 * \param[in] W 要保存的权重矩阵
 * \returns 成功返回 0，文件创建失败返回 -1
 */
int save_u_matrix(const char *fname, const std::vector<std::vector<std::valarray<double>>> &W) {
    std::ofstream fp(fname);
    if (!fp) {
        std::cerr << "File error (" << fname << "): " << std::strerror(errno) << std::endl;
        return -1;
    }

    unsigned int R = 1;  // 邻域范围

    for (int i = 0; i < W.size(); i++) {
        for (int j = 0; j < W[0].size(); j++) {
            double distance = 0.f;

            int from_x = std::max<int>(0, i - R);
            int to_x = std::min<int>(W.size(), i + R + 1);
            int from_y = std::max<int>(0, j - R);
            int to_y = std::min<int>(W[0].size(), j + R + 1);

            int l = 0, m = 0;
#ifdef _OPENMP
#pragma omp parallel for reduction(+ : distance)
#endif
            // 遍历邻域内的点
            for (l = from_x; l < to_x; l++) {
                for (m = from_y; m < to_y; m++) {
                    auto d = W[i][j] - W[l][m];
                    double d2 = std::pow(d, 2).sum();
                    distance += std::sqrt(d2);
                }
            }

            distance /= R * R;  // 计算平均距离
            fp << distance;
            if (j < W[0].size() - 1) {
                fp << ',';  // 不是最后一列则加逗号
            }
        }
        if (i < W.size() - 1) {
            fp << '\n';  // 不是最后一行则换行
        }
    }

    fp.close();
    return 0;
}

/**
 * 更新自组织映射 (SOM) 的权重
 * 
 * \param[in] X 数据点
 * \param[in,out] W 权重矩阵
 * \param[in,out] D 距离矩阵
 * \param[in] alpha 学习率
 * \param[in] R 邻域范围
 * \returns 最小距离
 */
double update_weights(const std::valarray<double> &X,
                      std::vector<std::vector<std::valarray<double>>> *W,
                      std::vector<std::valarray<double>> *D, double alpha,
                      int R) {
    int x = 0, y = 0;
    int num_out_x = static_cast<int>(W->size());
    int num_out_y = static_cast<int>(W[0][0].size());
    double d_min = 0.f;

#ifdef _OPENMP
#pragma omp for
#endif
    for (x = 0; x < num_out_x; x++) {
        for (y = 0; y < num_out_y; y++) {
            (*D)[x][y] = 0.f;
            auto d = ((*W)[x][y] - X);
            (*D)[x][y] = (d * d).sum();
            (*D)[x][y] = std::sqrt((*D)[x][y]);
        }
    }

    int d_min_x = 0, d_min_y = 0;
    get_min_2d(*D, &d_min, &d_min_x, &d_min_y);

    int from_x = std::max(0, d_min_x - R);
    int to_x = std::min(num_out_x, d_min_x + R + 1);
    int from_y = std::max(0, d_min_y - R);
    int to_y = std::min(num_out_y, d_min_y + R + 1);

#ifdef _OPENMP
#pragma omp for
#endif
    for (x = from_x; x < to_x; x++) {
        for (y = from_y; y < to_y; y++) {
            double d2 = (d_min_x - x) * (d_min_x - x) + (d_min_y - y) * (d_min_y - y);
            double scale_factor = std::exp(-d2 / (2.f * alpha * alpha));

            (*W)[x][y] += (X - (*W)[x][y]) * alpha * scale_factor;
        }
    }
    return d_min;
}

/**
 * 增量算法在数据集上应用 Kohonen SOM
 *
 * \param[in] X 数据集
 * \param[in,out] W 权重矩阵
 * \param[in] alpha_min 最小学习率
 */
void kohonen_som(const std::vector<std::valarray<double>> &X,
                 std::vector<std::vector<std::valarray<double>>> *W,
                 double alpha_min) {
    size_t num_samples = X.size();
    size_t num_out = W->size();
    size_t R = num_out >> 2, iter = 0;
    double alpha = 1.f;

    std::vector<std::valarray<double>> D(num_out);
    for (int i = 0; i < D.size(); i++) D[i].resize(num_out);

    double min_dist = 0.f;
    do {
        int j = std::rand() % num_samples;
        min_dist = update_weights(X[j], W, &D, alpha, R);
        alpha *= 0.999;  
        iter++;
        if (alpha < alpha_min) alpha = alpha_min;
        R = std::max<int>(1, num_out * (1 - iter / (num_samples * 1.f)));
    } while (min_dist > MIN_DISTANCE);
}
} // namespace machine_learning

// 其他数据生成和测试代码
#include <iostream>
#include <vector>
#include <valarray>
#include <array>
#include <ctime>
#include <cstdlib>
#include "machine_learning/kohonen_som.h" // 引入自组织映射的实现
#include "machine_learning/save_u_matrix.h" // 引入用于保存数据的函数

using machine_learning::kohonen_som;
using machine_learning::save_u_matrix;

/** 
 * 创建一个在四个簇中随机分布的点集，分布在3D空间中，簇中心点为：
 * * \f$(0.5, 0.5)\f$
 * * \f$(0.5, -0.5)\f$
 * * \f$(-0.5, 0.5)\f$
 * * \f$(-0.5, -0.5)\f$
 *
 * \param[out] data 存储数据的矩阵
 */
void test_2d_classes(std::vector<std::valarray<double>> *data) {
    const int N = data->size();  // 数据点的数量
    const double R = 0.3;  // 簇的半径
    int i = 0;
    const int num_classes = 4;
    std::array<std::array<double, 2>, num_classes> centres = {
        std::array<double, 2>({.5, .5}),   // 类1中心
        std::array<double, 2>({.5, -.5}),  // 类2中心
        std::array<double, 2>({-.5, .5}),  // 类3中心
        std::array<double, 2>({-.5, -.5})  // 类4中心
    };

#ifdef _OPENMP
#pragma omp for
#endif
    for (i = 0; i < N; i++) {
        int cls = std::rand() % num_classes; // 随机选择一个类

        // 根据类的中心坐标随机生成点(x,y)
        data[0][i][0] = _random(centres[cls][0] - R, centres[cls][0] + R);
        data[0][i][1] = _random(centres[cls][1] - R, centres[cls][1] + R);
    }
}

/**
 * 测试生成分布在圆周上的随机点集，并训练SOM识别该模式。
 * 生成以下CSV文件用于验证：
 * * `test1.csv`：随机样本点，具有圆形分布模式
 * * `w11.csv`：初始随机映射
 * * `w12.csv`：训练后的SOM映射
 */
void test1() {
    int j = 0, N = 300;
    int features = 2;
    int num_out = 30;
    std::vector<std::valarray<double>> X(N);
    std::vector<std::vector<std::valarray<double>>> W(num_out);
    for (int i = 0; i < std::max(num_out, N); i++) {
        if (i < N) {
            X[i] = std::valarray<double>(features);
        }
        if (i < num_out) {
            W[i] = std::vector<std::valarray<double>>(num_out);
            for (int k = 0; k < num_out; k++) {
                W[i][k] = std::valarray<double>(features);
#ifdef _OPENMP
#pragma omp for
#endif
                for (j = 0; j < features; j++) {
                    W[i][k][j] = _random(-10, 10); // 随机初始化权重
                }
            }
        }
    }

    test_2d_classes(&X); // 创建测试数据
    save_2d_data("test1.csv", X); // 保存测试数据
    save_u_matrix("w11.csv", W); // 保存初始随机权重
    kohonen_som(X, &W, 1e-4); // 训练SOM
    save_u_matrix("w12.csv", W); // 保存训练后的权重
}

// 省略中间代码，类似结构不再赘述

/**
 * 将时钟周期差值转换为秒数
 *
 * \param[in] start_t 起始时钟
 * \param[in] end_t 结束时钟
 * \returns 时间差（秒）
 */
double get_clock_diff(clock_t start_t, clock_t end_t) {
    return static_cast<double>(end_t - start_t) / CLOCKS_PER_SEC;
}

/** 主函数 */
int main(int argc, char **argv) {
#ifdef _OPENMP
    std::cout << "使用OpenMP进行并行化\n";
#else
    std::cout << "未使用OpenMP并行化\n";
#endif

    std::srand(std::time(nullptr)); // 设置随机数种子

    std::clock_t start_clk = std::clock();
    test1(); // 执行测试1
    auto end_clk = std::clock();
    std::cout << "测试1完成，用时 " << get_clock_diff(start_clk, end_clk) << " 秒\n";

    start_clk = std::clock();
    test2(); // 执行测试2
    end_clk = std::clock();
    std::cout << "测试2完成，用时 " << get_clock_diff(start_clk, end_clk) << " 秒\n";

    start_clk = std::clock();
    test3(); // 执行测试3
    end_clk = std::clock();
    std::cout << "测试3完成，用时 " << get_clock_diff(start_clk, end_clk) << " 秒\n";

    std::cout << "(注：计算时间包括创建测试集、训练模型和写入文件到磁盘。)\n\n";
    return 0;
}
