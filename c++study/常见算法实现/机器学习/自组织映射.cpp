/**
 * \addtogroup machine_learning 机器学习算法
 * @{
 * \file
 * \brief [Kohonen 自组织映射](https://en.wikipedia.org/wiki/Self-organizing_map)（数据追踪）
 *
 * 本示例实现了一个强大的自组织映射算法。
 * 该算法创建一个权重的连接网络，紧密跟随给定的数据点。这创造了一系列节点，类似于给定输入的形状。
 *
 * \author [Krishna Vedala](https://github.com/kvedala)
 *
 * \note 此 C++ 版本的程序比其 [C 版本](https://github.com/kvedala/C/blob/master/machine_learning/kohonen_som_trace.c)明显较慢
 * \note 与 GCC 在 Windows 上编译的代码相比，使用 MS Visual C++ 2019 编译的代码速度更慢
 * \see kohonen_som_topology.cpp
 */
#define _USE_MATH_DEFINES  // 为 MS Visual C++ 所需
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <valarray>
#include <vector>
#ifdef _OPENMP  // 检查是否可用基于 OpenMP 的并行化
#include <omp.h>
#endif

/**
 * 生成给定区间内的随机数的辅助函数。
 * \n 步骤：
 * 1. `r1 = rand() % 100` 获取一个 0 到 99 之间的随机数
 * 2. `r2 = r1 / 100` 将随机数转换为 0 到 0.99 之间
 * 3. 将随机数缩放并偏移到给定范围 \f$[a,b]\f$
 *
 * \param[in] a 下限
 * \param[in] b 上限
 * \returns 随机数，范围在 \f$[a,b]\f$ 之间
 */
double _random(double a, double b) {
    return ((b - a) * (std::rand() % 100) / 100.f) + a;
}

/**
 * 将给定 n 维数据矩阵保存到文件。
 *
 * \param[in] fname 要保存的文件名（无确认覆盖）
 * \param[in] X 要保存的矩阵
 * \returns 0 如果一切正常
 * \returns -1 如果文件创建失败
 */
int save_nd_data(const char *fname,
                 const std::vector<std::valarray<double>> &X) {
    size_t num_points = X.size();       // 行数
    size_t num_features = X[0].size();  // 列数

    std::ofstream fp;
    fp.open(fname);
    if (!fp.is_open()) {
        // 打开文件以进行写入时出错
        std::cerr << "打开文件 " << fname << " 时出错\n";
        return -1;
    }

    // 对于数组中的每个点
    for (int i = 0; i < num_points; i++) {
        // 对于数组中的每个特征
        for (int j = 0; j < num_features; j++) {
            fp << X[i][j];               // 打印特征值
            if (j < num_features - 1) {  // 如果不是最后一个特征
                fp << ",";               // 后缀逗号
            }
        }
        if (i < num_points - 1) {  // 如果不是最后一行
            fp << "\n";            // 开始新行
        }
    }

    fp.close();
    return 0;
}

/** \namespace machine_learning
 * \brief 机器学习算法
 */
namespace machine_learning {

/**
 * 使用 Kohonen 算法更新 SOM 权重
 *
 * \param[in] x 数据点
 * \param[in,out] W 权重矩阵
 * \param[in,out] D 临时向量，用于存储距离
 * \param[in] alpha 学习率 \f$0<\alpha\le1\f$
 * \param[in] R 邻域范围
 */
void update_weights(const std::valarray<double> &x,
                    std::vector<std::valarray<double>> *W,
                    std::valarray<double> *D, double alpha, int R) {
    int j = 0, k = 0;
    int num_out = W->size();  // SOM 输出节点的数量
    // int num_features = x.size();  // 数据特征的数量

#ifdef _OPENMP
#pragma omp for
#endif
    // 步骤 1：对于每个输出点
    for (j = 0; j < num_out; j++) {
        // 计算每个输出点与当前样本的欧几里得距离
        (*D)[j] = (((*W)[j] - x) * ((*W)[j] - x)).sum();
    }

    // 步骤 2：获取最近的节点，即与当前模式距离最小的节点
    auto result = std::min_element(std::begin(*D), std::end(*D));
    // double d_min = *result;
    int d_min_idx = std::distance(std::begin(*D), result);

    // 步骤 3a：获取邻域范围
    int from_node = std::max(0, d_min_idx - R);
    int to_node = std::min(num_out, d_min_idx + R + 1);

    // 步骤 3b：更新邻域内节点的权重
#ifdef _OPENMP
#pragma omp for
#endif
    for (j = from_node; j < to_node; j++) {
        // 更新邻域内节点的权重
        (*W)[j] += alpha * (x - (*W)[j]);
    }
}

/**
 * 在给定数据集的所有样本上应用增量算法，更新邻域和学习率
 *
 * \param[in] X 数据集
 * \param[in,out] W 权重矩阵
 * \param[in] alpha_min 学习率的终止值
 */
void kohonen_som_tracer(const std::vector<std::valarray<double>> &X,
                        std::vector<std::valarray<double>> *W,
                        double alpha_min) {
    int num_samples = X.size();  // 行数
    // int num_features = X[0].size();  // 列数
    int num_out = W->size();  // 行数
    int R = num_out >> 2, iter = 0;
    double alpha = 1.f;

    std::valarray<double> D(num_out);

    // 循环 alpha 从 1 到 alpha_min
    do {
        // 对于数据集中的每个样本模式循环
        for (int sample = 0; sample < num_samples; sample++) {
            // 更新当前输入模式样本的权重
            update_weights(X[sample], W, &D, alpha, R);
        }

        // 每 10 次迭代，减少邻域范围
        if (iter % 10 == 0 && R > 1) {
            R--;
        }

        alpha -= 0.01;  // 降低学习率
        iter++;
    } while (alpha > alpha_min);
}

}  // namespace machine_learning

