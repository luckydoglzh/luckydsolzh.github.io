/**
 * @file
 * @brief 该程序通过除法方法计算 n 个数的最大公约数（GCD）
 *
 * @see gcd_iterative_euclidean.cpp, gcd_recursive_euclidean.cpp
 */
#include <iostream>

/**
 * @brief 使用除法算法计算多个整数的最大公约数（GCD）
 *
 * @param[in] a 整数数组，包含要计算 GCD 的元素
 * @param[in] n 数组 `a` 中整数的数量
 * @returns 数组中所有整数的最大公约数
 */
int gcd(int *a, int n) {
    int j = 1;  ///< 访问数组中的所有元素，从索引 1 开始
    int gcd = a[0];  ///< 初始 GCD 值设为数组的第一个元素

    // 遍历数组并计算 GCD
    while (j < n) {
        if (a[j] % gcd == 0)  // 如果当前元素可以被 GCD 整除，说明 GCD 值仍然适用
            j++;  // 检查下一个元素
        else
            gcd = a[j] % gcd;  // 如果不能整除，更新 GCD 值
    }

    return gcd;
}

/** 
 * @brief 主函数
 * @returns 0 表示程序正常退出
 */
int main() {
    int n;  // 要计算的整数数量
    std::cout << "输入整数的个数 n:" << std::endl;
    std::cin >> n;

    // 动态分配数组以存储 n 个整数
    int *a = new int[n];
    int i;
    std::cout << "输入这 n 个整数:" << std::endl;
    for (i = 0; i < n; i++) {
        std::cin >> a[i];  // 将每个整数读入数组
    }

    // 输出 n 个整数的最大公约数
    std::cout << "输入的 n 个数的最大公约数为: " << gcd(a, n) << std::endl;

    delete[] a;  // 释放动态分配的数组内存
    return 0;
}
