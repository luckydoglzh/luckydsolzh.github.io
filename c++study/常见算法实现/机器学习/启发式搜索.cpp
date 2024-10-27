/**  
 * @brief  
 * [A* search algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm)  
 * @details  
 * A* 是一种启发式搜索算法，或称为最佳优先搜索，意味着它  
 * 以加权图为基础：从图的特定起始节点（初始状态）出发，旨在寻找  
 * 到给定目标节点的路径，其代价最小（行驶距离最短、时间最短等）。  
 * 它通过维护一棵从起始节点发出的路径树，  
 * 一次扩展这些路径，直到达到最终状态。  
 * 加权边（或成本）根据两个因素进行评估：G 分数  
 * （从起始节点或初始状态到当前状态所需的成本）和 H 分数  
 * （从当前状态到最终状态所需的成本）。然后，F(state) 的评估为：  
 * F(state) = G(state) + H(state)。  
 *  
 * 为了解决给定搜索中最短成本或路径的可能性，  
 * 需要检查具有最小 F(state) 值的状态。  
 * @author [Ashish Daulatabad](https://github.com/AshishYUO)  
 */  
#include <algorithm>   /// for `std::reverse` function  
#include <array>       /// for `std::array`，表示 `EightPuzzle` 板  
#include <cassert>     /// for `assert`  
#include <functional>  /// for `std::function` STL  
#include <iostream>    /// for IO operations  
#include <map>         /// for `std::map` STL  
#include <memory>      /// for `std::shared_ptr`  
#include <set>         /// for `std::set` STL  
#include <vector>      /// for `std::vector` STL  

/**  
 * @namespace machine_learning  
 * @brief 机器学习算法  
 */  
