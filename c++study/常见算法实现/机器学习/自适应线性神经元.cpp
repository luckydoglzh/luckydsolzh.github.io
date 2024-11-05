/**
 * \addtogroup machine_learning 机器学习算法
 * @{
 * \file
 * \brief [自适应线性神经元
 * (ADALINE)](https://en.wikipedia.org/wiki/ADALINE) 实现
 *
 * \author [Krishna Vedala](https://github.com/kvedala)
 *
 * \details
 * <a href="https://commons.wikimedia.org/wiki/File:Adaline_flow_chart.gif"><img
 * src="https://upload.wikimedia.org/wikipedia/commons/b/be/Adaline_flow_chart.gif"
 * alt="ADALINE网络结构。来源：维基百科"
 * style="width:200px; float:right;"></a>
 *
 * ADALINE 是一种最早和最简单的单层人工神经网络。该算法本质上实现了一个线性函数
 * \f[ f\left(x_0,x_1,x_2,\ldots\right) =
 * \sum_j x_jw_j+\theta
 * \f]
 * 其中，\f$x_j\f$ 是样本的输入特征，\f$w_j\f$ 是线性函数的系数，\f$\theta\f$ 是常数。
 * 如果我们知道 \f$w_j\f$，那么对于给定的一组特征，\f$y\f$ 可以被计算出来。计算 \f$w_j\f$
 * 是一种监督学习算法，使用一组特征和它们对应的输出，并通过随机梯度下降法计算权重。
 */

#include <array>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <vector>

/** 学习的最大迭代次数 */
constexpr int MAX_ITER = 500;  // INT_MAX

/** \namespace machine_learning
 * \brief 机器学习算法
 */
