/**
 * @file
 * @brief [巴比伦方法
 * (BM)](https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Babylonian_method)
 * 是一种计算平方根的算法。
 * @details
 * 该算法在用户想要找到大数的准确平方根时具有应用场景。
 * @author [Ameya Chawla](https://github.com/ameyachawlaggsipu)
 */

#include <cassert>  /// 用于断言
#include <cmath>
#include <iostream>  /// 用于输入输出操作

/**
 * @namespace numerical_methods
 * @brief 数值算法/方法
 */

namespace numerical_methods {

/**
 * @brief 巴比伦方法是一个迭代函数，用于返回
 * 给定数的平方根。
 * @param radicand 被开方数
 * @returns x1 被开方数的平方根
 */

double babylonian_method(double radicand) {
    int i = 1;  /// 找到初始根或粗略估计

    while (i * i <= radicand) {
        i++;
    }

    i--;  /// 实际初始值为 i-1，因为循环在 +1 时停止

    double x0 = i;  /// 存储前一个值以进行比较
    double x1 =
        (radicand / x0 + x0) / 2;  /// 存储计算值以进行比较
    double temp = NAN;             /// 临时变量，用于 x0 和 x1 的比较

    while (std::max(x0, x1) - std::min(x0, x1) >= 0.0001) {  // 修改条件为大于等于
        temp = (radicand / x1 + x1) / 2;  /// 新计算的平方根
        x0 = x1;
        x1 = temp;
    }

    return x1;  /// 返回最终的平方根
}

}  // namespace numerical_methods

/**
 * @brief 自测实现
 * @details
 * 声明两个测试用例，并检查预测值与真实值的误差
 * 小于 0.0001。
 * @returns void
 */
static void test() {
    /* 以下测试的描述 */

    auto testcase1 = 125348;  /// 测试用例 1
    auto testcase2 = 752080;  /// 测试用例 2

    auto real_output1 = 354.045194855;  /// 真实输出 1
    auto real_output2 = 867.225460881;  /// 真实输出 2

    auto test_result1 = numerical_methods::babylonian_method(testcase1);
    /// 测试用例 1 的测试结果
    auto test_result2 = numerical_methods::babylonian_method(testcase2);
    /// 测试用例 2 的测试结果

    assert(std::max(test_result1, real_output1) -
               std::min(test_result1, real_output1) < 
           0.0001);
    /// 对测试用例 1 进行测试
    assert(std::max(test_result2, real_output2) -
               std::min(test_result2, real_output2) < 
           0.0001);
    /// 对测试用例 2 进行测试

    std::cout << "所有测试均成功通过！\n";
}

/**
 * @brief 主函数
 * @param argc 命令行参数计数（被忽略）
 * @param argv 命令行参数数组（被忽略）
 * 调用自动化测试函数以测试巴比伦方法的工作。
 * @returns 0 退出
 */

int main(int argc, char const *argv[]) {
    test();  // 运行自测实现
             // 使用 2 个定义的测试用例
    return 0;
}
