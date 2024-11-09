/**
 * \file
 * \brief 使用 [不动点迭代法](https://en.wikipedia.org/wiki/Fixed-point_iteration) 的逐次逼近法
 */
#include <cmath>
#include <iostream>

/** 方程 1
 * \f[f(y) = 3y - \cos y - 2\f]
 */
static float eq(float y) { return (3 * y) - cos(y) - 2; }

/** 方程 2
 * \f[f(y) = \frac{\cos y + 2}{2}\f]
 */
static float eqd(float y) { return 0.5 * (cos(y) + 2); }

/** 主函数 */
int main() {
    float y, x1, x2, x3, sum, s, a, f1, f2, gd;
    int i, n;

    // 循环计算方程1在不同y值下的结果
    for (i = 0; i < 10; i++) {
        sum = eq(y);  // 计算方程1的结果
        std::cout << "方程在第 " << i << " 次迭代的值为 " << sum << "\n";  // 输出计算结果
        y++;  // y的值递增
    }

    // 获取用户输入的初始值 x1 和迭代次数 n
    std::cout << "请输入初始值 x1 -> ";
    std::cin >> x1;  // 输入初始值 x1
    std::cout << "请输入要进行的迭代次数 -> ";
    std::cin >> n;  // 输入迭代次数

    // 执行不动点迭代法
    for (i = 0; i <= n; i++) {
        x2 = eqd(x1);  // 计算方程2的结果，得到新的 x2
        std::cout << "\n第 " << i << " 次迭代结果: x2 -> " << x2;  // 输出每次迭代的结果
        x1 = x2;  // 更新 x1 为 x2，为下一次迭代做准备
    }

    return 0;  // 程序正常结束
}
