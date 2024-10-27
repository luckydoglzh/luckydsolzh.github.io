/**
 * @file
 * @brief 实现计算[将数字A转换为B所需翻转的位数]
 * (https://www.geeksforgeeks.org/count-number-of-bits-to-be-flipped-to-convert-a-to-b/)。
 *
 * @details
 * 给定两个整数A和B，计算将A转换为B所需翻转的位数。
 *
 * 示例:
 *
 * A  = 01010 B  = 10100
 * 可以看到，需要翻转A中的位以得到B的结果是01010。
 * 如果翻转这些位，就得到B，即10100。
 *
 * 最坏情况下时间复杂度: O(log n)
 * 空间复杂度: O(1)
 * @author [Yash Raj Singh](https://github.com/yashrajyash)
 */
#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作
/**
 * @namespace bit_manipulation
 * @brief 位操作算法
 */
namespace bit_manipulation {
/**
 * @namespace count_bits_flip
 * @brief [计数翻转位数](https://www.geeksforgeeks.org/count-set-bits-in-an-integer/)
 * 的实现函数
 */
namespace count_bits_flip {
/**
 * @brief 主要函数实现将A转换为B所需翻转的位数
 * @param A 给定的数字，需要翻转该数字的位以得到B
 * @param B 目标数字
 * @returns 转换A为B所需翻转的位数
 */
std::uint64_t countBitsFlip(
    std::int64_t A,
    std::int64_t B) {  // 使用int64_t避免溢出

    int count =
        0;  // "count"变量用于统计将A的位翻转成B所需的次数
    A = A ^ B;  // XOR操作计算出A和B不同的位
    while (A) {
        A = A & (A - 1);  // 每次消去最低位的1
        count++;
    }
    return count;
}
}  // namespace count_bits_flip
}  // namespace bit_manipulation

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    // A = 10, B = 20 应返回 4
    assert(bit_manipulation::count_bits_flip::countBitsFlip(10, 20) == 4);
    // A = 20, B = 25 应返回 3
    assert(bit_manipulation::count_bits_flip::countBitsFlip(20, 25) == 3);
    // A = 7, B = 10 应返回 3
    assert(bit_manipulation::count_bits_flip::countBitsFlip(7, 10) == 3);
    // A = 17, B = 25 应返回 1
    assert(bit_manipulation::count_bits_flip::countBitsFlip(17, 25) == 1);
    // A = 11, B = 8 应返回 2
    assert(bit_manipulation::count_bits_flip::countBitsFlip(11, 8) == 2);
    // A = 21, B = 22 应返回 2
    assert(bit_manipulation::count_bits_flip::countBitsFlip(21, 22) == 2);
    // A = 7, B = 786 应返回 5
    assert(bit_manipulation::count_bits_flip::countBitsFlip(7, 786) == 5);
    std::cout << "所有测试用例均通过!" << std::endl;
}
/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    test();  // 运行自测实现
    return 0;
}
