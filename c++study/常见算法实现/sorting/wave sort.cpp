/**
 * @file
 * @brief 实现 [Wave Sort](https://www.geeksforgeeks.org/sort-array-wave-form-2/) 算法
 * @details
 * Wave Sort 是一种排序算法，假设使用的排序函数是 O(nlogn) 时间复杂度，
 * 则该算法的时间复杂度为 O(nlogn)。
 * @author [Swastika Gupta](https://github.com/Swastyy)
 */

#include <algorithm>  /// 用于 std::is_sorted, std::swap
#include <cassert>    /// 用于 assert
#include <iostream>   /// 用于输入输出操作
#include <vector>     /// 用于 std::vector

/**
 * @namespace sorting
 * @brief 排序算法
 */
namespace sorting {
/**
 * @namespace wave_sort
 * @brief 实现 [Wave Sort](https://www.geeksforgeeks.org/sort-array-wave-form-2/) 算法的函数
 */
namespace wave_sort {
/**
 * @brief 主函数，实现 Wave Sort 算法
 * @tparam T 数组的类型
 * @param in_arr 需要排序的数组
 * @returns 返回排序后的波形数组
 */
template <typename T>
std::vector<T> waveSort(const std::vector<T> &in_arr, int64_t n) {
    std::vector<T> arr(in_arr);  // 创建一个拷贝数组

    for (int64_t i = 0; i < n; i++) {
        arr[i] = in_arr[i];  // 将输入数组复制到 arr 数组
    }

    std::sort(arr.begin(), arr.end());  // 先对数组进行排序

    // 然后交换相邻的元素，以形成波形
    for (int64_t i = 0; i < n - 1; i += 2) {
        std::swap(arr[i], arr[i + 1]);  // 每次交换相邻元素
    }

    return arr;  // 返回波形排序后的数组
}
}  // namespace wave_sort
}  // namespace sorting

/**
 * @brief 自我测试实现
 * @returns void
 */
static void test() {
    // 测试用例 1: 输入 [10, 90, 49, 2, 1, 5, 23]，返回波形排序后的数组 [2, 1, 10, 5, 49, 23, 90]
    std::vector<int64_t> array1 = {10, 90, 49, 2, 1, 5, 23};
    std::cout << "Test 1... ";
    std::vector<int64_t> arr1 = sorting::wave_sort::waveSort(array1, 7);
    const std::vector<int64_t> o1 = {2, 1, 10, 5, 49, 23, 90};
    assert(arr1 == o1);  // 确保排序结果正确
    std::cout << "passed" << std::endl;

    // 测试用例 2: 输入 [1, 3, 4, 2, 7, 8]，返回波形排序后的数组 [2, 1, 4, 3, 8, 7]
    std::vector<int64_t> array2 = {1, 3, 4, 2, 7, 8};
    std::cout << "Test 2... ";
    std::vector<int64_t> arr2 = sorting::wave_sort::waveSort(array2, 6);
    const std::vector<int64_t> o2 = {2, 1, 4, 3, 8, 7};
    assert(arr2 == o2);  // 确保排序结果正确
    std::cout << "passed" << std::endl;

    // 测试用例 3: 输入 [3, 3, 3, 3]，返回波形排序后的数组 [3, 3, 3, 3]
    std::vector<int64_t> array3 = {3, 3, 3, 3};
    std::cout << "Test 3... ";
    std::vector<int64_t> arr3 = sorting::wave_sort::waveSort(array3, 4);
    const std::vector<int64_t> o3 = {3, 3, 3, 3};
    assert(arr3 == o3);  // 确保排序结果正确
    std::cout << "passed" << std::endl;

    // 测试用例 4: 输入 [9, 4, 6, 8, 14, 3]，返回波形排序后的数组 [4, 3, 8, 6, 14, 9]
    std::vector<int64_t> array4 = {9, 4, 6, 8, 14, 3};
    std::cout << "Test 4... ";
    std::vector<int64_t> arr4 = sorting::wave_sort::waveSort(array4, 6);
    const std::vector<int64_t> o4 = {4, 3, 8, 6, 14, 9};
    assert(arr4 == o4);  // 确保排序结果正确
    std::cout << "passed" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 退出代码
 */
int main() {
    test();  // 运行自我测试
    return 0;
}
