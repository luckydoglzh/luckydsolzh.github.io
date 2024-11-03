#include <limits.h>  // 包含 INT_MAX 的定义
#include <iostream>  // 用于输入输出操作

using namespace std;

// 封装边的类
class Edge {
 public:
    int src, dst, weight;  // 源顶点、目标顶点和权重
};

// 封装图的类
class Graph {
 public:
    int vertexNum, edgeNum;  // 顶点数和边数
    Edge *edges;  // 存储边的数组

    // 构造一个包含 V 个顶点和 E 条边的图
    Graph(int V, int E) {
        this->vertexNum = V;  // 设置顶点数
        this->edgeNum = E;    // 设置边数
        this->edges = (Edge *)malloc(E * sizeof(Edge));  // 分配边的内存
    }

    // 将给定的边添加到图中
    void addEdge(int src, int dst, int weight) {
        static int edgeInd = 0;  // 静态变量，用于跟踪当前边的索引
        if (edgeInd < this->edgeNum) {
            Edge newEdge;  // 创建新边
            newEdge.src = src;    // 设置源顶点
            newEdge.dst = dst;    // 设置目标顶点
            newEdge.weight = weight;  // 设置权重
            this->edges[edgeInd++] = newEdge;  // 将新边添加到数组中
        }
    }
};

// 打印距离的工具函数
void print(int dist[], int V) {
    cout << "\nVertex  Distance" << endl;  // 打印标题
    for (int i = 0; i < V; i++) {
        if (dist[i] != INT_MAX)
            cout << i << "\t" << dist[i] << endl;  // 打印每个顶点及其距离
        else
            cout << i << "\tINF" << endl;  // 如果距离为无穷大，则打印 INF
    }
}

// 主函数：使用 Bellman-Ford 算法找到从给定源到所有其他顶点的最短路径。
// 还检测负权重循环
void BellmanFord(Graph graph, int src) {
    int V = graph.vertexNum;  // 获取顶点数
    int E = graph.edgeNum;    // 获取边数
    int dist[V];  // 创建距离数组

    // 初始化距离数组，除了源顶点外都设置为无穷大
    for (int i = 0; i < V; i++) dist[i] = INT_MAX;  // 所有距离初始化为无穷大
    dist[src] = 0;  // 源顶点的距离设置为 0

    // 计算从源到所有边的最短路径距离
    // 一个路径最多可以包含 (|V|-1) 条边
    for (int i = 0; i <= V - 1; i++)
        for (int j = 0; j < E; j++) {
            int u = graph.edges[j].src;  // 获取边的源顶点
            int v = graph.edges[j].dst;  // 获取边的目标顶点
            int w = graph.edges[j].weight;  // 获取边的权重

            // 进行松弛操作
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;  // 更新目标顶点的最短路径距离
        }

    // 再次进行内循环检查负权重循环
    for (int j = 0; j < E; j++) {
        int u = graph.edges[j].src;  // 获取边的源顶点
        int v = graph.edges[j].dst;  // 获取边的目标顶点
        int w = graph.edges[j].weight;  // 获取边的权重

        // 如果还能进行松弛，说明存在负权重循环
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            cout << "图包含负权重循环。因此，最短距离无法保证。" << endl;
            return;  // 返回
        }
    }

    print(dist, V);  // 打印最终的距离结果
}

// 驱动函数
int main() {
    int V, E, gsrc;  // 顶点数、边数和源顶点
    int src, dst, weight;  // 源、目标和权重
    cout << "输入顶点数量: ";
    cin >> V;  // 输入顶点数量
    cout << "输入边数量: ";
    cin >> E;  // 输入边数量
    Graph G(V, E);  // 创建图
    for (int i = 0; i < E; i++) {
        cout << "\n边 " << i + 1 << "\n输入源: ";
        cin >> src;  // 输入边的源顶点
        cout << "输入目标: ";
        cin >> dst;  // 输入边的目标顶点
        cout << "输入权重: ";
        cin >> weight;  // 输入边的权重
        G.addEdge(src, dst, weight);  // 添加边到图中
    }
    cout << "\n输入源: ";
    cin >> gsrc;  // 输入源顶点
    BellmanFord(G, gsrc);  // 调用 Bellman-Ford 函数

    return 0;  // 退出
}
