/**
 * @file
 * @brief [Gram Schmidt 正交化过程](https://en.wikipedia.org/wiki/Gram%E2%80%93Schmidt_process)
 *
 * @details
 * 输入线性无关的向量，返回相互正交的向量。
 *
 * ### 算法
 * 将输入的第一个向量作为正交向量的第一个向量。对第二个输入向量，计算它在第一个正交向量上的投影，并将投影从第二个向量中减去。对第三个向量，计算它在第二个正交向量上的投影，并将投影从第三个向量中减去。一直重复上述过程，直到所有输入向量都处理完毕。
 *
 * 例如：
 * 在 R2 空间中，
 * 输入线性无关向量={(3,1),(2,2)}
 * 则输出正交向量={(3, 1),(-0.4, 1.2)}
 *
 * 本程序定义了最大向量维度为 10，最多输入 20 个向量。
 * 请确保输入的向量是线性无关的。
 *
 * @author [Akanksha Gupta](https://github.com/Akanksha-Gupta920)
 */

#include <array>     /// 用于 std::array
#include <cassert>   /// 用于 assert
#include <cmath>     /// 用于 fabs
#include <iostream>  /// 用于输入输出操作

#include "math.h"

/**
 * @namespace numerical_methods
 * @brief 数值方法算法
 */
namespace numerical_methods {
/**
 * @namespace gram_schmidt
 * @brief [Gram Schmidt 正交化过程](https://en.wikipedia.org/wiki/Gram%E2%80%93Schmidt_process)的函数
 */
namespace gram_schmidt {
/**
 * 点积函数。
 * 输入两个向量及其维度，返回两个向量的点积。
 * @param x 向量 1
 * @param y 向量 2
 * @param c 向量的维度
 *
 * @returns 返回点积结果
 */
double dot_product(const std::array<double, 10>& x,
                   const std::array<double, 10>& y, const int& c) {
    double sum = 0;
    for (int i = 0; i < c; ++i) {
        sum += x[i] * y[i];
    }
    return sum;
}

/**
 * 投影函数
 * 输入两个向量及其维度，计算第一个向量在第二个向量上的投影并返回。
 *
 * @param x 向量 1
 * @param y 向量 2
 * @param c 向量的维度
 *
 * @returns 返回投影的系数
 */
double projection(const std::array<double, 10>& x,
                  const std::array<double, 10>& y, const int& c) {
    double dot =
        dot_product(x, y, c);  /// 计算两个向量的点积
    double anorm =
        dot_product(y, y, c);  /// 计算第二个向量的范数（即其点积的平方根）
    double factor =
        dot / anorm;  /// 使用点积除以第二个向量的范数，得到投影系数
    return factor;
}

/**
 * 打印正交化后的向量
 *
 * @param r 向量的数量
 * @param c 向量的维度
 * @param B 存储正交化后的向量
 *
 * @returns 无返回值
 */
void display(const int& r, const int& c,
             const std::array<std::array<double, 10>, 20>& B) {
    for (int i = 0; i < r; ++i) {
        std::cout << "向量 " << i + 1 << ": ";
        for (int j = 0; j < c; ++j) {
            std::cout << B[i][j] << " ";
        }
        std::cout << '\n';
    }
}

/**
 * Gram-Schmidt 正交化过程
 * @param r 向量的数量
 * @param c 向量的维度
 * @param A 存储输入的线性无关向量
 * @param B 存储正交化后的向量
 *
 * @returns 无返回值
 */
void gram_schmidt(int r, const int& c,
                  const std::array<std::array<double, 10>, 20>& A,
                  std::array<std::array<double, 10>, 20> B) {
    if (c < r) {  /// 检查维度是否适合给定向量的数量
        std::cout << "向量维度小于给定向量的数量，因此只会正交化前 " << c << " 个向量\n";
        r = c;
    }

    int k = 1;

    while (k <= r) {
        if (k == 1) {
            for (int j = 0; j < c; j++)
                B[0][j] = A[0][j];  /// 第一个向量直接复制
        }

        else {
            std::array<double, 10>
                all_projection{};  /// 用于存储所有投影的数组
            for (int i = 0; i < c; ++i) {
                all_projection[i] = 0;  /// 初始化为 0
            }

            int l = 1;
            while (l < k) {
                std::array<double, 10>
                    temp{};           /// 存储前一个投影的临时数组
                double factor = NAN;  /// 用于存储投影系数
                factor = projection(A[k - 1], B[l - 1], c);
                for (int i = 0; i < c; ++i) {
                    temp[i] = B[l - 1][i] * factor;  /// 计算投影后的向量
                }
                for (int j = 0; j < c; ++j) {
                    all_projection[j] =
                        all_projection[j] +
                        temp[j];  /// 将所有投影累加
                }
                l++;
            }
            for (int i = 0; i < c; ++i) {
                B[k - 1][i] =
                    A[k - 1][i] -
                    all_projection[i];  /// 从输入向量中减去所有投影向量
            }
        }
        k++;
    }
    display(r, c, B);  // 显示正交化后的向量
}
}  // namespace gram_schmidt
}  // namespace numerical_methods
/**
 * 测试函数。已测试三个示例输入
 * @returns 无返回值
 */
