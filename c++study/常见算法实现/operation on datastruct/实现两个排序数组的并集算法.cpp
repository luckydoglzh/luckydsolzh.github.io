/**
 * @file
 * @brief 实现两个排序数组的并集算法
 * @details 两个数组的并集是第一个数组中所有唯一元素，和第二个数组中所有唯一元素的集合。本实现使用有序数组，并通过一种算法正确排序并返回结果作为新数组（向量）。
 * @see intersection_of_two_arrays.cpp
 * @author [Alvin](https://github.com/polarvoid)
 */

#include <algorithm>  /// 用于 std::sort
#include <cassert>    /// 用于 assert
#include <iostream>   /// 用于输入输出操作
#include <vector>     /// 用于 std::vector

/**
 * @namespace operations_on_datastructures
 * @brief 数据结构操作
 */
namespace operations_on_datastructures {

 /**
  * @brief 顺序打印向量的值，最后换行
  * @param array 引用，指向要打印的数组
  * @returns void
  */
void print(const std::vector<int32_t> &array) {
    for (int32_t i : array) {
        std::cout << i << " ";  /// 打印数组中的每个值
    }
    std::cout << "\n";  /// 打印换行
}

/**
 * @brief 获取两个排序数组的并集，并返回一个新向量
 * @details 使用一种算法，通过比较两个向量的元素，依次将较小的元素添加到结果数组，并递增相应数组的索引。如果一个数组到达末尾，另一个数组中的所有元素将继续添加到结果数组。
 * @param first 一个包含已排序整数值的 std::vector
 * @param second 一个包含已排序整数值的 std::vector
 * @returns 返回两个数组的并集，按升序排列的 std::vector
 */
std::vector<int32_t> get_union(const std::vector<int32_t> &first,
                               const std::vector<int32_t> &second) {
    std::vector<int32_t> res;         ///< 存放并集的向量
    size_t f_index = 0;               ///< 第一个数组的索引
    size_t s_index = 0;               ///< 第二个数组的索引
    size_t f_length = first.size();   ///< 第一个数组的长度
    size_t s_length = second.size();  ///< 第二个数组的长度
    int32_t next = 0;  ///< 存储下一个元素的值

    while (f_index < f_length && s_index < s_length) {
        if (first[f_index] < second[s_index]) {
            next = first[f_index];  ///< 从第一个数组中添加元素
            f_index++;              ///< 递增第一个数组的索引
        } else if (first[f_index] > second[s_index]) {
            next = second[s_index];  ///< 从第二个数组中添加元素
            s_index++;               ///< 递增第二个数组的索引
        } else {
            next = first[f_index];  ///< 如果两个元素相等，从任意一个数组中添加元素
            f_index++;              ///< 递增第一个数组的索引
            s_index++;              ///< 递增第二个数组的索引
        }
        if ((res.size() == 0) || (next != res.back())) {
            res.push_back(next);  ///< 如果元素是唯一的，则添加到结果数组
        }
    }
    while (f_index < f_length) {
        next = first[f_index];  ///< 添加第一个数组剩余的元素
        if ((res.size() == 0) || (next != res.back())) {
            res.push_back(next);  ///< 如果元素是唯一的，则添加到结果数组
        }
        f_index++;
    }
    while (s_index < s_length) {
        next = second[s_index];  ///< 添加第二个数组剩余的元素
        if ((res.size() == 0) || (next != res.back())) {
            res.push_back(next);  ///< 如果元素是唯一的，则添加到结果数组
        }
        s_index++;
    }
    return res;
}

}  // namespace operations_on_datastructures

/**
 * @namespace tests
 * @brief 测试用例，用于检查两个数组的并集
 */
