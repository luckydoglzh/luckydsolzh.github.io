/**
 * @file
 * @brief [Stooge sort实现](https://en.wikipedia.org/wiki/Stooge_sort)的C++实现
 * @details
 * Stooge排序是一种递归排序算法。
 * 它将数组分成3个部分，并按以下步骤执行：
 *	- 排序数组的前两部分
 *	- 排序数组的后两部分
 *  - 再次排序数组的前两部分
 * 它的时间复杂度是 O(n^(log3/log1.5))，大约是 O(n^2.7)，
 * 使得它在平均情况下并不是最有效的排序算法。空间复杂度是O(1)。
 */

#include <vector> /// 用于 vector
#include <cassert> /// 用于 assert
#include <algorithm>  /// 用于 std::is_sorted
#include <iostream>   /// 用于输入输出操作

 /**
  * @brief stoogeSort() 函数用于排序数组。
  * @param L - 待排序的值的vector（整数类型），按升序排序
  * @param i - 数组的第一个索引（0）
  * @param j - 数组的最后一个索引（L.size() - 1）
  * @returns void
  */
void stoogeSort(std::vector<int>* L, size_t i, size_t j) {
    if (i >= j) { // 如果i大于等于j，说明已经排序完成，直接返回
        return;
    }
    // 如果L[i] > L[j]，则交换它们
    if ((*L)[i] > (*L)[j]) {
        std::swap((*L)[i], (*L)[j]);
    }
    // 如果当前范围超过1个元素，则继续分解并排序
    if (j - i > 1) {
        size_t third = (j - i + 1) / 3; // 计算每部分的大小，取数组长度的三分之一
        // 对前两部分进行排序
        stoogeSort(L, i, j - third);
        // 对后两部分进行排序
        stoogeSort(L, i + third, j);
        // 再次对前两部分进行排序
        stoogeSort(L, i, j - third);
    }
}

/**
 * @brief 测试排序算法，测试案例1
 * @returns void
 */
void test1() {
    std::vector<int> L = { 8, 9, 10, 4, 3, 5, 1 };
    stoogeSort(&L, 0, L.size() - 1); // 对数组进行排序
    assert(std::is_sorted(std::begin(L), std::end(L))); // 确保数组已排序
}

/**
 * @brief 测试排序算法，测试案例2（只有一个元素）
 * @returns void
 */
void test2() {
    std::vector<int> L = { -1 };
    stoogeSort(&L, 0, L.size() - 1); // 对数组进行排序
    assert(std::is_sorted(std::begin(L), std::end(L))); // 确保数组已排序
}

/**
 * @brief 测试排序算法，测试案例3（有重复元素）
 * @returns void
 */
void test3() {
    std::vector<int> L = { 1, 2, 5, 4, 1, 5 };
    stoogeSort(&L, 0, L.size() - 1); // 对数组进行排序
    assert(std::is_sorted(std::begin(L), std::end(L))); // 确保数组已排序
}

/**
 * @brief 主函数
 * @param argc 命令行参数数量（忽略）
 * @param argv 命令行参数数组（忽略）
 * @returns 0 表示程序正常退出
 */
int main() {
    test1(); // 执行测试案例1
    test2(); // 执行测试案例2
    test3(); // 执行测试案例3
    
    std::cout << "所有测试均已成功通过！\n"; // 输出测试通过信息
    return 0;
}
