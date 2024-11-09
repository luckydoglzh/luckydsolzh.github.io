/**
 * @file
 * @brief 实现[数组右移算法](https://www.javatpoint.com/program-to-right-rotate-the-elements-of-an-array)
 * @details 右移数组涉及将数组的每个元素移动，使其占据一个特定的偏移位置。该实现使用一个结果向量，并不改变输入数组。
 * @see array_left_rotation.cpp
 * @author [Alvin](https://github.com/polarvoid)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于 std::vector

/**
 * @namespace operations_on_datastructures
 * @brief 数据结构操作
 */
namespace operations_on_datastructures {

 /**
  * @brief 打印数组中的值，并以换行符结束
  * @param array 引用数组要打印的内容
  * @returns void
  */
void print(const std::vector<int32_t> &array) {
    for (int32_t i : array) {
        std::cout << i << " ";  /// 打印数组中的每个值
    }
    std::cout << "\n";  /// 打印换行
}

/**
 * @brief 将给定的数组右移指定的次数，并返回一个新的数组。原数组不被改变。
 * @details 通过创建一个新的数组，并从偏移位置开始将值添加到末尾，然后再将其余元素添加到数组的开头，完成右移操作。
 * @param array 输入的 std::vector 数组
 * @param shift 右移的次数
 * @returns 右移后的数组
 */
std::vector<int32_t> shift_right(const std::vector<int32_t> &array,
                                 size_t shift) {
    if (array.size() <= shift) {
        return {};  ///< 如果偏移量无效，返回空数组
    }
    std::vector<int32_t> res(array.size());  ///< 结果数组
    for (size_t i = shift; i < array.size(); i++) {
        res[i] = array[i - shift];  ///< 将偏移后的元素放入结果数组
    }
    for (size_t i = 0; i < shift; i++) {
        res[i] = array[array.size() - shift + i];  ///< 将数组开头的元素移动到末尾
    }
    return res;
}

}  // namespace operations_on_datastructures

/**
 * @namespace tests
 * @brief 测试用例，检查两个数组的并集
 */
namespace tests {
using operations_on_datastructures::print;
using operations_on_datastructures::shift_right;
/**
 * @brief 测试一个简单的情况
 * @returns void
 */
void test1() {
    std::cout << "测试用例 1\n";
    std::cout << "初始化的数组 arr = {1, 2, 3, 4, 5}\n";
    std::cout << "期望结果: {4, 5, 1, 2, 3}\n";
    std::vector<int32_t> arr = {1, 2, 3, 4, 5};
    std::vector<int32_t> res = shift_right(arr, 2);  // 右移2位
    std::vector<int32_t> expected = {4, 5, 1, 2, 3};
    assert(res == expected);  // 断言结果与期望相符
    print(res);  ///< 应该打印 4 5 1 2 3
    std::cout << "测试通过！\n\n";
}

/**
 * @brief 测试一个空数组
 * @returns void
 */
void test2() {
    std::cout << "测试用例 2\n";
    std::cout << "初始化的数组 arr = {}\n";
    std::cout << "期望结果: {}\n";
    std::vector<int32_t> arr = {};
    std::vector<int32_t> res = shift_right(arr, 2);  // 右移2位
    std::vector<int32_t> expected = {};
    assert(res == expected);  // 断言结果与期望相符
    print(res);  ///< 应该打印空行
    std::cout << "测试通过！\n\n";
}

/**
 * @brief 测试一个无效的右移值
 * @returns void
 */
void test3() {
    std::cout << "测试用例 3\n";
    std::cout << "初始化的数组 arr = {1, 2, 3, 4, 5}\n";
    std::cout << "期望结果: {}\n";
    std::vector<int32_t> arr = {1, 2, 3, 4, 5};
    std::vector<int32_t> res = shift_right(arr, 7);  ///< 7 > 5，偏移无效
    std::vector<int32_t> expected = {};
    assert(res == expected);  // 断言结果与期望相符
    print(res);  ///< 应该打印空行
    std::cout << "测试通过！\n\n";
}

/**
 * @brief 测试一个非常大的输入
 * @returns void
 */
void test4() {
    std::cout << "测试用例 4\n";
    std::cout << "初始化的数组 arr = {2, 4, ..., 420}\n";
    std::cout << "期望结果: {420, 2, 4, ..., 418}\n";
    std::vector<int32_t> arr;
    for (int i = 1; i <= 210; i++) {
        arr.push_back(i * 2);  // 填充数组
    }
    print(arr);  // 打印初始化的数组
    std::vector<int32_t> res = shift_right(arr, 1);  // 右移1位
    std::vector<int32_t> expected;
    expected.push_back(420);  // 将最后一个元素移到最前面
    for (int i = 0; i < 209; i++) {
        expected.push_back(arr[i]);  // 将原数组的其余元素复制到新数组
    }
    assert(res == expected);  // 断言结果与期望相符
    print(res);  ///< 应该打印 {420, 2, 4, ..., 418}
    std::cout << "测试通过！\n\n";
}

/**
 * @brief 测试零偏移量的情况
 * @returns void
 */
void test5() {
    std::cout << "测试用例 5\n";
    std::cout << "初始化的数组 arr = {1, 2, 3, 4, 5}\n";
    std::cout << "期望结果: {1, 2, 3, 4, 5}\n";
    std::vector<int32_t> arr = {1, 2, 3, 4, 5};
    std::vector<int32_t> res = shift_right(arr, 0);  // 偏移量为0，不做改变
    assert(res == arr);  // 断言结果与原数组相同
    print(res);  ///< 应该打印 1 2 3 4 5
    std::cout << "测试通过！\n\n";
}
}  // namespace tests

/**
 * @brief 用于测试 shift_right() 函数的正确性
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
 * @returns 0 正常退出
 */
int main() {
    test();  // 执行自测
    return 0;  // 程序正常退出
}
