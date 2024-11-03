/**
 * @file
 * @brief 实现 [Sparse Table](https://brilliant.org/wiki/sparse-table/) 的 `min()` 函数。
 * @author [Mann Patel](https://github.com/manncodes)
 * @details
 * 稀疏表是一种数据结构，用于回答区间查询。
 * 它可以在 O(logn) 时间内回答大多数区间查询，但其真正的优势在于回答
 * 区间最小查询（或等效的区间最大查询）。对于这些查询，它可以在 O(1) 时间内计算答案。
 * 该数据结构的唯一缺点是，它只能用于不可变数组。这意味着
 * 在两个查询之间，数组不能被更改。
 *
 * 如果数组中的任何元素发生变化，则必须重新计算整个数据结构。
 *
 * @todo 进行压力测试。
 *
 * @warning
 * 该稀疏表专为 `min(a1,a2,...an)` 重复不变函数而构建。
 * 通过更改几行代码，可以将此实现更改为其他函数，如
 * `gcd()`、`lcm()` 和 `max()`。
 */

#include <array>     /// for std::array
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace data_structures
 * @brief 数据结构算法
 */
namespace data_structures {

/**
 * @namespace sparse_table
 * @brief 实现 [Sparse Table](https://brilliant.org/wiki/sparse-table/) 的函数
 */
namespace sparse_table {

/**
 * @brief 表示稀疏表的结构，`min()` 为其不变函数，用于给定数组 `A`。
 * 查询的答案存储在数组 ST 中。
 */
constexpr uint32_t N = 12345;  ///< 数组的最大大小。
constexpr uint8_t M = 14;      ///< ceil(log2(N))。

struct Sparse_table {
    size_t n = 0;  ///< 输入数组的大小。

    /** @warning 检查 `N` 是否不小于 `n`。如果是，请手动增加 `N` 的值 */

    std::array<int64_t, N> A = {};  ///< 用于执行 RMQ 的输入数组。
    std::array<std::array<int64_t, N>, M>
        ST{};  ///< 存储给定区间的 `min()` 值的稀疏表。
    std::array<int64_t, N> LOG = {};  ///< 预计算的 `floor(log2(i))`。

    /**
     * @brief 构建稀疏表，以便计算任意连续子段的 min/max/gcd/lcm/...等
     * 这是计算最小值索引的示例。
     * @return void
     * @complexity: O(n.log(n))
     */
    void buildST() {
        LOG[0] = -1;

        for (size_t i = 0; i < n; ++i) {
            ST[0][i] = static_cast<int64_t>(i);
            LOG[i + 1] = LOG[i] + !(i & (i + 1));  ///< 预计算 `log2(i+1)`
        }

        for (size_t j = 1; static_cast<size_t>(1 << j) <= n; ++j) {
            for (size_t i = 0; static_cast<size_t>(i + (1 << j)) <= n; ++i) {
                /**
                 * @note 注意我们如何处理长度为 `pow(2,i)` 的范围，
                 * 我们可以重用为长度为 `pow(2,i-1)` 的范围所做的计算。
                 *
                 * 因此，ST[j][i] = min( ST[j-1][i], ST[j-1][i + pow(2,j-1)])。
                 * @example ST[2][3] = min(ST[1][3], ST[1][5])
                 */

                int64_t x = ST[j - 1][i];  ///< 表示范围 [j,i] 内的最小值
                int64_t y =
                    ST[j - 1]
                      [i + (1 << (j - 1))];  ///< 表示范围 [j,i + pow(2,j-1)] 内的最小值

                ST[j][i] =
                    (A[x] <= A[y] ? x : y);  ///< 表示范围 [j,i] 内的最小值
            }
        }
    }

    /**
     * @brief 查询稀疏表，获取区间 [l, r] 的值
     * (即从 l 到 r 包含在内)。
     * @param l 区间的左索引（包含）。
     * @param r 区间的右索引（包含）。
     * @return 计算得到的给定区间的值。
     * @complexity: O(1)
     */
    int64_t query(int64_t l, int64_t r) {
        int64_t g = LOG[r - l + 1];  ///< 覆盖 [l,r] 的最小 2 的幂
        int64_t x = ST[g][l];  ///< 表示范围 [g,l] 内的最小值
        int64_t y =
            ST[g][r - (1 << g) + 1];  ///< 表示范围 [g, r - pow(2,g) + 1] 内的最小值

        return (A[x] <= A[y] ? x : y);  ///< 表示整个范围 [l,r] 内的最小值
    }
};
}  // namespace sparse_table
}  // namespace data_structures

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    /* 我们以数组作为输入，在其上需要执行范围最小查询[RMQ](https://en.wikipedia.org/wiki/Range_minimum_query) */
    std::array<int64_t, 10> testcase = {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10};  ///< 将在其上执行 RMQ 的数组。
    size_t testcase_size =
        sizeof(testcase) / sizeof(testcase[0]);  ///< 自测数组的大小

    data_structures::sparse_table::Sparse_table
        st{};  ///< 声明稀疏树

    std::copy(std::begin(testcase), std::end(testcase),
              std::begin(st.A));  ///< 将数组复制到结构中
    st.n = testcase_size;         ///< 将数组大小传递给结构

    st.buildST();  ///< 预计算稀疏树

    // 传递查询形式: [l,r]
    assert(st.query(1, 9) == 1);  ///< 从 1 到 9 中最小的是 1
    assert(st.query(2, 6) == 2);  ///< 从 2 到 6 中最小的是 2
    assert(st.query(3, 8) == 3);  ///< 从 3 到 8 中最小的是 3

    std::cout << "自测实现通过！" << std::endl;
}

/**
 * @brief 主函数
 * @param argc 命令行参数计数（被忽略）
 * @param argv 命令行参数数组（被忽略）
 * @returns 0 退出
 */
int main(int argc, char *argv[]) {
    test();  // 运行自测实现
    return 0;
}
