#include <iostream>

int main() {
    int size = 10;  // 初始化数组大小
    int* array = new int[size];  // 动态分配内存

    // 输入部分
    std::cout << "\n你想输入多少个数字到未排序数组中：";
    std::cin >> size;  // 输入数组大小
    std::cout << "\n请输入未排序数组的数字：";
    for (int i = 0; i < size; i++) {
        std::cin >> array[i];  // 输入数组元素
    }

    // 排序部分 (Shell排序)
    for (int i = size / 2; i > 0; i = i / 2) {  // 逐步缩小步长
        for (int j = i; j < size; j++) {  // 从步长位置开始遍历数组
            for (int k = j - i; k >= 0; k = k - i) {  // 在当前步长范围内进行插入排序
                if (array[k] < array[k + i]) {  // 如果当前元素小于下一个元素，跳出循环
                    break;
                } else {
                    // 交换当前元素和下一个元素
                    int temp = array[k + i];
                    array[k + i] = array[k];
                    array[k] = temp;
                }
            }
        }
    }

    // 输出部分
    std::cout << "\n排序后的数组：";
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << "\t";  // 输出排序后的数组
    }

    delete[] array;  // 释放动态分配的内存
    return 0;
}
