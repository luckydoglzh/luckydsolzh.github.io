/**
 * @file
 * @brief [Dijkstra](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm) 算法实现
 * @details
 * _引自 Wikipedia。_
 * 
 * **Dijkstra 算法** 是一种在加权图中寻找最短路径的算法， 
 * 例如可以用来表示道路网络。由计算机科学家 Edsger W. Dijkstra 于 1956 年提出，并在三年后发表。
 *
 * @author [David Leal](https://github.com/Panquesito7)
 * @author [Arpan Jain](https://github.com/arpanjain97)
 */

#include <cassert>   /// 用于 assert
#include <climits>   /// 用于 INT_MAX
#include <iostream>  /// 用于 IO 操作
#include <vector>    /// 用于 std::vector

/**
 * @namespace
 * @brief 贪心算法
 */
namespace greedy_algorithms {
/**
 * @namespace
 * @brief Dijkstra 算法实现函数
 */
namespace dijkstra {
/**
 * @brief 存储图的包装类
 */
class Graph {
 public:
    int vertexNum = 0;  // 顶点数量
    std::vector<std::vector<int>> edges{};  // 边的邻接矩阵

    /**
     * @brief 构造图
     * @param V 图的顶点数量
     */
    explicit Graph(const int V) {
        // 初始化边的邻接矩阵
        this->edges = std::vector<std::vector<int>>(V, std::vector<int>(V, 0));

        this->vertexNum = V;  // 设置顶点数量
    }

    /**
     * @brief 向图中添加边
     * @param src 边的起始顶点
     * @param dst 边的终止顶点
     * @param weight 边的权重
     */
    void add_edge(int src, int dst, int weight) {
        this->edges[src][dst] = weight;  // 设置边的权重
    }
};

/**
 * @brief 找到在 `mdist` 中距离最小的顶点
 *
 * @param mdist 距离数组
 * @param vset 表示顶点是否在最短路径树中的数组
 * @param V 图中的顶点数量
 * @returns 距离最小的顶点索引
 */
int minimum_distance(std::vector<int> mdist, std::vector<bool> vset, int V) {
    int minVal = INT_MAX, minInd = 0;  // 初始化最小值和对应索引
    for (int i = 0; i < V; i++) {
        // 找到未被访问的最小距离顶点
        if (!vset[i] && (mdist[i] < minVal)) {
            minVal = mdist[i];
            minInd = i;
        }
    }

    return minInd;  // 返回最小距离顶点的索引
}

/**
 * @brief 打印到各个顶点的距离
 *
 * @param dist 存储每个顶点距离的数组
 * @param V 图中顶点的数量
 */
void print(std::vector<int> dist, int V) {
    std::cout << "\n顶点  距离\n";
    for (int i = 0; i < V; i++) {
        if (dist[i] < INT_MAX) {
            std::cout << i << "\t" << dist[i] << "\n";  // 打印距离
        }
        else {
            std::cout << i << "\tINF" << "\n";  // 如果距离为无穷大
        }
    }
}

/**
 * @brief 使用 Dijkstra 算法找到从源点到所有其他顶点的最短路径
 * @note 该算法不适用于带有负权边的图
 * @param graph 待处理的图
 * @param src 源顶点
 */
void dijkstra(Graph graph, int src) {
    int V = graph.vertexNum;  // 获取顶点数量
    std::vector<int> mdist(V, INT_MAX);  // 存储到每个顶点的最短距离
    std::vector<bool> vset(V, false);  // vset[i] 为真表示顶点 i 已包含在最短路径树中

    mdist[src] = 0;  // 源顶点到自身的距离为 0

    // 迭代寻找最短路径
    for (int count = 0; count < V - 1; count++) {
        int u = minimum_distance(mdist, vset, V);  // 找到未访问的最小距离顶点

        vset[u] = true;  // 标记为已访问

        // 更新与该顶点相邻的顶点的距离
        for (int v = 0; v < V; v++) {
            if (!vset[v] && graph.edges[u][v] && 
                mdist[u] + graph.edges[u][v] < mdist[v]) {
                mdist[v] = mdist[u] + graph.edges[u][v];  // 更新距离
            }
        }
    }

    print(mdist, V);  // 打印最终的距离
}
}  // namespace dijkstra
}  // namespace greedy_algorithms

/**
 * @brief 自测实现
 * @returns void
 */
static void tests() {
    greedy_algorithms::dijkstra::Graph graph(8);

    // 第一个测试
    graph.add_edge(6, 2, 4);
    graph.add_edge(2, 6, 4);
    assert(graph.edges[6][2] == 4);

    // 第二个测试
    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 0, 1);
    assert(graph.edges[0][1] == 1);

    // 第三个测试
    graph.add_edge(0, 2, 7);
    graph.add_edge(2, 0, 7);
    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 1, 1);
    assert(graph.edges[0][2] == 7);

    // 第四个测试
    graph.add_edge(1, 3, 3);
    graph.add_edge(3, 1, 3);
    graph.add_edge(1, 4, 2);
    graph.add_edge(4, 1, 2);
    graph.add_edge(2, 3, 2);
    assert(graph.edges[1][3] == 3);

    std::cout << "所有测试均已成功通过！\n";
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    tests();  // 运行自测实现
    return 0;
}
