// C++ 程序实现 TimSort 排序算法
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>

const int RUN = 32; // 定义每个子数组的大小

// 此函数对数组从左索引到右索引的部分进行插入排序，排序区间大小最多为 RUN
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        const int temp = arr[i];
        int j = i - 1;
        // 在已排序部分插入当前元素
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// merge 函数用于合并已排序的子数组
void merge(int arr[], int l, int m, int r) {
    // 将原始数组分为两个子数组，左子数组和右子数组
    const int len1 = m - l + 1, len2 = r - m;
    int *left = new int[len1], *right = new int[len2];
    for (int i = 0; i < len1; i++) left[i] = arr[l + i];
    for (int i = 0; i < len2; i++) right[i] = arr[m + 1 + i];

    int i = 0;
    int j = 0;
    int k = l;

    // 合并两个子数组到原数组
    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // 如果左边子数组还有剩余元素，继续复制
    while (i < len1) {
        arr[k] = left[i];
        k++;
        i++;
    }

    // 如果右边子数组还有剩余元素，继续复制
    while (j < len2) {
        arr[k] = right[j];
        k++;
        j++;
    }
    delete[] left;
    delete[] right;
}

// 迭代式 TimSort 函数，对数组 [0...n-1] 进行排序（类似于归并排序）
void timSort(int arr[], int n) {
    // 对大小为 RUN 的子数组进行插入排序
    for (int i = 0; i < n; i += RUN)
        insertionSort(arr, i, std::min((i + 31), (n - 1)));

    // 从大小为 RUN（或32）的子数组开始合并。每次合并后，合并的子数组大小翻倍：32 -> 64 -> 128 -> 256 ...
    for (int size = RUN; size < n; size = 2 * size) {
        // 选择左子数组的起始点。我们将合并 arr[left..left+size-1] 和 arr[left+size, left+2*size-1]
        // 每次合并后，left 的值增加 2*size
        for (int left = 0; left < n; left += 2 * size) {
            // 找到左子数组的结束点，mid+1 是右子数组的起始点
            const int mid = std::min((left + size - 1), (n - 1));
            const int right = std::min((left + 2 * size - 1), (n - 1));

            // 合并子数组 arr[left.....mid] 和 arr[mid+1....right]
            merge(arr, left, mid, right);
        }
    }
}

// 打印数组的辅助函数
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d  ", arr[i]);
    std::cout << std::endl;
}

/**
 * @brief 自我测试实现
 * @returns void
 */
void tests() {
    // 测试用例：长度为 65 的数组
    constexpr int N = 65;
    int arr[N];

    std::iota(arr, arr + N, 0);  // 填充数组为 0 到 64 的顺序
    std::reverse(arr, arr + N);  // 反转数组
    assert(!std::is_sorted(arr, arr + N));  // 确保数组未排序

    timSort(arr, N);  // 调用 TimSort 排序
    assert(std::is_sorted(arr, arr + N));  // 确保排序后的数组是有序的
}

// 驱动程序测试上述功能
int main() {
    tests();  // 运行自我测试

    int arr[] = {5, 21, 7, 23, 19};
    const int n = sizeof(arr) / sizeof(arr[0]);
    printf("Given Array is\n");
    printArray(arr, n);  // 打印排序前的数组

    timSort(arr, n);  // 调用 TimSort 排序

    printf("After Sorting Array is\n");
    printArray(arr, n);  // 打印排序后的数组
    return 0;
}
