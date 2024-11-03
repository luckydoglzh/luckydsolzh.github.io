/**
 * @file
 * @author [tGautot](https://github.com/tGautot)
 * @brief 简单的C++实现[SHA-1哈希算法](https://en.wikipedia.org/wiki/SHA-1)
 *
 * @details
 * [SHA-1](https://en.wikipedia.org/wiki/SHA-1)是一种加密哈希函数，
 * 由[NSA](https://en.wikipedia.org/wiki/National_Security_Agency)于1995年开发。
 * 自2010年起，SHA-1不再被认为是安全的。
 *
 * ### 算法
 * 算法的第一步是对消息进行填充，使其长度成为64的倍数（字节）。首先添加0x80（10000000），
 * 然后填充零，直到最后8个字节必须填充，最后添加输入的64位大小。
 *
 * 一旦完成，该算法将填充的消息分成64字节的块。每个块用于一个*轮次*，轮次将块分解为16个4字节的块。
 * 这16个块随后通过XOR运算扩展到80个块（具体细节请参见代码）。
 * 算法将使用之前构建的块的特殊函数计算的部分哈希来更新其160位状态（这里用5个32位整数表示）。
 * 有关这些操作的更多细节，请参阅[维基百科文章](https://en.wikipedia.org/wiki/SHA-1#SHA-1_pseudocode)。
 * @note 这是一个简单的字节字符串实现，但某些实现可以处理字节流和未知长度的消息。
 */

#include <algorithm>  /// 用于std::copy
#include <array>      /// 用于std::array
#include <cassert>    /// 用于assert
#include <cstring>    /// 用于std::memcpy
#include <iostream>   /// 用于IO操作
#include <string>     /// 用于字符串
#include <vector>     /// 用于std::vector

/**
 * @namespace hashing
 * @brief 哈希算法
 */
