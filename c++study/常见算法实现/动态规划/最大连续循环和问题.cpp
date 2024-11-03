/**
 * @file
 * @brief C++ 程序用于计算最大连续循环和问题，使用 [Kadane 算法](https://en.wikipedia.org/wiki/Maximum_subarray_problem)
 * @details
 * 该算法的思想是修改 Kadane 算法以找到最小连续子数组和和最大连续子数组和，然后检查最大值和从总和中减去最小值后的值之间的最大值。
 * 有关更多信息，请查看 [Geeks For Geeks](https://www.geeksforgeeks.org/maximum-contiguous-circular-sum/) 解释页面。
 */

#include <cassert>     /// 用于 assert
#include <iostream>    /// 用于输入输出操作
#include <vector>      /// 用于 std::vector


/**
 * @namespace dynamic_programming
 * @brief 动态规划算法
 */
namespace dynamic_programming {
/**
 * @brief 返回数组的最大连续循环和
 * 
 * @param arr 是输入数组/向量
 * @return int 最大和
 */
int maxCircularSum(std::vector<int>& arr)
{
    // 边界情况
    if (arr.size() == 1)
        return arr[0];
  
    // 存储数组总和的变量
    int sum = 0;
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
  
    // 每个变量存储数组的第一个值
    int current_max = arr[0], max_so_far = arr[0], current_min = arr[0], min_so_far = arr[0];
  
    // Kadane 算法的概念
    for (int i = 1; i < arr.size(); i++) {
        // Kadane 算法查找最大子数组和
        current_max = std::max(current_max + arr[i], arr[i]);
        max_so_far = std::max(max_so_far, current_max);
  
        // Kadane 算法查找最小子数组和
        current_min = std::min(current_min + arr[i], arr[i]);
        min_so_far = std::min(min_so_far, current_min);
    }
  
    // 如果最小和等于总和，返回最大和
    if (min_so_far == sum)
        return max_so_far;
  
    // 返回最大值
    return std::max(max_so_far, sum - min_so_far);
}
}  // namespace dynamic_programming

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    // 测试描述
    // 输入: arr[] = {8, -8, 9, -9, 10, -11, 12}
    // 输出: 22 
    // 解释: 子数组 12, 8, -8, 9, -9, 10 的最大和为 22。

    int n = 7; // 数组大小
    std::vector<int> arr = {8, -8, 9, -9, 10, -11, 12}; 
    assert(dynamic_programming::maxCircularSum(arr) == 22); // 确保算法按预期工作

    arr = {8, -8, 10, -9, 10, -11, 12};
    assert(dynamic_programming::maxCircularSum(arr) == 23);

    std::cout << "所有测试都已成功通过！\n";
}


/**
 * @brief 主函数
 * @param argc 命令行参数计数（忽略）
 * @param argv 命令行参数数组（忽略）
 * @returns 0 正常退出
 */
int main(int argc, char *argv[]) {
     test();  // 运行自测实现
     return 0; // 正常退出
}
