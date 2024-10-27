/**
 * @file
 * @brief A1Z26密码的实现
 * @details A1Z26密码是一种简单的替换密码，每个字母被其在字母表中的位置数字替换。例如，A对应1，B=2，C=3，依此类推。
 *
 * @author [Focusucof](https://github.com/Focusucof)
 */

#include <algorithm>  /// 用于 std::transform 和 std::replace
#include <cassert>    /// 用于 assert
#include <cstdint>    /// 用于 uint8_t
#include <iostream>   /// 用于输入输出操作
#include <map>        /// 用于 std::map
#include <sstream>    /// 用于 std::stringstream
#include <string>     /// 用于 std::string
#include <vector>     /// 用于 std::vector

/**
 * @namespace ciphers
 * @brief 加密和解密算法
 */
namespace ciphers {
/**
 * @namespace a1z26
 * @brief A1Z26加密和解密的实现
 */
namespace a1z26 {

std::map<uint8_t, char> a1z26_decrypt_map = {
    {1, 'a'},  {2, 'b'},  {3, 'c'},  {4, 'd'},  {5, 'e'},  {6, 'f'},  {7, 'g'},
    {8, 'h'},  {9, 'i'},  {10, 'j'}, {11, 'k'}, {12, 'l'}, {13, 'm'}, {14, 'n'},
    {15, 'o'}, {16, 'p'}, {17, 'q'}, {18, 'r'}, {19, 's'}, {20, 't'}, {21, 'u'},
    {22, 'v'}, {23, 'w'}, {24, 'x'}, {25, 'y'}, {26, 'z'},
};

std::map<char, uint8_t> a1z26_encrypt_map = {
    {'a', 1},  {'b', 2},  {'c', 3},  {'d', 4},  {'e', 5},  {'f', 6},  {'g', 7},
    {'h', 8},  {'i', 9},  {'j', 10}, {'k', 11}, {'l', 12}, {'m', 13}, {'n', 14},
    {'o', 15}, {'p', 16}, {'q', 17}, {'r', 18}, {'s', 19}, {'t', 20}, {'u', 21},
    {'v', 22}, {'w', 23}, {'x', 24}, {'y', 25}, {'z', 26}};

/**
 * @brief A1Z26加密的实现
 * @param text 是输入的明文
 * @returns 编码后的字符串，字母之间用短横线分隔
 */
std::string encrypt(std::string text) {
    std::string result;
    std::transform(text.begin(), text.end(), text.begin(),
                   ::tolower);  // 将字符串转换为小写
    std::replace(text.begin(), text.end(), ':', ' ');
    for (char letter : text) {
        if (letter != ' ') {
            result += std::to_string(
                a1z26_encrypt_map[letter]);  // 将整数转换为字符串并追加到结果中
            result += "-";  // 用短横线分隔每组数字
        } else {
            result.pop_back();
            result += ' ';
        }
    }
    result.pop_back();  // 移除开头的短横线
    return result;
}

/**
 * @brief A1Z26解密的实现
 * @param text 是输入的加密文本
 * @param bReturnUppercase 指定解码后的字符串是否为大写
 * @returns 解密后的字符串，全部为大写或小写
 */
std::string decrypt(const std::string& text, bool bReturnUppercase = false) {
    std::string result;

    // 将用空格分隔的单词分割到一个向量数组中
    std::vector<std::string> word_array;
    std::stringstream sstream(text);
    std::string word;
    while (sstream >> word) {
        word_array.push_back(word);
    }

    for (auto& i : word_array) {
        std::replace(i.begin(), i.end(), '-', ' ');
        std::vector<std::string> text_array;

        std::stringstream ss(i);
        std::string res_text;
        while (ss >> res_text) {
            text_array.push_back(res_text);
        }

        for (auto& i : text_array) {
            result += a1z26_decrypt_map[stoi(i)];
        }

        result += ' ';
    }
    result.pop_back();  // 移除多余的空格

    if (bReturnUppercase) {
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    }
    return result;
}

}  // namespace a1z26
}  // namespace ciphers

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    // 第一个测试
    std::string input = "Hello World";
    std::string expected = "8-5-12-12-15 23-15-18-12-4";
    std::string output = ciphers::a1z26::encrypt(input);

    std::cout << "输入: " << input << std::endl;
    std::cout << "预期: " << expected << std::endl;
    std::cout << "输出: " << output << std::endl;
    assert(output == expected);
    std::cout << "测试通过";

    // 第二个测试
    input = "12-15-23-5-18-3-1-19-5";
    expected = "lowercase";
    output = ciphers::a1z26::decrypt(input);

    std::cout << "输入: " << input << std::endl;
    std::cout << "预期: " << expected << std::endl;
    std::cout << "输出: " << output << std::endl;
    assert(output == expected);
    std::cout << "测试通过";

    // 第三个测试
    input = "21-16-16-5-18-3-1-19-5";
    expected = "UPPERCASE";
    output = ciphers::a1z26::decrypt(input, true);

    std::cout << "输入: " << input << std::endl;
    std::cout << "预期: " << expected << std::endl;
    std::cout << "输出: " << output << std::endl;
    assert(output == expected);
    std::cout << "测试通过";
}

/**
 * @brief 主函数
 * @returns 0 正常退出
 */
int main() {
    test();  // 运行自测实现
    return 0;
}
