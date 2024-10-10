#include <stdio.h>
//说白了就是上滤法排序
// 函数声明
void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);
void printArray(int arr[], int size);

// 主函数
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7}; // 测试数组
    int n = sizeof(arr) / sizeof(arr[0]); // 数组长度

    printf("原数组: ");
    printArray(arr, n);

    heapSort(arr, n); // 进行堆排序

    printf("排序后数组: ");
    printArray(arr, n); // 输出排序后的数组
    return 0;
}

// 堆化过程
void heapify(int arr[], int n, int i) {
    int largest = i; // 初始化最大元素为根
    int left = 2 * i + 1; // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 如果左子节点存在且大于根节点，则更新最大元素
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 如果右子节点存在且大于当前最大元素，则更新最大元素
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 如果最大元素不是根节点，则交换并递归堆化
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // 递归堆化影响到的子树
        heapify(arr, n, largest);
    }
}

// 堆排序
void heapSort(int arr[], int n) {
    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // 一个个提取元素
    for (int i = n - 1; i > 0; i--) {
        // 将当前根（最大值）交换到末尾
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // 递归堆化缩小的堆
        heapify(arr, i, 0);
    }
}

// 输出数组的函数
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
