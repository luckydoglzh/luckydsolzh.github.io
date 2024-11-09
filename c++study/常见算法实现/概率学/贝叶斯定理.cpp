/**
 * @file
 * @brief [贝叶斯定理](https://en.wikipedia.org/wiki/Bayes%27_theorem)
 *
 * 贝叶斯定理允许我们根据 \f$P(B|A)\f$ 和其他条件来计算 \f$P(A|B)\f$，或者反过来计算 \f$P(B|A)\f$ 给定 \f$P(A|B)\f$ 和 \f$P(A)\f$ 以及 \f$P(B)\f$。\n
 * 请注意，\f$P(A|B)\f$ 被解读为“在事件 B 发生的情况下，事件 A 发生的概率”。
 */
#include <iostream>

/** 
 * @brief 计算贝叶斯定理中的 P(A|B)
 * @param BgivenA 已知条件下的 P(B|A)
 * @param A 事件 A 发生的先验概率 P(A)
 * @param B 事件 B 发生的先验概率 P(B)
 * @returns 返回 P(A|B)，即事件 B 发生时事件 A 发生的条件概率
 */
double bayes_AgivenB(double BgivenA, double A, double B) {
    return (BgivenA * A) / B;  ///< 应用贝叶斯定理公式计算 P(A|B)
}

/** 
 * @brief 计算贝叶斯定理中的 P(B|A)
 * @param AgivenB 已知条件下的 P(A|B)
 * @param A 事件 A 发生的先验概率 P(A)
 * @param B 事件 B 发生的先验概率 P(B)
 * @returns 返回 P(B|A)，即事件 A 发生时事件 B 发生的条件概率
 */
double bayes_BgivenA(double AgivenB, double A, double B) {
    return (AgivenB * B) / A;  ///< 应用贝叶斯定理公式计算 P(B|A)
}

/** 
 * @brief 主函数
 * @returns 0 退出程序
 */
int main() {
    double A = 0.01;  ///< 事件 A 发生的先验概率 P(A)
    double B = 0.1;   ///< 事件 B 发生的先验概率 P(B)
    double BgivenA = 0.9;  ///< 事件 A 发生的情况下，事件 B 发生的条件概率 P(B|A)
    
    // 使用贝叶斯定理计算 P(A|B)
    double AgivenB = bayes_AgivenB(BgivenA, A, B);
    std::cout << "A given B = " << AgivenB << std::endl;  ///< 输出 P(A|B)
    
    // 使用贝叶斯定理计算 P(B|A)
    std::cout << "B given A = " << bayes_BgivenA(AgivenB, A, B) << std::endl;  ///< 输出 P(B|A)
    
    return 0;  ///< 结束程序
}
