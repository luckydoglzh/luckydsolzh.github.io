/**
 * @file
 * @brief 实现 [Kadane 算法](https://en.wikipedia.org/wiki/Kadane%27s_algorithm)
 *
 * @details
 * Kadane 算法用于查找数组中的最大连续子数组和。最大子数组和问题的任务是找到具有最大和的连续子数组。
 *
 * ### 算法说明
 * 该算法的基本思想是搜索数组中的所有正连续段，并跟踪具有最大和的连续正段（使用 curr_sum 变量）。
 * 每次获取正和时，将其与 max_sum 进行比较，如果 curr_sum 较大，则更新 max_sum。
 *
 * @author Ayush Singh
 */

#include <array>
#include <climits>
#include <iostream>

/**
 * @namespace dynamic_programming
 * @brief 动态规划算法
 */
namespace dynamic_programming {
/**
 * @namespace kadane
 * @brief [Kadane 算法](https://en.wikipedia.org/wiki/Kadane%27s_algorithm) 的函数。
 */
namespace kadane {
/**
 * @brief maxSubArray 函数用于计算最大子数组和并返回最大和的值
 * @tparam N 数组大小
 * @param n 数组，其中保存了元素
 * @returns 最大子数组和的值
 */
template <size_t N>
int maxSubArray(const std::array<int, N> &n) {
    int curr_sum = 0;           // 声明变量 curr_sum 并初始化为 0
    int max_sum = INT_MIN;       // 初始化 max_sum 为最小整数值 INT_MIN

    // 遍历数组中的元素
    for (int i : n) {
        curr_sum += i;           // 将当前元素添加到 curr_sum
        max_sum = std::max(max_sum, curr_sum);  // 更新 max_sum 为更大的值
        curr_sum = std::max(curr_sum, 0);       // 如果 curr_sum 为负数，则重置为 0
    }
    return max_sum;  // 返回 max_sum 的值
}
}  // namespace kadane
}  // namespace dynamic_programming

/**
 * @brief 主函数
 * @returns 0 表示程序正常退出
 */
int main() {
    const int N = 5;
    std::array<int, N> n{};  // 声明数组

    // 从用户输入中获取数组元素的值
    for (int i = 0; i < n.size(); i++) {
        std::cout << "输入 n[" << i << "] 的值: ";
        std::cin >> n[i];
    }

    // 调用 maxSubArray 函数计算最大子数组和
    int max_sum = dynamic_programming::kadane::maxSubArray<N>(n);
    std::cout << "最大连续子数组和为 " << max_sum;  // 输出结果

    return 0;
}
