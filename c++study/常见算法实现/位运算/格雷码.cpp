/**
 * @file
 * @brief 生成 n 位的[格雷码](https://en.wikipedia.org/wiki/Gray_code)的程序
 * 
 * @details
 * 格雷码是一种二进制编码系统，其中相邻的值只有一位不同。
 * 以下代码提供了一个生成指定位数格雷码的方法。
 */

#include <bitset>   /// 用于格雷码的二进制表示
#include <cassert>  /// 用于断言
#include <iostream> /// 用于输入输出操作
#include <vector>   /// 用于存储格雷码的向量数据结构

/**
 * @namespace bit_manipulation
 * @brief 位操作算法命名空间
 */
namespace bit_manipulation {
/**
 * @namespace gray_code
 * @brief 生成 n 位格雷码
 */
namespace gray_code {
/**
 * @brief 生成 n 位格雷码的主函数
 *
 * @param n 位数
 * @return 存储 n 位格雷码的向量
 */
std::vector<std::bitset<32>> gray_code_generation(int n) {
    std::vector<std::bitset<32>> gray_code = {};  // 初始化为空向量

    // 若 n 非正，则无格雷码可生成
    if (n <= 0) {
        return gray_code;
    }
    
    int total_codes = 1 << n;  // 计算 n 位格雷码的总数量 (2^n)

    for (int i = 0; i < total_codes; i++) {
        int gray_num = i ^ (i >> 1);  // 使用格雷码公式计算格雷码
        gray_code.push_back(std::bitset<32>(gray_num));  // 将格雷码值存入向量
    }

    return gray_code;
} 
}  // namespace gray_code
}  // namespace bit_manipulation

/**
 * @brief 自测函数实现
 *
 * @returns void
 */
static void test() { 
    // 测试用例

    // 当 n 为负数时返回空向量
    std::vector<std::bitset<32>> gray_code_negative_1 = {};

    // 当 n 为 0 时返回空向量
    std::vector<std::bitset<32>> gray_code_0 = {};

    // n 为 1 时的格雷码
    std::vector<std::bitset<32>> gray_code_1 = {
        std::bitset<32>(0), std::bitset<32>(1)
    };

    // n 为 2 时的格雷码
    std::vector<std::bitset<32>> gray_code_2 = {
        std::bitset<32>(0), std::bitset<32>(1), std::bitset<32>(3), std::bitset<32>(2)
    };

    // n 为 3 时的格雷码
    std::vector<std::bitset<32>> gray_code_3 = {
        std::bitset<32>(0), std::bitset<32>(1), std::bitset<32>(3), std::bitset<32>(2),
        std::bitset<32>(6), std::bitset<32>(7), std::bitset<32>(5), std::bitset<32>(4)
    };

    // n 为 4 时的格雷码
    std::vector<std::bitset<32>> gray_code_4 = {
        std::bitset<32>(0), std::bitset<32>(1), std::bitset<32>(3), std::bitset<32>(2),
        std::bitset<32>(6), std::bitset<32>(7), std::bitset<32>(5), std::bitset<32>(4),
        std::bitset<32>(12), std::bitset<32>(13), std::bitset<32>(15), std::bitset<32>(14),
        std::bitset<32>(10), std::bitset<32>(11), std::bitset<32>(9), std::bitset<32>(8)
    };

    // n 为 5 时的格雷码
    std::vector<std::bitset<32>> gray_code_5 = {
        std::bitset<32>(0), std::bitset<32>(1), std::bitset<32>(3), std::bitset<32>(2),
        std::bitset<32>(6), std::bitset<32>(7), std::bitset<32>(5), std::bitset<32>(4),
        std::bitset<32>(12), std::bitset<32>(13), std::bitset<32>(15), std::bitset<32>(14),
        std::bitset<32>(10), std::bitset<32>(11), std::bitset<32>(9), std::bitset<32>(8),
        std::bitset<32>(24), std::bitset<32>(25), std::bitset<32>(27), std::bitset<32>(26),
        std::bitset<32>(30), std::bitset<32>(31), std::bitset<32>(29), std::bitset<32>(28),
        std::bitset<32>(20), std::bitset<32>(21), std::bitset<32>(23), std::bitset<32>(22),
        std::bitset<32>(18), std::bitset<32>(19), std::bitset<32>(17), std::bitset<32>(16)
    };

    // 对无效的 n 值进行断言测试
    assert(bit_manipulation::gray_code::gray_code_generation(-1) == gray_code_negative_1);
    assert(bit_manipulation::gray_code::gray_code_generation(0) == gray_code_0);

    // 对有效的 n 值进行断言测试
    assert(bit_manipulation::gray_code::gray_code_generation(1) == gray_code_1);
    assert(bit_manipulation::gray_code::gray_code_generation(2) == gray_code_2);
    assert(bit_manipulation::gray_code::gray_code_generation(3) == gray_code_3);
    assert(bit_manipulation::gray_code::gray_code_generation(4) == gray_code_4);
    assert(bit_manipulation::gray_code::gray_code_generation(5) == gray_code_5);
}

/**
 * @brief 主函数
 * @returns 程序正常结束时返回 0
 */
int main() {
    test();  // 运行自测实现
    return 0;
}
