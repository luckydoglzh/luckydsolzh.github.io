/**
 * @file
 * @brief [Kruskal 最小生成树算法](https://www.simplilearn.com/tutorials/data-structure-tutorial/kruskal-algorithm) 的实现
 *
 * @details
 * _引用自 [Simplilearn](https://www.simplilearn.com/tutorials/data-structure-tutorial/kruskal-algorithm)。_
 *
 * Kruskal 算法是离散数学图论中引入的概念。它用于在一个连通加权图中发现两点之间的最短路径。此算法将给定图转换为森林，每个节点视为一棵独立的树。这些树只能通过连接它们的低值边相互连接，并且不生成最小生成树中的环。
 *
 * @author [coleman2246](https://github.com/coleman2246)
 */

#include <array>     /// 用于数组
#include <iostream>  /// 用于输入输出操作
#include <limits>    /// 用于数值限制
#include <cstdint>   /// 用于 uint32_t

/**
 * @namespace
 * @brief 贪心算法
 */
namespace greedy_algorithms {
/**
 * @brief 查找给定图的最小边
 * @param infinity 定义图中的无穷大
 * @param graph 将用于查找边的图
 * @returns void
 */
template <typename T, std::size_t N, std::size_t M>
void findMinimumEdge(const T &infinity,
                     const std::array<std::array<T, N>, M> &graph) {
    if (N != M) {
        std::cout << "\n输入错误。提供的数组维度为 " << N
                  << "x" << M << "。请提供一个方阵。\n";
        return;
    }
    for (int i = 0; i < graph.size(); i++) {
        int min = infinity;  // 最小边初始化为无穷大
        int minIndex = 0;    // 存储最小边的索引
        for (int j = 0; j < graph.size(); j++) {
            // 如果当前不是自己且边的权重有效
            if (i != j && graph[i][j] != 0 && graph[i][j] < min) {
                min = graph[i][j];  // 更新最小边
                minIndex = j;       // 更新最小边的索引
            }
        }
        std::cout << i << "  -  " << minIndex << "\t" << graph[i][minIndex]
                  << "\n";  // 输出最小边的信息
    }
}  // namespace greedy_algorithms

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    /**
     * 定义一个整数的较大值
     * 定义一个浮点数的较大值
     * 定义一个双精度浮点数的较大值
     * 定义一个 uint32_t 的较大值
     */
    constexpr int INFINITY_INT = std::numeric_limits<int>::max();
    constexpr float INFINITY_FLOAT = std::numeric_limits<float>::max();
    constexpr double INFINITY_DOUBLE = std::numeric_limits<double>::max();
    constexpr uint32_t INFINITY_UINT32 = UINT32_MAX;

    // 测试用例 1：整数值的图
    std::cout << "\n测试用例 1 :\n";
    std::array<std::array<int, 6>, 6> graph1{
        0,            4,            1,             4,        INFINITY_INT,   INFINITY_INT,
        4,            0,            3,             8,             3,         INFINITY_INT,
        1,            3,            0,        INFINITY_INT,       1,         INFINITY_INT,
        4,            8,       INFINITY_INT,        0,            5,              7,
        INFINITY_INT,      3,            1,              5,            0,         INFINITY_INT,
        INFINITY_INT, INFINITY_INT, INFINITY_INT,        7,       INFINITY_INT,       0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph1);

    // 测试用例 2：浮点值的图
    std::cout << "\n测试用例 2 :\n";
    std::array<std::array<float, 3>, 3> graph2{
        0.0f,           2.5f,  INFINITY_FLOAT,
        2.5f,           0.0f,       3.2f,
        INFINITY_FLOAT,      3.2f,       0.0f};
    greedy_algorithms::findMinimumEdge(INFINITY_FLOAT, graph2);

