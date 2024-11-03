/**
 * @file cycle_check_directed_graph.cpp
 *
 * @brief 使用 BFS 和 DFS 算法检查有向图中的循环。
 *
 * @author [Anmol3299](mailto:mittalanmol22@gmail.com)
 *
 */

#include <iostream>     // 用于 std::cout
#include <map>          // 用于 std::map
#include <queue>        // 用于 std::queue
#include <stdexcept>    // 用于抛出错误
#include <type_traits>  // 用于 std::remove_reference
#include <utility>      // 用于 std::move
#include <vector>       // 用于 std::vector

/**
 * 表示有向图的非加权边。
 *
 * 边的源顶点标记为 "src"，目标顶点标记为 "dest"。
 */
struct Edge {
    unsigned int src;  // 源顶点
    unsigned int dest; // 目标顶点

    Edge() = delete; // 禁止默认构造函数
    ~Edge() = default; // 默认析构函数
    Edge(Edge&&) = default; // 移动构造函数
    Edge& operator=(Edge&&) = default; // 移动赋值运算符
    Edge(Edge const&) = default; // 拷贝构造函数
    Edge& operator=(Edge const&) = default; // 拷贝赋值运算符

    /** 设置顶点的源和目标。
     *
     * @param source 是边的源顶点。
     * @param destination 是边的目标顶点。
     */
    Edge(unsigned int source, unsigned int destination)
        : src(source), dest(destination) {}
};

using AdjList = std::map<unsigned int, std::vector<unsigned int>>;

/**
 * 图类的实现。
 *
 * 图将使用邻接表表示。该类包含两个数据成员 "m_vertices" 和 "m_adjList"，分别用于表示图的顶点数量和邻接表。
 * 顶点标记为 0 到 (m_vertices - 1)。
 */
class Graph {
 public:
    Graph() : m_adjList({}) {}
    ~Graph() = default;
    Graph(Graph&&) = default;
    Graph& operator=(Graph&&) = default;
    Graph(Graph const&) = default;
    Graph& operator=(Graph const&) = default;

    /** 从顶点和邻接表创建图。
     *
     * @param vertices 指定图的顶点数量。
     * @param adjList 是图的邻接表表示。
     */
    Graph(unsigned int vertices, AdjList adjList)
        : m_vertices(vertices), m_adjList(std::move(adjList)) {}

    /** 从顶点和邻接表创建图。
     *
     * @param vertices 指定图的顶点数量。
     * @param adjList 是图的邻接表表示。
     */
    Graph(unsigned int vertices, AdjList&& adjList)
        : m_vertices(vertices), m_adjList(std::move(adjList)) {}

    /** 从顶点和边集合创建图。
     *
     * 图的邻接表将根据边集合创建。如果任何边的源或目标值大于或等于顶点数量，则会抛出范围错误。
     *
     * @param vertices 指定图的顶点数量。
     * @param edges 是边的向量。
     */
    Graph(unsigned int vertices, std::vector<Edge> const& edges)
        : m_vertices(vertices) {
        for (auto const& edge : edges) {
            if (edge.src >= vertices || edge.dest >= vertices) {
                throw std::range_error(
                    "Either src or dest of edge out of range");
            }
            m_adjList[edge.src].emplace_back(edge.dest);
        }
    }

    /** 返回邻接表的常量引用。
     *
     * @return 邻接表的常量引用
     */
    std::remove_reference<AdjList>::type const& getAdjList() const {
        return m_adjList;
    }

    /**
     * @return 图中的顶点数量。
     */
    unsigned int getVertices() const { return m_vertices; }

    /** 在图中添加顶点。
     *
     * @param num 是要添加的顶点数量。默认添加 1 个顶点。
     *
     */
    void addVertices(unsigned int num = 1) { m_vertices += num; }

    /** 在图中添加一条边。
     *
     * @param edge 需要添加的边。
     */
    void addEdge(Edge const& edge) {
        if (edge.src >= m_vertices || edge.dest >= m_vertices) {
            throw std::range_error("Either src or dest of edge out of range");
        }
        m_adjList[edge.src].emplace_back(edge.dest);
    }

    /** 在图中添加一条边。
     *
     * @param source 是边的源顶点。
     * @param destination 是边的目标顶点。
     */
    void addEdge(unsigned int source, unsigned int destination) {
        if (source >= m_vertices || destination >= m_vertices) {
            throw std::range_error(
                "Either source or destination of edge out of range");
        }
        m_adjList[source].emplace_back(destination);
    }

 private:
    unsigned int m_vertices = 0; // 顶点数量
    AdjList m_adjList; // 邻接表
};

/**
 * 检查有向图是否有循环。
 *
 * 该类提供 2 个方法来检查有向图中的循环：
 * isCyclicDFS 和 isCyclicBFS。
 *
 * - isCyclicDFS 使用 DFS 遍历方法检查图中的循环。
 * - isCyclicBFS 使用 BFS 遍历方法检查图中的循环。
 */
