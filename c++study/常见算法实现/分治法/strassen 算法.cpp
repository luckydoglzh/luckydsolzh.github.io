/**
 * @brief [Strassen算法](https://en.wikipedia.org/wiki/Strassen_algorithm) 是
 * 乘法两矩阵的其中一种方法。它是较大矩阵相比于朴素乘法方法更快的算法之一。
 *
 * 它涉及将每个矩阵划分为 4 个块，前提是它们是均匀可除的，并结合新定义的矩阵
 * ，只需进行 7 次矩阵乘法而不是 8 次，从而获得 O(n^2.8073) 的复杂度。
 *
 * @author [AshishYUO](https://github.com/AshishYUO)
 */
#include <cassert>   /// 用于断言操作
#include <chrono>    /// 用于 std::chrono; 时间测量
#include <iostream>  /// 用于输入输出操作
#include <tuple>     /// 用于 std::tuple
#include <vector>    /// 用于创建动态数组

/**
 * @namespace divide_and_conquer
 * @brief 分而治之算法
 */
namespace divide_and_conquer {

/**
 * @namespace strassens_multiplication
 * @brief 执行 Strassen 乘法的命名空间
 */
namespace strassens_multiplication {

/// 0 的补码是最大整数。
constexpr size_t MAX_SIZE = ~0ULL;
/**
 * @brief 矩阵类。
 */
template <typename T,
          typename = typename std::enable_if<
              std::is_integral<T>::value || std::is_floating_point<T>::value,
              bool>::type>
class Matrix {
    std::vector<std::vector<T>> _mat;  // 矩阵存储

 public:
    /**
     * @brief 构造函数
     * @tparam Integer 确保评估的是整数，而不是其他数据类型。
     * @param size 矩阵的大小，表示为 size x size
     */
    template <typename Integer,
              typename = typename std::enable_if<
                  std::is_integral<Integer>::value, Integer>::type>
    explicit Matrix(const Integer size) {
        for (size_t i = 0; i < size; ++i) {
            _mat.emplace_back(std::vector<T>(size, 0));  // 初始化矩阵为 0
        }
    }

    /**
     * @brief 构造函数
     * @tparam Integer 确保评估的是整数，而不是其他数据类型。
     * @param rows 矩阵的总行数
     * @param cols 矩阵每行的元素总数
     */
    template <typename Integer,
              typename = typename std::enable_if<
                  std::is_integral<Integer>::value, Integer>::type>
    Matrix(const Integer rows, const Integer cols) {
        for (size_t i = 0; i < rows; ++i) {
            _mat.emplace_back(std::vector<T>(cols, 0));  // 初始化矩阵为 0
        }
    }

    /**
     * @brief 获取矩阵的形状
     * @returns 返回一个整数对，表示总行数和列数
     */
    inline std::pair<size_t, size_t> size() const {
        return {_mat.size(), _mat[0].size()};  // 返回矩阵的行列大小
    }

    /**
     * @brief 返回第 i 行的元素地址
     * @tparam Integer 任意有效的整数
     * @param index 请求的索引
     * @returns 返回第 i 行的地址
     */
    template <typename Integer,
              typename = typename std::enable_if<
                  std::is_integral<Integer>::value, Integer>::type>
    inline std::vector<T> &operator[](const Integer index) {
        return _mat[index];  // 返回第 i 行
    }

    /**
     * @brief 创建一个新矩阵并返回其部分
     * @param row_start 行的开始位置
     * @param row_end 行的结束位置
     * @param col_start 列的开始位置
     * @param col_end 列的结束位置
     * @returns 从 row_start 行和 col_start 列开始的 (row_end - row_start) x (col_end - col_start) 大小的数组切片
     */
    Matrix slice(const size_t row_start, const size_t row_end = MAX_SIZE,
                 const size_t col_start = MAX_SIZE,
                 const size_t col_end = MAX_SIZE) const {
        const size_t h_size =
            (row_end != MAX_SIZE ? row_end : _mat.size()) - row_start;
        const size_t v_size = (col_end != MAX_SIZE ? col_end : _mat[0].size()) -
                              (col_start != MAX_SIZE ? col_start : 0);
        Matrix result = Matrix<T>(h_size, v_size);  // 创建切片矩阵

        const size_t v_start = (col_start != MAX_SIZE ? col_start : 0);
        for (size_t i = 0; i < h_size; ++i) {
            for (size_t j = 0; j < v_size; ++j) {
                result._mat[i][j] = _mat[i + row_start][j + v_start];  // 复制切片
            }
        }
        return result;  // 返回切片矩阵
    }

