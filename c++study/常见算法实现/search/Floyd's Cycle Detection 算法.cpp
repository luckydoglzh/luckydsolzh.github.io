/**
 * @file
 * @brief 实现 [Floyd's Cycle Detection](https://en.wikipedia.org/wiki/Cycle_detection) 算法
 * @details
 * 给定一个包含 n + 1 个整数的数组，其中每个整数的范围是 [1, n]（包括 1 和 n）。如果输入数组中仅有一个重复的数字，
 * 则此算法返回重复的数字，且空间复杂度为 O(1)，时间复杂度小于 O(n^2)，并且不修改原始数组，否则返回 -1。
 * @author [Swastika Gupta](https://github.com/Swastyy)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于 std::vector 类

/**
 * @namespace search
 * @brief 搜索算法
 */
namespace search {
/**
 * @namespace cycle_detection
 * @brief Floyd's Cycle Detection 算法的函数
 */
namespace cycle_detection {
/**
 * @brief 主要函数实现搜索算法
 * @tparam T 数组的类型
 * @param in_arr 输入数组
 * @param n 数组大小
 * @returns 返回重复的数字
 */
template <typename T>
int32_t duplicateNumber(const std::vector<T> &in_arr, const uint32_t &n) {
    // 如果数组大小为 0 或 1，无法找到重复数字，返回 -1
    if (n == 0 || n == 1) {
        return -1;
    }

    uint32_t tortoise = in_arr[0];  // tortoise 用于进行长跳跃
    uint32_t hare = in_arr[0];      // hare 用于进行短跳跃

    // 查找相遇点，tortoise 每次跳跃一个元素，hare 每次跳跃两个元素
    do {
        tortoise = in_arr[tortoise];  // tortoise 跳跃一个元素
        hare = in_arr[in_arr[hare]];  // hare 跳跃两个元素
    } while (tortoise != hare);  // 直到 tortoise 和 hare 相遇

    tortoise = in_arr[0];  // 将 tortoise 移动到数组的开始位置

    // 再次循环寻找重复的数字
    while (tortoise != hare) {
        tortoise = in_arr[tortoise];  // tortoise 跳跃一个元素
        hare = in_arr[hare];          // hare 跳跃一个元素
    }

    // 返回相遇点的数字，这就是重复的数字
    return tortoise;
}
}  // namespace cycle_detection
}  // namespace search

/**
 * @brief 自测试实现
 * @returns void
 */
static void test() {
    // 第一个测试
    // [3, 4, 8, 5, 9, 1, 2, 6, 7, 4] 返回 4
    std::vector<uint32_t> array1 = {3, 4, 8, 5, 9, 1, 2, 6, 7, 4};
    std::cout << "Test 1... ";
    assert(search::cycle_detection::duplicateNumber(array1, array1.size()) ==
           4);  // 这里的重复数字是 4
    std::cout << "passed" << std::endl;

    // 第二个测试
    // [1, 2, 3, 4, 2] 返回 2
    std::vector<uint32_t> array2 = {1, 2, 3, 4, 2};
    std::cout << "Test 2... ";
    assert(search::cycle_detection::duplicateNumber(array2, array2.size()) ==
           2);  // 这里的重复数字是 2
    std::cout << "passed" << std::endl;

    // 第三个测试
    // [] 返回 -1
    std::vector<uint32_t> array3 = {};
    std::cout << "Test 3... ";
    assert(search::cycle_detection::duplicateNumber(array3, array3.size()) ==
           -1);  // 由于输入数组为空，没有重复数字
    std::cout << "passed" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0
 */
int main() {
    test();  // 运行自测试
    return 0;
}
