/**
 * \file
 * \brief 插值查找算法 [Interpolation Search](https://en.wikipedia.org/wiki/Interpolation_search)
 */
#include <iostream>

/** 
 * 使用插值查找算法在数组中查找值
 * 
 * \param [in] A 要查找的数组
 * \param [in] n 数组的长度
 * \param [in] x 要查找的目标值
 * \returns 如果找到目标值，返回目标值的索引
 * \returns 如果未找到目标值，返回 -1
 */
int InterpolationSearch(int A[], int n, int x) {
    int low = 0;  // 设置查找范围的最小索引
    int high = n - 1;  // 设置查找范围的最大索引
    
    while (low <= high) {
        // 使用插值公式计算当前位置 mid
        int mid = low + (((high - low) * (x - A[low])) / (A[high] - A[low]));
        
        if (x == A[mid]) {
            return mid;  // 如果找到了目标值，返回该位置索引
        } else if (x < A[mid]) {
            high = mid - 1;  // 如果目标值小于 mid 位置的值，缩小查找范围至 mid 左侧
        } else {
            low = mid + 1;  // 如果目标值大于 mid 位置的值，缩小查找范围至 mid 右侧
        }
    }

    return -1;  // 如果未找到目标值，返回 -1
}

/** 主函数 */
int main() {
    int A[] = {2, 4, 5, 7, 13, 14, 15, 23};  // 定义一个已排序的数组
    int x = 17;  // 要查找的目标值

    // 调用插值查找函数，传入数组 A 和目标值 x
    int index = InterpolationSearch(A, 8, x);
    
    if (index < 0) {
        std::cout << "Number " << x << " not found" << std::endl;  // 如果未找到目标值
    } else {
        std::cout << "Number " << x << " is at " << index << std::endl;  // 如果找到目标值，输出其索引
    }
}

/**
 * 注释：
 * 1. 插值查找算法适用于已排序的数组。它通过插值估算目标值可能的位置，然后比较该位置的元素与目标值。
 * 2. 插值查找的时间复杂度与数据分布密切相关。理想情况下，时间复杂度接近 O(log log n)，
 *    但最坏情况下，时间复杂度可能退化为 O(n)。
 * 3. 在该程序中，数组 A 被硬编码为静态数组，因此目标值 x 是随机设定的。
 *    如果数组元素由用户输入，可以将其改为动态输入方式。
 */
