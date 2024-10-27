/**
 * @file
 * @brief [双向 Dijkstra 最短路径算法]
 * (https://www.coursera.org/learn/algorithms-on-graphs/lecture/7ml18/bidirectional-dijkstra)
 *
 * @author [Marinovksy](http://github.com/Marinovsky)
 *
 * @details
 * 这基本上是与 Dijkstra 算法相同，但更快，因为它从源点到目标点和从目标点到源点进行搜索，并在找到已经被直接搜索或反向搜索访问的顶点时停止。
 * 此处有一些模拟：
 * https://www.youtube.com/watch?v=DINCL5cd_w0&t=24s
 */

#include <cassert>   /// 用于 assert
#include <iostream>  /// 用于输入输出操作
#include <limits>    /// 用于变量 INF
#include <queue>     /// 用于距离的优先队列
#include <utility>   /// 用于 make_pair 函数
#include <vector>    /// 用于存储图、距离和路径

constexpr int64_t INF = std::numeric_limits<int64_t>::max(); /// 定义无穷大常量

/**
 * @namespace graph
 * @brief 图算法
 */
namespace graph {
/**
 * @namespace bidirectional_dijkstra
 * @brief [双向 Dijkstra 最短路径]
 * (https://www.coursera.org/learn/algorithms-on-graphs/lecture/7ml18/bidirectional-dijkstra)
 * 算法的函数
 */
namespace bidirectional_dijkstra {
/**
 * @brief 在图的两个节点或顶点之间添加边
 *
 * @param adj1 直接搜索的邻接表
 * @param adj2 反向搜索的邻接表
 * @param u 图的任意节点或顶点
 * @param v 图的任意节点或顶点
 * @param w 边的权重
 */
void addEdge(std::vector<std::vector<std::pair<uint64_t, uint64_t>>> *adj1,
             std::vector<std::vector<std::pair<uint64_t, uint64_t>>> *adj2,
             uint64_t u, uint64_t v, uint64_t w) {
    (*adj1)[u - 1].push_back(std::make_pair(v - 1, w)); /// 添加边到直接搜索的邻接表
    (*adj2)[v - 1].push_back(std::make_pair(u - 1, w)); /// 添加边到反向搜索的邻接表
}

/**
 * @brief 返回源点到目标点的最短距离（如果两点之间有路径）
 *
 * @param workset_ 访问过的顶点
 * @param distance_ 从源点到目标点和从目标点到源点的距离向量
 *
 * @return 返回最短路径的距离
 */
uint64_t Shortest_Path_Distance(
    const std::vector<uint64_t> &workset_,
    const std::vector<std::vector<uint64_t>> &distance_) {
    int64_t distance = INF; /// 初始化最短距离为无穷大
    for (uint64_t i : workset_) {
        /// 计算所有访问过的顶点的总距离
        if (distance_[0][i] + distance_[1][i] < distance) {
            distance = distance_[0][i] + distance_[1][i]; /// 更新最短距离
        }
    }
    return distance; /// 返回最短距离
}

/**
 * @brief 在图中对某个源点和目标点运行 Dijkstra 算法，并返回目标点从源点的最短距离。
 *
 * @param adj1 输入图
 * @param adj2 反向输入图
 * @param s 源点
 * @param t 目标点
 *
 * @return 如果目标点可从源点到达则返回最短距离，否则返回 -1（表示不可达）。
 */
int Bidijkstra(std::vector<std::vector<std::pair<uint64_t, uint64_t>>> *adj1,
               std::vector<std::vector<std::pair<uint64_t, uint64_t>>> *adj2,
               uint64_t s, uint64_t t) {
    /// n 表示图中的顶点数量
    uint64_t n = adj1->size();

    /// 初始化所有距离为 INF
    std::vector<std::vector<uint64_t>> dist(2, std::vector<uint64_t>(n, INF));

    /// 创建一个最小堆的向量，使用优先队列
    /// pq[0] 包含直接搜索的最小堆
    /// pq[1] 包含反向搜索的最小堆

    /// pair 的第一个元素包含距离
    /// 第二个元素包含顶点
    std::vector<
        std::priority_queue<std::pair<uint64_t, uint64_t>,
                            std::vector<std::pair<uint64_t, uint64_t>>,
                            std::greater<std::pair<uint64_t, uint64_t>>>>
        pq(2);

    /// 存储最短路径中的节点或顶点
    std::vector<uint64_t> workset(n);
    /// 存储访问过的节点或顶点
    std::vector<bool> visited(n);

    /// 将源点 's' 和距离 0 推入 pq[0] 最小堆
    pq[0].push(std::make_pair(0, s));

    /// 将源点的距离标记为 0
    dist[0][s] = 0;

    /// 将目标点 't' 和距离 0 推入 pq[1] 最小堆
    pq[1].push(std::make_pair(0, t));

    /// 将目标点的距离标记为 0
    dist[1][t] = 0;

    while (true) {
        /// 直接搜索

        // 如果 pq[0].size() 等于零，则节点/顶点不可达
        if (pq[0].size() == 0) {
            break;
        }

        /// pair 的第二个元素表示当前节点/顶点
        uint64_t currentNode = pq[0].top().second;

        /// pair 的第一个元素表示当前距离
        uint64_t currentDist = pq[0].top().first;

        pq[0].pop();

        /// 对于从当前正在探索的顶点可到达的所有顶点
        /// 我们将尝试最小化距离
        for (std::pair<int, int> edge : (*adj1)[currentNode]) {
            /// 最小化距离
            if (currentDist + edge.second < dist[0][edge.first]) {
                dist[0][edge.first] = currentDist + edge.second; /// 更新距离
                pq[0].push(std::make_pair(dist[0][edge.first], edge.first)); /// 推入优先队列
            }
        }

        // 存储处理过的节点/顶点
        workset.push_back(currentNode);

        /// 检查当前节点是否已被访问
        if (visited[currentNode] == 1) {
            return Shortest_Path_Distance(workset, dist); /// 返回最短路径距离
        }
        visited[currentNode] = true; /// 标记为已访问

        /// 反向搜索

        // 如果 pq[1].size() 等于零，则节点/顶点不可达
        if (pq[1].size() == 0) {
            break;
        }

        /// pair 的第二个元素表示当前节点/顶点
        currentNode = pq[1].top().second;

        /// pair 的第一个元素表示当前距离
        currentDist = pq[1].top().first;

        pq[1].pop();

        /// 对于从当前正在探索的顶点可到达的所有顶点
        /// 我们将尝试最小化距离
        for (std::pair<int, int> edge : (*adj2)[currentNode]) {
            /// 最小化距离
            if (currentDist + edge.second < dist[1][edge.first]) {
                dist[1][edge.first] = currentDist + edge.second; /// 更新距离
                pq[1].push(std::make_pair(dist[1][edge.first], edge.first)); /// 推入优先队列
            }
        }

        // 存储处理过的节点/顶点
        workset.push_back(currentNode);

        /// 检查当前节点是否已被访问
        if (visited[currentNode] == 1) {
            return Shortest_Path_Distance(workset, dist); /// 返回最短路径距离
        }
        visited[currentNode] = true; /// 标记为已访问
    }
    return -1; /// 如果不可达，返回 -1
}
}  // namespace bidirectional_dijkstra
}  // namespace graph