namespace tests {
using operations_on_datastructures::get_union;
using operations_on_datastructures::print;
/**
 * @brief 测试边缘情况（两个空数组）
 * @returns void
 */
void test1() {
    std::cout << "测试案例 1\n";
    std::cout << "初始化 a = {} b = {}\n";
    std::cout << "预期结果: {}\n";
    std::vector<int32_t> a = {};
    std::vector<int32_t> b = {};
    std::vector<int32_t> result = get_union(a, b);
    assert(result == a);  ///< 检查结果是否为空
    print(result);        ///< 应该只打印换行
    std::cout << "测试通过!\n\n";
}
/**
 * @brief 测试边缘情况（一个空数组）
 * @returns void
 */
void test2() {
    std::cout << "测试案例 2\n";
    std::cout << "初始化 a = {} b = {2, 3}\n";
    std::cout << "预期结果: {2, 3}\n";
    std::vector<int32_t> a = {};
    std::vector<int32_t> b = {2, 3};
    std::vector<int32_t> result = get_union(a, b);
    assert(result == b);  ///< 检查结果是否与 b 相等
    print(result);        ///< 应该打印 2 3
    std::cout << "测试通过!\n\n";
}
/**
 * @brief 使用简单的测试用例检查正确功能
 * @returns void
 */
void test3() {
    std::cout << "测试案例 3\n";
    std::cout << "初始化 a = {4, 6} b = {2, 3}\n";
    std::cout << "预期结果: {2, 3, 4, 6}\n";
    std::vector<int32_t> a = {4, 6};
    std::vector<int32_t> b = {2, 3};
    std::vector<int32_t> result = get_union(a, b);
    std::vector<int32_t> expected = {2, 3, 4, 6};
    assert(result == expected);  ///< 检查结果是否正确
    print(result);               ///< 应该打印 2 3 4 6
    std::cout << "测试通过!\n\n";
}
/**
 * @brief 测试包含重复值的正确功能
 * @returns void
 */
void test4() {
    std::cout << "测试案例 4\n";
    std::cout << "初始化 a = {4, 6, 6, 7} b = {2, 3, 4}\n";
    std::cout << "预期结果: {2, 3, 4, 6, 7}\n";
    std::vector<int32_t> a = {4, 6, 6, 7};
    std::vector<int32_t> b = {2, 3, 4};
    std::vector<int32_t> result = get_union(a, b);
    std::vector<int32_t> expected = {2, 3, 4, 6, 7};
    assert(result == expected);  ///< 检查结果是否正确
    print(result);               ///< 应该打印 2 3 4 6 7
    std::cout << "测试通过!\n\n";
}
/**
 * @brief 测试较复杂的测试案例
 * @returns void
 */
void test5() {
    std::cout << "测试案例 5\n";
    std::cout << "初始化 a = {1, 4, 6, 7, 9} b = {2, 3, 5}\n";
    std::cout << "预期结果: {1, 2, 3, 4, 5, 6, 7, 9}\n";
    std::vector<int32_t> a = {1, 4, 6, 7, 9};
    std::vector<int32_t> b = {2, 3, 5};
    std::vector<int32_t> result = get_union(a, b);
    std::vector<int32_t> expected = {1, 2, 3, 4, 5, 6, 7, 9};
    assert(result == expected);  ///< 检查结果是否正确
    print(result);               ///< 应该打印 1 2 3 4 5 6 7 9
    std::cout << "测试通过!\n\n";
}
/**
 * @brief 测试排序后的数组的正确功能
 * @returns void
 */
void test6() {
    std::cout << "测试案例 6\n";
    std::cout << "初始化 a = {1, 3, 3, 2, 5, 9, 4, 3, 2} ";
    std::cout << "b = {11, 3, 7, 8, 6}\n";
    std::cout << "预期结果: {1, 2, 3, 4, 5, 6, 7, 8, 9, 11}\n";
    std::vector<int32_t> a = {1, 3, 3, 2, 5, 9, 4, 3, 2};
    std::vector<int32_t> b = {11, 3, 7, 8, 6};
    std::sort(a.begin(), a.end());  ///< 排序数组 a
    std::sort(b.begin(), b.end());  ///< 排序数组 b
    std::vector<int32_t> result = get_union(a, b);
    std::vector<int32_t> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
    assert(result == expected);  ///< 检查结果是否正确
    print(result);               ///< 应该打印 1 2 3 4 5 6 7 8 9 11
    std::cout << "测试通过!\n\n";
}
}  // namespace tests

/**
 * @brief 测试 get_union() 函数的正确性
 * @returns void
 */
static void test() {
    tests::test1();
    tests::test2();
    tests::test3();
    tests::test4();
    tests::test5();
    tests::test6();
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    test();  // 运行自测
    return 0;
}
