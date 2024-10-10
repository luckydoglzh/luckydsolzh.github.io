#include <stdio.h>
//归并排序也很简单
// 思路：
// 1，把一个数组分成两块，分别排序
// 2, 排好序之后合并即可
// 3，不断递归直到叶子节点
// 函数声明
void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);
void printArray(int arr[], int size);

// 主函数
int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10}; // 测试数组
    int n = sizeof(arr) / sizeof(arr[0]); // 数组长度

    printf("原数组: ");
    printArray(arr, n);

    mergeSort(arr, 0, n - 1); // 进行归并排序

    printf("排序后数组: ");
    printArray(arr, n); // 输出排序后的数组
    return 0;
}

// 合并两个已排序的子数组
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1; // 左子数组的大小
    int n2 = right - mid; // 右子数组的大小

    // 创建临时数组
    int L[n1], R[n2];

    // 复制数据到临时数组
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // 合并临时数组
    i = 0; // 初始左子数组索引
    j = 0; // 初始右子数组索引
    k = left; // 初始合并数组索引

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // 复制剩余的元素（如果有的话）
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// 归并排序
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // 防止溢出

        mergeSort(arr, left, mid); // 对左半部分进行排序
        mergeSort(arr, mid + 1, right); // 对右半部分进行排序
        merge(arr, left, mid, right); // 合并已排序的子数组
    }
}

// 输出数组的函数
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
