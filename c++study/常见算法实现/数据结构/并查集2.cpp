/**
 * @file
 * @brief [并查集 (Disjoint sets)](https://en.wikipedia.org/wiki/Disjoint-set_data_structure)
 * @details
 * 并查集是一种非常强大的数据结构，用于跟踪不同元素的不同簇（集合），这些集合是互斥的（没有公共元素）。
 * 并查集的应用场景：查找图中的连通分量，使用于 Kruskal 算法寻找最小生成树。
 * 可以执行的操作：
 * 1) UnionSet(i,j)：将元素 i 和 j 添加到同一集合中
 * 2) findSet(i)：返回 i 所在集合的代表元素
 * 3) getParents(i)：打印 i 的父节点，依此类推。
 * 以下是基于类的实现，使用了秩（rank）的启发式方法。
 * 使用秩来在 findSet(i) 中找到 i 的代表元素，能在略微延迟的 O(logN) 时间内获得，但也能保持对 i 的父节点的追踪。
 * @author [AayushVyasKIIT](https://github.com/AayushVyasKIIT)
 * @see dsu_path_compression.cpp
 */

#include <cassert>   /// 用于 assert
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于 std::vector

using std::cout;
using std::endl;
using std::vector;

/**
 * @brief 并查集数据结构，基于类的表示
 * @param n 元素数量
 */
class dsu {
 private:
    vector<uint64_t> p;        ///< 记录第 i 个元素的父节点
    vector<uint64_t> depth;    ///< 记录树中第 i 个节点的深度（秩）
    vector<uint64_t> setSize;  ///< 每个集合的大小
 public:
    /**
     * @brief 构造函数，用于初始化所有数据成员
     * @param n 元素数量
     */
    explicit dsu(uint64_t n) {
        p.assign(n, 0);
        /// 初始时，所有元素都是自己的父节点
        depth.assign(n, 0);
        setSize.assign(n, 0);
        for (uint64_t i = 0; i < n; i++) {
            p[i] = i;         // 初始化每个元素的父节点为其自身
            depth[i] = 0;     // 初始化深度为 0
            setSize[i] = 1;   // 初始化每个集合的大小为 1
        }
    }

    /**
     * @brief 找到元素 i 所在集合的代表元素
     * T(n) = O(logN)
     * @param i 某个集合的元素
     * @returns i 所在集合的代表元素
     */
    uint64_t findSet(uint64_t i) {
        /// 使用秩的启发式方法
        while (i != p[i]) {
            i = p[i];  // 一直找到代表元素
        }
        return i;
    }

    /**
     * @brief 合并两个不相交的集合，i 和 j 所在的集合合并为一个集合
     * @param i 某个集合的元素
     * @param j 某个集合的元素
     * @returns void
     */
    void unionSet(uint64_t i, uint64_t j) {
        /// 检查 i 和 j 是否属于同一集合
        if (isSame(i, j)) {
            return; // 已经在同一集合中
        }
        /// 找到 i 和 j 的代表元素
        uint64_t x = findSet(i);
        uint64_t y = findSet(j);

        /// 始终保持较小的元素为 x，以创建较浅的树
        if (depth[x] > depth[y]) {
            std::swap(x, y); // 交换 x 和 y
        }
        /// 将较浅树的根节点的父节点设为较深树的根节点
        p[x] = y;

        /// 如果深度相同，增加较深树的深度
        if (depth[x] == depth[y]) {
            depth[y]++;
        }
        /// 更新合并后的集合的大小
        setSize[y] += setSize[x];
    }

    /**
     * @brief 检查元素 i 和 j 是否属于同一集合
     * @param i 某个集合的元素
     * @param j 某个集合的元素
     * @returns 如果元素 i 和 j 在同一集合中返回 true，否则返回 false
     */
    bool isSame(uint64_t i, uint64_t j) {
        return findSet(i) == findSet(j); // 如果代表元素相同则在同一集合中
    }

    /**
     * @brief 打印元素 i 所在集合的所有父节点，或从 i 到代表元素的路径
     * @param i 某个集合的元素
     * @returns void
     */
    vector<uint64_t> getParents(uint64_t i) {
        vector<uint64_t> ans;
        while (p[i] != i) {
            ans.push_back(i); // 记录当前节点
            i = p[i];        // 移动到父节点
        }
        ans.push_back(i); // 添加代表元素
        return ans;
    }
};

/**
 * @brief 自测试实现，第一组测试
 * @returns void
 */
static void test1() {
    /* 检查结果结构中的父节点 */
    uint64_t n = 10;   ///< 元素数量
    dsu d(n + 1);      ///< 创建并查集对象
    d.unionSet(2, 1);  ///< 对 1 和 2 进行合并操作
    d.unionSet(1, 4);
    d.unionSet(8, 1);
    d.unionSet(3, 5);
    d.unionSet(5, 6);
    d.unionSet(5, 7);
    d.unionSet(9, 10);
    d.unionSet(2, 10);
    // 跟踪父节点的变化
    vector<uint64_t> ans = {7, 5};
    for (uint64_t i = 0; i < ans.size(); i++) {
        assert(d.getParents(7).at(i) == ans[i]); // 确保算法工作正常
    }
    cout << "1st test passed!" << endl;
}

/**
 * @brief 自测试实现，第二组测试
 * @returns void
 */
static void test2() {
    // 检查结果结构中的父节点
    uint64_t n = 10;   ///< 元素数量
    dsu d(n + 1);      ///< 创建并查集对象
    d.unionSet(2, 1);  ///< 对 1 和 2 进行合并操作
    d.unionSet(1, 4);
    d.unionSet(8, 1);
    d.unionSet(3, 5);
    d.unionSet(5, 6);
    d.unionSet(5, 7);
    d.unionSet(9, 10);
    d.unionSet(2, 10);

    /// 跟踪父节点的变化
    vector<uint64_t> ans = {2, 1, 10};
    for (uint64_t i = 0; i < ans.size(); i++) {
        assert(d.getParents(2).at(i) == ans[i]); // 确保算法工作正常
    }
    cout << "2nd test passed!" << endl;
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    test1();  // 运行第一组测试
    test2();  // 运行第二组测试

    return 0; // 正常退出
}
