/**
 * @file hill_cipher.cpp
 * @brief 实现[希尔密码](https://en.wikipedia.org/wiki/Hill_cipher)算法。
 *
 * 该程序生成加密和解密密钥，并使用著名的块密码算法对ASCII文本进行加密和解密。这个强大的加密算法相对容易实现，给定密钥。算法的强度取决于块加密矩阵密钥的大小；矩阵越大，加密越强大，也就越难破解。然而，矩阵的重要要求是：
 * 1. 矩阵应可逆——满足所有逆转条件。
 * 2. 它的行列式与字符集长度之间不能有任何公因子。
 * 由于这个限制，大多数实现只使用较小的3x3加密密钥和小部分ASCII字母。
 *
 * 在当前实现中，我提供了一个生成更大加密密钥的实现（我尝试过最大为10x10），以及97个可打印字符的ASCII字符集。因此，典型的ASCII文本文件可以轻松地使用该模块加密。较大的字符集增加了密码的模数，因此矩阵的行列式可能会迅速变得非常大，导致它们不再定义。
 *
 * \note 本程序使用来自文件lu_decomposition.h的LU分解计算行列式
 * \note 矩阵生成算法非常简单，不保证生成可逆模矩阵。 \todo 更好的矩阵生成算法。
 *
 * @author [Krishna Vedala](https://github.com/kvedala)
 */

#include <cassert>
#include <cmath>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#ifdef _OPENMP
#include <omp.h>
#endif

#include "../numerical_methods/lu_decomposition.h"

/**
 * 用于打印矩阵的操作符
 */
template <typename T>
static std::ostream &operator<<(std::ostream &out, matrix<T> const &v) {
    const int width = 15; // 列宽
    const char separator = ' '; // 分隔符

    for (size_t row = 0; row < v.size(); row++) {
        for (size_t col = 0; col < v[row].size(); col++)
            out << std::left << std::setw(width) << std::setfill(separator)
                << v[row][col]; // 打印每个元素
        out << std::endl; // 换行
    }

    return out;
}

/** \namespace ciphers
 * \brief 加密和解密算法
 */
namespace ciphers {
/** 可加密和解密的字符字典 */
static const char *STRKEY =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789~!@#$%^&"
    "*()_+`-=[]{}|;':\",./<>?\\\r\n \0"; // 定义字符集

/**
 * @brief 实现[希尔密码](https://en.wikipedia.org/wiki/Hill_cipher)算法
 */
class HillCipher {
 private:
    /**
     * @brief 生成给定区间内的随机整数
     *
     * @param a 区间下限
     * @param b 区间上限
     * @tparam T 类型的输出
     * @return 在区间 \f$[a,b)\f$ 内的随机整数
     */
    template <typename T1, typename T2>
    static const T2 rand_range(T1 a, T1 b) {
        // 生成0到1之间的随机数
        long double r = static_cast<long double>(std::rand()) / RAND_MAX;

        // 缩放并返回随机数作为整数
        return static_cast<T2>(r * (b - a) + a);
    }

    /**
     * @brief 函数重载，用于在给定区间内用随机整数填充矩阵
     *
     * @param M 指向要填充随机数的矩阵的指针
     * @param a 区间下限
     * @param b 区间上限
     * @tparam T1 输入范围的类型
     * @tparam T2 矩阵的类型
     * @return 生成随机矩阵的行列式
     *
     * @warning 矩阵大小和随机数范围之间需要取得平衡。如果矩阵很大，随机数的范围必须小，以生成良定义的密钥；如果矩阵较小，随机数范围可以大一些。对于8x8的矩阵，范围不应超过 \f$[0,10]\f$。
     */
    template <typename T1, typename T2>
    static double rand_range(matrix<T2> *M, T1 a, T1 b) {
        for (size_t i = 0; i < M->size(); i++) {
            for (size_t j = 0; j < M[0][0].size(); j++) {
                M[0][i][j] = rand_range<T1, T2>(a, b);
            }
        }

        return determinant_lu(*M); // 返回矩阵的行列式
    }

