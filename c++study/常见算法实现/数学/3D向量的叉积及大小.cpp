/**
 * @file
 *
 * @brief 计算两个三维数学向量的 [叉积](https://en.wikipedia.org/wiki/Cross_product) 和其大小。
 *
 * @details
 * 叉积是两个向量的乘积，结果是一个向量。
 * 向量的方向比率是给定向量的数值部分，即决定向量大小的三个分量。
 * 计算叉积的方法与求一个包含三个行的矩阵的行列式相同，其中第一行是单位向量（每个分量的大小为1），
 * 第二行是第一个向量的方向比率，第三行是第二个向量的方向比率。
 * 向量的大小是其值的数值表示，即方向比率的平方和的平方根。
 * 假设第一个向量P的方向比率为：a, b, c
 * 假设第二个向量Q的方向比率为：x, y, z
 * 则叉积的计算可以表示为：
 *
 * ```
 * P x Q:
 *    1  1  1
 *    a  b  c
 *    x  y  z
 * ```
 *
 * 方向比率（DR）计算如下：
 *   第一个DR，J：  (b * z) - (c * y)
 *   第二个DR，A： -((a * z) - (c * x))
 *   第三个DR，N：  (a * y) - (b * x)
 *
 * 所以，叉积的方向比率是：J, A, N。
 * 该程序通过函数cross()计算两个向量的叉积方向比率。
 * 程序要求用户输入两个向量的方向比率（每个向量分量以空格分隔）。
 *
 * 向量的大小是其方向比率的平方和的平方根。
 *
 * ### 示例：
 * 运行实例：
 * 	输入第一个向量: 1 2 3
 *	输入第二个向量: 4 5 6
 *	叉积结果为: -3 6 -3
 *	大小: 7.34847
 *
 * @author [Shreyas Sable](https://github.com/Shreyas-OwO)
 */

#include <iostream>
#include <array>
#include <cmath>
#include <cassert>

/**
 * @namespace math
 * @brief 数学算法
 */
namespace math {
	/**
	 * @namespace vector_cross
	 * @brief 向量叉积算法
	 */
	namespace vector_cross {
		/**
		 * @brief 计算两个数学向量的叉积，输入为包含两个向量方向比率的数组。
		 * @param A 包含第一个数学向量的方向比率。
		 * @param B 包含第二个数学向量的方向比率。
		 * @returns 返回叉积的方向比率。
		 */
		std::array<double, 3> cross(const std::array<double, 3> &A, const std::array<double, 3> &B) {
			std::array<double, 3> product;
			// 按照公式计算叉积的三个方向比率
			product[0] = (A[1] * B[2]) - (A[2] * B[1]);
			product[1] = -((A[0] * B[2]) - (A[2] * B[0]));
			product[2] = (A[0] * B[1]) - (A[1] * B[0]);
			return product;
		}

		/**
		 * @brief 计算向量的大小（长度），即方向比率的平方和的平方根。
		 * @param vec 向量的方向比率数组。
		 * @returns 返回向量的大小。
		 */
		double mag(const std::array<double, 3> &vec) {
			// 计算大小（平方和的平方根）
			double magnitude = sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2]));
			return magnitude;
		}
	} /// namespace vector_cross
} /// namespace math

/**
 * @brief 测试函数。
 * @details 测试cross()和mag()函数。
 */
static void test() {
	// 测试cross()函数。
	std::array<double, 3> t_vec = math::vector_cross::cross({1, 2, 3}, {4, 5, 6});
	assert(t_vec[0] == -3 && t_vec[1] == 6 && t_vec[2] == -3);

	// 测试mag()函数。
	double t_mag = math::vector_cross::mag({6, 8, 0});
	assert(t_mag == 10);
}

/**
 * @brief 主函数
 * @details 提示用户输入两个数学向量的方向比率，使用std::cin获取。
 * @returns 退出时返回0。
 */
int main() {

	// 在请求用户输入之前，使用示例输入测试函数。
	test();

	std::array<double, 3> vec1;
	std::array<double, 3> vec2;

	// 获取第一个向量的方向比率。
	std::cout << "\n请输入第一个向量: ";
	std::cin >> vec1[0] >> vec1[1] >> vec1[2];

	// 获取第二个向量的方向比率。
	std::cout << "\n请输入第二个向量: ";
	std::cin >> vec2[0] >> vec2[1] >> vec2[2];

	// 计算并显示叉积的结果。
	std::array<double, 3> product = math::vector_cross::cross(vec1, vec2);
	std::cout << "\n叉积为: " << product[0] << " " << product[1] << " " << product[2] << std::endl;

	// 计算并显示叉积的大小。
	std::cout << "大小: " << math::vector_cross::mag(product) << "\n" << std::endl;

	return 0;
}
