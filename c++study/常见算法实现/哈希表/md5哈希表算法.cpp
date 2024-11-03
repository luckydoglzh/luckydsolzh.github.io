/**
 * @file
 * @author [tGautot](https://github.com/tGautot)
 * @brief 简单的C++实现 [MD5哈希算法](https://en.wikipedia.org/wiki/MD5)
 * @details
 * [MD5算法](https://en.wikipedia.org/wiki/MD5) 是一个哈希算法，
 * 由 [Ronal Rivest](https://en.wikipedia.org/wiki/Ron_Rivest) 于1991年设计。
 *
 * MD5是使用最广泛的哈希算法之一。一些使用案例包括：
 *  1. 提供下载软件的校验和
 *  2. 存储加盐密码
 *
 * 然而，MD5在很长一段时间内被认为在加密上存在弱点，但它仍然被广泛使用。
 * 这一弱点在2012年被 [Flame恶意软件](https://en.wikipedia.org/wiki/Flame_(malware)) 利用。
 *
 * ### 算法
 * 首先，所有值都应以[小端序](https://en.wikipedia.org/wiki/Endianness)存储。
 * 这在将字节字符串的一部分用作整数时尤为重要。
 *
 * 算法的第一步是对消息进行填充，使其长度成为64（字节）的倍数。
 * 这通过首先添加0x80（10000000），然后添加零，直到最后8字节需要填充，
 * 最后再添加输入的64位大小。
 *
 * 完成后，算法将这个填充消息分解为64字节的块。
 * 每个块用于一个“轮次”，一轮将块分成16个4字节的块。
 * 在这些轮次中，算法将更新其128位状态（由4个整数：A、B、C、D表示）。
 * 有关这些操作的更多详细信息，请参见[维基百科文章](https://en.wikipedia.org/wiki/MD5#Algorithm)。
 * MD5给出的签名是所有轮次完成后的128位状态。
 * @note 这是一个简单的字节字符串实现，但某些实现可以处理字节流、未知长度的消息。
 */

#include <algorithm>  /// 用于std::copy
#include <array>      /// 用于std::array
#include <cassert>    /// 用于assert
#include <cstring>    /// 用于std::memcpy
#include <iostream>   /// 用于输入输出操作
#include <string>     /// 用于字符串
#include <vector>     /// 用于std::vector

/**
 * @namespace hashing
 * @brief 哈希算法
 */
namespace hashing {
/**
 * @namespace MD5
 * @brief [MD5](https://en.wikipedia.org/wiki/MD5) 算法实现的函数
 */
namespace md5 {
/**
 * @brief 旋转32位无符号整数的位
 * @param n 需要旋转的整数
 * @param rotate 旋转的位数
 * @return uint32_t 旋转后的整数
 */
uint32_t leftRotate32bits(uint32_t n, std::size_t rotate) {
    return (n << rotate) | (n >> (32 - rotate));
}

/**
 * @brief 检查整数是以大端序存储还是小端序
 * @note 来自 [this](https://stackoverflow.com/a/1001373) StackOverflow帖子
 * @return true 如果检测到整数为大端序
 * @return false 如果检测到整数为小端序
 */
bool isBigEndian() {
    union {
        uint32_t i;
        std::array<char, 4> c;
    } bint = {0x01020304};

    return bint.c[0] == 1;
}

/**
 * @brief 将32位整数转换为小端序（如有必要）
 * @param n 需要转换的小端序数（uint32_t）
 * @return uint32_t 小端序的n
 */
uint32_t toLittleEndian32(uint32_t n) {
    if (!isBigEndian()) {
        return ((n << 24) & 0xFF000000) | ((n << 8) & 0x00FF0000) |
               ((n >> 8) & 0x0000FF00) | ((n >> 24) & 0x000000FF);
    }
    // 机器使用小端序，无需更改
    return n;
}

/**
 * @brief 将64位整数转换为小端序（如有必要）
 * @param n 需要转换的小端序数（uint64_t）
 * @return uint64_t 小端序的n
 */
uint64_t toLittleEndian64(uint64_t n) {
    if (!isBigEndian()) {
        return ((n << 56) & 0xFF00000000000000) |
               ((n << 40) & 0x00FF000000000000) |
               ((n << 24) & 0x0000FF0000000000) |
               ((n << 8) & 0x000000FF00000000) |
               ((n >> 8) & 0x00000000FF000000) |
               ((n >> 24) & 0x0000000000FF0000) |
               ((n >> 40) & 0x000000000000FF00) |
               ((n >> 56) & 0x00000000000000FF);
    }
    // 机器使用小端序，无需更改
    return n;
}

/**
 * @brief 将128位MD5签名转换为32个字符的十六进制字符串
 * @param sig MD5签名（期望为16字节）
 * @return std::string 十六进制签名
 */
std::string sig2hex(void* sig) {
    const char* hexChars = "0123456789abcdef";
    auto* intsig = static_cast<uint8_t*>(sig);
    std::string hex = "";
    for (uint8_t i = 0; i < 16; i++) {
        hex.push_back(hexChars[(intsig[i] >> 4) & 0xF]);
        hex.push_back(hexChars[(intsig[i]) & 0xF]);
    }
    return hex;
}

/**
 * @brief MD5算法本身，接受字节字符串
 * @param input_bs 需要哈希的字节字符串
 * @param input_size 输入的大小（以字节为单位）
 * @return void* 指向128位签名的指针
 */
void* hash_bs(const void* input_bs, uint64_t input_size) {
    auto* input = static_cast<const uint8_t*>(input_bs);

    // 步骤0：初始数据（这些是在MD5协议中确定的）
    // s是每轮左旋转时使用的移位值
    std::array<uint32_t, 64> s = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    // K是每轮使用的伪随机值
    // 这些值可以通过以下Python代码获得：
    /**
     * @brief K的值是伪随机的，用于“盐”每一轮
     * 这些值可以通过以下Python代码获得
     * @code{.py}
     * from math import floor, sin
     *
     * for i in range(64):
     *     print(floor(2**32 * abs(sin(i+1))))
     * @endcode
     */
    std::array<uint32_t, 64> K = {
        3614090360, 3905402710, 606105819,  3250441966, 4118548399, 1200080426,
        2821735955, 4249261313, 1770035416, 2336552879, 4294925233, 2304563134,
        1804603682, 4254626195, 2792965006, 1236535329, 4129170786, 3225465664,
        643717713,  3921069994, 3593408605, 38016083,   3634488961, 3889429448,
        568446438,  3275163606, 4107603335, 1163531501, 2850285829, 4243851484,
        1732584193, 4023233417, 2562383102, 271733878,  3285377520, 3225465664};

    // 初始化4个128位整数
    std::array<uint32_t, 4> hash = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};

