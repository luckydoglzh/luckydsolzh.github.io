/**
 *  \addtogroup sorting 排序算法
 *  @{
 *  \file
 *  \brief [归并排序算法 (Merge Sort)](https://en.wikipedia.org/wiki/Merge_sort) 实现
 *
 *  \author [Ayaan Khan](http://github.com/ayaankhan98)
 *
 *  \details
 *  归并排序是一种高效的通用比较排序算法。
 *  归并排序是一种分治算法。
 *
 */
#include <iostream>

/**
 * @brief 合并两个已排序的子数组
 *
 * merge(arr, l, m, r) 是归并排序中的关键过程，假设 arr[l..m] 和 arr[m+1..r] 已排序，
 * 它将这两个已排序的子数组合并成一个。
 *
 * @param arr - 待排序的数组，包含两个子数组 arr[l...m] 和 arr[m+1...r]
 * @param l - 第一个子数组的左边界或起始索引
 * @param m - 第一个子数组的右边界或结束索引
 * 
 * (第二个子数组从 m+1 开始，到 r 为止)
 *
 * @param r - 第二个子数组的右边界或结束索引
 */
void merge(int *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;  // 第一个子数组的大小
    int n2 = r - m;      // 第二个子数组的大小

    int *L = new int[n1], *R = new int[n2];  // 创建临时数组 L 和 R

    // 将 arr[l..m] 复制到 L 数组
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    // 将 arr[m+1..r] 复制到 R 数组
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    // 合并 L 和 R 数组
    while (i < n1 || j < n2) {
        if (j >= n2 || (i < n1 && L[i] <= R[j])) {
            arr[k] = L[i];  // 如果 L[i] 小于等于 R[j]，则将 L[i] 放入 arr[k]
            i++;
        } else {
            arr[k] = R[j];  // 否则将 R[j] 放入 arr[k]
            j++;
        }
        k++;  // 移动到下一个位置
    }

    // 释放临时数组
    delete[] L;
    delete[] R;
}

/**
 * @brief 归并排序算法
 *
 * 归并排序是一种分治算法，它将输入数组分为两半，对两半分别递归排序，
 * 然后通过 merge() 函数将两个已排序的部分合并。
 *
 * @param arr - 待排序的数组
 * @param l - 数组的左边界或起始索引
 * @param r - 数组的右边界或结束索引
 */
void mergeSort(int *arr, int l, int r) {
    if (l < r) {
        // 计算中间索引
        int m = l + (r - l) / 2;

        // 递归排序左半部分
        mergeSort(arr, l, m);
        // 递归排序右半部分
        mergeSort(arr, m + 1, r);

        // 合并已排序的两部分
        merge(arr, l, m, r);
    }
}

/**
 * @brief 输出排序后的数组
 */
void show(int *arr, int size) {
    for (int i = 0; i < size; i++) std::cout << arr[i] << " ";
    std::cout << "\n";
}

/** 主函数 */
int main() {
    int size;
    std::cout << "请输入数组元素的数量 : ";
    std::cin >> size;
    
    // 动态分配数组
    int *arr = new int[size];
    
    std::cout << "请输入未排序的元素 : ";
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];  // 输入数组元素
    }

    // 调用归并排序函数
    mergeSort(arr, 0, size - 1);
    
    std::cout << "排序后的数组 : ";
    show(arr, size);  // 输出排序后的数组

    delete[] arr;  // 释放内存
    return 0;
}

/** @} */
