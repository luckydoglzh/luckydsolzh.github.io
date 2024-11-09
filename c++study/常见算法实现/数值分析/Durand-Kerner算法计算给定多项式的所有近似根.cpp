/**
 * @file
 * \brief 使用Durand-Kerner算法计算给定多项式的所有近似根
 * \author [Krishna Vedala](https://github.com/kvedala)
 *
 * 在线测试算法:
 * https://gist.github.com/kvedala/27f1b0b6502af935f6917673ec43bcd7
 *
 * 测试高度不稳定的威尔金森多项式：
 * ```
 * ./numerical_methods/durand_kerner_roots 1 -210 20615 -1256850 53327946
 * -1672280820 40171771630 -756111184500 11310276995381 -135585182899530
 * 1307535010540395 -10142299865511450 63030812099294896 -311333643161390640
 * 1206647803780373360 -3599979517947607200 8037811822645051776
 * -12870931245150988800 13803759753640704000 -8752948036761600000
 * 2432902008176640000
 * ```
 * 示例实现结果，计算方程 \f$x^4-1=0\f$ 的近似根:\n
 * <img
 * src="https://raw.githubusercontent.com/TheAlgorithms/C-Plus-Plus/docs/images/numerical_methods/durand_kerner_error.svg"
 * width="400" alt="Error evolution during root approximations computed every
 * iteration."/> <img
 * src="https://raw.githubusercontent.com/TheAlgorithms/C-Plus-Plus/docs/images/numerical_methods/durand_kerner_roots.svg"
 * width="400" alt="Roots evolution - shows the initial approximation of the
 * roots and their convergence to a final approximation along with the iterative
 * approximations" />
 */

#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <valarray>
#ifdef _OPENMP
#include <omp.h>
#endif

#define ACCURACY 1e-10 /**< 最大精度限制 */

/**
 * 计算给定多项式的值
 * \param[in] coeffs 多项式的系数
 * \param[in] x 计算多项式值的点
 * \returns \f$f(x)\f$
 **/
std::complex<double> poly_function(const std::valarray<double> &coeffs,
                                   std::complex<double> x) {
    double real = 0.f, imag = 0.f;
    int n;

    // 遍历每个项并计算多项式的值
    for (n = 0; n < coeffs.size(); n++) {
        std::complex<double> tmp =
            coeffs[n] * std::pow(x, coeffs.size() - n - 1);
        real += tmp.real();
        imag += tmp.imag();
    }

    return std::complex<double>(real, imag);
}

/**
 * 创建复数的字符串形式
 * \param[in] x 复数
 * \returns 转换后的字符串
 */
const char *complex_str(const std::complex<double> &x) {
#define MAX_BUFF_SIZE 50
    static char msg[MAX_BUFF_SIZE];

    std::snprintf(msg, MAX_BUFF_SIZE, "% 7.04g%+7.04gj", x.real(), x.imag());

    return msg;
}

/**
 * 检查终止条件
 * \param[in] delta 根的更新量
 * \returns `false` 表示未达到终止条件
 * \returns `true` 表示已经达到终止条件
 */
bool check_termination(long double delta) {
    static long double past_delta = INFINITY;
    if (std::abs(past_delta - delta) <= ACCURACY || delta < ACCURACY)
        return true;
    past_delta = delta;
    return false;
}

/**
 * 实现Durand-Kerner迭代算法计算多项式的所有根
 * 
 * \param[in] coeffs 多项式的系数
 * \param[out] roots 计算得到的多项式根
 * \param[in] write_log 是否保存日志文件（默认值 = `false`）
 * \returns 返回迭代次数和最终精度
 */
