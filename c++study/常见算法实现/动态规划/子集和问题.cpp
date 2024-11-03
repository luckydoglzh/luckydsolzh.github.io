/**
 * @file
 * @brief 实现 [子集和问题] (https://en.wikipedia.org/wiki/Subset_sum_problem) 算法，用于判断是否存在一个子集使其和等于给定目标值。
 *
 * @details
 * 在这个问题中，我们使用动态规划来判断是否可以从数组中提取出一个子集，使其和等于给定的目标值。该问题的总体时间复杂度为 O(n * targetSum)，其中 n 是数组的大小。例如，数组 = [1, -10, 2, 31, -6]，目标和 = -14。
 * 输出：true => 我们可以选择子集 [-10, 2, -6]，其和为 (-10) + 2 + (-6) = -14。
 * @author [KillerAV](https://github.com/KillerAV)
 */

#include <cassert>        /// 用于 std::assert
#include <iostream>       /// 用于输入输出操作
#include <unordered_map>  /// 用于无序映射
#include <vector>         /// 用于 std::vector

/**
 * @namespace dynamic_programming
 * @brief 动态规划算法
 */
namespace dynamic_programming {

/**
 * @namespace subset_sum
 * @brief [子集和问题] (https://en.wikipedia.org/wiki/Subset_sum_problem) 算法的函数
 */
namespace subset_sum {

/**
 * 使用动态规划的递归函数，查找是否存在所需和的子集。
 * @param arr 输入数组
 * @param targetSum 子集的目标和
 * @param dp 存储结果的映射
 * @returns true/false，表示是否存在目标和的子集。
 */
bool subset_sum_recursion(const std::vector<int> &arr, int targetSum,
                          std::vector<std::unordered_map<int, bool>> *dp,
                          int index = 0) {
    if (targetSum == 0) {  // 找到一个和为目标值的有效子集
        return true;
    }
    if (index == arr.size()) {  // 到达数组末尾
        return false;
    }

    if ((*dp)[index].count(targetSum)) {  // 答案已存在于映射中
        return (*dp)[index][targetSum];
    }

    // 递归计算：选择当前元素或不选择
    bool ans =
        subset_sum_recursion(arr, targetSum - arr[index], dp, index + 1) ||
        subset_sum_recursion(arr, targetSum, dp, index + 1);
    
    (*dp)[index][targetSum] = ans;  // 将答案保存到 dp 映射中
    return ans;
}

/**
 * 实现子集和算法的自顶向下方法
 * @param arr 输入数组
 * @param targetSum 子集的目标和
 * @returns true/false，表示是否存在目标和的子集。
 */
bool subset_sum_problem(const std::vector<int> &arr, const int targetSum) {
    size_t n = arr.size();
    std::vector<std::unordered_map<int, bool>> dp(n);
    return subset_sum_recursion(arr, targetSum, &dp);
}
}  // namespace subset_sum
}  // namespace dynamic_programming

/**
 * @brief 测试函数
 * @return void
 */
static void test() {
    // 自定义输入向量
    std::vector<std::vector<int>> custom_input_arr(3);
    custom_input_arr[0] = std::vector<int>{1, -10, 2, 31, -6};
    custom_input_arr[1] = std::vector<int>{2, 3, 4};
    custom_input_arr[2] = std::vector<int>{0, 1, 0, 1, 0};

    std::vector<int> custom_input_target_sum(3);
    custom_input_target_sum[0] = -14;
    custom_input_target_sum[1] = 10;
    custom_input_target_sum[2] = 2;

    // 通过 subset_sum_problem 函数计算的输出向量
    std::vector<int> calculated_output(3);

    for (int i = 0; i < 3; i++) {
        calculated_output[i] =
            dynamic_programming::subset_sum::subset_sum_problem(
                custom_input_arr[i], custom_input_target_sum[i]);
    }

    // 预期输出向量
    std::vector<bool> expected_output{true, false, true};

    // 使用 assert 函数测试实现
    // 如果任何预期测试失败，将引发错误
    // 否则不做任何事情
    for (int i = 0; i < 3; i++) {
        assert(expected_output[i] == calculated_output[i]);
    }

    std::cout << "所有测试均成功通过！\n";
}

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main() {
    test();  // 执行测试
    return 0;
}
