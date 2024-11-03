/**
 * @file
 * @brief 计算数组中最长递增子序列的长度
 *
 * @details
 * 在计算机科学中，最长递增子序列问题是找到给定序列的一个子序列，
 * 该子序列的元素按升序排列，并且子序列尽可能长。
 * 这个子序列不一定是连续的，也不唯一。
 * 最长递增子序列在与数学相关的各种学科中都有研究，
 * 包括算法学、随机矩阵理论、表示理论和物理学。
 * 最长递增子序列问题的时间复杂度为 O(n log n)，
 * 其中 n 表示输入序列的长度。
 *
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @author [David Leal](https://github.com/Panquesito7)
 */

#include <cassert>   /// 用于 assert
#include <climits>   /// 用于 std::max
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于 std::vector

/**
 * @namespace dynamic_programming
 * @brief 动态规划算法
 */
namespace dynamic_programming {
/**
 * @brief 计算指定数字的最长递增子序列
 * @param a 用于计算最长递增子序列的数组
 * @param n 数组的大小
 * @returns 返回 `a` 数组中最长递增子序列的长度
 */
uint64_t LIS(const std::vector<uint64_t> &a, const uint32_t &n) {
    std::vector<int> lis(n);  // 创建一个用于存储最长递增子序列长度的数组
    for (int i = 0; i < n; ++i) {
        lis[i] = 1;  // 初始化每个位置的 LIS 长度为 1
    }
    
    // 填充 lis 数组
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[i] > a[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;  // 更新 LIS 长度
            }
        }
    }
    
    int res = 0;  // 结果变量
    for (int i = 0; i < n; ++i) {
        res = std::max(res, lis[i]);  // 获取最大的 LIS 长度
    }
    
    return res;  // 返回最长递增子序列的长度
}
}  // namespace dynamic_programming

/**
 * @brief 自我测试实现
 * @returns void
 */
static void test() {
    std::vector<uint64_t> a = {15, 21, 2, 3, 4, 5, 8, 4, 1, 1};
    uint32_t n = a.size();

    uint32_t result = dynamic_programming::LIS(a, n);
    assert(result == 5);  ///< 最长递增子序列为 `{2,3,4,5,8}`

    std::cout << "自我测试通过!" << std::endl;
}

/**
 * @brief 主函数
 * @param argc 命令行参数个数（被忽略）
 * @param argv 命令行参数数组（被忽略）
 * @returns 0 表示正常退出
 */
int main(int argc, char const *argv[]) {
    uint32_t n = 0;  // 数组大小

    std::cout << "输入数组大小: ";
    std::cin >> n;  // 读取数组大小

    std::vector<uint64_t> a(n);  // 创建数组

    std::cout << "输入数组元素: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];  // 读取数组元素
    }

    std::cout << "\n结果是: " << dynamic_programming::LIS(a, n)
              << std::endl;  // 输出最长递增子序列的长度
    test();  // 运行自我测试

    return 0;  // 正常退出
}
