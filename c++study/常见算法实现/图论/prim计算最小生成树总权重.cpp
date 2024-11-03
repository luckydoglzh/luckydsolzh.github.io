// C++ 程序实现 Prim 算法
#include <iostream>
#include <queue>
#include <vector>

using PII = std::pair<int, int>; // 定义一个整型对，表示边的权重和节点

// Prim 算法实现
int prim(int x, const std::vector<std::vector<PII>> &graph) {
    // 优先队列，用于根据边的权重维护边
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> Q;
    std::vector<bool> marked(graph.size(), false); // 标记数组，跟踪已添加的节点
    int minimum_cost = 0; // 最小生成树的总权重

    Q.push(std::make_pair(0, x)); // 将起始节点的边权重和节点推入优先队列
    while (!Q.empty()) {
        // 选择权重最小的边
        PII p = Q.top();
        Q.pop();
        x = p.second; // 当前节点
        // 检查是否形成环路
        if (marked[x] == true) {
            continue; // 如果当前节点已标记，则跳过
        }
        minimum_cost += p.first; // 增加当前边的权重
        marked[x] = true; // 标记当前节点为已访问

        // 遍历当前节点的邻居
        for (const PII &neighbor : graph[x]) {
            int y = neighbor.second; // 邻居节点
            if (marked[y] == false) { // 如果邻居节点未被访问
                Q.push(neighbor); // 将邻居边推入优先队列
            }
        }
    }
    return minimum_cost; // 返回最小生成树的总权重
}

int main() {
    int nodes = 0, edges = 0;
    std::cin >> nodes >> edges;  // 输入节点数和边数
    if (nodes == 0 || edges == 0) {
        return 0; // 如果节点或边数为0，则结束程序
    }

    std::vector<std::vector<PII>> graph(nodes); // 创建邻接表表示图

    // 输入每条边的节点及其权重
    for (int i = 0; i < edges; ++i) {
        int x = 0, y = 0, weight = 0;
        std::cin >> x >> y >> weight; // 输入边的起点、终点和权重
        graph[x].push_back(std::make_pair(weight, y)); // 添加边到邻接表
        graph[y].push_back(std::make_pair(weight, x)); // 添加反向边到邻接表
    }

    // 选择节点 1 作为起始节点
    int minimum_cost = prim(1, graph); // 调用 Prim 算法计算最小生成树的权重
    std::cout << minimum_cost << std::endl; // 输出最小生成树的总权重
    return 0;
}
