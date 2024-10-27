/**
 * @file
 * @brief 实现 [数组左旋转](https://www.javatpoint.com/program-to-left-rotate-the-elements-of-an-array) 算法。
 * @details 将数组左移涉及到移动数组的每个元素，使其占据一个特定的移位值之前的位置。此实现使用结果向量，并且不改变输入。
 * @author [Alvin](https://github.com/polarvoid)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于 std::vector

/**
 * @namespace operations_on_datastructures
 * @brief 数据结构上的操作
 */
namespace operations_on_datastructures {

/**
 * @brief 顺序打印向量的值，最后以换行符结束。
 * @param array 要打印的数组的引用
 * @returns void
 */
void print(const std::vector<int32_t> &array) {
    for (int32_t i : array) {
        std::cout << i << " ";  /// 打印数组中的每个值
    }
    std::cout << "\n";  /// 打印换行符
}

/**
 * @brief 将给定向量向左移动指定的移位量，并返回一个包含结果的新向量。原始向量不会被改变。
 * @details 通过创建一个新向量并将值从移位索引添加到末尾，然后附加向量开头的其余元素，来移动向量的值。
 * @param array 对输入 std::vector 的引用
 * @param shift 要向左移动的数量
 * @returns 包含移位值的 std::vector
 */
std::vector<int32_t> shift_left(const std::vector<int32_t> &array,
                                size_t shift) {
    if (array.size() <= shift) {
        return {};  ///< 如果移位无效，则返回空数组
    }
    std::vector<int32_t> res(array.size());  ///< 结果数组
    for (size_t i = shift; i < array.size(); i++) {
        res[i - shift] = array[i];  ///< 将移位索引后的值添加到结果数组
    }
    for (size_t i = 0; i < shift; i++) {
        res[array.size() - shift + i] =
            array[i];  ///< 将开头的值添加到结果数组
    }
    return res;
}

}  // namespace operations_on_datastructures

/**
 * @namespace tests
 * @brief 测试用例以检查两个数组的并集。
 */
namespace tests {
using operations_on_datastructures::print;
using operations_on_datastructures::shift_left;

/**
 * @brief 测试简单案例
 * @returns void
 */
void test1() {
    std::cout << "测试案例 1\n";
    std::cout << "初始化的数组 = {1, 2, 3, 4, 5}\n";
    std::cout << "预期结果: {3, 4, 5, 1, 2}\n";
    std::vector<int32_t> arr = {1, 2, 3, 4, 5};
    std::vector<int32_t> res = shift_left(arr, 2);
    std::vector<int32_t> expected = {3, 4, 5, 1, 2};
    assert(res == expected);
    print(res);  ///< 应该打印 3 4 5 1 2
    std::cout << "测试通过!\n\n";
}

/**
 * @brief 测试空向量
 * @returns void
 */
void test2() {
    std::cout << "测试案例 2\n";
    std::cout << "初始化的数组 = {}\n";
    std::cout << "预期结果: {}\n";
    std::vector<int32_t> arr = {};
    std::vector<int32_t> res = shift_left(arr, 2);
    std::vector<int32_t> expected = {};
    assert(res == expected);
    print(res);  ///< 应该打印空行
    std::cout << "测试通过!\n\n";
}

/**
 * @brief 测试无效的移位值
 * @returns void
 */
void test3() {
    std::cout << "测试案例 3\n";
    std::cout << "初始化的数组 = {1, 2, 3, 4, 5}\n";
    std::cout << "预期结果: {}\n";
    std::vector<int32_t> arr = {1, 2, 3, 4, 5};
    std::vector<int32_t> res = shift_left(arr, 7);  ///< 7 > 5
    std::vector<int32_t> expected = {};
    assert(res == expected);
    print(res);  ///< 应该打印空行
    std::cout << "测试通过!\n\n";
}

/**
 * @brief 测试非常大的输入
 * @returns void
 */
void test4() {
    std::cout << "测试案例 4\n";
    std::cout << "初始化的数组 = {2, 4, ..., 420}\n";
    std::cout << "预期结果: {4, 6, ..., 420, 2}\n";
    std::vector<int32_t> arr;
    for (int i = 1; i <= 210; i++) {
        arr.push_back(i * 2);
    }
    print(arr);
    std::vector<int32_t> res = shift_left(arr, 1);
    std::vector<int32_t> expected;
    for (int i = 1; i < 210; i++) {
        expected.push_back(arr[i]);
    }
    expected.push_back(2);
    assert(res == expected);
    print(res);  ///< 应该打印 {4, 6, ..., 420, 2}
    std::cout << "测试通过!\n\n";
}

/**
 * @brief 测试零移位
 * @returns void
 */
void test5() {
    std::cout << "测试案例 5\n";
    std::cout << "初始化的数组 = {1, 2, 3, 4, 5}\n";
    std::cout << "预期结果: {1, 2, 3, 4, 5}\n";
    std::vector<int32_t> arr = {1, 2, 3, 4, 5};
    std::vector<int32_t> res = shift_left(arr, 0);
    assert(res == arr);
    print(res);  ///< 应该打印 1 2 3 4 5
    std::cout << "测试通过!\n\n";
}
}  // namespace tests

/**
 * @brief 测试 shift_left() 函数的正确性
 * @returns void
 */
static void test() {
    tests::test1();
    tests::test2();
    tests::test3();
    tests::test4();
    tests::test5();
}

/**
 * @brief 主函数
 * @returns 0 退出时返回
 */
int main() {
    test();  // 运行自我测试实现
    return 0;
}
