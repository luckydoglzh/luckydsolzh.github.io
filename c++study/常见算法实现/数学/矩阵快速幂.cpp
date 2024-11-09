/**
 * @brief 使用 [矩阵快速幂](https://www.hackerearth.com/practice/notes/matrix-exponentiation-1/) 评估递推关系
 * @details
 * 给定一个递推关系，使用矩阵快速幂方法计算第n项的值。
 * 例如，斐波那契数列的递推关系是 `f(n) = f(n-1) + f(n-2)`，
 * 其中 `f(0) = 0` 和 `f(1) = 1`。
 * 注意，该方法仅展示一个变量（n）的递推关系，不像 `nCr` 问题那样有两个变量（n, r）。
 *
 * ### 算法
 * 这个问题可以通过矩阵快速幂方法来解决。
 * @see 这里是一个简单的 [数值指数算法](https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/math/modular_exponentiation.cpp) 解释
 * 或者 [解释在这里](https://en.wikipedia.org/wiki/Exponentiation_by_squaring)。
 * @author [Ashish Daulatabad](https://github.com/AshishYUO)
 */
#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于 std::vector 容器

/**
 * @namespace math
 * @brief 数学算法相关函数
 */
namespace math {
/**
 * @namespace linear_recurrence_matrix
 * @brief [线性递推矩阵](https://www.hackerearth.com/practice/notes/matrix-exponentiation-1/)实现
 */
namespace linear_recurrence_matrix {
/**
 * @brief 矩阵相乘
 * @details 实现矩阵 A 和矩阵 B 的乘法，要求矩阵 A 的列数等于矩阵 B 的行数
 * @tparam T 模板类型，支持整数或浮点类型，默认使用 long long int
 * @param _mat_a 第一个矩阵，大小为 n * m
 * @param _mat_b 第二个矩阵，大小为 m * k
 * @returns 返回矩阵 C，大小为 n * k
 * 复杂度：`O(n*m*k)`
 * @note 由于矩阵乘法的特性，复杂度为 O(n^3)，因为我们通常会多次将矩阵与自己相乘。
 */
template <typename T = int64_t>
std::vector<std::vector<T>> matrix_multiplication(
    const std::vector<std::vector<T>>& _mat_a,
    const std::vector<std::vector<T>>& _mat_b, const int64_t mod = 1000000007) {
    // 断言：矩阵 A 的列数和矩阵 B 的行数相等
    assert(_mat_a[0].size() == _mat_b.size());
    std::vector<std::vector<T>> _mat_c(_mat_a.size(),
                                       std::vector<T>(_mat_b[0].size(), 0));
    /**
     * 实际的矩阵乘法操作
     */
    for (uint32_t i = 0; i < _mat_a.size(); ++i) {
        for (uint32_t j = 0; j < _mat_b[0].size(); ++j) {
            for (uint32_t k = 0; k < _mat_b.size(); ++k) {
                _mat_c[i][j] =
                    (_mat_c[i][j] % mod +
                     (_mat_a[i][k] % mod * _mat_b[k][j] % mod) % mod) % mod;
            }
        }
    }
    return _mat_c;
}

/**
 * @brief 判断矩阵是否为零矩阵
 * @details 判断给定矩阵是否为零矩阵
 * @tparam T 模板类型，支持整数或浮点类型，默认使用 long long int
 * @param _mat 要判断的矩阵
 * @returns 如果是零矩阵返回 true，否则返回 false
 */
template <typename T = int64_t>
bool is_zero_matrix(const std::vector<std::vector<T>>& _mat) {
    for (uint32_t i = 0; i < _mat.size(); ++i) {
        for (uint32_t j = 0; j < _mat[i].size(); ++j) {
            if (_mat[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief 实现矩阵快速幂
 * @details 返回矩阵 `_mat` 的 `power` 次方，时间复杂度为 `O(k^3 * log(power))`，其中 `k` 是矩阵的大小（k x k）
 * @tparam T 模板类型，支持整数或浮点类型，默认使用 long long int
 * @param _mat 要进行快速幂的矩阵
 * @param power 幂次
 * @returns 返回 `_mat` 的 `power` 次方矩阵
 */
template <typename T = int64_t>
std::vector<std::vector<T>> matrix_exponentiation(
    std::vector<std::vector<T>> _mat, uint64_t power,
    const int64_t mod = 1000000007) {
    /**
     * 初始化为单位矩阵。参考二进制指数算法， [请参见这里](https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/math/modular_exponentiation.cpp)
     */
    if (is_zero_matrix(_mat)) {
        return _mat;
    }

    std::vector<std::vector<T>> _mat_answer(_mat.size(),
                                            std::vector<T>(_mat.size(), 0));

    for (uint32_t i = 0; i < _mat.size(); ++i) {
        _mat_answer[i][i] = 1;
    }
    
    // 进行快速幂计算
    while (power > 0) {
        if (power & 1) {
            _mat_answer = matrix_multiplication(_mat_answer, _mat, mod);
        }
        power >>= 1;
        _mat = matrix_multiplication(_mat, _mat, mod);
    }

    return _mat_answer;
}

/**
 * @brief 计算递推序列的第n项
 * @details 根据矩阵快速幂计算递推关系的第n项。假设递推关系有已定义的基础情况（例如，斐波那契数列中 `f(0)` 和 `f(1)` 是已定义的）。
 * @tparam T 模板类型，支持整数或浮点类型，默认使用 long long int
 * @param _mat 矩阵，使用快速幂计算第n项
 * @param _base_cases 2D 数组，包含基础情况下的值，例如斐波那契数列中的 `f(0)` 和 `f(1)`
 * @param nth_term 要计算的第n项
 * @param constant_or_sum_included 递推关系是否包含常数项或是前n项和
 * @returns 返回递推关系的第n项，时间复杂度为 `O(k^3 * log(n))`
 */
template <typename T = int64_t>
T get_nth_term_of_recurrence_series(
    const std::vector<std::vector<T>>& _mat,
    const std::vector<std::vector<T>>& _base_cases, uint64_t nth_term,
    bool constant_or_sum_included = false) {
    assert(_mat.size() == _base_cases.back().size());

    // 如果n小于基础情况的长度，直接返回基础情况的值
    if (nth_term < _base_cases.back().size() - constant_or_sum_included) {
        return _base_cases.back()[nth_term - constant_or_sum_included];
    } else {
        /**
         * 否则，使用矩阵快速幂计算。
         */
        std::vector<std::vector<T>> _res_matrix =
            matrix_exponentiation(_mat, nth_term - _base_cases.back().size() +
                                            1 + constant_or_sum_included);

        // 矩阵乘法，计算结果
        std::vector<std::vector<T>> _res =
            matrix_multiplication(_base_cases, _res_matrix);

        return _res.back().back();
    }
}
}  // namespace linear_recurrence_matrix
}  // namespace math

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    /*
     * 示例 1: [斐波那契数列](https://en.wikipedia.org/wiki/Fibonacci_number);
     *
     * [fn-2    fn-1]  [0      1]  ==   [fn-1   (fn-2 + fn-1)] => [fn-1   fn]
     *                 [1      1]
     *
     * 令 A = [fn-2   fn-1]，B = [0   1]
     *                                [1   1]
     *
     * 因为 A.B....(n-1 次) = [fn-1   fn]
     * 我们可以将 B 自身乘以 n-1 次来获得所需的值
     */
    std::vector<std::vector<int64_t>> fibonacci_matrix = {{0, 1}, {1, 1}};
    std::vector<std::vector<int64_t>> base_case_fibonacci = {{0}, {1}};

    // 计算第 10 项
    std::cout << math::linear_recurrence_matrix::get_nth_term_of_recurrence_series<int64_t>(
        fibonacci_matrix, base_case_fibonacci, 10) << std::endl;
    // 返回 55
}

int main() {
    test();
    return 0;
}
