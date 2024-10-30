/**
 * @file
 *
 * @details 128位无符号整数的实现。
 * @note 此实现可以标记为未完成。该头文件用于作为256位整数的更大整数类型的一部分，具有足够的操作。
 * @author [Ashish Daulatabad](https://github.com/AshishYUO)
 */

#include <algorithm>  /// 用于 `std::reverse` 和其他操作
#include <ostream>    /// 用于 `std::cout` 重载
#include <string>     /// 用于 `std::string`
#include <utility>    /// 用于 `std::pair` 库

#ifdef _MSC_VER
#include <intrin.h>  /// 用于 _BitScanForward64 和 __BitScanReverse64 操作
#endif

#ifndef CIPHERS_UINT128_T_HPP_
#define CIPHERS_UINT128_T_HPP_

class uint128_t;

// 针对 uint128_t 类型的特化类型 trait
template <>
struct std::is_integral<uint128_t> : std::true_type {};
template <>
struct std::is_arithmetic<uint128_t> : std::true_type {};
template <>
struct std::is_unsigned<uint128_t> : std::true_type {};

/**
 * @brief 添加两个字符串
 * @details 仅用于打印数字的两个长整型相加
 * @param first 第一个整数字符串
 * @param second 第二个整数字符串
 * @returns 表示两个字符串相加的字符串
 */
std::string add(const std::string &first, const std::string &second) {
    std::string third;  // 用于存储结果的字符串
    int16_t sum = 0, carry = 0;  // sum: 当前位的和，carry: 进位
    // 从右往左遍历两个字符串
    for (int32_t i = static_cast<int32_t>(first.size()) - 1,
                 j = static_cast<int32_t>(second.size()) - 1;
         i >= 0 || j >= 0; --i, --j) {
        // 计算当前位的和
        sum = ((i >= 0 ? first[i] - '0' : 0) + (j >= 0 ? second[j] - '0' : 0) +
               carry);
        carry = sum / 10;  // 计算进位
        sum %= 10;  // 当前位的结果
        third.push_back(sum + '0');  // 将当前位的结果添加到结果字符串中
    }
    if (carry) {
        third.push_back('1');  // 如果还有进位，则添加1
    }
    std::reverse(third.begin(), third.end());  // 反转结果字符串
    return third;  // 返回相加后的字符串
}

/**
 * @class uint128_t
 * @brief 128位无符号整数类
 */
class uint128_t {
    uint64_t f{}, s{};  /// 128位数的高低两部分

    /**
     * @brief 从给定字符串获取整数。
     * @details 从给定字符串创建一个整数
     * @param str 整数字符串，可以是十六进制（以0x...开头）或数字
     * @returns void
     */
    void __get_integer_from_string(const std::string &str) {
        this->f = this->s = 0;  // 初始化高低部分为0
        if (str.size() > 1 && str[1] == 'x') {  // 如果是十六进制
            for (auto i = 2; i < str.size(); ++i) {
                *this *= 16LL;  // 乘以16
                // 根据字符计算对应的值并加到当前对象
                if (str[i] >= '0' && str[i] <= '9') {
                    *this += (str[i] - '0');
                } else if (str[i] >= 'A' && str[i] <= 'F') {
                    *this += (str[i] - 'A' + 10);
                } else if (str[i] >= 'a' && str[i] <= 'f') {
                    *this += (str[i] - 'a' + 10);
                }
            }
        } else {  // 如果是十进制
            for (auto &x : str) {
                *this *= 10LL;  // 乘以10
                *this += (x - '0');  // 加上对应的数字
            }
        }
    }

 public:
    uint128_t() = default;  // 默认构造函数

    /**
     * @brief 带参数的构造函数
     * @tparam T 整数类型
     * @param low 低位64位无符号整数
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    explicit uint128_t(T low) : s(low) {}  // 使用低位初始化

    /**
     * @brief 带参数的构造函数
     * @param str 整数字符串（以0x..开头的十六进制或十进制）
     */
    explicit uint128_t(const std::string &str) {
        __get_integer_from_string(str);  // 从字符串获取整数
    }

    /**
     * @brief 带参数的构造函数
     * @param high 高位64位无符号整数
     * @param low 低位64位无符号整数
     */
    uint128_t(const uint64_t high, const uint64_t low) : f(high), s(low) {}

    /**
     * @brief 拷贝构造函数
     * @param num 128位无符号整数
     */
    uint128_t(const uint128_t &num) = default;

