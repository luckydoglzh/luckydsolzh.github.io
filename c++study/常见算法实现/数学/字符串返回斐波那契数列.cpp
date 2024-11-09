/**
 * @file
 * @brief 该程序返回第 N 个斐波那契数，结果以字符串形式表示。
 *
 * 使用的方法是手动加法，处理进位，并将结果放入字符串中，这种方法称为字符串加法。
 * 这种方法没有上限或限制，因此能够处理非常大的数字。
 *
 * @see fibonacci_large.cpp, fibonacci_fast.cpp, fibonacci.cpp
 */

#include <iostream>
#ifdef _MSC_VER
#include <string>  // 对于 MS Visual C 编译器使用这个头文件
#else
#include <cstring>  // 否则使用这个头文件
#endif

/**
 * 字符串加法函数
 * \param [in] a 第一个数字，以字符串形式表示
 * \param [in] b 第二个数字，以字符串形式表示
 * \returns 返回两个字符串数字的和，结果也是一个字符串
 */
std::string add(std::string a, std::string b) {
    std::string temp = "";  // 存放结果

    // 进位标志
    int carry = 0;

    // 如果 a 的长度小于 b 的长度，填充 a 使其与 b 长度相同
    while (a.length() < b.length()) {
        a = "0" + a;
    }

    // 如果 b 的长度小于 a 的长度，填充 b 使其与 a 长度相同
    while (b.length() < a.length()) {
        b = "0" + b;
    }

    // 从个位开始逐位加法，处理进位
    for (int i = a.length() - 1; i >= 0; i--) {
        // 计算当前位的和，包含进位
        char val = static_cast<char>(((a[i] - 48) + (b[i] - 48)) + 48 + carry);
        
        // 如果和大于 9，设置进位并调整当前位的值
        if (val > 57) {
            carry = 1;
            val -= 10;
        } else {
            carry = 0;
        }

        // 将当前位的结果加入到字符串的前面
        temp = val + temp;
    }

    // 如果最终还有进位，处理进位
    if (carry == 1) {
        temp = "1" + temp;
    }

    // 移除多余的前导零
    while (temp[0] == '0' && temp.length() > 1) {
        temp = temp.substr(1);
    }

    return temp;
}

/** 计算第 N 个斐波那契数
 * \param [in] n 要计算的斐波那契数的索引（从 0 开始）
 */
void fib_Accurate(uint64_t n) {
    std::string tmp = "";  // 临时存储中间结果
    std::string fibMinus1 = "1";  // 第 N-1 个斐波那契数
    std::string fibMinus2 = "0";  // 第 N-2 个斐波那契数
    
    // 通过迭代计算斐波那契数
    for (uint64_t i = 0; i < n; i++) {
        tmp = add(fibMinus1, fibMinus2);  // 计算 fib(N) = fib(N-1) + fib(N-2)
        fibMinus2 = fibMinus1;  // 更新 fib(N-2)
        fibMinus1 = tmp;  // 更新 fib(N-1)
    }

    std::cout << fibMinus2;  // 输出第 N 个斐波那契数
}

/** 主函数 */
int main() {
    int n;
    std::cout << "请输入您想要计算的斐波那契数的索引 N\n";
    std::cin >> n;  // 读取用户输入的 N
    std::cout << n << " 的斐波那契数是：\n";
    fib_Accurate(n);  // 调用函数计算并输出结果

    return 0;
}
