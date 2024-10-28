// 在本问题中，有根树指满足以下条件的 有向 图。该树只有一个根节点，所有其他节点都是该根节点的后继。该树除了根节点之外的每一个节点都有且只有一个父节点，而根节点没有父节点。

// 输入一个有向图，该图由一个有着 n 个节点（节点值不重复，从 1 到 n）的树及一条附加的有向边构成。附加的边包含在 1 到 n 中的两个不同顶点间，这条附加的边不属于树中已存在的边。

// 结果图是一个以边组成的二维数组 edges 。 每个元素是一对 [ui, vi]，用以表示 有向 图中连接顶点 ui 和顶点 vi 的边，其中 ui 是 vi 的一个父节点。

// 返回一条能删除的边，使得剩下的图是有 n 个节点的有根树。若有多个答案，返回最后出现在给定二维数组的答案。
int* ancestor;

int find(int index) {
    return index == ancestor[index] ? index : (ancestor[index] = find(ancestor[index]));
}

void merge(int u, int v) {
    ancestor[find(u)] = find(v);
}

int* findRedundantDirectedConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    int n = edgesSize;
    ancestor = malloc(sizeof(int) * (n + 1));
    for (int i = 1; i <= n; ++i) {
        ancestor[i] = i;
    }
    int parent[n + 1];
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
    }
    int conflict = -1;
    int cycle = -1;
    for (int i = 0; i < n; ++i) {
        int node1 = edges[i][0], node2 = edges[i][1];
        if (parent[node2] != node2) {
            conflict = i;
        } else {
            parent[node2] = node1;
            if (find(node1) == find(node2)) {
                cycle = i;
            } else {
                merge(node1, node2);
            }
        }
    }
    int* redundant = malloc(sizeof(int) * 2);
    *returnSize = 2;
    if (conflict < 0) {
        redundant[0] = edges[cycle][0], redundant[1] = edges[cycle][1];
        return redundant;
    } else {
        int* conflictEdge = edges[conflict];
        if (cycle >= 0) {
            redundant[0] = parent[conflictEdge[1]], redundant[1] = conflictEdge[1];
            return redundant;
        } else {
            redundant[0] = conflictEdge[0], redundant[1] = conflictEdge[1];
            return redundant;
        }
    }
    return redundant;
}

