/**
 * @class uint256_t
 * @brief class for 256-bit unsigned integer
 */
/**
 * @file
 *
 * @details 实现256位无符号整数。
 * @note 此实现可能标记为未完成。此头文件用于提供足够的操作，以演示 ECDH（椭圆曲线Diffie-Hellman）密钥交换的用法。
 * @author [Ashish Daulatabad](https://github.com/AshishYUO)
 */
#include <string>   /// 为了使用 `std::string`
#include <utility>  /// 为了使用 `std::pair` 库

#include "uint128_t.hpp"  /// 用于引入 uint128_t 整数

#ifndef CIPHERS_UINT256_T_HPP_
#define CIPHERS_UINT256_T_HPP_

class uint256_t;

// 特化 std::is_integral 模板，表示 uint256_t 是一个整数类型
template <>
struct std::is_integral<uint256_t> : std::true_type {};

// 特化 std::is_arithmetic 模板，表示 uint256_t 是一个算术类型
template <>
struct std::is_arithmetic<uint256_t> : std::true_type {};

// 特化 std::is_unsigned 模板，表示 uint256_t 是一个无符号类型
template <>
struct std::is_unsigned<uint256_t> : std::true_type {};

#endif  // CIPHERS_UINT256_T_HPP_

class uint256_t {
    uint128_t f{}, s{};  /// 256位数的前后两个128位部分

/**
 * @brief 从给定字符串获取整数。
 * @details 从给定字符串创建整数。
 * @param str 整数字符串，可以是十六进制（以0x...开头）或数字
 * @returns void
 */
void __get_integer_from_string(const std::string &str) {
    this->f = this->s = uint128_t(0);  // 初始化 f 和 s 为0
    if (str.size() > 1 && str[1] == 'x') {  // 检查是否为十六进制字符串
        for (auto i = 2; i < str.size(); ++i) {
            *this *= 16LL;  // 将当前值乘以16
            if (str[i] >= '0' && str[i] <= '9') {
                *this += (str[i] - '0');  // 将字符转换为数字并加到当前值
            } else if (str[i] >= 'A' && str[i] <= 'F') {
                *this += (str[i] - 'A' + 10);  // 将十六进制字母A-F转换为相应的数字
            } else if (str[i] >= 'a' && str[i] <= 'f') {
                *this += (str[i] - 'a' + 10);  // 将十六进制字母a-f转换为相应的数字
            }
        }
    } else {  // 如果不是十六进制字符串，假设为十进制
        for (auto &x : str) {
            *this *= 10LL;  // 将当前值乘以10
            *this += (x - '0');  // 将字符转换为数字并加到当前值
        }
    }
}

public:
    // 构造函数
    uint256_t() = default;  // 默认构造函数

    /**
     * @brief 带参数的构造函数
     * @tparam T 整数类型的模板
     * @param low 表示低128位的整数
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    explicit uint256_t(T low) : s(low), f(0) {}  // 使用给定的低位整数初始化

    /**
     * @brief 带参数的构造函数
     * @param str 整数字符串（十六进制以0x..开头或十进制）
     */
    explicit uint256_t(const std::string &str) {
        __get_integer_from_string(str);  // 从字符串获取整数
    }

    /**
     * @brief 拷贝构造函数
     * @param num 256位无符号整数
     */
    uint256_t(const uint256_t &num) = default;  // 默认拷贝构造函数

    /**
     * @brief 移动构造函数
     * @param num 256位无符号整数
     */
    uint256_t(uint256_t &&num) noexcept
        : f(std::move(num.f)), s(std::move(num.s)) {}  // 移动构造函数

    /**
     * @brief 带参数的构造函数
     * @param high 高128位无符号整数
     * @param low 低128位无符号整数
     */
    uint256_t(uint128_t high, uint128_t low)
        : f(std::move(high)), s(std::move(low)) {}  // 用给定的高低位初始化

    /**
     * @brief 带参数的构造函数
     * @param high 高64位无符号整数
     * @param low 低64位无符号整数
     */
    uint256_t(const uint64_t high, const uint64_t low) : f(high), s(low) {}  // 使用64位无符号整数初始化

    /**
     * @brief uint256_t的析构函数
     */
    ~uint256_t() = default;  // 默认析构函数

