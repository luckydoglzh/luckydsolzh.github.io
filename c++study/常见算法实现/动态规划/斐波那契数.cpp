#include <iostream>
using namespace std;

// 函数 fib 计算第 n 个斐波那契数
int fib(int n) {
    int res[3];  // 用于存储计算过程中需要的三个中间结果
    res[0] = 0;  // 初始化第 0 个斐波那契数为 0
    res[1] = 1;  // 初始化第 1 个斐波那契数为 1

    for (int i = 2; i <= n; i++) {
        res[2] = res[1] + res[0];  // 计算当前的斐波那契数
        res[0] = res[1];           // 更新 res[0] 为上一个斐波那契数
        res[1] = res[2];           // 更新 res[1] 为当前计算的斐波那契数
    }

    return res[1];  // 返回第 n 个斐波那契数
}

int main(int argc, char const *argv[]) {
    int n;
    cout << "请输入 n 的值: ";
    cin >> n;
    cout << "斐波那契数为 ";
    cout << fib(n) << endl;
    return 0;
}
