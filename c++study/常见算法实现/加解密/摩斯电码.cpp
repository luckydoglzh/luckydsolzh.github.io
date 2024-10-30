/**
 * @file
 * @author [Deep Raval](https://github.com/imdeep2905)
 *
 * @brief 实现 [摩尔斯电码](https://en.wikipedia.org/wiki/Morse_code)。
 *
 * @details
 * 摩尔斯电码是一种在电信中用于编码文本字符的方法，
 * 将文本字符编码为两个不同信号持续时间的标准化序列，称为点（dots）和划（dashes），或称为 dits 和 dahs。
 * 摩尔斯电码以电报发明者塞缪尔·摩尔斯的名字命名。
 */
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

/** \namespace ciphers
 * \brief 加密和解密算法
 */
namespace ciphers {
/** \namespace morse
 * \brief [摩尔斯电码](https://en.wikipedia.org/wiki/Morse_code)的函数
 */
namespace morse {
/**
 * 获取给定字符的摩尔斯电码表示。
 * @param c 字符
 * @returns 字符的摩尔斯电码表示字符串
 */
std::string char_to_morse(const char &c) {
    // 返回相应的摩尔斯电码
    switch (c) {
        case 'a':
            return ".-";
        case 'b':
            return "-...";
        case 'c':
            return "-.-.";
        case 'd':
            return "-..";
        case 'e':
            return ".";
        case 'f':
            return "..-.";
        case 'g':
            return "--.";
        case 'h':
            return "....";
        case 'i':
            return "..";
        case 'j':
            return ".---";
        case 'k':
            return "-.-";
        case 'l':
            return ".-..";
        case 'm':
            return "--";
        case 'n':
            return "-.";
        case 'o':
            return "---";
        case 'p':
            return ".--.";
        case 'q':
            return "--.-";
        case 'r':
            return ".-.";
        case 's':
            return "...";
        case 't':
            return "-";
        case 'u':
            return "..-";
        case 'v':
            return "...-";
        case 'w':
            return ".--";
        case 'x':
            return "-..-";
        case 'y':
            return "-.--";
        case 'z':
            return "--..";
        case '1':
            return ".----";
        case '2':
            return "..---";
        case '3':
            return "...--";
        case '4':
            return "....-";
        case '5':
            return ".....";
        case '6':
            return "-....";
        case '7':
            return "--...";
        case '8':
            return "---..";
        case '9':
            return "----.";
        case '0':
            return "-----";
        default:
            std::cerr << "发现无效字符: " << c << ' ' << std::endl;
            std::exit(0);
    }
}

/**
 * 从摩尔斯电码表示中获取字符。
 * @param s 摩尔斯电码表示
 * @returns 相应的字符
 */
char morse_to_char(const std::string &s) {
    // 返回相应的字符
    if (s == ".-") {
        return 'a';
    } else if (s == "-...") {
        return 'b';
    } else if (s == "-.-.") {
        return 'c';
    } else if (s == "-..") {
        return 'd';
    } else if (s == ".") {
        return 'e';
    } else if (s == "..-.") {
        return 'f';
    } else if (s == "--.") {
        return 'g';
    } else if (s == "....") {
        return 'h';
    } else if (s == "..") {
        return 'i';
    } else if (s == ".---") {
        return 'j';
    } else if (s == "-.-") {
        return 'k';
    } else if (s == ".-..") {
        return 'l';
    } else if (s == "--") {
        return 'm';
    } else if (s == "-.") {
        return 'n';
    } else if (s == "---") {
        return 'o';
    } else if (s == ".--.") {
        return 'p';
    } else if (s == "--.-") {
        return 'q';
    } else if (s == ".-.") {
        return 'r';
    } else if (s == "...") {
        return 's';
    } else if (s == "-") {
        return 't';
    } else if (s == "..-") {
        return 'u';
    } else if (s == "...-") {
        return 'v';
    } else if (s == ".--") {
        return 'w';
    } else if (s == "-..-") {
        return 'x';
    } else if (s == "-.--") {
        return 'y';
    } else if (s == "--..") {
        return 'z';
    } else if (s == ".----") {
        return '1';
    } else if (s == "..---") {
        return '2';
    } else if (s == "...--") {
        return '3';
    } else if (s == "....-") {
        return '4';
    } else if (s == ".....") {
        return '5';
    } else if (s == "-....") {
        return '6';
    } else if (s == "--...") {
        return '7';
    } else if (s == "---..") {
        return '8';
    } else if (s == "----.") {
        return '9';
    } else if (s == "-----") {
        return '0';
    } else {
        std::cerr << "发现无效摩尔斯电码: " << s << ' ' << std::endl;
        std::exit(0);
    }
}

/**
 * 使用摩尔斯电码加密给定文本。
 * @param text 要加密的文本
 * @returns 新的加密文本
 */
std::string encrypt(const std::string &text) {
    std::string encrypted_text = "";  // 存储加密文本的空字符串
    // 遍历文本的每个字符并将其转换为摩尔斯电码表示
    for (const char &c : text) {
        encrypted_text += ciphers::morse::char_to_morse(c) + " ";
    }
    return encrypted_text;  // 返回加密文本
}

/**
 * 解密给定的摩尔斯电码文本。
 * @param text 要解密的文本
 * @returns 新的解密文本
 */
std::string decrypt(const std::string &text) {
    // 遍历文本的每个字符并将其转换回正常表示
    std::string decrypted_text = "";  // 存储解密文本的空字符串
    // 使用空格作为分隔符分割字符串并存储在向量中
    std::size_t pos_start = 0, pos_end = 0, delim_len = 1;
    std::vector<std::string> splits;
    while ((pos_end = text.find(' ', pos_start)) != std::string::npos) {
        std::string token = text.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        splits.push_back(token);
    }

    // 遍历每个摩尔斯电码字符串
    for (const std::string &s : splits) {
        // 添加相应的字符
        decrypted_text += ciphers::morse::morse_to_char(s);
    }

    return decrypted_text;  // 返回解密文本
}
}  // namespace morse
}  // namespace ciphers

/**
 * @brief 测试上述算法的函数
 * @returns void
 */
static void test() {
    // 测试 1
    std::string text1 = "01234567890";
    std::string encrypted1 = ciphers::morse::encrypt(text1);
    std::string decrypted1 = ciphers::morse::decrypt(encrypted1);
    assert(text1 == decrypted1);
    std::cout << "原始文本 : " << text1 << std::endl;
    std::cout << "加密文本 : " << encrypted1 << std::endl;
    std::cout << "解密文本 : " << decrypted1 << std::endl;

    // 测试 2
    std::string text2 = "abcdefghijklmnopqrstuvwxyz";
    std::string encrypted2 = ciphers::morse::encrypt(text2);
    std::string decrypted2 = ciphers::morse::decrypt(encrypted2);
    assert(text2 == decrypted2);
    std::cout << "原始文本 : " << text2 << std::endl;
    std::cout << "加密文本 : " << encrypted2 << std::endl;
    std::cout << "解密文本 : " << decrypted2 << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main() {
    // 测试
    test();
    return 0;
}
