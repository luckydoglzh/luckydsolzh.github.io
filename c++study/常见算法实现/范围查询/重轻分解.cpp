#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <list>
#include <numeric>
#include <string>
#include <vector>

namespace range_queries {
namespace heavy_light_decomposition {

/**
 * @brief 一个基本的树，支持二进制提升
 * @tparam X 节点值的数据类型
 * @details 删除默认构造函数，只能通过节点数量来创建实例
 * 默认值：节点索引从 0 开始，根节点为 0，根节点深度为 0
 * 支持功能：提升节点，找到第 k 祖先，寻找最近公共祖先 (LCA)
 */
template <typename X> class Tree {
private:
  std::vector<std::list<int>> t_adj; ///< 邻接表，存储树的边
  const int t_nodes, ///< 树的节点数
      t_maxlift;     ///< 树的最大提升高度
  std::vector<std::vector<int>> t_par; ///< 存储每个节点的 2^k 祖先
  std::vector<int> t_depth, t_size; ///< 存储节点的深度和子树的大小

  int t_root; ///< 树的根节点
  std::vector<X> t_val; ///< 节点的值

  // 仅重载 HLD 类可以访问
  template <typename T> friend class HLD;

  /**
   * @brief 计算子树大小的辅助函数
   * @param u 当前的 DFS 节点
   * @param p 节点 u 的父节点
   */
  void dfs_size(int u, int p = -1) {
    for (const int &v : t_adj[u]) {
      if (v ^ p) {
        dfs_size(v, u);
        t_size[u] += t_size[v];
      }
    }
  }

  /**
   * @brief 用于填充 t_par 向量的辅助函数
   * @param u 当前的 DFS 节点
   * @param p 节点 u 的父节点
   */
  void dfs_lca(int u, int p = -1) {
    t_par[u][0] = p;
    if (p != -1) {
      t_depth[u] = 1 + t_depth[p];
    }
    for (int k = 1; k < t_maxlift; k++) {
      if (t_par[u][k - 1] != -1) {
        t_par[u][k] = t_par[t_par[u][k - 1]][k - 1];
      }
    }

    for (const int &v : t_adj[u]) {
      if (v ^ p) {
        dfs_lca(v, u);
      }
    }
  }

public:
  /**
   * @brief 类的构造函数，初始化成员变量
   * @param nodes 树的节点数量
   */
  explicit Tree(int nodes)
      : t_nodes(nodes), t_maxlift(static_cast<int>(floor(log2(nodes))) + 1) {
    t_root = 0; /* 默认根节点为 0 */
    t_adj.resize(t_nodes);
    t_par.assign(t_nodes, std::vector<int>(t_maxlift, -1));
    t_depth.assign(t_nodes, 0);
    t_size.assign(t_nodes, 1);
    t_val.resize(t_nodes);
  }

  /**
   * @brief 在树中添加一条无向边
   * @param u 边的一个端点
   * @param v 边的另一个端点
   */
  void add_edge(const int u, const int v) {
    t_adj[u].push_back(v);
    t_adj[v].push_back(u);
  }

  /**
   * @brief 设置树的根节点
   * @param new_root 新的根节点
   */
  void change_root(int new_root) { t_root = new_root; }

  /**
   * @brief 设置树中所有节点的值
   * @param node_val 存储每个节点初始值的向量
   */
  void set_node_val(const std::vector<X> &node_val) {
    assert(static_cast<int>(node_val.size()) == t_nodes);
    t_val = node_val;
  }

  /**
   * @brief 初始化函数，在树和节点值设置后调用，初始化相关信息
   */
  void init() {
    assert(t_nodes > 0);
    dfs_size(t_root); // 计算每个子树的大小
    dfs_lca(t_root);  // 计算每个节点的 2^k 祖先
  }

  /**
   * @brief 提升节点，k 次提升
   * @param p 节点 ID 的指针
   * @param dist 向上提升的距离
   */
  void lift(int *const p, int dist) {
    for (int k = 0; k < t_maxlift; k++) {
      if (*p == -1) {
        return;
      }
      if (dist & 1) {
        *p = t_par[*p][k];
      }
      dist >>= 1;
    }
  }

  /**
   * @brief 获取节点 p 的第 k 祖先
   * @param p 节点 ID
   * @param dist 提升的距离
   * @returns p 节点的第 k 祖先
   */
  int kth_ancestor(int p, const int &dist) {
    lift(&p, dist);
    return p;
  }

  /**
   * @brief 获取节点 a 和 b 的最近公共祖先 (LCA)
   * @param a 节点 ID
   * @param b 节点 ID
   * @returns 节点 a 和 b 的 LCA
   */
  int lca(int a, int b) {
    assert(a >= 0 and b >= 0 and a < t_nodes and b < t_nodes);
    if (t_depth[a] > t_depth[b]) {
      lift(&a, t_depth[a] - t_depth[b]);
    }
    if (t_depth[b] > t_depth[a]) {
      lift(&b, t_depth[b] - t_depth[a]);
    }
    if (a == b) {
      return a;
    }
    for (int k = t_maxlift - 1; k >= 0; k--) {
      if (t_par[a][k] != t_par[b][k]) {
        a = t_par[a][k];
        b = t_par[b][k];
      }
    }
    return t_par[a][0];
  }
};

} // namespace heavy_light_decomposition
} // namespace range_queries

// 测试用例，验证实现是否正确
static void test_1() {
  std::cout << "Test 1:\n";

  // 测试数据：5个节点
  int n = 5;
  std::vector<int64_t> node_values = {4, 2, 5, 2, 1};  // 节点值
  std::vector<std::vector<int>> edges = {{1, 2}, {1, 3}, {3, 4}, {3, 5}}; // 树的边
  std::vector<std::vector<int>> queries = {
      {2, 1, 4},  // 查询路径1到4的节点值和
      {1, 3, 2},  // 更新节点3的值为2
      {2, 1, 4},  // 再次查询路径1到4的节点值和
  };
  std::vector<int> expected_result = {11, 8};  // 期望结果
  std::vector<int> code_result;  // 实际计算结果

  range_queries::heavy_light_decomposition::HLD<int64_t> hld(n);
  hld.set_node_val(node_values);  // 设置节点值
  for (int i = 0; i < n - 1; i++) {
    int u = edges[i][0], v = edges[i][1];
    hld.add_edge(u - 1, v - 1);  // 添加边
  }
  hld.init();  // 初始化 HLD 结构
  for (const auto &q : queries) {
    int type = q[0];
    if (type == 1) {  // 更新节点值
      int p = q[1], x = q[2];
      hld.update(p - 1, x);
    } else if (type == 2) {  // 查询路径和
      int a = q[1], b = q[2];
      code_result.push_back(hld.query(a - 1, b - 1));
    } else {
      continue;
    }
  }
  // 比较实际结果与期望结果
  for (int i = 0; i < static_cast<int>(expected_result.size()); i++) {
    assert(expected_result[i] == code_result[i]);
  }
  std::cout << "\nTest 1 passed!\n";
}

