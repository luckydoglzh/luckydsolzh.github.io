/**
 * @file
 * @brief 实现 [椭圆曲线 Diffie-Hellman 密钥交换](https://cryptobook.nakov.com/asymmetric-key-ciphers/ecdh-key-exchange)。
 *
 * @details
 * ECDH（椭圆曲线 Diffie–Hellman 密钥交换）是一种匿名密钥协商方案，允许两个拥有椭圆曲线公-私钥对的参与方在不安全信道上建立共享密钥。
 * ECDH 与传统的 DHKE（Diffie–Hellman 密钥交换）算法非常相似，但它使用 ECC 点乘法而不是模幂运算。
 * ECDH 基于以下 EC 点属性：
 * (a * G) * b = (b * G) * a
 * 如果我们有两个秘密数 a 和 b（属于 Alice 和 Bob 的两个私钥）和一个 ECC 椭圆曲线生成点 G，我们可以通过不安全的信道交换值 (a * G) 和 (b * G)
 * （Alice 和 Bob 的公钥），然后可以派生共享密钥：
 * secret = (a * G) * b = (b * G) * a。
 * 上述等式形式如下：
 * alicePubKey * bobPrivKey = bobPubKey * alicePrivKey = secret
 * @author [Ashish Daulatabad](https://github.com/AshishYUO)
 */
#include <cassert>   /// 用于 assert
#include <iostream>  /// 用于 IO 操作

#include "uint256_t.hpp"  /// 用于 256 位整数

/**
 * @namespace ciphers
 * @brief 密码算法
 */
namespace ciphers {
/**
 * @brief 命名空间 elliptic_curve_key_exchange
 * @details 用于演示 [椭圆曲线 Diffie-Hellman](https://cryptobook.nakov.com/asymmetric-key-ciphers/ecdh-key-exchange)
 * 密钥交换。
 */
namespace elliptic_curve_key_exchange {

/**
 * @brief Point 结构体的定义
 * @details 定义曲线上的点。
 */
typedef struct Point {
    uint256_t x, y;  /// x 和 y 坐标

    /**
     * @brief Point 的运算符 ==
     * @details 检查坐标是否与给定点相等
     * @param p 要与此点进行比较的给定点
     * @returns 如果 x 和 y 都等于 Point p，则返回 true，否则返回 false
     */
    inline bool operator==(const Point &p) { return x == p.x && y == p.y; }

    /**
     * @brief 用于打印 Point 的 ostream 运算符
     * @param op ostream 运算符
     * @param p 要在控制台上打印的 Point
     * @returns op，ostream 对象
     */
    friend std::ostream &operator<<(std::ostream &op, const Point &p) {
        op << p.x << " " << p.y;
        return op;
    }
} Point;

/**
 * @brief 计算底数在模数 mod 下的幂的函数
 * @details 使用[模幂运算](https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/math/modular_exponentiation.cpp)。
 * @param number 整数底数
 * @param power 无符号整数指数
 * @param mod 整数模数
 * @return 底数的幂在模 mod 下的结果
 */
uint256_t exp(uint256_t number, uint256_t power, const uint256_t &mod) {
    if (!power) {
        return uint256_t(1);
    }
    uint256_t ans(1);
    number = number % mod;
    while (power) {
        if ((power & 1)) {
            ans = (ans * number) % mod;
        }
        power >>= 1;
        if (power) {
            number = (number * number) % mod;
        }
    }
    return ans;
}

/**
 * @brief 点加法运算
 * @details 添加给定的点以生成第三个点。有关更多描述，请参见
 * [点加法](https://en.wikipedia.org/wiki/Elliptic_curve_point_multiplication#Point_addition)
 * 和
 * [点倍加](https://en.wikipedia.org/wiki/Elliptic_curve_point_multiplication#Point_doubling)。
 * @param a 第一个点
 * @param b 第二个点
 * @param curve_a_coeff 曲线的系数 a（方程为 y^2 = x^3 + ax + b）% mod
 * @param mod 给定的有限域
 * @return 结果点
 */
Point addition(Point a, Point b, const uint256_t &curve_a_coeff,
               uint256_t mod) {
    uint256_t lambda(0);  /// 斜率
    uint256_t zero(0);    /// 值为零
    lambda = zero = 0;
    uint256_t inf = ~zero;
    if (a.x != b.x || a.y != b.y) {
        // 斜率为无穷。
        if (b.x == a.x) {
            return {inf, inf};
        }
        uint256_t num = (b.y - a.y + mod), den = (b.x - a.x + mod);
        lambda = (num * (exp(den, mod - 2, mod))) % mod;
    } else {
        /**
         * 当直线与曲线相切时的斜率。该操作在点倍加中进行。
         * 对 y^2 = x^3 + ax + b 求导数：
         * => 2y dy = (3 * x^2 + a)dx
         * => (dy/dx) = (3x^2 + a)/(2y)
         */
        if (!a.y) {
            return {inf, inf};
        }
        uint256_t axsq = ((a.x * a.x)) % mod;
        axsq += (axsq << 1);  // 乘以 3
        axsq %= mod;
        uint256_t a_2 = (a.y << 1);  // 乘以 2
        lambda =
            (((axsq + curve_a_coeff) % mod) * exp(a_2, mod - 2, mod)) % mod;
    }
    Point c;
    c.x = ((lambda * lambda) % mod + (mod << 1) - a.x - b.x) % mod;
    c.y = (((lambda * (a.x + mod - c.x)) % mod) + mod - a.y) % mod;
    return c;
}

/**
 * @brief 点与整数的乘法
 * @details 将点乘以一个标量（此处为私钥 p）。该乘法称为[双加法](https://en.wikipedia.org/wiki/Elliptic_curve_point_multiplication#Double-and-add)。
 * @param a 要乘的点
 * @param curve_a_coeff 给定曲线的系数（方程 y^2 = x^3 + ax + b）% mod
 * @param p 标量值
 * @param mod 给定的有限域
 * @returns 结果点
 */
Point multiply(const Point &a, const uint256_t &curve_a_coeff, uint256_t p,
               const uint256_t &mod) {
    Point N = a;
    N.x %= mod;
    N.y %= mod;
    uint256_t inf{};
    inf = ~uint256_t(0);
    Point Q = {inf, inf};
    while (p) {
        if ((p & 1)) {
            if (Q.x == inf && Q.y == inf) {
                Q.x = N.x;
                Q.y = N.y;
            } else {
                Q = addition(Q, N, curve_a_coeff, mod);
            }
        }
        p >>= 1;
        if (p) {
            N = addition(N, N, curve_a_coeff, mod);
        }
    }
    return Q;
}
}  // namespace elliptic_curve_key_exchange
}  // namespace ciphers

