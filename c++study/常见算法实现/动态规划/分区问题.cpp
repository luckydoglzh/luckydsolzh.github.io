/******************************************************************************
 * @file
 * @brief 实现 [分区问题](https://en.wikipedia.org/wiki/Partition_problem)
 * @details
 * 分区问题，或称为数字分区，任务是决定给定的正整数多重集 S 是否可以被分成两个子集 S1 和 S2，使得 S1 中数字的和等于 S2 中数字的和。尽管分区问题是 NP 完全的，但存在一种伪多项式时间的动态规划解决方案，还有一些启发式方法能在许多实例中优化或近似解决该问题。因此，它被称为“最简单的难题”。
 *
 * Jarvis 算法的最坏时间复杂度是 O(n^2)。使用 Graham 扫描算法，可以在 O(n log n) 的时间内找到凸包。
 *
 * ### 实现步骤
 *
 * 第一步：计算数组的和。如果和是奇数，则不能将其分成两个和相等的子集，因此返回 false。
 *
 * 第二步：如果数组元素的和是偶数，则计算和的一半，并查找一个子集，其和等于该值。
 *
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 *
 *******************************************************************************/
#include <cassert>   /// 用于 assert
#include <iostream>  /// 用于输入输出操作
#include <numeric>   /// 用于 std::accumulate
#include <vector>    /// 用于 std::vector

/******************************************************************************
 * @namespace dp
 * @brief 动态规划算法
 *******************************************************************************/
namespace dp {

/******************************************************************************
 * @namespace partitionProblem
 * @brief 分区问题算法
 *******************************************************************************/
namespace partitionProblem {

/******************************************************************************
 * @brief 如果 arr 可以被分成两个和相等的子集，则返回 true，否则返回 false
 * @param arr 包含元素的向量
 * @param size 向量的大小
 * @returns bool 向量是否可以被分区的结果
 *******************************************************************************/
bool findPartiion(const std::vector<uint64_t> &arr, uint64_t size) {
    uint64_t sum = std::accumulate(arr.begin(), arr.end(), 0);  // 计算所有元素的和

    if (sum % 2 != 0) {
        return false;  // 如果和是奇数，不能分成两个相等的和
    }
    std::vector<bool> part; // 创建用于存储子集和的布尔数组

    // 初始化 part 数组
    for (uint64_t it = 0; it <= sum / 2; ++it) {
        part.push_back(false);
    }

    // 以自底向上的方式填充分区表
    for (uint64_t it = 0; it < size; ++it) {
        // 要包含在和中的元素不能大于当前和
        for (uint64_t it2 = sum / 2; it2 >= arr[it]; --it2) { // 检查是否可以用之前的元素形成和
            // 如果 sum - arr[i] 可以用之前的元素形成
            if (part[it2 - arr[it]] == true || it2 == arr[it]) {
                part[it2] = true; // 更新当前和的可达性
            }
        }
    }
    return part[sum / 2]; // 返回是否存在和为 sum/2 的子集
}
}  // namespace partitionProblem
}  // namespace dp

/*******************************************************************************
 * @brief 自测实现
 * @returns void
 *******************************************************************************/
static void test() {
    std::vector<uint64_t> arr = {{1, 3, 3, 2, 3, 2}}; // 自定义测试数组
    uint64_t n = arr.size(); // 数组大小
    bool expected_result = true; // 预期结果
    bool derived_result = dp::partitionProblem::findPartiion(arr, n); // 调用分区函数
    std::cout << "第一个测试: ";
    assert(expected_result == derived_result); // 验证结果
    std::cout << "通过测试!" << std::endl; // 输出测试结果
}

/*******************************************************************************
 * @brief 主函数
 * @returns 0 正常退出
 *******************************************************************************/
int main() {
    test();  // 执行自测
    return 0; // 正常退出
}