    /**
     * @brief 移动构造函数
     * @param num 128位无符号整数
     */
    uint128_t(uint128_t &&num) noexcept : f(num.f), s(num.s) {}

    /**
     * @brief uint128_t 的析构函数
     */
    ~uint128_t() = default;

    /**
     * @brief 计算二进制的前导零
     * @details 计算128位整数的前导零
     * @returns 表示前导零的整数
     */
    inline uint32_t _lez() {
#ifndef _MSC_VER
        if (f) {
            return __builtin_clzll(f);  // 计算高64位的前导零
        }
        return 64 + __builtin_clzll(s);  // 计算低64位的前导零
#else
        unsigned long r = 0;
        _BitScanForward64(&r, f);
        if (r == 64) {
            unsigned long l = 0;
            _BitScanForward64(&l, s);
            return 64 + l;  // 计算低64位的前导零
        }
        return r;  // 返回高64位的前导零
#endif
    }

    /**
     * @brief 计算二进制的尾随零
     * @details 计算128位整数的尾随零
     * @returns 表示尾随零的整数
     */
    inline uint32_t _trz() {
#ifndef _MSC_VER
        if (f) {
            return __builtin_ctzll(f);  // 计算高64位的尾随零
        }
        return 64 + __builtin_ctzll(s);  // 计算低64位的尾随零
#else
        unsigned long r = 0;
        _BitScanReverse64(&r, s);
        if (r == 64) {
            unsigned long l = 0;
            _BitScanReverse64(&l, f);
            return 64 + l;  // 计算高64位的尾随零
        }
        return r;  // 返回低64位的尾随零
#endif
    }

    /**
     * @brief 布尔值转换操作符
     * @returns 如果值非零则为真，否则为假
     */
    inline explicit operator bool() const { return (f || s); }

    /**
     * @brief 转换操作符到任何整数值
     * @tparam T 任何整数类型
     * @returns 转换为指定类型的整数值
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline explicit operator T() const {
        return static_cast<T>(s);  // 仅返回低位
    }

    /**
     * @brief 返回低64位整数部分
     * @returns 返回低64位整数部分
     */
    inline uint64_t lower() const { return s; }

    /**
     * @brief 返回高64位整数部分
     * @returns 返回高64位整数部分
     */
    inline uint64_t upper() const { return f; }

    /**
     * @brief 赋值操作符用于其他类型
     * @tparam T 表示任何整数类型
     * @param p 一个整数来赋值
     * @returns 返回当前对象的指针，其值等于 `p`
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t &operator=(const T &p) {
        this->s = p;  // 直接赋值低位
        return *this;  // 返回当前对象
    }

    /**
     * @brief 赋值操作符用于字符串类型
     * @param p 一个字符串，将其值赋给等效整数
     * @returns 返回当前对象的指针，其值等于 `p`
     */
    inline uint128_t &operator=(const std::string &p) {
        this->__get_integer_from_string(p);  // 从字符串获取整数
        return *this;  // 返回当前对象
    }

    /**
     * @brief 赋值操作符用于 uint128_t 类型
     * @param p 一个128位整数，赋值给当前对象
     * @returns 返回当前对象的指针，其值等于 `p`
     */
    inline uint128_t &operator=(const uint128_t &p) = default;

    /**
     * @brief 移动赋值操作符
     */
    inline uint128_t &operator=(uint128_t &&p) = default;

    /**
     * @brief 对于 uint128_t 和其他整数类型的加法操作符。
     * @tparam T 表示整数类型
     * @param p 一个整数变量
     * @returns 当前对象与 `p` 的和，返回 uint128_t 整数
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t operator+(const T p) {
        return uint128_t(f + (p + s < s), p + s);  // 计算加法并返回新对象
    }

    /**
     * @brief 对于 uint128_t 和其他整数类型的加法操作符。
     * @param p 128位无符号整数
     * @returns 当前对象与 `p` 的和，返回 uint128_t 整数
     */
    inline uint128_t operator+(const uint128_t &p) {
        return uint128_t(f + (p.s + s < s) + p.f, p.s + s);  // 计算加法并返回新对象
    }

