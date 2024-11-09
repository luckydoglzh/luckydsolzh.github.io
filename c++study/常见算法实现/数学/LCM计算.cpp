/**
 * Copyright 2020 @author tjgurwara99
 * @file
 *
 * 最小公倍数（LCM）函数的基本实现
 */

#include <cassert>
#include <iostream>

/**
 * 计算两个数的最大公约数（GCD）的函数。
 * @params 两个整数 x 和 y，计算它们的最大公约数。
 * @return x 和 y 的最大公约数。
 */
unsigned int gcd(unsigned int x, unsigned int y) {
    if (x == 0) {
        return y;  // 如果 x 为 0，返回 y
    }
    if (y == 0) {
        return x;  // 如果 y 为 0，返回 x
    }
    if (x == y) {
        return x;  // 如果 x 和 y 相等，返回它们
    }
    if (x > y) {
        // 计算 x 和 y 的最大公约数。此处用递归实现辗转相除法
        unsigned int temp = x / y;  // 计算商
        return gcd(y, x - temp * y);  // 递归调用
    }
    // 如果 x 小于 y，交换 x 和 y 后继续递归计算
    unsigned int temp = y / x;  // 计算商
    return gcd(x, y - temp * x);  // 递归调用
}

/**
 * 计算两个数的最小公倍数（LCM）的函数。
 * @params 两个整数 x 和 y，计算它们的最小公倍数。
 * @return x 和 y 的最小公倍数，使用公式：x * y = gcd(x, y) * lcm(x, y)
 */
unsigned int lcm(unsigned int x, unsigned int y) {
  return x / gcd(x, y) * y;  // 根据公式计算 LCM
}

/**
 * 测试 lcm() 函数，包含一些 assert 语句来验证其正确性。
 */
void tests() {
    // 第一个测试，计算 lcm(5, 10) 应该等于 10
    assert(((void)"LCM of 5 and 10 is 10 but lcm function gives a different "
                  "result.\n",
            lcm(5, 10) == 10));
    std::cout << "第一个测试通过：5 和 10 的 LCM 是 " << lcm(5, 10) << std::endl;

    // 第二个测试，计算 lcm(2, 3) 应该等于 6，因为 2 和 3 是互质的（素数）
    assert(((void)"LCM of 2 and 3 is 6 but lcm function gives a different "
                  "result.\n",
            lcm(2, 3) == 6));
    std::cout << "第二个测试通过：2 和 3 的 LCM 是 " << lcm(2, 3) << std::endl;

    // 测试整数溢出。算法应该能正常工作，只要结果能适配到整数范围。
    assert(((void)"LCM of 987654321 and 987654321 is 987654321 but lcm function"
                  " gives a different result.\n",
            lcm(987654321, 987654321) == 987654321));
    std::cout << "第三个测试通过：987654321 和 987654321 的 LCM 是 "
              << lcm(987654321, 987654321)
              << std::endl;
}

/**
 * 主函数
 */
int main() {
    tests();  // 执行所有测试
    return 0;
}