    /**
     * @brief 使用欧几里得算法计算两个整数的[GCD](https://en.wikipedia.org/wiki/Greatest_common_divisor)
     *
     * @param a 第一个数
     * @param b 第二个数
     * @return \f$a\f$ 和 \f$b\f$ 的GCD
     */
    template <typename T>
    static const T gcd(T a, T b) {
        if (b > a)  // 确保始终是 a < b
            std::swap(a, b);

        while (b != 0) {
            T tmp = b;
            b = a % b;
            a = tmp;
        }

        return a;
    }

    /**
     * @brief 辅助函数，与加密或解密矩阵执行向量乘法
     *
     * @param vector 要乘的向量
     * @param key 加密或解密密钥矩阵
     * @return 对应的加密或解密文本
     */
    static const std::valarray<uint8_t> mat_mul(
        const std::valarray<uint8_t> &vector, const matrix<int> &key) {
        std::valarray<uint8_t> out(vector);  // 创建副本

        size_t L = std::strlen(STRKEY); // 获取字符集的长度

        for (size_t i = 0; i < key.size(); i++) {
            int tmp = 0;
            for (size_t j = 0; j < vector.size(); j++) {
                tmp += key[i][j] * vector[j]; // 进行矩阵乘法
            }
            out[i] = static_cast<uint8_t>(tmp % L); // 按模L计算
        }

        return out;
    }

    /**
     * @brief 获取::STRKEY中给定索引的字符
     *
     * @param idx 索引值
     * @return 在索引处的字符
     */
    static inline char get_idx_char(const uint8_t idx) { return STRKEY[idx]; }

    /**
     * @brief 获取::STRKEY中字符的索引
     *
     * @param ch 要查找的字符
     * @return 字符的索引
     */
    static inline uint8_t get_char_idx(const char ch) {
        size_t L = std::strlen(STRKEY);

        for (size_t idx = 0; idx <= L; idx++)
            if (STRKEY[idx] == ch)
                return idx;

        std::cerr << __func__ << ":" << __LINE__ << ": (" << ch
                  << ") 不应到达此处！\n";
        return 0; // 找不到时返回0
    }

    /**
     * @brief 便利函数，执行块密码操作。加密和解密的操作相同。
     *
     * @param text 输入文本以加密或解密
     * @param key 加密或解密的密钥
     * @return 加密/解密后的输出
     */
    static const std::string codec(const std::string &text,
                                   const matrix<int> &key) {
        size_t text_len = text.length();
        size_t key_len = key.size();

        // 输出字符串的长度必须是key_len的倍数
        // 创建输出字符串并用'\0'字符初始化
        size_t L2 = text_len % key_len == 0
                        ? text_len
                        : text_len + key_len - (text_len % key_len);
        std::string coded_text(L2, '\0');

        // 临时数组进行批处理
        int i;
#ifdef _OPENMP
#pragma parallel omp for private(i)
#endif
        for (i = 0; i < L2 - key_len + 1; i += key_len) {
            std::valarray<uint8_t> batch_int(key_len);
            for (size_t j = 0; j < key_len; j++) {
                batch_int[j] = get_char_idx(text[i + j]); // 将字符转换为索引
            }
            // 将batch_int发送到乘法操作
            batch_int = mat_mul(batch_int, key); // 执行矩阵乘法
            for (size_t j = 0; j < key_len; j++) {
                coded_text[i + j] = get_idx_char(batch_int[j]); // 将结果转换回字符
            }
        }
        return coded_text; // 返回编码后的字符串
    }

 public:
    /**
     * @brief 用于加密文本
     *
     * @param text 输入文本
     * @param key 加密密钥
     * @return 加密后的字符串
     */
    static const std::string encrypt(const std::string &text,
                                      const matrix<int> &key) {
        return codec(text, key); // 执行加密
    }

    /**
     * @brief 用于解密文本
     *
     * @param text 输入文本
     * @param key 解密密钥
     * @return 解密后的字符串
     */
    static const std::string decrypt(const std::string &text,
                                      const matrix<int> &key) {
        return codec(text, key); // 执行解密
    }

