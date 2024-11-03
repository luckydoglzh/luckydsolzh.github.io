// 程序用于计算数组中最长递增子序列的长度，时间复杂度为 O(n log n)
// 测试链接: https://cses.fi/problemset/task/1145/

#include <iostream>
#include <set>  // 引入集合类
using namespace std;

/**
 * @brief 计算数组中最长递增子序列的长度
 * @param arr 输入数组
 * @param n 数组大小
 * @return 返回最长递增子序列的长度
 */
int LIS(int arr[], int n) {
    set<int> active;  // 当前构建的最长递增子序列
    active.insert(arr[0]);  // 插入第一个元素

    // 遍历数组中的每一个元素
    for (int i = 1; i < n; ++i) {
        auto get = active.lower_bound(arr[i]);  // 查找当前元素在 active 中的位置
        if (get == active.end()) {
            // 如果当前元素大于所有已存元素，插入 active
            active.insert(arr[i]);
        }  
        else {
            int val = *get;  // 找到当前元素在 LIS 中的潜在位置
            if (val > arr[i]) {
                // 如果 val 大于当前元素，删除 val，并插入当前元素
                active.erase(get);
                active.insert(arr[i]);
            }
        }
    }
    return active.size();  // 返回最长递增子序列的长度
}

/**
 * @brief 主函数
 * @return 0 表示正常退出
 */
int main(int argc, char const* argv[]) {
    int n;
    cout << "Enter size of array: ";  // 输入数组大小提示
    cin >> n;  // 读取数组大小
    int a[n];  // 创建数组
    cout << "Enter array elements: ";  // 输入数组元素提示
    for (int i = 0; i < n; ++i) {
        cin >> a[i];  // 读取数组元素
    }
    cout << "Length of Longest Increasing Subsequence is: " << LIS(a, n) << endl;  // 输出最长递增子序列的长度
    return 0;  // 正常退出
}
