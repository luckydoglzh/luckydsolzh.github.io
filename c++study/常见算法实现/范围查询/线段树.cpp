/**
 * @file
 * @brief   实现 [线段树（Segment Tree）](https://en.wikipedia.org/wiki/Segment_tree) 数据结构
 *
 * @details
 * 线段树是一种树形数据结构，用于存储关于区间或区段的信息。它的经典版本允许查询哪些存储的区间包含给定的点，
 * 但我们的修改允许我们对数组中的任意范围执行（查询）任何二进制操作，查询时间复杂度为 O(logN)。
 * 在此实现中，我们使用的是加法 (+) 操作。
 * 对于区间更新，我们使用了懒标记传播（Lazy Propagation）。
 *
 * * 空间复杂度 : O(NlogN) \n
 * * 构建时间复杂度 : O(NlogN) \n
 * * 查询时间复杂度 : O(logN) \n
 *
 * @author  [Madhav Gaba](https://github.com/madhavgaba)
 * @author  [Soham Roy](https://github.com/sohamroy19)
 */

#include <cassert>   /// 用于断言操作
#include <cmath>     /// 用于计算 log2
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于 std::vector 容器

/**
 * @brief   构建初始的线段树
 *
 * @param   arr 输入数组，用于构建树
 * @param   segtree 线段树
 * @param   low 输入数组的最小索引
 * @param   high 输入数组的最大索引
 * @param   pos 当前线段树的节点索引
 * @returns void
 */
void ConsTree(const std::vector<int64_t> &arr, std::vector<int64_t> *segtree,
              uint64_t low, uint64_t high, uint64_t pos) {
    if (low == high) {
        (*segtree)[pos] = arr[low];  // 叶节点存储数组的元素
        return;
    }

    uint64_t mid = (low + high) / 2;
    ConsTree(arr, segtree, low, mid, 2 * pos + 1);  // 递归构建左子树
    ConsTree(arr, segtree, mid + 1, high, 2 * pos + 2);  // 递归构建右子树
    (*segtree)[pos] = (*segtree)[2 * pos + 1] + (*segtree)[2 * pos + 2];  // 当前节点存储左右子树的和
}

/**
 * @brief   返回指定区间的元素和
 *
 * @param   segtree 线段树
 * @param   lazy 懒标记数组，用于懒标记传播
 * @param   qlow 查询区间的下界
 * @param   qhigh 查询区间的上界
 * @param   low 当前区间的下界
 * @param   high 当前区间的上界
 * @param   pos 当前线段树的节点索引
 * @return  当前区间查询的结果
 */
int64_t query(std::vector<int64_t> *segtree, std::vector<int64_t> *lazy,
              uint64_t qlow, uint64_t qhigh, uint64_t low, uint64_t high,
              uint64_t pos) {
    if (low > high || qlow > high || low > qhigh) {  // 无交集时，返回 0
        return 0;
    }

    // 如果该节点有未处理的懒标记
    if ((*lazy)[pos] != 0) {
        (*segtree)[pos] += (*lazy)[pos] * (high - low + 1);  // 更新节点

        if (low != high) {  // 不是叶节点，继续标记子节点
            (*lazy)[2 * pos + 1] += (*lazy)[pos];
            (*lazy)[2 * pos + 2] += (*lazy)[pos];
        }
        (*lazy)[pos] = 0;  // 清除当前节点的懒标记
    }

    if (qlow <= low && qhigh >= high) {  // 当前区间完全包含查询区间，直接返回该区间的和
        return (*segtree)[pos];
    }

    uint64_t mid = (low + high) / 2;

    // 递归查询左右子树
    return query(segtree, lazy, qlow, qhigh, low, mid, 2 * pos + 1) +
           query(segtree, lazy, qlow, qhigh, mid + 1, high, 2 * pos + 2);
}

/**
 * @brief   更新线段树的指定区间
 *
 * @param   segtree 线段树
 * @param   lazy 懒标记数组，用于懒标记传播
 * @param   start 区间更新的起始索引
 * @param   end 区间更新的结束索引
 * @param   delta 需要添加的值
 * @param   low 当前区间的下界
 * @param   high 当前区间的上界
 * @param   pos 当前线段树的节点索引
 * @returns void
 */
