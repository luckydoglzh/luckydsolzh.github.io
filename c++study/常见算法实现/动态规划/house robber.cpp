#include <cassert>   /// 用于断言
#include <climits>   /// 用于 std::max
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于 std::vector

/**
 * @namespace dynamic_programming
 * @brief 动态规划算法命名空间
 */
namespace dynamic_programming {
/**
 * @namespace house_robber
 * @brief [House Robber](https://labuladong.gitbook.io/algo-en/i.-dynamic-programming/houserobber) 算法的函数
 */
namespace house_robber {
/**
 * @brief 实现 House Robber 问题的主函数，使用动态规划
 * @param money 包含各个房屋中钱数的数组
 * @param n 数组的大小
 * @returns 能够偷取的最大金额
 */
std::uint32_t houseRobber(const std::vector<uint32_t> &money,
                          const uint32_t &n) {
    if (n == 0) {  // 如果没有房屋
        return 0;
    }
    if (n == 1) {  // 如果只有一个房屋
        return money[0];
    }
    if (n == 2) {  // 如果有两个房屋，选择金额较大的那个房屋
        return std::max(money[0], money[1]);
    }
    uint32_t max_value = 0;  // 最终的最大偷窃金额
    uint32_t value1 = money[0];
    uint32_t value2 = std::max(money[0], money[1]);
    for (uint32_t i = 2; i < n; i++) {
        max_value = std::max(money[i] + value1, value2);  // 当前房屋与前两个房屋的最大值
        value1 = value2;
        value2 = max_value;
    }

    return max_value;
}
}  // namespace house_robber
}  // namespace dynamic_programming

/**
 * @brief 自我测试实现
 * @returns void
 */
static void test() {
    // 测试 1
    // [1, 2, 3, 1] 返回 4
    std::vector<uint32_t> array1 = {1, 2, 3, 1};
    std::cout << "测试 1... ";
    assert(
        dynamic_programming::house_robber::houseRobber(array1, array1.size()) ==
        4);  // 选择第一个和第三个房屋，总金额为 4
    std::cout << "通过" << std::endl;

    // 测试 2
    // [6, 7, 1, 3, 8, 2, 4] 返回 19
    std::vector<uint32_t> array2 = {6, 7, 1, 3, 8, 2, 4};
    std::cout << "测试 2... ";
    assert(
        dynamic_programming::house_robber::houseRobber(array2, array2.size()) ==
        19);  // 选择第一个、第三个、第五个和第七个房屋，总金额为 19
    std::cout << "通过" << std::endl;

    // 测试 3
    // [] 返回 0
    std::vector<uint32_t> array3 = {};
    std::cout << "测试 3... ";
    assert(
        dynamic_programming::house_robber::houseRobber(array3, array3.size()) ==
        0);  // 没有房屋可以偷窃
    std::cout << "通过" << std::endl;

    // 测试 4
    // [2,7,9,3,1] 返回 12
    std::vector<uint32_t> array4 = {2, 7, 9, 3, 1};
    std::cout << "测试 4... ";
    assert(
        dynamic_programming::house_robber::houseRobber(array4, array4.size()) ==
        12);  // 选择第一个、第三个和第五个房屋，总金额为 12
    std::cout << "通过" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 表示成功退出
 */
int main() {
    test();  // 运行自我测试
    return 0;
}
