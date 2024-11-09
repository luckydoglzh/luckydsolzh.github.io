/**
 * @file
 * @brief 使用勒让德公式找出最大的 x，使得 p^x 可以整除 n! (阶乘)。
 * @details 给定一个整数 n 和一个质数 p，任务是找出最大的 x，使得 p^x（p 的 x 次方）整除 n!（阶乘）。
 * 这将使用勒让德公式计算：
 * x = [n/(p^1)] + [n/(p^2)] + [n/(p^3)] + ... + 1
 * @see 更多信息参见 https://math.stackexchange.com/questions/141196/highest-power-of-a-prime-p-dividing-n
 * @author [uday6670](https://github.com/uday6670)
 */

#include <iostream> /// 用于 std::cin 和 std::cout
#include <cassert>  /// 用于 assert

/**
 * @namespace math
 * @brief 数学算法
 */
namespace math {

    /** 
     * @brief 计算最大的幂
     * @param n 数字
     * @param p 质数
     * @returns 最大的幂
     */ 
    uint64_t largestPower(uint32_t n, const uint16_t& p)  
    {  
        // 初始化结果  
        int x = 0;  
      
        // 计算结果 
        while (n)  
        {  
            n /= p;  // n 除以 p
            x += n;  // 累加
        }  
        return x;  // 返回结果
    }

}  // namespace math

/**
 * @brief 用于测试 largestPower 函数的函数。
 * 包含测试用例和 assert 语句。
 * @returns `void`
 */
static void test()
{
    uint8_t test_case_1 = math::largestPower(5,2);
    assert(test_case_1 == 3);  // 5! 中包含的 2 的最大幂是 3
    std::cout << "Test 1 Passed!" << std::endl;
    
    uint16_t test_case_2 = math::largestPower(10,3);
    assert(test_case_2 == 4);  // 10! 中包含的 3 的最大幂是 4
    std::cout << "Test 2 Passed!" << std::endl;
    
    uint32_t test_case_3 = math::largestPower(25,5);
    assert(test_case_3 == 6);  // 25! 中包含的 5 的最大幂是 6
    std::cout << "Test 3 Passed!" << std::endl;
    
    uint32_t test_case_4 = math::largestPower(27,2);
    assert(test_case_4 == 23);  // 27! 中包含的 2 的最大幂是 23
    std::cout << "Test 4 Passed!" << std::endl;
    
    uint16_t test_case_5 = math::largestPower(7,3);
    assert(test_case_5 == 2);  // 7! 中包含的 3 的最大幂是 2
    std::cout << "Test 5 Passed!" << std::endl;
} 

/**
 * @brief 主函数
 * @returns 0 程序结束时返回 0
 */
int main() 
{ 
    test(); // 执行测试
    return 0;
}  
