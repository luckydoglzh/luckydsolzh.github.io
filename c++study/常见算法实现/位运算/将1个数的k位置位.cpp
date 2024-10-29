/**
 * @file
 * @brief 实现[从右侧设置N的二进制表示中K位](https://practice.geeksforgeeks.org/problems/set-kth-bit3724/1/)。
 *
 * @details
 * 给定一个数字N和一个值K。从右侧开始，在N的二进制表示中设置K位。最低有效位（或最后一位）的位置为0，倒数第二位为1，依此类推。
 *
 * 一个二进制数由两位组成：0 和 1。数字1在计算机术语中称为“置位”。
 * 最坏情况下的时间复杂度：O(1)
 * 空间复杂度：O(1)
 *
 * @author [Aman Raj](https://github.com/aman2000raj)
 */

#include <cassert>   /// 引入断言库
#include <iostream>  /// 引入输入输出库

/**
 * @namespace bit_manipulation
 * @brief 位操作算法
 */
namespace bit_manipulation {
/**
 * @namespace setKthBit
 * @brief [从右侧设置N的二进制表示中K位](https://practice.geeksforgeeks.org/problems/set-kth-bit3724/1/) 的实现函数
 */
namespace set_kth_bit {
/**
 * @brief 设置K位的主函数
 * @param N 要设置K位的数字
 * @param k 要设置的位的位置
 * @returns 返回在N中设置K位后的整数
 */
std::uint64_t setKthBit(std::int64_t N,
                        std::int64_t k) {  // 使用int64_t以避免溢出

    int pos = 1 << k;  // "pos"变量用于在k位置上存储1，其他位为0。
                       // 在数字'N'的二进制表示中。

    return N | pos;  // 通过与pos和N进行按位或操作，设置N在k位置的位。
}
}  // namespace set_kth_bit
}  // namespace bit_manipulation

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    // n = 10, k = 2 返回14
    assert(bit_manipulation::set_kth_bit::setKthBit(10, 2) == 14);
    // n = 25, k = 1 返回27
    assert(bit_manipulation::set_kth_bit::setKthBit(25, 1) == 27);
    // n = 400001, k = 5 返回400033
    assert(bit_manipulation::set_kth_bit::setKthBit(400001, 5) == 400033);
    // n = 123, k = 3 返回123
    assert(bit_manipulation::set_kth_bit::setKthBit(123, 3) == 123);

    std::cout << "所有测试用例成功通过！" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    test();  // 运行自测实现
    return 0;
}
