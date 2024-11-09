/**
 * Copyright 2020 @author iamnambiar
 *
 * @file
 * \brief 一个C++程序，用于计算输入整数的各位数字之和。
 */
#include <cassert>
#include <iostream>

/**
 * 计算整数各位数字之和的函数。
 * @param num 输入的整数。
 * @return 返回整数各位数字之和。
 *
 * \detail
 * 首先算法检查num是正数还是负数，
 * 如果是负数，则忽略负号。
 * 接下来，通过取余运算（num % 10）提取num的最后一位数字，并将其加到sum中。
 * 然后num除以10，去掉最后一位数字。
 * 该循环会一直持续，直到num变为0。
 */
int sum_of_digits(int num) {
    // 如果num是负数，则忽略负号。
    if (num < 0) {
        num = -1 * num;  // 将负数转为正数
    }
    int sum = 0;  // 用于存储各位数字之和
    // 当num大于0时，继续提取数字
    while (num > 0) {
        sum = sum + (num % 10);  // 提取最后一位数字并加到sum
        num = num / 10;  // 去掉最后一位数字
    }
    return sum;  // 返回数字的和
}

/**
 * 测试sum_of_digits()函数的第一个测试用例，输入值为119765，断言结果为29。
 */
void test1() {
    int test_case_1 = sum_of_digits(119765);
    assert(test_case_1 == 29);  // 断言结果为29
}

/**
 * 测试sum_of_digits()函数的第二个测试用例，输入值为-12256，断言结果为16。
 */
void test2() {
    int test_case_2 = sum_of_digits(-12256);
    assert(test_case_2 == 16);  // 断言结果为16
}

/**
 * 测试所有测试用例的函数。
 */
void test() {
    // 第一个测试用例
    test1();
    // 第二个测试用例
    test2();
}

/**
 * 主函数
 */
int main() {
    test();  // 执行所有测试
    std::cout << "Success." << std::endl;  // 打印测试成功信息
    return 0;  // 程序正常退出
}
