/**
 * @file
 * @brief [不相交联合](https://en.wikipedia.org/wiki/Disjoint_union)
 *
 * @details
 * 不相交联合是一种高效查找图中连通分量的技术。
 *
 * ### 算法
 * 在图中，如果你需要查找连通分量的数量，有两种选择：
 * 1. 深度优先搜索
 * 2. 不相交联合
 * 第一种选择效率较低，而不相交联合是最优的解决方法。
 *
 * @author Unknown author
 * @author [Sagar Pandya](https://github.com/sagarpandyansit)
 */
#include <iostream> /// 用于输入输出操作
#include <set>    /// 用于 std::set
#include <vector> /// 用于 std::vector

/**
 * @namespace graph
 * @brief 图算法
 */
namespace graph {
/**
 * @namespace disjoint_union
 * @brief [不相交联合](https://en.wikipedia.org/wiki/Disjoint_union) 实现的函数
 */
namespace disjoint_union {
uint32_t number_of_nodes = 0;                // 表示节点的数量
std::vector<int64_t> parent{};               // 每个节点的父节点
std::vector<uint32_t> connected_set_size{};  // 每个集合的大小

/**
 * @brief 初始化每个节点为自己的父节点
 * @returns void
 */
void make_set() {
    for (uint32_t i = 1; i <= number_of_nodes; i++) {
        parent[i] = i;  // 每个节点的父节点是自己
        connected_set_size[i] = 1;  // 每个集合的初始大小为1
    }
}

/**
 * @brief 查找某个节点所属的连通分量
 * @param val 需要查找父节点的值
 * @return val 的父节点
 */
int64_t find_set(int64_t val) {
    while (parent[val] != val) {
        parent[val] = parent[parent[val]];  // 路径压缩
        val = parent[val];  // 更新val为其父节点
    }
    return val;  // 返回找到的根节点
}

/**
 * @brief 合并两个连通分量
 * @param node1 第一个节点
 * @param node2 第二个节点
 * @returns void
 */
void union_sets(int64_t node1, int64_t node2) {
    node1 = find_set(node1);  // 查找 node1 的根节点
    node2 = find_set(node2);  // 查找 node2 的根节点

    // 如果两个节点的根节点不同，进行合并
    if (node1 != node2) {
        // 确保 node1 是较大的集合
        if (connected_set_size[node1] < connected_set_size[node2]) {
            std::swap(node1, node2);  // 交换
        }
        parent[node2] = node1;  // 让 node1 成为 node2 的父节点
        connected_set_size[node1] +=
            connected_set_size[node2];  // 更新 node1 的集合大小
    }
}

/**
 * @brief 查找连通分量的总数
 * @return 连通分量的数量
 */
uint32_t no_of_connected_components() {
    std::set<int64_t> temp;  // 临时集合用于计数连通分量
    for (uint32_t i = 1; i <= number_of_nodes; i++) {
        temp.insert(find_set(i));  // 插入每个节点的根节点
    }
    return temp.size();  // 返回临时集合的大小，即连通分量的数量
}
}  // namespace disjoint_union
}  // namespace graph

/**
 * @brief 测试实现
 * @returns void
 */
static void test() {
    namespace dsu = graph::disjoint_union;
    std::cin >> dsu::number_of_nodes;  // 输入节点数量
    dsu::parent.resize(dsu::number_of_nodes + 1);  // 调整 parent 向量大小
    dsu::connected_set_size.resize(dsu::number_of_nodes + 1);  // 调整集合大小向量
    dsu::make_set();  // 初始化每个节点
    uint32_t edges = 0;
    std::cin >> edges;  // 输入边的数量
    while (edges--) {
        int64_t node_a = 0, node_b = 0;
        std::cin >> node_a >> node_b;  // 输入每条边
        dsu::union_sets(node_a, node_b);  // 合并两个节点
    }
    std::cout << dsu::no_of_connected_components() << std::endl;  // 输出连通分量的数量
}

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main() {
    test();  // 执行测试
    return 0;
}
