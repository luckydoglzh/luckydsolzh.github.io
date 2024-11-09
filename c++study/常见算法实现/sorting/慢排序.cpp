// 返回排序后的数组，执行SlowSort排序算法
// SlowSort是一种幽默性质的排序算法，实际上并不实用。
// 它基于“乘以并投降”的原则，这是“分而治之”方法的一种戏谑。
// 该算法由Andrei Broder和Jorge Stolfi在1986年提出，
// 他们的论文《Pessimal Algorithms and Simplexity Analysis》中描述了这一算法。
// 该算法将一个问题分解成多个子问题，因此是“最差”的排序算法，
// 但是它依然在不懈地朝着结果努力。
// 它的时间复杂度是极其差的。

#include <iostream>

// SlowSort 算法的实现
void SlowSort(int a[], int i, int j) {
    if (i >= j)  // 如果i大于或等于j，则无需继续排序
        return;
    int m = i + (j - i) / 2;  // 计算中点m，避免溢出的方式
    int temp;
    
    // 对左半部分排序
    SlowSort(a, i, m);
    
    // 对右半部分排序
    SlowSort(a, m + 1, j);
    
    // 如果右部分的元素小于中点元素，则交换两者
    if (a[j] < a[m]) {
        temp = a[j];  // 交换a[j]和a[m]
        a[j] = a[m];
        a[m] = temp;
    }
    
    // 对剩余部分进行排序
    SlowSort(a, i, j - 1);
}

// 示例主函数
int main() {
    int size;
    std::cout << "\n请输入元素的个数：";

    std::cin >> size;  // 输入数组大小

    int *arr = new int[size];  // 动态分配数组

    std::cout << "\n请输入未排序的元素：";

    for (int i = 0; i < size; ++i) {
        std::cout << "\n";
        std::cin >> arr[i];  // 输入数组元素
    }

    // 执行SlowSort排序算法
    SlowSort(arr, 0, size - 1);

    std::cout << "排序后的数组：\n";

    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";  // 输出排序后的数组
    }

    delete[] arr;  // 释放动态分配的内存
    return 0;
}
