/**
 * @file
 * @brief 快速排序实现（参考 [Quick sort](https://en.wikipedia.org/wiki/Quicksort)）
 * @details
 *      快速排序是一种 [分治算法](https://en.wikipedia.org/wiki/Category:Divide-and-conquer_algorithms)，
 *      它选择一个元素作为基准，并围绕该基准对给定数组进行分区。快速排序有不同的版本，选择基准的方式也不同：
 *
 *      1. 总是选择第一个元素作为基准
 *      2. 总是选择最后一个元素作为基准（下面实现的方式）
 *      3. 随机选择一个元素作为基准
 *      4. 选择中位数作为基准
 *
 *      快速排序的关键过程是分区（partition）。分区的目标是，给定一个数组和一个元素 x（作为基准），
 *      将 x 放到其在排序数组中的正确位置，并将所有小于 x 的元素放在 x 的左边，所有大于 x 的元素放在右边。
 *      所有这些操作应当在线性时间内完成。
 *
 * @author [David Leal](https://github.com/Panquesito7)
 * @author [popoapp](https://github.com/popoapp)
 */

#include <algorithm>  /// 用于 std::is_sorted
#include <cassert>    /// 用于 std::assert
#include <ctime>      /// 用于 std::time
#include <iostream>   /// 用于输入输出操作
#include <vector>     /// 用于 std::vector

/**
 * @brief 排序算法
 * @namespace sorting
 */
namespace sorting {
/**
 * @namespace quick_sort
 * @brief 快速排序的实现函数
 */
namespace quick_sort {
/**
 * @brief 使用最后一个元素作为基准对数组进行排序
 * @details
 * 该函数选择数组的最后一个元素作为基准，将基准元素放置在正确的位置，并将所有小于基准的元素
 * 放在基准的左边，所有大于基准的元素放在基准的右边。
 * @tparam T 数组类型
 * @param arr 用户提供的数组
 * @param low 数组的起始索引
 * @param high 数组的结束索引
 * @returns 返回较小元素的索引
 */
template <typename T>
int partition(std::vector<T> *arr, const int &low, const int &high) {
    T pivot = (*arr)[high];  // 选择最后一个元素作为基准
    int i = (low - 1);       // 较小元素的索引

    for (int j = low; j < high; j++) {
        // 如果当前元素小于或等于基准
        if ((*arr)[j] <= pivot) {
            i++;  // 增加较小元素的索引
            std::swap((*arr)[i], (*arr)[j]);
        }
    }

    std::swap((*arr)[i + 1], (*arr)[high]);
    return (i + 1);
}

/**
 * @brief 实现快速排序的主函数（递归版本）
 * @details
 * 该函数通过递归调用对数组进行排序。它会将数组分成两部分：左部分小于基准，右部分大于基准，
 * 并对这两部分递归调用快速排序。
 * @tparam T 数组类型
 * @param arr 需要排序的数组
 * @param low 起始索引
 * @param high 结束索引
 */
template <typename T>
void quick_sort(std::vector<T> *arr, const int &low, const int &high) {
    if (low < high) {
        int p = partition(arr, low, high);  // 获取基准元素的位置

        // 对基准元素左边的子数组进行递归排序
        quick_sort(arr, low, p - 1);

        // 对基准元素右边的子数组进行递归排序
        quick_sort(arr, p + 1, high);
    }
}

/**
 * @brief 实现快速排序的主函数（返回排序后的数组）
 * @details
 * 该函数实现快速排序并返回排序后的数组。它与递归版本类似，但返回排序后的数组，而不是直接
 * 修改输入数组。
 * @tparam T 数组类型
 * @param arr 需要排序的数组
 * @param low 起始索引
 * @param high 结束索引
 * @returns 排序后的数组
 */
template <typename T>
std::vector<T> quick_sort(std::vector<T> arr, const int &low, const int &high) {
    if (low < high) {
        int p = partition(&arr, low, high);  // 获取基准元素的位置

        // 对基准元素左边的子数组进行递归排序
        quick_sort(&arr, low, p - 1);

        // 对基准元素右边的子数组进行递归排序
        quick_sort(&arr, p + 1, high);
    }
    return arr;  // 返回排序后的数组
}

/**
 * @brief 打印数组内容的辅助函数
 * @param arr 需要打印的数组
 * @param size 数组的大小
 * @returns void
 */
template <typename T>
void show(const std::vector<T> &arr, const int &size) {
    for (int i = 0; i < size; i++) std::cout << arr[i] << " ";
    std::cout << "\n";
}

}  // namespace quick_sort
}  // namespace sorting

