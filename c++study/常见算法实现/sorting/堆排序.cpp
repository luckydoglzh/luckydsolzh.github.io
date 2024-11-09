/**
 * \file
 * \brief [堆排序算法](https://en.wikipedia.org/wiki/Heapsort) 实现
 *
 * \author [Ayaan Khan](http://github.com/ayaankhan98)
 *
 * \details
 * 堆排序是一种基于比较的排序算法。
 * 堆排序可以被看作是改进版的选择排序：
 * 与选择排序相似，堆排序将输入分为已排序区间和未排序区间，
 * 每次从未排序区间中提取最大元素并将其插入已排序区间。
 * 不同于选择排序，堆排序通过维护一个堆数据结构来高效地找到每一步中的最大元素，
 * 而不需要在未排序区间进行线性扫描。
 *
 * 时间复杂度 - \f$O(n \log(n))\f$
 *
 */
#include <algorithm>
#include <cassert>
#include <iostream>

/**
 *
 * 工具函数，用于排序后打印数组。
 *
 * @param arr 要打印的数组
 * @param sz 数组大小
 *
 */
template <typename T>
void printArray(T *arr, int sz) {
    for (int i = 0; i < sz; i++) std::cout << arr[i] << "  ";
    std::cout << "\n";
}

/**
 *
 * \addtogroup sorting 排序算法
 * @{
 *
 * 堆化过程可以被看作是从底向上构建堆，通过不断向下筛选以满足堆的性质。
 *
 * @param arr 要排序的数组
 * @param n 数组大小
 * @param i 要比较的节点位置（在二叉树中为元素位置）
 *
 */
template <typename T>
void heapify(T *arr, int n, int i) {
    int largest = i;           // 假设当前节点是最大值
    int l = 2 * i + 1;         // 左子节点索引
    int r = 2 * i + 2;         // 右子节点索引

    if (l < n && arr[l] > arr[largest])  // 如果左子节点比当前节点大
        largest = l;

    if (r < n && arr[r] > arr[largest])  // 如果右子节点比当前节点大
        largest = r;

    if (largest != i) {  // 如果最大元素不是当前元素，交换并递归堆化
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

/**
 * 使用堆化过程对数组进行排序
 *
 * @param arr 要排序的数组
 * @param n 数组大小
 *
 */
template <typename T>
void heapSort(T *arr, int n) {
    // 1. 构建最大堆（从最后一个非叶子节点开始）
    for (int i = n - 1; i >= 0; i--) heapify(arr, n, i);

    // 2. 一个一个的提取元素，并重新堆化
    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);  // 将最大元素移到数组末尾
        heapify(arr, i, 0);         // 对剩余元素重新堆化
    }
}

/**
 *
 * @}
 * 测试程序
 *
 */
void test() {
    std::cout << "Test 1\n";
    int arr[] = {-10, 78, -1, -6, 7, 4, 94, 5, 99, 0};
    int sz = sizeof(arr) / sizeof(arr[0]);  // sz - 数组大小
    printArray(arr, sz);  // 打印排序前的数组
    heapSort(arr, sz);    // 调用堆排序进行排序
    printArray(arr, sz);  // 打印排序后的数组
    assert(std::is_sorted(arr, arr + sz));  // 断言数组已排序
    std::cout << "Test 1 Passed\n========================\n";

    std::cout << "Test 2\n";
    double arr2[] = {4.5, -3.6, 7.6, 0, 12.9};
    sz = sizeof(arr2) / sizeof(arr2[0]);
    printArray(arr2, sz);  // 打印排序前的数组
    heapSort(arr2, sz);    // 调用堆排序进行排序
    printArray(arr2, sz);  // 打印排序后的数组
    assert(std::is_sorted(arr2, arr2 + sz));  // 断言数组已排序
    std::cout << "Test 2 passed\n";
}

/** 主函数 */
int main() {
    test();  // 执行测试
    return 0;
}
