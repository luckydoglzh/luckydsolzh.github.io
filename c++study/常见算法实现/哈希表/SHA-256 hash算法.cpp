/**
 * @file
 * @author [Md. Anisul Haque](https://github.com/mdanisulh)
 * @brief 简单的 C++ 实现 [SHA-256 哈希算法]
 * (https://en.wikipedia.org/wiki/SHA-2)
 *
 * @details
 * [SHA-2](https://en.wikipedia.org/wiki/SHA-2) 是一组由
 * [NSA](https://en.wikipedia.org/wiki/National_Security_Agency) 设计的
 * 加密哈希函数，首次发布于 2001 年。SHA-256 是 SHA-2 家族的一部分。
 * SHA-256 广泛用于软件包的认证和安全密码哈希。
 */

#include <array>     /// 用于 std::array
#include <cassert>   /// 用于 assert
#include <cstdint>   /// 用于 uint8_t, uint32_t 和 uint64_t 数据类型
#include <iomanip>   /// 用于 std::setfill 和 std::setw
#include <iostream>  /// 用于输入输出操作
#include <sstream>   /// 用于 std::stringstream
#include <utility>   /// 用于 std::move
#include <vector>    /// 用于 std::vector

/**
 * @namespace hashing
 * @brief 哈希算法
 */
namespace hashing {
/**
 * @namespace SHA-256
 * @brief 实现 [SHA-256](https://en.wikipedia.org/wiki/SHA-2) 算法的函数
 */
namespace sha256 {
/**
 * @class Hash
 * @brief 包含哈希数组及其更新和转换为十六进制字符串的函数
 */
class Hash {
    // 使用前 8 个质数（2..19）的平方根的小数部分的前 32 位初始化哈希值数组
    std::array<uint32_t, 8> hash = {0x6A09E667, 0xBB67AE85, 0x3C6EF372,
                                    0xA54FF53A, 0x510E527F, 0x9B05688C,
                                    0x1F83D9AB, 0x5BE0CD19};

 public:
    void update(const std::array<uint32_t, 64> &blocks);
    std::string to_string() const;
};

/**
 * @brief 右旋转 32 位无符号整数的位
 * @param n 要旋转的整数
 * @param rotate 旋转的位数
 * @return uint32_t 旋转后的整数
 */
uint32_t right_rotate(uint32_t n, size_t rotate) {
    return (n >> rotate) | (n << (32 - rotate));
}

/**
 * @brief 更新哈希数组
 * @param blocks 消息调度数组
 * @return void
 */
void Hash::update(const std::array<uint32_t, 64> &blocks) {
    // 使用前 64 个质数（2..311）的小数部分的前 32 位初始化轮常量数组
    const std::array<uint32_t, 64> round_constants = {
        0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1,
        0x923F82A4, 0xAB1C5ED5, 0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
        0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174, 0xE49B69C1, 0xEFBE4786,
        0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
        0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147,
        0x06CA6351, 0x14292967, 0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
        0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85, 0xA2BFE8A1, 0xA81A664B,
        0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
        0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A,
        0x5B9CCA4F, 0x682E6FF3, 0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
        0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2};

    // 初始化工作变量
    auto a = hash[0];
    auto b = hash[1];
    auto c = hash[2];
    auto d = hash[3];
    auto e = hash[4];
    auto f = hash[5];
    auto g = hash[6];
    auto h = hash[7];

    // 压缩函数主循环
    for (size_t block_num = 0; block_num < 64; ++block_num) {
        const auto s1 =
            right_rotate(e, 6) ^ right_rotate(e, 11) ^ right_rotate(e, 25);
        const auto ch = (e & f) ^ (~e & g);
        const auto temp1 =
            h + s1 + ch + round_constants[block_num] + blocks[block_num];
        const auto s0 =
            right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22);
        const auto maj = (a & b) ^ (a & c) ^ (b & c);
        const auto temp2 = s0 + maj;

        // 更新工作变量
        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    // 更新哈希值
    hash[0] += a;
    hash[1] += b;
    hash[2] += c;
    hash[3] += d;
    hash[4] += e;
    hash[5] += f;
    hash[6] += g;
    hash[7] += h;
}

/**
 * @brief 将哈希值转换为十六进制字符串
 * @return std::string 最终哈希值
 */
std::string Hash::to_string() const {
    std::stringstream ss;
    for (size_t i = 0; i < 8; ++i) {
        ss << std::hex << std::setfill('0') << std::setw(8) << hash[i];
    }
    return ss.str();
}

/**
 * @brief 计算填充输入的大小
 * @param input 输入字符串
 * @return size_t 填充后的输入大小
 */
std::size_t compute_padded_size(const std::size_t input_size) {
    if (input_size % 64 < 56) {
        return input_size + 64 - (input_size % 64);
    }
    return input_size + 128 - (input_size % 64);
}

/**
 * @brief 返回 in_value 中 byte_num 位置的字节
 * @param in_value 输入值
 * @param byte_num 要返回的字节的位置
 * @return uint8_t 位置为 byte_num 的字节
 */
template <typename T>
uint8_t extract_byte(const T in_value, const std::size_t byte_num) {
    if (sizeof(in_value) <= byte_num) {
        throw std::out_of_range("Byte at index byte_num does not exist");
    }
    return (in_value >> (byte_num * 8)) & 0xFF;
}

/**
 * @brief 返回填充后输入位置 pos 的字符
 * @param input 输入字符串
 * @param pos 要返回的字符的位置
 * @return char 填充字符串中索引 pos 的字符
 */
char get_char(const std::string &input, std::size_t pos) {
    const auto input_size = input.length();
    if (pos < input_size) {
        return input[pos];
    }
    if (pos == input_size) {
        return '\x80';  // 填充位
    }
    const auto padded_input_size = compute_padded_size(input_size);
    if (pos < padded_input_size - 8) {
        return '\x00';  // 填充零
    }
    if (padded_input_size <= pos) {
        throw std::out_of_range("pos is out of range");
    }
    return static_cast<char>(
        extract_byte<size_t>(input_size * 8, padded_input_size - pos - 1));
}

/**
 * @brief 创建消息调度数组
 * @param input 输入字符串
 * @param byte_num 块的第一个字节的位置
 * @return std::array<uint32_t, 64> 消息调度数组
 */
std::array<uint32_t, 64> create_message_schedule_array(const std::string &input,
                                                       const size_t byte_num) {
    std::array<uint32_t, 64> blocks{};

    // 将块复制到消息调度数组的前 16 个字
    for (size_t block_num = 0; block_num < 16; ++block_num) {
        blocks[block_num] =
            (static_cast<uint8_t>(get_char(input, byte_num + block_num * 4))
             << 24) |
            (static_cast<uint8_t>(get_char(input, byte_num + block_num * 4 + 1))
             << 16) |
            (static_cast<uint8_t>(get_char(input, byte_num + block_num * 4 + 2))
             << 8) |
            static_cast<uint8_t>(get_char(input, byte_num + block_num * 4 + 3));
    }

    // 将前 16 个字扩展到消息调度数组的剩余 48 个字
    for (size_t block_num = 16; block_num < 64; ++block_num) {
        const auto s0 = right_rotate(blocks[block_num - 15], 7) ^
                        right_rotate(blocks[block_num - 15], 18) ^
                        (blocks[block_num - 15] >> 3);
        const auto s1 = right_rotate(blocks[block_num - 2], 17) ^
                        right_rotate(blocks[block_num - 2], 19) ^
                        (blocks[block_num - 2] >> 10);
        blocks[block_num] =
            blocks[block_num - 16] + s0 + blocks[block_num - 7] + s1;
    }

    return blocks;
}

/**
 * @brief 计算最终哈希值
 * @param input 输入字符串
 * @return std::string 最终哈希值
 */
std::string sha256(const std::string &input) {
    Hash h;
    // 以 512 位（64 字节）为单位处理消息
    for (size_t byte_num = 0; byte_num < compute_padded_size(input.length());
         byte_num += 64) {
        h.update(create_message_schedule_array(input, byte_num));
    }
    return h.to_string();
}
}  // namespace sha256
}  // namespace hashing

