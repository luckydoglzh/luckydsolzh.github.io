/**
 * @file
 * @brief [几何分布](https://en.wikipedia.org/wiki/Geometric_distribution)示例
 *
 * @details
 * 几何分布模型描述了进行伯努利试验，直到观察到一次成功为止。有两种几何分布的定义：1) 第一次成功所需的伯努利试验次数 X 的概率分布，支持在 {1, 2, 3, ...} 上；2) 第一次成功之前的失败次数 Y = X − 1 的概率分布，支持在 {0, 1, 2, 3, ...} 上。此处实现的是第一种定义。
 *
 * 常用变量：
 * p - 成功概率
 * k - 尝试次数
 *
 * @author [Domenic Zingsheim](https://github.com/DerAndereDomenic)
 */

#include <cassert>   /// 用于 assert
#include <cmath>     /// 用于数学函数
#include <cstdint>   /// 用于固定大小数据类型
#include <ctime>     /// 用于时间初始化随机数生成器
#include <iostream>  /// 用于 std::cout
#include <limits>    /// 用于 std::numeric_limits
#include <random>    /// 用于随机数
#include <vector>    /// 用于 std::vector

/**
 * @namespace probability
 * @brief 概率算法
 */
namespace probability {
/**
 * @namespace geometric_dist
 * @brief 几何分布的相关函数实现
 */
namespace geometric_dist {
/**
 * @brief 返回一个 [0,1] 之间的随机数
 * @returns 一个在 0（包括）到 1（包括）之间均匀分布的随机数
 */
float generate_uniform() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

/**
 * @brief 一个类来模拟几何分布
 */
class geometric_distribution {
 private:
    float p;  ///< 成功的概率 p

 public:
    /**
     * @brief 构造函数，初始化几何分布
     * @param p 成功的概率
     */
    explicit geometric_distribution(const float& p) : p(p) {}

    /**
     * @brief 返回几何分布随机变量 X 的期望值
     * @returns E[X] = 1 / p
     */
    float expected_value() const { return 1.0f / p; }

    /**
     * @brief 返回几何分布随机变量 X 的方差
     * @returns V[X] = (1 - p) / p^2
     */
    float variance() const { return (1.0f - p) / (p * p); }

    /**
     * @brief 返回几何分布随机变量 X 的标准差
     * @returns \sigma = \sqrt{V[X]}
     */
    float standard_deviation() const { return std::sqrt(variance()); }

    /**
     * @brief 概率密度函数
     * @details 使用几何数列的第一种定义（1），我们进行 k - 1 次失败试验，第 k 次试验为成功。
     * @param k 观察到第一次成功的试验次数，范围为 [1, ∞)
     * @returns 根据公式 p * (1 - p)^(k - 1)，返回一个介于 [0, 1] 之间的数
     */
    float probability_density(const uint32_t& k) const {
        return std::pow((1.0f - p), static_cast<float>(k - 1)) * p;
    }

    /**
     * @brief 累积分布函数
     * @details 计算所有概率的总和，直到（包括）k 次试验。基本上 CDF(k) = P(x <= k)
     * @param k 试验次数，范围为 [1, ∞)
     * @returns 在 k 次试验中成功的概率
     */
    float cumulative_distribution(const uint32_t& k) const {
        return 1.0f - std::pow((1.0f - p), static_cast<float>(k));
    }

    /**
     * @brief 逆累积分布函数
     * @details 该函数回答问题：需要多少次试验才能以给定的 CDF 概率成功？返回精确的浮动点值。
     * @param cdf 概率，范围为 [0, 1]
     * @returns 所需的精确试验次数
     */
    float inverse_cumulative_distribution(const float& cdf) const {
        return std::log(1.0f - cdf) / std::log(1.0f - p);
    }

    /**
     * @brief 根据几何分布生成一个（离散）样本
     * @returns 一个几何分布的样本，范围为 [1, ∞)
     */
    uint32_t draw_sample() const {
        float uniform_sample = generate_uniform();
        return static_cast<uint32_t>(
                   inverse_cumulative_distribution(uniform_sample)) +
               1;
    }

    /**
     * @brief 计算在给定的试验次数范围内成功的概率
     * @details 计算 P(min_tries <= x <= max_tries)。
     * 如果只给定一个最小试验次数参数，可以计算 P(x >= min_tries)。
     * 如果只给定一个最大试验次数参数，可以计算 P(x <= max_tries)。
     * @param min_tries 最小试验次数，范围为 [1, ∞)，包含该值
     * @param max_tries 最大试验次数，范围为 [min_tries, ∞)，包含该值
     * @returns 在试验次数范围 [min_tries, max_tries] 内成功的概率
     */
    float range_tries(const uint32_t& min_tries = 1,
                      const uint32_t& max_tries =
                          std::numeric_limits<uint32_t>::max()) const {
        float cdf_lower = cumulative_distribution(min_tries - 1);
        float cdf_upper = max_tries == std::numeric_limits<uint32_t>::max()
                              ? 1.0f
                              : cumulative_distribution(max_tries);
        return cdf_upper - cdf_lower;
    }
};
}  // namespace geometric_dist
}  // namespace probability

