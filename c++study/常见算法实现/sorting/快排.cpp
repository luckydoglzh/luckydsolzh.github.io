/**
 * @file
 * @brief 实现细节
 * @details 快速排序 3 基于荷兰国旗问题算法（Dutch National Flag Algorithm）。
 * 快速排序 3 和普通快速排序的主要区别在于 `partition3` 函数，
 * 在 `quick_sort_partition3` 中，我们将数组分成三个部分。
 * 快速排序 3 在某些情况下比普通的快速排序更快。
 * @author immortal-j
 * @author [Krishna Vedala](https://github.com/kvedala)
 */
#include <algorithm>
#include <cassert>
#include <ctime>
#include <iostream>
#include <vector>

namespace {
/**
 * 操作符：用于打印数组
 * @param out std::ostream 对象，用于输出
 * @param arr 要打印的数组
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        out << arr[i];
        if (i < arr.size() - 1) {
            out << ", ";
        }
    }
    return out;
}

}  // namespace

/**
 * @namespace sorting
 * @brief 排序算法
 */
namespace sorting {
namespace {  // 使用匿名命名空间以防止 partition3 函数对外暴露

/** 该函数将 `arr[]` 分成三个部分：
 * 1. \f$arr[l\ldots i]\f$ 包含所有小于基准值的元素
 * 2. \f$arr[(i+1)\ldots (j-1)]\f$ 包含所有等于基准值的元素
 * 3. \f$arr[j\ldots r]\f$ 包含所有大于基准值的元素
 * @tparam T 数组中的数据类型
 * @param [in,out] arr 要分区的数组
 * @param [in] low 分区的下限
 * @param [in] high 分区的上限
 * @param [out] i 更新后的下限
 * @param [out] j 更新后的上限
 */
template <typename T>
void partition3(std::vector<T> *arr, int32_t low, int32_t high, int32_t *i,
                int32_t *j) {
    // 处理只有两个元素的情况
    if (high - low <= 1) {
        if ((*arr)[high] < (*arr)[low]) {
            std::swap((*arr)[high], (*arr)[low]);
        }
        *i = low;
        *j = high;
        return;
    }

    int32_t mid = low;
    T pivot = (*arr)[high];  // 选择最右边的元素作为基准
    while (mid <= high) {
        if ((*arr)[mid] < pivot) {  // 当前元素小于基准
            std::swap((*arr)[low++], (*arr)[mid++]);
        } else if ((*arr)[mid] == pivot) {  // 当前元素等于基准
            mid++;
        } else if ((*arr)[mid] > pivot) {  // 当前元素大于基准
            std::swap((*arr)[mid], (*arr)[high--]);
        }
    }

    // 更新 i 和 j 的值
    *i = low - 1;
    *j = mid;  // 或者是 high-1
}
}  // namespace

/** 基于 3 路分区的快速排序算法。此函数接受数组指针并修改原始数组
 * @tparam T 数组中的数据类型
 * @param [in,out] arr 要排序的数组
 * @param [in] low 分区的下限
 * @param [in] high 分区的上限
 */
template <typename T>
void quicksort(std::vector<T> *arr, int32_t low, int32_t high) {
    if (low >= high) {  // 1 个或 0 个元素
        return;
    }

    int32_t i = 0, j = 0;

    // 传递 i 和 j 引用
    partition3(arr, low, high, &i, &j);

    // 对两个子数组递归排序
    quicksort(arr, low, i);
    quicksort(arr, j, high);
}

/** 基于 3 路分区的快速排序算法。此函数通过值传递数组，并创建一个数组副本
 * 该副本会被排序并返回
 * @tparam T 数组中的数据类型
 * @param [in] arr 要排序的数组
 * @param [in] low 分区的下限
 * @param [in] high 分区的上限
 * @returns 排序后的数组副本
 */
template <typename T>
std::vector<T> quicksort(std::vector<T> arr, int32_t low, int32_t high) {
    if (low >= high) {  // 1 个或 0 个元素
        return arr;
    }

    int32_t i = 0, j = 0;

    // 传递 i 和 j 引用
    partition3(&arr, low, high, &i, &j);

    // 对两个子数组递归排序
    quicksort(&arr, low, i);
    quicksort(&arr, j, high);

    return arr;
}
}  // namespace sorting

/** 测试整数类型数组 */
static void test_int() {
    std::cout << "\n测试整数类型数组\n";

    for (int num_tests = 1; num_tests < 21; num_tests++) {
        size_t size = std::rand() % 500;
        std::vector<int> arr(size);
        for (auto &a : arr) {
            a = std::rand() % 500 - 250;  // 生成 -250 到 249 之间的随机数
        }

        std::cout << "测试 " << num_tests << "\t 数组大小:" << size << "\t ";
        std::vector<int> sorted = sorting::quicksort(arr, 0, int32_t(size) - 1);
        if (size < 20) {
            std::cout << "\t 排序后的数组:\n\t";
            std::cout << sorted << "\n";
        }
        assert(std::is_sorted(std::begin(sorted), std::end(sorted)));  // 验证数组是否已排序
        std::cout << "\t 通过\n";
}

/** 测试双精度类型数组 */
static void test_double() {
    std::cout << "\n测试双精度类型数组\n";
    for (int num_tests = 1; num_tests < 21; num_tests++) {
        size_t size = std::rand() % 500;
        std::vector<double> arr(size);
        for (auto &a : arr) {
            a = double(std::rand() % 500) - 250.f;  // 生成 -250 到 249 之间的随机数
            a /= 100.f;  // 转换为 -2.5 到 2.49 之间的浮点数
        }

        std::cout << "测试 " << num_tests << "\t 数组大小:" << size << "\t ";
        std::vector<double> sorted = sorting::quicksort(arr, 0, int32_t(size) - 1);
        if (size < 20) {
            std::cout << "\t 排序后的数组:\n\t";
            std::cout << sorted << "\n";
        }
        assert(std::is_sorted(std::begin(sorted), std::end(sorted)));  // 验证数组是否已排序
        std::cout << "\t 通过\n";
}

/** 驱动程序 */
int main() {
    std::srand(std::time(nullptr));  // 设置随机数种子
    test_int();  // 测试整数类型数组
    test_double();  // 测试双精度类型数组
    return 0;  // 程序结束
}
