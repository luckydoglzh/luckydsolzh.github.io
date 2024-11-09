/**
 * \file
 * \brief [二分插入排序算法
 * (插入排序)](https://en.wikipedia.org/wiki/Insertion_sort)
 *
 * \details
 * 当比较操作的代价超过交换操作时，比如使用引用存储的字符串键，或者像人类交互（选择并排显示的一个）等情况，
 * 使用二分插入排序可能会带来更好的性能。二分插入排序通过二分查找来确定正确的插入位置，因此在最坏的情况下，
 * 每次插入操作的比较次数为 ⌈log2 n⌉。当每个元素都进行搜索和插入时，算法的时间复杂度为 O(n log n)。
 * 然而，整个算法的时间复杂度平均仍然是 O(n²)，因为每次插入都需要交换位置。然而，二分插入排序有几个优点：
 * 1. 易于实现
 * 2. 对于小数据集非常高效
 * 3. 比其他二次复杂度的算法（如选择排序或冒泡排序）更高效
 * 4. 在比较操作代价较高时尤其有效
 * 5. 它是稳定的，即不会改变具有相同键的元素的相对顺序
 * 6. 它可以在接收数据时对数组或列表进行排序
 *
 * 示例执行步骤：
 * 1. 假设初始数组为
 * \f{bmatrix}{40 &30 &20 &50 &10\f}
 * 2. 我们从40开始遍历，直到到达10。遇到30时，发现它的位置不对，于是我们将30插入到正确的位置，
 * 数组变为 \f{bmatrix}{30 &40 &20 &50 &10\f}
 * 3. 在下一次迭代中，我们处理20，发现它也不在正确位置，于是将其插入到正确的排序位置，
 * 数组变为 \f{bmatrix}{20 &30 &40 &50 &10\f}
 * 4. 我们不对50做任何操作，继续下一次迭代，处理10，发现它的位置不对，并将其插入到正确的位置，
 * 最终数组变为 \f{bmatrix}{10 &20 &30 &40 &50\f}
 */

#include <algorithm>  /// 用于算法函数
#include <cassert>    /// 用于断言
#include <iostream>   /// 用于 IO 操作
#include <vector>     /// 用于操作向量

/**
 * \namespace sorting
 * @brief 排序算法
 */
namespace sorting {

/**
 * \brief 二分查找函数，用于查找元素的合适位置。
 * \tparam T 泛型数据类型。
 * \param arr 要搜索的实际向量。
 * \param val 需要找到合适位置的值。
 * \param low 搜索范围的下界。
 * \param high 搜索范围的上界。
 * \returns 返回值 val 在 arr 中的合适位置索引。
 */
template <class T>
int64_t binary_search(std::vector<T> &arr, T val, int64_t low, int64_t high) {
    if (high <= low) {
        // 如果 val 大于 arr[low]，则返回 low + 1，否则返回 low
        return (val > arr[low]) ? (low + 1) : low;
    }
    int64_t mid = low + (high - low) / 2;  // 计算中间位置
    if (arr[mid] > val) {
        // 如果中间值大于 val，继续在左侧递归查找
        return binary_search(arr, val, low, mid - 1);
    } else if (arr[mid] < val) {
        // 如果中间值小于 val，继续在右侧递归查找
        return binary_search(arr, val, mid + 1, high);
    } else {
        // 如果值相等，返回 mid + 1
        return mid + 1;
    }
}

/**
 * \brief 插入排序函数，使用二分查找来找到合适的插入位置。
 * \tparam T 泛型数据类型。
 * \param arr 要排序的实际向量。
 * \returns 无返回值。
 */
template <typename T>
void insertionSort_binsrch(std::vector<T> &arr) {
    int64_t n = arr.size();  // 获取向量的大小

    // 从第二个元素开始遍历
    for (int64_t i = 1; i < n; i++) {
        T key = arr[i];  // 当前要插入的元素
        int64_t j = i - 1;
        // 使用二分查找找到当前元素的插入位置
        int64_t loc = sorting::binary_search(arr, key, 0, j);
        // 移动元素以腾出位置
        while (j >= loc) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;  // 插入元素到正确的位置
    }
}
}  // namespace sorting

/**
 * @brief 自我测试实现
 * @returns 无返回值
 */
static void test() {
    /* 第一个测试：
       输入 [5, -3, -1, -2, 7] 输出 [-3, -2, -1, 5, 7] */
    std::vector<int64_t> arr1({5, -3, -1, -2, 7});
    std::cout << "1st test... ";
    sorting::insertionSort_binsrch(arr1);
    assert(std::is_sorted(std::begin(arr1), std::end(arr1)));  // 验证数组是否已排序
    std::cout << "passed" << std::endl;

    /* 第二个测试：
       输入 [12, 26, 15, 91, 32, 54, 41] 输出 [12, 15, 26, 32, 41, 54, 91] */
    std::vector<int64_t> arr2({12, 26, 15, 91, 32, 54, 41});
    std::cout << "2nd test... ";
    sorting::insertionSort_binsrch(arr2);
    assert(std::is_sorted(std::begin(arr2), std::end(arr2)));  // 验证数组是否已排序
    std::cout << "passed" << std::endl;

    /* 第三个测试：
       输入 [7.1, -2.5, -4.0, -2.1, 5.7] 输出 [-4.0, -2.5, -2.1, 5.7, 7.1] */
    std::vector<float> arr3({7.1, -2.5, -4.0, -2.1, 5.7});
    std::cout << "3rd test... ";
    sorting::insertionSort_binsrch(arr3);
    assert(std::is_sorted(std::begin(arr3), std::end(arr3)));  // 验证数组是否已排序
    std::cout << "passed" << std::endl;

    /* 第四个测试：
       输入 [12.8, -3.7, -20.7, -7.1, 2.2] 输出 [-20.7, -7.1, -3.7, 2.2, 12.8] */
    std::vector<float> arr4({12.8, -3.7, -20.7, -7.1, 2.2});
    std::cout << "4th test... ";
    sorting::insertionSort_binsrch(arr4);
    assert(std::is_sorted(std::begin(arr4), std::end(arr4)));  // 验证数组是否已排序
    std::cout << "passed" << std::endl;
}

/**
 * @brief 主函数
 * @return 0 作为程序退出的状态。
 */
int main() {
    test();  // 运行自我测试
    return 0;
}
