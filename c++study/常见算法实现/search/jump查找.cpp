/**
 * \file
 * \brief C++ 程序实现 [Jump Search](https://en.wikipedia.org/wiki/Jump_search) 算法
 */
#include <algorithm>
#include <cmath>
#include <iostream>

/** 
 * Jump Search 算法实现
 * 
 * @param arr 待查找的数组
 * @param x 目标值
 * @param n 数组长度
 * @return 如果找到目标值，返回目标值的索引，否则返回 -1
 */
int jumpSearch(int arr[], int x, int n) {
    // 计算跳跃的步长（即每次跳跃的区间大小）
    int step = std::sqrt(n);

    // 查找目标值所在的区间
    int prev = 0;
    while (arr[std::min(step, n) - 1] < x) {  // 如果目标值在当前区间的末尾值之前
        prev = step;  // 将区间的开始位置移动到当前区间的结束位置
        step += std::sqrt(n);  // 跳跃到下一个区间
        if (prev >= n)  // 如果跳跃位置超出数组范围，说明目标值不存在
            return -1;
    }

    // 在目标区间内使用线性查找
    while (arr[prev] < x) {  // 如果当前区间的起始值小于目标值，继续向后查找
        prev++;

        // 如果已到达下一个区间的起始位置或数组末尾，说明目标值不存在
        if (prev == std::min(step, n))
            return -1;
    }

    // 如果目标值在当前区间内
    if (arr[prev] == x)
        return prev;  // 返回目标值的索引

    return -1;  // 如果找不到目标值，返回 -1
}

// 主程序，用于测试 Jump Search 函数
int main() {
    int arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610};  // 已排序数组
    int x = 55;  // 要查找的目标值
    int n = sizeof(arr) / sizeof(arr[0]);  // 计算数组的长度

    // 使用 Jump Search 查找目标值的索引
    int index = jumpSearch(arr, x, n);

    // 输出目标值的索引
    std::cout << "\nNumber " << x << " is at index " << index;
    return 0;
}

/**
 * 中文注释：
 * 1. Jump Search 算法是一种适用于已排序数组的搜索算法，通过跳跃的方式减少比较次数。
 * 2. 算法的核心思想是将数组分成若干个固定大小的区间，每次跳跃一个区间，查找目标值所在的区间，
 *    然后在该区间内执行线性查找。
 * 3. 该算法的时间复杂度为 O(√n)，比线性查找 O(n) 要快，但慢于二分查找 O(log n)。
 * 4. 在此实现中，使用 `std::sqrt(n)` 作为每次跳跃的步长，并根据目标值的位置调整跳跃区间。
 */