    /**
     * @brief 对于 uint128_t 和其他整数类型的加法赋值操作符。
     * @tparam T 表示整数类型
     * @param p 一个整数变量
     * @returns 当前对象与 `p` 的和，返回当前对象
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint128_t &operator+=(const T p) {
        bool app = p + s < s;  // 检查是否需要进位
        this->f += app;  // 更新高位
        this->s += p;  // 更新低位
        return *this;  // 返回当前对象
    }

    /**
     * @brief 对于 uint128_t 的加法赋值操作符
     * @param p 128位无符号整数
     * @returns 当前对象与 `p` 的和，返回当前对象
     */
    uint128_t &operator+=(const uint128_t &p) {
        bool app = p.s + s < s;  // 检查是否需要进位
        f = f + app + p.f;  // 更新高位
        s = p.s + s;  // 更新低位
        return *this;  // 返回当前对象
    }
/**
 * @brief 前置自增运算符
 * @returns 自增后的当前对象值
 */
inline uint128_t &operator++() {
    *this += 1;  // 调用加法运算符自增1
    return *this;  // 返回自增后的对象
}

/**
 * @brief 后置自增运算符
 * @returns 自增前的当前对象值
 */
inline uint128_t operator++(int) {
    uint128_t temp = *this;  // 先保存当前对象的值
    ++*this;  // 调用前置自增运算符自增1
    return temp;  // 返回自增前的对象
}

/**
 * @brief 对于 uint128_t 和其他整数类型的减法运算符
 * @tparam T 表示整型
 * @param p 一个整数变量
 * @returns 当前对象减去 p 的结果，返回 uint128_t 整数
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator-(const T &p) {
    bool app = p > s;  // 检查是否需要借位
    return uint128_t(f - app, s - p);  // 计算减法并返回新对象
}

/**
 * @brief 对于 uint128_t 的减法运算符
 * @param p 另一个 uint128_t 类型的对象
 * @returns 当前对象减去 p 的结果，返回 uint128_t 整数
 */
inline uint128_t operator-(const uint128_t &p) {
    bool app = p.s > s;  // 检查是否需要借位
    return uint128_t(f - p.f - app, s - p.s);  // 计算减法并返回新对象
}

/**
 * @brief 获取当前对象的二补数
 * @returns 当前对象的二补数
 */
inline uint128_t operator-() { return ~*this + uint128_t(1); }

/**
 * @brief 前置自减运算符
 * @returns 自减后的当前对象值
 */
inline uint128_t &operator--() {
    *this -= 1;  // 调用减法运算符自减1
    return *this;  // 返回自减后的对象
}

/**
 * @brief 后置自减运算符
 * @returns 自减前的当前对象值
 */
inline uint128_t operator--(int) {
    uint128_t temp = *this;  // 先保存当前对象的值
    --*this;  // 调用前置自减运算符自减1
    return temp;  // 返回自减前的对象
}

/**
 * @brief 对于 uint128_t 和其他整数类型的减法赋值运算符
 * @tparam T 表示整型
 * @param p 一个整数变量
 * @returns 当前对象减去 p 的结果，返回当前对象
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
uint128_t &operator-=(const T &p) {
    bool app = p > s;  // 检查是否需要借位
    f -= app;  // 更新高位
    s -= p;  // 更新低位
    return *this;  // 返回当前对象
}

/**
 * @brief 对于 uint128_t 的减法赋值运算符
 * @param p 另一个 uint128_t 类型的对象
 * @returns 当前对象减去 p 的结果，返回当前对象
 */
uint128_t &operator-=(const uint128_t &p) {
    bool app = p.s > s;  // 检查是否需要借位
    f = f - p.f - app;  // 更新高位
    s = s - p.s;  // 更新低位
    return *this;  // 返回当前对象
}

/**
 * @brief 对于 uint128_t 和其他整数类型的乘法运算符
 * @tparam T 表示整型
 * @param p 一个整数变量
 * @returns 当前对象与 p 的乘积，返回 uint128_t 整数
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator*(const T p) {
    return *this * uint128_t(p);  // 将整数转换为 uint128_t 后进行乘法
}

/**
 * @brief 对于 uint128_t 的乘法运算符
 * @param p 另一个 uint128_t 类型的对象
 * @returns 当前对象与 p 的乘积，返回 uint128_t 整数
 */
uint128_t operator*(const uint128_t &p) {
    uint64_t f_first = s >> 32, f_second = s & 0xFFFFFFFF,
             s_first = p.s >> 32, s_second = p.s & 0xFFFFFFFF;  // 分解高低位
    uint64_t fi = f_first * s_first, se = f_first * s_second,
             th = s_first * f_second, fo = s_second * s_second;  // 进行乘法运算
    uint64_t tmp = ((se & 0xFFFFFFFF) << 32), tmp2 = (th & 0xFFFFFFFF) << 32;  // 计算部分结果
    int cc = (tmp + tmp2 < tmp);  // 检查是否有进位
    tmp += tmp2;  // 汇总部分结果
    cc += (tmp + fo < tmp);  // 检查乘积中的进位
    uint64_t carry = fi + (se >> 32) + (th >> 32);  // 计算最终的高位
    return uint128_t(this->f * p.s + this->s * p.f + carry + cc, tmp + fo);  // 返回乘法结果
}

/**
 * @brief 对于 uint128_t 和其他整数类型的乘法赋值运算符
 * @tparam T 表示整型
 * @param p 一个整数变量
 * @returns 当前对象与 p 的乘积，返回当前对象
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t &operator*=(const T p) {
    *this *= uint128_t(p);  // 将整数转换为 uint128_t 后进行乘法赋值
    return *this;  // 返回当前对象
}

/**
 * @brief 对于 uint128_t 的乘法赋值运算符
 * @param p 另一个 uint128_t 类型的对象
 * @returns 当前对象与 p 的乘积，返回当前对象
 */
uint128_t &operator*=(const uint128_t &p) {
    uint64_t f_first = s >> 32, f_second = s & 0xFFFFFFFF,
             s_first = p.s >> 32, s_second = p.s & 0xFFFFFFFF;  // 分解高低位
    uint64_t fi = f_first * s_first, se = f_first * s_second,
             th = s_first * f_second, fo = s_second * s_second;  // 进行乘法运算
    uint64_t tmp = (se << 32), tmp2 = (th << 32);  // 计算部分结果
    int cc = (tmp + tmp2 < tmp);  // 检查是否有进位
    tmp += tmp2;  // 汇总部分结果
    cc += (tmp + fo < tmp);  // 检查乘积中的进位
    uint64_t carry = fi + (se >> 32) + (th >> 32);  // 计算最终的高位
    f = this->f * p.s + this->s * p.f + carry + cc;  // 更新高位
    s = tmp + fo;  // 更新低位
    return *this;  // 返回当前对象
}

/**
 * @brief 除法函数，用于 uint128_t 和其他整数类型
 * @details 计算当前对象与 p 的商和余数
 * @param p 另一个 uint128_t 类型的对象
 * @returns 返回一个包含商和余数的 pair
 */
std::pair<uint128_t, uint128_t> divide(const uint128_t &p) {
    if (*this < p) {  // 如果当前对象小于除数
        return {uint128_t(0), *this};  // 商为0，余数为当前对象
    } else if (*this == p) {  // 如果当前对象等于除数
        return {uint128_t(1), uint128_t(0)};  // 商为1，余数为0
    }
    uint128_t tmp = p, tmp2 = *this;  // 复制除数和被除数
    uint16_t left = tmp._lez() - _lez();  // 计算需要左移的位数
    tmp <<= left;  // 将除数左移
    uint128_t quotient(0);  // 初始化商为0
    uint128_t zero(0);  // 初始化余数为0
    while (tmp2 >= p) {  // 当被除数大于等于除数时
        uint16_t shf = tmp2._lez() - tmp._lez();  // 计算需要右移的位数
        if (shf) {
            tmp >>= shf;  // 右移除数
            quotient <<= shf;  // 左移商
            left -= shf;  // 更新左移位数
        }
        if (tmp2 < tmp) {  // 如果被除数小于除数
            tmp >>= 1;  // 右移除数
            quotient <<= 1;  // 左移商
            --left;  // 更新左移位数
        }
        tmp2 -= tmp;  // 被除数减去除数
        ++quotient;  // 商加1
    }
    return {quotient << left, tmp2};  // 返回商和余数
}

/**
 * @brief 对于 uint128_t 和其他整数类型的除法运算符
 * @param p 另一个 uint128_t 类型的对象
 * @returns 返回当前对象与 p 的商
 */
inline uint128_t operator/(const uint128_t &p) { return divide(p).first; }

/**
 * @brief 对于 uint128_t 和其他整数类型的除法运算符
 * @tparam T 表示整型
 * @param p 一个整数变量
 * @returns 返回当前对象与 p 的商
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator/(const T p) {
    uint128_t tmp = *this;  // 复制当前对象
    tmp /= uint128_t(0, p);  // 将整数转换为 uint128_t 后进行除法
    return tmp;  // 返回结果
}

/**
 * @brief 对于 uint128_t 的除法赋值运算符
 * @param p 另一个 uint128_t 类型的对象
 * @returns 当前对象设置为与 p 的商
 */
inline uint128_t &operator/=(const uint128_t &p) {
    *this = divide(p).first;  // 更新当前对象为商
    return *this;  // 返回当前对象
}

/**
 * @brief 对于 uint128_t 和其他整数类型的除法赋值运算符
 * @tparam T 表示整型
 * @param p 一个整数变量
 * @returns 当前对象设置为与 p 的商
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t &operator/=(const T p) {
    *this /= uint128_t(0, p);  // 将整数转换为 uint128_t 后进行除法赋值
    return *this;  // 返回当前对象
}

/**
 * @brief uint128_t 类型的取模运算符
 * @param p 128 位无符号整数
 * @returns 返回无符号 128 位余数。
 */
inline uint128_t operator%(const uint128_t &p) { return divide(p).second; }

/**
 * @brief uint128_t 与其他整型的取模运算符。
 * @tparam T 表示整型
 * @param p 一个整型变量
 * @returns 返回无符号 128 位余数。
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
inline uint128_t operator%(const T &p) {
    return *this % uint128_t(p);
}

/**
 * @brief uint128_t 的取模赋值运算符
 * @param p 128 位无符号整数
 * @returns 当前对象设置为无符号 128 位余数。
 */
inline uint128_t &operator%=(const uint128_t &p) {
    *this = divide(p).second;
    return *this;
}

/**
 * @brief uint128_t 与其他整型的取模赋值运算符
 * @tparam T 表示整型
 * @param p 一个整型变量
 * @returns 当前对象设置为无符号 128 位余数。
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
inline uint128_t &operator%=(const T &p) {
    *this %= uint128_t(p);
    return *this;
}

/**
 * @brief uint128_t 的小于运算符
 * @param other 要与当前对象比较的数字
 * @returns 如果当前对象小于 other，返回 true，否则返回 false
 */
inline bool operator<(const uint128_t &other) {
    return f < other.f || (f == other.f && s < other.s);
}

/**
 * @brief uint128_t 的小于或等于运算符
 * @param other 要与当前对象比较的数字
 * @returns 如果当前对象小于或等于 other，返回 true，否则返回 false
 */
inline bool operator<=(const uint128_t &other) {
    return f < other.f || (f == other.f && s <= other.s);
}

/**
 * @brief uint128_t 的大于运算符
 * @param other 要与当前对象比较的数字
 * @returns 如果当前对象大于 other，返回 true，否则返回 false
 */
inline bool operator>(const uint128_t &other) {
    return f > other.f || (f == other.f && s > other.s);
}

/**
 * @brief uint128_t 的大于或等于运算符
 * @param other 要与当前对象比较的数字
 * @returns 如果当前对象大于或等于 other，返回 true，否则返回 false
 */
inline bool operator>=(const uint128_t &other) {
    return (f > other.f) || (f == other.f && s >= other.s);
}

/**
 * @brief uint128_t 的等于运算符
 * @param other 要与当前对象比较的数字
 * @returns 如果当前对象等于 other，返回 true，否则返回 false
 */
inline bool operator==(const uint128_t &other) {
    return f == other.f && s == other.s;
}

/**
 * @brief uint128_t 的不等于运算符
 * @param other 要与当前对象比较的数字
 * @returns 如果当前对象不等于 other，返回 true，否则返回 false
 */
inline bool operator!=(const uint128_t &other) {
    return f != other.f || s != other.s;
}

/**
 * @brief uint128_t 的逻辑非运算符
 * @returns 如果当前对象的值为零，返回 true，否则返回 false
 */
inline bool operator!() { return !f && !s; }

/**
 * @brief uint128_t 的逻辑与运算符
 * @param b 要与当前对象比较的数字
 * @returns 如果两个值都不为零，返回 true，否则返回 false
 */
inline bool operator&&(const uint128_t &b) {
    return (s || f) && (b.s || b.f);
}

/**
 * @brief uint128_t 的逻辑或运算符
 * @param b 要与当前对象比较的数字
 * @returns 如果有一个值不为零，返回 true，否则返回 false
 */
inline bool operator||(const uint128_t &b) {
    return (s || f) || (b.s || b.f);
}

/**
 * @brief uint128_t 的调用运算符
 * @returns 如果当前值非零，返回 true，否则返回 false
 */
inline bool operator()() { return s || f; }

/**
 * @brief 对其他类型的 < 运算符
 * @tparam T 整型
 * @param other 要与当前对象比较的数字
 * @returns 如果当前对象小于 other，返回 true，否则返回 false
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
inline bool operator<(const T other) {
    return *this < uint128_t(other);
}

/**
 * @brief 对其他类型的 <= 运算符
 * @tparam T 整型
 * @param other 要与当前对象比较的数字
 * @returns 如果当前对象小于或等于 other，返回 true，否则返回 false
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
inline bool operator<=(const T other) {
    return *this <= uint128_t(other);
}

/**
 * @brief 对其他类型的 > 运算符
 * @tparam T 整型
 * @param other 要与当前对象比较的数字
 * @returns 如果当前对象大于 other，返回 true，否则返回 false
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
inline bool operator>(const T other) {
    return *this > uint128_t(other);
}

/**
 * @brief 对其他类型的 >= 运算符
 * @tparam T 整型
 * @param other 要与当前对象比较的数字
 * @returns 如果当前对象大于或等于 other，返回 true，否则返回 false
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
inline bool operator>=(const T other) {
    return *this >= uint128_t(other);
}

/**
 * @brief 对其他类型的 == 运算符
 * @tparam T 整型
 * @param other 要与当前对象比较的数字
 * @returns 如果当前对象等于 other，返回 true，否则返回 false
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
inline bool operator==(const T other) {
    return *this == uint128_t(other);
}

/**
 * @brief 对其他类型的 != 运算符
 * @tparam T 整型
 * @param other 要与当前对象比较的数字
 * @returns 如果当前对象不等于 other，返回 true，否则返回 false
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
inline bool operator!=(const T other) {
    return *this != uint128_t(other);
}

/**
 * @brief 对其他类型的 && 运算符
 * @tparam T 整型
 * @param other 要与当前对象比较的数字
 * @returns 如果两个值都不为零，返回 true，否则返回 false
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
inline bool operator&&(const T b) {
    return (f || s) && b;
}

/**
 * @brief 对其他类型的 || 运算符
 * @tparam T 整型
 * @param other 要与当前对象比较的数字
 * @returns 如果当前对象的任意一个值不为零，返回 true，否则返回 false
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
inline bool operator||(const T b) {
    return (f || s) || b;
}

/**
 * @brief uint128_t 的按位取反运算符
 * @returns 返回该数字的 1's 互补
 */
uint128_t operator~() { return uint128_t(~this->f, ~this->s); }

/**
 * @brief uint128_t 的左移运算符
 * @tparam T 整型
 * @param p 表示移位的数量
 * @returns 当前值左移 p 位后的值
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
uint128_t operator<<(const T p) {
    if (!p) {
        return uint128_t(f, s);
    } else if (p >= 64 && p <= 128) {
        return uint128_t((this->s << (p - 64)), 0);
    } else if (p < 64 && p > 0) {
        return uint128_t((this->f << p) + ((this->s >> (64 - p))),
                         this->s << p);
    }
    return uint128_t(0);
}
/**
 * @brief operator <<= for uint128_t
 * @tparam T integral type
 * @param p number denoting number of shifts
 * @returns this shifted by p to left
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
uint128_t &operator<<=(const T p) {
    if (p) {
        if (p >= 64 && p <= 128) {
            // 当 p 在 64 到 128 之间时，左移并清零高位
            this->f = (this->s << (p - 64));
            this->s = 0;
        } else {
            // 左移 p 位并处理高位
            f = ((this->f << p) + (this->s >> (64 - p)));
            s = (this->s << p);
        }
    }
    return *this;
}

/**
 * @brief operator >> for uint128_t
 * @tparam T integral type
 * @param p number denoting number of shifts
 * @returns value of this shifted by p to right
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
uint128_t operator>>(const T p) {
    if (!p) {
        // 如果 p 为 0，返回当前值
        return uint128_t(this->f, this->s);
    } else if (p >= 64 && p <= 128) {
        // 当 p 在 64 到 128 之间时，右移并清零高位
        return uint128_t(0, (this->f >> (p - 64)));
    } else if (p < 64 && p > 0) {
        // 右移 p 位并处理高位
        return uint128_t((this->f >> p),
                         (this->s >> p) + (this->f << (64 - p)));
    }
    return uint128_t(0);
}

/**
 * @brief operator >>= for uint128_t
 * @tparam T integral type
 * @param p number denoting number of shifts
 * @returns this shifted by p to right
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
uint128_t &operator>>=(const T p) {
    if (p) {
        if (p >= 64) {
            // 当 p >= 64 时，清零高位，右移低位
            f = 0;
            s = (this->f >> (p - 64));
        } else {
            // 右移 p 位并处理高位
            s = (this->s >> p) + (this->f << (64 - p));
            f = (this->f >> p);
        }
    }
    return *this;
}

/**
 * @brief operator & for uint128_t (bitwise operator)
 * @param p number to be operated
 * @returns value of this & p (& is bit-wise operator)
 */
inline uint128_t operator&(const uint128_t &p) {
    // 按位与运算
    return uint128_t(this->f & p.f, this->s & p.s);
}

/**
 * @brief operator & for other types (bitwise operator)
 * @tparam T integral type
 * @param p number to be operated
 * @returns value of this & p (& is bit-wise operator)
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
uint128_t operator&(const T p) {
    uint128_t tmp = *this;
    // 将 T 转换为 uint128_t 并执行按位与
    return tmp & uint128_t(p);
}

/**
 * @brief operator &= for uint128_t (bitwise operator)
 * @param p number to be operated
 * @returns this = this & p (& is bit-wise operator)
 */
uint128_t &operator&=(const uint128_t &p) {
    // 按位与赋值
    this->f &= p.f;
    this->s &= p.s;
    return *this;
}

/**
 * @brief operator &= for other types (bitwise operator)
 * @tparam T integral type
 * @param p number to be operated
 * @returns this = this & p (& is bit-wise operator)
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
uint128_t &operator&=(const T p) {
    *this &= uint128_t(p);
    return *this;
}

/**
 * @brief operator | for other types (bitwise operator)
 * @tparam T integral type
 * @param p number to be operated
 * @returns value of this | p (| is bit-wise operator)
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
inline uint128_t operator|(const T p) {
    // 将 T 转换为 uint128_t 并执行按位或运算
    return uint128_t(p | s);
}

/**
 * @brief operator | for uint128_t (bitwise operator)
 * @param p number to be operated
 * @returns value of this | p (| is bit-wise OR operator)
 */
inline uint128_t operator|(const uint128_t &p) {
    // 按位或运算
    return uint128_t(this->f | p.f, this->s | p.s);
}

/**
 * @brief operator |= for uint128_t (bitwise operator)
 * @param p number to be operated
 * @returns this = this | p (| is bit-wise OR operator)
 */
uint128_t &operator|=(const uint128_t &p) {
    // 按位或赋值
    f |= p.f;
    s |= p.s;
    return *this;
}

/**
 * @brief operator |= for other types (bitwise operator)
 * @tparam T integral type
 * @param p number to be operated
 * @returns this = this | p (| is bit-wise OR operator)
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
inline uint128_t &operator|=(const T p) {
    s |= p.s;
    return *this;
}

/**
 * @brief operator ^ for other types (bitwise operator)
 * @tparam T integral type
 * @param p number to be operated
 * @returns value of this ^ p (^ is bit-wise XOR operator)
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
inline uint128_t operator^(const T p) {
    // 将 T 转换为 uint128_t 并执行按位异或运算
    return uint128_t(this->f, this->s ^ p);
}

/**
 * @brief operator ^ for uint128_t (bitwise operator)
 * @param p number to be operated
 * @returns value of this ^ p (^ is bit-wise XOR operator)
 */
inline uint128_t operator^(const uint128_t &p) {
    // 按位异或运算
    return uint128_t(this->f ^ p.f, this->s ^ p.s);
}

/**
 * @brief operator ^= for uint128_t (bitwise operator)
 * @param p number to be operated
 * @returns this = this ^ p (^ is bit-wise XOR operator)
 */
uint128_t &operator^=(const uint128_t &p) {
    // 按位异或赋值
    f ^= p.f;
    s ^= p.s;
    return *this;
}

/**
 * @brief operator ^= for other types (bitwise operator)
 * @tparam T integral type
 * @param p number to be operated
 * @returns this = this ^ p (^ is bit-wise XOR operator)
 */
template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
inline uint128_t &operator^=(const T &p) {
    s ^= p;
    return *this;
}

/**
 * @brief operator << for printing uint128_t integer
 * @details Prints the uint128_t integer in decimal form
 * @note Note that this operator is costly since it uses strings to print
 * the value
 * @param op ostream object
 * @param p 128-bit integer
 * @returns op, ostream object.
 */
friend std::ostream &operator<<(std::ostream &op, const uint128_t &p) {
    if (!p.f) {
        // 如果高位为 0，则只打印低位
        op << p.s;
    } else {
        // 将 uint128_t 转换为字符串并打印
        std::string out = "0", p_2 = "1";
        for (int i = 0; i < 64; ++i) {
            // 计算低位
            if (p.s & (1LL << i)) {
                out = add(out, p_2);
            }
            p_2 = add(p_2, p_2);
        }
        for (int i = 0; i < 64; ++i) {
            // 计算高位
            if (p.f & (1LL << i)) {
                out = add(out, p_2);
            }
            p_2 = add(p_2, p_2);
        }
        op << out; // 打印最终结果
    }
    return op;
}
};
// 算术运算符
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator+(const T &p, const uint128_t &q) {
    // 重载 + 运算符，支持 T 类型与 uint128_t 的相加
    return uint128_t(p) + q; // 将 T 转换为 uint128_t 进行相加
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator-(const T p, const uint128_t &q) {
    // 重载 - 运算符，支持 T 类型与 uint128_t 的相减
    return uint128_t(p) - q; // 将 T 转换为 uint128_t 进行相减
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator*(const T p, const uint128_t &q) {
    // 重载 * 运算符，支持 T 类型与 uint128_t 的相乘
    return uint128_t(p) * q; // 将 T 转换为 uint128_t 进行相乘
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator/(const T p, const uint128_t &q) {
    // 重载 / 运算符，支持 T 类型与 uint128_t 的相除
    return uint128_t(p) / q; // 将 T 转换为 uint128_t 进行相除
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator%(const T p, const uint128_t &q) {
    // 重载 % 运算符，支持 T 类型与 uint128_t 的取模
    return uint128_t(p) % q; // 将 T 转换为 uint128_t 进行取模
}

// 位运算符
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator&(const T &p, const uint128_t &q) {
    // 重载 & 运算符，支持 T 类型与 uint128_t 的按位与
    return uint128_t(p) & q; // 将 T 转换为 uint128_t 进行按位与
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator|(const T p, const uint128_t &q) {
    // 重载 | 运算符，支持 T 类型与 uint128_t 的按位或
    return uint128_t(p) | q; // 将 T 转换为 uint128_t 进行按位或
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint128_t operator^(const T p, const uint128_t &q) {
    // 重载 ^ 运算符，支持 T 类型与 uint128_t 的按位异或
    return uint128_t(p) ^ q; // 将 T 转换为 uint128_t 进行按位异或
}

// 布尔运算符
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator&&(const T p, const uint128_t &q) {
    // 重载 && 运算符，支持 T 类型与 uint128_t 的逻辑与
    return uint128_t(p) && q; // 将 T 转换为 uint128_t 进行逻辑与
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator||(const T p, const uint128_t &q) {
    // 重载 || 运算符，支持 T 类型与 uint128_t 的逻辑或
    return uint128_t(p) || q; // 将 T 转换为 uint128_t 进行逻辑或
}

// 比较运算符
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator==(const T p, const uint128_t &q) {
    // 重载 == 运算符，支持 T 类型与 uint128_t 的相等比较
    return uint128_t(p) == q; // 将 T 转换为 uint128_t 进行比较
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator!=(const T p, const uint128_t &q) {
    // 重载 != 运算符，支持 T 类型与 uint128_t 的不相等比较
    return uint128_t(p) != q; // 将 T 转换为 uint128_t 进行比较
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator<(const T p, const uint128_t &q) {
    // 重载 < 运算符，支持 T 类型与 uint128_t 的小于比较
    return uint128_t(p) < q; // 将 T 转换为 uint128_t 进行比较
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator<=(const T p, const uint128_t &q) {
    // 重载 <= 运算符，支持 T 类型与 uint128_t 的小于等于比较
    return uint128_t(p) <= q; // 将 T 转换为 uint128_t 进行比较
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator>(const T p, const uint128_t &q) {
    // 重载 > 运算符，支持 T 类型与 uint128_t 的大于比较
    return uint128_t(p) > q; // 将 T 转换为 uint128_t 进行比较
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator>=(const T p, const uint128_t &q) {
    // 重载 >= 运算符，支持 T 类型与 uint128_t 的大于等于比较
    return uint128_t(p) >= q; // 将 T 转换为 uint128_t 进行比较
}

#endif  // CIPHERS_UINT128_T_HPP_
