#include <algorithm>
#include <array>
#include <cassert>
#include <ctime>
#include <iostream>
#include <memory>

/**
 * \namespace sorting
 * \brief 排序算法的命名空间
 */
namespace sorting {
/** 
 * \namespace merge_insertion
 * \brief 结合了插入排序和归并排序的排序算法
 */
namespace merge_insertion {

/**
 * @brief 插入排序算法
 * @see insertion_sort.cpp
 * 
 * 当数据窗口较小（小于阈值）时，使用插入排序进行排序。
 * 
 * @tparam T 数组的数据类型
 * @tparam N 数组的大小
 * @param A 指向数组的指针
 * @param start 排序窗口的起始索引
 * @param end 排序窗口的结束索引
 */
template <typename T, size_t N>
static void InsertionSort(std::array<T, N> *A, size_t start, size_t end) {
    size_t i = 0, j = 0;
    T *ptr = A->data();  // 获取数组的指针

    // 遍历窗口中的每个元素
    for (i = start; i < end; i++) {
        T temp = ptr[i];  // 临时存储当前元素
        j = i;
        // 插入排序的核心：将当前元素插入到已排序部分的正确位置
        while (j > start && temp < ptr[j - 1]) {
            ptr[j] = ptr[j - 1];  // 移动元素
            j--;  // 向前移动
        }
        ptr[j] = temp;  // 将当前元素插入到正确的位置
    }
}

/**
 * @brief 执行数组合并操作
 * 
 * 通过合并操作将左右两部分已排序的数据合并为一个有序的数组。
 * 
 * @tparam T 数组的数据类型
 * @tparam N 数组的大小
 * @param A 指向数组的指针
 * @param min 排序窗口的最小索引
 * @param max 排序窗口的最大索引
 * @param mid 排序窗口的中间索引
 */
template <typename T, size_t N>
static void merge(std::array<T, N> *array, size_t min, size_t max, size_t mid) {
    size_t firstIndex = min;
    size_t secondIndex = mid + 1;

    auto ptr = array->data();
    std::array<T, N + 1> tempArray{0};  // 临时数组用于存储合并后的结果

    // 合并左右两部分数据
    for (size_t index = min; index <= max; index++) {
        // 如果左侧部分元素存在且小于右侧部分的元素
        if (firstIndex <= mid &&
            (secondIndex > max || ptr[firstIndex] <= ptr[secondIndex])) {
            tempArray[index] = ptr[firstIndex];
            firstIndex++;
        } else {
            tempArray[index] = ptr[secondIndex];
            secondIndex++;
        }
    }

    // 将合并后的结果复制回原数组
    memcpy(ptr + min, tempArray.data() + min, (max - min) * sizeof(T));
}

/**
 * @brief 结合了插入排序和归并排序的最终算法
 * 
 * 如果数据窗口的大小小于指定的阈值，则使用插入排序，否则使用归并排序递归地对数组进行排序。
 * 
 * @tparam T 数组的数据类型
 * @tparam N 数组的大小
 * @param A 指向数组的指针
 * @param min 排序窗口的最小索引
 * @param max 排序窗口的最大索引
 * @param threshold 窗口大小的阈值
 */
template <typename T, size_t N>
void mergeSort(std::array<T, N> *array, size_t min, size_t max,
               size_t threshold) {
    // 如果当前窗口大小小于等于阈值，则使用插入排序
    if ((max - min) <= threshold) {
        InsertionSort(array, min, max);
    } else {
        // 否则，递归地将数组分成两半并进行归并排序
        size_t mid = (max + min) >> 1;

        // 对左半部分进行归并排序
        mergeSort(array, min, mid, threshold);
        // 对右半部分进行归并排序
        mergeSort(array, mid, max, threshold);

        // 合并已排序的两部分
        merge(array, min, max, mid);
    }
}

}  // namespace merge_insertion
}  // namespace sorting

/**
 * @brief 测试排序算法的函数
 * 
 * 生成随机数组并测试排序算法是否能够正确地排序该数组。
 */
static void test() {
    constexpr size_t size = 30;
    std::array<int, size> array{0};

    // 生成随机数组并输出
    for (int i = 0; i < size; i++) {
        array[i] = std::rand() % 100 - 50;  // 生成范围在 [-50, 49] 之间的随机数
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    // 使用插入排序对数组进行排序
    sorting::merge_insertion::InsertionSort(&array, 0, size);
    // 也可以选择使用归并排序：sorting::merge_insertion::mergeSort(&array, 0, size, 10);

    // 输出排序后的数组
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    // 验证数组是否已经排序
    assert(std::is_sorted(std::begin(array), std::end(array)));
    std::cout << "测试通过\n";
}

/**
 * @brief 主函数
 * 
 * 程序的入口函数，调用 `test` 函数进行测试。
 * 
 * @return 0 表示程序正常退出
 */
int main() {
    std::srand(std::time(nullptr));  // 使用当前时间作为随机数种子
    test();  // 调用测试函数
    return 0;
}