void update(std::vector<int64_t> *segtree, std::vector<int64_t> *lazy,
            int64_t start, int64_t end, int64_t delta, uint64_t low,
            uint64_t high, uint64_t pos) {
    if (low > high) {
        return;
    }

    // 如果该节点有未处理的懒标记
    if ((*lazy)[pos] != 0) {
        (*segtree)[pos] += (*lazy)[pos] * (high - low + 1);

        if (low != high) {  // 不是叶节点，继续标记子节点
            (*lazy)[2 * pos + 1] += (*lazy)[pos];
            (*lazy)[2 * pos + 2] += (*lazy)[pos];
        }
        (*lazy)[pos] = 0;  // 清除当前节点的懒标记
    }

    if (start > high || end < low) {  // 区间不相交，直接返回
        return;
    }

    if (start <= low && end >= high) {  // 当前区间完全包含更新区间
        (*segtree)[pos] += delta * (high - low + 1);

        if (low != high) {  // 不是叶节点，继续标记子节点
            (*lazy)[2 * pos + 1] += delta;
            (*lazy)[2 * pos + 2] += delta;
        }

        return;
    }

    uint64_t mid = (low + high) / 2;

    // 递归更新左右子树
    update(segtree, lazy, start, end, delta, low, mid, 2 * pos + 1);
    update(segtree, lazy, start, end, delta, mid + 1, high, 2 * pos + 2);
    // 更新当前节点的值
    (*segtree)[pos] = (*segtree)[2 * pos + 1] + (*segtree)[2 * pos + 2];
}

/**
 * @brief   自我测试实现
 *
 * @returns void
 */
static void test() {
    auto max = static_cast<int64_t>(2 * pow(2, ceil(log2(7))) - 1);  // 线段树的最大节点数
    assert(max == 15);

    std::vector<int64_t> arr{1, 2, 3, 4, 5, 6, 7}, lazy(max), segtree(max);
    ConsTree(arr, &segtree, 0, 7 - 1, 0);  // 构建线段树

    // 查询区间 [1, 5] 的和
    assert(query(&segtree, &lazy, 1, 5, 0, 7 - 1, 0) == 2 + 3 + 4 + 5 + 6);

    // 更新区间 [2, 4]，每个元素加 1
    update(&segtree, &lazy, 2, 4, 1, 0, 7 - 1, 0);
    // 查询更新后的区间 [1, 5] 的和
    assert(query(&segtree, &lazy, 1, 5, 0, 7 - 1, 0) == 2 + 4 + 5 + 6 + 6);

    // 更新区间 [0, 6]，每个元素减 2
    update(&segtree, &lazy, 0, 6, -2, 0, 7 - 1, 0);
    // 查询更新后的区间 [0, 4] 的和
    assert(query(&segtree, &lazy, 0, 4, 0, 7 - 1, 0) == -1 + 0 + 2 + 3 + 4);
}

/**
 * @brief   主函数
 *
 * @return  0 退出
 */
int main() {
    test();  // 执行自我测试

    std::cout << "请输入元素数量: ";

    uint64_t n = 0;
    std::cin >> n;

    // 计算线段树的最大节点数
    auto max = static_cast<uint64_t>(2 * pow(2, ceil(log2(n))) - 1);
    std::vector<int64_t> arr(n), lazy(max), segtree(max);

    int choice = 0;
    std::cout << "\n是否手动输入每个数字？\n"
                 "1: 是\n"
                 "0: 否（默认初始化为 0）\n";

    std::cin >> choice;
    if (choice == 1) {
        std::cout << "请输入 " << n << " 个数字:\n";
        for (int i = 1; i <= n; i++) {
            std::cout << i << ": ";
            std::cin >> arr[i];
        }
    }

    // 构建线段树
    ConsTree(arr, &segtree, 0, n - 1, 0);

    do {
        std::cout << "\n请选择操作:\n"
                     "1: 区间更新 (输入)\n"
                     "2: 区间查询 (输出)\n"
                     "0: 退出\n";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "请输入 1 索引区间下界、上界和更新值:\n";

            uint64_t p = 1, q = 1, v = 0;
            std::cin >> p >> q >> v;
            update(&segtree, &lazy, p - 1, q - 1, v, 0, n - 1, 0);
        } else if (choice == 2) {
            std::cout << "请输入 1 索引区间下界和上界:\n";

            uint64_t p = 1, q = 1;
            std::cin >> p >> q;
            std::cout << query(&segtree, &lazy, p - 1, q - 1, 0, n - 1, 0);
            std::cout << "\n";
        }
    } while (choice > 0);

    return 0;
}
