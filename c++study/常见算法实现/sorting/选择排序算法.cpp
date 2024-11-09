/******************************************************************************
 * @file
 * @brief 实现了使用交换操作的 [选择排序算法](https://en.wikipedia.org/wiki/Selection_sort)
 * @details
 * 选择排序算法将输入的向量分为两个部分：已排序的子向量（从左到右构建）和剩余的未排序部分。
 * 初始时，已排序的子向量为空，未排序的部分是整个输入向量。
 * 算法通过在未排序的部分中找到最小（或最大）元素，并将其与最左边的未排序元素交换，
 * 然后将未排序部分的边界向右移动一个元素来逐步排序。
 *
 * ### 实现
 *
 * 选择排序
 * 算法将输入向量分为两个部分：已排序的子向量从左到右构建。
 * 初始时，已排序的子向量为空，未排序的部分是整个输入向量。
 * 算法通过在未排序的部分中找到最小元素，并将其与最左边的未排序元素交换，
 * 然后将未排序部分的边界向右移动一个元素。
 *
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 * @author Unknown author
 *******************************************************************************/
#include <algorithm>  /// 用于 std::is_sorted
#include <cassert>    /// 用于 std::assert
#include <iostream>   /// 用于输入输出操作
#include <vector>     /// 用于 std::vector

/******************************************************************************
 * @namespace sorting
 * @brief 排序算法
 *******************************************************************************/
namespace sorting {
/******************************************************************************
 * @brief 选择排序的主函数实现
 * @param arr 需要排序的向量
 * @param len 向量的长度
 * @returns 返回排序后的向量
 *******************************************************************************/

std::vector<uint64_t> selectionSort(const std::vector<uint64_t> &arr,
                                    uint64_t len) {
    std::vector<uint64_t> array(
        arr.begin(),
        arr.end());  // 声明一个新的向量用于存储结果
    for (uint64_t it = 0; it < len; ++it) {
        uint64_t min = it;  // 初始化最小值为当前索引
        for (uint64_t it2 = it + 1; it2 < len; ++it2) {
            if (array[it2] < array[min]) {  // 找到比当前最小值更小的元素
                min = it2;  // 更新最小值的索引
            }
        }

        if (min != it) {  // 如果最小值的索引不等于当前索引，交换元素
            uint64_t tmp = array[min];
            array[min] = array[it];
            array[it] = tmp;
        }
    }

    return array;  // 返回排序后的向量
}
}  // namespace sorting

/*******************************************************************************
 * @brief 自测试用例实现
 * @returns void
 *******************************************************************************/
static void test() {
    // 测试用例 #1
    // [1, 0, 0, 1, 1, 0, 2, 1] 应该返回 [0, 0, 0, 1, 1, 1, 1, 2]
    std::vector<uint64_t> vector1 = {1, 0, 0, 1, 1, 0, 2, 1};
    uint64_t vector1size = vector1.size();
    std::cout << "1st test... ";
    std::vector<uint64_t> result_test1;
    result_test1 = sorting::selectionSort(vector1, vector1size);
    assert(std::is_sorted(result_test1.begin(), result_test1.end()));  // 检查排序是否正确
    std::cout << "Passed" << std::endl;

    // 测试用例 #2
    // [19, 22, 540, 241, 156, 140, 12, 1] 应该返回 [1, 12, 19, 22, 140, 156, 241, 540]
    std::vector<uint64_t> vector2 = {19, 22, 540, 241, 156, 140, 12, 1};
    uint64_t vector2size = vector2.size();
    std::cout << "2nd test... ";
    std::vector<uint64_t> result_test2;
    result_test2 = sorting::selectionSort(vector2, vector2size);
    assert(std::is_sorted(result_test2.begin(), result_test2.end()));  // 检查排序是否正确
    std::cout << "Passed" << std::endl;

    // 测试用例 #3
    // [11, 20, 30, 41, 15, 60, 82, 15] 应该返回 [11, 15, 15, 20, 30, 41, 60, 82]
    std::vector<uint64_t> vector3 = {11, 20, 30, 41, 15, 60, 82, 15};
    uint64_t vector3size = vector3.size();
    std::cout << "3rd test... ";
    std::vector<uint64_t> result_test3;
    result_test3 = sorting::selectionSort(vector3, vector3size);
    assert(std::is_sorted(result_test3.begin(), result_test3.end()));  // 检查排序是否正确
    std::cout << "Passed" << std::endl;

    // 测试用例 #4
    // [1, 9, 11, 546, 26, 65, 212, 14, -11] 应该返回 [-11, 1, 9, 11, 14, 26, 65, 212, 546]
    std::vector<uint64_t> vector4 = {1, 9, 11, 546, 26, 65, 212, 14, -11};
    uint64_t vector4size = vector2.size();
    std::cout << "4th test... ";
    std::vector<uint64_t> result_test4;
    result_test4 = sorting::selectionSort(vector4, vector4size);
    assert(std::is_sorted(result_test4.begin(), result_test4.end()));  // 检查排序是否正确
    std::cout << "Passed" << std::endl;
}

/*******************************************************************************
 * @brief 主函数
 * @returns 0 表示程序正常退出
 *******************************************************************************/
int main() {
    test();  // 运行自测试用例
    return 0;
}
