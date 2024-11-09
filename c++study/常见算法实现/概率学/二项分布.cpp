/**
 * @file
 * @brief [二项分布](https://en.wikipedia.org/wiki/Binomial_distribution) 示例
 *
 * 二项分布模型描述了在一系列独立的 n 次实验中，成功的次数。
 *
 * 使用的变量总结：
 * * n : 实验次数
 * * p : 单次实验成功的概率
 * * x : 所需的成功次数
 */
#include <cmath>
#include <iostream>

/** 
 * @brief 计算二项分布的期望值
 * @param [in] n 实验次数
 * @param [in] p 单次实验成功的概率
 * @returns \f$\mu = np\f$，即期望值
 */
double binomial_expected(double n, double p) { return n * p; }

/** 
 * @brief 计算二项分布的方差
 * @param [in] n 实验次数
 * @param [in] p 单次实验成功的概率
 * @returns \f$\sigma^2 = n \cdot p \cdot (1 - p)\f$，即方差
 */
double binomial_variance(double n, double p) { return n * p * (1 - p); }

/** 
 * @brief 计算二项分布的标准差
 * @param [in] n 实验次数
 * @param [in] p 单次实验成功的概率
 * @returns \f$\sigma = \sqrt{\sigma^2} = \sqrt{n \cdot p \cdot (1 - p)}\f$，即标准差
 */
double binomial_standard_deviation(double n, double p) {
    return std::sqrt(binomial_variance(n, p));
}

/** 
 * @brief 计算组合数，即从 n 个中选 r 个的组合数
 * @param [in] n 总数
 * @param [in] r 选择的数量
 * @returns 组合数 \f$\displaystyle {n \choose r} =
 * \frac{n!}{r!(n - r)!} = \frac{n \times (n-1) \times (n-2) \times \cdots (n-r)}{r!}
 * \f$
 */
double nCr(double n, double r) {
    double numerator = n;
    double denominator = r;

    // 计算分子的乘积
    for (int i = n - 1; i >= ((n - r) + 1); i--) {
        numerator *= i;
    }

    // 计算分母的阶乘
    for (int i = 1; i < r; i++) {
        denominator *= i;
    }

    return numerator / denominator;  ///< 返回组合数
}

/** 
 * @brief 计算恰好 x 次成功的概率
 * @returns \f$\displaystyle P(n,p,x) = {n \choose x} p^x (1-p)^{n-x}\f$，即恰好 x 次成功的概率
 */
double binomial_x_successes(double n, double p, double x) {
    return nCr(n, x) * std::pow(p, x) * std::pow(1 - p, n - x);  ///< 计算概率
}

/** 
 * @brief 计算在指定范围内（包含边界）成功的概率
 * @returns \f$\displaystyle \left.P(n,p)\right|_{x_0}^{x_1} =
 * \sum_{i=x_0}^{x_1} P(i) = \sum_{i=x_0}^{x_1} {n \choose i} p^i (1-p)^{n-i}\f$
 * @param [in] n 实验次数
 * @param [in] p 单次实验成功的概率
 * @param [in] lower_bound 范围的下界
 * @param [in] upper_bound 范围的上界
 * @returns 在范围 [x0, x1] 内成功的概率
 */
double binomial_range_successes(double n, double p, double lower_bound,
                                double upper_bound) {
    double probability = 0;
    // 在指定范围内计算成功的概率
    for (int i = lower_bound; i <= upper_bound; i++) {
        probability += nCr(n, i) * std::pow(p, i) * std::pow(1 - p, n - i);
    }
    return probability;  ///< 返回范围内的总概率
}

/** 
 * @brief 主函数，演示如何使用二项分布函数
 * @returns 0 退出程序
 */
int main() {
    // 计算并输出期望值
    std::cout << "期望值 : " << binomial_expected(100, 0.5) << std::endl;

    // 计算并输出方差
    std::cout << "方差 : " << binomial_variance(100, 0.5) << std::endl;

    // 计算并输出标准差
    std::cout << "标准差 : " << binomial_standard_deviation(100, 0.5) << std::endl;

    // 计算并输出恰好 30 次成功的概率
    std::cout << "恰好 30 次成功的概率 : " << binomial_x_successes(100, 0.5, 30)
              << std::endl;

    // 计算并输出至少 45 次成功的概率
    std::cout << "45 次或更多成功的概率 : "
              << binomial_range_successes(100, 0.5, 45, 100) << std::endl;

    return 0;  ///< 结束程序
}
