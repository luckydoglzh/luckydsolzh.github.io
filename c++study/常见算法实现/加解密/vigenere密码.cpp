/**
 * @file vigenere_cipher.cpp
 * @brief 实现 [Vigenère cipher](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher) 算法。
 *
 * @details
 * Vigenère 密码是一种通过使用关键字的字母系列对字母文本进行加密的方法。它采用一种多重替换的方法。
 *
 * ### 算法
 * 加密也可以通过模运算来表示，首先将字母转换为数字，按照方案 A → 0, B → 1, ..., Z → 25。
 * 用数学形式表示，第 \f{i^{th}}\f$ 字符在消息 M 中的加密可以描述为：
 * 
 * \f[ E_{K}(M_{i}) = (M_{i} + K_{i})\;\mbox{mod}\; 26\f]
 * 
 * 而对密文 C 中第 \f{i^{th}}\f$ 字符的解密可以描述为：
 *
 * \f[ D_{k}(C_{i}) = (C_{i} - K_{i} + 26)\;\mbox{mod}\; 26\f]
 * 
 * 其中 \f$K_{i}\f$ 表示关键字中的相应字符。如果 \f$|key| < |text|\f$，则同一个关键字会重复，直到它们的长度相等。
 * 
 * 例如，
 * 如果 M = "ATTACKATDAWN" 且 K = "LEMON"，那么 K 变为 "LEMONLEMONLE"。
 * 
 * \note 与其创建相等长度的新关键字，该程序通过使用关键字的模索引来实现（即 \f$(j + 1) \;\mbox{mod}\; |\mbox{key}|\f$）
 * 
 * \note 此程序仅实现对大写英语字母字符（即 A-Z）的 Vigenère 密码。 
 * 
 * @author [Deep Raval](https://github.com/imdeep2905)
 */
#include <iostream>
#include <string>
#include <cassert>

/** \namespace ciphers
 * \brief 加密和解密算法
 */
namespace ciphers {
    /** \namespace vigenere
     * \brief [Vigenère cipher](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher) 算法的函数。
     */
    namespace vigenere {   
        namespace {
            /**
             * 该函数根据给定的值找到对应的字符（即 A-Z）
             * @param x 要查找字符的值 
             * @return 返回对应于特定值的字符
             */        
            inline char get_char(const int x) {
                // 通过加 65 将 0-25 映射到 65-90。
                // 这些实际上是 A-Z 的 ASCII 值。 
                return char(x + 65); 
            }
            /**
             * 该函数找到给定字符的值（即 0-25）
             * @param c 要查找值的字符
             * @return 返回对应于特定字符的值
             */  
            inline int get_value(const char c) {
                // A-Z 的 ASCII 值范围在 65-90 之间。
                // 因此，减去 65 将它们映射到 0-25。
                return int(c - 65);
            }
        } // 无名命名空间
        /**
         * 使用 Vigenère 密码加密给定文本。
         * @param text 要加密的文本
         * @param key 用于加密的关键字
         * @return 新的加密文本
         */
        std::string encrypt(const std::string &text, const std::string &key) {
            std::string encrypted_text = ""; // 用于存储加密文本的空字符串
            // 遍历文本和关键字的每个字符
            // 注意：关键字以循环方式访问，因此 j = (j + 1) % |key|
            for(size_t i = 0, j = 0; i < text.length(); i++, j = (j + 1) % key.length()) {
                int place_value_text = get_value(text[i]); // 获取文本字符的值
                int place_value_key = get_value(key[j]); // 获取关键字字符的值
                place_value_text = (place_value_text + place_value_key) % 26; // 应用加密
                char encrypted_char = get_char(place_value_text); // 从加密值获取新字符
                encrypted_text += encrypted_char; // 追加加密字符
            }
            return encrypted_text; // 返回加密文本
        }
        /**
         * 使用 Vigenère 密码解密给定文本。
         * @param text 要解密的文本
         * @param key 用于解密的关键字
         * @return 新的解密文本
         */        
        std::string decrypt(const std::string &text, const std::string &key) {
            // 遍历文本和关键字的每个字符
            // 注意：关键字以循环方式访问，因此 j = (j + 1) % |key|
            std::string decrypted_text = ""; // 用于存储解密文本的空字符串
            for(size_t i = 0, j = 0; i < text.length(); i++, j = (j + 1) % key.length()) {
                int place_value_text = get_value(text[i]); // 获取文本字符的值
                int place_value_key = get_value(key[j]); // 获取关键字字符的值
                place_value_text = (place_value_text - place_value_key + 26) % 26; // 应用解密
                char decrypted_char = get_char(place_value_text); // 从解密值获取新字符
                decrypted_text += decrypted_char; // 追加解密字符
            }        
            return decrypted_text; // 返回解密文本
        }
    } // 命名空间 vigenere
} // 命名空间 ciphers

/**
 * 测试上述算法的函数
 */
void test() {
    // 测试 1
    std::string text1 = "NIKOLATESLA";
    std::string encrypted1 = ciphers::vigenere::encrypt(text1, "TESLA");
    std::string decrypted1 = ciphers::vigenere::decrypt(encrypted1, "TESLA");
    assert(text1 == decrypted1); // 确保解密后的文本与原文本相同
    std::cout << "原始文本 : " << text1;
    std::cout << " , 加密文本（使用关键字 = TESLA） : " << encrypted1;
    std::cout << " , 解密文本 : " << decrypted1 << std::endl;

    // 测试 2
    std::string text2 = "GOOGLEIT";
    std::string encrypted2 = ciphers::vigenere::encrypt(text2, "REALLY");
    std::string decrypted2 = ciphers::vigenere::decrypt(encrypted2, "REALLY");
    assert(text2 == decrypted2); // 确保解密后的文本与原文本相同
    std::cout << "原始文本 : " << text2;
    std::cout << " , 加密文本（使用关键字 = REALLY） : " << encrypted2;
    std::cout << " , 解密文本 : " << decrypted2 << std::endl;
}

/** 主程序 */
int main() {
    // 测试
    test();
    return 0;
}
