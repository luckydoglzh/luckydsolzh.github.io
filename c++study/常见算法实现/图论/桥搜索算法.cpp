/*
 *  Copyright : 2020 , MIT
 *  Author : Amit Kumar (offamitkumar)
 *  Last Modified Date: May 24, 2020
 *
 */
#include <algorithm>  // 用于 min 和 max
#include <iostream>   // 用于 cout
#include <vector>     // 用于 std::vector

class Solution {
    std::vector<std::vector<int>> graph;  // 图的邻接表
    std::vector<int> in_time, out_time;   // 节点的入时间和出时间
    int timer = 0;                         // 时间计数器
    std::vector<std::vector<int>> bridge;  // 存储桥的结果
    std::vector<bool> visited;             // 访问标记

    // 深度优先搜索 (DFS) 方法
    void dfs(int current_node, int parent) {
        visited.at(current_node) = true;  // 标记当前节点为已访问
        in_time[current_node] = out_time[current_node] = timer++;  // 设置入时间和出时间
        for (auto& itr : graph[current_node]) {  // 遍历邻接节点
            if (itr == parent) {
                continue;  // 如果是父节点，跳过
            }
            if (!visited[itr]) {
                dfs(itr, current_node);  // 递归访问未访问的邻接节点
                // 检查当前节点与邻接节点之间是否存在桥
                if (out_time[itr] > in_time[current_node]) {
                    bridge.push_back({itr, current_node});  // 记录桥
                }
            }
            // 更新当前节点的出时间
            out_time[current_node] = std::min(out_time[current_node], out_time[itr]);
        }
    }

 public:
    // 查找桥的方法
    std::vector<std::vector<int>> search_bridges(int n, const std::vector<std::vector<int>>& connections) {
        timer = 0;  // 重置时间计数器
        graph.resize(n);  // 根据节点数初始化图
        in_time.assign(n, 0);  // 初始化入时间
        visited.assign(n, false);  // 初始化访问标记
        out_time.assign(n, 0);  // 初始化出时间
        
        // 构建图的邻接表
        for (auto& itr : connections) {
            graph.at(itr[0]).push_back(itr[1]);
            graph.at(itr[1]).push_back(itr[0]);
        }
        dfs(0, -1);  // 从第一个节点开始 DFS
        return bridge;  // 返回找到的桥
    }
};

/**
 * 主函数
 */
int main() {
    Solution s1;
    int number_of_node = 5;  // 节点数量
    std::vector<std::vector<int>> node;  // 存储连接的边
    node.push_back({0, 1});
    node.push_back({1, 3});
    node.push_back({1, 2});
    node.push_back({2, 4});
    /*
     *     0 <--> 1 <---> 2
     *            ^       ^
     *            |       |
     *            |       |
     *            \/     \/
     *            3       4
     *
     * 在这个图中有 4 条桥: [0,2] , [2,4] , [3,5] , [1,2]
     *
     * 我假设图是双向的并且是连通的。
     *
     */
    std::vector<std::vector<int>> bridges = s1.search_bridges(number_of_node, node);
    std::cout << bridges.size() << " 条桥被找到！\n";
    for (auto& itr : bridges) {
        std::cout << itr[0] << " --> " << itr[1] << '\n';
    }
    return 0;
}
