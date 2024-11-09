/**
 * @file
 * @brief [泊松统计](https://en.wikipedia.org/wiki/Poisson_distribution)
 *
 * 泊松分布用来计算在某个固定时间间隔内发生多少个事件。
 */
#include <cmath>
#include <iostream>

/**
 * @brief 计算泊松分布的事件率
 * 
 * @details
 * 事件率是指单位时间内发生事件的数量。例如：
 * 每2分钟发生5个事件，那么事件率为 5 / 2 = 2.5。
 * @param events 事件的数量
 * @param timeframe 时间框架，单位时间
 * @return 事件率
 */
double poisson_rate(double events, double timeframe) {
    return events / timeframe;
}

/**
 * @brief 计算在给定时间内的期望值
 * 
 * @details
 * 例如，事件率为 2.5，时间框架为 10 分钟，那么期望事件数量为 2.5 * 10 = 25。
 * @param rate 事件率
 * @param time 时间框架
 * @return 期望的事件数量
 */
double poisson_expected(double rate, double time) { return rate * time; }

/**
 * @brief 计算给定数字的阶乘
 * @param x 输入数字
 * @return x 的阶乘
 */
double fact(double x) {
    double x_fact = x;
    for (int i = x - 1; i > 0; i--) {
        x_fact *= i;  // 计算阶乘
    }

    if (x_fact <= 0) {
        x_fact = 1;  // 如果阶乘结果为 0，则返回 1
    }
    return x_fact;
}

/**
 * @brief 计算在泊松分布下，发生 x 次成功的概率
 * @details
 * 使用公式：\f[p(\mu,x) = \frac{\mu^x e^{-\mu}}{x!}\f]
 * @param expected 期望值
 * @param x 成功次数
 * @return x 次成功的概率
 */
double poisson_x_successes(double expected, double x) {
    return (std::pow(expected, x) * std::exp(-expected)) / fact(x);
}

/**
 * @brief 计算在泊松分布下，成功次数在指定范围内的概率（包括上下界）
 * @details
 * 计算公式：\f[P = \sum_i p(\mu,i)\f]
 * 计算从 lower 到 upper 之间所有成功次数的概率总和
 * @param expected 期望值
 * @param lower 最低成功次数
 * @param upper 最高成功次数
 * @return 在给定范围内成功的概率
 */
double poisson_range_successes(double expected, double lower, double upper) {
    double probability = 0;
    for (int i = lower; i <= upper; i++) {
        probability += poisson_x_successes(expected, i);  // 累加每个成功次数的概率
    }
    return probability;
}

/**
 * @brief 主函数
 * @return 0 退出程序
 */
int main() {
    double rate, expected;

    // 计算泊松分布的事件率
    rate = poisson_rate(3, 1);  // 3个事件在1个时间单位内发生
    std::cout << "Poisson rate : " << rate << std::endl;

    // 计算期望值
    expected = poisson_expected(rate, 2);  // 事件率为2.5，计算2个时间单位内的期望事件数
    std::cout << "Poisson expected : " << expected << std::endl;

    // 计算0次成功的概率
    std::cout << "Poisson 0 successes : " << poisson_x_successes(expected, 0)
              << std::endl;

    // 计算从0到8次成功的总概率
    std::cout << "Poisson 0-8 successes : "
              << poisson_range_successes(expected, 0, 8) << std::endl;

    return 0;
}
