// C++ 程序用于找到排序数组所需的最小交换次数
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

// 函数返回将数组排序所需的最小交换次数
int minSwaps(int arr[], int n) {
    // 创建一个由对组成的数组，第一个元素是数组元素，第二个元素是该元素的初始位置
    std::pair<int, int> *arrPos = new std::pair<int, int>[n];
    for (int i = 0; i < n; i++) {
        arrPos[i].first = arr[i];    // 数组元素
        arrPos[i].second = i;        // 元素的原始位置
    }

    // 根据数组元素的值进行排序，得到每个元素应处的位置（即对中的第二个元素）
    std::sort(arrPos, arrPos + n);

    // 创建一个布尔数组用于跟踪元素是否已访问
    std::vector<bool> vis(n, false);

    // 初始化交换次数结果
    int ans = 0;

    // 遍历所有元素
    for (int i = 0; i < n; i++) {
        // 如果元素已经交换过或者已经在正确位置上，就跳过
        if (vis[i] || arrPos[i].second == i)
            continue;

        // 计算当前环中的节点数，并更新交换次数
        int cycle_size = 0;
        int j = i;
        while (!vis[j]) {
            vis[j] = 1;  // 标记元素为已访问

            // 移动到下一个节点，即元素的原始位置
            j = arrPos[j].second;
            cycle_size++;
        }

        // 更新答案，当前环中的交换次数是环的大小减一
        if (cycle_size > 0) {
            ans += (cycle_size - 1);  // 环的大小减去 1 即为需要的交换次数
        }
    }

    // 释放动态分配的内存
    delete[] arrPos;

    // 返回最终的交换次数
    return ans;
}

// 测试程序
int main() {
    int arr[] = {6, 7, 8, 1, 2, 3, 9, 12};  // 输入数组
    int n = (sizeof(arr) / sizeof(int));   // 获取数组的大小
    std::cout << minSwaps(arr, n);  // 输出最小交换次数
    return 0;
}
