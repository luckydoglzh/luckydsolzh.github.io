/* C++ 实现 奇偶排序（Odd-Even Sort） */

#include <iostream>
#include <vector>

using namespace std;

// 奇偶排序算法的实现
void oddEven(vector<int> &arr, int size) {
    bool sorted = false;
    
    // 当数组未排序完成时，继续循环
    while (!sorted) {
        sorted = true;
        
        // 进行奇数索引位置的元素比较和交换
        for (int i = 1; i < size - 1; i += 2)  // 奇数位置
        {
            if (arr[i] > arr[i + 1]) {  // 如果当前元素大于下一个元素
                swap(arr[i], arr[i + 1]);  // 交换元素
                sorted = false;  // 设置为未排序，继续进行下一轮
            }
        }

        // 进行偶数索引位置的元素比较和交换
        for (int i = 0; i < size - 1; i += 2)  // 偶数位置
        {
            if (arr[i] > arr[i + 1]) {  // 如果当前元素大于下一个元素
                swap(arr[i], arr[i + 1]);  // 交换元素
                sorted = false;  // 设置为未排序，继续进行下一轮
            }
        }
    }
}

// 输出排序后的数组
void show(vector<int> A, int size) {
    int i;
    for (i = 0; i < size; i++) cout << A[i] << "\n";  // 输出每个元素
}

int main() {
    int size, temp;
    
    // 输入数组的元素个数
    cout << "\n请输入元素个数: ";
    cin >> size;

    vector<int> arr;

    // 输入未排序的元素
    cout << "\n请输入未排序的元素: \n";

    for (int i = 0; i < size; ++i) {
        cin >> temp;
        arr.push_back(temp);  // 将输入的元素添加到数组中
    }

    // 调用奇偶排序算法
    oddEven(arr, size);

    // 输出排序后的数组
    cout << "排序后的数组:\n";
    show(arr, size);

    return 0;
}
