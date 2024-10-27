/**
 * @file
 * @brief 实现 [Karatsuba 算法快速乘法](https://en.wikipedia.org/wiki/Karatsuba_algorithm)
 * @details
 * 给定两个二进制表示的字符串，我们希望将它们相乘并返回值。简单的方法是逐位相乘，这样的时间复杂度大约为 O(n^2)。为了提高效率，我们将使用 Karatsuba 算法以 O(nlogn) 的时间复杂度解决问题。
 * @author [Swastika Gupta](https://github.com/Swastyy)
 * @author [Ameer Carlo Lubang](https://github.com/poypoyan)
 */

#include <cassert>   /// 用于断言
#include <cstring>   /// 用于字符串操作
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于 std::vector

/**
 * @namespace divide_and_conquer
 * @brief 分治算法命名空间
 */
namespace divide_and_conquer {
/**
 * @namespace karatsuba_algorithm
 * @brief 实现 [Karatsuba 算法快速乘法](https://en.wikipedia.org/wiki/Karatsuba_algorithm) 的函数
 */
namespace karatsuba_algorithm {
/**
 * @brief 二进制加法
 * @param first 输入字符串 1
 * @param second 输入字符串 2
 * @returns 返回二进制字符串的和
 */
std::string add_strings(std::string first, std::string second) {
    std::string result;  // 存储结果的和

    // 使字符串长度相等
    int64_t len1 = first.size();
    int64_t len2 = second.size();
    std::string zero = "0";
    if (len1 < len2) {
        for (int64_t i = 0; i < len2 - len1; i++) {
            zero += first;
            first = zero;
            zero = "0"; // 防止 CI 失败
        }
    } else if (len1 > len2) {
        for (int64_t i = 0; i < len1 - len2; i++) {
            zero += second;
            second = zero;
            zero = "0"; // 防止 CI 失败
        }
    }

    int64_t length = std::max(len1, len2);
    int64_t carry = 0;
    for (int64_t i = length - 1; i >= 0; i--) {
        int64_t firstBit = first.at(i) - '0';
        int64_t secondBit = second.at(i) - '0';

        int64_t sum = (char(firstBit ^ secondBit ^ carry)) + '0';  // 三个位的和
        result.insert(result.begin(), sum);

        carry = char((firstBit & secondBit) | (secondBit & carry) |
                (firstBit & carry));  // 进位
    }

    if (carry) {
        result.insert(result.begin(), '1');  // 如果溢出，添加 1
    }
    return result;
}

/**
 * @brief 考虑前导零的 substr 包装函数。
 * @param str 输入的二进制字符串
 * @param x1 substr 参数整数 1
 * @param x2 substr 参数整数 2
 * @param n "整体" 字符串的长度：前导零 + str
 * @returns 返回无前导零的“安全”子字符串
 * @returns 如果子字符串仅跨越前导零则返回 "0"
 */
std::string safe_substr(const std::string &str, int64_t x1, int64_t x2, int64_t n) {
    int64_t len = str.size();

    if (len >= n) {
        return str.substr(x1, x2);
    }

    int64_t y1 = x1 - (n - len);  // "整体" 字符串中子字符串第一个字符的索引
    int64_t y2 = (x1 + x2 - 1) - (n - len);  // "整体" 字符串中子字符串最后一个字符的索引

    if (y2 < 0) {
        return "0";
    } else if (y1 < 0) {
        return str.substr(0, y2 + 1);
    } else {
        return str.substr(y1, x2);
    }
}

/**
 * @brief 主函数实现 Karatsuba 算法进行快速乘法
 * @param str1 输入字符串 1
 * @param str2 输入字符串 2
 * @returns 返回乘积的数值
 */
int64_t karatsuba_algorithm(std::string str1, std::string str2) {
    int64_t len1 = str1.size();
    int64_t len2 = str2.size();
    int64_t n = std::max(len1, len2);

    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return (str1[0] - '0') * (str2[0] - '0');
    }

    int64_t fh = n / 2;     // 字符串的前半部分
    int64_t sh = n - fh;   // 字符串的后半部分

    std::string Xl = divide_and_conquer::karatsuba_algorithm::safe_substr(str1, 0, fh, n);   // 第一个字符串的前半部分
    std::string Xr = divide_and_conquer::karatsuba_algorithm::safe_substr(str1, fh, sh, n);  // 第一个字符串的后半部分

    std::string Yl = divide_and_conquer::karatsuba_algorithm::safe_substr(str2, 0, fh, n);   // 第二个字符串的前半部分
    std::string Yr = divide_and_conquer::karatsuba_algorithm::safe_substr(str2, fh, sh, n);  // 第二个字符串的后半部分

    // 递归计算大小为 n/2 的输入的三个乘积
    int64_t product1 = karatsuba_algorithm(Xl, Yl);
    int64_t product2 = karatsuba_algorithm(Xr, Yr);
    int64_t product3 = karatsuba_algorithm(
        divide_and_conquer::karatsuba_algorithm::add_strings(Xl, Xr),
        divide_and_conquer::karatsuba_algorithm::add_strings(Yl, Yr));

    return product1 * (1 << (2 * sh)) +
           (product3 - product1 - product2) * (1 << sh) +
           product2;  // 合并三个乘积以得到最终结果
}
}  // namespace karatsuba_algorithm
}  // namespace divide_and_conquer

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    // 第一个测试
    std::string s11 = "1";     // 1
    std::string s12 = "1010";  // 10
    std::cout << "第一个测试... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(
               s11, s12) == 10);
    std::cout << "通过" << std::endl;

    // 第二个测试
    std::string s21 = "11";    // 3
    std::string s22 = "1010";  // 10
    std::cout << "第二个测试... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(
               s21, s22) == 30);
    std::cout << "通过" << std::endl;

    // 第三个测试
    std::string s31 = "110";   // 6
    std::string s32 = "1010";  // 10
    std::cout << "第三个测试... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(
               s31, s32) == 60);
    std::cout << "通过" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 正常退出
 */
int main() {
    test();  // 运行自测实现
    return 0;
}
