#include <climits>   // 用于 INT_MIN
#include <iostream>  // 用于输入输出操作

/**
 * @brief 找到数组的最大子数组和
 * @param a 输入数组
 * @param size 数组的大小
 * @return 最大连续子数组和
 */
int maxSubArraySum(int a[], int size) {
    int max_so_far = INT_MIN;   // 初始化最大和为最小整数值
    int max_ending_here = 0;    // 当前子数组和

    for (int i = 0; i < size; i++) {
        max_ending_here = max_ending_here + a[i];  // 更新当前子数组和

        // 更新最大和，如果当前子数组和比最大和大
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;

        // 如果当前子数组和为负数，将其重置为 0
        if (max_ending_here < 0)
            max_ending_here = 0;
    }
    return max_so_far;  // 返回最大连续子数组和
}

int main() {
    int n, i;
    std::cout << "输入元素的数量: \n";
    std::cin >> n;
    int a[n];  // 定义数组 a 大小为 n

    // 输入数组元素
    std::cout << "输入数组元素: \n";
    for (i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    // 调用函数计算最大子数组和
    int max_sum = maxSubArraySum(a, n);
    std::cout << "最大连续子数组和是 " << max_sum;
    return 0;
}
