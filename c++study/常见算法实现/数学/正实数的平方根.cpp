/**
 * @file
 * @brief 计算任意正实数的平方根，时间复杂度为 \f$O(\log N)\f$，并使用 [二分法](https://en.wikipedia.org/wiki/Bisection_method) 来固定精度。
 *
 * @see 可以通过更快和更好的算法实现，如 newton_raphson_method.cpp 和 false_position.cpp。
 */
#include <cassert>
#include <iostream>

/** 
 * 实现二分法来求解方程 \f$x^2 - a = 0\f$ 的根，
 * 其根为 \f$\pm\sqrt{a}\f$，返回正根。
 * 
 * @param a 需要求平方根的正实数
 * @return 正平方根
 */
double Sqrt(double a) {
    if (a > 0 && a < 1) {
        return 1 / Sqrt(1 / a);  // 如果 a 在 0 和 1 之间，使用倒数法优化计算
    }
    
    double l = 0, r = a;  // 左右边界初始值，l 是 0，r 是 a 本身
    /* Epsilon 是精度要求，精度越高，计算越精确。
       较好的精度通常在 1e-7 到 1e-12 之间。
       double epsilon = 1e-12;
    */
    double epsilon = 1e-12;  // 设置精度为 1e-12
    
    // 二分法循环，直到找到足够精确的平方根
    while (l <= r) {
        double mid = (l + r) / 2;  // 计算中间值
        if (mid * mid > a) {  // 如果 mid 的平方大于 a，则减小右边界
            r = mid;
        } else {
            if (a - mid * mid < epsilon) {  // 如果平方与 a 的差小于精度要求，则返回 mid
                return mid;
            }
            l = mid;  // 否则，增大左边界
        }
    }
    
    return -1;  // 如果没有找到合适的平方根，返回 -1
}

/** 主函数 */
int main() {
    double n{};  // 定义变量 n 来存储输入的数值
    std::cin >> n;  // 从标准输入读取一个实数
    assert(n >= 0);  // 确保输入的数是非负的
    
    // 设置输出精度，精确到小数点后 12 位
    std::cout.precision(12);  
    std::cout << std::fixed << Sqrt(n);  // 调用 Sqrt 函数并输出结果
}
