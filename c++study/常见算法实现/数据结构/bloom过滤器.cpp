/**
 * @file
 * @brief [布隆过滤器](https://en.wikipedia.org/wiki/Bloom_filter)
 * 的通用实现（C++）
 * @details 布隆过滤器是一种空间高效的概率数据结构，
 * 查询返回“可能在集合中”或“肯定不在集合中”。
 *
 * 一般而言，所需的每个元素少于 10 位，以实现 1% 的误报概率，
 * 与集合的大小或元素数量无关。
 *
 * 它帮助我们避免执行“昂贵的操作”，例如磁盘 IO - 我们可以使用布隆过滤器
 * 检查传入请求，并以良好的概率获得布隆过滤器的答案，这样我们就不需要
 * 执行“昂贵的操作”。
 *
 * [非常好的用例示例](https://stackoverflow.com/a/30247022)
 *
 * 基本布隆过滤器不支持删除元素，因此在我们的情况下
 * 不需要实现布隆过滤器和位集合的删除功能。
 * @author [DanArmor](https://github.com/DanArmor)
 */

#include <cassert>           /// 用于断言
#include <functional>        /// 用于布隆过滤器构造函数的哈希函数列表
#include <initializer_list>  /// 用于布隆过滤器构造函数的初始化列表
#include <string>            /// 用于字符串测试
#include <vector>            /// 用于 std::vector
#include <iostream>          /// 用于 IO 操作

/**
 * @namespace data_structures
 * @brief 数据结构算法
 */
namespace data_structures {
/**
 * @brief 布隆过滤器的简单位集合实现
 */
class Bitset {
 private:
    std::vector<std::size_t> data;  ///< 此变量的简短信息
    static const std::size_t blockSize =
        sizeof(std::size_t);  ///< 我们在位集合中使用的整数类型的大小
 public:
    explicit Bitset(std::size_t);
    std::size_t size();
    void add(std::size_t);
    bool contains(std::size_t);
};

/**
 * @brief 返回内部数组的大小的实用函数
 * @returns 内部数组的大小
 */
std::size_t Bitset::size() { return data.size(); }

/**
 * @brief BitSet 类构造函数
 * @param initSize 块的数量，每个块包含 sizeof(std::size_t) 位
 */
Bitset::Bitset(std::size_t initSize) : data(initSize) {}

/**
 * @brief 将位置 x 的位设置为 1
 *
 * @param x 要设置为 1 的位置
 * @returns void
 */
void Bitset::add(std::size_t x) {
    std::size_t blockIndex = x / blockSize;
    if (blockIndex >= data.size()) {
        data.resize(blockIndex + 1);
    }
    data[blockIndex] |= 1 << (x % blockSize);
}

/**
 * @brief 位集合是否包含元素 x
 *
 * @param x 要检查的位集合中的位置
 * @returns 如果位位置 x 是 1，则返回 true
 * @returns 如果位位置 x 是 0，则返回 false
 */
bool Bitset::contains(std::size_t x) {
    std::size_t blockIndex = x / blockSize;
    if (blockIndex >= data.size()) {
        return false;
    }
    return data[blockIndex] & (1 << (x % blockSize));
}

/**
 * @brief 布隆过滤器模板类
 * @tparam T 需要过滤的元素类型
 */
template <typename T>
class BloomFilter {
 private:
    Bitset set;  ///< 用于元素的内部位集合
    std::vector<std::function<std::size_t(T)>>
        hashFunks;  ///< T 类型的哈希函数

