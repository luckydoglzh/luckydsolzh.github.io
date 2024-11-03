/**
 * @file
 * @brief 基于二叉搜索树和堆的平衡二叉搜索树（BST）：Treap 算法实现
 *
 * @details
 * Treap 数据结构的实现
 *
 * 支持的操作包括插入、删除和查询（指定元素的排名或排名为 x 的元素），与 BST 类似
 *
 * 这些操作的时间复杂度为 O(log N)，因为 Treap 通过旋转操作保持堆的属性，并且树的期望深度为 O(log N)。
 * 它几乎不可能退化为像 BST 一样的链。
 *
 * @author [Kairao ZHENG](https://github.com/fgmn)
 */

#include <array>     /// 用于数组
#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作

/**
 * @namespace
 * @brief 数据结构
 */
namespace data_structures {
/**
 * @namespace
 * @brief [Treap](https://en.wikipedia.org/wiki/Treap) 算法实现的函数
 */
namespace treap {
const int maxNode = 1e5 + 5;  ///< 最大节点数
/**
 * @brief Treap 的结构表示
 */
struct Treap {
    int root = 0;      ///< Treap 的根节点
    int treapCnt = 0;  ///< Treap 中当前节点的总数
    std::array<int, maxNode> key = {};       ///< 节点标识符
    std::array<int, maxNode> priority = {};  ///< 随机优先级
    std::array<std::array<int, 2>, maxNode> childs = {
        {}};  ///< [i][0] 表示节点 i 的左子节点， [i][1] 表示右子节点
    std::array<int, maxNode> cnt =
        {};  ///< 维护子树大小以供排名查询
    std::array<int, maxNode> size = {};  ///< 每个节点的副本数量
    /**
     * @brief 初始化
     */
    Treap() : treapCnt(1) {
        priority[0] = INT32_MAX;  // 初始化根节点的优先级为最大整数
        size[0] = 0;               // 初始化根节点的副本数量为 0
    }
    /**
     * @brief 更新节点的子树大小
     * @param x 要更新的节点
     */
    void update(int x) {
        size[x] = size[childs[x][0]] + cnt[x] + size[childs[x][1]];  // 更新当前节点的子树大小
    }
    /**
     * @brief 旋转而不破坏 BST 的属性
     * @param x 要旋转的节点
     * @param t 0 表示左旋，1 表示右旋
     */
    void rotate(int &x, int t) {
        int y = childs[x][t];
        childs[x][t] = childs[y][1 - t];
        childs[y][1 - t] = x;
        // 旋转只会改变自身及其子节点
        update(x);
        update(y);
        x = y;  // 更新 x 为旋转后的节点
    }
    /**
     * @brief 将值插入指定的子树（内部方法）
     * @param x 插入到节点 x 的子树中（通常 x = root）
     * @param k 要插入的键
     */
    void _insert(int &x, int k) {
        if (x) {
            if (key[x] == k) {
                cnt[x]++;  // 如果节点已存在，副本数量 ++
            } else {
                int t = (key[x] < k);  // 根据 BST 属性插入
                _insert(childs[x][t], k);
                // 插入后通过旋转保持堆的属性
                if (priority[childs[x][t]] < priority[x]) {
                    rotate(x, t);
                }
            }
        } else {  // 创建新节点
            x = treapCnt++;
            key[x] = k;
            cnt[x] = 1;
            priority[x] = rand();  // 随机优先级
            childs[x][0] = childs[x][1] = 0;
        }
        update(x);  // 更新节点的子树大小
    }
    /**
     * @brief 从指定的子树中删除值（内部方法）
     * @param x 从节点 x 的子树中删除（通常 x = root）
     * @param k 要删除的键
     */
    void _erase(int &x, int k) {
        if (key[x] == k) {
            if (cnt[x] > 1) {
                cnt[x]--;  // 如果节点有多个副本，副本数量 --
            } else {
                if (childs[x][0] == 0 && childs[x][1] == 0) {
                    x = 0;  // 如果没有子节点，删除并返回
                    return;
                }
                // 否则，需要旋转子节点并递归删除
                int t = (priority[childs[x][0]] > priority[childs[x][1]]);
                rotate(x, t);
                _erase(x, k);
            }
        } else {  // 根据 BST 属性查找目标值
            _erase(childs[x][key[x] < k], k);
        }
        update(x);  // 更新节点的子树大小
    }
    /**
     * @brief 查找第 K 大的值（内部方法）
     * @param x 查询节点 x 的子树（通常 x = root）
     * @param k 查询的排名
     * @return 排名为 k 的元素
     */
    int _get_k_th(int &x, int k) {
        if (k <= size[childs[x][0]]) {
            return _get_k_th(childs[x][0], k);  // 在左子树中继续查找
        }
        k -= size[childs[x][0]] + cnt[x];
        if (k <= 0) {
            return key[x];  // 找到目标元素
        }
        return _get_k_th(childs[x][1], k);  // 在右子树中继续查找
    }
    /**
     * @brief 查询指定元素的排名（内部方法）
     * @param x 查询节点 x 的子树（通常 x = root）
     * @param k 查询的元素
     * @return 元素 k 的排名
     */
    int _get_rank(int x, int k) {
        if (!x) {
            return 0;  // 如果节点不存在，返回 0
        }
        if (k == key[x]) {
            return size[childs[x][0]] + 1;  // 返回排名
        } else if (k < key[x]) {
            return _get_rank(childs[x][0], k);  // 在左子树中查找
        } else {
            return size[childs[x][0]] + cnt[x] + _get_rank(childs[x][1], k);  // 在右子树中查找
        }
    }
    /**
     * @brief 获取元素 k 的前驱节点
     * @param k 查询的元素
     * @return 前驱节点
     */
    int get_predecessor(int k) {
        int x = root, pre = -1;
        while (x) {
            if (key[x] < k) {
                pre = key[x], x = childs[x][1];  // 更新前驱节点
            } else {
                x = childs[x][0];  // 在左子树中继续查找
            }
        }
        return pre;  // 返回前驱节点
    }
    /**
     * @brief 获取元素 k 的后继节点
     * @param k 查询的元素
     * @return 后继节点
     */
    int get_next(int k) {
        int x = root, next = -1;
        while (x) {
            if (key[x] > k) {
                next = key[x], x = childs[x][0];  // 更新后继节点
            } else {
                x = childs[x][1];  // 在右子树中继续查找
            }
        }
        return next;  // 返回后继节点
    }
    /**
     * @brief 插入元素（外部方法）
     * @param k 要插入的键
     */
    void insert(int k) { _insert(root, k); }
    /**
     * @brief 删除元素（外部方法）
     * @param k 要删除的键
     */
    void erase(int k) { _erase(root, k); }
    /**
     * @brief 获取第 K 大的值（外部方法）
     * @param k 查询的排名
     * @return 排名为 x 的元素
     */
    int get_k_th(int k) { return _get_k_th(root, k); }
    /**
     * @brief 获取指定元素的排名（外部方法）
     * @param k 查询的元素
     * @return 元素 k 的排名
     */
    int get_rank(int k) { return _get_rank(root, k); }
};
}  // namespace treap
}  // namespace data_structures

/**
 * @brief 自我测试实现
 * @returns void
 */
static void test() {
    data_structures::treap::Treap mTreap;  ///< Treap 对象实例

    mTreap.insert(1);
    mTreap.insert(2);
    mTreap.insert(3);
    assert(mTreap.get_k_th(2) == 2);  // 验证第 2 大的元素
    mTreap.insert(4);
    mTreap.insert(5);
    mTreap.insert(6);
    assert(mTreap.get_next(4) == 5);  // 验证 4 的后继
    mTreap.insert(7);
    assert(mTreap.get_predecessor(7) == 6);  // 验证 7 的前驱
    mTreap.erase(4);
    assert(mTreap.get_k_th(4) == 5);  // 验证删除 4 后的第 4 大元素
    assert(mTreap.get_rank(5) == 4);   // 验证 5 的排名
    mTreap.insert(10);
    assert(mTreap.get_rank(10) == 7);  // 验证 10 的排名
    assert(mTreap.get_predecessor(10) == 7);  // 验证 10 的前驱

    std::cout << "所有测试均已成功通过！\n";
}
/**
 * @brief 主函数
 * @returns 0 以退出
 */
int main() {
    test();  // 运行自我测试实现
    return 0;
}
