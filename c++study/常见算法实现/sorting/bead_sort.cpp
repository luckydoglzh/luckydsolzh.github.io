// C++ 程序实现重力/珠子排序
#include <cstdio>     // 用于输入输出
#include <cstring>    // 用于内存操作

#define BEAD(i, j) beads[i * max + j]  // 定义宏来访问珠子数组

// 执行珠子排序算法的函数
void beadSort(int *a, int len) {
    // 找到最大元素
    int max = a[0];
    for (int i = 1; i < len; i++)
        if (a[i] > max)
            max = a[i];

    // 分配内存
    unsigned char *beads = new unsigned char[max * len];
    memset(beads, 0, static_cast<size_t>(max) * len);  // 初始化珠子数组为0

    // 标记珠子
    for (int i = 0; i < len; i++)
        for (int j = 0; j < a[i]; j++) BEAD(i, j) = 1;  // 在对应位置标记珠子

    for (int j = 0; j < max; j++) {
        // 计算每根柱子上的珠子数量
        int sum = 0;
        for (int i = 0; i < len; i++) {
            sum += BEAD(i, j);  // 统计珠子数
            BEAD(i, j) = 0;      // 将当前珠子位置重置为0
        }

        // 将珠子向下移动
        for (int i = len - sum; i < len; i++) BEAD(i, j) = 1;  // 在底部放置珠子
    }

    // 使用珠子将排序后的值放入数组中
    for (int i = 0; i < len; i++) {
        int j;
        for (j = 0; j < max && BEAD(i, j); j++) {
            // 统计珠子数
        }

        a[i] = j;  // 将珠子数量赋值回原数组
    }
    delete[] beads;  // 释放内存
}

// 驱动函数以测试算法
int main() {
    int a[] = {5, 3, 1, 7, 4, 1, 1, 20};  // 待排序数组
    int len = sizeof(a) / sizeof(a[0]);  // 计算数组长度

    beadSort(a, len);  // 调用珠子排序函数

    // 输出排序后的数组
    for (int i = 0; i < len; i++) printf("%d ", a[i]);

    return 0;  // 程序结束
}