    // 测试用例 3：双精度浮点值的图
    std::cout << "\n测试用例 3 :\n";
    std::array<std::array<double, 5>, 5> graph3{
        0.0,             10.5,       INFINITY_DOUBLE,        6.7,              3.3,
        10.5,            0.0,              8.1,              15.4,       INFINITY_DOUBLE,
        INFINITY_DOUBLE,        8.1,              0.0,        INFINITY_DOUBLE,         7.8,
        6.7,             15.4,       INFINITY_DOUBLE,        0.0,               9.9,
        3.3,       INFINITY_DOUBLE,        7.8,              9.9,               0.0};
    greedy_algorithms::findMinimumEdge(INFINITY_DOUBLE, graph3);

    // 测试用例 4：带负权重的图
    std::cout << "\n测试用例 4 :\n";
    std::array<std::array<int, 3>, 3> graph_neg{
        0,   -2,   4,
       -2,    0,   3,
        4,    3,   0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph_neg);

    // 测试用例 5：带自环的图
    std::cout << "\n测试用例 5 :\n";
    std::array<std::array<int, 3>, 3> graph_self_loop{
        2,       1, INFINITY_INT,
        INFINITY_INT,   0,        4,
        INFINITY_INT,   4,        0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph_self_loop);

    // 测试用例 6：没有边的图
    std::cout << "\n测试用例 6 :\n";
    std::array<std::array<int, 4>, 4> no_edges{
        0,       INFINITY_INT,   INFINITY_INT,   INFINITY_INT,
        INFINITY_INT,         0,        INFINITY_INT,   INFINITY_INT,
        INFINITY_INT,   INFINITY_INT,          0,       INFINITY_INT,
        INFINITY_INT,   INFINITY_INT,   INFINITY_INT,           0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, no_edges);

    // 测试用例 7：非连通图
    std::cout << "\n测试用例 7:\n";
    std::array<std::array<int, 4>, 4> partial_graph{
        0,             2,    INFINITY_INT,         6,
        2,             0,            3,     INFINITY_INT,
        INFINITY_INT,          3,            0,             4,
        6,     INFINITY_INT,         4,             0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, partial_graph);

    // 测试用例 8：有向加权图（Kruskal 算法不一定能得到最优解）
    std::cout << "\n测试用例 8:\n";
    std::array<std::array<int, 4>, 4> directed_graph{
        0,            3,            7,   INFINITY_INT,  // 顶点 0 有边连接到顶点 1 和 2
        INFINITY_INT,         0,            2,           5,  // 顶点 1 有边连接到顶点 2 和 3
        INFINITY_INT, INFINITY_INT,         0,           1,  // 顶点 2 有边连接到顶点 3
        INFINITY_INT, INFINITY_INT, INFINITY_INT,        0};  // 顶点 3 没有出边
    greedy_algorithms::findMinimumEdge(INFINITY_INT, directed_graph);

    // 测试用例 9：输入错误
    std::cout << "\n测试用例 9:\n";
    std::array<std::array<int, 4>, 3> graph9{
        0,        5,        5,        5,
        5,        0,        5,        5,        
        5,        5,        5,        5};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph9);

    // 测试用例 10：每条边的权重相同
    std::cout << "\n测试用例 10:\n";
    std::array<std::array<int, 5>, 5> graph10{
        0,        5,        5,        5,        5,
        5,        0,        5,        5,        5,
        5,        5,        0,        5,        5,
        5,        5,        5,        0,        5,
        5,        5,        5,        5,        0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph10);

    // 测试用例 11：uint32_t 类型的图
    std::cout << "\n测试用例 11 :\n";
    std::array<std::array<uint32_t, 4>, 4> graph_uint32{
        0,                      5,        INFINITY_UINT32,          9,
        5,                      0,                2,        INFINITY_UINT32,
        INFINITY_UINT32,                2,                0,                6,
        9,               INFINITY_UINT32,         6,                0};
    greedy_algorithms::findMinimumEdge(INFINITY_UINT32, graph_uint32);

    std::cout << "\n所有测试均已成功通过！\n";
}

/**
 * @brief 主函数
 * @returns 0 表示退出成功
 */
int main() {
    test();  // 运行自测实现
    return 0;
}
