/**
 * @file
 * @brief C++ 程序通过 [费马小定理](https://en.wikipedia.org/wiki/Fermat%27s_little_theorem) 计算模逆。
 *
 * 费马小定理指出 \f[ϕ(m) = m-1\f]
 * 其中 \f$m\f$ 是质数。
 * \f{eqnarray*}{
 *  a \cdot x &≡& 1 \;\text{mod}\; m\\
 *  x &≡& a^{-1} \;\text{mod}\; m
 * \f}
 * 使用欧拉定理我们可以修改该方程：
 *\f[
 * a^{ϕ(m)} ≡ 1 \;\text{mod}\; m
 * \f]
 * （其中 '^' 表示指数运算）
 *
 * 这里 'ϕ' 是欧拉函数。为了使模逆存在，'a' 和 'm' 必须是互质的数。要应用费马小定理，'m' 必须是质数。在许多竞赛编程中，'m' 常常是 1000000007 (1e9+7) 或 998244353。
 *
 * 我们假设 'm' 是大质数（1e9+7）。
 * \f$a^{ϕ(m)} ≡ 1 \;\text{mod}\; m\f$ （使用欧拉定理）
 * \f$ϕ(m) = m-1\f$ 根据费马小定理。
 * \f$a^{m-1} ≡ 1 \;\text{mod}\; m\f$
 * 现在两边同时乘以 \f$a^{-1}\f$。
 * \f{eqnarray*}{
 * a^{m-1} \cdot a^{-1} &≡& a^{-1} \;\text{mod}\; m\\
 * a^{m-2} &≡&  a^{-1} \;\text{mod}\; m
 * \f}
 *
 * 我们将通过二进制指数算法计算该指数，使得算法的时间复杂度为 \f$O(\log m)\f$。
 *
 * 示例：-
 * * a = 3，m = 7
 * * \f$a^{-1} \;\text{mod}\; m\f$ 等价于
 * \f$a^{m-2} \;\text{mod}\; m\f$
 * * \f$3^5 \;\text{mod}\; 7 = 243 \;\text{mod}\; 7 = 5\f$
 * <br/>因此，\f$3^{-1} \;\text{mod}\; 7 = 5\f$
 * 或 \f$3 \times 5  \;\text{mod}\; 7 = 1 \;\text{mod}\; 7\f$
 * （因为 \f$a\times a^{-1} = 1\f$）
 */

#include <iostream>
#include <vector>

/** 通过二进制指数法递归计算指数，时间复杂度为 \f$O(\log n)\f$ */
int64_t binExpo(int64_t a, int64_t b, int64_t m) {
    a %= m;  // 对 a 进行模 m 操作
    int64_t res = 1;  // 初始化结果为 1
    while (b > 0) {
        if (b % 2) {  // 如果 b 是奇数
            res = res * a % m;  // 将当前 a 乘到结果中
        }
        a = a * a % m;  // a 更新为 a 的平方模 m
        b >>= 1;  // b 右移一位，相当于 b = b / 2
    }
    return res;
}

/** 判断 m 是否为质数，时间复杂度为 \f$O(\sqrt{m})\f$ */
bool isPrime(int64_t m) {
    if (m <= 1) {
        return false;  // m 小于等于 1 不是质数
    } else {
        for (int64_t i = 2; i * i <= m; i++) {  // 从 2 开始判断，直到 sqrt(m)
            if (m % i == 0) {  // 如果 m 可以被 i 整除，则 m 不是质数
                return false;
            }
        }
    }
    return true;  // 否则 m 是质数
}

/**
 * 主函数
 */
int main() {
    int64_t a, m;
    // 输入 a 和 m 的值
    std::cout << "通过费马小定理计算 ((a^(-1))%(m)) 的模逆" << std::endl;
    std::cout << "请输入 'a' 和 'm'，以空格分隔：";
    std::cin >> a >> m;
    
    if (isPrime(m)) {  // 如果 m 是质数
        std::cout << "a 的模逆（a^(m-2) mod m）为：";
        std::cout << binExpo(a, m - 2, m) << std::endl;  // 计算并输出结果
    } else {
        std::cout << "m 必须是质数。" << std::endl;  // 如果 m 不是质数，输出提示
    }
}
