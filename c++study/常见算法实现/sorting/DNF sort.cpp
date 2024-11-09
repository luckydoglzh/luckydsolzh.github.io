/**
 * @file
 * @brief 实现 [DNF 排序](https://www.geeksforgeeks.org/sort-an-array-of-0s-1s-and-2s/) 算法
 * @details
 * C++ 程序，用于在一次遍历中对包含 0、1 和 2 的数组进行排序（DNF 排序）。
 * 由于只有一次遍历，因此其时间复杂度为 O(n)。
 * @author [Sujal Gupta](https://github.com/heysujal)
 */

#include <algorithm>  /// 引入 std::is_sorted
#include <cassert>    /// 引入 assert
#include <iostream>   /// 引入 std::swap 和输入输出操作
#include <vector>     /// 引入 std::vector

/**
 * @namespace sorting
 * @brief 排序算法
 */
namespace sorting {
/**
 * @namespace dnf_sort
 * @brief [DNF 排序](https://en.wikipedia.org/wiki/Dutch_national_flag_problem) 算法实现
 */
namespace dnf_sort {

/**
 * @brief 主函数实现 DNF 排序
 * @tparam T 数组的类型
 * @param a 需要排序的数组
 * @param arr_size 数组的大小
 * @returns 排序后的数组
 */
template <typename T>
std::vector<T> dnfSort(const std::vector<T> &in_arr) {
    std::vector<T> arr(in_arr);  // 创建数组副本，以免修改原始数组
    uint64_t lo = 0;  // 0 的边界
    uint64_t hi = arr.size() - 1;  // 2 的边界
    uint64_t mid = 0;  // 1 的边界

    // 进行排序，直到所有元素都在正确的位置
    while (mid <= hi) {
        switch (arr[mid]) {
            // 如果当前元素是 0
            case 0:
                std::swap(arr[lo++], arr[mid++]);  // 将 0 与 lo 位置交换，并移动 lo 和 mid
                break;

            // 如果当前元素是 1
            case 1:
                mid++;  // 1 已经在正确的位置，直接向后移动
                break;

            // 如果当前元素是 2
            case 2:
                std::swap(arr[mid], arr[hi--]);  // 将 2 与 hi 位置交换，并移动 hi
                break;
        }
    }
    return arr;  // 返回排序后的数组
}
}  // namespace dnf_sort
}  // namespace sorting

/**
 * @brief 自我测试实现
 * @returns void
 */
static void test() {
    // 测试 1
    // [0, 1, 1, 2] 排序后应为 [0, 1, 1, 2]
    std::vector<uint64_t> array1 = {0, 1, 1, 2};
    std::cout << "Test 1... ";
    std::vector<uint64_t> arr1 = sorting::dnf_sort::dnfSort(array1);
    assert(std::is_sorted(std::begin(arr1), std::end(arr1)));  // 验证数组是否已排序
    std::cout << "passed" << std::endl;

    // 测试 2
    // [1, 0, 0, 1, 1, 0, 2, 1] 排序后应为 [0, 0, 0, 1, 1, 1, 1, 2]
    std::vector<uint64_t> array2 = {1, 0, 0, 1, 1, 0, 2, 1};
    std::cout << "Test 2... ";
    std::vector<uint64_t> arr2 = sorting::dnf_sort::dnfSort(array2);
    assert(std::is_sorted(std::begin(arr2), std::end(arr2)));  // 验证数组是否已排序
    std::cout << "passed" << std::endl;

    // 测试 3
    // [1, 1, 0, 0, 1, 2, 2, 0, 2, 1] 排序后应为 [0, 0, 0, 1, 1, 1, 1, 2, 2, 2]
    std::vector<uint64_t> array3 = {1, 1, 0, 0, 1, 2, 2, 0, 2, 1};
    std::cout << "Test 3... ";
    std::vector<uint64_t> arr3 = sorting::dnf_sort::dnfSort(array3);
    assert(std::is_sorted(std::begin(arr3), std::end(arr3)));  // 验证数组是否已排序
    std::cout << "passed" << std::endl;

    // 测试 4
    // [2, 2, 2, 0, 0, 1, 1] 排序后应为 [0, 0, 1, 1, 2, 2, 2]
    std::vector<uint64_t> array4 = {2, 2, 2, 0, 0, 1, 1};
    std::cout << "Test 4... ";
    std::vector<uint64_t> arr4 = sorting::dnf_sort::dnfSort(array4);
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
