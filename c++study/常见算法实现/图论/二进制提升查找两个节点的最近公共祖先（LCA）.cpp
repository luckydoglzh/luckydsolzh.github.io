/**
 *
 * \file
 *
 * \brief 使用二进制提升找到根树中两个节点的最低公共祖先的数据结构
 *
 * \details
 * 算法链接: https://cp-algorithms.com/graph/lca_binary_lifting.html
 *
 * 复杂度：
 *   - 预处理： \f$O(N \log N)\f$，其中 \f$N\f$ 是树中的节点数
 *   - 查询： \f$O(\log N)\f$
 *   - 空间： \f$O(N \log N)\f$
 *
 * 示例：
 * <br/>  树：
 * <pre>
 *             _  3  _
 *          /     |     \
 *        1       6       4
 *      / |     /   \       \
 *    7   5   2       8       0
 *            |
 *            9
 * </pre>
 *
 * <br/>  lowest_common_ancestor(7, 4) = 3
 * <br/>  lowest_common_ancestor(9, 6) = 6
 * <br/>  lowest_common_ancestor(0, 0) = 0
 * <br/>  lowest_common_ancestor(8, 2) = 6
 *
 *   查询是对称的，因此
 *     lowest_common_ancestor(x, y) = lowest_common_ancestor(y, x)
 */

#include <cassert>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

/**
 * \namespace graph
 * \brief 图算法
 */
namespace graph {
/**
 * 表示一个图的类，使用邻接列表表示法。
 * 其顶点索引为 0, 1, ..., N - 1。
 */
class Graph {
 public:
    /**
     * \brief 为图中每个顶点填充邻接列表。
     * 假设每条边都是一对有效的顶点索引。
     *
     * @param N 图中顶点的数量
     * @param undirected_edges 图的无向边列表
     */
    Graph(size_t N, const std::vector<std::pair<int, int> > &undirected_edges) {
        neighbors.resize(N);
        for (auto &edge : undirected_edges) {
            neighbors[edge.first].push_back(edge.second);
            neighbors[edge.second].push_back(edge.first);
        }
    }

    /**
     * 获取图中顶点的数量
     * @return 图中的顶点数量
     */
    int number_of_vertices() const { return neighbors.size(); }

    /** \brief 每个顶点存储其邻居的索引列表 */
    std::vector<std::vector<int> > neighbors;
};

/**
 * 表示一棵根树。为每个顶点预计算其父节点。
 */
class RootedTree : public Graph {
 public:
    /**
     * \brief 通过计算每个顶点的父节点构造树。
     * 假设提供了有效的树描述。
     *
     * @param undirected_edges 图的无向边列表
     * @param root_ 根节点的索引
     */
    RootedTree(const std::vector<std::pair<int, int> > &undirected_edges,
               int root_)
        : Graph(undirected_edges.size() + 1, undirected_edges), root(root_) {
        populate_parents();
    }

    /**
     * \brief 存储每个顶点的父节点，根节点的父节点为其自身的索引。
     * 根节点技术上不是自己的父节点，但在最低公共祖先算法中非常实用。
     */
    std::vector<int> parent;
    /** \brief 存储从根节点的距离。 */
    std::vector<int> level;
    /** \brief 根节点的索引。 */
    int root;