class CycleCheck {
 private:
    enum nodeStates : uint8_t { not_visited = 0, in_stack, visited };

    /** "isCyclicDFS" 的辅助函数。
     *
     * @param adjList 是某个图的邻接表表示。
     * @param state 是图中节点的状态。
     * @param node 是正在评估的节点。
     *
     * @return 如果图中有循环，则返回 true，否则返回 false。
     */
    static bool isCyclicDFSHelper(AdjList const& adjList,
                                  std::vector<nodeStates>* state,
                                  unsigned int node) {
        // 将节点标记为 "in_stack" 状态。
        (*state)[node] = in_stack;

        // 如果节点有子节点，则递归访问所有子节点。
        auto const it = adjList.find(node);
        if (it != adjList.end()) {
            for (auto child : it->second) {
                // 如果子节点状态为 "not_visited"，则评估该子节点是否存在循环。
                auto state_of_child = (*state)[child];
                if (state_of_child == not_visited) {
                    if (isCyclicDFSHelper(adjList, state, child)) {
                        return true;
                    }
                } else if (state_of_child == in_stack) {
                    // 如果子节点为 "in_stack"，则表示图中存在循环。返回 true。
                    return true;
                }
            }
        }

        // 当前节点已被评估，且没有循环。标记当前节点为 "visited"。
        (*state)[node] = visited;
        // 返回当前节点没有导致循环的结果。
        return false;
    }

 public:
    /** 驱动函数检查图是否有循环。
     *
     * 此函数使用 DFS 检查图中的循环。
     *
     * @param graph 需要评估是否存在循环的图。
     * @return 如果检测到循环，则返回 true，否则返回 false。
     */
    static bool isCyclicDFS(Graph const& graph) {
        auto vertices = graph.getVertices();

        /** 节点的状态。
         *
         * 它是一个 "nodeStates" 的向量，表示节点的状态。
         * 它只能取三种值：“not_visited”、“in_stack”和“visited”。
         *
         * 初始时，所有节点处于 "not_visited" 状态。
         */
        std::vector<nodeStates> state(vertices, not_visited);

        // 开始访问每个节点。
        for (unsigned int node = 0; node < vertices; node++) {
            // 如果节点未被访问，才检查是否存在循环。
            // 已访问的节点不需要再检查。
            if (state[node] == not_visited) {
                // 检查是否存在循环。
                if (isCyclicDFSHelper(graph.getAdjList(), &state, node)) {
                    return true;
                }
            }
        }

        // 所有节点已安全遍历，表示图中没有循环。返回 false。
        return false;
    }

    /** 检查图是否有循环。
     *
     * 此函数使用 BFS 检查图是否为循环。
     *
     * @param graph 需要评估是否存在循环的图。
     * @return 如果检测到循环，则返回 true，否则返回 false。
     */
    static bool isCyclicBFS(Graph const& graph) {
        auto graphAjdList = graph.getAdjList();
        auto vertices = graph.getVertices();

        std::vector<unsigned int> indegree(vertices, 0);
        // 计算入度，即节点的入边数量。
        for (auto const& list : graphAjdList) {
            auto children = list.second;
            for (auto const& child : children) {
                indegree[child]++;
            }
        }

        std::queue<unsigned int> can_be_solved;
        for (unsigned int node = 0; node < vertices; node++) {
            // 如果节点没有入边，则该节点肯定不会导致循环，可以安全访问。
            if (!indegree[node]) {
                can_be_solved.emplace(node);
            }
        }

        // 需要遍历的节点数量。
        auto remain = vertices;
        // 当有可以安全访问的节点时。
        while (!can_be_solved.empty()) {
            auto solved = can_be_solved.front();
            // 访问节点。
            can_be_solved.pop();
            // 减少需要遍历的节点数量。
            remain--;

            // 访问已访问节点的所有子节点。
            auto it = graphAjdList.find(solved);
            if (it != graphAjdList.end()) {
                for (auto child : it->second) {
                    // 检查是否可以安全访问子节点。
                    if (--indegree[child] == 0) {
                        // 如果节点可以安全访问，则将其添加到访问队列。
                        can_be_solved.emplace(child);
                    }
                }
            }
        }

        // 如果还有无法访问的节点，则表示存在循环，返回 true，否则返回 false。
        return !(remain == 0);
    }
};

/**
 * 主函数。
 */
int main() {
    // 实例化图。
    Graph g(7, std::vector<Edge>{{0, 1}, {1, 2}, {2, 0}, {2, 5}, {3, 5}});
    // 使用 BFS 方法检查循环。
    std::cout << CycleCheck::isCyclicBFS(g) << '\n';

    // 使用 DFS 方法检查循环。
    std::cout << CycleCheck::isCyclicDFS(g) << '\n';
    return 0;
}
