/**
 *
 * \file
 * \brief [广度优先搜索算法](https://en.wikipedia.org/wiki/Breadth-first_search)
 *
 * \author [Ayaan Khan](https://github.com/ayaankhan98)
 * \author [Aman Kumar Pandey](https://github.com/gpamangkp)
 *
 * \details
 * 广度优先搜索（BFS）是一种图遍历算法。
 * 时间复杂度为 O(|V| + |E|)，其中 V 是顶点数量，E 是边的数量。
 *
 * 广度优先搜索的应用包括：
 *
 * 1. 找到两个顶点之间的最短路径（路径长度按边的数量计算）。
 * 2. Ford-Fulkerson 方法用于计算流网络中的最大流。
 * 3. 测试图的二分性。
 * 4. Cheney 算法，用于垃圾回收。
 *
 * 还有很多其他应用...
 *
 * <h4>工作原理</h4>
 * 在下面的实现中，我们首先使用邻接表表示法创建图。
 * 广度优先搜索的工作原理如下：
 * 需要一个起始顶点作为遍历图的起点。
 * 我们维护一个布尔数组或向量来跟踪已经访问过的顶点，以避免重复遍历。
 * 还会使用一个队列。
 *
 * 1. 首先标记起始顶点为已访问。
 * 2. 将该已访问顶点压入队列。
 * 3. 当队列不为空时，重复以下步骤：
 *
 *      1. 从队列前端取出一个元素。
 *      2. 探索该顶点的邻接表。
 *         如果邻接表中的元素未访问，则将该元素压入队列并标记为已访问。
 *
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <vector>

/**
 * \namespace graph
 * \brief 图算法
 */
namespace graph {
/* 图的定义 */
template <typename T>
class Graph {
    /**
     * 邻接表将每个顶点映射到其邻居的列表，按添加顺序。
     */
    std::map<T, std::list<T> > adjacency_list;

 public:
    Graph() = default;

    void add_edge(T u, T v, bool bidir = true) {
        /**
         * add_edge(u, v, bidir) 用于在节点 u 和节点 v 之间添加边。
         * 默认情况下，bidir 为 true，表示图是双向的。
         * 这意味着如果添加边 (u, v)，则存在 u-->v 和 v-->u 两条边。
         *
         * 要使图单向，只需将 add_edge 的第三个参数设置为 false。
         */
        adjacency_list[u].push_back(v);  // 添加 u-->v 边
        if (bidir == true) {
            // 如果图是双向的
            adjacency_list[v].push_back(u);  // 添加 v-->u 边
        }
    }

    /**
     * 执行图的广度优先搜索并返回一个映射，表示节点是否被遍历。
     */
    std::map<T, bool> breadth_first_search(T src) {
        /// 用于跟踪所有访问过的节点的映射
        std::map<T, bool> visited;
        /// 初始化每个可能的顶点映射为 false，表示未访问
        for (auto const &adjlist : adjacency_list) {
            visited[adjlist.first] = false;
            for (auto const &node : adjacency_list[adjlist.first]) {
                visited[node] = false;
            }
        }

        /// 队列，用于存储尚未遍历的节点
        std::queue<T> tracker;

        /// 将源顶点推入队列以开始遍历
        tracker.push(src);
        /// 标记源顶点为已访问
        visited[src] = true;
        while (!tracker.empty()) {
            /// 在没有剩余连接顶点时遍历图
            /// 从队列中提取一个节点进行进一步遍历
            T node = tracker.front();
            /// 从队列中移除该节点
            tracker.pop();
            for (T const &neighbour : adjacency_list[node]) {
                /// 检查与该节点连接的每个未访问的顶点
                if (!visited[neighbour]) {
                    /// 如果邻居未访问，将其压入队列
                    tracker.push(neighbour);
                    /// 标记邻居为已访问
                    visited[neighbour] = true;
                }
            }
        }
        return visited;
    }
};
/* 类定义结束 */
}  // namespace graph

/** 测试函数 */
static void tests() {
    /// 测试 1 开始
    graph::Graph<int> g;
    std::map<int, bool> correct_result;
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    correct_result[0] = true;
    correct_result[1] = true;
    correct_result[2] = true;
    correct_result[3] = true;

    std::map<int, bool> returned_result = g.breadth_first_search(2);

    assert(returned_result == correct_result);
    std::cout << "测试 1 通过..." << std::endl;

    /// 测试 2 开始
    returned_result = g.breadth_first_search(0);

    assert(returned_result == correct_result);
    std::cout << "测试 2 通过..." << std::endl;

    /// 测试 3 开始
    graph::Graph<std::string> g2;

    g2.add_edge("Gorakhpur", "Lucknow", false);
    g2.add_edge("Gorakhpur", "Kanpur", false);
    g2.add_edge("Lucknow", "Agra", false);
    g2.add_edge("Kanpur", "Agra", false);
    g2.add_edge("Lucknow", "Prayagraj", false);
    g2.add_edge("Agra", "Noida", false);

    std::map<std::string, bool> correct_res;
    std::map<std::string, bool> returned_res =
        g2.breadth_first_search("Kanpur");
    correct_res["Gorakhpur"] = false;
    correct_res["Lucknow"] = false;
    correct_res["Kanpur"] = true;
    correct_res["Agra"] = true;
    correct_res["Prayagraj"] = false;
    correct_res["Noida"] = true;
    assert(correct_res == returned_res);
    std::cout << "测试 3 通过..." << std::endl;
}

/** 主函数 */
int main() {
    tests();
    size_t edges = 0;
    std::cout << "输入边的数量: ";
    std::cin >> edges;

    graph::Graph<int> g;

    std::cout << "输入形成边的顶点对（以空格分隔）: " << std::endl;
    while (edges--) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    g.breadth_first_search(0);
    return 0;
}
