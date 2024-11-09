/**
 * @file
 * @brief 实现 [Gnome 排序](https://en.wikipedia.org/wiki/Gnome_sort) 算法
 * @author [beqakd](https://github.com/beqakd)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @details
 * Gnome 排序算法虽然不是最优的排序算法，但它是一个常用的排序算法。
 * 该算法通过反复检查数组中的相邻元素对，如果它们已经按正确的顺序排列，就检查下一个元素对，否则交换它们。
 * 这个过程不断重复，直到没有交换发生为止，这表明数组已经按升序排列。
 * 
 * 该算法的时间复杂度是 \f$O(n^2)\f$，在某些情况下它的时间复杂度可以是 \f$O(n)\f$。
 */

#include <algorithm>  // 引入 std::swap
#include <array>      // 引入 std::array
#include <cassert>    // 引入 assert 用于断言
#include <iostream>   // 引入输入输出操作

/**
 * @namespace sorting
 * 排序算法
 */
namespace sorting {
/**
 * 该实现适用于 C 风格的数组输入，数组在原地修改。
 * @param [in,out] arr 要排序的数组。
 * @param size 数组的大小
 */
template <typename T>
void gnomeSort(T *arr, int size) {
    // 处理一些简单情况
    if (size <= 1) {
        return;
    }

    int index = 0;  // 初始化变量
    while (index < size) {
        // 检查是否需要交换
        if ((index == 0) || (arr[index] >= arr[index - 1])) {
            index++;  // 如果当前元素不小于前一个元素，继续移动
        } else {
            std::swap(arr[index], arr[index - 1]);  // 交换元素
            index--;  // 交换后需要检查前一个元素
        }
    }
}

/**
 * 该实现适用于 C++ 风格的数组输入。函数的参数是按值传递，因此会创建数组的副本，
 * 并对副本进行修改，最后返回排序后的数组。
 * @tparam T 数组元素的数据类型
 * @tparam size 数组的大小
 * @param [in] arr 要排序的数组。
 * @return 排序后的数组
 */
template <typename T, size_t size>
std::array<T, size> gnomeSort(std::array<T, size> arr) {
    // 处理一些简单情况
    if (size <= 1) {
        return arr;
    }

    int index = 0;  // 初始化循环索引
    while (index < size) {
        // 检查是否需要交换
        if ((index == 0) || (arr[index] >= arr[index - 1])) {
            index++;  // 如果当前元素不小于前一个元素，继续移动
        } else {
            std::swap(arr[index], arr[index - 1]);  // 交换元素
            index--;  // 交换后需要检查前一个元素
        }
    }
    return arr;  // 返回排序后的数组
}
}  // namespace sorting

/**
 * 测试函数
 */
static void test() {
    // 示例 1：创建一个 int 数组
    std::cout << "Test 1 - C 风格数组排序...";
    const int size = 6;
    std::array<int, size> arr = {-22, 100, 150, 35, -10, 99};
    sorting::gnomeSort(arr.data(),
                       size);  // 将数组传递为 C 风格数组指针
    assert(std::is_sorted(std::begin(arr), std::end(arr)));  // 确认数组已排序
    std::cout << " Passed\n";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ", ";  // 打印排序后的数组
    }
    std::cout << std::endl;

    // 示例 2：创建一个 double 数组
    std::cout << "\nTest 2 - std::array 风格数组排序...";
    std::array<double, size> double_arr = {-100.2, 10.2, 20.0, 9.0, 7.5, 7.2};
    std::array<double, size> sorted_arr = sorting::gnomeSort(double_arr);
    assert(std::is_sorted(std::begin(sorted_arr), std::end(sorted_arr)));  // 确认数组已排序
    std::cout << " Passed\n";
    for (int i = 0; i < size; i++) {
        std::cout << double_arr[i] << ", ";  // 打印排序后的数组
    }
    std::cout << std::endl;

    // 示例 3：创建一个随机的 float 数组
    std::cout << "\nTest 3 - 200 个随机数排序...";
    const int size2 = 200;
    std::array<float, size2> rand_arr{};

    for (auto &a : rand_arr) {
        // 生成 -5.0 到 4.99 之间的随机数
        a = float(std::rand() % 1000 - 500) / 100.f;
    }

    std::array<float, size2> float_arr = sorting::gnomeSort(rand_arr);
    assert(std::is_sorted(std::begin(float_arr), std::end(float_arr)));  // 确认数组已排序
    std::cout << " Passed\n";
    // for (int i = 0; i < size; i++) std::cout << double_arr[i] << ", ";
    std::cout << std::endl;
}

/**
 * 主函数，展示排序方法
 */
int main() {
    test();  // 执行测试
    return 0;
}