    /**
     * @brief 水平堆叠矩阵（一个接一个）
     * @tparam Number 任意类型的数字
     * @param other 其他矩阵：注意此数组未被修改
     * @returns void，但修改当前数组
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   Number>::type>
    void h_stack(const Matrix<Number> &other) {
        assert(_mat.size() == other._mat.size());  // 确保行数相等
        for (size_t i = 0; i < other._mat.size(); ++i) {
            for (size_t j = 0; j < other._mat[i].size(); ++j) {
                _mat[i].push_back(other._mat[i][j]);  // 水平堆叠
            }
        }
    }

    /**
     * @brief 垂直堆叠矩阵（当前矩阵在其他矩阵上面）
     * @tparam Number 任意类型的数字（整数或浮点数）
     * @param other 其他矩阵：注意此数组未被修改
     * @returns void，但修改当前数组
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   Number>::type>
    void v_stack(const Matrix<Number> &other) {
        assert(_mat[0].size() == other._mat[0].size());  // 确保列数相等
        for (size_t i = 0; i < other._mat.size(); ++i) {
            _mat.emplace_back(std::vector<T>(other._mat[i].size()));  // 添加新行
            for (size_t j = 0; j < other._mat[i].size(); ++j) {
                _mat.back()[j] = other._mat[i][j];  // 复制数据
            }
        }
    }

    /**
     * @brief 加法运算，返回一个新矩阵
     * @tparam Number 任意实数值进行加法
     * @param other 其他矩阵与此矩阵相加
     * @returns 新矩阵
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix operator+(const Matrix<Number> &other) const {
        assert(this->size() == other.size());  // 确保尺寸相同
        Matrix C = Matrix<Number>(_mat.size(), _mat[0].size());  // 创建结果矩阵
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                C._mat[i][j] = _mat[i][j] + other._mat[i][j];  // 逐元素相加
            }
        }
        return C;  // 返回新矩阵
    }

    /**
     * @brief 将其他矩阵加到当前矩阵
     * @tparam Number 任意实数值进行加法
     * @param other 其他矩阵与此矩阵相加
     * @returns 当前矩阵的引用
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix &operator+=(const Matrix<Number> &other) const {
        assert(this->size() == other.size());  // 确保尺寸相同
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                _mat[i][j] += other._mat[i][j];  // 逐元素相加
            }
        }
        return *this;  // 返回当前矩阵
    }

    /**
     * @brief 乘法运算
     * @param other 其他矩阵
     * @returns 当前矩阵乘以其他矩阵的结果
     */
    Matrix operator*(const Matrix &other) const {
        assert(this->size().second == other.size().first);  // 确保列数与行数匹配
        Matrix C = Matrix<T>(_mat.size(), other.size().second);  // 创建结果矩阵

        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < other.size().second; ++j) {
                for (size_t k = 0; k < _mat[i].size(); ++k) {
                    C._mat[i][j] += _mat[i][k] * other._mat[k][j];  // 逐元素相乘
                }
            }
        }
        return C;  // 返回结果矩阵
    }
};

/**
 * @brief 从子矩阵生成
 * @param a 第一个子矩阵
 * @param b 第二个子矩阵
 * @returns 创建一个新的矩阵，横向和纵向组合 a 和 b
 */
template <typename T>
Matrix<T> create_matrix(const Matrix<T> &a, const Matrix<T> &b) {
    Matrix<T> m(a.size().first, a.size().second + b.size().second);
    for (size_t i = 0; i < a.size().first; ++i) {
        for (size_t j = 0; j < a.size().second; ++j) {
            m[i][j] = a[i][j];  // 将第一个矩阵的元素添加到新矩阵
        }
    }
    for (size_t i = 0; i < b.size().first; ++i) {
        for (size_t j = 0; j < b.size().second; ++j) {
            m[i][j + a.size().second] = b[i][j];  // 将第二个矩阵的元素添加到新矩阵
        }
    }
    return m;  // 返回新矩阵
}

