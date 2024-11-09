#include <cmath>   // 用于数学计算，如 pow 函数
#include <cstdlib> // 用于 malloc 和 free 等内存管理函数
#include <cstring> // 用于 memset 函数
#include <iostream> // 用于输入输出

// 基数排序函数
void radixsort(int a[], int n) {
    int count[10];     // 计数数组，用于存储每个位的出现频率
    int* output = new int[n]; // 临时数组用于存储排序后的数组
    memset(output, 0, n * sizeof(*output)); // 初始化 output 数组
    memset(count, 0, sizeof(count)); // 初始化计数数组

    int max = 0; // 用于记录数组中的最大值
    // 找出数组中的最大值
    for (int i = 0; i < n; ++i) {
        if (a[i] > max) {
            max = a[i];
        }
    }

    int maxdigits = 0; // 最大值的位数
    // 计算最大值的位数
    while (max) {
        maxdigits++;
        max /= 10;
    }

    // 对每一位进行排序（从低位到高位）
    for (int j = 0; j < maxdigits; j++) {
        // 计数排序：对当前位的每个数字进行计数
        for (int i = 0; i < n; i++) {
            int t = std::pow(10, j);  // 计算当前位的权值
            count[(a[i] % (10 * t)) / t]++;  // 更新计数数组
        }

        int k = 0; // 用于将排序结果存放到 output 数组中
        // 根据计数数组进行排序
        for (int p = 0; p < 10; p++) {
            for (int i = 0; i < n; i++) {
                int t = std::pow(10, j); // 当前位的权值
                // 判断当前数字在第 j 位的值是否等于 p
                if ((a[i] % (10 * t)) / t == p) {
                    output[k] = a[i]; // 将符合条件的数字放入 output 数组
                    k++;
                }
            }
        }

        memset(count, 0, sizeof(count)); // 重置计数数组

        // 将排序后的结果复制回原数组
        for (int i = 0; i < n; ++i) {
            a[i] = output[i];
        }
    }

    delete[] output; // 释放临时数组的内存
}

// 打印数组的函数
void print(int a[], int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << a[i] << " "; // 打印每个元素
    }
    std::cout << std::endl;
}

// 主函数
int main(int argc, char const* argv[]) {
    int a[] = {170, 45, 75, 90, 802, 24, 2, 66};  // 待排序数组
    int n = sizeof(a) / sizeof(a[0]); // 计算数组的长度
    radixsort(a, n);  // 调用基数排序函数
    print(a, n); // 打印排序后的数组
    return 0;
}