/**
 * @brief 自我测试函数
 * @returns void
 */
static void tests() {
    // 第1个测试（普通数字）
    std::vector<uint64_t> arr = {5, 3, 8, 12, 14, 16, 28, 96, 2, 5977};
    std::vector<uint64_t> arr_sorted = sorting::quick_sort::quick_sort(
        arr, 0, int(std::end(arr) - std::begin(arr)) - 1);

    assert(std::is_sorted(std::begin(arr_sorted), std::end(arr_sorted)));
    std::cout << "\n第1个测试: 通过！\n";

    // 第2个测试（普通和负数）
    std::vector<int64_t> arr2 = {9,    15,   28,   96,  500, -4, -58,
                                 -977, -238, -800, -21, -53, -55};
    std::vector<int64_t> arr_sorted2 = sorting::quick_sort::quick_sort(
        arr2, 0, std::end(arr2) - std::begin(arr2));

    assert(std::is_sorted(std::begin(arr_sorted2), std::end(arr_sorted2)));
    std::cout << "第2个测试: 通过！\n";

    // 第3个测试（小数和普通数字）
    std::vector<double> arr3 = {29,  36,   1100, 0,      77,     1,
                                6.7, 8.97, 1.74, 950.10, -329.65};
    std::vector<double> arr_sorted3 = sorting::quick_sort::quick_sort(
        arr3, 0, int(std::end(arr3) - std::begin(arr3)) - 1);

    assert(std::is_sorted(std::begin(arr_sorted3), std::end(arr_sorted3)));
    std::cout << "第3个测试: 通过！\n";

    // 第4个测试（随机小数和负数）
    size_t size = std::rand() % 750 + 100;

    std::vector<float> arr4(size);
    for (uint64_t i = 0; i < size; i++) {
        arr4[i] = static_cast<float>(std::rand()) / 
                  static_cast<float>(RAND_MAX / 999.99 - 0.99) - 
                  250;
    }

    std::vector<float> arr4_sorted = sorting::quick_sort::quick_sort(
        arr4, 0, int(std::end(arr4) - std::begin(arr4)) - 1);
    assert(std::is_sorted(std::begin(arr4_sorted), std::end(arr4_sorted)));

    std::cout << "第4个测试: 通过！\n";

    // 打印所有排序后的数组
    std::cout << "\n\t打印所有排序后的数组：\t\n";

    std::cout << "第1个数组:\n";
    sorting::quick_sort::show(arr_sorted, std::end(arr) - std::begin(arr));
    std::cout << std::endl;
    std::cout << "第2个数组:\n";
    sorting::quick_sort::show(arr_sorted2, std::end(arr2) - std::begin(arr2));
    std::cout << std::endl;
    std::cout << "第3个数组:\n";
    sorting::quick_sort::show(arr_sorted3,
                              int(std::end(arr3) - std::begin(arr3)) - 1);
    std::cout << std::endl;
    std::cout << "开始：第4个数组:\n\n";
    sorting::quick_sort::show(
        arr4_sorted, int(std::end(arr4_sorted) - std::begin(arr4_sorted)) - 1);
    std::cout << "\n结束：第4个数组。\n";
}

/**
 * @brief 主函数
 * @returns 0 表示退出
 */
int main() {
    int choice = 0;

    std::cout << "\t可选模式\t\n\n";
    std::cout << "1. 自我测试模式\n2. 交互模式";

    std::cout << "\n请选择模式: ";
    std::cin >> choice;
    std::cout << "\n";

    while ((choice != 1) && (choice != 2)) {
        std::cout << "无效的选项。请选择有效模式: ";
        std::cin >> choice;
    }

    if (choice == 1) {
        std::srand(std::time(nullptr));
        tests();  // 运行自我测试
    } else if (choice == 2) {
        int size = 0;
        std::cout << "\n请输入元素个数: ";

        std::cin >> size;
        std::vector<float> arr(size);

        std::cout
            << "\n请输入未排序的元素（可以是负数/小数）：";

        for (int i = 0; i < size; ++i) {
            std::cout << "\n";
            std::cin >> arr[i];
        }
        sorting::quick_sort::quick_sort(&arr, 0, size - 1);
        std::cout << "\n排序后的数组：\n";
        sorting::quick_sort::show(arr, size);
    }
    return 0;
}
