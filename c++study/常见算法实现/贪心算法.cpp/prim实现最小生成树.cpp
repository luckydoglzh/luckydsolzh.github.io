#include <iostream>
using namespace std;

#define V 4           // 图中顶点的数量
#define INFINITY 99999  // 定义无穷大的值

// 定义图的邻接矩阵
int graph[V][V] = {{0, 5, 1, 2}, 
                   {5, 0, 3, 3}, 
                   {1, 3, 0, 4}, 
                   {2, 3, 4, 0}};

struct mst {
    bool visited;  // 是否已访问
    int key;      // 最小边的权重
    int near;     // 与最小边相连的顶点
};

mst MST_Array[V]; // 存储最小生成树的信息

// 初始化函数
void initilize() {
    for (int i = 0; i < V; i++) {
        MST_Array[i].visited = false;  // 标记为未访问
        MST_Array[i].key = INFINITY;    // 将权重初始化为无穷大
        MST_Array[i].near = i;           // 初始化为自身
    }

    MST_Array[0].key = 0; // 从第一个顶点开始
}

// 更新与当前生成树连接的边
void updateNear() {
    for (int v = 0; v < V; v++) {
        int min = INFINITY;  // 初始化最小值为无穷大
        int minIndex = 0;    // 存储最小边的索引
        for (int i = 0; i < V; i++) {
            // 寻找未访问的最小边
            if (MST_Array[i].key < min && !MST_Array[i].visited && 
                MST_Array[i].key != INFINITY) {
                min = MST_Array[i].key;   // 更新最小值
                minIndex = i;             // 更新最小边的索引
            }
        }

        MST_Array[minIndex].visited = true; // 标记为已访问

        // 更新与新加入的顶点相连的边
        for (int i = 0; i < V; i++) {
            if (graph[minIndex][i] != 0 && graph[minIndex][i] < INFINITY) {
                // 如果存在边且权重小于当前权重
                if (graph[minIndex][i] < MST_Array[i].key) {
                    MST_Array[i].key = graph[minIndex][i]; // 更新权重
                    MST_Array[i].near = minIndex;           // 更新连接顶点
                }
            }
        }
    }
}

// 显示生成树的结果
void show() {
    for (int i = 0; i < V; i++) {
        cout << i << "  -  " << MST_Array[i].near << "\t"
             << graph[i][MST_Array[i].near] << "\n"; // 输出顶点和相连的边
    }
}

int main() {
    initilize();     // 初始化数据
    updateNear();    // 更新生成树
    show();          // 显示结果
    return 0;
}