/**
 * @brief 测试上述提供的算法的函数
 * @returns void
 */
static void tests() {
    std::cout << "正在启动预定义测试..." << std::endl;
    std::cout << "启动测试 1..." << std::endl;
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj1_1(
        4, std::vector<std::pair<uint64_t, uint64_t>>());
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj2_1(
        4, std::vector<std::pair<uint64_t, uint64_t>>());
    graph::bidirectional_dijkstra::addEdge(&adj1_1, &adj2_1, 1, 2, 1);
    graph::bidirectional_dijkstra::addEdge(&adj1_1, &adj2_1, 2, 3, 1);
    graph::bidirectional_dijkstra::addEdge(&adj1_1, &adj2_1, 1, 4, 2);
    graph::bidirectional_dijkstra::addEdge(&adj1_1, &adj2_1, 4, 3, 2);
    assert(graph::bidirectional_dijkstra::Bidijkstra(&adj1_1, &adj2_1, 1, 3) == 2);
    std::cout << "测试 1 通过！" << std::endl;

    std::cout << "启动测试 2..." << std::endl;
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj1_2(
        4, std::vector<std::pair<uint64_t, uint64_t>>());
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj2_2(
        4, std::vector<std::pair<uint64_t, uint64_t>>());
    graph::bidirectional_dijkstra::addEdge(&adj1_2, &adj2_2, 1, 2, 1);
    graph::bidirectional_dijkstra::addEdge(&adj1_2, &adj2_2, 2, 3, 2);
    graph::bidirectional_dijkstra::addEdge(&adj1_2, &adj2_2, 1, 4, 3);
    graph::bidirectional_dijkstra::addEdge(&adj1_2, &adj2_2, 4, 3, 1);
    assert(graph::bidirectional_dijkstra::Bidijkstra(&adj1_2, &adj2_2, 1, 3) == 3);
    std::cout << "测试 2 通过！" << std::endl;

    std::cout << "启动测试 3..." << std::endl;
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj1_3(
        4, std::vector<std::pair<uint64_t, uint64_t>>());
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj2_3(
        4, std::vector<std::pair<uint64_t, uint64_t>>());
    graph::bidirectional_dijkstra::addEdge(&adj1_3, &adj2_3, 1, 2, 1);
    graph::bidirectional_dijkstra::addEdge(&adj1_3, &adj2_3, 2, 3, 2);
    graph::bidirectional_dijkstra::addEdge(&adj1_3, &adj2_3, 1, 4, 2);
    graph::bidirectional_dijkstra::addEdge(&adj1_3, &adj2_3, 4, 3, 3);
    assert(graph::bidirectional_dijkstra::Bidijkstra(&adj1_3, &adj2_3, 1, 3) == 4);
    std::cout << "测试 3 通过！" << std::endl;

    std::cout << "启动测试 4..." << std::endl;
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj1_4(
        4, std::vector<std::pair<uint64_t, uint64_t>>());
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj2_4(
        4, std::vector<std::pair<uint64_t, uint64_t>>());
    graph::bidirectional_dijkstra::addEdge(&adj1_4, &adj2_4, 1, 2, 1);
    graph::bidirectional_dijkstra::addEdge(&adj1_4, &adj2_4, 2, 3, 1);
    graph::bidirectional_dijkstra::addEdge(&adj1_4, &adj2_4, 3, 4, 1);
    assert(graph::bidirectional_dijkstra::Bidijkstra(&adj1_4, &adj2_4, 1, 3) == 2);
    std::cout << "测试 4 通过！" << std::endl;

    std::cout << "测试完成" << std::endl;
}

/**
 * @brief 主函数
 * @return 0 表示程序成功
 */
int main() {
    tests(); /// 运行测试
    return 0; /// 返回 0
}