namespace hashing {
/**
 * @namespace SHA-1
 * @brief 实现[SHA-1](https://en.wikipedia.org/wiki/SHA-1)算法的函数
 */
namespace sha1 {
/**
 * @brief 旋转32位无符号整数的位
 * @param n 要旋转的整数
 * @param rotate 旋转的位数
 * @return uint32_t 旋转后的整数
 */
uint32_t leftRotate32bits(uint32_t n, std::size_t rotate) {
    return (n << rotate) | (n >> (32 - rotate));
}

/**
 * @brief 将160位SHA-1签名转换为40字符的十六进制字符串
 * @param sig SHA-1签名（预期为20字节）
 * @return std::string 十六进制签名
 */
std::string sig2hex(void* sig) {
    const char* hexChars = "0123456789abcdef";
    auto* intsig = static_cast<uint8_t*>(sig);
    std::string hex = "";
    for (uint8_t i = 0; i < 20; i++) {
        hex.push_back(hexChars[(intsig[i] >> 4) & 0xF]);
        hex.push_back(hexChars[(intsig[i]) & 0xF]);
    }
    return hex;
}

/**
 * @brief SHA-1算法本身，接收字节字符串
 * @param input_bs 要哈希的字节字符串
 * @param input_size 输入的大小（以字节为单位）
 * @return void* 指向160位签名的指针
 */
void* hash_bs(const void* input_bs, uint64_t input_size) {
    auto* input = static_cast<const uint8_t*>(input_bs);

    // 步骤0：初始化160位状态
    uint32_t h0 = 0x67452301, a = 0;
    uint32_t h1 = 0xEFCDAB89, b = 0;
    uint32_t h2 = 0x98BADCFE, c = 0;
    uint32_t h3 = 0x10325476, d = 0;
    uint32_t h4 = 0xC3D2E1F0, e = 0;

    // 步骤1：处理字节字符串
    // 首先计算填充消息的大小，以便分配正确的内存
    uint64_t padded_message_size = 0;
    if (input_size % 64 < 56) {
        padded_message_size = input_size + 64 - (input_size % 64);
    } else {
        padded_message_size = input_size + 128 - (input_size % 64);
    }

    // 为填充消息分配内存
    std::vector<uint8_t> padded_message(padded_message_size);

    // 填充消息的开始是原始消息
    std::copy(input, input + input_size, padded_message.begin());

    // 接下来是一个1位，后面是零
    padded_message[input_size] = 1 << 7;  // 10000000
    for (uint64_t i = input_size; i % 64 != 56; i++) {
        if (i == input_size) {
            continue;  // 跳过第一次迭代
        }
        padded_message[i] = 0;
    }

    // 然后将消息的64位大小（因此是乘以8）添加到最后8个字节
    uint64_t input_bitsize = input_size * 8;
    for (uint8_t i = 0; i < 8; i++) {
        padded_message[padded_message_size - 8 + i] =
            (input_bitsize >> (56 - 8 * i)) & 0xFF;
    }

    // 为块分配内存
    std::array<uint32_t, 80> blocks{};

    // 轮次
    for (uint64_t chunk = 0; chunk * 64 < padded_message_size; chunk++) {
        // 首先，从块中构建16个32位块
        for (uint8_t bid = 0; bid < 16; bid++) {
            blocks[bid] = 0;

            // 从4位单词构建32位单词
            // 添加每个并向左移动
            for (uint8_t cid = 0; cid < 4; cid++) {
                blocks[bid] = (blocks[bid] << 8) +
                              padded_message[chunk * 64 + bid * 4 + cid];
            }

            // 将16个32位单词扩展到80个32位单词
            for (uint8_t i = 16; i < 80; i++) {
                blocks[i] =
                    leftRotate32bits(blocks[i - 3] ^ blocks[i - 8] ^
                                         blocks[i - 14] ^ blocks[i - 16],
                                     1);
            }
        }

        a = h0;
        b = h1;
        c = h2;
        d = h3;
        e = h4;

        // 主“哈希”循环
        for (uint8_t i = 0; i < 80; i++) {
            uint32_t F = 0, g = 0;
            if (i < 20) {
                F = (b & c) | ((~b) & d);
                g = 0x5A827999;
            } else if (i < 40) {
                F = b ^ c ^ d;
                g = 0x6ED9EBA1;
            } else if (i < 60) {
                F = (b & c) | (b & d) | (c & d);
                g = 0x8F1BBCDC;
            } else {
                F = b ^ c ^ d;
                g = 0xCA62C1D6;
            }

            // 更新累加器
            uint32_t temp = leftRotate32bits(a, 5) + F + e + g + blocks[i];
            e = d;
            d = c;
            c = leftRotate32bits(b, 30);
            b = a;
            a = temp;
        }
        // 用这个块的哈希更新状态
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    // 从状态构建签名
    // 注意，签名可以使用任何类型
    // 使用uint8_t使20个字节明显
    auto* sig = new uint8_t[20];
    for (uint8_t i = 0; i < 4; i++) {
        sig[i] = (h0 >> (24 - 8 * i)) & 0xFF;
        sig[i + 4] = (h1 >> (24 - 8 * i)) & 0xFF;
        sig[i + 8] = (h2 >> (24 - 8 * i)) & 0xFF;
        sig[i + 12] = (h3 >> (24 - 8 * i)) & 0xFF;
        sig[i + 16] = (h4 >> (24 - 8 * i)) & 0xFF;
    }

    return sig;
}

/**
 * @brief 将字符串转换为字节字符串并调用主算法
 * @param message 要哈希的普通字符消息
 * @return void* 指向SHA-1签名的指针
 */
void* hash(const std::string& message) {
    return hash_bs(&message[0], message.size());
}
}  // namespace sha1
}  // namespace hashing

/**
 * @brief 自测试已知的SHA-1哈希值实现
 * @returns void
 */
static void test() {
    // 哈希空字符串并存储签名
    void* sig = hashing::sha1::hash("");
    std::cout << "哈希空字符串" << std::endl;
    // 打印签名的十六进制表示
    std::cout << hashing::sha1::sig2hex(sig) << std::endl << std::endl;
    // 使用assert测试签名是否与预期值相符
    assert(hashing::sha1::sig2hex(sig).compare(
               "da39a3ee5e6b4b0d3255bfef95601890afd80709") == 0);

    // 哈希"The quick brown fox jumps over the lazy dog"并存储签名
    void* sig2 =
        hashing::sha1::hash("The quick brown fox jumps over the lazy dog");
    std::cout << "哈希 The quick brown fox jumps over the lazy dog"
              << std::endl;
    // 打印签名的十六进制表示
    std::cout << hashing::sha1::sig2hex(sig2) << std::endl << std::endl;
    // 使用assert测试签名是否与预期值相符
    assert(hashing::sha1::sig2hex(sig2).compare(
               "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12") == 0);

    // 哈希"The quick brown fox jumps over the lazy dog."（注意附加的句号）并存储签名
    void* sig3 =
        hashing::sha1::hash("The quick brown fox jumps over the lazy dog.");
    std::cout << "哈希 The quick brown fox jumps over the lazy dog."
              << std::endl;
    // 打印签名的十六进制表示
    std::cout << hashing::sha1::sig2hex(sig3) << std::endl << std::endl;
    // 使用assert测试签名是否与预期值相符
    assert(hashing::sha1::sig2hex(sig3).compare(
               "408d94384216f890ff7a0c3528e8bed1e0b01621") == 0);

    // 哈希"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"并存储签名
    void* sig4 = hashing::sha1::hash(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    std::cout
        << "哈希 "
           "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
        << std::endl;
    // 打印签名的十六进制表示
    std::cout << hashing::sha1::sig2hex(sig4) << std::endl << std::endl;
    // 使用assert测试签名是否与预期值相符
    assert(hashing::sha1::sig2hex(sig4).compare(
               "761c457bf73b14d27e9e9265c46f4b4dda11f940") == 0);
}

/**
 * @brief 进入一个循环，允许用户输入消息并计算SHA-1哈希
 * @returns void
 */
static void interactive() {
    while (true) {
        std::string input;
        std::cout << "请输入要哈希的消息（按Ctrl-C退出）：" << std::endl;
        std::getline(std::cin, input);
        void* sig = hashing::sha1::hash(input);
        std::cout << "哈希结果是：" << hashing::sha1::sig2hex(sig) << std::endl;

        while (true) {
            std::cout << "想要输入另一条消息吗？（y/n）";
            std::getline(std::cin, input);
            if (input.compare("y") == 0) {
                break;
            } else if (input.compare("n") == 0) {
                return;
            }
        }
    }
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    test();  // 运行自测试实现

    // 启动交互模式，用户可以输入消息并查看它们的哈希
    interactive();
    return 0;
}