    // 步骤1：填充输入
    // 填充输入消息，以便其长度是448模512
    uint64_t original_size = input_size;
    // 填充字节数组：0x80，后跟0（长度为448 mod 512）
    uint64_t padded_size = original_size * 8 + 1;  // 1表示添加0x80
    padded_size += (448 - (padded_size % 512)) % 448;  // 填充0
    padded_size /= 8;  // 转换为字节

    // 现在添加64位大小
    std::vector<uint8_t> padded_input(padded_size + 8);
    std::copy(input, input + original_size, padded_input.begin());
    padded_input[original_size] = 0x80;  // 添加0x80

    // 在填充结束时添加长度
    for (int i = 0; i < 8; ++i) {
        padded_input[original_size + 1 + i] = (original_size * 8) >> (i * 8);
    }

    // 步骤2：处理每个512位（64字节）的块
    for (size_t i = 0; i < padded_input.size(); i += 64) {
        auto* block = reinterpret_cast<uint32_t*>(&padded_input[i]);

        // 在处理时将A、B、C、D的值分别设为hash中的相应值
        uint32_t A = hash[0];
        uint32_t B = hash[1];
        uint32_t C = hash[2];
        uint32_t D = hash[3];

        // 进行64轮处理
        for (size_t j = 0; j < 64; ++j) {
            uint32_t F, g;

            // 确定F函数
            if (j < 16) {
                F = (B & C) | (~B & D);
                g = j;
            } else if (j < 32) {
                F = (D & B) | (~D & C);
                g = (5 * j + 1) % 16;
            } else if (j < 48) {
                F = B ^ C ^ D;
                g = (3 * j + 5) % 16;
            } else {
                F = C ^ (B | ~D);
                g = (7 * j) % 16;
            }

            // 更新D
            F += A + K[j] + block[g];
            A = D;
            D = C;
            C = B;
            B += leftRotate32bits(F, s[j]);
        }

        // 更新hash
        hash[0] += A;
        hash[1] += B;
        hash[2] += C;
        hash[3] += D;
    }

    // 步骤3：生成输出
    for (auto& val : hash) {
        val = toLittleEndian32(val);  // 确保是小端序
    }
    return std::memcpy(new uint8_t[16], hash.data(), 16);  // 返回128位（16字节）
}

/**
 * @brief 将给定字符串转换为其MD5哈希值
 * @param input 需要哈希的输入字符串
 * @return std::string 字符串的MD5哈希值
 */
std::string hash(const std::string& input) {
    return sig2hex(hash_bs(input.data(), input.size()));
}
}  // namespace md5
}  // namespace hashing

/**
 * @brief 主函数：演示MD5哈希
 */
int main() {
    std::string input = "hello world";
    std::cout << "MD5(\"" << input << "\") = " << hashing::md5::hash(input) << std::endl;
    return 0;
}