/** @} */

using machine_learning::kohonen_som_tracer;

/** 创建一组随机点，这些点分布在一个圆的周围，并训练一个 SOM 来找到这个圆形模式。生成函数为
 * \f{eqnarray*}{
 * r &\in& [1-\delta r, 1+\delta r)\\
 * \theta &\in& [0, 2\pi)\\
 * x &=& r\cos\theta\\
 * y &=& r\sin\theta
 * \f}
 *
 * \param[out] data 用于存储数据的矩阵
 */
void test_circle(std::vector<std::valarray<double>> *data) {
    const int N = data->size();
    const double R = 0.75, dr = 0.3;
    double a_t = 0., b_t = 2.f * M_PI;  // theta 在 0 到 2*pi 之间随机
    double a_r = R - dr, b_r = R + dr;  // 半径在 R-dr 到 R+dr 之间随机
    int i = 0;

#ifdef _OPENMP
#pragma omp for
#endif
    for (i = 0; i < N; i++) {
        double r = _random(a_r, b_r);      // 随机半径
        double theta = _random(a_t, b_t);  // 随机 theta
        data[0][i][0] = r * cos(theta);    // 从极坐标转换为笛卡尔坐标
        data[0][i][1] = r * sin(theta);
    }
}

/** 测试创建一组随机点，这些点分布在一个圆的周围，并训练一个 SOM 来找到这个圆形模式。
 * 以下 [CSV](https://en.wikipedia.org/wiki/Comma-separated_values) 文件用于验证执行情况。
 *
 * - `data.csv` 输入数据
 * - `weights.csv` 输出权重
 */
int main() {
    std::srand(std::time(0));  // 以时间为种子初始化随机数生成器
    const int N = 300;  // 数据点数量
    const int N_w = 100;  // 权重矩阵大小
    std::vector<std::valarray<double>> data(N);  // 存储数据点的矩阵

    for (int i = 0; i < N; i++) {
        data[i] = std::valarray<double>(2);  // 每个数据点有 2 个特征（x 和 y）
    }

    test_circle(&data);  // 测试生成随机圆形点

    // 初始化权重矩阵
    std::vector<std::valarray<double>> weights(N_w);
    for (int i = 0; i < N_w; i++) {
        weights[i] = std::valarray<double>(2);  // 每个权重节点也有 2 个特征
        for (int j = 0; j < 2; j++) {
            weights[i][j] = _random(-1., 1.);  // 随机初始化权重
        }
    }

    save_nd_data("data.csv", data);      // 将输入数据保存到文件
    kohonen_som_tracer(data, &weights, 0.01);  // 训练 SOM
    save_nd_data("weights.csv", weights);  // 将输出权重保存到文件

    return 0;
}
/**
 * 将时钟周期差转换为秒数
 *
 * \param[in] start_t 开始时钟
 * \param[in] end_t 结束时钟
 * \returns 时间差，单位为秒
 */
double get_clock_diff(clock_t start_t, clock_t end_t) {
    return static_cast<double>(end_t - start_t) / CLOCKS_PER_SEC;  // 返回以秒为单位的时间差
}

/** 主函数 */
int main(int argc, char **argv) {
#ifdef _OPENMP
    std::cout << "使用基于 OpenMP 的并行化\n";  // 如果启用了 OpenMP，则输出相应的信息
#else
    std::cout << "未使用基于 OpenMP 的并行化\n";  // 如果未启用 OpenMP，则输出相应的信息
#endif

    std::srand(std::time(nullptr));  // 使用当前时间初始化随机数生成器

    std::clock_t start_clk = std::clock();  // 记录开始时钟
    test1();  // 执行测试 1
    auto end_clk = std::clock();  // 记录结束时钟
    std::cout << "测试 1 完成，耗时 " << get_clock_diff(start_clk, end_clk)
              << " 秒\n";  // 输出测试 1 的耗时

    start_clk = std::clock();  // 记录开始时钟
    test2();  // 执行测试 2
    end_clk = std::clock();  // 记录结束时钟
    std::cout << "测试 2 完成，耗时 " << get_clock_diff(start_clk, end_clk)
              << " 秒\n";  // 输出测试 2 的耗时

    start_clk = std::clock();  // 记录开始时钟
    test3();  // 执行测试 3
    end_clk = std::clock();  // 记录结束时钟
    std::cout << "测试 3 完成，耗时 " << get_clock_diff(start_clk, end_clk)
              << " 秒\n";  // 输出测试 3 的耗时

    std::cout
        << "(注意：计算的时间包括：创建测试集、训练模型和将文件写入磁盘的时间。）\n\n";
    return 0;  // 程序正常结束
}
