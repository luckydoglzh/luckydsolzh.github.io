/**
 * @file
 * @brief 实现一个函数来检查一个数字是否是2的幂。
 *
 * @details
 * 该算法使用位操作来检查一个数字是否是2的幂。
 *
 * ### 算法
 * 设输入数字为n，那么n与n-1进行按位与操作可以判断该数字是否是2的幂。
 *
 * 例如：
 * 如果N = 32，则N-1为31，若对这两个数字执行按位与操作，则结果为0，
 * 这表明N是2的幂。
 * 如果N = 23，则N-1为22，若对这两个数字执行按位与操作，则结果不为0，
 * 这表明N不是2的幂。
 * \note 该实现比朴素的递归或迭代方法更高效。
 *
 * @author [Neha Hasija](https://github.com/neha-hasija17)
 * @author [Rijul.S](https://github.com/Rijul24)
 */

#include <iostream>  /// 用于输入输出操作
#include <cassert>   /// 用于断言验证


/**
 * @namespace math
 * @brief 数学算法
 */
namespace math {
/**
 * @brief 判断一个数字是否是2的幂
 * @param n 要检查的值
 * 打印结果："Yes, the number n is a power of 2" 或者
 * "No, the number is not a power of 2" （无引号）
 * @returns 1 如果 `n` 是2的幂
 * @returns 0 如果 n 不是2的幂
 */
int power_of_two(int n) {
    /// result存储n与n-1的按位与操作结果
    int result = n & (n - 1);
    
    // 如果result为0，则n是2的幂
    if (result == 0) {
        return 1;
    }

    // 否则，n不是2的幂
    return 0;
}
}  // namespace math

/**
 * @brief 自测函数
 * @returns void
 */
static void test() {
    std::cout << "First case testing... \n"; // 对于n = 32，应该返回1
    assert(math::power_of_two(32) == 1);
    std::cout << "\nPassed!\n";

    std::cout << "Second case testing... \n"; // 对于n = 5，应该返回0
    assert(math::power_of_two(5) == 0);
    std::cout << "\nPassed!\n";

    std::cout << "Third case testing... \n"; // 对于n = 232，应该返回0
    assert(math::power_of_two(232) == 0);
    std::cout << "\nPassed!\n";

    std::cout << "\nAll test cases have successfully passed!\n";
}

/**
 * @brief 用户输入测试（可选，当前注释掉）
 * @returns void
 */
void user_input_test() {
    int n = 0; // 用户输入的数字
    
    std::cout << "Enter a number " << std::endl;
    std::cin >> n; 

    // 调用函数检查n是否是2的幂
    int result = math::power_of_two(n);
    if (result == 1) {
        std::cout << "Yes, the number " << n << " is a power of 2\n";
    }
    else { 
        std::cout << "No, the number " << n << " is not a power of 2\n";
    }
}

/**
 * @brief 主函数
 * @returns 0 退出时返回0
 */
int main() {
    test(); // 运行自测

    // 若要启用用户输入测试，可以取消下面一行的注释
    //user_input_test();

    return 0;
}