/**
 * @brief 测试几何分布的采样方法
 * @details 绘制 1000000 个随机样本，估计均值和方差，
 * 这些值应该接近给定分布的期望值和方差才能通过测试。
 * @param dist 要测试的分布
 */
void sample_test(
    const probability::geometric_dist::geometric_distribution& dist) {
    uint32_t n_tries = 1000000;
    std::vector<float> tries;
    tries.resize(n_tries);

    float mean = 0.0f;
    for (uint32_t i = 0; i < n_tries; ++i) {
        tries[i] = static_cast<float>(dist.draw_sample());
        mean += tries[i];
    }

    mean /= static_cast<float>(n_tries);

    float var = 0.0f;
    for (uint32_t i = 0; i < n_tries; ++i) {
        var += (tries[i] - mean) * (tries[i] - mean);
    }

    // 无偏方差估计
    var /= static_cast<float>(n_tries - 1);

    std::cout << "该值应该接近 " << dist.expected_value() << ": "
              << mean << std::endl;
    std::cout << "该值应该接近 " << dist.variance() << ": " << var
              << std::endl;
}

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    probability::geometric_dist::geometric_distribution dist(0.3);

    const float threshold = 1e-3f;

    std::cout << "开始测试 p = 0.3..." << std::endl;
    assert(std::abs(dist.expected_value() - 3.33333333f) < threshold);
    assert(std::abs(dist.variance() - 7.77777777f) < threshold);
    assert(std::abs(dist.standard_deviation() - 2.788866755) < threshold);
    assert(std::abs(dist.probability_density(5) - 0.07203) < threshold);
    assert(std::abs(dist.cumulative_distribution(6) - 0.882351) < threshold);
    assert(std::abs(dist.inverse_cumulative_distribution(
                        dist.cumulative_distribution(8)) - 
                    8) < threshold);
    assert(std::abs(dist.range_tries() - 1.0f) < threshold);
    assert(std::abs(dist.range_tries(3) - 0.49f) < threshold);
    assert(std::abs(dist.range_tries(5, 11) - 0.2203267f) < threshold);
    std::cout << "所有测试通过" << std::endl;
    sample_test(dist);

    dist = probability::geometric_dist::geometric_distribution(0.5f);

    std::cout << "开始测试 p = 0.5..." << std::endl;
    assert(std::abs(dist.expected_value() - 2.0f) < threshold);
    assert(std::abs(dist.variance() - 2.0f) < threshold);
    assert(std::abs(dist.standard_deviation() - 1.4142135f) < threshold);
    assert(std::abs(dist.probability_density(5) - 0.03125) < threshold);
    assert(std::abs(dist.cumulative_distribution(6) - 0.984375) < threshold);
    assert(std::abs(dist.inverse_cumulative_distribution(
                        dist.cumulative_distribution(8)) - 
                    8) < threshold);
    assert(std::abs(dist.range_tries() - 1.0f) < threshold);
    assert(std::abs(dist.range_tries(3) - 0.25f) < threshold);
    assert(std::abs(dist.range_tries(5, 11) - 0.062011f) < threshold);
    std::cout << "所有测试通过" << std::endl;
    sample_test(dist);

    dist = probability::geometric_dist::geometric_distribution(0.8f);

    std::cout << "开始测试 p = 0.8..." << std::endl;
    assert(std::abs(dist.expected_value() - 1.25f) < threshold);
    assert(std::abs(dist.variance() - 0.3125f) < threshold);
    assert(std::abs(dist.standard_deviation() - 0.559016f) < threshold);
    assert(std::abs(dist.probability_density(5) - 0.00128) < threshold);
    assert(std::abs(dist.cumulative_distribution(6) - 0.999936) < threshold);
    assert(std::abs(dist.inverse_cumulative_distribution(
                        dist.cumulative_distribution(8)) - 
                    8) < threshold);
    assert(std::abs(dist.range_tries() - 1.0f) < threshold);
    assert(std::abs(dist.range_tries(3) - 0.04f) < threshold);
    assert(std::abs(dist.range_tries(5, 11) - 0.00159997f) < threshold);
    std::cout << "所有测试已成功通过！" << std::endl;
    sample_test(dist);
}

/**
 * @brief 主函数
 * @return 0 退出
 */
int main() {
    srand(time(nullptr));
    test();  // 执行自测
    return 0;
}
