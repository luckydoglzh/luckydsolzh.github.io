/**
 * @file
 * @brief 概率的加法规则
 */
#include <iostream>

/**
 * 计算独立事件 A 或 B 的概率
 * \param [in] A 事件 A 的概率
 * \param [in] B 事件 B 的概率
 * \returns 事件 A 或 B 的概率
 */
double addition_rule_independent(double A, double B) {
    return (A + B) - (A * B);
}

/**
 * 计算依赖事件 A 或 B 的概率
 * 注意，如果 B_given_A 的值未知，请使用链式法则来找到它
 * \param [in] A 事件 A 的概率
 * \param [in] B 事件 B 的概率
 * \param [in] B_given_A 事件 B 在事件 A 条件下的概率
 * \returns 事件 A 或 B 的概率
 */
double addition_rule_dependent(double A, double B, double B_given_A) {
    return (A + B) - (A * B_given_A);
}

/** 主函数 */
int main() {
    double A = 0.5;             // 事件 A 的概率
    double B = 0.25;            // 事件 B 的概率
    double B_given_A = 0.05;    // 事件 B 在事件 A 条件下的概率

    std::cout << "独立事件 P(A 或 B) = " << addition_rule_independent(A, B)
              << std::endl;

    std::cout << "依赖事件 P(A 或 B) = "
              << addition_rule_dependent(A, B, B_given_A) << std::endl;

    return 0;
}
