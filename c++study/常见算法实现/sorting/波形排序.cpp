/**
 * \addtogroup sorting 排序算法
 * @{
 * \file
 * \brief [Wiggle Sort 算法](https://leetcode.com/problems/wiggle-sort-ii/) 实现
 *
 * \author [Roshan Kanwar](http://github.com/roshan0708)
 *
 * \details
 * Wiggle Sort 算法将数组排序成波形形式。
 * 如果数组 `arr[0..n-1]` 排序成波形数组，
 * 那么满足以下条件：
 * arr[0] >= arr[1] <= arr[2] >= arr[3] <= arr[4] >= ……
 *
 * \example
 * 输入 arr = [1,1,5,6,1,4]，经过波形排序后数组为 [1,1,6,1,5,4]
 * 输入 arr = [2,8,9,1,7]，经过波形排序后数组为 [8,2,9,1,7]
 */

#include <algorithm>
#include <cassert>
#include <ctime>
#include <iostream>  /// 用于输入输出操作
#include <vector>

/**
 * @namespace sorting
 * @brief 排序算法
 */
namespace sorting {
/**
 * @namespace wiggle_sort
 * @brief 实现 [Wiggle Sort](https://leetcode.com/problems/wiggle-sort-ii/) 算法的函数
 */
namespace wiggle_sort {

/**
 * @brief 函数用于将元素按波形形式排序
 * @details
 * 检查偶数索引的元素是否大于它们相邻的奇数索引元素。
 * 遍历所有偶数索引的元素。如果当前元素小于前一个奇数元素，则交换它们。
 * 如果当前元素小于下一个奇数元素，也交换它们。
 *
 * @param arr 输入的数组（未排序的元素）
 * @returns 排序后的波形数组
 */
template <typename T>  // 允许处理 int、double、float 等类型的向量
std::vector<T> wiggleSort(const std::vector<T> &arr) {
    uint32_t size = arr.size();

    std::vector<T> out(
        arr);  // 创建输入向量的副本，这样原始输入向量不会被修改，返回一个排序后的数组

    // 遍历所有偶数索引的元素
    for (int i = 0; i < size; i += 2) {
        // 如果当前偶数索引元素小于前一个奇数索引元素，交换它们
        if (i > 0 && out[i - 1] > out[i]) {
            std::swap(out[i], out[i - 1]);  // 交换两个值
        }

        // 如果当前偶数索引元素小于下一个奇数索引元素，交换它们
        if (i < size - 1 && out[i] < out[i + 1]) {
            std::swap(out[i], out[i + 1]);  // 交换两个值
        }
    }

    return out;  // 返回波形排序后的数组
}
}  // namespace wiggle_sort
}  // namespace sorting

/**
 * @brief 用于打印元素的辅助函数
 * 打印通过波形排序算法排序后的数组
 *
 * @param arr 排序后的数组
 */
template <typename T>
static void displayElements(const std::vector<T> &arr) {
    uint32_t size = arr.size();

    std::cout << "排序后的元素如下: ";

    std::cout << "[";

    for (int i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i != size - 1) {
            std::cout << ", ";
        }
    }

    std::cout << "]" << std::endl;
}

/**
 * 测试函数
 * @returns void
 */
static void test() {
    std::srand(std::time(nullptr));  // 初始化随机数生成器

    std::vector<float> data1(100);
    for (auto &d : data1) {  // 生成介于 -5.0 和 4.99 之间的随机数
        d = float(std::rand() % 1000 - 500) / 100.f;
    }

    // 使用波形排序算法对数据进行排序
    std::vector<float> sorted = sorting::wiggle_sort::wiggleSort<float>(data1);

    // 打印排序后的数组
    displayElements(sorted);

    // 验证波形排序是否正确
    for (uint32_t j = 0; j < data1.size(); j += 2) {
        assert(data1[j] <= data1[j + 1] &&  // 检查当前元素小于等于下一个元素
               data1[j + 1] >= data1[j + 2]);  // 检查下一个元素大于等于下下一个元素
    }

    std::cout << "测试通过\n";
}

/** 主函数 */
int main() {
    test();  // 运行测试
    return 0;
}

/** @} */
