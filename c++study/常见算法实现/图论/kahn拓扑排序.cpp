#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

// 声明拓扑排序函数
std::vector<int> topoSortKahn(int N, const std::vector<std::vector<int>> &adj);

int main() {
    int nodes = 0, edges = 0;
    std::cin >> edges >> nodes; // 输入边数和节点数
    if (edges == 0 || nodes == 0) {
        return 0; // 如果边数或节点数为0，则结束程序
    }
    int u = 0, v = 0;

    std::vector<std::vector<int>> graph(nodes); // 创建邻接表表示图

    // 构建图
    // 示例输入:
    // 6 6
    // 5 0 5 2 2 3 4 0 4 1 1 3

    for (int i = 0; i < edges; i++) {
        std::cin >> u >> v; // 输入边的起点 u 和终点 v
        graph[u].push_back(v); // 将 v 添加到 u 的邻接列表中
    }

    std::vector<int> topo = topoSortKahn(nodes, graph); // 调用 Kahn 算法进行拓扑排序
    // 输出拓扑排序后的节点
    for (int i = 0; i < nodes; i++) {
        std::cout << topo[i] << " "; // 输出每个节点
    }
}

// Kahn 算法实现拓扑排序
std::vector<int> topoSortKahn(int V, const std::vector<std::vector<int>> &adj) {
    std::vector<bool> vis(V + 1, false); // 访问标记数组
    std::vector<int> deg(V + 1, 0); // 入度数组

    // 计算每个节点的入度
    for (int i = 0; i < V; i++) {
        for (int j : adj[i]) {
            deg[j]++; // 增加 j 的入度
        }
    }

    std::queue<int> q; // 用于存储入度为 0 的节点
    // 将入度为 0 的节点入队
    for (int i = 0; i < V; i++) {
        if (deg[i] == 0) {
            q.push(i);
            vis[i] = true; // 标记该节点为已访问
        }
    }

    std::vector<int> arr(V + 1, 0); // 存储拓扑排序结果
    int count = 0; // 计数器
    // 进行拓扑排序
    while (!q.empty()) {
        int cur = q.front(); // 当前节点
        q.pop();
        arr[count++] = cur; // 将当前节点添加到结果数组
        // 遍历当前节点的邻接节点
        for (int i : adj[cur]) {
            if (!vis[i]) {
                deg[i]--; // 减少邻接节点的入度
                if (deg[i] == 0) {
                    q.push(i); // 如果入度为 0，入队
                    vis[i] = true; // 标记该节点为已访问
                }
            }
        }
    }
    return arr; // 返回拓扑排序结果
}