namespace machine_learning {  

/**  
 * @namespace aystar_search  
 * @brief [A*搜索](https://en.wikipedia.org/wiki/A*_search_algorithm) 实现的函数。  
 */  
namespace aystar_search {  

/**  
 * @class EightPuzzle  
 * @brief 定义 [八数码/15-拼图](https://en.wikipedia.org/wiki/15_puzzle) 游戏的类  
 * @details  
 * 一个著名的 3 x 3 拼图，形式为  
 * `  
 * 1   2   3  
 * 4   5   6  
 * 7   8   0  
 * `  
 * 其中 `0` 代表拼图中的空格。  
 * 给定任意随机状态，目标是实现上述配置  
 * （或如果可能的话实现任何其他配置）  
 * @tparam N 方形拼图的大小，默认设置为 3（因为它是八数码拼图）  
 */  
template <size_t N = 3> class EightPuzzle {     
    std::array<std::array<uint32_t, N>, N>         
    board;  /// N x N 数组来存储拼图的当前状态。      

    std::vector<std::pair<int8_t, int8_t>> moves = {         
        {0, 1},         
        {1, 0},         
        {0, -1},         
        {-1, 0}};  /// 帮助数组以评估从当前状态生成的下一个状态。     

    /**      
     * @brief 找到拼图中的空格（在这种情况下为零）      
     * @returns 一对表示距离顶部和右侧的整数      
     * 如果未找到则返回 -1, -1      
     */     
    std::pair<uint32_t, uint32_t> find_zero() {         
        for (size_t i = 0; i < N; ++i) {             
            for (size_t j = 0; j < N; ++j) {                 
                if (!board[i][j]) {                     
                    return {i, j};                 
                }             
            }         
        }         
        return {-1, -1};     
    }     

    /**      
     * @brief 检查索引值是否在拼图区域内      
     * @param value 当前棋盘的索引      
     * @returns 如果索引在棋盘内，则返回 `true`，否则返回 `false`      
     */     
    inline bool in_range(const uint32_t value) const { return value < N; }   

public:     
    /**      
     * @brief 从右侧 i 单位和从左侧 j 单位获取值      
     * @param i 表示第 i 行的整数      
     * @param j 表示第 j 列的整数      
     * @returns 非负整数，表示第 i 行和第 j 列的值      
     * 如果无效则返回 -1      
     */     
    uint32_t get(size_t i, size_t j) const {         
        if (in_range(i) && in_range(j)) {             
            return board[i][j];         
        }         
        return -1;     
    }     

    /**      
     * @brief 返回棋盘的当前状态      
     */     
    std::array<std::array<uint32_t, N>, N> get_state() { return board; }      

    /**      
     * @brief 返回八数码拼图的大小（行/列的数量）      
     * @return N，拼图的大小。      
     */     
    inline size_t get_size() const { return N; }     

    /**      
     * @brief 八数码拼图的默认构造函数      
     */     
    EightPuzzle() {         
        for (size_t i = 0; i < N; ++i) {             
            for (size_t j = 0; j < N; ++j) {                 
                board[i][j] = ((i * 3 + j + 1) % (N * N));             
            }         
        }     
    }     

    /**      
     * @brief 八数码拼图的参数化构造函数      
     * @param init 二维数组，表示拼图配置      
     */     
    explicit EightPuzzle(const std::array<std::array<uint32_t, N>, N> &init)         
        : board(init) {}      

    /**      
     * @brief 复制构造函数      
     * @param A 八数码拼图的引用      
     */     
    EightPuzzle(const EightPuzzle<N> &A) : board(A.board) {}      

    /**      
     * @brief 移动构造函数      
     * @param A 八数码拼图的引用      
     */     
    EightPuzzle(const EightPuzzle<N> &&A) noexcept         
        : board(std::move(A.board)) {}     

    /**      
     * @brief 八数码拼图的析构函数      
     */     
    ~EightPuzzle() = default;      

    /**      
     * @brief 复制赋值运算符      
     * @param A 八数码拼图的引用      
     */     
    EightPuzzle &operator=(const EightPuzzle &A) {         
        board = A.board;         
        return *this;     
    }      

    /**      
     * @brief 移动赋值运算符      
     * @param A 八数码拼图的引用      
     */     
    EightPuzzle &operator=(EightPuzzle &&A) noexcept {         
        board = std::move(A.board);         
        return *this;     
    }      

    /**      
     * @brief 查找处理所有可能移动后生成的所有可能状态，  
     * 给定拼图的当前状态      
     * @returns 包含所有可能下一个移动的向量列表      
     * @note 该实现是创建 A* 搜索的必需条件      
     */     
    std::vector<EightPuzzle<N>> generate_possible_moves() {         
        auto zero_pos = find_zero();         
        // 存储当前状态的所有可能状态的向量         
        std::vector<EightPuzzle<N>> NewStates;         
        for (auto &move : moves) {             
            if (in_range(zero_pos.first + move.first) &&                 
                in_range(zero_pos.second + move.second)) {                 
                // 用可能的移动进行交换                 
                std::array<std::array<uint32_t, N>, N> new_config = board;                 
                std::swap(new_config[zero_pos.first][zero_pos.second],                           
                          new_config[zero_pos.first + move.first]                                     
                          [zero_pos.second + move.second]);                 
                EightPuzzle<N> new_state(new_config);                 
                // 存储新状态并计算启发值和深度                 
                NewStates.emplace_back(new_state);             
            }         
        }         
        return NewStates;     
    }     

    /**      
     * @brief 检查两个棋盘是否相等      
     * @returns 如果 check.state 等于 `this->state`，则返回 `true`，否则返回 `false`      
     */     
    bool operator==(const EightPuzzle<N> &check) const {         
        if (check.get_size() != N) {             
            return false;         
        }         
        for (size_t i = 0; i < N; ++i) {             
            for (size_t j = 0; j < N; ++j) {                 
                if (check.get(i, j) != get(i, j)) {                     
                    return false;                 
                }             
            }         
        }         
        return true;     
    }      

    /**      
     * @brief 检查两个棋盘是否不相等      
     * @returns 如果不相等，则返回 `true`，否则返回 `false`      
     */     
    bool operator!=(const EightPuzzle<N> &check) const { return !(*this == check); }      

    /**      
     * @brief 计算八数码拼图的 G 评分      
     * @param goal_goal 目标状态      
     * @returns uint32_t，G 评分      
     */     
    uint32_t calculate_g(const EightPuzzle<N> &goal_goal) const {         
        return 0;  // 在这里应实现计算 G 评分的逻辑     
    }      

    /**      
     * @brief 计算八数码拼图的 H 评分      
     * @param goal_goal 目标状态      
     * @returns uint32_t，H 评分      
     */     
    uint32_t calculate_h(const EightPuzzle<N> &goal_goal) const {         
        return 0;  // 在这里应实现计算 H 评分的逻辑     
    }      

    /**      
     * @brief 计算八数码拼图的 F 评分      
     * @param goal_goal 目标状态      
     * @returns uint32_t，F 评分      
     */     
    uint32_t calculate_f(const EightPuzzle<N> &goal_goal) const {         
        return calculate_g(goal_goal) + calculate_h(goal_goal);     
    }     
};  /// @class结束  
}  /// @namespace结束  
}  /// @namespace结束  
/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    // 为简化命名
    using matrix3 = std::array<std::array<uint32_t, 3>, 3>;  // 定义 3x3 矩阵
    using row3 = std::array<uint32_t, 3>;                     // 定义 3 元数组
    using matrix4 = std::array<std::array<uint32_t, 4>, 4>;  // 定义 4x4 矩阵
    using row4 = std::array<uint32_t, 4>;                     // 定义 4 元数组

    // 第 1 个测试：对简单的八数码问题进行 A* 搜索
    matrix3 puzzle;  // 存储拼图的初始状态
    puzzle[0] = row3({0, 2, 3});
    puzzle[1] = row3({1, 5, 6});
    puzzle[2] = row3({4, 7, 8});

    matrix3 ideal;  // 存储拼图的目标状态
    ideal[0] = row3({1, 2, 3});
    ideal[1] = row3({4, 5, 6});
    ideal[2] = row3({7, 8, 0});

    /*
     * 启发式函数：曼哈顿距离
     */
    auto manhattan_distance =
        [](const machine_learning::aystar_search::EightPuzzle<> &first,
           const machine_learning::aystar_search::EightPuzzle<> &second) {
            uint32_t ret = 0;  // 存储曼哈顿距离的变量
            for (size_t i = 0; i < first.get_size(); ++i) {
                for (size_t j = 0; j < first.get_size(); ++j) {
                    uint32_t find = first.get(i, j);  // 获取当前值
                    size_t m = first.get_size(), n = first.get_size();
                    for (size_t k = 0; k < second.get_size(); ++k) {
                        for (size_t l = 0; l < second.get_size(); ++l) {
                            if (find == second.get(k, l)) {  // 找到目标值的位置
                                std::tie(m, n) = std::make_pair(k, l);
                                break;
                            }
                        }
                        if (m != first.get_size()) {
                            break;  // 找到后跳出循环
                        }
                    }
                    if (m != first.get_size()) {
                        // 计算曼哈顿距离
                        ret += (std::max(m, i) - std::min(m, i)) +
                               (std::max(n, j) - std::min(n, j));
                    }
                }
            }
            return ret;  // 返回计算出的曼哈顿距离
        };

    machine_learning::aystar_search::EightPuzzle<> Puzzle(puzzle);  // 创建当前状态的八数码拼图对象
    machine_learning::aystar_search::EightPuzzle<> Ideal(ideal);    // 创建目标状态的八数码拼图对象
    machine_learning::aystar_search::AyStarSearch<
        machine_learning::aystar_search::EightPuzzle<3>>
        search(Puzzle, Ideal);  /// 搜索对象

    std::vector<matrix3> answer;  /// 存储有效答案的数组

    // 添加预期解决方案
    answer.push_back(
        matrix3({row3({0, 2, 3}), row3({1, 5, 6}), row3({4, 7, 8})}));
    answer.push_back(
        matrix3({row3({1, 2, 3}), row3({0, 5, 6}), row3({4, 7, 8})}));
    answer.push_back(
        matrix3({row3({1, 2, 3}), row3({4, 5, 6}), row3({0, 7, 8})}));
    answer.push_back(
        matrix3({row3({1, 2, 3}), row3({4, 5, 6}), row3({7, 0, 8})}));
    answer.push_back(
        matrix3({row3({1, 2, 3}), row3({4, 5, 6}), row3({7, 8, 0})}));

    auto Solution = search.a_star_search(manhattan_distance);  // 执行 A* 搜索
    std::cout << Solution.size() << std::endl;  // 输出解决方案的大小

    assert(Solution.size() == answer.size());  // 断言解决方案的大小与预期相等

    uint32_t i = 0;  // 用于索引的变量
    for (auto it = Solution.rbegin(); it != Solution.rend(); ++it) {
        assert(it->get_state() == answer[i]);  // 检查每一步的状态是否正确
        ++i;
    }

    // 第 2 个测试：对复杂的八数码问题进行 A* 搜索
    // 初始状态
    puzzle[0] = row3({5, 7, 3});
    puzzle[1] = row3({2, 0, 6});
    puzzle[2] = row3({1, 4, 8});
    // 目标状态
    ideal[0] = row3({1, 2, 3});
    ideal[1] = row3({4, 5, 6});
    ideal[2] = row3({7, 8, 0});

    Puzzle = machine_learning::aystar_search::EightPuzzle<>(puzzle);  // 更新当前状态
    Ideal = machine_learning::aystar_search::EightPuzzle<>(ideal);    // 更新目标状态

    // 初始化搜索对象
    search = machine_learning::aystar_search::AyStarSearch<
        machine_learning::aystar_search::EightPuzzle<3>>(Puzzle, Ideal);

    Solution = search.a_star_search(manhattan_distance);  // 执行 A* 搜索
    std::cout << Solution.size() << std::endl;  // 输出解决方案的大小

    // 静态断言由于解决方案较大
    assert(13 == Solution.size());
    // 检查最终状态是否等于预期
    assert(Solution[0].get_state() == ideal);
    for (auto it = Solution.rbegin(); it != Solution.rend(); ++it) {
        std::cout << *it << std::endl;  // 输出解决方案的每一步
    }

    // 第 3 个测试：对 15-Puzzle 进行 A* 搜索
    // 拼图的初始状态
    matrix4 puzzle2;
    puzzle2[0] = row4({10, 1, 6, 2});
    puzzle2[1] = row4({5, 8, 4, 3});
    puzzle2[2] = row4({13, 0, 7, 11});
    puzzle2[3] = row4({14, 9, 15, 12});
    // 拼图的目标状态
    matrix4 ideal2;
    ideal2[0] = row4({1, 2, 3, 4});
    ideal2[1] = row4({5, 6, 7, 8});
    ideal2[2] = row4({9, 10, 11, 12});
    ideal2[3] = row4({13, 14, 15, 0});

    // 为 A* 实例化状态，初始状态和目标状态
    machine_learning::aystar_search::EightPuzzle<4> Puzzle2(puzzle2),
        Ideal2(ideal2);
    // 初始化搜索对象
    machine_learning::aystar_search::AyStarSearch<
        machine_learning::aystar_search::EightPuzzle<4>>
        search2(Puzzle2, Ideal2);
    /**
     * 启发式函数：曼哈顿距离
     */
    auto manhattan_distance2 =
        [](const machine_learning::aystar_search::EightPuzzle<4> &first,
           const machine_learning::aystar_search::EightPuzzle<4> &second) {
            uint32_t ret = 0;  // 存储曼哈顿距离的变量
            for (size_t i = 0; i < first.get_size(); ++i) {
                for (size_t j = 0; j < first.get_size(); ++j) {
                    uint32_t find = first.get(i, j);  // 获取当前值
                    size_t m = first.get_size(), n = first.get_size();
                    for (size_t k = 0; k < second.get_size(); ++k) {
                        for (size_t l = 0; l < second.get_size(); ++l) {
                            if (find == second.get(k, l)) {  // 找到目标值的位置
                                std::tie(m, n) = std::make_pair(k, l);
                                break;
                            }
                        }
                        if (m != first.get_size()) {
                            break;  // 找到后跳出循环
                        }
                    }
                    if (m != first.get_size()) {
                        // 计算曼哈顿距离
                        ret += (std::max(m, i) - std::min(m, i)) +
                               (std::max(n, j) - std::min(n, j));
                    }
                }
            }
            return ret;  // 返回计算出的曼哈顿距离
        };

    auto sol2 = search2.a_star_search(manhattan_distance2);  // 执行 A* 搜索
    std::cout << sol2.size() << std::endl;  // 输出解决方案的大小

    // 静态断言由于解决方案较大
    assert(24 == sol2.size());
    // 检查最终状态是否等于预期
    assert(sol2[0].get_state() == ideal2);

    for (auto it = sol2.rbegin(); it != sol2.rend(); ++it) {
        std::cout << *it << std::endl;  // 输出解决方案的每一步
    }
}

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main() {
    test();  // 运行自测实现
    return 0;
}
