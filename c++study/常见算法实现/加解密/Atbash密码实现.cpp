/**
 * @file
 * @brief [Atbash Cipher](https://en.wikipedia.org/wiki/Atbash) 实现
 * @details Atbash密码是一种替换密码，字母表中的字母按反序排列。
 * 例如，A 被替换为 Z，B 被替换为 Y，等等。
 *
 * ### 算法
 * 该算法接受一个字符串，并查找每个字母在反序字母表中的对应字母并替换之。
 * 空格被忽略，且大小写保持不变。
 *
 * @作者 [Focusucof](https://github.com/Focusucof)
 */
#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作
#include <map>       /// 用于 std::map
#include <string>    /// 用于 std::string

/** \namespace ciphers
 * \brief 加密和解密算法
 */
namespace ciphers {
/** \namespace atbash
 * \brief 用于 [Atbash
 * Cipher](https://en.wikipedia.org/wiki/Atbash) 的实现函数
 */
namespace atbash {
// Atbash 密码映射表
std::map<char, char> atbash_cipher_map = {
    {'a', 'z'}, {'b', 'y'}, {'c', 'x'}, {'d', 'w'}, {'e', 'v'}, {'f', 'u'},
    {'g', 't'}, {'h', 's'}, {'i', 'r'}, {'j', 'q'}, {'k', 'p'}, {'l', 'o'},
    {'m', 'n'}, {'n', 'm'}, {'o', 'l'}, {'p', 'k'}, {'q', 'j'}, {'r', 'i'},
    {'s', 'h'}, {'t', 'g'}, {'u', 'f'}, {'v', 'e'}, {'w', 'd'}, {'x', 'c'},
    {'y', 'b'}, {'z', 'a'}, {'A', 'Z'}, {'B', 'Y'}, {'C', 'X'}, {'D', 'W'},
    {'E', 'V'}, {'F', 'U'}, {'G', 'T'}, {'H', 'S'}, {'I', 'R'}, {'J', 'Q'},
    {'K', 'P'}, {'L', 'O'}, {'M', 'N'}, {'N', 'M'}, {'O', 'L'}, {'P', 'K'},
    {'Q', 'J'}, {'R', 'I'}, {'S', 'H'}, {'T', 'G'}, {'U', 'F'}, {'V', 'E'},
    {'W', 'D'}, {'X', 'C'}, {'Y', 'B'}, {'Z', 'A'}, {' ', ' '}

};

/**
 * @brief Atbash密码的加密和解密函数
 * @param text 要加密的明文
 * @returns 加密或解密后的字符串
 */
std::string atbash_cipher(const std::string& text) {
    std::string result;
    for (char letter : text) {
        result += atbash_cipher_map[letter];
    }
    return result;
}

}  // namespace atbash
}  // namespace ciphers

/**
 * @brief 自测函数
 * @returns void
 */
static void test() {
    // 第一个测试
    std::string text = "Hello World";
    std::string expected = "Svool Dliow";
    std::string encrypted_text = ciphers::atbash::atbash_cipher(text);
    std::string decrypted_text = ciphers::atbash::atbash_cipher(encrypted_text);
    assert(expected == encrypted_text);
    assert(text == decrypted_text);
    std::cout << "原文: " << text << std::endl;
    std::cout << "，预期文本: " << expected << std::endl;
    std::cout << "，加密文本: " << encrypted_text << std::endl;
    std::cout << "，解密文本: " << decrypted_text << std::endl;
    std::cout << "\n所有测试均已成功通过！\n";
}

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main() {
    test();  // 运行自测
    return 0;
}
