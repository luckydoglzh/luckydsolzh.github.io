/**
 *
 * \file
 * \brief [插入排序算法](https://en.wikipedia.org/wiki/Insertion_sort)
 *
 * \details
 * 插入排序是一种简单的排序算法，它通过逐步构建最终排序的数组来实现排序。
 * 相比于堆排序、归并排序或快速排序等其他排序算法，它的效率较低。
 * 然而，它有几个优点：
 * 1. 实现简单
 * 2. 对于小规模数据，效率较高
 * 3. 比其他平方时间复杂度的算法（如选择排序或冒泡排序）更高效
 * 4. 它是稳定排序，即相等元素的相对顺序不会改变
 * 5. 插入排序是“在线”的，意味着它在接收到新的数据时可以排序数组或列表。
 *
 * 插入排序的基本思想与人们整理扑克牌时相似。
 * 算法的执行方式是：我们从头开始遍历数组，每当遇到一个不在正确位置的元素时，就把它放到已排序的部分中的正确位置。
 *
 * 示例执行步骤：
 * 1. 假设最初我们有
 * \f{bmatrix}{4 &3 &2 &5 &1\f}
 * 2. 我们从4开始遍历，到达3时发现它不在正确的位置，于是将3放到正确位置，数组变为
 * \f{bmatrix}{3 &4 &2 &5 &1\f}
 * 3. 接下来，我们看到2也不在正确位置，于是将2放到正确的位置，数组变为
 * \f{bmatrix}{2 &3 &4 &5 &1\f}
 * 4. 对5不做任何处理，继续向前，选择1，它也不在正确位置，于是将1放到正确位置，最终数组变为
 * \f{bmatrix}{1 &2 &3 &4 &5\f}
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/** \namespace sorting
 * \brief 排序算法
 */
namespace sorting {
/** \brief
 * 插入排序函数
 *
 * @tparam T 数组的类型
 * @param [in,out] arr 要排序的数组
 * @param n 数组的大小
 */
template <typename T>
void insertionSort(T *arr, int n) {
    for (int i = 1; i < n; i++) {  // 从数组的第二个元素开始
        T temp = arr[i];            // 取出当前元素
        int j = i - 1;
        // 将当前元素与前面已排序的元素逐一比较并插入到正确的位置
        while (j >= 0 && temp < arr[j]) {
            arr[j + 1] = arr[j];  // 移动元素
            j--;
        }
        arr[j + 1] = temp;  // 插入元素到正确的位置
    }
}

/** 插入排序函数（针对std::vector）
 *
 * @tparam T 数组的类型
 * @param [in,out] arr 指向要排序数组的指针
 */
template <typename T>
void insertionSort(std::vector<T> *arr) {
    size_t n = arr->size();  // 获取数组大小

    for (size_t i = 1; i < n; i++) {  // 从第二个元素开始
        T temp = arr->at(i);           // 获取当前元素
        int32_t j = i - 1;
        // 将当前元素与前面已排序的元素逐一比较并插入到正确的位置
        while (j >= 0 && temp < arr->at(j)) {
            arr->at(j + 1) = arr->at(j);  // 移动元素
            j--;
        }
        arr->at(j + 1) = temp;  // 插入元素到正确的位置
    }
}

}  // namespace sorting

/**
 * @brief 创建随机数组的辅助函数
 *
 * @tparam T 数组的类型
 * @param arr 要填充的数组（必须预先分配内存）
 * @param N 数组元素的个数
 */
template <typename T>
static void create_random_array(T *arr, int N) {
    while (N--) {
        double r = (std::rand() % 10000 - 5000) / 100.f;  // 生成[-50.0, 50.0]之间的随机数
        arr[N] = static_cast<T>(r);
    }
}

/** 测试算法的测试用例 */
void tests() {
    int arr1[10] = {78, 34, 35, 6, 34, 56, 3, 56, 2, 4};
    std::cout << "Test 1... ";
    sorting::insertionSort(arr1, 10);  // 对数组进行排序
    assert(std::is_sorted(arr1, arr1 + 10));  // 确保数组已排序
    std::cout << "passed" << std::endl;

    int arr2[5] = {5, -3, 7, -2, 1};
    std::cout << "Test 2... ";
    sorting::insertionSort(arr2, 5);
    assert(std::is_sorted(arr2, arr2 + 5));
    std::cout << "passed" << std::endl;

    float arr3[5] = {5.6, -3.1, -3.0, -2.1, 1.8};
    std::cout << "Test 3... ";
    sorting::insertionSort(arr3, 5);
    assert(std::is_sorted(arr3, arr3 + 5));
    std::cout << "passed" << std::endl;

    std::vector<float> arr4({5.6, -3.1, -3.0, -2.1, 1.8});
    std::cout << "Test 4... ";
    sorting::insertionSort(&arr4);
    assert(std::is_sorted(std::begin(arr4), std::end(arr4)));
    std::cout << "passed" << std::endl;

    int arr5[50];
    std::cout << "Test 5... ";
    create_random_array(arr5, 50);  // 创建一个随机数组
    sorting::insertionSort(arr5, 50);  // 排序
    assert(std::is_sorted(arr5, arr5 + 50));
    std::cout << "passed" << std::endl;

    float arr6[50];
    std::cout << "Test 6... ";
    create_random_array(arr6, 50);
    sorting::insertionSort(arr6, 50);
    assert(std::is_sorted(arr6, arr6 + 50));
    std::cout << "passed" << std::endl;
}

/** 主函数 */
int main() {
    /// 执行预定义的测试以验证算法的正确性
    tests();

    /// 用户交互部分
    size_t n;
    std::cout << "请输入数组的长度（输入0退出）：";
    std::cin >> n;
    if (n == 0) {
        return 0;
    }

    int *arr = new int[n];  // 动态分配数组
    std::cout << "请输入" << n << "个未排序的数字：";

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];  // 输入数组元素
    }

    sorting::insertionSort(arr, n);  // 排序

    std::cout << "\n排序后的数组：";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";  // 打印排序后的数组
    }

    std::cout << std::endl;
    delete[] arr;  // 释放动态分配的内存
    return 0;
}