namespace machine_learning {
class adaline {
 public:
    /**
     * 默认构造函数
     * \param[in] num_features 特征数量
     * \param[in] eta 学习率（可选，默认=0.1）
     * \param[in] accuracy 收敛精度（可选，
     * 默认=\f$1\times10^{-5}\f$）
     */
    explicit adaline(int num_features, const double eta = 0.01f,
                     const double accuracy = 1e-5)
        : eta(eta), accuracy(accuracy) {
        if (eta <= 0) {
            std::cerr << "学习率应为正数且非零" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        weights = std::vector<double>(
            num_features +
            1);  // 额外的权重用于常数偏置项

        // 用范围 [-50, 49] 内的随机权重初始化
        for (double &weight : weights) weight = 1.f;
        // weights[i] = (static_cast<double>(std::rand() % 100) - 50);
    }

    /**
     * 重载输出流运算符，用于打印模型的权重
     */
    friend std::ostream &operator<<(std::ostream &out, const adaline &ada) {
        out << "<";
        for (int i = 0; i < ada.weights.size(); i++) {
            out << ada.weights[i];
            if (i < ada.weights.size() - 1) {
                out << ", ";
            }
        }
        out << ">";
        return out;
    }

    /**
     * 预测模型输出，对于给定的一组特征
     * \param[in] x 输入向量
     * \param[out] out 可选参数，用于返回激活函数前的神经元输出
     * （可选，`nullptr` 忽略） \returns 模型预测输出
     */
    int predict(const std::vector<double> &x, double *out = nullptr) {
        if (!check_size_match(x)) {
            return 0;
        }

        double y = weights.back();  // 分配偏置值

        // for (int i = 0; i < x.size(); i++) y += x[i] * weights[i];
        y = std::inner_product(x.begin(), x.end(), weights.begin(), y);

        if (out != nullptr) {  // 如果提供了 out 变量
            *out = y;
        }

        return activation(y);  // 量化器：应用 ADALINE 阈值函数
    }

    /**
     * 使用监督学习更新模型的权重，对于一个特征向量
     * \param[in] x 特征向量
     * \param[in] y 已知输出值
     * \returns 校正因子
     */
    double fit(const std::vector<double> &x, const int &y) {
        if (!check_size_match(x)) {
            return 0;
        }

        /* 当前权重的模型输出 */
        int p = predict(x);
        int prediction_error = y - p;  // 估计误差
        double correction_factor = eta * prediction_error;

        /* 更新每个权重，最后一个权重是偏置项 */
        for (int i = 0; i < x.size(); i++) {
            weights[i] += correction_factor * x[i];
        }
        weights[x.size()] += correction_factor;  // 更新偏置

        return correction_factor;
    }

    /**
     * 使用监督学习更新模型的权重，对于一个特征向量数组
     * \param[in] X 特征向量数组
     * \param[in] y 每个特征向量对应的已知输出值
     */
    template <size_t N>
    void fit(std::array<std::vector<double>, N> const &X,
             std::array<int, N> const &Y) {
        double avg_pred_error = 1.f;

        int iter = 0;
        for (iter = 0; (iter < MAX_ITER) && (avg_pred_error > accuracy);
             iter++) {
            avg_pred_error = 0.f;

            // 对每个样本进行拟合
            for (int i = 0; i < N; i++) {
                double err = fit(X[i], Y[i]);
                avg_pred_error += std::abs(err);
            }
            avg_pred_error /= N;

            // 每隔200次迭代打印更新
            // if (iter % 100 == 0)
            std::cout << "\t迭代 " << iter << ": 训练权重: " << *this
                      << "\t平均误差: " << avg_pred_error << std::endl;
        }

        if (iter < MAX_ITER) {
            std::cout << "在 " << iter << " 次迭代后收敛。" << std::endl;
        } else {
            std::cout << "在 " << iter << " 次迭代后未收敛。" << std::endl;
        }
    }

    /** 定义激活函数为海维赛德阶跃函数。
     * \f[
     * f(x) = \begin{cases}
     * -1 & \forall x \le 0\\
     *  1 & \forall x > 0
     * \end{cases}
     * \f]
     * @param x 输入值，应用激活函数
     * @return 激活输出
     */
    int activation(double x) { return x > 0 ? 1 : -1; }

 private:
    /**
     * 检查输入特征向量的大小是否与模型权重的大小匹配的便捷函数
     * \param[in] x 要检查的特征向量
     * \returns `true` 大小匹配
     * \returns `false` 大小不匹配
     */
    bool check_size_match(const std::vector<double> &x) {
        if (x.size() != (weights.size() - 1)) {
            std::cerr << __func__ << ": "
                      << "x中的特征数与模型中的特征维度不匹配！"
                      << std::endl;
            return false;
        }
        return true;
    }

    const double eta;             ///< 算法的学习率
    const double accuracy;        ///< 模型拟合收敛精度
    std::vector<double> weights;  ///< 神经网络的权重
};

}  // namespace machine_learning

using machine_learning::adaline;

/** @} */

/**
 * 测试函数，在二维坐标系中预测点是否在直线 \f$x=y\f$ 上方
 * 上方为+1，其余为-1。
 * 注意每个点由2个值或2个特征定义。
 * \param[in] eta 学习率（可选，默认=0.01）
 */
void test1(double eta = 0.01) {
    adaline ada(2, eta);  // 2个特征

    const int N = 10;  // 样本点数量

    std::array<std::vector<double>, N> X = {
        std::vector<double>({0, 1}),   std::vector<double>({1, -2}),
        std::vector<double>({2, 3}),   std::vector<double>({3, -1}),
        std::vector<double>({4, 1}),   std::vector<double>({-1, 1}),
        std::vector<double>({-2, 2}),  std::vector<double>({-3, 2}),
        std::vector<double>({-4, -4}), std::vector<double>({5, 3})};

    std::array<int, N> y = {-1, -1, +1, -1, +1, -1, -1, -1, -1, +1};

    ada.fit(X, y);  // 训练模型

    std::cout << "训练后模型的权重：" << ada << std::endl;

    std::cout << "进行预测..." << std::endl;

    std::array<int, N> p{};
    for (int i = 0; i < N; i++) {
        p[i] = ada.predict(X[i]);
        std::cout << "点 " << i << " " << X[i][0] << "," << X[i][1] << "\t => "
                  << (p[i] == 1 ? "上方" : "其他") << std::endl;
    }
}

/** 主函数 */
int main(int argc, char *argv[]) {
    double eta = 0.01f;

    if (argc == 2) {
        eta = std::atof(argv[1]);
    }
    test1(eta);

    return 0;
}
