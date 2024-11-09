/**
 * \file
 * \authors [Krishna Vedala](https://github.com/kvedala)
 * \brief 使用 [前向欧拉方法](https://en.wikipedia.org/wiki/Numerical_methods_for_ordinary_differential_equations#Euler_method) 求解多变量一阶 [常微分方程 (ODEs)](https://en.wikipedia.org/wiki/Ordinary_differential_equation)
 *
 * \details
 * 求解的常微分方程为：
 * \f{eqnarray*}{
 * \dot{u} &=& v\\
 * \dot{v} &=& -\omega^2 u\\
 * \omega &=& 1\\
 * [x_0, u_0, v_0] &=& [0,1,0]\qquad\ldots\text{(初始值)}
 * \f}
 * 上述问题的精确解为：
 * \f{eqnarray*}{
 * u(x) &=& \cos(x)\\
 * v(x) &=& -\sin(x)\\
 * \f}
 * 计算结果会存储到文本文件 `forward_euler.csv` 中，精确解的结果存储在 `exact.csv` 文件中，以便对比。
 * <img
 * src="https://raw.githubusercontent.com/TheAlgorithms/C-Plus-Plus/docs/images/numerical_methods/ode_forward_euler.svg"
 * alt="Implementation solution"/>
 *
 * 若要实现 [Van der Pol 振荡器](https://en.wikipedia.org/wiki/Van_der_Pol_oscillator)，请将 ::problem 函数更改为：
 * ```cpp
 * const double mu = 2.0;
 * dy[0] = y[1];
 * dy[1] = mu * (1.f - y[0] * y[0]) * y[1] - y[0];
 * ```
 * \see ode_midpoint_euler.cpp, ode_semi_implicit_euler.cpp
 */

#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <valarray>

/**
 * @brief 问题陈述，描述了具有一阶微分方程的系统，并更新系统的微分变量。
 * \note 该函数可以更新为任意阶数的常微分方程。
 *
 * @param[in] 		x 		自变量
 * @param[in,out]	y		因变量
 * @param[in,out]	dy		因变量的导数
 */
void problem(const double &x, std::valarray<double> *y,
             std::valarray<double> *dy) {
    const double omega = 1.F;             // 问题中常数 ω
    (*dy)[0] = (*y)[1];                   // x 的导数 // NOLINT
    (*dy)[1] = -omega * omega * (*y)[0];  // y 的导数 // NOLINT
}

/**
 * @brief 问题的精确解，用于解的对比。
 *
 * @param[in] 		x 		自变量
 * @param[in,out]	y		因变量
 */
void exact_solution(const double &x, std::valarray<double> *y) {
    y[0][0] = std::cos(x);  // u(x) = cos(x)
    y[0][1] = -std::sin(x); // v(x) = -sin(x)
}

/** \addtogroup ode 常微分方程
 * 集合中包含求解 [常微分方程](https://en.wikipedia.org/wiki/Ordinary_differential_equation)
 * (ODE) 的各种方法，可以处理任意阶数和多个自变量的ODE问题。
 * @{
 */
/**
 * @brief 使用前向欧拉方法计算下一个近似值。公式为：@f[y_{n+1}=y_n + dx\cdot f\left(x_n,y_n\right)@f]
 * @param[in] 		dx	步长
 * @param[in] 	    x	自变量值 \f$x_n\f$
 * @param[in,out] 	y	因变量 \f$y_n\f$
 * @param[in,out]	dy	计算 \f$f\left(x_n,y_n\right)\f$
 */
void forward_euler_step(const double dx, const double x,
                        std::valarray<double> *y, std::valarray<double> *dy) {
    problem(x, y, dy);  // 求解微分方程
    *y += *dy * dx;     // 使用欧拉方法更新 y
}

/**
 * @brief 在给定的范围内使用前向欧拉方法计算近似解。
 * @param[in] 		dx  	步长
 * @param[in]   	x0  	自变量初值
 * @param[in] 	    x_max	自变量最大值
 * @param[in,out] 	y	    因变量 \f$y_n\f$
 * @param[in] save_to_file	是否保存结果到CSV文件 (1 表示保存，0 表示不保存)
 * @returns 计算所花费的时间（秒）
 */
double forward_euler(double dx, double x0, double x_max,
                     std::valarray<double> *y, bool save_to_file = false) {
    std::valarray<double> dy = *y;  // 因变量的导数

    std::ofstream fp;
    if (save_to_file) {
        fp.open("forward_euler.csv", std::ofstream::out);
        if (!fp.is_open()) {
            std::perror("打开文件失败! ");
        }
    }

    std::size_t L = y->size();  // 因变量的大小

    /* 开始积分 */
    std::clock_t t1 = std::clock();
    double x = x0;

    do {  // 遍历每个自变量的步长
        if (save_to_file && fp.is_open()) {
            // 保存结果到文件
            fp << x << ",";
            for (int i = 0; i < L - 1; i++) {
                fp << y[0][i] << ",";  // NOLINT
            }
            fp << y[0][L - 1] << "\n";  // NOLINT
        }

        forward_euler_step(dx, x, y, &dy);  // 执行欧拉方法
        x += dx;                            // 更新自变量
    } while (x <= x_max);  // 直到自变量达到最大值
    /* 积分结束 */
    std::clock_t t2 = std::clock();

    if (fp.is_open()) {
        fp.close();
    }

    return static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
}

/** @} */

/**
 * 函数计算并保存精确解以进行对比
 *
 * \param [in]    X0  	    自变量初值
 * \param [in] 	  X_MAX	    自变量最大值
 * \param [in] 	  step_size	自变量步长
 * \param [in]    Y0	    因变量初值
 */
void save_exact_solution(const double &X0, const double &X_MAX,
                         const double &step_size,
                         const std::valarray<double> &Y0) {
    double x = X0;
    std::valarray<double> y(Y0);

    std::ofstream fp("exact.csv", std::ostream::out);
    if (!fp.is_open()) {
        std::perror("打开文件失败! ");
        return;
    }
    std::cout << "计算精确解\n";

    std::clock_t t1 = std::clock();
    do {
        fp << x << ",";
        for (int i = 0; i < y.size() - 1; i++) {
            fp << y[i] << ",";  // NOLINT
        }
        fp << y[y.size() - 1] << "\n";  // NOLINT

        exact_solution(x, &y);  // 计算精确解

        x += step_size;  // 更新自变量
    } while (x <= X_MAX);

    std::clock_t t2 = std::clock();
    double total_time = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
    std::cout << "\t总时间 = " << total_time << " 秒\n";

    fp.close();
}

/**
 * 主函数
 */
int main(int argc, char *argv[]) {
    double X0 = 0.f;                    /* 自变量初值 x0 */
    double X_MAX = 10.F;                /* 积分上限 */
    std::valarray<double> Y0{1.f, 0.f}; /* 因变量初值 Y = y(x = x_0) */
    double step_size = NAN;

    if (argc == 1) {
        std::cout << "\n请输入步长: ";
        std::cin >> step_size;
    } else {
        // 使用命令行参数作为自变量步长
        step_size = std::atof(argv[1]);
    }

    // 获取近似解
    double total_time = forward_euler(step_size, X0, X_MAX, &Y0, true);
    std::cout << "\t计算时间 = " << total_time << " 秒\n";

    /* 计算精确解并进行对比 */
    save_exact_solution(X0, X_MAX, step_size, Y0);

    return 0;
}
