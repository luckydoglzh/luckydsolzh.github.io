/*
 * Author: Amit Kumar
 * Created: May 24, 2020
 * Copyright: 2020, Open-Source
 * Last Modified: May 25, 2020
 */

#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

// 图中节点的最大容量
const int MAXN = 505;

class Graph {
    // 残量容量和容量矩阵
    std::vector<std::vector<int>> residual_capacity, capacity;
    int total_nodes = 0; // 总节点数
    int total_edges = 0; // 总边数
    int source = 0; // 源节点
    int sink = 0; // 汇节点
    std::vector<int> parent; // 存储路径中的父节点
    std::vector<std::tuple<int, int, int>> edge_participated; // 参与流的边
    std::bitset<MAXN> visited; // 访问标记
    int max_flow = 0; // 最大流

    // 广度优先搜索，寻找增广路径
    bool bfs(int source, int sink) {
        visited.reset(); // 重置访问标记
        std::queue<int> q;
        q.push(source);
        bool is_path_found = false;

        while (!q.empty() && !is_path_found) {
            int current_node = q.front();
            visited.set(current_node); // 标记当前节点为已访问
            q.pop();
            for (int i = 0; i < total_nodes; ++i) {
                // 如果当前边的残量大于0且目标节点未被访问
                if (residual_capacity[current_node][i] > 0 && !visited[i]) {
                    visited.set(i); // 标记目标节点为已访问
                    parent[i] = current_node; // 更新父节点
                    if (i == sink) { // 如果到达汇节点
                        return true;
                    }
                    q.push(i); // 将目标节点入队
                }
            }
        }
        return false; // 未找到增广路径
    }

 public:
    // 设置图的节点和边
    void set_graph() {
        std::cin >> total_nodes >> total_edges >> source >> sink; // 输入总节点数、总边数、源节点和汇节点
        parent = std::vector<int>(total_nodes, -1); // 初始化父节点
        capacity = residual_capacity = std::vector<std::vector<int>>(
            total_nodes, std::vector<int>(total_nodes)); // 初始化容量和残量矩阵

        for (int start = 0, destination = 0, capacity_ = 0, i = 0; i < total_edges; ++i) {
            std::cin >> start >> destination >> capacity_; // 输入每条边的起点、终点和容量
            residual_capacity[start][destination] = capacity_; // 设置残量容量
            capacity[start][destination] = capacity_; // 设置总容量
        }
    }

    // 福特-福尔克森算法计算最大流
    void ford_fulkerson() {
        while (bfs(source, sink)) { // 当找到增广路径时
            int current_node = sink;
            int flow = std::numeric_limits<int>::max(); // 设置流的初始值为最大整数

            // 计算当前增广路径的最小残量
            while (current_node != source) {
                int parent_ = parent[current_node];
                flow = std::min(flow, residual_capacity[parent_][current_node]);
                current_node = parent_; // 回溯到源节点
            }
            current_node = sink;
            max_flow += flow; // 更新最大流

            // 更新残量图
            while (current_node != source) {
                int parent_ = parent[current_node];
                residual_capacity[parent_][current_node] -= flow; // 减去流量
                residual_capacity[current_node][parent_] += flow; // 反向增加流量
                current_node = parent_; // 回溯到源节点
            }
        }
    }

    // 输出流的信息
    void print_flow_info() {
        for (int i = 0; i < total_nodes; ++i) {
            for (int j = 0; j < total_nodes; ++j) {
                // 如果该边参与了流
                if (capacity[i][j] && residual_capacity[i][j] < capacity[i][j]) {
                    edge_participated.emplace_back(std::make_tuple(
                        i, j, capacity[i][j] - residual_capacity[i][j])); // 记录参与流的边
                }
            }
        }
        std::cout << "\nNodes : " << total_nodes << "\nMax flow: " << max_flow
                  << "\nEdge present in flow: " << edge_participated.size()
                  << '\n';
        std::cout << "\nSource\tDestination\tCapacity\n";
        for (auto& edge_data : edge_participated) {
            int source = 0, destination = 0, capacity_ = 0;
            std::tie(source, destination, capacity_) = edge_data; // 解包边的信息
            std::cout << source << "\t" << destination << "\t\t" << capacity_ << '\n';
        }
    }
};

int main() {
    /*
       输入图: (用于测试 )
        4 5 0 3
        0 1 10
        1 2 1
        1 3 1
        0 2 1
        2 3 10
     */
    Graph graph;
    graph.set_graph(); // 设置图
    graph.ford_fulkerson(); // 计算最大流
    graph.print_flow_info(); // 输出流的信息
    return 0;
}
