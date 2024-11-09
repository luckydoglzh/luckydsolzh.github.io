/**
 *
 * \file
 * \brief [Comb Sort算法](https://en.wikipedia.org/wiki/Comb_sort)
 *
 * \author
 *
 * \details
 * - 是冒泡排序算法的改进版本
 * - 冒泡排序比较相邻元素，而Comb Sort使用大于1的间隔（gap）
 * - 最佳时间复杂度：O(n)
 *   最坏时间复杂度：O(n^2)
 *
 */

#include <algorithm>
#include <cassert>
#include <iostream>

/**
 *
 * 通过将当前gap缩小1.3倍来计算下一个gap
 * @param gap 当前gap
 * @return 新的gap
 *
 */
int FindNextGap(int gap) {
    gap = (gap * 10) / 13;  // 按照1.3的缩小因子计算新的gap

    // 返回gap，确保gap不小于1
    return std::max(1, gap);
}

/** 
 * CombSort排序函数
 *
 * @param arr 需要排序的数组
 * @param l 数组的起始索引
 * @param r 数组的结束索引
 *
 */
void CombSort(int *arr, int l, int r) {
    /**
     *
     * 初始gap设置为数组的最大值，即r，避免传递数组大小n的参数，使用r来初始化gap。
     *
     */
    int gap = r;  // 设置初始gap为数组的大小

    // 初始化swapped为true，确保循环运行
    bool swapped = true;

    // 只要gap不等于1，或者有元素被交换，就继续运行
    while (gap != 1 || swapped) {
        // 计算下一个gap
        gap = FindNextGap(gap);

        // 设置swapped为false，表示没有元素被交换
        swapped = false;

        // 使用当前gap比较所有元素
        for (int i = l; i < r - gap; ++i) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);  // 交换元素
                swapped = true;  // 标记为已交换
            }
        }
    }
}

void tests() {
    /// 测试1
    int arr1[10] = {34, 56, 6, 23, 76, 34, 76, 343, 4, 76};
    CombSort(arr1, 0, 10);
    assert(std::is_sorted(arr1, arr1 + 10));  // 检查数组是否已排序
    std::cout << "Test 1 passed\n";

    /// 测试2
    int arr2[8] = {-6, 56, -45, 56, 0, -1, 8, 8};
    CombSort(arr2, 0, 8);
    assert(std::is_sorted(arr2, arr2 + 8));  // 检查数组是否已排序
    std::cout << "Test 2 Passed\n";
}

/** 主函数 */
int main() {
    /// 执行预定义的测试
    tests();

    /// 用户交互部分
    int n;
    std::cin >> n;  // 输入数组元素数量
    int *arr = new int[n];  // 动态分配数组
    for (int i = 0; i < n; ++i) std::cin >> arr[i];  // 输入数组元素

    CombSort(arr, 0, n);  // 对数组进行CombSort排序

    // 输出排序后的数组
    for (int i = 0; i < n; ++i) std::cout << arr[i] << ' ';
    
    delete[] arr;  // 释放动态分配的内存
    return 0;
}
