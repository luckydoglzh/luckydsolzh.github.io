// C++ 程序使用桶排序算法对数组进行排序
#include <algorithm>
#include <iostream>
#include <vector>

// 使用桶排序算法对数组 arr[] 进行排序，数组大小为 n
void bucketSort(float arr[], int n) {
    // 1) 创建 n 个空桶
    std::vector<float> *b = new std::vector<float>[n];

    // 2) 将数组元素分配到不同的桶中
    for (int i = 0; i < n; i++) {
        int bi = n * arr[i];  // 计算桶的索引
        b[bi].push_back(arr[i]);  // 将元素放入对应的桶中
    }

    // 3) 对每个桶内的元素进行排序
    for (int i = 0; i < n; i++) {
        std::sort(b[i].begin(), b[i].end());  // 对每个桶中的元素进行排序
    }

    // 4) 将所有桶中的元素合并到原数组 arr[] 中
    int index = 0;  // 用于重新排列元素的索引
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++) arr[index++] = b[i][j];  // 将桶中的元素按顺序复制回数组

    // 释放桶的内存
    delete[] b;
}

/* 驱动程序用于测试上述函数 */
int main() {
    float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};  // 测试数据
    int n = sizeof(arr) / sizeof(arr[0]);  // 数组的大小
    bucketSort(arr, n);  // 调用桶排序函数进行排序

    // 输出排序后的数组
    std::cout << "排序后的数组是：\n";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";  // 输出每个排序后的元素
    }
    return 0;
}