 protected:
    /**
     * \brief 计算树中所有顶点的父节点。
     * 从根节点开始，使用广度优先搜索遍历整棵树，并为所有顶点标记父节点。
     * @returns 无
     */
    void populate_parents() {
        // 用 -1 初始化向量，表示该顶点尚未被访问。
        parent = std::vector<int>(number_of_vertices(), -1);
        level = std::vector<int>(number_of_vertices());
        parent[root] = root;  // 将根的父节点设置为其自身
        level[root] = 0;       // 根的层级为 0
        std::queue<int> queue_of_vertices;  // 存储待处理的顶点
        queue_of_vertices.push(root);
        while (!queue_of_vertices.empty()) {
            int vertex = queue_of_vertices.front();
            queue_of_vertices.pop();
            for (int neighbor : neighbors[vertex]) {
                // 只要该顶点尚未被访问。
                if (parent[neighbor] == -1) {
                    parent[neighbor] = vertex;  // 设置父节点
                    level[neighbor] = level[vertex] + 1;  // 更新层级
                    queue_of_vertices.push(neighbor);
                }
            }
        }
    }
};

/**
 * 一个结构体，持有一棵根树，并允许有效查询两给定顶点在树中的最低公共祖先。
 */
class LowestCommonAncestor {
 public:
    /**
     * \brief 存储树并预计算“向上提升”。
     * @param tree_ 根树。
     */
    explicit LowestCommonAncestor(const RootedTree &tree_) : tree(tree_) {
        populate_up();
    }

    /**
     * \brief 查询结构以找到最低公共祖先。
     * 假设提供的数字是有效的顶点索引。
     * 迭代性地修改（"提升"）u 和 v 直到找到它们的最低公共祖先。
     * @param u 其中一个查询顶点的索引
     * @param v 另一个查询顶点的索引
     * @return u 和 v 的最低公共祖先的索引
     */
    int lowest_common_ancestor(int u, int v) const {
        // 确保 u 是两个顶点中层级更深的（更高层级）
        if (tree.level[v] > tree.level[u]) {
            std::swap(u, v);
        }

        // 将 u 提升到与 v 相同的层级。
        int level_diff = tree.level[u] - tree.level[v];
        for (int i = 0; (1 << i) <= level_diff; ++i) {
            if (level_diff & (1 << i)) {
                u = up[u][i];  // 提升 u
            }
        }
        assert(tree.level[u] == tree.level[v]);  // 确保层级相同

        if (u == v) {
            return u;  // 如果相等，则返回 u
        }

        // 同时提升 u 和 v，直到它们的祖先不再相同
        for (int i = static_cast<int>(up[u].size()) - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }

        // 返回它们的父节点作为结果
        assert(up[u][0] == up[v][0]);
        return up[u][0];
    }

    /* \brief 引用该结构允许查询的根树 */
    const RootedTree &tree;
    /**
     * \brief 对于每个顶点，存储其祖先的列表，按 2 的幂次存储
     * 每个顶点的列表的第一个元素包含其父节点的索引。
     * 第 i 个元素是该顶点的 (2^i) 祖先的索引。
     */
    std::vector<std::vector<int> > up;

 protected:
    /**
     * 填充“up”结构。见上文。
     */
    void populate_up() {
        up.resize(tree.number_of_vertices());
        for (int vertex = 0; vertex < tree.number_of_vertices(); ++vertex) {
            up[vertex].push_back(tree.parent[vertex]);
        }
        for (int level = 0; (1 << level) < tree.number_of_vertices(); ++level) {
            for (int vertex = 0; vertex < tree.number_of_vertices(); ++vertex) {
                // up[vertex][level + 1] = 2^(level + 1) 祖先的索引
                up[vertex].push_back(up[up[vertex][level]][level]);
            }
        }
    }
};

}  // namespace graph

/**
 * 单元测试
 * @returns none
 */
static void tests() {
    /**
     *             _  3  _
     *          /     |     \
     *        1       6       4
     *      / |     /   \       \
     *    7   5   2       8       0
     *            |
     *            9
     */
    std::vector<std::pair<int, int> > edges = {
        {7, 1}, {1, 5}, {1, 3}, {3, 6}, {6, 2}, {2, 9}, {6, 8}, {4, 3}, {0, 4}};
    graph::RootedTree t(edges, 3);
    graph::LowestCommonAncestor lca(t);
    assert(lca.lowest_common_ancestor(7, 4) == 3);
    assert(lca.lowest_common_ancestor(9, 6) == 6);
    assert(lca.lowest_common_ancestor(0, 0) == 0);
    assert(lca.lowest_common_ancestor(8, 2) == 6);
}

/** 主函数 */
int main() {
    tests();  // 运行测试
    return 0;
}
