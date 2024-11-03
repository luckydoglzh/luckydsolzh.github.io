// C++ 程序：使用自底向上的动态规划计算树的高度

/*
 * 给定一个以节点 1 为根的树。
 * 任务是找出树的高度。
 * 示例：-
 * 4
 * 1 2
 * 1 3
 * 2 4
 * 这可以表示为
 *   1
 *  / \
 * 2   3
 * |
 * 4
 *
 * 树的高度：- 2
 */

#include <iostream>
#include <vector>

// 全局声明
// 节点数最大限制
const int MAX = 1e5;
// 邻接表
std::vector<int> adj[MAX];
std::vector<bool> visited; // 记录节点是否被访问过
std::vector<int> dp;       // 存储每个节点的高度

// 深度优先搜索函数
void depth_first_search(int u) {
    visited[u] = true; // 标记当前节点为已访问
    int child_height = 1; // 初始化子树的高度为 1
    for (int v : adj[u]) { // 遍历当前节点的所有邻接节点
        if (!visited[v]) { // 如果该邻接节点未被访问
            depth_first_search(v); // 递归访问该节点

            // 从所有子节点中选择最大的子树高度
            child_height = std::max(child_height, dp[v] + 1);
        }
    }
    // 将最大子树高度赋值给当前节点
    dp[u] = child_height;
}

int main() {
    // 输入节点数量
    int number_of_nodes;
    std::cout << "请输入树的节点数量: " << std::endl;
    std::cin >> number_of_nodes;

    // u, v 表示树的无向边
    int u, v;
    // 树恰好包含 n-1 条边，其中 n 表示节点数量
    std::cout << "请输入树的边: " << std::endl;
    for (int i = 0; i < number_of_nodes - 1; i++) {
        std::cin >> u >> v;
        // 无向树 u -> v 和 v -> u
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // 初始化所有节点为未访问
    visited.assign(number_of_nodes + 1, false);
    // 初始化所有节点的高度为 0
    dp.assign(number_of_nodes + 1, 0);
    // 调用函数初始化所有节点的高度
    depth_first_search(1);
    std::cout << "树的高度: " << dp[1] << std::endl;
}
