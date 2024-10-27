/**
 * @author [Jason Nardoni](https://github.com/JNardoni)
 * @file
 *
 * @brief
 * [Borůvka算法](https://en.wikipedia.org/wiki/Borůvka's_algorithm) 用于寻找最小生成树
 *
 *
 * @details
 * Borůvka算法是一种贪心算法，通过从小树开始，并将它们组合起来构建更大的树来找到最小生成树（MST）。
 * 1. 为每个顶点创建一个组。
 * 2. 检查每个顶点的每条边，寻找最小权重。跟踪当前组的最小边。
 * 3. 根据共享最小边的组合并每个组，将最小边添加到MST中。
 * 4. 重复步骤2-3，直到所有顶点合并成一个组。
 *
 * 该算法假定图是连通的。非连接边可以用0或INT_MAX表示。
 *
 */

#include <cassert>   /// 用于assert
#include <climits>   /// 用于INT_MAX
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于std::vector

/**
 * @namespace greedy_algorithms
 * @brief 贪心算法
 */
namespace greedy_algorithms {
/**
 * @namespace boruvkas_minimum_spanning_tree
 * @brief Borůvka算法的实现函数
 */
namespace boruvkas_minimum_spanning_tree {
/**
 * @brief 递归返回树根的顶点父节点
 * @param parent 要检查的数组
 * @param v 要查找父节点的顶点
 * @returns 顶点的父节点
 */
int findParent(std::vector<std::pair<int, int>> parent, const int v) {
    if (parent[v].first != v) {
        parent[v].first = findParent(parent, parent[v].first);
    }

    return parent[v].first;
}

/**
 * @brief Borůvka算法的实现
 * @param adj 图的邻接矩阵，存储为2D向量
 * @returns 作为2D向量的最小生成树（MST）
 */
std::vector<std::vector<int>> boruvkas(std::vector<std::vector<int>> adj) {
    size_t size = adj.size();
    size_t total_groups = size;

    if (size <= 1) {
        return adj;
    }

    // 存储当前的最小生成树（MST）。随着组的合并，它们被添加到MST中
    std::vector<std::vector<int>> MST(size, std::vector<int>(size, INT_MAX));
    for (int i = 0; i < size; i++) {
        MST[i][i] = 0;
    }

    // 第一步：为每个顶点创建一个组

    // 存储顶点的父节点及其当前深度，均初始化为0
    std::vector<std::pair<int, int>> parent(size, std::make_pair(0, 0));

    for (int i = 0; i < size; i++) {
        parent[i].first =
            i;  // 将每个顶点的父节点设置为自身，深度保持为0
    }

    // 重复直到所有顶点都在一个组中
    while (total_groups > 1) {
        std::vector<std::pair<int, int>> smallest_edge(
            size, std::make_pair(-1, -1));  // 配对：起始节点，结束节点

        // 第二步：检查每个顶点寻找其最小边，只使用邻接矩阵的右半部分
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (adj[i][j] == INT_MAX || adj[i][j] == 0) {  // 没有连接
                    continue;
                }

                // 查找起点和终点的父节点，以确保它们不在同一组
                int parentA = findParent(parent, i);
                int parentB = findParent(parent, j);

                if (parentA != parentB) {
                    // 获取第一个组的当前最小边的起始和结束点
                    int start = smallest_edge[parentA].first;
                    int end = smallest_edge[parentA].second;

                    // 如果没有当前最小边，或者新边更小，则记录新的最小边
                    if (start == -1 || adj[i][j] < adj[start][end]) {
                        smallest_edge[parentA].first = i;
                        smallest_edge[parentA].second = j;
                    }

                    // 对第二组执行相同操作
                    start = smallest_edge[parentB].first;
                    end = smallest_edge[parentB].second;

                    if (start == -1 || adj[j][i] < adj[start][end]) {
                        smallest_edge[parentB].first = j;
                        smallest_edge[parentB].second = i;
                    }
                }
            }
        }

        // 第三步：根据最小边合并组

        for (int i = 0; i < size; i++) {
            // 确保最小边存在
            if (smallest_edge[i].first != -1) {
                // 最小边的起始和结束点
                int start = smallest_edge[i].first;
                int end = smallest_edge[i].second;

                // 两个组的父节点 - A始终是自身
                int parentA = i;
                int parentB = findParent(parent, end);

                // 确保两个节点不共享相同的父节点。如果两组通过公共最短边合并过，会发生这种情况
                if (parentA == parentB) {
                    continue;
                }

                // 在合并时尽量平衡树。较浅树的父节点指向较深树的父节点。
                if (parent[parentA].second < parent[parentB].second) {
                    parent[parentB].first = parentA;  // 新父节点
                    parent[parentB].second++;         // 增加深度
                } else {
                    parent[parentA].first = parentB;
                    parent[parentA].second++;
                }
                // 将连接添加到MST中，使用邻接矩阵的两个部分
                MST[start][end] = adj[start][end];
                MST[end][start] = adj[end][start];
                total_groups--;  // 组数减少1
            }
        }
    }
    return MST;
}

/**
 * @brief 计算给定树中边的总和
 * @param adj 2D向量邻接矩阵
 * @returns 树的大小（int类型）
 */
int test_findGraphSum(std::vector<std::vector<int>> adj) {
    size_t size = adj.size();
    int sum = 0;

    // 遍历邻接矩阵的一侧，计算每条边的和
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (adj[i][j] < INT_MAX) {
                sum += adj[i][j];
            }
        }
    }
    return sum;
}
}  // namespace boruvkas_minimum_spanning_tree
}  // namespace greedy_algorithms

/**
 * @brief 自我测试实现
 * @returns void
 */
static void tests() {
    std::cout << "开始测试...\n\n";
    std::vector<std::vector<int>> graph = {
        {0, 5, INT_MAX, 3, INT_MAX}, {5, 0, 2, INT_MAX, 5},
        {INT_MAX, 2, 0, INT_MAX, 3}, {3, INT_MAX, INT_MAX, 0, INT_MAX},
        {INT_MAX, 5, 3, INT_MAX, 0},
    };
    std::vector<std::vector<int>> MST =
        greedy_algorithms::boruvkas_minimum_spanning_tree::boruvkas(graph);
    assert(greedy_algorithms::boruvkas_minimum_spanning_tree::test_findGraphSum(
               MST) == 13);
    std::cout << "第1个测试通过!" << std::endl;

    graph = {{0, 2, 0, 6, 0},
             {2, 0, 3, 8, 5},
             {0, 3, 0, 0, 7},
             {6, 8, 0, 0, 9},
             {0, 5, 7, 9, 0}};
    MST = greedy_algorithms::boruvkas_minimum_spanning_tree::boruvkas(graph);
    assert(greedy_algorithms::boruvkas_minimum_spanning_tree::test_findGraphSum(
               MST) == 16);
    std::cout << "第2个测试通过!" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 退出时返回
 */
int main() {
    tests();  // 运行自我测试实现
    return 0;
}
