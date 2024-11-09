/**
 * @file
 * @brief 实现两个已排序数组的交集算法
 * @details 数组的交集是两个数组中所有共同元素的集合。此实现使用已排序的数组，采用合适的算法来返回结果数组（向量）。
 * @see union_of_two_arrays.cpp
 * @author [Alvin](https://github.com/polarvoid)
 */

#include <algorithm>  /// 用于 std::sort 排序
#include <cassert>    /// 用于断言
#include <iostream>   /// 用于输入输出操作
#include <vector>     /// 用于 std::vector 容器

/**
 * @namespace operations_on_datastructures
 * @brief 数据结构相关操作
 */
namespace operations_on_datastructures {

/**
 * @brief 按顺序打印一个整数向量的值，以空格分隔，并以换行符结束
 * @param array 要打印的向量引用
 * @returns void
 */
void print(const std::vector<int32_t> &array) {
    for (int32_t i : array) {
        std::cout << i << " ";  /// 打印数组中的每个值
    }
    std::cout << "\n";  /// 打印换行符
}

/**
 * @brief 获取两个已排序数组的交集，返回交集的向量
 * @details 使用一种算法，比较两个数组的元素，并根据元素的大小来递增索引。如果元素相同，就将元素添加到结果数组中。
 * @param first 一个已排序的整数向量
 * @param second 另一个已排序的整数向量
 * @returns 返回两个数组的交集，按升序排列
 */
std::vector<int32_t> get_intersection(const std::vector<int32_t> &first,
                                      const std::vector<int32_t> &second) {
    std::vector<int32_t> res;         ///< 存储交集结果的向量
    size_t f_index = 0;               ///< 第一个数组的索引
    size_t s_index = 0;               ///< 第二个数组的索引
    size_t f_length = first.size();   ///< 第一个数组的长度
    size_t s_length = second.size();  ///< 第二个数组的长度

    while (f_index < f_length && s_index < s_length) {
        if (first[f_index] < second[s_index]) {
            f_index++;  ///< 如果第一个数组的元素较小，递增第一个数组的索引
        } else if (first[f_index] > second[s_index]) {
            s_index++;  ///< 如果第二个数组的元素较小，递增第二个数组的索引
        } else {
            if ((res.size() == 0) || (first[f_index] != res.back())) {
                res.push_back(first[f_index]);  ///< 如果该元素没有出现在结果中，就加入结果
            }
            f_index++;  ///< 递增第一个数组的索引
            s_index++;  ///< 同时递增第二个数组的索引
        }
    }
    return res;
}

}  // namespace operations_on_datastructures

/**
 * @namespace tests
 * @brief 测试两个数组交集的测试用例
 */
namespace tests {
using operations_on_datastructures::get_intersection;
using operations_on_datastructures::print;

/**
 * @brief 测试用例1：边缘情况（两个空数组）
 * @returns void
 */
void test1() {
    std::cout << "测试用例 1\n";
    std::cout << "初始化 a = {} b = {}\n";
    std::cout << "预期结果: {}\n";
    std::vector<int32_t> a = {};
    std::vector<int32_t> b = {};
    std::vector<int32_t> result = get_intersection(a, b);
    assert(result == a);  ///< 验证结果为空
    print(result);        ///< 只会打印换行符
    std::cout << "测试通过!\n\n";
}

/**
 * @brief 测试用例2：边缘情况（一个空数组）
 * @returns void
 */
void test2() {
    std::cout << "测试用例 2\n";
    std::cout << "初始化 a = {} b = {2, 3}\n";
    std::cout << "预期结果: {}\n";
    std::vector<int32_t> a = {};
    std::vector<int32_t> b = {2, 3};
    std::vector<int32_t> result = get_intersection(a, b);
    assert(result == a);  ///< 验证结果与 a 相同
    print(result);        ///< 只会打印换行符
    std::cout << "测试通过!\n\n";
}

/**
 * @brief 测试用例3：简单测试用例
 * @returns void
 */
void test3() {
    std::cout << "测试用例 3\n";
    std::cout << "初始化 a = {4, 6} b = {3, 6}\n";
    std::cout << "预期结果: {6}\n";
    std::vector<int32_t> a = {4, 6};
    std::vector<int32_t> b = {3, 6};
    std::vector<int32_t> result = get_intersection(a, b);
    std::vector<int32_t> expected = {6};
    assert(result == expected);  ///< 验证结果正确
    print(result);               ///< 应该打印 6
    std::cout << "测试通过!\n\n";
}

/**
 * @brief 测试用例4：带有重复值的测试用例
 * @returns void
 */
void test4() {
    std::cout << "测试用例 4\n";
    std::cout << "初始化 a = {4, 6, 6, 6} b = {2, 4, 4, 6}\n";
    std::cout << "预期结果: {4, 6}\n";
    std::vector<int32_t> a = {4, 6, 6, 6};
    std::vector<int32_t> b = {2, 4, 4, 6};
    std::vector<int32_t> result = get_intersection(a, b);
    std::vector<int32_t> expected = {4, 6};
    assert(result == expected);  ///< 验证结果正确
    print(result);               ///< 应该打印 4 6
    std::cout << "测试通过!\n\n";
}

/**
 * @brief 测试用例5：复杂的测试用例
 * @returns void
 */
void test5() {
    std::cout << "测试用例 5\n";
    std::cout << "初始化 a = {1, 2, 3, 4, 6, 7, 9} b = {2, 3, 4, 5}\n";
    std::cout << "预期结果: {2, 3, 4}\n";
    std::vector<int32_t> a = {1, 2, 3, 4, 6, 7, 9};
    std::vector<int32_t> b = {2, 3, 4, 5};
    std::vector<int32_t> result = get_intersection(a, b);
    std::vector<int32_t> expected = {2, 3, 4};
    assert(result == expected);  ///< 验证结果正确
    print(result);               ///< 应该打印 2 3 4
    std::cout << "测试通过!\n\n";
}

/**
 * @brief 测试用例6：使用 std::sort 排序的数组
 * @returns void
 */
void test6() {
    std::cout << "测试用例 6\n";
    std::cout << "初始化 a = {1, 3, 3, 2, 5, 9, 4, 7, 3, 2} ";
    std::cout << "b = {11, 3, 7, 8, 6}\n";
    std::cout << "预期结果: {3, 7}\n";
    std::vector<int32_t> a = {1, 3, 3, 2, 5, 9, 4, 7, 3, 2};
    std::vector<int32_t> b = {11, 3, 7, 8, 6};
    std::sort(a.begin(), a.end());  ///< 对数组 a 进行排序
    std::sort(b.begin(), b.end());  ///< 对数组 b 进行排序
    std::vector<int32_t> result = get_intersection(a, b);
    std::vector<int32_t> expected = {3, 7};
    assert(result == expected);  ///< 验证结果正确
    print(result);               ///< 应该打印 3 7
    std::cout << "测试通过!\n\n";
}
}  // namespace tests

/**
 * @brief 用于测试 get_intersection() 函数的正确性
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
 * @returns 0 表示退出
 */
int main() {
    test();  // 执行自我测试
    return 0;
}
