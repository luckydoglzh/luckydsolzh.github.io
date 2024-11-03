/**
 * @brief 检查给定图是否为二分图
 * @details
 * 二分图是一个节点可以分为两个不相交的集合，
 * 使得一个集合中的节点之间没有连接，即不存在同集合内的连接。
 * 唯一存在的连接是集合间的连接，
 * 即一个集合中的节点连接到另一个集合的部分节点。
 * 本实现使用邻接列表形式的图来检查给定图是否为二分图。
 *
 * 使用的参考资料：
 * [GeeksForGeeks](https://www.geeksforgeeks.org/bipartite-graph/)
 * @author [tushar2407](https://github.com/tushar2407)
 */
#include <cassert>   /// 用于 assert
#include <iostream>  /// 用于输入输出操作
#include <queue>     /// 用于队列数据结构
#include <vector>    /// 用于向量数据结构

/**
 * @namespace graph
 * @brief 图形算法
 */
namespace graph {
/**
 * @brief 检查传入的图是否为二分图
 * @param graph 是一个 2D 矩阵，第一维表示节点，
 * 第二维表示该节点连接到的节点
 * @param index 当前观察的节点的值
 * @param visited 存储节点是否被遍历的向量
 * @returns 布尔值
 */
bool checkBipartite(const std::vector<std::vector<int64_t>> &graph,
                    int64_t index, std::vector<int64_t> *visited) {
    std::queue<int64_t> q;  ///< 存储被访问节点的索引
    q.push(index);          /// 将当前节点加入队列
    (*visited)[index] = 1;  /// 标记当前节点为已访问
    while (q.size()) {
        int64_t u = q.front();
        q.pop();
        for (uint64_t i = 0; i < graph[u].size(); i++) {
            int64_t v = graph[u][i];  ///< 存储当前节点的邻居
            if (!(*visited)[v]) {  /// 检查邻居节点是否已被访问
                (*visited)[v] = ((*visited)[u] == 1) ? -1 : 1;  /// 将邻居节点标记为与当前节点不同的颜色
                q.push(v);    /// 将邻居节点加入队列
            } else if ((*visited)[v] == (*visited)[u]) {  /// 如果当前节点和邻居节点颜色相同，则不是二分图
                return false;
            }
        }
    }
    return true;  /// 如果所有连接的节点都已访问且满足条件，则返回 true
}

/**
 * @brief 如果给定图是二分图，则返回 true，否则返回 false
 * @param graph 是一个 2D 矩阵，第一维表示节点，
 * 第二维表示该节点连接到的节点
 * @returns 布尔值
 */
bool isBipartite(const std::vector<std::vector<int64_t>> &graph) {
    std::vector<int64_t> visited(graph.size());  ///< 存储节点是否已访问的布尔值

    for (uint64_t i = 0; i < graph.size(); i++) {
        if (!visited[i]) {  /// 如果当前节点未访问，则检查该子图是否为二分图
            if (!checkBipartite(graph, i, &visited)) {
                return false;
            }
        }
    }
    return true;
}
}  // namespace graph

/**
 * @brief 自测试实现
 * @returns void
 */
static void test() {
    std::vector<std::vector<int64_t>> graph = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};

    assert(graph::isBipartite(graph) == true);  /// 检查上面定义的图是否为二分图

    std::vector<std::vector<int64_t>> graph_not_bipartite = {
        {1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}};

    assert(graph::isBipartite(graph_not_bipartite) == false);  /// 检查上面定义的图是否不是二分图
    std::cout << "所有测试都已成功通过！\n";
}

/**
 * @brief 主函数
 * 实例化一个小规模的虚拟图，其中包含
 * 一些随机节点之间的边。
 * 通过应用算法，检查实例化的图是否为二分图。
 * @returns 0
 */
int main() {
    test();  // 运行自测试实现
    return 0;
}
