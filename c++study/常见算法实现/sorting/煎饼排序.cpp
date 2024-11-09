/**
 * @file
 * @brief 薄煎饼排序（Pancake Sort）算法实现
 * 该算法通过翻转任意数量的薄煎饼来将无序的薄煎饼堆排序，
 * 目标是使用最少的翻转次数来完成排序。
 *
 * @details
 * 与传统的排序算法不同，薄煎饼排序的目标是以最少的翻转次数对序列进行排序，
 * 而不是最少的比较次数。整体时间复杂度是 O(n^2)。
 * 例如：
 * 示例1：无序薄煎饼尺寸：{2,5,3,7,8} 排序后：{2,3,5,7,8}
 * 示例2：无序薄煎饼尺寸：{22,51,37,73,81} 排序后：{22,37,51,73,81}
 * @author [Divyansh Gupta](https://github.com/divyansh12323)
 * @see 更多关于 [Pancake sort](https://en.wikipedia.org/wiki/Pancake_sorting)
 * @see 相关问题在 [Leetcode](https://leetcode.com/problems/pancake-sorting/)
 */

#include <algorithm>  // 用于 std::is_sorted
#include <cassert>    // 用于 std::assert
#include <iostream>   // 用于输入输出操作
#include <vector>     // 用于 std::vector

/**
 * @namespace sorting
 * @brief 排序算法
 */
namespace sorting {
/**
 * @namespace pancake_sort
 * @brief 薄煎饼排序算法的相关函数
 */
namespace pancake_sort {
/**
 * @brief 反转 C 风格数组中的元素
 * @param [start,end] arr 数组的元素。
 * @param start 数组的起始索引
 * @param end 数组的结束索引
 * @returns void
 */
template <typename T>
void reverse(std::vector<T> &arr, int start, int end) {
    T temp;  // 临时变量
    while (start <= end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

/**
 * @brief 该实现用于处理 C 风格数组输入，并就地修改数组。
 * @param [start,end] arr 数组元素
 * @param size 数组的大小
 * @returns 0
 */
template <typename T>
int pancakeSort(std::vector<T> &arr, int size) {
    // 从最大元素开始，逐步减少排序的范围
    for (int i = size; i > 1; --i) {
        int max_index = 0, j = 0;  // 初始化一些变量
        T max_value = 0;
        
        // 找到最大元素的索引
        for (j = 0; j < i; j++) {
            if (arr[j] >= max_value) {
                max_value = arr[j];
                max_index = j;
            }
        }

        // 如果最大元素不是当前范围的最后一个元素，则进行两次反转
        if (max_index != i - 1) {
            reverse(arr, 0, max_index);  // 反转前半部分
            reverse(arr, 0, i - 1);      // 反转整个当前范围
        }
    }
    return 0;
}
}  // namespace pancake_sort
}  // namespace sorting

/**
 * @brief 测试实现
 * @returns void
 */
static void test() {
    // 示例1：整数数组
    const int size1 = 7;
    std::cout << "\nTest 1- std::vector<int>类型...";
    std::vector<int> arr1 = {23, 10, 20, 11, 12, 6, 7};
    sorting::pancake_sort::pancakeSort(arr1, size1);
    assert(std::is_sorted(arr1.begin(), arr1.end()));  // 检查数组是否排序
    std::cout << "通过测试\n";
    for (int i = 0; i < size1; i++) {
        std::cout << arr1[i] << " ,";
    }
    std::cout << std::endl;

    // 示例2：浮点数数组
    const int size2 = 8;
    std::cout << "\nTest 2- std::vector<double>类型...";
    std::vector<double> arr2 = {23.56, 10.62, 200.78, 111.484,
                                3.9,   1.2,   61.77,  79.6};
    sorting::pancake_sort::pancakeSort(arr2, size2);
    assert(std::is_sorted(arr2.begin(), arr2.end()));  // 检查数组是否排序
    std::cout << "通过测试\n";
    for (int i = 0; i < size2; i++) {
        std::cout << arr2[i] << ", ";
    }
    std::cout << std::endl;

    // 示例3：浮动数组
    const int size3 = 7;
    std::cout << "\nTest 3- std::vector<float>类型...";
    std::vector<float> arr3 = {6.56, 12.62, 200.78, 768.484, 19.27, 68.87, 9.6};
    sorting::pancake_sort::pancakeSort(arr3, size3);
    assert(std::is_sorted(arr3.begin(), arr3.end()));  // 检查数组是否排序
    std::cout << "通过测试\n";
    for (int i = 0; i < size3; i++) {
        std::cout << arr3[i] << ", ";
    }
    std::cout << std::endl;
}

/**
 * @brief 主函数
 * @returns 0
 */
int main() {
    test();  // 运行测试
    return 0;
}