std::pair<uint32_t, double> durand_kerner_algo(
    const std::valarray<double> &coeffs,
    std::valarray<std::complex<double>> *roots, bool write_log = false) {
    long double tol_condition = 1;
    uint32_t iter = 0;
    int n;
    std::ofstream log_file;

    if (write_log) {
        // 保存中间结果到CSV文件
        log_file.open("durand_kerner.log.csv");
        if (!log_file.is_open()) {
            perror("无法创建日志文件!");
            std::exit(EXIT_FAILURE);
        }
        log_file << "iter#,";

        for (n = 0; n < roots->size(); n++) log_file << "root_" << n << ",";

        log_file << "avg. correction";
        log_file << "\n0,";
        for (n = 0; n < roots->size(); n++)
            log_file << complex_str((*roots)[n]) << ",";  // 输出初始根
    }

    bool break_loop = false;
    while (!check_termination(tol_condition) && iter < INT16_MAX &&
           !break_loop) {
        tol_condition = 0;
        iter++;
        break_loop = false;

        if (log_file.is_open())
            log_file << "\n" << iter << ",";

        // 计算每个根的更新量
#ifdef _OPENMP
#pragma omp parallel for shared(break_loop, tol_condition)
#endif
        for (n = 0; n < roots->size(); n++) {
            if (break_loop)
                continue;

            std::complex<double> numerator, denominator;
            numerator = poly_function(coeffs, (*roots)[n]);
            denominator = 1.0;
            for (int i = 0; i < roots->size(); i++)
                if (i != n)
                    denominator *= (*roots)[n] - (*roots)[i];

            std::complex<long double> delta = numerator / denominator;

            // 检查溢出或无穷大错误
            if (std::isnan(std::abs(delta)) || std::isinf(std::abs(delta))) {
                std::cerr << "\n\n溢出/下溢错误 - 得到的值 = "
                          << std::abs(delta) << "\n";
                break_loop = true;
            }

            (*roots)[n] -= delta;  // 更新根的值

#ifdef _OPENMP
#pragma omp critical
#endif
            tol_condition = std::max(tol_condition, std::abs(std::abs(delta)));
        }

        if (break_loop)
            break;

        if (log_file.is_open()) {
            for (n = 0; n < roots->size(); n++)
                log_file << complex_str((*roots)[n]) << ",";  // 保存根的中间结果
        }

#if defined(DEBUG) || !defined(NDEBUG)
        if (iter % 500 == 0) {
            std::cout << "迭代次数: " << iter << "\t";
            for (n = 0; n < roots->size(); n++)
                std::cout << "\t" << complex_str((*roots)[n]);
            std::cout << "\t\t平均变化量: " << tol_condition << "\n";
        }
#endif

        if (log_file.is_open())
            log_file << tol_condition;  // 保存当前精度
    }

    return std::pair<uint32_t, long double>(iter, tol_condition);
}

/**
 * 测试算法，检查 \f$x^2+4=0\f$ 的根，根为 \f$0 \pm 2i\f$
 */
void test1() {
    const std::valarray<double> coeffs = {1, 0, 4};  // x^2 - 2 = 0
    std::valarray<std::complex<double>> roots(2);
    std::valarray<std::complex<double>> expected = {
        std::complex<double>(0., 2.),
        std::complex<double>(0., -2.)  // 已知的期望根
    };

    // 初始化根的近似值
    for (int n = 0; n < roots.size(); n++) {
        roots[n] = std::complex<double>(std::rand() % 100, std::rand() % 100);
        roots[n] -= 50.f;
        roots[n] /= 25.f;
    }

    auto result = durand_kerner_algo(coeffs, &roots, false);

    for (int i = 0; i < roots.size(); i++) {
        // 检查根的近似值是否与期望值误差小于0.1%
        bool err1 = false;
        for (int j = 0; j < roots.size(); j++)
            err1 |= std::abs(std::abs(roots[i] - expected[j])) < 1e-3;
        assert(err1);
    }

    std::cout << "测试通过，找到所有根!" << std::endl;
}

int main() {
    std::cout << "Durand-Kerner 多项式根求解算法" << std::endl;
    std::srand(std::time(0));

    test1();

    return 0;
}
