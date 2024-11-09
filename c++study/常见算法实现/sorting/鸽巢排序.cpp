/**
 * @file
 * @brief [鸽巢排序算法](https://en.wikipedia.org/wiki/Pigeonhole_sort)的实现
 * @author [Lownish](https://github.com/Lownish)
 * @details
 * 鸽巢排序是一种适用于元素数量和可能的键值数量大致相同的情况的排序算法。
 * 它的时间复杂度为 O(n + Range)，其中 n 是输入数组的元素数量，‘Range’ 是数组中可能值的数量。
 *
 * 该算法的时间复杂度是 O(n+N)。
 */

#include <algorithm>  // 用于 std::is_sorted
#include <array>      // 用于 std::array
#include <cassert>    // 用于 assert
#include <iostream>   // 用于输入输出操作

/**
 * @namespace sorting
 * @brief 排序算法
 */
namespace sorting {

/**
 * 使用鸽巢排序算法对大小为 n 的数组进行排序
 * 该函数将通过鸽巢算法排序数组并打印结果
 * @param arr 未排序的数组
 * @returns 排序后的数组
 */
template <std::size_t N>
std::array<int, N> pigeonSort(std::array<int, N> arr) {
    // 找到数组中的最小值和最大值
    auto min = std::min_element(std::begin(arr), std::end(arr));
    auto max = std::max_element(std::begin(arr), std::end(arr));

    // Range 表示需要的鸽巢数量
    int range = *max - *min + 1;
    int *hole = new int[range]();  // 创建一个数组用于存放鸽巢

    // 将所有数组元素放入鸽巢中
    for (int i = 0; i < N; i++) {
        hole[arr[i] - *min] = arr[i];
    }

    // 从鸽巢中取出元素并存储回原数组
    int count = 0;
    for (int i = 0; i < range; i++) {
        while (hole[i] != '\0') {
            arr[count] = hole[i];
            hole[i] = {};  // 清空该位置
            count++;
        }
    }
    delete[] hole;  // 释放鸽巢空间

    return arr;  // 返回排序后的数组
}
}  // namespace sorting

/**
 * 测试函数 1，使用未排序的数组 {8, 3, 2, 7, 4, 6, 8}
 * @returns 无
 */
static void test_1() {
    const int n = 7;
    std::array<int, n> test_array = {8, 3, 2, 7, 4, 6, 8};

    test_array = sorting::pigeonSort<n>(test_array);

    assert(std::is_sorted(std::begin(test_array), std::end(test_array)));  // 验证数组是否已排序

    // 打印排序后的数组
    for (int i = 0; i < n; i++) {
        std::cout << test_array.at(i) << " ";
    }
    std::cout << "\nPassed\n";
}

/**
 * 测试函数 2，使用未排序的数组 {802, 630, 20, 745, 52, 300, 612, 932, 78, 187}
 * @returns 无
 */
static void test_2() {
    const int n = 10;
    std::array<int, n> test_array = {802, 630, 20,  745, 52,
                                     300, 612, 932, 78,  187};

    test_array = sorting::pigeonSort<n>(test_array);

    assert(std::is_sorted(std::begin(test_array), std::end(test_array)));  // 验证数组是否已排序

    // 打印排序后的数组
    for (int i = 0; i < n; i++) {
        std::cout << test_array.at(i) << " ";
    }
    std::cout << "\nPassed\n";
}

/**
 * 测试函数 3，使用未排序的数组 {11,13,12,14}
 * @returns 无
 */
static void test_3() {
    const int n = 4;
    std::array<int, n> test_array = {11, 13, 12, 14};

    test_array = sorting::pigeonSort<n>(test_array);

    assert(std::is_sorted(std::begin(test_array), std::end(test_array)));  // 验证数组是否已排序

    // 打印排序后的数组
    for (int i = 0; i < n; i++) {
        std::cout << test_array.at(i) << " ";
    }
    std::cout << "\nPassed\n";
}

/**
 * 主函数
 */
int main() {
    test_1();  // 执行测试 1
    test_2();  // 执行测试 2
    test_3();  // 执行测试 3

    return 0;  // 程序结束
}