static void test() {
    std::array<std::array<double, 10>, 20> a1 = {
        {{1, 0, 1, 0}, {1, 1, 1, 1}, {0, 1, 2, 1}}};
    std::array<std::array<double, 10>, 20> b1 = {{0}};
    double dot1 = 0;
    numerical_methods::gram_schmidt::gram_schmidt(3, 4, a1, b1);
    int flag = 1;
    for (int i = 0; i < 2; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            dot1 = fabs(
                numerical_methods::gram_schmidt::dot_product(b1[i], b1[j], 4));
            if (dot1 > 0.1) {
                flag = 0;
                break;
            }
        }
    }
    if (flag == 0)
        std::cout << "向量是线性相关的\n";
    assert(flag == 1);
    std::cout << "通过测试案例 1\n ";

    std::array<std::array<double, 10>, 20> a2 = {{{3, 1}, {2, 2}}};
    std::array<std::array<double, 10>, 20> b2 = {{0}};
    double dot2 = 0;
    numerical_methods::gram_schmidt::gram_schmidt(2, 2, a2, b2);
    flag = 1;
    for (int i = 0; i < 1; ++i) {
        for (int j = i + 1; j < 2; ++j) {
            dot2 = fabs(
                numerical_methods::gram_schmidt::dot_product(b2[i], b2[j], 2));
            if (dot2 > 0.1) {
                flag = 0;
                break;
            }
        }
    }
    if (flag == 0)
        std::cout << "向量是线性相关的\n";
    assert(flag == 1);
    std::cout << "通过测试案例 2\n";

    std::array<std::array<double, 10>, 20> a3 = {{{1, 2, 2}, {-4, 3, 2}}};
    std::array<std::array<double, 10>, 20> b3 = {{0}};
    double dot3 = 0;
    numerical_methods::gram_schmidt::gram_schmidt(2, 3, a3, b3);
    flag = 1;
    for (int i = 0; i < 1; ++i) {
        for (int j = i + 1; j < 2; ++j) {
            dot3 = fabs(
                numerical_methods::gram_schmidt::dot_product(b3[i], b3[j], 3));
            if (dot3 > 0.1) {
                flag = 0;
                break;
            }
        }
    }
    if (flag == 0)
        std::cout << "向量是线性相关的\n";
    assert(flag == 1);
    std::cout << "通过测试案例 3\n";
}

/**
 * @brief 主函数
 * @return 0 退出程序
 */
int main() {
    int r = 0, c = 0;
    test();  // 执行自我测试
    std::cout << "请输入向量的维度\n";
    std::cin >> c;
    std::cout << "请输入你将输入的向量数量\n";
    std::cin >> r;

    std::array<std::array<double, 10>, 20>
        A{};  /// 用于存储所有向量的二维数组
    std::array<std::array<double, 10>, 20> B = {
        {0}};  /// 用于存储正交化后的向量的二维数组
    /// 输入向量并存储在 A 数组中
    for (int i = 0; i < r; ++i) {
        std::cout << "请输入第 " << i + 1 << " 个向量\n";
        for (int j = 0; j < c; ++j) {
            std::cout << "第 " << j + 1 << " 个向量的值: ";
            std::cin >> A[i][j];
        }
        std::cout << '\n';
    }

    numerical_methods::gram_schmidt::gram_schmidt(r, c, A, B);

    double dot = 0;
    int flag = 1;  /// 检查向量是否正交
    for (int i = 0; i < r - 1; ++i) {
        for (int j = i + 1; j < r; ++j) {
            dot = fabs(
                numerical_methods::gram_schmidt::dot_product(B[i], B[j], c));
            if (dot > 0.1)  /// 为了确保数值稳定性，设置点积的上限为 0.1
            {
                flag = 0;
                break;
            }
        }
    }
    if (flag == 0)
        std::cout << "向量是线性相关的\n";
    return 0;
}
