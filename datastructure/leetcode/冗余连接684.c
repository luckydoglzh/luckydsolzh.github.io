/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
// 树可以看成是一个连通且 无环 的 无向 图。

// 给定往一棵 n 个节点 (节点值 1～n) 的树中添加一条边后的图。添加的边的两个顶点包含在 1 到 n 中间，且这条附加的边不属于树中已存在的边。图的信息记录于长度为 n 的二维数组 edges ，edges[i] = [ai, bi] 表示图中在 ai 和 bi 之间存在一条边。

// 请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n 个节点的树。如果有多个答案，则返回数组 edges 中最后出现的那个。
// 并查集的思想：查找两个点是否闭环：直接看他的根节点是否相同
#define MAXN 1001

int parent[MAXN]; // 并查集的父节点数组
int rank[MAXN];   // 并查集的秩数组（用于优化）

// 初始化并查集
void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// 查找并查集根节点（路径压缩）
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// 合并两个集合（按秩合并）
int unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) {
        return 1; // x 和 y 在同一集合，形成环
    }
    if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
    return 0;
}

int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    *returnSize = 2;
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    init(edgesSize);

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        if (unionSets(u, v)) {
            result[0] = u;
            result[1] = v;
        }
    }
    return result;
}