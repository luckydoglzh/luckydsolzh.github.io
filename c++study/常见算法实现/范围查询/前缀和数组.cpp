/**
 * @file
 * @brief
 * [前缀和数组（Prefix Sum Array）](https://en.wikipedia.org/wiki/Prefix_sum) 数据结构实现
 *
 * @details
 * 前缀和数组是一种数据结构，用于快速回答区间和查询。它通过预先计算数组的前缀和，在查询时可以在 O(1) 时间内返回指定区间的和。构建该数据结构的时间复杂度为 O(N)，但它不支持更新查询。
 *
 * * 运行时间复杂度 \n
 * * 构建：O(N) \n
 * * 区间查询：O(1) \n
 * @author [Paulo Vitor Lima Borges](https://github.com/PauloVLB)
 */

#include <cassert>   /// 用于断言操作
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于使用 std::vector 容器

/**
 * @namespace range_queries
 * @brief 区间查询算法
 */
namespace range_queries {
/**
 * @namespace prefix_sum_array
 * @brief 使用前缀和数组进行区间和查询
 */
namespace prefix_sum_array {

std::vector<int64_t> PSA(1, 0);  /// 存储前缀和数组，初始化时包含一个元素 0

/**
 * @brief 构建前缀和数组
 * @param original_array 原始数组，包含要进行区间和查询的数值
 * @returns void
 */
void build(std::vector<int64_t> original_array) {
    // 遍历原始数组，构建前缀和数组 PSA
    for (int i = 1; i <= static_cast<int>(original_array.size()); i++) {
        PSA.push_back(PSA[i - 1] + original_array[i]);  // PSA[i] 存储原始数组前 i 个元素的和
    }
}

/**
 * @brief 区间和查询函数
 * @param beg 查询区间的起始位置
 * @param end 查询区间的结束位置
 * @returns 返回区间 [beg, end] 的和
 */
int64_t query(int64_t beg, int64_t end) {
    // 区间和等于 PSA[end] - PSA[beg - 1]
    return PSA[end] - PSA[beg - 1];
}

}  // namespace prefix_sum_array
}  // namespace range_queries

/**
 * @brief 自我测试实现
 * @returns void
 */
static void test() {
    // 原始数组示例
    std::vector<int64_t> values{0,  123, 0,  2,  -2, 5,
                                24, 0,   23, -1, -1};  // 原始数组

    range_queries::prefix_sum_array::build(values);  // 构建前缀和数组
    // 查询类型：区间 [a, b] 的和 = psa[b] - psa[a-1]

    // 查询整个数组的和
    assert(range_queries::prefix_sum_array::query(1, 10) == 173);  
    // 查询区间 [4, 6] 的和
    assert(range_queries::prefix_sum_array::query(4, 6) == 27);  
    // 查询区间 [5, 9] 的和
    assert(range_queries::prefix_sum_array::query(5, 9) == 51);  
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    test();  // 运行自我测试
    return 0;
}
