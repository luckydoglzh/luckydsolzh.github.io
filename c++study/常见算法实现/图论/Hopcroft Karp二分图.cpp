/**
 * @file 
 * @brief [Hopcroft–Karp](https://en.wikipedia.org/wiki/Hopcroft%E2%80%93Karp_algorithm) 算法的实现。
 * @details 
 * Hopcroft–Karp 算法用于处理二分图，输出最大基数匹配，最坏情况下的时间复杂度为 O(E√V)。
 * 
 * ### 二分图
 * 二分图（或称为大图）是一个图，其顶点可以被分为两个不相交的独立集合 U 和 V， 
 * 每条边连接 U 中的一个顶点与 V 中的一个顶点。U 和 V 被称为图的两个部分。
 * 等价地，二分图是一个不包含任何奇长度环的图。
 * 
 * ### 匹配与非匹配边
 * 给定一个匹配 M，属于匹配的边称为匹配边，不属于 M（或连接自由节点）的边称为非匹配边。
 * 
 * ### 最大基数匹配
 * 给定一个二分图 G = ( V = ( X , Y ) , E )，其中分区有部分 X 和 Y， 
 * E 表示图的边，目标是找到一组尽可能多的匹配边。
 * 等价地，找到尽可能多覆盖顶点的匹配。
 * 
 * ### 增广路径
 * 给定一个匹配 M，增广路径是一个交替路径，起点和终点都是自由顶点。
 * 所有以自由顶点开始和结束的单边路径都是增广路径。
 * 
 * ### 概念
 * 如果存在增广路径，则匹配 M 不是最大匹配。反之亦然，若不存在增广路径，则匹配是最大匹配。
 * 
 * ### 算法
 * 1) 初始化最大匹配 M 为一个空集。
 * 2) 当存在增广路径 P 时：
 *    从 M 中移除 P 的匹配边，并将 P 的非匹配边加入 M（
 *    这使得 M 的大小增加 1，因为 P 以自由顶点开始和结束，即不属于匹配的节点。）
 * 3) 返回 M。
 * 
 * @author [Krishna Pal Deora](https://github.com/Krishnapal4050)
 */

#include <iostream>
#include <cstdlib> 
#include <queue>
#include <list>
#include <climits>
#include <memory>
#include <cassert>

/**
 * @namespace graph 
 * @brief 图算法命名空间
 */
namespace graph { 

/**
 * @brief 表示 Hopcroft Karp 实现的二分图
 */
class HKGraph
{
    int m{};  ///< m 是二分图左侧的顶点数量
    int n{};  ///< n 是二分图右侧的顶点数量
    const int NIL{0};  ///< 哨兵节点
    const int INF{INT_MAX};  ///< 表示无穷大的常量

    std::vector<std::list<int>> adj;  ///< adj[u] 存储左侧顶点的邻接点，0 用于占位哨兵

    std::vector<int> pair_u; ///< 存储左侧顶点 u 的匹配值，范围为 1 到 m
    std::vector<int> pair_v; ///< 存储右侧顶点 v 的匹配值，范围为 1 到 n
    std::vector<int> dist;   ///< dist 表示左侧顶点 u 与右侧顶点 v 之间的距离

public:
    HKGraph();  // 默认构造函数
    HKGraph(int m, int n);  // 构造函数
    void addEdge(int u, int v); // 添加边
    
    bool bfs(); // 如果存在增广路径则返回 true    
    bool dfs(int u); // 如果存在从 u 开始的增广路径则返回 true
	
