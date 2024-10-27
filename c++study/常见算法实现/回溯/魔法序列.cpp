
// 魔法方阵：一个n阶魔法方阵是一个n×n的矩阵，包含数字从1到n²，且每行、每列和主对角线
// 的和相等。此外，我们对存在特定大小的魔法方阵的数量感兴趣。有几种有趣的变体。例如，我们可
// 能会要求某些方格中有特定的值（如在类群完成中），并询问魔法方阵是否可以被完成。在
// heterosquare 中，每行、每列和对角线的和都不同。在anti-magic square 中，行、列和对角线
// 的和形成一个连续整数的序列。

// 魔法序列：一个长度为n的魔法序列是一个整数序列Xo...X-1，其值在0到n-1之间，且对于所
// 有的i（从0到n-1），数字i在序列中恰好出现x次。例如，6,2,1,0,0,0,1,0,0,0是一个魔
// 法序列，因为0出现了6次，1出现了两次，等等。

#include <algorithm>  /// 用于 std::count
#include <cassert>    /// 用于 assert
#include <iostream>   /// 用于输入输出操作
#include <list>       /// 用于 std::list
#include <numeric>    /// 用于 std::accumulate
#include <vector>     /// 用于 std::vector

/**
 * @namespace backtracking
 * @brief 回溯算法
 */
namespace backtracking {
/**
 * @namespace magic_sequence
 * @brief [魔法序列](https://www.csplib.org/Problems/prob019/) 的实现函数
 */
namespace magic_sequence {
using sequence_t =
    std::vector<unsigned int>;  ///< 定义序列类型

/**
 * @brief 打印魔法序列
 * @param s 工作序列
 */
void print(const sequence_t& s) {
    for (const auto& item : s) std::cout << item << " ";
    std::cout << std::endl;
}

/**
 * @brief 检查序列是否为魔法序列
 * @param s 工作序列
 * @returns 如果是魔法序列则返回 true
 * @returns 如果不是魔法序列则返回 false
 */
bool is_magic(const sequence_t& s) {
    for (unsigned int i = 0; i < s.size(); i++) {
        // 检查 i 在序列中出现的次数是否等于 s[i]
        if (std::count(s.cbegin(), s.cend(), i) != s[i]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief 子解决方案过滤
 * @param s 工作序列
 * @param depth 当前树深度
 * @returns 如果子解决方案有效则返回 true
 * @returns 如果子解决方案无效则返回 false
 */
bool filtering(const sequence_t& s, unsigned int depth) {
    // 检查当前深度之前的总和是否小于等于序列长度
    return std::accumulate(s.cbegin(), s.cbegin() + depth,
                           static_cast<unsigned int>(0)) <= s.size();
}

/**
 * @brief 解决魔法序列问题
 * @param s 工作序列
 * @param ret 有效魔法序列的列表
 * @param depth 当前树深度
 */
void solve(sequence_t* s, std::list<sequence_t>* ret, unsigned int depth = 0) {
    // 如果当前深度等于序列大小
    if (depth == s->size()) {
        // 检查序列是否为魔法序列
        if (is_magic(*s)) {
            ret->push_back(*s);  // 将有效的魔法序列添加到结果列表中
        }
    } else {
        // 遍历可能的值
        for (unsigned int i = 0; i < s->size(); i++) {
            (*s)[depth] = i;  // 在当前深度设置值
            // 过滤有效的子解决方案
            if (filtering(*s, depth + 1)) {
                solve(s, ret, depth + 1);  // 递归调用解决方案
            }
        }
    }
}

}  // namespace magic_sequence
}  // namespace backtracking

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    // 测试有效的魔法序列
    backtracking::magic_sequence::sequence_t s_magic = {6, 2, 1, 0, 0,
                                                        0, 1, 0, 0, 0};
    assert(backtracking::magic_sequence::is_magic(s_magic));

    // 测试无效的魔法序列
    backtracking::magic_sequence::sequence_t s_not_magic = {5, 2, 1, 0, 0,
                                                            0, 1, 0, 0, 0};
    assert(!backtracking::magic_sequence::is_magic(s_not_magic));
}

/**
 * @brief 主函数
 * @returns 0 正常退出
 */
int main() {
    test();  // 运行自测实现

    // 解决大小从 2 到 11 的魔法序列并打印解决方案
    for (unsigned int i = 2; i < 12; i++) {
        std::cout << "Solution for n = " << i << std::endl;
        // 有效魔法序列列表
        std::list<backtracking::magic_sequence::sequence_t> list_of_solutions;
        // 初始化序列
        backtracking::magic_sequence::sequence_t s1(i, i);
        // 启动解决问题
        backtracking::magic_sequence::solve(&s1, &list_of_solutions);
        // 打印解决方案
        for (const auto& item : list_of_solutions) {
            backtracking::magic_sequence::print(item);
        }
    }
    return 0;
}
