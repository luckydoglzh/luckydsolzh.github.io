/**
 * @file
 * @brief 使用 [Merge Sort](https://en.wikipedia.org/wiki/Merge_sort) 算法计算数组中的逆序对
 *
 * @details
 * 使用归并排序计算数组中的逆序对数量。
 * 逆序对的数量有助于确定数组与升序排列的接近程度。
 *
 * 如果两个元素 a[i] 和 a[j] 满足 `a[i] > a[j]` 且 `i < j`，则它们构成一个逆序对。
 *
 * 时间复杂度 --> `O(n.log n)`
 * 空间复杂度 --> `O(n)`；额外的数组 `temp[1..n]`
 *
 * ### 算法
 *
 *   1. 算法与归并排序类似，将数组分成两个相等或几乎相等的部分，直到达到基准情况。
 *   2. 创建 `merge` 函数，在合并两个数组时统计逆序对的数量，创建两个索引 i 和 j，i 是左半部分的索引，j 是右半部分的索引。
 *      如果 `a[i]` 大于 `a[j]`，则有 `(mid - i)` 个逆序对。因为左右子数组已排序，所以左子数组中剩余的所有元素（`a[i+1], a[i+2], ... a[mid]`）都会大于 `a[j]`。
 *   3. 创建递归函数来将数组分为两部分，通过将左半部分、右半部分以及合并时的逆序对数量相加来得出答案。
 *   4. 递归的基准情况是当给定部分的数组只包含一个元素时。
 *   5. 输出结果。
 *
 * @author [Rakshit Raj](https://github.com/rakshitraj)
 */
#include <cassert>   /// 用于assert验证
#include <cstdint>   /// 用于定义数据类型 uint64_t
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于std::vector

/**
 * @namespace sorting
 * @brief 排序算法
 */
namespace sorting {
/**
 * @namespace inversion
 * @brief 使用归并排序算法计算逆序对的函数
 */
namespace inversion {

// 使用的函数 --->
// int mergeSort(int* arr, int* temp, int left, int right);
// int merge(int* arr, int* temp, int left, int mid, int right);
// int countInversion(int* arr, const int size);
// void show(int* arr, const int size);

/**
 * @brief 合并两个子数组的函数
 *
 * @details
 * merge() 函数从 mergeSort() 中调用，用于合并排序后的两个子数组，
 * 同时在合并过程中统计逆序对的数量并返回。
 *
 * @param arr    输入数组，即std::vector的数据成员
 * @param temp   用于存储合并结果的临时数组
 * @param left   数组的下界和左半部分的下界
 * @param mid    中点，左半部分的上界，`mid + 1` 为右半部分的下界
 * @param right  数组的上界和右半部分的上界
 * @returns 合并过程中发现的逆序对数量
 */
template <typename T>
uint32_t merge(T* arr, T* temp, uint32_t left, uint32_t mid, uint32_t right) {
    uint32_t i = left;       /* i --> 左子数组的索引 */
    uint32_t j = mid + 1;    /* j --> 右子数组的索引 */
    uint32_t k = left;       /* k --> 结果数组temp的索引 */
    uint32_t inv_count = 0;  // 逆序对计数

    while ((i <= mid) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];  // 将较小的元素放入临时数组
        } else {
            temp[k++] = arr[j++];  // 如果右子数组的元素小于左子数组的元素，放入临时数组并增加逆序对的数量
            inv_count += (mid - i + 1);  // 每次右子数组的元素小于左子数组时，都会增加 (mid - i + 1) 个逆序对
        }
    }

    // 将左子数组剩余的元素添加到temp数组
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    // 将右子数组剩余的元素添加到temp数组
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // 将合并结果从temp数组拷贝回arr数组
    for (k = left; k <= right; k++) {
        arr[k] = temp[k];
    }

    return inv_count;  // 返回在合并过程中找到的逆序对数量
}

/**
 * @brief 实现归并排序并在合并时统计逆序对
 *
 * @details
 * mergeSort() 函数实现了归并排序，是一种分治算法，它将输入数组分成两半，
 * 并对每个子数组递归调用自己，然后调用merge()函数来合并两个子数组。
 *
 * @param arr   - 待排序的数组
 * @param temp  - 合并后的临时数组
 * @param left  - 数组的下界
 * @param right - 数组的上界
 * @returns 数组中的逆序对数量
 */
template <typename T>
uint32_t mergeSort(T* arr, T* temp, uint32_t left, uint32_t right) {
    uint32_t mid = 0, inv_count = 0;
    if (right > left) {
        // 计算中点，分割数组
        mid = (right + left) / 2;
        // 递归计算左子数组的逆序对数量
        inv_count += mergeSort(arr, temp, left, mid);  // 左子数组
        // 递归计算右子数组的逆序对数量
        inv_count += mergeSort(arr, temp, mid + 1, right);  // 右子数组

        // 在合并时统计逆序对数量
        inv_count += merge(arr, temp, left, mid, right);
    }
    return inv_count;  // 返回逆序对的总数
}

/**
 * @brief 函数countInversion()返回输入数组中的逆序对数量
 *
 * @details
 * 排序数组的逆序对数量为0，
 * 一个长度为n的数组完全按非升序排列时，逆序对数量为n(n-1)/2，
 * 因为每一对元素都构成一个逆序对。
 *
 * @param arr   - 输入的数组，数据成员为std::vector<int>
 * @param size  - 数组中的元素数量
 * @returns 输入数组中的逆序对数量，同时将数组排序
 */
template <class T>
uint32_t countInversion(T* arr, const uint32_t size) {
    std::vector<T> temp;
    temp.reserve(size);
    temp.assign(size, 0);
    return mergeSort(arr, temp.data(), 0, size - 1);  // 调用mergeSort来统计逆序对数量
}

/**
 * @brief 打印数组的实用函数
 * @param arr[]   - 要打印的数组
 * @param size    - 数组的大小
 * @returns void
 *
 */
template <typename T>
void show(T* arr, const uint32_t array_size) {
    std::cout << "打印数组: \n";
    for (uint32_t i = 0; i < array_size; i++) {
        std::cout << " " << arr[i];
    }
    std::cout << "\n";
}

}  // namespace inversion
}  // namespace sorting

/**
 * @brief 测试实现
 * @returns void
 */
static void test() {
    // 测试1
    std::vector<uint64_t> arr1 = {
        100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84,
        83,  82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67,
        66,  65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50,
        49,  48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33,
        32,  31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,
        15,  14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
    };
    const auto size1 = arr1.size();
    const auto inv_count1 = sorting::inversion::countInversion(arr1.data(), size1);
    std::cout << "逆序对数量: " << inv_count1 << std::endl;
    sorting::inversion::show(arr1.data(), size1);
    std::cout << "\n\n";

    // 测试2
    std::vector<uint64_t> arr2 = { 1, 2, 3, 4, 5 };
    const auto size2 = arr2.size();
    const auto inv_count2 = sorting::inversion::countInversion(arr2.data(), size2);
    std::cout << "逆序对数量: " << inv_count2 << std::endl;
    sorting::inversion::show(arr2.data(), size2);
    std::cout << "\n\n";
}

int main() {
    test();  // 执行测试
    return 0;
}
