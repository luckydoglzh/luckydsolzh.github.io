/* 实现 Kosaraju 算法以找出图中的强连通分量（SCC）。作者：Anirban166 */

#include <iostream>
#include <stack>
#include <vector>

/**
 * @brief 打印图的邻接列表表示
 * @param a 图的邻接列表
 * @param V 顶点数量
 * @return void
 **/
void print(const std::vector<std::vector<int>> &a, int V) {
    for (int i = 0; i < V; i++) {
        if (!a[i].empty()) {
            std::cout << "i=" << i << "-->";
        }
        for (int j : a[i]) {
            std::cout << j << " ";
        }
        if (!a[i].empty()) {
            std::cout << std::endl;
        }
    }
}

/**
 * @brief 递归函数，将顶点压入栈中
 * @param v 当前顶点
 * @param st 传递的栈（引用）
 * @param vis 访问记录数组（布尔类型）
 * @param adj 图的邻接列表
 * @return void
 **/
void push_vertex(int v, std::stack<int> *st, std::vector<bool> *vis,
                 const std::vector<std::vector<int>> &adj) {
    (*vis)[v] = true;
    for (auto i = adj[v].begin(); i != adj[v].end(); i++) {
        if ((*vis)[*i] == false) {
            push_vertex(*i, st, vis, adj);
        }
    }
    st->push(v);  // 当前顶点处理完后压入栈中
}

/**
 * @brief 递归函数，进行深度优先遍历（DFS）
 * @param v 当前顶点
 * @param vis 访问记录数组（布尔类型）
 * @param grev 反向图
 * @return void
 **/
void dfs(int v, std::vector<bool> *vis,
         const std::vector<std::vector<int>> &grev) {
    (*vis)[v] = true;  // 标记当前顶点为已访问
    for (auto i = grev[v].begin(); i != grev[v].end(); i++) {
        if ((*vis)[*i] == false) {
            dfs(*i, vis, grev);
        }
    }
}

/**
 * @brief 实现 Kosaraju 算法以查找强连通分量
 * @param V 图中的顶点数量
 * @param adj 图的邻接列表
 * @return int 强连通分量的数量
 **/
int kosaraju(int V, const std::vector<std::vector<int>> &adj) {
    std::vector<bool> vis(V, false);  // 访问记录
    std::stack<int> st;                // 存储完成处理的顶点
    for (int v = 0; v < V; v++) {
        if (vis[v] == false) {
            push_vertex(v, &st, &vis, adj);  // 深度优先搜索并填充栈
        }
    }

    // 创建反向图
    std::vector<std::vector<int>> grev(V);
    for (int i = 0; i < V; i++) {
        for (auto j = adj[i].begin(); j != adj[i].end(); j++) {
            grev[*j].push_back(i);  // 添加反向边
        }
    }

    // 重新初始化访问记录
    for (int i = 0; i < V; i++) vis[i] = false;
    int count_scc = 0;  // 强连通分量计数
    while (!st.empty()) {
        int t = st.top();
        st.pop();
        if (vis[t] == false) {
            dfs(t, &vis, grev);  // 在反向图上进行 DFS
            count_scc++;         // 增加强连通分量计数
        }
    }
    return count_scc;  // 返回强连通分量的数量
}

// 主函数，输入所需的值（不硬编码）
int main() {
    int t = 0;
    std::cin >> t;  // 输入测试用例数量
    while (t--) {
        int a = 0, b = 0;  // a -> 顶点数量，b -> 有向边数量
        std::cin >> a >> b;
        int m = 0, n = 0;
        std::vector<std::vector<int>> adj(a + 1);  // 邻接列表，顶点从 1 开始
        for (int i = 0; i < b; i++) {
            std::cin >> m >> n;  // 输入边 m -> n
            adj[m].push_back(n);
        }
        // 调用函数，输出强连通分量的数量
        std::cout << kosaraju(a, adj) << std::endl;
    }
    return 0;
}
