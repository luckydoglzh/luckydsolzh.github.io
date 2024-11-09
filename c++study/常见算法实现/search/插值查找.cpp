/******************************************************************************
 * @file
 * @brief 插值查找算法 [Interpolation Search](https://en.wikipedia.org/wiki/interpolation_search)
 *
 * @details
 * 插值查找算法类似于人们查找电话簿中的名字的方法（电话簿中的条目是按关键字排序的）：
 * 每一步，算法根据查找范围的上下边界的键值和目标键值，估算出目标元素可能出现的位置，通常通过线性插值来实现。
 * 然后将该估算位置的实际键值与目标键值进行比较。如果两者不相等，则根据比较结果，缩小查找范围，
 * 继续在估算位置前或后的部分查找。此方法只有在计算出来的键值差异是合理的情况下才有效。
 *
 * ### 时间复杂度
 *
 * n为数组元素个数。
 *
 * 最坏情况下时间复杂度	O(n)                （当元素分布呈指数级时）
 * 平均时间复杂度	        O(log2(log2 n))
 * 空间复杂度	            O(1)
 *
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 * @author Unknown author
 *******************************************************************************/

#include <algorithm>  /// 用于 std::sort 函数
#include <cassert>    /// 用于 std::assert
#include <iostream>   /// 用于输入输出操作
#include <vector>     /// 用于 std::vector

/******************************************************************************
 * @namespace search
 * @brief 搜索算法
 *******************************************************************************/
namespace search {

/******************************************************************************
 * @namespace interpolation_search
 * @brief 插值查找算法的实现
 *******************************************************************************/
namespace interpolation_search {

/******************************************************************************
 * @brief 插值查找算法的主要实现函数
 * @param arr 要查找的数组
 * @param number 要查找的值
 * @returns 返回目标值在数组中的索引
 *******************************************************************************/
uint64_t interpolationSearch(const std::vector<uint64_t> &arr,
                             uint64_t number) {
    uint64_t size = arr.size();      // 数组的大小
    uint64_t low = 0, high = (size - 1);  // 设置查找范围的低位和高位

    // 由于数组已经排序，目标元素必须在范围内
    while (low <= high && number >= arr[low] && number <= arr[high]) {
        if (low == high) {  // 如果范围只剩一个元素
            if (arr[low] == number) {
                return low;  // 如果找到了目标值，返回索引
            }
            return -1;  // 否则返回 -1，表示未找到
        }
        // 使用线性插值计算估算的位置
        uint64_t pos =
            low +
            ((static_cast<uint64_t>(high - low) / (arr[high] - arr[low])) *
             (number - arr[low]));

        if (arr[pos] == number) {  // 如果找到目标值，返回位置
            return pos;
        }

        if (arr[pos] < number) {  // 如果目标值大于当前元素，缩小查找范围到上半部分
            low = pos + 1;
        } else {  // 如果目标值小于当前元素，缩小查找范围到下半部分
            high = pos - 1;
        }
    }
    return -1;  // 如果未找到目标值，返回 -1
}

}  // namespace interpolation_search

}  // namespace search

/*******************************************************************************
 * @brief 自测试函数实现
 * @returns void
 *******************************************************************************/
static void tests() {
    // 测试用例
    // 数组 = [10, 12, 13, 16, 18, 19, 20, 21, 1, 2, 3, 4, 22, 23, 24, 33, 35,
    // 42, 47] , 目标值 = 33，应返回 15
    std::vector<uint64_t> arr = {{10, 12, 13, 16, 18, 19, 20, 21, 1, 2, 3, 4,
                                  22, 23, 24, 33, 35, 42, 47}};
    sort(arr.begin(), arr.end());  // 对数组进行排序
    uint64_t number = 33;  // 需要查找的元素
    uint64_t expected_answer = 15;  // 预期的答案是索引 15
    uint64_t derived_answer =
        search::interpolation_search::interpolationSearch(arr, number);
    std::cout << "Testcase: ";
    assert(derived_answer == expected_answer);  // 校验实际结果与预期结果是否一致
    std::cout << "Passed!\n";
}

/*******************************************************************************
 * @brief 主函数
 * @returns 0 退出
 *******************************************************************************/
int main() {
    tests();  // 执行自测试函数
    return 0;
}
