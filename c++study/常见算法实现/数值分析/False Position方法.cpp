/**
 * \file
 * \brief 使用[False Position方法](https://en.wikipedia.org/wiki/Regula_falsi)解决方程 \f$f(x)=0\f$
 * 也叫做割线法（Secant方法）
 *
 * \details
 * 首先，在给定的区间范围内选择多个区间。对于每个根，递归函数会被单独调用。
 * 方程的根将分别打印出来。
 *
 * 对于区间 \([a,b]\)，若 \f$f(a)<0\f$ 且 \f$f(b)>0\f$，则第 \((i+1)\)-次近似值为：
 * \f[
 * x_{i+1} = \frac{a_i \cdot f(b_i) - b_i \cdot f(a_i)}{f(b_i) - f(a_i)}
 * \f]
 * 在下一次迭代中，若 \f$x > 0\f$，则选择新的区间 \([a, x]\)，
 * 否则选择 \([x, b]\)。这个过程会继续进行，直到获得足够精确的近似值。
 *
 * \see newton_raphson_method.cpp, bisection_method.cpp
 *
 * \author Unknown author
 * \author [Samruddha Patil](https://github.com/sampatil578)
 */
#include <cmath>     /// 包含数学运算相关的库
#include <iostream>  /// 包含输入输出相关的库

/**
 * @namespace numerical_methods
 * @brief 数值方法的命名空间
 */
namespace numerical_methods {
/**
 * @namespace false_position
 * @brief [False Position](https://en.wikipedia.org/wiki/Regula_falsi) 方法的函数
 */
namespace false_position {
/**
 * @brief 计算给定 \f$x\f$ 的方程 \f$f(x)\f$ 的值
 * @param x 给定的值，用于计算 \f$f(x)\f$
 * @return 给定 \f$x\f$ 的 \f$f(x)\f$ 值
 */
static float eq(float x) {
    return (x * x - x);  // 目标方程：x^2 - x = 0
}

/**
 * @brief 计算在给定区间 \([x1, x2]\) 内的方程根
 * @param x1 区间的起始值
 * @param x2 区间的结束值
 * @param y1 方程在 x1 处的值
 * @param y2 方程在 x2 处的值
 * @return 在给定区间内的根
 */
static float regula_falsi(float x1, float x2, float y1, float y2) {
    float diff = x1 - x2;
    if (diff < 0) {
        diff = (-1) * diff;
    }
    if (diff < 0.00001) {  // 近似值误差小于0.00001时结束
        if (y1 < 0) {
            y1 = -y1;
        }
        if (y2 < 0) {
            y2 = -y2;
        }
        if (y1 < y2) {
            return x1;
        } else {
            return x2;
        }
    }
    float x3 = 0, y3 = 0;
    // 计算下一个近似根
    x3 = x1 - (x1 - x2) * (y1) / (y1 - y2);
    y3 = eq(x3);  // 计算新的根值
    return regula_falsi(x2, x3, y2, y3);  // 递归调用
}

/**
 * @brief 打印方程的根
 * @param root 需要打印的根
 * @param count 当前根在区间中的编号
 */
void printRoot(float root, const int16_t &count) {
    if (count == 1) {
        std::cout << "你的第1个根是 : " << root << std::endl;
    } else if (count == 2) {
        std::cout << "你的第2个根是 : " << root << std::endl;
    } else if (count == 3) {
        std::cout << "你的第3个根是 : " << root << std::endl;
    } else {
        std::cout << "你的第" << count << "个根是 : " << root << std::endl;
    }
}
}  // namespace false_position
}  // namespace numerical_methods

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main() {
    float a = 0, b = 0, i = 0, root = 0;
    int16_t count = 0;
    float range =
        100000;       // 查找根的区间范围 (-range, range)
    float gap = 0.5;  // 区间间隔，间隔越小，精度越高
    a = numerical_methods::false_position::eq((-1) * range);
    i = ((-1) * range + gap);

    // 使用while循环根据给定的区间和间隔选择合适的区间
    while (i <= range) {
        b = numerical_methods::false_position::eq(i);
        if (b == 0) {  // 如果b处方程值为0，则根就是b
            count++;
            numerical_methods::false_position::printRoot(i, count);
        }
        if (a * b < 0) {  // 如果f(a)与f(b)异号，说明根在区间[a, b]之间
            root = numerical_methods::false_position::regula_falsi(i - gap, i,
                                                                   a, b);
            count++;
            numerical_methods::false_position::printRoot(root, count);
        }
        a = b;  // 更新a的值
        i += gap;  // 移动到下一个区间
    }
    return 0;
}
