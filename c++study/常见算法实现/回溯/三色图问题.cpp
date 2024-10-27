//给你四个点的邻接矩阵，需要判断是否可以通过三种颜色上色，相邻节点不可以使用相同的颜色
#include <array>     /// for std::array
#include <iostream>  /// for IO operations

/**
 * @namespace backtracking
 * @brief 回溯算法命名空间
 */
namespace backtracking {
    
/**
 * @namespace graph_coloring
 * @brief 图着色算法命名空间
 */
namespace graph_coloring {

/**
 * @brief 打印每个顶点分配的颜色
 * @tparam V 图中的顶点数
 * @param color 包含每个顶点颜色的数组
 */
template <size_t V>
void printSolution(const std::array<int, V>& color) {
    std::cout << "以下是分配的颜色:\n";
    for (auto& col : color) {
        std::cout << col << " ";
    }
    std::cout << "\n";
}

/**
 * @brief 检查当前颜色是否可以安全分配给顶点 v
 * @tparam V 图中的顶点数
 * @param v 顶点索引
 * @param graph 图的邻接矩阵
 * @param color 已分配给各顶点的颜色数组
 * @param c 要检查的颜色值
 * @returns 若分配颜色 c 给顶点 v 合法，则返回 `true`，否则返回 `false`
 */
template <size_t V>
bool isSafe(int v, const std::array<std::array<int, V>, V>& graph,
            const std::array<int, V>& color, int c) {
    for (int i = 0; i < V; i++) {
        // 如果顶点 v 与顶点 i 相连，且顶点 i 的颜色与待分配颜色 c 相同，则不安全
        if (graph[v][i] && c == color[i]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief 递归函数，解决图着色问题
 * @tparam V 图中的顶点数
 * @param graph 图的邻接矩阵
 * @param m 可用的颜色数
 * @param color 各顶点的颜色数组 (就地修改)
 * @param v 当前要分配颜色的顶点索引
 */
template <size_t V>
void graphColoring(const std::array<std::array<int, V>, V>& graph, int m,
                   std::array<int, V> color, int v) {
    // 基本情况：所有顶点都已分配颜色
    if (v == V) {
        printSolution<V>(color);  // 输出当前颜色分配方案
        return;
    }

    // 尝试将每种颜色从 1 到 m 分配给当前顶点 v
    for (int c = 1; c <= m; c++) {
        // 检查分配颜色 c 给顶点 v 是否安全
        if (isSafe<V>(v, graph, color, c)) {
            color[v] = c;  // 分配颜色 c 给顶点 v

            // 递归分配给下一个顶点
            graphColoring<V>(graph, m, color, v + 1);

            // 回溯：如果当前颜色分配方案不成功，将顶点 v 的颜色重置为 0
            color[v] = 0;
        }
    }
}
}  // namespace graph_coloring
}  // namespace backtracking

/**
 * @brief 主函数
 * @returns 0 正常退出
 */
int main() {

    const int V = 4;  // 图中的顶点数
    std::array<std::array<int, V>, V> graph = {
        std::array<int, V>({0, 1, 1, 1}), std::array<int, V>({1, 0, 1, 0}),
        std::array<int, V>({1, 1, 0, 1}), std::array<int, V>({1, 0, 1, 0})};

    int m = 3;  // 可用的颜色数
    std::array<int, V> color{};  // 用于存储各顶点的颜色分配情况

    // 调用图着色函数
    backtracking::graph_coloring::graphColoring<V>(graph, m, color, 0);
    return 0;
}
