/**
 * @file
 * @brief 不使用递归的快速排序。该方法使用栈代替递归。
 * 递归和非递归的实现都具有 O(n log n) 的最好情况和 O(n^2) 的最坏情况。
 * @details
 * 参考链接：
 * https://stackoverflow.com/questions/12553238/quicksort-iterative-or-recursive
 * https://en.wikipedia.org/wiki/Quicksort
 * https://www.geeksforgeeks.org/iterative-quick-sort/
 * @author [Sebe324](https://github.com/sebe324)
 */

#include <iostream> /// 用于 std::cout
#include <vector> /// 用于 std::vector
#include <stack> /// 用于 std::stack
#include <algorithm> /// 用于 std::is_sorted
#include <cassert> /// 用于 assert


/**
 * @namespace sorting
 * @brief 排序算法
 */
namespace sorting {
/**
 * @brief 分区函数：使用最后一个元素作为基准，排序数组。
 * @param arr 需要排序的数组
 * @param start 起始索引
 * @param end 结束索引
 * @return int 返回基准元素的下一个索引
 */
int partition(std::vector<int> &arr, int start, int end)
{
    int pivot = arr[end];  // 选择最后一个元素作为基准
    int index = start - 1;

    for (int j = start; j < end; j++) {
        if (arr[j] <= pivot) {  // 如果当前元素小于或等于基准，则交换
            std::swap(arr[++index], arr[j]);
        }
    }

    std::swap(arr[index + 1], arr[end]);  // 将基准元素放到正确位置
    return index + 1;  // 返回基准元素的新位置
}

/**
 * @brief 主排序函数
 * @details 非递归的快速排序使用栈代替递归来保存和恢复调用之间的环境。
 * 它不需要起始和结束参数，因为它不是递归的。
 * @param arr 需要排序的数组
 * @return void
 */
void iterativeQuickSort(std::vector<int> &arr)
{
    std::stack<int> stack;  // 用栈来模拟递归调用
    int start = 0;
    int end = arr.size() - 1;
    stack.push(start);
    stack.push(end);

    while(!stack.empty())
    {
        end = stack.top();  // 获取栈顶的结束索引
        stack.pop();
        start = stack.top();  // 获取栈顶的起始索引
        stack.pop();

        int pivotIndex = partition(arr, start, end);  // 对当前部分进行分区

        // 如果基准元素左侧有元素，则继续分区
        if(pivotIndex - 1 > start)
        {
            stack.push(start);
            stack.push(pivotIndex - 1);  // 将分区后的左右子区间压入栈中
        }

        // 如果基准元素右侧有元素，则继续分区
        if(pivotIndex + 1 < end)
        {
            stack.push(pivotIndex + 1);
            stack.push(end);
        }
    }
}

} // namespace sorting

/**
 * @brief 自我测试函数
 * @returns void
 */
void tests()
{
    // 测试 1 - 正数数组
    std::vector<int> case1 = {100, 534, 1000000, 553, 10, 61, 2000, 238, 2756, 9, 12, 56, 30};
    std::cout << "测试 1\n";
    std::cout << "排序前: \n";
    for (auto x : case1) std::cout << x << ",";
    std::cout << "\n";
    sorting::iterativeQuickSort(case1);  // 调用迭代版快速排序
    assert(std::is_sorted(std::begin(case1), std::end(case1)));  // 检查排序是否成功
    std::cout << "测试 1 成功!\n";
    std::cout << "排序后: \n";
    for (auto x : case1) std::cout << x << ",";
    std::cout << "\n";

    // 测试 2 - 负数数组
    std::vector<int> case2 = {-10, -2, -5, -2, -3746, -785, -123, -452, -32456};
    std::cout << "测试 2\n";
    std::cout << "排序前: \n";
    for (auto x : case2) std::cout << x << ",";
    std::cout << "\n";
    sorting::iterativeQuickSort(case2);  // 调用迭代版快速排序
    assert(std::is_sorted(std::begin(case2), std::end(case2)));  // 检查排序是否成功
    std::cout << "测试 2 成功!\n";
    std::cout << "排序后: \n";
    for (auto x : case2) std::cout << x << ",";
    std::cout << "\n";
}


/**
 * @brief 主函数
 * @returns 0 退出
 */
int main()
{
    tests();  // 运行自我测试函数
    return 0;  // 程序正常结束
}
