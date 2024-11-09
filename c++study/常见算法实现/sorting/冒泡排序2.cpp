/**
 * @file
 * @author [Aditya Prakash](https://adityaprakash.tech)
 * @brief 这是 [冒泡排序算法](https://www.geeksforgeeks.org/recursive-bubble-sort/) 的递归实现。
 *
 * @details
 * 冒泡排序算法的工作原理。
 *
 * 冒泡排序是一种简单的排序算法，用于重新排列元素的升序或降序。
 * 冒泡排序之所以得名，是因为数据会“冒泡”到数据集的顶部。
 *
 * ### 算法
 *
 * 什么是交换？
 *
 * 交换两个数字意味着我们交换它们的值。
 * 通常，需要一个额外的变量来完成此操作。
 * 这在下面的代码中有所说明：
 *
 * void swap(int x, int y){
 *     int z = x;
 *     x = y;
 *     y = z;
 * }
 *
 * 上面的过程是一个典型的交换过程。
 * 当我们给 x 赋值时，x 的旧值就会丢失。
 * 所以我们创建了一个临时变量 z 来存储 x 的初始值。
 * 然后使用 z 将 x 的初始值赋给 y，完成交换。
 *
 * 递归
 *
 * 尽管递归方法在性能上并不一定优于迭代版本，但它有助于增强对算法本身及递归概念的理解。
 * 在递归冒泡排序算法中，我们首先对整个数组进行函数调用，然后在每次递归时排除最后一个元素。
 * 这样，每次递归都固定了一个元素的位置。正式来说，对于第 `i` 次迭代，我们考虑的元素范围是到 `n-i`，其中 `n` 是数组的元素个数。退出条件：`n==1`，即子数组中只有一个元素。
 *
 * 复杂度分析
 * 时间复杂度：最优情况为 O(n)，平均情况为 O(n²)，最坏情况为 O(n²)。
 * 空间复杂度：O(n)
 *
 * 由于需要遍历数组 `n * (n-1)` 次。如果整个数组已经排序，则只需要遍历一次，因此最优情况的时间复杂度是 O(n)。
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于 std::vector 容器
#include <array>     /// 用于 std::array 容器
#include <algorithm> /// 用于 std::is_sorted 函数

/**
 * @namespace sorting
 * @brief 排序算法
 */
namespace sorting {

/**
 * @brief 递归冒泡排序算法的实现。函数接受一个数组，并通过递归进行排序。
 *        该函数还接受第二个参数 `n`，它表示数组的大小。
 * 
 * @tparam T 数组中元素的数据类型
 * @param nums 指向元素数组的指针。
 * @param n 数组的大小
 */
template <typename T>
void recursive_bubble_sort(std::vector<T> *nums, uint64_t n) {
    if (n == 1) {  //!< 基本情况，当数组的大小为1时直接返回
        return;
    }

    // 遍历整个数组
    for (uint64_t i = 0; i < n - 1; i++) {
        //!< 如果当前数字比下一个数字大，则交换它们的位置
        if ((*nums)[i] > (*nums)[i + 1]) {
            std::swap((*nums)[i], (*nums)[i + 1]);
        }
    }

    //!< 递归调用，在每次递归后固定一个元素（即排好序的最后一个元素）
    recursive_bubble_sort(nums, n - 1);
}
}  // namespace sorting

/**
 * @brief 测试用例实现
 * @returns void
 */
static void test() {
    // 1. 使用 `int` 类型的数组进行测试
    std::cout << "1st test using `int`\n";
    const uint64_t size = 6;
    std::vector<int64_t> arr;
    // 填充数组
    arr.push_back(22);
    arr.push_back(46);
    arr.push_back(94);
    arr.push_back(12);
    arr.push_back(37);
    arr.push_back(63);
    // 数组填充结束

    sorting::recursive_bubble_sort(&arr, size);  // 调用递归冒泡排序函数
    assert(std::is_sorted(std::begin(arr), std::end(arr)));  // 确保排序正确
    std::cout << " 1st test passed!\n";
    
    // 打印排序后的数组
    for (uint64_t i = 0; i < size; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;

    // 2. 使用 `double` 类型的数组进行测试
    std::cout << "2nd test using doubles\n";
    std::vector<double> double_arr;

    // 填充数组
    double_arr.push_back(20.4);
    double_arr.push_back(62.7);
    double_arr.push_back(12.2);
    double_arr.push_back(43.6);
    double_arr.push_back(74.1);
    double_arr.push_back(57.9);
    // 数组填充结束

    sorting::recursive_bubble_sort(&double_arr, size);  // 调用递归冒泡排序函数
    assert(std::is_sorted(std::begin(double_arr), std::end(double_arr)));  // 确保排序正确
    std::cout << " 2nd test passed!\n";
    
    // 打印排序后的数组
    for (uint64_t i = 0; i < size; i++) {
        std::cout << double_arr[i] << ", ";
    }
    std::cout << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 表示程序正常退出
 */
int main() { 
    test();  // 运行自测试用例
    return 0;
}
