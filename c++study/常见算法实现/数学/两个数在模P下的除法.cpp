/**
 * @file
 * @brief 一个计算两个数在模p下的除法的算法 [模除](https://www.geeksforgeeks.org/modular-division)
 * @details 计算两个数在模p下的除法
 * 除法的模运算不是分配律的，因此我们首先要通过[费马小定理](https://en.wikipedia.org/wiki/Fermat%27s_little_theorem)
 * 计算除数的逆元素。
 * 现在，我们可以将被除数与除数的逆元素相乘，因为模运算是分配于乘法的。
 * 设有3个数 a, b, p
 * 计算 (a/b)%p
 * (a/b)%p ≡ (a*(inverse(b)))%p ≡ ((a%p)*inverse(b)%p)%p
 * 注意：为了使 'b' 的逆元素存在，'b' 和 'p' 必须互质。
 * 为了简化，假设p是质数。
 * 时间复杂度：O(log(b))
 * 例子： ( 24 / 3 ) % 5 => 8 % 5 = 3 --- (i)
 *          现在3的逆元素是2
 *          (24 * 2) % 5 = (24 % 5) * (2 % 5) = (4 * 2) % 5 = 3 --- (ii)
 *          (i)和(ii)相等，因此答案是正确的。
 * @see modular_inverse_fermat_little_theorem.cpp, modular_exponentiation.cpp
 * @author [Shubham Yadav](https://github.com/shubhamamsa)
 */

#include <cassert>   /// 用于 assert 断言
#include <iostream>  /// 用于输入输出操作

/**
 * @namespace math
 * @brief 数学算法相关函数
 */
namespace math {
/**
 * @namespace modular_division
 * @brief 实现 [模除](https://www.geeksforgeeks.org/modular-division) 的函数
 */
namespace modular_division {
/**
 * @brief 该函数使用模幂运算计算a的b次幂模c的结果
 * @param a 整数底数
 * @param b 无符号整数指数
 * @param c 整数模数
 * @return a 的 b 次幂模 c 的结果
 */
uint64_t power(uint64_t a, uint64_t b, uint64_t c) {
    uint64_t ans = 1;  /// 初始化返回的结果为1
    a = a % c;         /// 如果a大于等于c，则更新a
    if (a == 0) {
        return 0;  /// 如果a能被c整除，返回0
    }
    while (b > 0) {
        /// 如果b是奇数，乘上a
        if (b & 1) {
            ans = ((ans % c) * (a % c)) % c;
        }
        /// b现在是偶数
        b = b >> 1;  /// b = b/2
        a = ((a % c) * (a % c)) % c;
    }
    return ans;
}

/**
 * @brief 该函数计算模除操作的结果
 * @param a 整数被除数
 * @param b 整数除数
 * @param p 整数模数
 * @return a/b 模 p 的结果
 */
uint64_t mod_division(uint64_t a, uint64_t b, uint64_t p) {
    uint64_t inverse = power(b, p - 2, p) % p;  /// 计算b的逆元素
    uint64_t result =
        ((a % p) * (inverse % p)) % p;  /// 计算最终的结果
    return result;
}
}  // namespace modular_division
}  // namespace math

/**
 * @brief 测试 power 函数的功能
 * 包含测试用例和断言
 * @returns `void`
 */
static void test() {
    uint64_t test_case_1 = math::modular_division::mod_division(8, 2, 2);
    assert(test_case_1 == 0);  /// 测试案例1：8除以2模2应该返回0
    std::cout << "Test 1 Passed!" << std::endl;
    uint64_t test_case_2 = math::modular_division::mod_division(15, 3, 7);
    assert(test_case_2 == 5);  /// 测试案例2：15除以3模7应该返回5
    std::cout << "Test 2 Passed!" << std::endl;
    uint64_t test_case_3 = math::modular_division::mod_division(10, 5, 2);
    assert(test_case_3 == 0);  /// 测试案例3：10除以5模2应该返回0
    std::cout << "Test 3 Passed!" << std::endl;
    uint64_t test_case_4 = math::modular_division::mod_division(81, 3, 5);
    assert(test_case_4 == 2);  /// 测试案例4：81除以3模5应该返回2
    std::cout << "Test 4 Passed!" << std::endl;
    uint64_t test_case_5 = math::modular_division::mod_division(12848, 73, 29);
    assert(test_case_5 == 2);  /// 测试案例5：12848除以73模29应该返回2
    std::cout << "Test 5 Passed!" << std::endl;
}

/**
 * @brief 主函数
 * @param argc 命令行参数的数量（忽略）
 * @param argv 命令行参数数组（忽略）
 * @returns 0 表示退出
 */
int main(int argc, char *argv[]) {
    test();  // 执行测试
    return 0;
}