    /**
     * @brief 计算二进制中的前导零
     * @details 计算256位整数的前导零
     * @returns 表示前导零的整数
     */
    inline uint32_t _lez() {
        if (f) {
            return f._lez();  // 如果高128位非零，返回高128位的前导零
        }
        return 128 + s._lez();  // 否则返回128加上低128位的前导零
    }

    /**
     * @brief 计算二进制中的尾随零
     * @details 计算256位整数的尾随零
     * @returns 表示尾随零的整数
     */
    inline uint32_t _trz() {
        if (s) {
            return s._trz();  // 如果低128位非零，返回低128位的尾随零
        }
        return 128 + f._trz();  // 否则返回128加上高128位的尾随零
    }

    /**
     * @brief 转换为布尔值的操作符
     * @returns 如果此值非零则返回true，否则返回false
     */
    inline explicit operator bool() const { return f || s; }

    /**
     * @brief 转换为任意整数值的操作符
     * @tparam T 任何整数类型
     * @returns 转换为指定类型的整数值
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline explicit operator T() const {
        return static_cast<T>(s);  // 返回低128位部分
    }

    /**
     * @brief 转换为uint128_t的操作符
     * @returns 返回低128位整数部分
     */
    inline explicit operator uint128_t() const { return s; }

    /**
     * @brief 返回低128位整数部分
     * @returns 返回低128位整数部分
     */
    inline uint128_t lower() const { return s; }

    /**
     * @brief 返回高128位整数部分
     * @returns 返回高128位整数部分
     */
    inline uint128_t upper() const { return f; }

    /**
     * @brief uint256_t的赋值操作符
     * @param p 要赋值的256位整数
     * @returns 指向此对象的指针，其值等于`p`
     */
    inline uint256_t &operator=(const uint256_t &p) = default;

    /**
     * @brief 对其他类型的赋值操作符
     * @tparam T 任何整数类型
     * @param p 要赋值的整数
     * @returns 指向此对象的指针，其值等于`p`
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t &operator=(const T &p) {
        this->s = p;  // 将低128位赋值为p
        return *this;
    }

    /**
     * @brief 对字符串的赋值操作符
     * @param p 要赋值的字符串，转换为等效整数
     * @returns 指向此对象的指针，其值等于`p`
     */
    inline uint256_t &operator=(const std::string &p) {
        __get_integer_from_string(p);  // 从字符串获取整数
        return *this;
    }

    /**
     * @brief 移动赋值操作符
     */
    inline uint256_t &operator=(uint256_t &&p) = default;

    /**
     * @brief operator + 用于uint256_t和其他整数类型。
     * @tparam T 表示整型
     * @param p 一个整数变量
     * @returns 返回此和p的和，返回uint256_t整数
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t operator+(const T &p) {
        bool app = s + p < s;  // 检查是否有进位
        return uint256_t(f + app, s + p);  // 返回新值
    }

    /**
     * @brief operator + 用于uint256_t和其他整数类型。
     * @param p 256位无符号整数
     * @returns 返回此和p的和，返回uint256_t整数
     */
    inline uint256_t operator+(const uint256_t &p) {
        bool app = (s + p.s < s);  // 检查是否有进位
        return {f + app + p.f, s + p.s};  // 返回新值
    }

    /**
     * @brief operator += 用于uint256_t和其他整数类型。
     * @tparam T 表示整型
     * @param p 一个整数变量
     * @returns 返回此和p的和，返回此
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t &operator+=(const T &p) {
        bool app = (p + s < s);  // 检查是否有进位
        this->f += app;  // 更新高128位
        this->s += p;  // 更新低128位
        return *this;  // 返回此对象
    }

    /**
     * @brief operator += 用于uint256_t
     * @param p 256位无符号整数
     * @returns 返回此和p的和，返回此
     */
    inline uint256_t &operator+=(const uint256_t &p) {
        bool app = (s + p.s < s);  // 检查是否有进位
        f = f + app + p.f;  // 更新高128位
        s = s + p.s;  // 更新低128位
        return *this;  // 返回此对象
    }

    /**
     * @brief 前置递增操作符
     * @returns 此的递增值。
     */
    inline uint256_t &operator++() {
        *this += 1;  // 自增1
        return *this;  // 返回此对象
    }

    /**
     * @brief 后置递增操作符
     * @returns 此的递增值。
     */
    inline uint256_t operator++(int) {
        ++*this;  // 自增1
        return *this;  // 返回递增前的值
    }

