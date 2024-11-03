#include <algorithm>
#include <iostream>
#include <vector>

int number_of_vertices,
    number_of_edges;  // 顶点数 (V) 和边数 (E)
std::vector<std::vector<int>> graph; // 图的邻接表表示
std::vector<bool> visited; // 访问标记数组
std::vector<int> topological_order; // 存储拓扑排序结果

// 深度优先搜索
void dfs(int v) {
    visited[v] = true; // 标记当前节点为已访问
    for (int u : graph[v]) { // 遍历当前节点的所有邻接节点
        if (!visited[u]) { // 如果邻接节点未访问
            dfs(u); // 递归访问该邻接节点
        }
    }
    topological_order.push_back(v); // 当前节点处理完成，加入拓扑排序结果
}

// 拓扑排序
void topological_sort() {
    visited.assign(number_of_vertices, false); // 初始化访问标记
    topological_order.clear(); // 清空之前的结果
    for (int i = 0; i < number_of_vertices; ++i) {
        if (!visited[i]) { // 如果节点未访问
            dfs(i); // 从该节点开始 DFS
        }
    }
    reverse(topological_order.begin(), topological_order.end()); // 反转结果
}

int main() {
    std::cout << "请输入顶点数和有向边数:\n"; // 提示用户输入
    std::cin >> number_of_vertices >> number_of_edges; // 输入顶点数和边数
    int x = 0, y = 0;
    graph.resize(number_of_vertices, std::vector<int>()); // 初始化图的邻接表
    for (int i = 0; i < number_of_edges; ++i) {
        std::cin >> x >> y; // 输入每条边的起点和终点
        x--, y--;  // 将 1 索引转换为 0 索引
        graph[x].push_back(y); // 将边添加到邻接表中
    }
    topological_sort(); // 进行拓扑排序
    std::cout << "拓扑排序结果 : \n";
    for (int v : topological_order) {
        std::cout << v + 1 << ' '; // 将零基索引转换回一基索引输出
    }
    std::cout << '\n';
    return 0;
}
