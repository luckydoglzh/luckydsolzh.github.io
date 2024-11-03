/**
 *
 * @file
 * @brief [深度优先搜索算法 (Depth First Search Algorithm)](https://en.wikipedia.org/wiki/Depth-first_search)
 *
 * @author [Ayaan Khan](http://github.com/ayaankhan98)
 * @author [Saurav Uppoor](https://github.com/sauravUppoor)
 *
 * @details
 * 深度优先搜索（DFS）是一种图遍历算法。
 * 时间复杂度为 O(|V| + |E|)，其中 V 是顶点数，E 是边数。
 *
 * 深度优先搜索的应用包括：
 *
 * 1. 查找连通分量
 * 2. 查找 2-（边或顶点）连通分量
 * 3. 查找 3-（边或顶点）连通分量
 * 4. 查找图中的桥
 * 5. 生成词以绘制群的极限集
 * 6. 查找强连通分量
 *
 * <h4>工作原理</h4>
 * 1. 将所有顶点标记为未访问（颜色为白色）。
 * 2. 将起始顶点压入栈中，并将其标记为灰色。
 * 3. 一旦栈顶的节点被弹出并标记为灰色，则将其标记为黑色。
 * 4. 将所有未标记为黑色的邻居压入栈中。
 * 5. 重复步骤 4 和 5，直到栈为空。
 */

#include <iostream>     // 用于输入输出操作
#include <stack>        // std::stack 的头文件
#include <vector>       // std::vector 的头文件
#include <cassert>      // 断言宏的头文件
#include <limits>       // 整数类型的限制

constexpr int WHITE = 0; // 表示节点未被探索
constexpr int GREY = 1;  // 表示节点在栈中等待被探索
constexpr int BLACK = 2; // 表示节点已经被探索
constexpr int64_t INF = std::numeric_limits<int16_t>::max();

/**
 * @namespace graph
 * @brief 图算法
 */
namespace graph {
/**
 * @namespace depth_first_search
 * @brief 深度优先搜索算法的函数
 */
namespace depth_first_search {
/**
 * @brief
 * 在图的两个顶点 u 和 v 之间添加边。
 *
 * @param adj 图的邻接表表示
 * @param u 第一个顶点
 * @param v 第二个顶点
 */
void addEdge(std::vector<std::vector<size_t>> *adj, size_t u, size_t v) {
    /*
    * 在这里我们考虑无向图，因此我们将 v 添加到 u 的邻接表中
    * 同时也将 u 添加到 v 的邻接表中
    */
    (*adj)[u - 1].push_back(v - 1);
}

/**
 * @brief
 * 探索给定的顶点，探索一个顶点意味着遍历所有与当前正在探索的顶点相连的顶点并将其压入栈中。
 *
 * @param adj 图
 * @param start DFS 的起始顶点
 * @return 按 DFS 遍历顺序存储节点的向量
 */
std::vector<size_t> dfs(const std::vector<std::vector<size_t>> &graph, size_t start) {
    // checked[i] 存储每个节点的状态
    std::vector<size_t> checked(graph.size(), WHITE), traversed_path;

    checked[start] = GREY;
    std::stack<size_t> stack;
    stack.push(start);

    // 当栈不为空时，我们继续探索栈顶的节点
    while (!stack.empty()) {
        int act = stack.top();
        stack.pop();

        if (checked[act] == GREY) {
            // 将节点添加到最终结果向量中
            traversed_path.push_back(act + 1);

            // 探索当前节点的邻居
            for (auto it : graph[act]) {
                stack.push(it);
                if (checked[it] != BLACK) {
                    checked[it] = GREY;
                }
            }
            checked[act] = BLACK;  // 节点已被探索
        }
    }
    return traversed_path;
}
}  // namespace depth_first_search
}  // namespace graph

/**
 * 自测试实现
 * @returns 无
 */
static void tests() {
    size_t start_pos;

    // 测试 1
    std::cout << "案例 1: " << std::endl;
    start_pos = 1;
    std::vector<std::vector<size_t>> g1(3, std::vector<size_t>());

    graph::depth_first_search::addEdge(&g1, 1, 2);
    graph::depth_first_search::addEdge(&g1, 2, 3);
    graph::depth_first_search::addEdge(&g1, 3, 1);

    std::vector<size_t> expected1 {1, 2, 3}; // 对于上述样本数据，这是期望的输出
    assert(graph::depth_first_search::dfs(g1, start_pos - 1) == expected1);
    std::cout << "通过" << std::endl;

    // 测试 2
    std::cout << "案例 2: " << std::endl;
    start_pos = 1;
    std::vector<std::vector<size_t>> g2(4, std::vector<size_t>());

    graph::depth_first_search::addEdge(&g2, 1, 2);
    graph::depth_first_search::addEdge(&g2, 1, 3);
    graph::depth_first_search::addEdge(&g2, 2, 4);
    graph::depth_first_search::addEdge(&g2, 4, 1);

    std::vector<size_t> expected2 {1, 3, 2, 4}; // 对于上述样本数据，这是期望的输出
    assert(graph::depth_first_search::dfs(g2, start_pos - 1) == expected2);
    std::cout << "通过" << std::endl;

    // 测试 3
    std::cout << "案例 3: " << std::endl;
    start_pos = 2;
    std::vector<std::vector<size_t>> g3(4, std::vector<size_t>());

    graph::depth_first_search::addEdge(&g3, 1, 2);
    graph::depth_first_search::addEdge(&g3, 1, 3);
    graph::depth_first_search::addEdge(&g3, 2, 4);
    graph::depth_first_search::addEdge(&g3, 4, 1);

    std::vector<size_t> expected3 {2, 4, 1, 3}; // 对于上述样本数据，这是期望的输出
    assert(graph::depth_first_search::dfs(g3, start_pos - 1) == expected3);
    std::cout << "通过" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    tests();  // 执行测试

    size_t vertices = 0, edges = 0, start_pos = 1;
    std::vector<size_t> traversal;

    std::cout << "输入顶点数量 : ";
    std::cin >> vertices;
    std::cout << "输入边数量 : ";
    std::cin >> edges;

    // 创建图
    std::vector<std::vector<size_t>> adj(vertices, std::vector<size_t>());

    // 输入边
    std::cout << "输入有边相连的顶点 : " << std::endl;
    while (edges--) {
        size_t u = 0, v = 0;
        std::cin >> u >> v;
        graph::depth_first_search::addEdge(&adj, u, v);
    }

    // 输入起始位置
    std::cout << "输入起始顶点 [1,n]: " << std::endl;
    std::cin >> start_pos;
    start_pos -= 1;
    traversal = graph::depth_first_search::dfs(adj, start_pos);

    // 打印遍历顺序
    for (auto x : traversal) {
        std::cout << x << ' ';
    }

    return 0;
}