/**
 * @brief 自测试实现
 * @returns void
 */
static void test_compute_padded_size() {
    assert(hashing::sha256::compute_padded_size(55) == 64);
    assert(hashing::sha256::compute_padded_size(56) == 128);
    assert(hashing::sha256::compute_padded_size(130) == 192);
}

static void test_extract_byte() {
    assert(hashing::sha256::extract_byte<uint32_t>(512, 0) == 0);
    assert(hashing::sha256::extract_byte<uint32_t>(512, 1) == 2);
    bool exception = false;
    try {
        hashing::sha256::extract_byte<uint32_t>(512, 5);
    } catch (const std::out_of_range &) {
        exception = true;
    }
    assert(exception);
}

static void test_get_char() {
    assert(hashing::sha256::get_char("test", 3) == 't');
    assert(hashing::sha256::get_char("test", 4) == '\x80');
    assert(hashing::sha256::get_char("test", 5) == '\x00');
    assert(hashing::sha256::get_char("test", 63) == 32);
    bool exception = false;
    try {
        hashing::sha256::get_char("test", 64);
    } catch (const std::out_of_range &) {
        exception = true;
    }
    assert(exception);
}

static void test_right_rotate() {
    assert(hashing::sha256::right_rotate(128, 3) == 16);
    assert(hashing::sha256::right_rotate(1, 30) == 4);
    assert(hashing::sha256::right_rotate(6, 30) == 24);
}

static void test_sha256() {
    struct TestCase {
        const std::string input;
        const std::string expected_hash;
        TestCase(std::string input, std::string expected_hash)
            : input(std::move(input)),
              expected_hash(std::move(expected_hash)) {}
    };
    const std::vector<TestCase> test_cases{
        TestCase(
            "",
            "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"),
        TestCase(
            "test",
            "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08"),
        TestCase(
            "Hello World",
            "a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e"),
        TestCase("Hello World!",
                 "7f83b1657ff1fc53b92dc18148a1d65dfc2d4b1fa3d677284addd200126d9"
                 "069")};
    for (const auto &tc : test_cases) {
        assert(hashing::sha256::sha256(tc.input) == tc.expected_hash);
    }
}

static void test() {
    test_compute_padded_size();
    test_extract_byte();
    test_get_char();
    test_right_rotate();
    test_sha256();

    std::cout << "所有测试成功通过！\n";
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    test();  // 运行自测试实现
    return 0;
}
