/**
 * \file
 * \brief 实时计算输入数据的统计量
 *
 * 这个算法特别适合计算实时读取的数据的统计量。比如，读取生物特征数据的设备。这个算法足够简单，可以在嵌入式系统中轻松实现。
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#include <cassert>
#include <cmath>
#include <iostream>

/**
 * \namespace statistics
 * \brief 统计学算法
 */
namespace statistics {

/**
 * 使用第一个值作为均值的近似来计算连续的均值和方差。
 * 如果第一个数与均值相差很远，这个算法会变得非常不准确，无法正确计算方差和标准差。
 */
template <typename T>
class stats_computer1 {
 public:
    /** 构造函数
     * \param[in] x 新的数据样本
     */
    void new_val(T x) {
        if (n == 0)
            K = x;  // 第一个样本直接作为初始均值
        n++;  // 样本数量加一
        T tmp = x - K;
        Ex += tmp;  // 累积样本与均值差值的和
        Ex2 += static_cast<double>(tmp) * tmp;  // 累积样本与均值差值的平方和
    }

    /** 返回当前样本的均值 */
    double mean() const { return K + Ex / n; }

    /** 返回当前样本的方差 */
    double variance() const { return (Ex2 - (Ex * Ex) / n) / (n - 1); }

    /** 返回当前样本的标准差 */
    double std() const { return std::sqrt(this->variance()); }

    /** 简化的操作符，允许直接从输入流读取新样本
     * \n 例如：`std::cin >> stats1;`
     */
    friend std::istream &operator>>(std::istream &input,
                                    stats_computer1 &stat) {
        T val;
        input >> val;
        stat.new_val(val);
        return input;
    }

 private:
    unsigned int n = 0;  // 样本数量
    double Ex = 0, Ex2 = 0;  // 样本差值和差值平方和
    T K;  // 初始均值
};

/**
 * 使用 Welford 算法（非常准确）来计算连续的均值和方差
 */
template <typename T>
class stats_computer2 {
 public:
    /** 构造函数
     * \param[in] x 新的数据样本
     */
    void new_val(T x) {
        n++;  // 样本数量加一
        double delta = x - mu;  // 当前样本与均值的差值
        mu += delta / n;  // 更新均值
        double delta2 = x - mu;  // 计算新的差值
        M += delta * delta2;  // 更新方差的累积值
    }

    /** 返回当前样本的均值 */
    double mean() const { return mu; }

    /** 返回当前样本的方差 */
    double variance() const { return M / n; }

    /** 返回当前样本的标准差 */
    double std() const { return std::sqrt(this->variance()); }

    /** 简化的操作符，允许直接从输入流读取新样本
     * \n 例如：`std::cin >> stats2;`
     */
    friend std::istream &operator>>(std::istream &input,
                                    stats_computer2 &stat) {
        T val;
        input >> val;
        stat.new_val(val);
        return input;
    }

 private:
    unsigned int n = 0;  // 样本数量
    double mu = 0, var = 0, M = 0;  // 当前均值、方差和累积值
};

}  // namespace statistics

using statistics::stats_computer1;
using statistics::stats_computer2;

/** 测试算法实现
 * \param[in] test_data 测试数据数组
 */
void test_function(const float *test_data, const int number_of_samples) {
    float mean = 0.f, variance = 0.f;

    stats_computer1<float> stats01;  // 使用第一种算法
    stats_computer2<float> stats02;  // 使用第二种算法

    // 计算数据的总和，用于计算均值
    for (int i = 0; i < number_of_samples; i++) {
        stats01.new_val(test_data[i]);
        stats02.new_val(test_data[i]);
        mean += test_data[i];
    }

    mean /= number_of_samples;  // 计算均值

    // 计算方差
    for (int i = 0; i < number_of_samples; i++) {
        float temp = test_data[i] - mean;
        variance += temp * temp;
    }
    variance /= number_of_samples;  // 计算方差

    // 打印测试结果
    std::cout << "<<<<<<<< 测试函数 >>>>>>>>" << std::endl
              << "期望结果: 均值: " << mean << "\t 方差: " << variance
              << std::endl;
    std::cout << "\t方法 1:"
              << "\t均值: " << stats01.mean()
              << "\t 方差: " << stats01.variance()
              << "\t 标准差: " << stats01.std() << std::endl;
    std::cout << "\t方法 2:"
              << "\t均值: " << stats02.mean()
              << "\t 方差: " << stats02.variance()
              << "\t 标准差: " << stats02.std() << std::endl;

    // 使用 assert 检查结果是否符合期望
    assert(std::abs(stats01.mean() - mean) < 0.01);
    assert(std::abs(stats02.mean() - mean) < 0.01);
    assert(std::abs(stats02.variance() - variance) < 0.01);

    std::cout << "(测试通过)" << std::endl;
}

/** 主函数 */
int main(int argc, char **argv) {
    // 测试数据
    const float test_data1[] = {3, 4, 5, -1.4, -3.6, 1.9, 1.};
    test_function(test_data1, sizeof(test_data1) / sizeof(test_data1[0]));

    std::cout
        << "请输入数据。任何非数字输入将终止数据输入。" << std::endl;

    stats_computer1<float> stats1;  // 方法1
    stats_computer2<float> stats2;  // 方法2

    // 循环接受用户输入的数据
    while (1) {
        double val;
        std::cout << "请输入数字: ";
        std::cin >> val;

        // 检查输入是否失败，发生非数字输入时退出
        if (std::cin.fail())
            break;

        stats1.new_val(val);
        stats2.new_val(val);

        // 输出当前统计结果
        std::cout << "\t方法 1:"
                  << "\t均值: " << stats1.mean()
                  << "\t 方差: " << stats1.variance()
                  << "\t 标准差: " << stats1.std() << std::endl;
        std::cout << "\t方法 2:"
                  << "\t均值: " << stats2.mean()
                  << "\t 方差: " << stats2.variance()
                  << "\t 标准差: " << stats2.std() << std::endl;
    }

    return 0;
}
