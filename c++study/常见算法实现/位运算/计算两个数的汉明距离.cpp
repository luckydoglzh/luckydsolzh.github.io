/**
 * @file
 * @brief 返回两个整数之间的[汉明距离](https://en.wikipedia.org/wiki/Hamming_distance)
 *
 * @details
 * 为了计算两个整数之间的汉明距离，我们可以对它们进行异或运算。
 * 在异或结果中，只有在两数的位不同时才会出现1，因此，返回结果中位为1的数量即可。
 *
 * @author [Ravishankar Joshi](https://github.com/ravibitsgoa)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作

/**
 * @namespace bit_manipulation
 * @brief 位操作算法命名空间
 */
namespace bit_manipulation {
/**
 * @namespace hamming_distance
 * @brief 汉明距离实现的函数命名空间
 */
namespace hamming_distance {
/**
 * 此函数返回给定数字中为1的位数。
 * @param value 要计算的数字
 * @returns 数字中位为1的数量
 */
uint64_t bitCount(uint64_t value) {
    uint64_t count = 0;
    while (value) {       // 直到所有位都为0
        if (value & 1) {  // 检查最低位
            count++;
        }
        value >>= 1;  // 移位，去掉最低位
    }
    return count;
}

/**
 * 此函数返回两个整数之间的汉明距离。
 * @param a 第一个整数
 * @param b 第二个整数
 * @returns 两个整数之间不同位的数量
 */
uint64_t hamming_distance(uint64_t a, uint64_t b) { return bitCount(a ^ b); }

/**
 * 此函数返回两个字符串之间的汉明距离。
 * @param a 第一个字符串
 * @param b 第二个字符串
 * @returns 两个字符串之间不同字符的数量
 */
uint64_t hamming_distance(const std::string& a, const std::string& b) {
    assert(a.size() == b.size());  // 确保字符串长度相同
    size_t n = a.size();
    uint64_t count = 0;
    for (size_t i = 0; i < n; i++) {
        count += (b[i] != a[i]);  // 比较每个字符是否相同
    }
    return count;
}
}  // namespace hamming_distance
}  // namespace bit_manipulation

/**
 * @brief 测试汉明距离函数
 * @returns void
 */
static void test() {
    // 测试整数汉明距离
    assert(bit_manipulation::hamming_distance::hamming_distance(11, 2) == 2);
    assert(bit_manipulation::hamming_distance::hamming_distance(2, 0) == 1);
    assert(bit_manipulation::hamming_distance::hamming_distance(11, 0) == 3);

    // 测试字符串汉明距离
    assert(bit_manipulation::hamming_distance::hamming_distance("1101", "1111") == 1);
    assert(bit_manipulation::hamming_distance::hamming_distance("1111", "1111") == 0);
    assert(bit_manipulation::hamming_distance::hamming_distance("0000", "1111") == 4);

    assert(bit_manipulation::hamming_distance::hamming_distance("alpha", "alphb") == 1);
    assert(bit_manipulation::hamming_distance::hamming_distance("abcd", "abcd") == 0);
    assert(bit_manipulation::hamming_distance::hamming_distance("dcba", "abcd") == 4);
}

/**
 * @brief 主函数
 * @returns 程序正常退出时返回0
 */
int main() {
    test();           // 执行测试用例
    uint64_t a = 11;  // 二进制表示为1011
    uint64_t b = 2;   // 二进制表示为0010

    std::cout << "汉明距离 between " << a << " 和 " << b << " 是 "
              << bit_manipulation::hamming_distance::hamming_distance(a, b)
              << std::endl;
}
