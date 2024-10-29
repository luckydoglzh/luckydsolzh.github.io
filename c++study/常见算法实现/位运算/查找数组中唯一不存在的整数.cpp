/**
 * @file
 * @brief 实现寻找数组中唯一不重复的整数。[Single Number](https://leetcode.com/problems/single-number/)
 *
 * @details
 * 给定一个整数数组，其中所有数字均恰好出现两次，除了一个整数仅出现一次。
 * 找出这个不重复的整数。
 *
 * 最坏情况时间复杂度：O(n)
 * 空间复杂度：O(1)
 *
 * @author [Ravidev Pandey](https://github.com/literalEval)
 */

#include <cassert>   /// 用于 assert
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于存储数字

/**
 * @namespace bit_manipulation
 * @brief 位操作算法命名空间
 */
namespace bit_manipulation {
/**
 * @namespace find_non_repeating_integer
 * @brief 用于在重复整数的数组中寻找唯一不重复整数的函数。[Single Number](https://leetcode.com/problems/single-number/)
 */
namespace find_non_repeating_integer {
/**
 * @brief 实现寻找唯一不重复的整数的函数
 * @param nums 整数数组
 * @returns 返回仅出现一次的整数
 */
int64_t find_non_repeating_integer(const std::vector<int>& nums) {
    // 该算法基于异或（XOR）的性质。
    // 我们知道 'a' XOR 'a' 为 '0'，'0' XOR 'b' 为 b。
    // 使用这一特性，如果我们将数组中的所有元素进行异或操作，
    // 所有重复的元素会抵消为 '0'，最后剩下的就是唯一不重复的数。

    int _xor = 0;

    for (const int& num : nums) {
        _xor ^= num;
    }

    return _xor;
}
}  // namespace find_non_repeating_integer
}  // namespace bit_manipulation

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    // 测试用例

    std::vector<int> nums_one{1, 1, 2, 2, 4, 5, 5};  // 4 是唯一不重复的数字
    std::vector<int> nums_two{203, 3434, 4545, 3434, 4545};  // 203 是唯一不重复的数字
    std::vector<int> nums_three{90, 1, 3, 90, 3};  // 1 是唯一不重复的数字

    // 测试 1
    assert(bit_manipulation::find_non_repeating_integer::
               find_non_repeating_integer(nums_one) == 4);
    // 测试 2
    assert(bit_manipulation::find_non_repeating_integer::
               find_non_repeating_integer(nums_two) == 203);
    // 测试 3
    assert(bit_manipulation::find_non_repeating_integer::
               find_non_repeating_integer(nums_three) == 1);

    std::cout << "所有测试用例均成功通过！" << std::endl;
}

/**
 * @brief 主函数
 * @returns 程序正常结束时返回 0
 */
int main() {
    test();  // 运行自测实现
    return 0;
}