/**
 * @brief 执行 Strassen 乘法
 * @param A 矩阵 A
 * @param B 矩阵 B
 * @returns 矩阵乘法的结果
 */
template <typename T>
Matrix<T> strassen(const Matrix<T> &A, const Matrix<T> &B) {
    // 基础情况
    if (A.size().first <= 2) {
        return A * B;  // 使用基础乘法
    }
    // 确定新的大小
    size_t new_size = A.size().first / 2;
    if (A.size().first % 2 == 1) {
        new_size++;  // 如果大小不是 2 的倍数，调整大小
    }

    // 创建子矩阵
    Matrix<T> a11 = A.slice(0, new_size, 0, new_size);
    Matrix<T> a12 = A.slice(0, new_size, new_size, MAX_SIZE);
    Matrix<T> a21 = A.slice(new_size, MAX_SIZE, 0, new_size);
    Matrix<T> a22 = A.slice(new_size, MAX_SIZE, new_size, MAX_SIZE);
    Matrix<T> b11 = B.slice(0, new_size, 0, new_size);
    Matrix<T> b12 = B.slice(0, new_size, new_size, MAX_SIZE);
    Matrix<T> b21 = B.slice(new_size, MAX_SIZE, 0, new_size);
    Matrix<T> b22 = B.slice(new_size, MAX_SIZE, new_size, MAX_SIZE);

    // 计算 p 矩阵
    Matrix<T> p1 = strassen(a11 + a22, b11 + b22);  // p1
    Matrix<T> p2 = strassen(a21 + a22, b11);  // p2
    Matrix<T> p3 = strassen(a11, b12 - b22);  // p3
    Matrix<T> p4 = strassen(a22, b21 - b11);  // p4
    Matrix<T> p5 = strassen(a11 + a12, b22);  // p5
    Matrix<T> p6 = strassen(a21 - a11, b11 + b12);  // p6
    Matrix<T> p7 = strassen(a12 - a22, b21 + b22);  // p7

    // 组合结果
    Matrix<T> c11 = p1 + p4 - p5 + p7;
    Matrix<T> c12 = p3 + p5;
    Matrix<T> c21 = p2 + p4;
    Matrix<T> c22 = p1 - p2 + p3 + p6;

    // 组合 c11, c12, c21, c22 到最终结果
    Matrix<T> C = create_matrix(create_matrix(c11, c12), create_matrix(c21, c22));
    return C;  // 返回结果矩阵
}
}  // namespace strassens_multiplication
}  // namespace divide_and_conquer

/**
 * @brief 处理输入
 * @returns 计算时间和结果
 */
int main() {
    size_t n;
    std::cout << "输入矩阵大小 n: ";
    std::cin >> n;  // 读取矩阵大小
    Matrix<int> A(n, n);  // 创建矩阵 A
    Matrix<int> B(n, n);  // 创建矩阵 B

    std::cout << "输入矩阵 A: \n";
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cin >> A[i][j];  // 读取矩阵 A 的元素
        }
    }

    std::cout << "输入矩阵 B: \n";
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cin >> B[i][j];  // 读取矩阵 B 的元素
        }
    }

    auto start = std::chrono::steady_clock::now();  // 开始计时
    Matrix<int> C = divide_and_conquer::strassens_multiplication::strassen(A, B);  // 执行 Strassen 乘法
    auto end = std::chrono::steady_clock::now();  // 结束计时

    std::cout << "结果矩阵 C: \n";  // 输出结果矩阵
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cout << C[i][j] << ' ';  // 输出矩阵元素
        }
        std::cout << '\n';
    }

    std::chrono::duration<double> elapsed_seconds = end - start;  // 计算时间
    std::cout << "计算时间: " << elapsed_seconds.count() << " 秒\n";  // 输出计算时间
    return 0;  // 结束程序
}
