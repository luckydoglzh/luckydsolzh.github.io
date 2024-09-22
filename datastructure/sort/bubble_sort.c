#include <stdio.h>
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // 设定一个标志位，用于优化
        int swapped = 0; 
        
        // 最后 i 个元素已经排好序
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换 arr[j] 和 arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1; // 标记发生了交换
            }
        }
        
        // 如果没有发生交换，数组已经排好序，提前结束
        if (swapped == 0) {
            break;
        }
    }
}