    /**
     * @brief 生成一个有效的加密密钥，确保它可逆并且行列式与字符集长度之间没有公共因子
     *
     * @param n 密钥大小
     * @param key 返回的密钥矩阵
     */
    static void generate_key(int n, matrix<int> &key) {
        assert(n > 0 && n <= 10); // 确保矩阵的大小合理

        // 随机填充矩阵并检查其行列式
        double det;
        do {
            det = rand_range(&key, 0, 10); // 随机填充矩阵
        } while (gcd(static_cast<int>(det), static_cast<int>(std::strlen(STRKEY))) != 1); // 确保满足条件
    }
};
}  // namespace ciphers
/**
 * @brief 自测 1 - 使用随机生成的 3x3 密钥
 *
 * @param text 要加密和解密的字符串
 */
void test1(const std::string &text) {
    std::cout << "======测试 1 (3x3 密钥) ======\n原始文本:\n\t" << text
              << std::endl;

    // 生成 3x3 的加密和解密密钥
    std::pair<matrix<int>, matrix<int>> p =
        ciphers::HillCipher::generate_keys(3, 0, 100);
    matrix<int> ekey = p.first; // 加密密钥
    matrix<int> dkey = p.second; // 解密密钥

    // 进行加密操作
    std::string gibberish = ciphers::HillCipher::encrypt_text(text, ekey);
    std::cout << "加密后的文本:\n\t" << gibberish << std::endl;

    // 使用解密密钥进行解密操作
    std::string txt_back = ciphers::HillCipher::decrypt_text(gibberish, dkey);
    std::cout << "重构后的文本:\n\t" << txt_back << std::endl;

    // 将结果写入文件
    std::ofstream out_file("hill_cipher_test1.txt");
    out_file << "块大小: " << ekey.size() << "\n";
    out_file << "加密密钥:\n" << ekey;
    out_file << "\n解密密钥:\n" << dkey;
    out_file.close();

    // 检查解密结果是否与原文本一致
    assert(txt_back == text);
    std::cout << "通过测试 :)\n";
}

/**
 * @brief 自测 2 - 使用随机生成的 8x8 密钥
 *
 * @param text 要加密和解密的字符串
 */
void test2(const std::string &text) {
    std::cout << "======测试 2 (8x8 密钥) ======\n原始文本:\n\t" << text
              << std::endl;

    // 生成 8x8 的加密和解密密钥
    std::pair<matrix<int>, matrix<int>> p =
        ciphers::HillCipher::generate_keys(8, 0, 3);
    matrix<int> ekey = p.first; // 加密密钥
    matrix<int> dkey = p.second; // 解密密钥

    // 进行加密操作
    std::string gibberish = ciphers::HillCipher::encrypt_text(text, ekey);
    std::cout << "加密后的文本:\n\t" << gibberish << std::endl;

    // 使用解密密钥进行解密操作
    std::string txt_back = ciphers::HillCipher::decrypt_text(gibberish, dkey);
    std::cout << "重构后的文本:\n\t" << txt_back << std::endl;

    // 将结果写入文件
    std::ofstream out_file("hill_cipher_test2.txt");
    out_file << "块大小: " << ekey.size() << "\n";
    out_file << "加密密钥:\n" << ekey;
    out_file << "\n解密密钥:\n" << dkey;
    out_file.close();

    // 检查解密结果是否与原文本一致
    assert(txt_back.compare(0, text.size(), text) == 0);
    std::cout << "通过测试 :)\n";
}

/** 主函数 */
int main() {
    std::srand(std::time(nullptr)); // 设置随机数种子
    std::cout << "密钥字典: (" << std::strlen(ciphers::STRKEY) << ")\n\t"
              << ciphers::STRKEY << "\n"; // 打印字符集

    std::string text = "This is a simple text with numb3r5 and exclamat!0n.";

    // 执行自测 1 和自测 2
    test1(text);
    test2(text);

    return 0; // 返回 0 表示程序成功结束
}
