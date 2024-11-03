/**
 * @file
 * @brief 一个用于快速进行范围操作的数据结构：线段树（Segment Tree）算法实现
 * @details
 * 线段树数据结构的实现
 *
 * 可以进行点更新（更新某个位置的值）
 * 和范围查询，返回某个范围内的某种结合操作的值
 *
 * 这两种操作的时间复杂度为 O(log N)
 * @author [Nishant Chatterjee](https://github.com/nishantc1527)
 */

#include <iostream>     /// 用于输入输出操作
#include <vector>       /// 用于 std::vector
#include <algorithm>    /// 用于 std::min 和 std::max
#include <cassert>      /// 用于 assert

/*
 * @namespace
 * @brief 数据结构
 */
namespace data_structures {
/**
 * @brief 线段树的类表示
 * @tparam T 数据结构中元素的类型
 */
template <class T>
class SegmentTree {
private:
    const T ID = 0;   ///< ID元素，用于结合操作的单位元素
    std::vector<T> t; ///< 用于表示树的向量
    int size = 0;     ///< 可查询的树中元素的数量
private:
    /**
     * @brief 任何结合性函数，用于结合两个值
     * @param x 第一个操作数
     * @param y 第二个操作数
     * @return 对这两个值应用的某种结合操作。在这里，我们使用加法
     */
    T comb(T x, T y) {
        return x + y;  // 返回两个值的和
    }
    /**
     * @brief 获取两个整数之间的中点
     * @param l 左端点
     * @param r 右端点
     * @return 它们之间的中点
     */
    int mid(int l, int r) {
        return l + (r - l) / 2;  // 计算中点
    }
    /**
     * @brief 更新方法的辅助方法
     * @param i 当前节点的索引
     * @param l 当前节点的最左边的节点
     * @param r 当前节点的最右边的节点
     * @param pos 要更新的位置
     * @param val 要更新的值
     */
    void update(int i, int l, int r, int pos, T val) {
        if(l == r) t[i] = val;  // 如果当前节点是要更新的节点，直接更新值
        else {
            int m = mid(l, r);  // 计算中点
            if(pos <= m) update(i * 2, l, m, pos, val);  // 如果位置在左半边，递归更新左子树
            else update(i * 2 + 1, m + 1, r, pos, val);  // 否则更新右子树
            t[i] = comb(t[i * 2], t[i * 2 + 1]);  // 更新当前节点的值
        }
    }
    /**
     * @brief 范围结合操作的辅助方法
     * @param i 当前节点
     * @param l 当前节点的最左边的节点
     * @param r 当前节点的最右边的节点
     * @param tl 范围的左端点
     * @param tr 范围的右端点
     * @return 对 tl 和 tr 之间所有值应用结合操作的结果
     */
    T range_comb(int i, int l, int r, int tl, int tr) {
        if(l == tl && r == tr) return t[i];  // 如果当前节点的范围与查询范围相同，直接返回节点值
        if(tl > tr) return 0;  // 如果范围不合法，返回单位元素
        int m = mid(l, r);  // 计算中点
        // 递归查询左右子树的结果，并进行结合操作
        return comb(range_comb(i * 2, l, m, tl, std::min(tr, m)), 
                    range_comb(i * 2 + 1, m + 1, r, std::max(tl, m + 1), tr));
    }
public:
    SegmentTree(int n) : t(n * 4, ID), size(n) {}  // 初始化线段树，大小为 4n，所有值为 ID
    /** 
     * @brief 在某个位置更新值
     * @param pos 要更新的位置
     * @param val 要更新的值
     */
    void update(int pos, T val) {
        update(1, 1, size, pos, val);  // 从根节点开始更新
    }
    /**
     * @brief 返回范围 [l, r] 内的结合操作的结果
     * @param l 范围的左端点
     * @param r 范围的右端点
     * @return 结合操作的值
     */
    T range_comb(int l, int r) {
        return range_comb(1, 1, size, l, r);  // 从根节点开始查询
    }
}; 
} // namespace data_structures

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    data_structures::SegmentTree<int> t(5);  // 创建一个大小为 5 的线段树
    t.update(1, 1);  // 更新位置 1 的值为 1
    t.update(2, 2);  // 更新位置 2 的值为 2
    t.update(3, 3);  // 更新位置 3 的值为 3
    t.update(4, 4);  // 更新位置 4 的值为 4
    t.update(5, 5);  // 更新位置 5 的值为 5
    assert(t.range_comb(1, 3) == 6); // 查询范围 [1, 3] 的和，1 + 2 + 3 = 6
    t.update(1, 3);  // 更新位置 1 的值为 3
    assert(t.range_comb(1, 3) == 8); // 再次查询范围 [1, 3] 的和，3 + 2 + 3 = 8

    std::cout << "所有测试都成功通过!\n";  // 输出测试成功信息
}

/**
 * @brief 主函数
 * @returns 0 正常退出
 */
int main() {
    test();  // 运行自测实现
    return 0;  // 返回成功
}