 public:
    BloomFilter(std::size_t,
                std::initializer_list<std::function<std::size_t(T)>>);
    void add(T);
    bool contains(T);
};

/**
 * @brief 布隆过滤器构造函数
 *
 * @tparam T 需要过滤的元素类型
 * @param size 布隆过滤器的初始大小
 * @param funks T 类型的哈希函数
 * @returns none
 */
template <typename T>
BloomFilter<T>::BloomFilter(
    std::size_t size,
    std::initializer_list<std::function<std::size_t(T)>> funks)
    : set(size), hashFunks(funks) {}

/**
 * @brief 布隆过滤器的添加函数
 *
 * @tparam T 需要过滤的元素类型
 * @param x 要添加到过滤器的元素
 * @returns void
 */
template <typename T>
void BloomFilter<T>::add(T x) {
    for (std::size_t i = 0; i < hashFunks.size(); i++) {
        set.add(hashFunks[i](x) % (sizeof(std::size_t) * set.size()));
    }
}

/**
 * @brief 布隆过滤器的检查元素函数
 *
 * @tparam T 需要过滤的元素类型
 * @param x 要在过滤器中检查的元素
 * @return true 如果元素可能出现在过滤器中
 * @return false 如果元素肯定不出现在过滤器中
 */
template <typename T>
bool BloomFilter<T>::contains(T x) {
    for (std::size_t i = 0; i < hashFunks.size(); i++) {
        if (set.contains(hashFunks[i](x) %
                         (sizeof(std::size_t) * set.size())) == false) {
            return false;
        }
    }
    return true;
}

/**
 * @brief [函数 djb2](http://www.cse.yorku.ca/~oz/hash.html)
 * 用于获取给定字符串的哈希值。
 *
 * @param s 要获取哈希值的字符串
 * @returns 字符串的哈希值
 */
static std::size_t hashDJB2(std::string const& s) {
    std::size_t hash = 5381;
    for (char c : s) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

/**
 * @brief [哈希函数](https://stackoverflow.com/questions/8317508/hash-function-for-a-string)
 * 用于获取给定字符串的哈希值。
 *
 * @param s 要获取哈希值的字符串
 * @returns 给定字符串的哈希值
 */
static std::size_t hashStr(std::string const& s) {
    std::size_t hash = 37;
    std::size_t primeNum1 = 54059;
    std::size_t primeNum2 = 76963;
    for (char c : s) {
        hash = (hash * primeNum1) ^ (c * primeNum2);
    }
    return hash;
}

/**
 * @brief [用于测试的哈希函数](https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key)
 *
 * @param x 要获取哈希值的参数
 * @returns `x` 参数的哈希值
 */
std::size_t hashInt_1(int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

/**
 * @brief [用于测试的哈希函数](https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key)
 *
 * @param x 要获取哈希值的参数
 * @returns `x` 参数的哈希值
 */
std::size_t hashInt_2(int x) {
    auto y = static_cast<std::size_t>(x);
    y = (y ^ (y >> 30)) * static_cast<std::size_t>(0xbf58476d1ce4e5b9);
    y = (y ^ (y >> 27)) * static_cast<std::size_t>(0x94d049bb133111eb);
    y = y ^ (y >> 31);
    return y;
}
}  // namespace data_structures

/**
 * @brief 测试以字符串作为通用类型的布隆过滤器
 * @returns void
 */
static void test_bloom_filter_string() {
    data_structures::BloomFilter<std::string> filter(
        10, {data_structures::hashDJB2, data_structures::hashStr});
    std::vector<std::string> toCheck{"hello", "world", "!"};
    std::vector<std::string> toFalse{"false", "world2", "!!!"};
    for (const auto& x : toCheck) {
        filter.add(x);
    }
    for (const auto& x : toFalse) {
        assert(filter.contains(x) == false);
    }
    for (const auto& x : toCheck) {
        assert(filter.contains(x));
    }
}

/**
 * @brief 测试以 int 作为通用类型的布隆过滤器
 * @returns void
 */
static void test_bloom_filter_int() {
    data_structures::BloomFilter<int> filter(
        20, {data_structures::hashInt_1, data_structures::hashInt_2});
    std::vector<int> toCheck{100, 200, 300, 50};
    std::vector<int> toFalse{1, 2, 3, 4, 5, 6, 7, 8};
    for (int x : toCheck) {
        filter.add(x);
    }
    for (int x : toFalse) {
        assert(filter.contains(x) == false);
    }
    for (int x : toCheck) {
        assert(filter.contains(x));
    }
}

/**
 * @brief 测试位集合
 *
 * @returns void
 */
static void test_bitset() {
    data_structures::Bitset set(2);
    std::vector<std::size_t> toCheck{0, 1, 5, 8, 63, 64, 67, 127};
    for (auto x : toCheck) {
        set.add(x);
        assert(set.contains(x));
    }
    assert(set.contains(128) == false);
    assert(set.contains(256) == false);
}

/**
 * @brief 主函数
 * @returns 0 正常退出
 */
int main() {
    // 运行自测实现

    test_bitset();  // 运行位集合的测试，因为布隆过滤器依赖于它
    test_bloom_filter_string();
    test_bloom_filter_int();
    
    std::cout << "所有测试均已成功通过！\n";
    return 0;
}
