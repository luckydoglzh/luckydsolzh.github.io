/**
 * @file
 * @brief [树状数组](https://en.wikipedia.org/wiki/Fenwick_tree)算法实现
 * @details
 * _来自维基百科，自由百科全书。_
 *
 * 树状数组或二进制索引树（BIT）是一种巧妙的数据结构实现，称为二项树。它可以通过累加、关联和具有逆运算的操作来更新值和解决范围查询。它还可以解决不可变范围查询（最小/最大），当操作仅对该类型的元素是关联时。通过存储冗余信息（如最大/最小范围查询）可以去掉其中一些限制。
 *
 * @author [Mateusz Grzegorzek](https://github.com/mateusz-grzegorzek)
 * @author [David Leal](https://github.com/Panquesito7)
 */

#include <cassert>   /// 用于 assert
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于 std::vector

/**
 * @namespace
 * @brief 范围查询
 */
namespace range_queries {
/**
 * @brief 初始化树状数组的类。
 */
class fenwick_tree {
    size_t n = 0;            ///< 输入数组中元素的数量
    std::vector<int> bit{};  ///< 表示二进制索引树的数组。

    /**
     * @brief 返回不大于 `x` 的最大2的幂。
     * @param x 原始数组中元素的索引。
     * @return 索引的偏移量。
     */
    inline int offset(int x) { return (x & (-x)); }
 public:
    /**
     * @brief 类构造函数
     * @tparam T 数组的类型
     * @param[in] arr 用于计算前缀和的输入数组。
     * @return void
     */
    template <typename T>
    explicit fenwick_tree(const std::vector<T>& arr) : n(arr.size()) {
        bit.assign(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            update(i, arr[i]);
        }
    }

    /**
     * @brief 类构造函数
     * @tparam T 变量的类型
     * @param[in] x 表示二进制索引树的数组大小。
     * @return void
     */
    template <typename T>
    explicit fenwick_tree(T x) : n(x) { bit.assign(n + 1, 0); }

    /**
     * @brief 更新原始数组中元素的值，并相应地更新BIT数组中的值。
     * @tparam T 变量的类型
     * @param id 原始数组中元素的索引。
     * @param val 用于更新元素值的值。
     * @return void
     */
    template <typename T>
    void update(T id, T val) {
        id++;
        while (id <= n) {
            bit[id] += val;
            id += offset(id);
        }
    }

    /**
     * @brief 返回从0到ID的元素和。
     * @tparam T 变量的类型
     * @param id 原始数组中用于计算和的索引。
     * @return 从0到id的元素和。
     */
    template <typename T>
    int sum(T id) {
        id++;
        T res = 0;
        while (id > 0) {
            res += bit[id];
            id -= offset(id);
        }
        return res;
    }

    /**
     * @brief 返回从L到R的前缀和。
     * @param l 范围的左索引。
     * @param r 范围的右索引。
     * @return 从L到R的元素和。
     */
    int sum_range(int l, int r) { return sum(r) - sum(l - 1); }
};
}  // namespace range_queries

/**
 * @brief 自测试实现
 * @returns void
 */
static void tests() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    range_queries::fenwick_tree fenwick_tree(arr);

    assert(fenwick_tree.sum_range(0, 0) == 1);
    assert(fenwick_tree.sum_range(0, 1) == 3);
    assert(fenwick_tree.sum_range(0, 2) == 6);
    assert(fenwick_tree.sum_range(0, 3) == 10);
    assert(fenwick_tree.sum_range(0, 4) == 15);

    fenwick_tree.update(0, 6);
    std::cout << "所有测试均已成功通过！\n";
}

/**
 * @brief 主函数
 * @returns 0 退出时返回
 */
int main() {
    tests();  // 运行自测试实现
    return 0;
}
