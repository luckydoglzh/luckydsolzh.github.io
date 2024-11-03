/**
 * @file
 *
 * @brief 检查图是否为 [二分图](https://en.wikipedia.org/wiki/Bipartite_graph)
 *
 * @details
 * 图是节点（也称为顶点）的集合，这些顶点通过边连接。 
 * 如果一个图的顶点可以分成两个不相交且独立的集合 U 和 V， 
 * 并且每条边都连接 U 中的一个顶点与 V 中的一个顶点，则该图为二分图。
 *
 * 本文件实现的算法确定给定的图是否为二分图。
 *
 * <pre>
 *  示例 - 这是一个有 5 个顶点的图 g1，且它是二分图
 *
 *     1   4
 *    / \ / \
 *   2   3   5
 *
 * 示例 - 这是一个有 3 个顶点的图 G2，且它不是二分图
 *
 *   1 --- 2
 *    \   /
 *      3
 *
 * </pre>
 *
 * @author [Akshat Vaya](https://github.com/AkVaya)
 *
 */
#include <iostream>
#include <queue>
#include <vector>

/**
 * @namespace graph
 * @brief 图算法
 */
namespace graph {
/**
 * @namespace is_graph_bipartite
 * @brief 检查图是否为二分图的函数
 */
namespace is_graph_bipartite {
/**
 * @brief 以邻接列表形式表示图的类。
 */
class Graph {
 private:
    int n;  ///< 图的顶点数量

    std::vector<std::vector<int>> adj;  ///< 存储图的邻接列表

    std::vector<int> side;  ///< 存储每个顶点所在的集合

 public:
    /**
     * @brief 构造函数，初始化图
     * @param size 图的顶点数量
     */
    explicit Graph(int size) {
        n = size;
        adj.resize(n);  // 初始化邻接列表
        side.resize(n, -1);  // 初始化侧边，-1 表示未分配
    }

    void addEdge(int u, int v);  ///< 添加边的函数

    bool is_bipartite();  ///< 检查图是否为二分图的函数
};

/**
 * @brief 添加图中两个节点（顶点）之间的边
 *
 * @param u 图中的一个节点或顶点
 * @param v 图中的另一个节点或顶点
 */
void Graph::addEdge(int u, int v) {
    adj[u - 1].push_back(v - 1);  // 将 v 添加到 u 的邻接列表中
    adj[v - 1].push_back(u - 1);  // 将 u 添加到 v 的邻接列表中
}

/**
 * @brief 检查图是否为二分图
 * 如果图是二分图，则返回 true；否则返回 false。
 *
 * @details
 * 这里，side 表示二分图的两个不相交子集。
 * 初始时，side 的值设为 -1，表示未分配状态。
 * 对于图中的每个顶点，如果当前边未分配侧边，则执行广度优先搜索（BFS）。
 * 如果两个邻居具有相同的侧边，则图不是二分图，返回 false。
 * 如果每对邻居具有不同的侧边，则图是二分图，返回 true。
 *
 * @returns `true` 如果图是二分图
 * @returns `false` 否则
 */
bool Graph::is_bipartite() {
    bool check = true;  // 用于记录图是否为二分图
    std::queue<int> q;  // BFS 队列

    // 遍历每个顶点
    for (int current_edge = 0; current_edge < n; ++current_edge) {
        // 如果当前顶点未分配侧边
        if (side[current_edge] == -1) {
            q.push(current_edge);  // 将顶点加入队列
            side[current_edge] = 0;  // 分配侧边 0
            while (q.size()) {
                int current = q.front();  // 当前顶点出队
                q.pop();
                // 遍历当前顶点的所有邻接顶点
                for (auto neighbour : adj[current]) {
                    if (side[neighbour] == -1) {
                        side[neighbour] = (1 ^ side[current]);  // 分配相反的侧边
                        q.push(neighbour);  // 将邻接顶点加入队列
                    } else {
                        check &= (side[neighbour] != side[current]);  // 检查是否有相同侧边
                    }
                }
            }
        }
    }
    return check;  // 返回图是否为二分图的结果
}
}  // namespace is_graph_bipartite
}  // namespace graph

/**
 * 测试上述算法的函数
 * @returns none
 */
static void test() {
    graph::is_graph_bipartite::Graph G1(5);  ///< 创建图 G1，包含 5 个顶点
    /// 根据示例添加边
    G1.addEdge(1, 2);
    G1.addEdge(1, 3);
    G1.addEdge(3, 4);
    G1.addEdge(4, 5);

    graph::is_graph_bipartite::Graph G2(3);  ///< 创建图 G2，包含 3 个顶点
    /// 根据示例添加边
    G2.addEdge(1, 2);
    G2.addEdge(1, 3);
    G2.addEdge(2, 3);

    /// 检查图是否为二分图
    if (G1.is_bipartite()) {
        std::cout << "给定的图 G1 是一个二分图\n";
    } else {
        std::cout << "给定的图 G1 不是一个二分图\n";
    }
    if (G2.is_bipartite()) {
        std::cout << "给定的图 G2 是一个二分图\n";
    } else {
        std::cout << "给定的图 G2 不是一个二分图\n";
    }
}

/**
 * 主函数
 */
int main() {
    test();  ///< 测试
    return 0;
}
