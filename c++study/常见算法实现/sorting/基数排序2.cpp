/**
 * @file
 * @brief [基数排序](https://en.wikipedia.org/wiki/Radix_sort)算法实现
 * @author [Suyash Jaiswal](https://github.com/Suyashjaiswal)
 * @details
 * 使用基数排序对无符号整数向量进行排序，即按位排序，使用 [计数排序](https://en.wikipedia.org/wiki/Counting_sort)作为子例程。
 * 基数排序的运行时间为 O(d*(n+b))，其中 b 是表示数字的进制，d 是输入整数的最大位数，n 是无符号整数的个数。
 * 举例说明：对于 n = 5，数组元素 = {432, 234, 143, 332, 123}，按位排序：
 * 1) 第一位排序：
 * => 432, 332, 143, 123, 234
 * 
 * 2) 第二位排序：
 * => 123, 432, 332, 234, 143
 * 
 * 3) 第三位排序：
 * => 123, 143, 234, 332, 432
 * 
 * 每次使用稳定的计数排序进行排序。
 */

/// 引入头文件
#include <algorithm>  /// 提供各种函数库，如 sort 等
#include <cassert>    /// 提供 assert 宏，用于验证假设
#include <iostream>   /// 提供输入输出功能
#include <vector>     /// 提供 std::vector 容器

/**
 * @namespace sorting
 * @brief 排序算法集合
 */
namespace sorting {
/**
 * @namespace radix_sort
 * @brief [基数排序](https://en.wikipedia.org/wiki/Radix_sort)算法相关函数
 */
namespace radix_sort {
/**
 * @brief 根据当前位进行排序，使用稳定排序方法。
 * @param cur_digit - 当前位，用于按照该位进行排序
 * @param ar - 需要排序的向量
 * @returns 排序后到当前位的结果
 */
std::vector<uint64_t> step_ith(
    uint16_t cur_digit,
    const std::vector<uint64_t>& ar) {  // 根据当前位进行排序
    int n = ar.size();  // 获取数组大小
    std::vector<uint32_t> position(10, 0);  // 位置数组，用于存储每个数字（0-9）出现的频率
    // 统计每个数字在当前位的出现频率
    for (int i = 0; i < n; ++i) {
        position[(ar[i] / cur_digit) % 10]++;  // 获取当前位的值，并更新频率
    }

    int cur = 0;
    // 计算每个数字（0-9）在当前位置的起始位置
    for (int i = 0; i < 10; ++i) {
        int a = position[i];
        position[i] = cur;  // 记录每个数字的起始位置
        cur += a;  // 更新当前位的起始位置
    }

    std::vector<uint64_t> temp(n);  // 临时数组，用于存储排序后的元素
    // 根据当前位的值将元素放入正确的位置
    for (int i = 0; i < n; ++i) {
        temp[position[(ar[i] / cur_digit) % 10]] = ar[i];  // 将元素放入正确的桶中
        position[(ar[i] / cur_digit) % 10]++;  // 增加当前位置索引
    }

    return temp;  // 返回根据当前位排序后的数组
}

/**
 * @brief 根据每一位进行基数排序。
 * @param ar - 需要排序的向量
 * @returns 排序后的向量
 */
std::vector<uint64_t> radix(const std::vector<uint64_t>& ar) {
    uint64_t max_ele =
        *max_element(ar.begin(), ar.end());  // 获取数组中的最大元素
    std::vector<uint64_t> temp = ar;  // 临时数组用于排序

    // 根据每一位进行排序，直到最大元素的位数
    for (int i = 1; max_ele / i > 0; i *= 10) {  // 当 i 大于最大元素时，退出排序
        temp = step_ith(i, temp);  // 根据当前位排序
    }

    // 打印排序结果
    for (uint64_t i : temp) {
        std::cout << i << " ";  // 输出排序后的每个元素
    }
    std::cout << "\n";  // 输出换行符
    return temp;  // 返回最终排序后的数组
}
}  // namespace radix_sort
}  // namespace sorting

/**
 * @brief 用于测试算法的函数
 * @returns 无返回值
 */
static void tests() {
    /// 测试1
    std::vector<uint64_t> ar1 = {432, 234, 143, 332, 123};  // 初始化测试数组
    ar1 = sorting::radix_sort::radix(ar1);  // 调用基数排序
    assert(std::is_sorted(ar1.begin(), ar1.end()));  // 验证排序结果是否正确

    /// 测试2
    std::vector<uint64_t> ar2 = {213, 3214, 123, 111, 112, 142,
                                 133, 132,  32,  12,  113};  // 初始化另一个测试数组
    ar2 = sorting::radix_sort::radix(ar2);  // 调用基数排序
    assert(std::is_sorted(ar2.begin(), ar2.end()));  // 验证排序结果是否正确
}

/**
 * @brief 主函数
 * @returns 0，程序退出时返回0
 */
int main() {
    tests();  // 执行测试
    return 0;  // 返回0，表示程序正常结束
}
