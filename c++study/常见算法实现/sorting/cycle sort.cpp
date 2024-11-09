/**
 * @file
 * @brief 实现 [Cycle Sort](https://en.wikipedia.org/wiki/Cycle_sort) 算法
 * @details
 * Cycle Sort 是一种排序算法，它在最好情况下时间复杂度为 \f$O(n^2)\f$，在最坏情况下也是 \f$O(n^2)\f$。
 * 如果一个元素已经在正确的位置上，就不做任何操作。如果元素不在正确的位置上，我们需要通过计算正确的位置
 * 将其移到正确的位置。需要注意处理重复元素。
 * @author [TsungHan Ho](https://github.com/dalaoqi)
 */

#include <algorithm>  /// 引入 std::is_sorted 和 std::swap
#include <cassert>    /// 引入 assert
#include <iostream>   /// 引入输入输出操作
#include <vector>     /// 引入 std::vector

/**
 * @namespace sorting
 * @brief 排序算法
 */
namespace sorting {
/**
 * @namespace cycle_sort
 * @brief [Cycle Sort](https://en.wikipedia.org/wiki/Cycle_sort) 算法相关的函数
 */
namespace cycle_sort {

/**
 * @brief 实现 Cycle Sort 算法的主函数
 * @tparam T 数组元素的类型
 * @param in_arr 需要排序的数组
 * @returns 排序后的数组
 */
template <typename T>
std::vector<T> cycleSort(const std::vector<T> &in_arr) {
    std::vector<T> arr(in_arr);  // 创建一个副本用于排序
    for (int cycle_start = 0; cycle_start <= arr.size() - 1; cycle_start++) {
        // 初始化元素
        T item = arr[cycle_start];

        // 计算比当前元素小的元素的个数，这个数字就是当前元素的正确位置
        int pos = cycle_start;
        for (int i = cycle_start + 1; i < arr.size(); i++) {
            if (arr[i] < item) {
                pos++;  // 统计比当前元素小的个数
            }
        }

        // 如果元素已经在正确的位置，则跳过
        if (pos == cycle_start) {
            continue;
        }

        // 处理重复元素
        while (item == arr[pos]) pos += 1;
        if (pos == cycle_start) {
            continue;
        } else {
            std::swap(item, arr[pos]);  // 将元素交换到其正确位置
        }

        // 处理剩余的元素
        while (pos != cycle_start) {
            pos = cycle_start;
            // 计算当前元素的正确位置
            for (size_t i = cycle_start + 1; i < arr.size(); i++) {
                if (arr[i] < item) {
                    pos += 1;
                }
            }

            // 处理重复元素
            while (item == arr[pos]) pos += 1;
            if (item == arr[pos]) {
                continue;
            } else {
                std::swap(item, arr[pos]);  // 将元素交换到正确位置
            }
        }
    }
    return arr;
}
}  // namespace cycle_sort
}  // namespace sorting

/**
 * @brief 测试实现
 * @returns void
 */
static void test() {
    // 测试 1
    // [4, 3, 2, 1] 排序后应为 [1, 2, 3, 4]
    std::vector<uint32_t> array1 = {4, 3, 2, 1};
    std::cout << "Test 1... ";
    std::vector<uint32_t> arr1 = sorting::cycle_sort::cycleSort(array1);
    assert(std::is_sorted(std::begin(arr1), std::end(arr1)));  // 验证数组是否已排序
    std::cout << "passed" << std::endl;

    // 测试 2
    // [4.3, -6.5, -7.4, 0, 2.7, 1.8] 排序后应为 [-7.4, -6.5, 0, 1.8, 2.7, 4.3]
    std::vector<double> array2 = {4.3, -6.5, -7.4, 0, 2.7, 1.8};
    std::cout << "Test 2... ";
    std::vector<double> arr2 = sorting::cycle_sort::cycleSort(array2);
    assert(std::is_sorted(std::begin(arr2), std::end(arr2)));  // 验证数组是否已排序
    std::cout << "passed" << std::endl;

    // 测试 3
    // [3, 3, 3, 3] 排序后应为 [3, 3, 3, 3]（重复元素的排序）
    std::vector<uint32_t> array3 = {3, 3, 3, 3};
    std::cout << "Test 3... ";
    std::vector<uint32_t> arr3 = sorting::cycle_sort::cycleSort(array3);
    assert(std::is_sorted(std::begin(arr3), std::end(arr3)));  // 验证数组是否已排序
    std::cout << "passed" << std::endl;

    // 测试 4
    // [9, 4, 6, 8, 14, 3] 排序后应为 [3, 4, 6, 8, 9, 14]
    std::vector<uint32_t> array4 = {3, 4, 6, 8, 9, 14};
    std::cout << "Test 4... ";
    std::vector<uint32_t> arr4 = sorting::cycle_sort::cycleSort(array4);
    assert(std::is_sorted(std::begin(arr4), std::end(arr4)));  // 验证数组是否已排序
    std::cout << "passed" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main() {
    test();  // 执行测试
    return 0;
}
