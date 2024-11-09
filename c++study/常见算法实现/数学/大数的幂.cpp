/**
 * @file
 * @brief 计算大数的幂
 */
#include <iostream>

/** 最大的输出位数
 *  \f$x^n\f$ 其中 \f$1 <= x,\; n <= 10000\f$，且可能会发生溢出
 */
#define MAX 100000

/** 该函数将x与res[]表示的数字相乘
 * res_size是res[]的大小，或者说res中数字的个数
 * 该函数使用简单的学校数学进行乘法
 * 该函数可能会改变res_size的值，并返回新的res_size
 * @param x 被乘数
 * @param res 用数组表示的大数
 * @param res_size res数组中的数字个数
 */
int multiply(int x, int res[], int res_size) {
    // 初始化进位
    int carry = 0;

    // 一次乘以x与res[]的每一位数字
    for (int i = 0; i < res_size; i++) {
        int prod = res[i] * x + carry;

        // 将'prod'的最后一位数字存储到res[]
        res[i] = prod % 10;

        // 将其余部分存入进位
        carry = prod / 10;
    }

    // 将进位存储到res中，并增加结果的大小
    while (carry) {
        res[res_size] = carry % 10;
        carry = carry / 10;
        res_size++;
    }
    return res_size;
}

/** 该函数计算x的n次幂，并打印 \f$x^n\f$
 * @param x 底数
 * @param n 指数
 */
void power(int x, int n) {
    // 如果指数为0，则输出1
    if (n == 0) {
        std::cout << "1";
        return;
    }

    int res[MAX]; // 用于存储结果的大数
    int res_size = 0; // 结果的大小
    int temp = x;

    // 初始化结果
    // 将x的各位数字存储在res数组中
    while (temp != 0) {
        res[res_size++] = temp % 10;
        temp = temp / 10;
    }

    // 将x乘以n次 (x^n = x * x * x.... n次)
    for (int i = 2; i <= n; i++) {
        res_size = multiply(x, res, res_size);
    }

    // 输出计算结果
    std::cout << x << "^" << n << " = ";
    // 逆序输出res数组中的数字
    for (int i = res_size - 1; i >= 0; i--) {
        std::cout << res[i];
    }
}

/** 主函数 */
int main() {
    int exponent, base;

    // 获取用户输入的底数和指数
    std::cout << "Enter base ";
    std::cin >> base;
    std::cout << "Enter exponent ";
    std::cin >> exponent;

    // 计算并打印结果
    power(base, exponent);
    return 0;
}