    /**
     * @brief operator - 用于uint256_t和其他整数类型。
     * @tparam T 表示整型
     * @param p 一个整数变量
     * @returns 返回此和p的差，返回uint256_t整数
     */
    template <typename T, typename = typename std::enable_if<
                              std::is_integral<T>::value, T>::type>
    inline uint256_t operator-(const T &p) {
        bool app = (p > s);  // 检查是否借位
        return uint256_t(f - app, s - p);  // 返回新值
    }

    /**
     * @brief operator - 用于uint256_t
     * @param p 一个256位无符号整数
     * @returns 返回此和p的差，返回uint256_t整数
     */
    inline uint256_t operator-(const uint256_t &p) {
        bool app = s < p.s;  // 检查是否借位
        return {f - p.f - app, s - p.s};  // 返回新值
    }

    /**
     * @brief 采用二进制补码表示操作符 -
     * @returns 此的二进制补码。
     */
    inline uint256_t operator-() { return ~*this + uint256_t(1); }

    /**
     * @brief operator -- (前置递减)
     * @returns 此的递减值
     */
    inline uint256_t &operator--() {
        *this -= 1;  // 自减1
        return *this;  // 返回此对象
    }

    /**
     * @brief operator -- (后置递减)
     * @returns 此的递减值
     */
    inline uint256_t operator--(int p) {
        --*this;  // 自减1
        return *this;  // 返回递减前的值
    }
    /**
 * @brief operator -= 用于 uint256_t 和其他整数类型。
 * @tparam T 表示整型
 * @param p 一个整数变量
 * @returns 返回此和 p 的差，返回此
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator-=(const T p) {
    bool app = (p > s);  // 检查是否需要借位
    f = f - app;  // 更新高128位
    s = s - p;  // 更新低128位
    return *this;  // 返回此对象
}

/**
 * @brief operator -= 用于 uint256_t
 * @param p 256位无符号整数
 * @returns 返回此和 p 的差，返回此
 */
inline uint256_t &operator-=(const uint256_t &p) {
    bool app = s < p.s;  // 检查是否需要借位
    f = f - app - p.f;  // 更新高128位
    s = s - p.s;  // 更新低128位
    return *this;  // 返回此对象
}

/**
 * @brief operator * 用于 uint256_t 和其他整数类型。
 * @tparam T 表示整型
 * @param p 一个整数变量
 * @returns 返回此和 p 的乘积，返回 uint256_t 整数
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator*(const T &p) {
    return *this * uint256_t(p);  // 转换 p 为 uint256_t 并相乘
}

/**
 * @brief operator * 用于 uint256_t
 * @param p 256位无符号整数
 * @returns 返回此和 p 的乘积，返回 uint256_t 整数
 */
uint256_t operator*(const uint256_t &p) {
    // 分别获取高低128位
    uint128_t f_first(s.upper()), f_second(s.lower()), s_first(p.s.upper()),
        s_second(p.s.lower());
    
    // 进行乘法运算
    uint128_t fi = f_first * s_first, se = f_first * s_second,
              th = s_first * f_second, fo = s_second * s_second;

    uint128_t tmp = se << 64, tmp2 = th << 64;  // 左移64位
    int cc = (tmp + tmp2 < tmp);  // 检查是否有进位
    tmp += tmp2;  // 更新临时值
    cc += (tmp + fo < tmp);  // 检查是否有进位

    return {f * p.s + s * p.f + fi + se.upper() + th.upper() + cc,
            tmp + fo};  // 返回乘积
}

/**
 * @brief operator *= 用于 uint256_t 和其他整数类型。
 * @tparam T 表示整型
 * @param p 一个整数变量
 * @returns 返回此和 p 的乘积，返回此
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t &operator*=(const T &p) {
    return (*this *= uint256_t(p));  // 转换 p 为 uint256_t 并相乘
}

/**
 * @brief operator *= 用于 uint256_t
 * @param p 256位无符号整数
 * @returns 返回此和 p 的乘积，返回此
 */
uint256_t &operator*=(const uint256_t &p) {
    // 分别获取高低128位
    uint128_t f_first(s.upper()), f_second(s.lower()), s_first(p.s.upper()),
        s_second(p.s.lower());

    // 进行乘法运算
    uint128_t fi = f_first * s_first, se = f_first * s_second,
              th = s_first * f_second, fo = s_second * s_second;

    uint128_t tmp = se << 64, tmp2 = th << 64;  // 左移64位
    int cc = (tmp + tmp2 < tmp);  // 检查是否有进位
    tmp += tmp2;  // 更新临时值
    cc += (tmp + fo < tmp);  // 检查是否有进位

    // 更新结果
    f = f * p.s + s * p.f + fi + se.upper() + th.upper() + cc;
    s = tmp + fo;
    return *this;  // 返回此对象
}

/**
 * @brief divide 函数用于 uint256_t 和其他整数类型。
 * @details 除以此值
 * @param p 256位无符号整数
 * @returns 一对，表示商和余数。
 */
std::pair<uint256_t, uint256_t> divide(const uint256_t &p) {
    if (*this < p) {  // 如果此值小于除数
        return {uint256_t(0), *this};  // 返回商为0，余数为自身
    } else if (*this == p) {  // 如果此值等于除数
        return {uint256_t(1), uint256_t(0)};  // 返回商为1，余数为0
    }

    uint256_t tmp = p, tmp2 = *this;  // 创建临时值
    uint16_t left = tmp._lez() - _lez();  // 获取移位数量
    tmp <<= left;  // 左移临时值
    uint256_t quotient(0);  // 初始化商
    uint256_t zero(0);  // 零值

    while (tmp2 >= p) {  // 当被除数大于等于除数时
        uint16_t shf = tmp2._lez() - tmp._lez();  // 计算移位数量
        if (shf) {
            tmp >>= shf;  // 右移临时值
            quotient <<= shf;  // 左移商
            left -= shf;  // 更新移位数量
        }
        if (tmp2 < tmp) {  // 如果被除数小于临时值
            tmp >>= 1;  // 右移临时值
            quotient <<= 1;  // 左移商
            --left;  // 更新移位数量
        }
        tmp2 -= tmp;  // 被除数减去临时值
        ++quotient;  // 商加1
    }
    return {quotient << left, tmp2};  // 返回商和余数
}

/**
 * @brief operator / 用于 uint256_t 和其他整数类型。
 * @tparam T 表示整型
 * @param p 一个整数变量
 * @returns 返回无符号 256 位商。
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator/(const T &p) {
    uint256_t tmp = *this;
    tmp /= uint256_t(p);  // 除以转换后的 p
    return tmp;  // 返回结果
}

/**
 * @brief operator / 用于 uint256_t
 * @param p 256位无符号整数
 * @returns 返回无符号 256 位商。
 */
inline uint256_t operator/(const uint256_t &p) {
    return divide(p).first;  // 返回商
}

/**
 * @brief operator /= 用于 uint256_t
 * @param p 256位无符号整数
 * @returns 将此设置为无符号 256 位商。
 */
inline uint256_t &operator/=(const uint256_t &p) {
    *this = divide(p).first;  // 更新为商
    return *this;  // 返回此对象
}

/**
 * @brief operator /= 用于 uint256_t 和其他整数类型。
 * @tparam T 表示整型
 * @param p 一个整数变量
 * @returns 将此设置为无符号 256 位商。
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t &operator/=(const T &p) {
    *this /= uint256_t(p);  // 除以转换后的 p
    return *this;  // 返回此对象
}

/**
 * @brief operator % 用于 uint256_t
 * @param p 256位无符号整数
 * @returns 返回无符号 256 位余数。
 */
inline uint256_t operator%(const uint256_t &p) {
    return divide(p).second;  // 返回余数
}

/**
 * @brief operator % 用于 uint256_t 和其他整数类型。
 * @tparam T 表示整型
 * @param p 一个整数变量
 * @returns 返回无符号 256 位余数。
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator%(const T &p) {
    uint256_t tmp = *this;
    tmp %= uint256_t(p);  // 取模运算
    return tmp;  // 返回结果
}

/**
 * @brief operator %= 用于 uint256_t
 * @param p 256位无符号整数
 * @returns 将此设置为无符号 256 位余数。
 */
inline uint256_t &operator%=(const uint256_t &p) {
    *this = divide(p).second;  // 更新为余数
    return *this;  // 返回此对象
}

/**
 * @brief operator %= 用于 uint256_t
 * @tparam T 表示整型
 * @param p 一个整数变量
 * @returns 将此设置为无符号 256 位余数。
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t &operator%=(const T &p) {
    *this %= uint256_t(p);  // 取模运算
    return *this;  // 返回此对象
}

/**
 * @brief operator < 用于 uint256_t
 * @param other 要与此比较的数字
 * @returns 如果此小于 other 返回真，否则返回假
 */
inline bool operator<(const uint256_t &other) {
    return f < other.f || (f == other.f && s < other.s);  // 比较高128位和低128位
}

/**
 * @brief operator <= 用于 uint256_t
 * @param other 要与此比较的数字
 * @returns 如果此小于或等于 other 返回真，否则返回假
 */
inline bool operator<=(const uint256_t &other) {
    return f < other.f || (f == other.f && s <= other.s);  // 比较高128位和低128位
}

/**
 * @brief operator > 用于 uint256_t
 * @param other 要与此比较的数字
 * @returns 如果此大于 other 返回真，否则返回假
 */
inline bool operator>(const uint256_t &other) {
    return f > other.f || (f == other.f && s > other.s);  // 比较高128位和低128位
}

/**
 * @brief operator >= 用于 uint256_t
 * @param other 要与此比较的数字
 * @returns 如果此大于或等于 other 返回真，否则返回假
 */
inline bool operator>=(const uint256_t &other) {
    return (f > other.f) || (f == other.f && s >= other.s);  // 比较高128位和低128位
}

/**
 * @brief operator == 用于 uint256_t
 * @param other 要与此比较的数字
 * @returns 如果此等于 other 返回真，否则返回假
 */
inline bool operator==(const uint256_t &other) {
    return f == other.f && s == other.s;  // 比较高128位和低128位
}

/**
 * @brief operator != 用于 uint256_t
 * @param other 要与此比较的数字
 * @returns 如果此不等于 other 返回真，否则返回假
 */
inline bool operator!=(const uint256_t &other) {
    return !((*this) == other);  // 调用 == 运算符
}

/**
 * @brief operator ! 用于 uint256_t
 * @returns 如果此值为零返回真，否则返回假
 */
inline bool operator!() { return !f && !s;  // 检查高低128位是否为零
}

/**
 * @brief operator && 用于 uint256_t
 * @param b 要与此比较的数字
 * @returns 如果两个值均不为零返回真，否则返回假
 */
inline bool operator&&(const uint256_t &b) {
    return (s || f) && (b.s || b.f);  // 检查高低128位是否为零
}

/**
 * @brief operator || 用于 uint256_t
 * @param b 要与此比较的数字
 * @returns 如果任一值不为零返回真，否则返回假
 */
inline bool operator||(const uint256_t &b) {
    return (s || f) || (b.s || b.f);  // 检查高低128位是否为零
}

/**
 * @brief operator () 用于 uint256_t
 * @returns 如果此值非零返回真，否则返回假
 */
inline bool operator()() { return s || f;  // 检查高低128位是否为零
}

/**
 * @brief operator < 用于其他类型
 * @tparam T 整数类型
 * @param other 要与此比较的数字
 * @returns 如果此小于 other 返回真，否则返回假
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
bool operator<(const T &other) {
    return *this < uint256_t(other);  // 转换 other 为 uint256_t 并比较
}
/**
 * @brief operator <= for other types
 * @tparam T integral type
 * @param other 要与此比较的数字
 * @returns 如果此小于或等于 other 返回真，否则返回假
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
bool operator<=(const T &other) {
    return *this <= uint256_t(other);  // 转换 other 为 uint256_t 并比较
}

/**
 * @brief operator > for other types
 * @tparam T integral type
 * @param other 要与此比较的数字
 * @returns 如果此大于 other 返回真，否则返回假
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
bool operator>(const T &other) {
    return *this > uint256_t(other);  // 转换 other 为 uint256_t 并比较
}

/**
 * @brief operator >= for other types
 * @tparam T integral type
 * @param other 要与此比较的数字
 * @returns 如果此大于或等于 other 返回真，否则返回假
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
bool operator>=(const T &other) {
    return *this >= uint256_t(other);  // 转换 other 为 uint256_t 并比较
}

/**
 * @brief operator == for other types
 * @tparam T integral type
 * @param other 要与此比较的数字
 * @returns 如果此等于 other 返回真，否则返回假
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
bool operator==(const T &other) {
    return *this == uint256_t(other);  // 转换 other 为 uint256_t 并比较
}

/**
 * @brief operator != for other types
 * @tparam T integral type
 * @param other 要与此比较的数字
 * @returns 如果此不等于 other 返回真，否则返回假
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
bool operator!=(const T &other) {
    return *this != uint256_t(other);  // 转换 other 为 uint256_t 并比较
}

/**
 * @brief operator && for other types
 * @tparam T integral type
 * @param b 要与此比较的数字
 * @returns 如果此值和 b 都为非零返回真，否则返回假
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator&&(const T &b) {
    return (s || f) && (b);  // 检查高低128位和 b 是否为零
}

/**
 * @brief operator || for other types
 * @tparam T integral type
 * @param b 要与此比较的数字
 * @returns 如果此值或 b 其中一个为非零返回真，否则返回假
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator||(const T &b) {
    return (s || f) || (b);  // 检查高低128位或 b 是否为零
}

/**
 * @brief operator ~ for uint256_t
 * @returns 此数字的 1 的补数
 */
inline uint256_t operator~() { return {~f, ~s}; }  // 返回高低128位取反

/**
 * @brief operator << for uint256_t
 * @tparam T integral type
 * @param p 表示移位的位数
 * @returns 此值左移 p 位的结果
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
uint256_t operator<<(const T &p) {
    if (!p) {
        return {this->f, this->s};  // 不移位时返回自身
    } else if (p >= 128) {
        return uint256_t((this->s << (p - 128)), uint128_t(0));  // 高位左移
    }
    return uint256_t((this->f << p) + (this->s >> (128 - p)),
                     (this->s << p));  // 左移并处理溢出
}

/**
 * @brief operator <<= for uint256_t
 * @tparam T integral type
 * @param p 表示移位的位数
 * @returns 此值左移 p 位的结果（就地操作）
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
uint256_t &operator<<=(const T &p) {
    if (p) {
        if (p >= 128) {
            this->f = (this->s << (p - 128));  // 高位左移
            this->s = uint128_t(0);  // 低位清零
        } else {
            f = ((this->s >> (128 - p)) + (this->f << p));  // 左移并处理溢出
            s = (this->s << p);  // 低位左移
        }
    }
    return *this;  // 返回自身
}

/**
 * @brief operator >> for uint256_t
 * @tparam T integral type
 * @param p 表示移位的位数
 * @returns 此值右移 p 位的结果
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
uint256_t operator>>(const T &p) {
    if (!p) {
        return {this->f, this->s};  // 不移位时返回自身
    } else if (p >= 128) {
        return uint256_t(uint128_t(0), (this->f >> (p - 128)));  // 低位右移
    }
    return uint256_t((this->f >> p),
                     (this->s >> p) + (this->f << (128 - p)));  // 右移并处理溢出
}

/**
 * @brief operator >>= for uint256_t
 * @tparam T integral type
 * @param p 表示移位的位数
 * @returns 此值右移 p 位的结果（就地操作）
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
uint256_t &operator>>=(const T &p) {
    if (p) {
        if (p >= 128) {
            f = uint128_t(0);  // 高位清零
            s = (this->f >> (p - 128));  // 低位右移
        } else {
            s = (this->s >> p) + (this->f << (128 - p));  // 右移并处理溢出
            f = (this->f >> p);  // 高位右移
        }
    }
    return *this;  // 返回自身
}

/**
 * @brief operator & for other types (bitwise operator)
 * @tparam T integral type
 * @param p 要进行操作的数字
 * @returns 此值与 p 的按位与结果
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator&(const T &p) {
    return *this & uint256_t(p);  // 转换 p 为 uint256_t 并进行按位与
}

/**
 * @brief operator & for uint256_t (bitwise operator)
 * @param p 要进行操作的数字
 * @returns 此值与 p 的按位与结果
 */
inline uint256_t operator&(const uint256_t &p) {
    return {f & p.f, s & p.s};  // 高低128位按位与
}

/**
 * @brief operator &= for uint256_t (bitwise operator)
 * @param p 要进行操作的数字
 * @returns 此 = 此 & p（按位与操作）
 */
inline uint256_t &operator&=(const uint256_t &p) {
    f &= p.f;  // 高位按位与
    s &= p.s;  // 低位按位与
    return *this;  // 返回自身
}

/**
 * @brief operator &= for other types (bitwise operator)
 * @tparam T integral type
 * @param p 要进行操作的数字
 * @returns 此 = 此 & p（按位与操作）
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t &operator&=(const T p) {
    s &= p;  // 低位按位与
    return *this;  // 返回自身
}

/**
 * @brief operator | for other types (bitwise operator)
 * @tparam T integral type
 * @param p 要进行操作的数字
 * @returns 此值与 p 的按位或结果
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator|(const T &p) {
    return *this | uint256_t(p);  // 转换 p 为 uint256_t 并进行按位或
}

/**
 * @brief operator | for uint256_t (bitwise operator)
 * @param p 要进行操作的数字
 * @returns 此值与 p 的按位或结果
 */
inline uint256_t operator|(const uint256_t &p) {
    return {f | p.f, s | p.s};  // 高低128位按位或
}

/**
 * @brief operator |= for uint256_t (bitwise operator)
 * @param p 要进行操作的数字
 * @returns 此 = 此 | p（按位或操作）
 */
inline uint256_t &operator|=(const uint256_t &p) {
    f |= p.f;  // 高位按位或
    s |= p.s;  // 低位按位或
    return *this;  // 返回自身
}

/**
 * @brief operator |= for other types (bitwise operator)
 * @tparam T integral type
 * @param p 要进行操作的数字
 * @returns 此 = 此 | p（按位或操作）
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t &operator|=(const T p) {
    s |= p;  // 低位按位或
    return *this;  // 返回自身
}

/**
 * @brief operator ^ for other types (bitwise operator)
 * @tparam T integral type
 * @param p 要进行操作的数字
 * @returns 此值与 p 的按位异或结果
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator^(const T &p) {
    return *this ^ uint256_t(p);  // 转换 p 为 uint256_t 并进行按位异或
}

/**
 * @brief operator ^ for uint256_t (bitwise operator)
 * @param p 要进行操作的数字
 * @returns 此值与 p 的按位异或结果
 */
inline uint256_t operator^(const uint256_t &p) {
    return {f ^ p.f, s ^ p.s};  // 高低128位按位异或
}

/**
 * @brief operator ^= for uint256_t (bitwise operator)
 * @param p 要进行操作的数字
 * @returns 此 = 此 ^ p（按位异或操作）
 */
inline uint256_t &operator^=(const uint256_t &p) {
    f ^= p.f;  // 高位按位异或
    s ^= p.s;  // 低位按位异或
    return *this;  // 返回自身
}

/**
 * @brief operator ^= for other types (bitwise operator)
 * @tparam T integral type
 * @param p 要进行操作的数字
 * @returns 此 = 此 ^ p（按位异或操作）
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t &operator^=(const T p) {
    s ^= p;  // 低位按位异或
    return *this;  // 返回自身
}
}
// Artihmetic
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator+(const T p, const uint256_t &q) {
    return uint256_t(p) + q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator-(const T p, const uint256_t &q) {
    return (uint256_t(p) - q);
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator*(const T p, const uint256_t &q) {
    return uint256_t(p) * q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator/(const T p, const uint256_t &q) {
    return uint256_t(p) / q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator%(const T p, const uint256_t &q) {
    return uint256_t(p) % q;
}

// Bitwise operators
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator&(const T &p, const uint256_t &q) {
    return uint256_t(p) & q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator|(const T p, const uint256_t &q) {
    return uint256_t(p) | q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator^(const T p, const uint256_t &q) {
    return uint256_t(p) ^ q;
}

// Boolean operators
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator&&(const T p, const uint256_t &q) {
    return uint256_t(p) && q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator||(const T p, const uint256_t &q) {
    return uint256_t(p) || q;
}

// Comparison operators
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator==(const T p, const uint256_t &q) {
    return uint256_t(p) == q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator!=(const T p, const uint256_t &q) {
    return uint256_t(p) != q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator<(const T p, const uint256_t &q) {
    return uint256_t(p) < q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator<=(const T p, const uint256_t &q) {
    return uint256_t(p) <= q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator>(const T p, const uint256_t &q) {
    return uint256_t(p) > q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator>=(const T p, const uint256_t &q) {
    return uint256_t(p) >= q;
}

#endif  // CIPHERS_UINT256_T_HPP_