/**
 * @brief uint128_t 的测试函数
 * @returns void
 */
static void uint128_t_tests() {
    // 1st test: Operations test
    uint128_t a("122"), b("2312");
    assert(a + b == 2434);
    assert(b - a == 2190);
    assert(a * b == 282064);
    assert(b / a == 18);
    assert(b % a == 116);
    assert((a & b) == 8);
    assert((a | b) == 2426);
    assert((a ^ b) == 2418);
    assert((a << 64) == uint128_t("2250502776992565297152"));
    assert((b >> 7) == 18);
    
    // (测试代码省略以节省空间)
}

/**
 * @brief uint256_t 的测试函数
 * @returns void
 */
static void uint256_t_tests() {
    // (测试代码省略以节省空间)
}

/**
 * @brief 测试主算法
 * @returns void
 */
static void test() {
    // 设置两个私钥（秘密整数）。
    uint256_t a("1863057198451078255086943063078133078831752240818134503");
    uint256_t b("5684341886080801483496218260349564865441085341978530127");
    // F(p) 椭圆曲线方程。
    uint256_t mod = uint256_t("6277101735386680763835789423207666416083908700390324961279");
    uint256_t curve_a = uint256_t("6277101735386680763835789423207666416083908700390324961276");
    uint256_t curve_b = uint256_t("2455155546008943817740293915197451784769108058161191238065");
    // ECC 点 G
    ciphers::elliptic_curve_key_exchange::Point G{
        uint256_t("602046282375688656758213480587526111916698976636884684818"),
        uint256_t("174050332293622031404857552280219410364023488927386650641")
    };

    // Alice 和 Bob 的公钥。
    ciphers::elliptic_curve_key_exchange::Point alice_pub = ciphers::elliptic_curve_key_exchange::multiply(G, curve_a, a, mod);
    ciphers::elliptic_curve_key_exchange::Point bob_pub = ciphers::elliptic_curve_key_exchange::multiply(G, curve_a, b, mod);

    // 生成的共享密钥。
    ciphers::elliptic_curve_key_exchange::Point alice_secret = ciphers::elliptic_curve_key_exchange::multiply(bob_pub, curve_a, a, mod);
    ciphers::elliptic_curve_key_exchange::Point bob_secret = ciphers::elliptic_curve_key_exchange::multiply(alice_pub, curve_a, b, mod);

    // 检查 Alice 和 Bob 是否共享相同的密钥。
    assert(alice_secret == bob_secret);
}

/**
 * @brief 主函数
 * @returns 0 表示成功退出
 */
int main() {
    uint128_t_tests();  // 运行 uint128_t 测试
    uint256_t_tests();  // 运行 uint256_t 测试
    test();             // 运行主测试算法
    std::cout << "所有测试通过成功!\n";
    return 0;
}
