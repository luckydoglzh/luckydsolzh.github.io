/**
 * @file vector_ops.hpp
 * @author [Deep Raval](https://github.com/imdeep2905)
 *
 * @brief 与[神经网络 (多层感知机)]
 * (https://en.wikipedia.org/wiki/Multilayer_perceptron)相关的向量操作函数
 *
 */
#ifndef VECTOR_OPS_FOR_NN
#define VECTOR_OPS_FOR_NN

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <valarray>
#include <vector>

/**
 * @namespace machine_learning
 * @brief 机器学习算法
 */
namespace machine_learning {
/**
 * 重载输出运算符 "<<" 用于打印二维向量
 * @tparam T 向量的类型
 * @param out 用于输出的 std::ostream
 * @param A 要打印的二维向量
 */
template <typename T>
std::ostream &operator<<(std::ostream &out,
                         std::vector<std::valarray<T>> const &A) {
    out.precision(4); // 设置浮点数的输出精度为 4
    for (const auto &a : A) {       // 遍历 A 中的每一行
        for (const auto &x : a) {   // 遍历每一行中的每个元素
            std::cout << x << ' ';  // 输出元素
        }
        std::cout << std::endl;
    }
    return out;
}

/**
 * 重载输出运算符 "<<" 用于打印 pair
 * @tparam T pair 的类型
 * @param out 用于输出的 std::ostream
 * @param A 要打印的 pair
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::pair<T, T> &A) {
    out.precision(4); // 设置浮点数的输出精度为 4
    std::cout << "(" << A.first << ", " << A.second << ")";
    return out;
}

/**
 * 重载输出运算符 "<<" 用于打印一维向量
 * @tparam T 向量的类型
 * @param out 用于输出的 std::ostream
 * @param A 要打印的一维向量
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::valarray<T> &A) {
    out.precision(4); // 设置浮点数的输出精度为 4
    for (const auto &a : A) {   // 遍历向量中的每个元素
        std::cout << a << ' ';  // 输出元素
    }
    std::cout << std::endl;
    return out;
}

/**
 * 插入元素到一维向量中
 * @tparam T 向量和元素的类型
 * @param A 要插入元素的一维向量
 * @param ele 要插入的元素
 * @return 新的一维向量
 */
template <typename T>
std::valarray<T> insert_element(const std::valarray<T> &A, const T &ele) {
    std::valarray<T> B;      // 新的一维向量，用于存储结果
    B.resize(A.size() + 1);  // 根据需要调整大小
    for (size_t i = 0; i < A.size(); i++) {  // 遍历 A 中的每个元素
        B[i] = A[i];                         // 复制元素到 B
    }
    B[B.size() - 1] = ele;  // 在最后一个位置插入新元素
    return B;               // 返回结果向量
}

/**
 * 从一维向量中删除第一个元素
 * @tparam T 向量的类型
 * @param A 要删除第一个元素的一维向量
 * @return 新的结果向量
 */
template <typename T>
std::valarray<T> pop_front(const std::valarray<T> &A) {
    std::valarray<T> B;      // 新的一维向量，用于存储结果
    B.resize(A.size() - 1);  // 根据需要调整大小
    for (size_t i = 1; i < A.size();
         i++) {           // 遍历 A 中的每个元素（除了第一个）
        B[i - 1] = A[i];  // 将元素复制到 B，位置左移
    }
    return B;  // 返回结果向量
}

/**
 * 从一维向量中删除最后一个元素
 * @tparam T 向量的类型
 * @param A 要删除最后一个元素的一维向量
 * @return 新的结果向量
 */
template <typename T>
std::valarray<T> pop_back(const std::valarray<T> &A) {
    std::valarray<T> B;      // 新的一维向量，用于存储结果
    B.resize(A.size() - 1);  // 根据需要调整大小
    for (size_t i = 0; i < A.size() - 1;
         i++) {       // 遍历 A 中的每个元素（除了最后一个）
        B[i] = A[i];  // 将元素复制到 B
    }
    return B;  // 返回结果向量
}

/**
 * 等比例地打乱两个三维向量（用于打乱训练数据）
 * @tparam T 向量的类型
 * @param A 第一个三维向量
 * @param B 第二个三维向量
 */
template <typename T>
void equal_shuffle(std::vector<std::vector<std::valarray<T>>> &A,
                   std::vector<std::vector<std::valarray<T>>> &B) {
    // 如果两个向量的大小不同
    if (A.size() != B.size()) {
        std::cerr << "错误 (" << __func__ << ") : ";
        std::cerr << "无法打乱大小不同的两个向量: ";
        std::cerr << A.size() << " 和 " << B.size() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < A.size(); i++) {  // 遍历 A 和 B 中的每个元素
        std::srand(std::chrono::system_clock::now().time_since_epoch().count());
        size_t random_index = std::rand() % A.size(); // 生成小于 A 和 B 大小的随机索引
        std::swap(A[i], A[random_index]); // 同时打乱 A 和 B 中相同随机索引处的元素
        std::swap(B[i], B[random_index]);
    }
    return;
}

/**
 * 使用均匀分布初始化二维向量
 * @tparam T 向量的类型
 * @param A 要初始化的二维向量
 * @param shape 所需的形状
 * @param low 最小值
 * @param high 最大值
 */
template <typename T>
void uniform_random_initialization(std::vector<std::valarray<T>> &A,
                                   const std::pair<size_t, size_t> &shape,
                                   const T &low, const T &high) {
    A.clear();  // 清空 A
    std::default_random_engine generator(
        std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<T> distribution(low, high);
    for (size_t i = 0; i < shape.first; i++) {  // 遍历每一行
        std::valarray<T> row;
        row.resize(shape.second);
        for (auto &r : row) { // 初始化行中的每个元素
            r = distribution(generator); 
        }
        A.push_back(row); // 插入新行
    }
    return;
}

/**
 * 将二维向量初始化为单位矩阵
 * @tparam T 向量的类型
 * @param A 要初始化的二维向量
 * @param shape 所需的形状
 */
template <typename T>
void unit_matrix_initialization(std::vector<std::valarray<T>> &A,
                                const std::pair<size_t, size_t> &shape) {
    A.clear();  // 清空 A
    for (size_t i = 0; i < shape.first; i++) {
        std::valarray<T> row;
        row.resize(shape.second);
        row[i] = T(1); // 在第 i 个位置插入 1
        A.push_back(row); // 插入新行
    }
    return;
}

/**
 * 将二维向量初始化为全零矩阵
 * @tparam T 向量的类型
 * @param A 要初始化的二维向量
 * @param shape 所需的形状
 */
template <typename T>
void zeroes_initialization(std::vector<std::valarray<T>> &A,
                           const std::pair<size_t, size_t> &shape) {
    A.clear();  // 清空 A
    for (size_t i = 0; i < shape.first; i++) {
        std::valarray<T> row;
        row.resize(shape.second); // 默认情况下所有元素为零
        A.push_back(row); // 插入新行
    }
    return;
}

/**
 * 获取二维向量中所有元素的和
 * @tparam T 向量的类型
 * @param A 二维向量
 * @return 所有元素的和
 */
template <typename T>
T sum_of_elements(const std::vector<std::valarray<T>> &A) {
    T sum = T(0);  // 初始化和为 T 类型的零
    for (const auto &row : A) { // 遍历 A 的每一行
        sum += row.sum(); // 累加每行的和
    }
    return sum;
}

/**
 * 获取二维向量中所有元素的最大值
 * @tparam T 向量的类型
 * @param A 二维向量
 * @return 所有元素的最大值
 */
template <typename T>
T max_of_elements(const std::vector<std::valarray<T>> &A) {
    T max = std::numeric_limits<T>::min(); // 初始化最大值
    for (const auto &row : A) {  // 遍历 A 的每一行
        max = std::max(max, row.max()); // 更新最大值
    }
    return max;
}
}  // namespace machine_learning
/**
 * 重载运算符 "*"，用于将给定的二维向量与标量相乘
 * @tparam T 向量和标量的类型
 * @param A 需要乘以标量的二维向量
 * @param val 将要相乘的标量值
 * @return 新的结果向量
 */
template <typename T>
std::vector<std::valarray<T>> operator*(const std::vector<std::valarray<T>> &A, const T &val) {
    std::vector<std::valarray<double>> B = A;  // 用于存储结果的新向量
    for (auto &b : B) {  // 遍历向量的每一行
        b = b * val;  // 将行与标量相乘
    }
    return B;  // 返回新的二维向量
}

/**
 * 重载运算符 "/"，用于将给定的二维向量除以标量
 * @tparam T 向量和标量的类型
 * @param A 需要除以标量的二维向量
 * @param val 将要相除的标量值
 * @return 新的结果向量
 */
template <typename T>
std::vector<std::valarray<T>> operator/(const std::vector<std::valarray<T>> &A, const T &val) {
    std::vector<std::valarray<double>> B = A;  // 用于存储结果的新向量
    for (auto &b : B) {  // 遍历向量的每一行
        b = b / val;  // 将行与标量相除
    }
    return B;  // 返回新的二维向量
}

/**
 * 获取二维向量的转置
 * @tparam T 向量的类型
 * @param A 需要转置的二维向量
 * @return 新的结果向量
 */
template <typename T>
std::vector<std::valarray<T>> transpose(const std::vector<std::valarray<T>> &A) {
    const auto shape = get_shape(A);  // 获取向量的当前形状
    std::vector<std::valarray<T>> B;  // 用于存储结果的新向量
    // 将A的转置值存储到B
    for (size_t j = 0; j < shape.second; j++) {
        std::valarray<T> row;
        row.resize(shape.first);
        for (size_t i = 0; i < shape.first; i++) {
            row[i] = A[i][j];
        }
        B.push_back(row);
    }
    return B;  // 返回新的二维向量
}

/**
 * 重载运算符 "+"，用于将两个二维向量相加
 * @tparam T 向量的类型
 * @param A 第一个二维向量
 * @param B 第二个二维向量
 * @return 新的结果向量
 */
template <typename T>
std::vector<std::valarray<T>> operator+(const std::vector<std::valarray<T>> &A, const std::vector<std::valarray<T>> &B) {
    const auto shape_a = get_shape(A);
    const auto shape_b = get_shape(B);
    // 如果向量形状不同
    if (shape_a.first != shape_b.first || shape_a.second != shape_b.second) {
        std::cerr << "错误 (" << __func__ << ") : 提供的向量形状不同 ";
        std::cerr << shape_a << " 和 " << shape_b << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::vector<std::valarray<T>> C;
    for (size_t i = 0; i < A.size(); i++) {  // 遍历每一行
        C.push_back(A[i] + B[i]);  // 元素逐一相加
    }
    return C;  // 返回新的二维向量
}

/**
 * 重载运算符 "-"，用于将两个二维向量相减
 * @tparam T 向量的类型
 * @param A 第一个二维向量
 * @param B 第二个二维向量
 * @return 新的结果向量
 */
template <typename T>
std::vector<std::valarray<T>> operator-(const std::vector<std::valarray<T>> &A, const std::vector<std::valarray<T>> &B) {
    const auto shape_a = get_shape(A);
    const auto shape_b = get_shape(B);
    // 如果向量形状不同
    if (shape_a.first != shape_b.first || shape_a.second != shape_b.second) {
        std::cerr << "错误 (" << __func__ << ") : 提供的向量形状不同 ";
        std::cerr << shape_a << " 和 " << shape_b << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::vector<std::valarray<T>> C;  // 用于存储结果的新向量
    for (size_t i = 0; i < A.size(); i++) {  // 遍历每一行
        C.push_back(A[i] - B[i]);  // 元素逐一相减
    }
    return C;  // 返回新的二维向量
}

/**
 * 乘两个二维向量
 * @tparam T 向量的类型
 * @param A 第一个二维向量
 * @param B 第二个二维向量
 * @return 新的结果向量
 */
template <typename T>
std::vector<std::valarray<T>> multiply(const std::vector<std::valarray<T>> &A, const std::vector<std::valarray<T>> &B) {
    const auto shape_a = get_shape(A);
    const auto shape_b = get_shape(B);
    // 如果向量不符合乘法条件
    if (shape_a.second != shape_b.first) {
        std::cerr << "错误 (" << __func__ << ") : 向量不符合乘法条件 ";
        std::cerr << shape_a << " 和 " << shape_b << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::vector<std::valarray<T>> C;  // 用于存储结果的新向量
    // 常规矩阵乘法
    for (size_t i = 0; i < shape_a.first; i++) {
        std::valarray<T> row;
        row.resize(shape_b.second);
        for (size_t j = 0; j < shape_b.second; j++) {
            for (size_t k = 0; k < shape_a.second; k++) {
                row[j] += A[i][k] * B[k][j];
            }
        }
        C.push_back(row);
    }
    return C;  // 返回新的二维向量
}

/**
 * 获取两个二维向量的Hadamard积
 * @tparam T 向量的类型
 * @param A 第一个二维向量
 * @param B 第二个二维向量
 * @return 新的结果向量
 */
template <typename T>
std::vector<std::valarray<T>> hadamard_product(const std::vector<std::valarray<T>> &A, const std::vector<std::valarray<T>> &B) {
    const auto shape_a = get_shape(A);
    const auto shape_b = get_shape(B);
    // 如果向量不符合Hadamard积条件
    if (shape_a.first != shape_b.first || shape_a.second != shape_b.second) {
        std::cerr << "错误 (" << __func__ << ") : 向量形状不同 ";
        std::cerr << shape_a << " 和 " << shape_b << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::vector<std::valarray<T>> C;  // 用于存储结果的新向量
    for (size_t i = 0; i < A.size(); i++) {
        C.push_back(A[i] * B[i]);  // 元素逐一相乘
    }
    return C;  // 返回新的二维向量
}  // namespace machine_learning

#endif

