#include <stdio.h>
// 快速排序的分区函数
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为基准
    int i = low; // 小于基准的元素的索引

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            // 交换 arr[i] 和 arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // 将基准元素放到正确的位置
    int temp = arr[i];
    arr[i] = arr[high];
    arr[high] = temp;
    return i; // 返回基准元素的索引
}

// 快速排序函数
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // 分区操作
        int pi = partition(arr, low, high);

        // 递归排序基准元素左右两侧的子数组
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void printArry(int* nums, int numsSize){
    for(int i = 0; i < numsSize;i++){
        printf("%d, ", nums[i]);
    }
}

int main()
{
    int nums[11] = {3,2,1,5,6,9,8,5,6,4,5};
    int len = sizeof(nums)/sizeof(int);

    quickSort(nums, 0, len-1);
    printArry(nums, len);
    printf("\n");
    //system("pause");
    return 0;
}