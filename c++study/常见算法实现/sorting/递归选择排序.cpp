/**
 * @file
 * @brief 使用递归实现的 [选择排序](https://en.wikipedia.org/wiki/Selection_sort)
 * @details
 * 选择排序算法将输入列表分为两部分：已排序的子列表（从左到右构建）和剩余的未排序项。
 * 初始时，已排序的子列表为空，未排序的子列表是整个输入列表。
 * 算法通过在未排序的子列表中找到最小（或最大）元素，并将其与最左边的未排序元素交换，
 * 然后将子列表的边界向右移动一个元素。
 *
 * ### 实现
 * FindMinIndex
 * 该函数通过递归找到数组（列表）的最小元素，方法是将数组大小减少1，并将其与数组的最后一个元素进行比较，
 * 以找出整个数组的最小值。
 *
 * SelectionSortRecursive
 * 与选择排序类似，它将列表分为两部分（即已排序和未排序部分），并找到未排序部分的最小元素。
 * 通过调用 `FindMinIndex` 函数，它将最小元素与列表的第一个元素交换，然后对剩余的未排序列表递归排序。
 * @author [Tushar Khanduri](https://github.com/Tushar-K24)
 */

#include <algorithm>  /// 用于 std::is_sorted
#include <cassert>    /// 用于 assert
#include <iostream>   /// 用于 std::swap 和输入输出操作
#include <vector>     /// 用于 std::vector

/**
 * @namespace sorting
 * @brief 排序算法
 */
namespace sorting {
/**
 * @namespace selection_sort_recursive
 * @brief 使用递归实现的 [选择排序](https://en.wikipedia.org/wiki/Selection_sort)
 */
namespace selection_sort_recursive {
/**
 * @brief 主要函数用于查找最小元素的索引
 * @tparam T 数组的类型
 * @param in_arr 要查找最小元素的数组
 * @param current_position 当前处理的位置（索引）
 * @returns 最小元素的索引
 */
template <typename T>
uint64_t findMinIndex(const std::vector<T> &in_arr,
                      uint64_t current_position = 0) {
    // 如果当前位置是数组的倒数第二个元素，返回当前位置
    if (current_position + 1 == in_arr.size()) {
        return current_position;
    }
    // 递归调用，找到当前数组中最小元素的索引
    uint64_t answer = findMinIndex(in_arr, current_position + 1);
    // 如果当前位置的元素更小，更新最小元素的索引
    if (in_arr[current_position] < in_arr[answer]) {
        answer = current_position;
    }
    return answer;
}

/**
 * @brief 主要函数实现选择排序
 * @tparam T 数组的类型
 * @param in_arr 要排序的数组，
 * @param current_position 当前处理的位置（索引）
 * @returns void
 */
template <typename T>
void selectionSortRecursive(std::vector<T> &in_arr,
                            uint64_t current_position = 0) {
    // 当当前位置等于数组的大小时，排序完成，递归结束
    if (current_position == in_arr.size()) {
        return;
    }
    // 找到从当前位置开始的最小元素的索引
    uint64_t min_element_idx =
        selection_sort_recursive::findMinIndex(in_arr, current_position);
    // 如果最小元素的索引不等于当前索引，交换位置
    if (min_element_idx != current_position) {
        std::swap(in_arr[min_element_idx], in_arr[current_position]);
    }
    // 对剩余未排序部分递归进行选择排序
    selectionSortRecursive(in_arr, current_position + 1);
}
}  // namespace selection_sort_recursive
}  // namespace sorting

/**
 * @brief 自测试用例实现
 * @returns void
 */
static void test() {
    // 1st 测试
    // [1, 0, 2, 1] 应该返回 [0, 1, 1, 2]
    std::vector<uint64_t> array1 = {0, 1, 1, 2};
    std::cout << "1st test... ";
    sorting::selection_sort_recursive::selectionSortRecursive(array1);
    // 检查排序后的数组是否正确
    assert(std::is_sorted(std::begin(array1), std::end(array1)));
    std::cout << "passed" << std::endl;

    // 2nd 测试
    // [1, 0, 0, 1, 1, 0, 2, 1] 应该返回 [0, 0, 0, 1, 1, 1, 1, 2]
    std::vector<uint64_t> array2 = {1, 0, 0, 1, 1, 0, 2, 1};
    std::cout << "2nd test... ";
    sorting::selection_sort_recursive::selectionSortRecursive(array2);
    // 检查排序后的数组是否正确
    assert(std::is_sorted(std::begin(array2), std::end(array2)));
    std::cout << "passed" << std::endl;

    // 3rd 测试
    // [1, 1, 0, 0, 1, 2, 2, 0, 2, 1] 应该返回 [0, 0, 0, 1, 1, 1, 1, 2, 2, 2]
    std::vector<uint64_t> array3 = {1, 1, 0, 0, 1, 2, 2, 0, 2, 1};
    std::cout << "3rd test... ";
    sorting::selection_sort_recursive::selectionSortRecursive(array3);
    // 检查排序后的数组是否正确
    assert(std::is_sorted(std::begin(array3), std::end(array3)));
    std::cout << "passed" << std::endl;

    // 4th 测试
    // [2, 2, 2, 0, 0, 1, 1] 应该返回 [0, 0, 1, 1, 2, 2, 2]
    std::vector<uint64_t> array4 = {2, 2, 2, 0, 0, 1, 1};
    std::cout << "4th test... ";
    sorting::selection_sort_recursive::selectionSortRecursive(array4);
    // 检查排序后的数组是否正确
    assert(std::is_sorted(std::begin(array4), std::end(array4)));
    std::cout << "passed" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 表示程序正常退出
 */
int main() {
    test();  // 运行自测试用例
    return 0;
}
