#include <climits>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

// 定义一个图的包装类
class Graph {
 public:
    int vertexNum;  // 顶点数量
    int **edges;    // 用于存储图中边的二维数组

    // 构造函数：创建一个包含 V 个顶点的图
    Graph(int V) {
        this->vertexNum = V;
        this->edges = new int *[V];
        for (int i = 0; i < V; i++) {
            this->edges[i] = new int[V];
            for (int j = 0; j < V; j++) this->edges[i][j] = INT_MAX;  // 初始化边的权重为无穷大
            this->edges[i][i] = 0;  // 自环边权重为 0
        }
    }

    // 析构函数：释放动态分配的内存
    ~Graph() {
        for (int i = 0; i < vertexNum; i++) delete[] edges[i];
        delete[] edges;
    }

    // 添加边的函数，将边 (src, dst) 的权重设为 weight
    void addEdge(int src, int dst, int weight) {
        this->edges[src][dst] = weight;
    }
};

// 辅助函数，用于打印距离矩阵
void print(int dist[], int V) {
    cout << "\nFloyd-Warshall 算法计算的距离矩阵：" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i * V + j] != INT_MAX)
                cout << dist[i * V + j] << "\t";
            else
                cout << "INF"
                     << "\t";  // 使用 "INF" 表示无穷大
        }
        cout << endl;
    }
}

// 使用 Floyd-Warshall 算法计算各顶点之间的最短路径
void FloydWarshall(Graph graph) {
    int V = graph.vertexNum;
    int dist[V][V];  // 用于存储最短距离的二维数组

    // 初始化距离数组
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) dist[i][j] = graph.edges[i][j];

    // 计算最短路径
    for (int k = 0; k < V; k++)  // 选择一个中间顶点
        for (int i = 0; i < V; i++)  // 选择一个源顶点
            for (int j = 0; j < V; j++)  // 选择一个目的顶点
                // 如果通过中间顶点 k 可以找到更短的路径，则更新距离
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    // 将二维数组转换为一维数组用于打印
    int dist1d[V * V];
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) dist1d[i * V + j] = dist[i][j];

    print(dist1d, V);  // 打印距离矩阵
}

// 主函数
int main() {
    int V, E;
    int src, dst, weight;
    cout << "请输入顶点数量: ";
    cin >> V;
    cout << "请输入边的数量: ";
    cin >> E;
    Graph G(V);
    for (int i = 0; i < E; i++) {
        cout << "\n边 " << i + 1 << "\n请输入起点: ";
        cin >> src;
        cout << "请输入终点: ";
        cin >> dst;
        cout << "请输入权重: ";
        cin >> weight;
        G.addEdge(src, dst, weight);  // 添加边到图中
    }
    FloydWarshall(G);  // 计算最短路径

    return 0;
}