    int hopcroftKarpAlgorithm();  // 返回最大匹配的大小
};

/**
 * @brief 计算二分图左右两侧之间增广路径的数量
 * @returns 最大匹配的大小
 */
int HKGraph::hopcroftKarpAlgorithm()
{
    // pair_u[u] 存储左侧二分图中 u 的匹配对
    // 如果 u 没有匹配对，则 pair_u[u] 为 NIL
    pair_u = std::vector<int>(m + 1, NIL); 

    // pair_v[v] 存储右侧二分图中 v 的匹配对
    // 如果 v 没有匹配对，则 pair_v[v] 为 NIL
    pair_v = std::vector<int>(n + 1, NIL); 

    dist = std::vector<int>(m + 1);  // dist[u] 存储左侧顶点的距离

    int result = 0;  // 初始化结果

    // 持续更新结果，直到没有增广路径为止
    while (bfs())
    {
        // 找到一个自由顶点来检查匹配
        for (int u = 1; u <= m; u++){
            // 如果当前顶点是自由的，并且存在从该顶点出发的增广路径
            // 则增大结果
            if (pair_u[u] == NIL && dfs(u)){
                result++;
            }
        }
    }
    return result;
}

/**
 * @brief 检查增广路径是否存在
 * @returns 如果存在增广路径则返回 `true`
 * @returns 如果不存在增广路径则返回 `false`
 */
bool HKGraph::bfs()
{
    std::queue<int> q; // 用于 BFS 的整数队列

    // 第一层顶点（设置距离为 0）
    for (int u = 1; u <= m; u++)
    {
        // 如果是自由顶点，则将其添加到队列
        if (pair_u[u] == NIL){
            dist[u] = 0; // u 未匹配，因此距离为 0
            q.push(u);
        }
        else{
            dist[u] = INF; // 将距离设为无穷大，以便下次考虑
        }
    }

    dist[NIL] = INF; // 将 NIL 的距离初始化为无穷大

    // q 将仅包含左侧顶点。
    while (!q.empty())
    {
        int u = q.front();  // 出队一个顶点
        q.pop();

        // 如果该节点不是 NIL，并且能提供到 NIL 的更短路径
        if (dist[u] < dist[NIL])
        {
            // 获取出队顶点 u 的所有邻接顶点
            std::list<int>::iterator it;
            for (it = adj[u].begin(); it != adj[u].end(); ++it)
            {
                int v = *it;

                // 如果 v 的匹配对尚未考虑
                if (dist[pair_v[v]] == INF)
                {
                    dist[pair_v[v]] = dist[u] + 1; 
                    q.push(pair_v[v]); // 考虑该匹配并将其推入队列
                }
            }
        }
    }

    return (dist[NIL] != INF);   // 如果可以通过交替路径到达 NIL，则存在增广路径
}

/**
 * @brief 检查从自由顶点 u 开始是否存在增广路径
 * @param u 表示顶点的位置
 * @returns 如果从自由顶点 u 开始存在增广路径则返回 `true`
 * @returns 如果不存在增广路径则返回 `false`
 */
bool HKGraph::dfs(int u)
{
    if (u != NIL)
    {
        std::list<int>::iterator it;
        for (it = adj[u].begin(); it != adj[u].end(); ++it)
        {
            int v = *it; // u 的邻接顶点

            // 根据 BFS 搜索设置的距离进行查找
            if (dist[pair_v[v]] == dist[u] + 1)
            {
                // 如果 v 的匹配对的 DFS 返回 true，则新的匹配可能成功
                if (dfs(pair_v[v]) == true)
                {   
                    pair_v[v] = u; // 更新匹配
                    pair_u[u] = v; // 更新匹配
                    return true;
                }
            }
        }

        dist[u] = INF; // 如果从 u 开始没有增广路径，则设置距离为无穷大
        return false;
    }
    return true;
}

/**
 * @brief 默认构造函数进行初始化
 */
HKGraph::HKGraph() = default;

/**
 * @brief 构造函数进行初始化
 * @param m 二分图左侧的顶点数量
 * @param n 二分图右侧的顶点数量
 */
HKGraph::HKGraph(int m, int n) {
    this->m = m;
    this->n = n;
    adj = std::vector<std::list<int>>(m + 1);
}

/**
 * @brief 添加从 u 到 v 的边
 * @param u 第一个顶点的位置
 * @param v 第二个顶点的位置
 */
void HKGraph::addEdge(int u, int v)
{
    adj[u].push_back(v); // 将 v 添加到 u 的邻接列表
}

} // namespace graph

using graph::HKGraph;

/**
 * 自测试实现
 * @returns none
 */
void tests(){
    // 示例测试用例 1
    int v1a = 3, v1b = 5, e1 = 2;  // 左侧、右侧顶点数量和边数
    HKGraph g1(v1a, v1b); // 执行算法 

    g1.addEdge(0,1);
    g1.addEdge(1,4);

    int expected_res1 = 0; // 该示例数据的期望输出
    int res1 = g1.hopcroftKarpAlgorithm();

    assert(res1 == expected_res1); // 断言检查算法在测试 1 中的执行是否正确
	
    // 示例测试用例 2
    int v2a = 4, v2b = 4, e2 = 6;  // 左侧、右侧顶点数量和边数
    HKGraph g2(v2a, v2b); // 执行算法 

    g2.addEdge(1,1);
    g2.addEdge(1,3);
    g2.addEdge(2,3);
    g2.addEdge(3,4);
    g2.addEdge(4,3);
    g2.addEdge(4,2);
	
    int expected_res2 = 0; // 该示例数据的期望输出
    int res2 = g2.hopcroftKarpAlgorithm();

    assert(res2 == expected_res2); // 断言检查算法在测试 2 中的执行是否正确
	
    // 示例测试用例 3
    int v3a = 6, v3b = 6, e3 = 4;  // 左侧、右侧顶点数量和边数
    HKGraph g3(v3a, v3b); // 执行算法 

    g3.addEdge(0,1);
    g3.addEdge(1,4);
    g3.addEdge(1,5);
    g3.addEdge(5,0);

    int expected_res3 = 0; // 该示例数据的期望输出
    int res3 = g3.hopcroftKarpAlgorithm();

    assert(res3 == expected_res3); // 断言检查算法在测试 3 中的执行是否正确
}

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main()
{
    tests();  // 执行自测试

    int v1 = 0, v2 = 0, e = 0;
    std::cin >> v1 >> v2 >> e; // 输入左侧、右侧顶点数量和边数
    HKGraph g(v1, v2);  
    int u = 0, v = 0;
    for (int i = 0; i < e; ++i)
    {
        std::cin >> u >> v; // 输入边的两个端点
        g.addEdge(u, v);
    }
  
    int res = g.hopcroftKarpAlgorithm();
    std::cout << "最大匹配数为 " << res << "\n";

    return 0;
}
