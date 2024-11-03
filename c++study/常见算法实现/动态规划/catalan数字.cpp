/**
 * @file
 * @brief 提供使用动态规划计算 Catalan 数字的工具。
 * Catalan 数字满足以下递推关系：
 * C(0) = C(1) = 1; C(n) = sum(C(i).C(n-i-1)), 对于 i = 0 到 n-1
 * 了解有关 Catalan 数字的更多信息：
 * https://en.wikipedia.org/wiki/Catalan_number
 * https://oeis.org/A000108/
 */

#include <cassert>  /// 用于 assert
#include <cstdint>  /// 用于 std::uint64_t
#include <cstdlib>  /// 用于 std::size_t
#include <numeric>  /// 用于 std::transform_reduce
#include <vector>   /// 用于 std::vector

/**
 * @brief 计算和缓存 Catalan 数字
 */
class catalan_numbers {
    using value_type = std::uint64_t;  // 使用无符号 64 位整型作为值类型
    std::vector<value_type> known{1, 1};  // 缓存已知的 Catalan 数字，初始值为 C(0) 和 C(1)

    // 计算下一个 Catalan 数字
    value_type compute_next() {
        return std::transform_reduce(known.begin(), known.end(), known.rbegin(),
                                     static_cast<value_type>(), std::plus<>(),
                                     std::multiplies<>());
    }

    // 将下一个 Catalan 数字添加到缓存中
    void add() { known.push_back(this->compute_next()); }

 public:
    /**
     * @brief 计算第 n 个 Catalan 数字并更新缓存。
     * @return 第 n 个 Catalan 数字
     */
    value_type get(std::size_t n) {
        // 如果缓存的数字数量小于或等于 n，则计算并添加下一个数字
        while (known.size() <= n) {
            this->add();
        }
        return known[n];  // 返回第 n 个 Catalan 数字
    }
};

// 测试前 20 个 Catalan 数字
void test_catalan_numbers_up_to_20() {
    // 数据验证参考 https://oeis.org/A000108/
    catalan_numbers cn;  // 创建 catalan_numbers 对象
    assert(cn.get(0) == 1ULL);   // C(0) = 1
    assert(cn.get(1) == 1ULL);   // C(1) = 1
    assert(cn.get(2) == 2ULL);   // C(2) = 2
    assert(cn.get(3) == 5ULL);   // C(3) = 5
    assert(cn.get(4) == 14ULL);  // C(4) = 14
    assert(cn.get(5) == 42ULL);  // C(5) = 42
    assert(cn.get(6) == 132ULL); // C(6) = 132
    assert(cn.get(7) == 429ULL); // C(7) = 429
    assert(cn.get(8) == 1430ULL); // C(8) = 1430
    assert(cn.get(9) == 4862ULL); // C(9) = 4862
    assert(cn.get(10) == 16796ULL); // C(10) = 16796
    assert(cn.get(11) == 58786ULL); // C(11) = 58786
    assert(cn.get(12) == 208012ULL); // C(12) = 208012
    assert(cn.get(13) == 742900ULL); // C(13) = 742900
    assert(cn.get(14) == 2674440ULL); // C(14) = 2674440
    assert(cn.get(15) == 9694845ULL); // C(15) = 9694845
    assert(cn.get(16) == 35357670ULL); // C(16) = 35357670
    assert(cn.get(17) == 129644790ULL); // C(17) = 129644790
    assert(cn.get(18) == 477638700ULL); // C(18) = 477638700
    assert(cn.get(19) == 1767263190ULL); // C(19) = 1767263190
    assert(cn.get(20) == 6564120420ULL); // C(20) = 6564120420
}

// 测试第 25 个 Catalan 数字
void test_catalan_numbers_25() {
    // 数据验证参考 https://oeis.org/A000108/
    catalan_numbers cn;  // 创建 catalan_numbers 对象
    assert(cn.get(25) == 4861946401452ULL); // C(25) = 4861946401452
}

// 主函数
int main() {
    test_catalan_numbers_up_to_20(); // 测试前 20 个 Catalan 数字
    test_catalan_numbers_25(); // 测试第 25 个 Catalan 数字
    return 0; // 退出
}
