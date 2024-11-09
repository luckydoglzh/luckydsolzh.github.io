/**
 * @file sparse_table.cpp
 * @brief 实现了 [Sparse Table](https://en.wikipedia.org/wiki/Range_minimum_query) 数据结构
 *
 * @details
 * Sparse Table 是一种可以快速回答区间查询的数据结构，特别适用于求区间最小值或最大值。
 * 对于区间最小值（或等效的区间最大值）查询，它可以在 O(1) 时间内计算出答案。
 * 对于其他类型的区间查询，Sparse Table 可以在 O(logn) 时间内计算出答案。
 *
 * * 时间复杂度：
 *   * 构建：O(NlogN)
 *   * 区间查询：O(1)
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/**
 * @namespace range_queries
 * @brief 范围查询算法
 */
namespace range_queries {
/**
 * @namespace sparse_table
 * @brief 使用 Sparse Table 进行范围查询
 */
namespace sparse_table {

/**
 * 该函数预计算了日志表，用于后续的计算。
 * @param A 输入数组的大小
 * @return 返回相应的日志表
 */
template <typename T>
std::vector<T> computeLogs(const std::vector<T>& A) {
    int n = A.size();
    std::vector<T> logs(n);
    logs[1] = 0;  // 初始化 logs[1] = 0
    // 计算从 2 开始的每个数的 log 值
    for (int i = 2; i < n; i++) {
        logs[i] = logs[i / 2] + 1;  // log(i) = log(i / 2) + 1
    }
    return logs;
}

/**
 * 该函数构建了主数据结构 Sparse Table。
 * @param A 输入数组
 * @param logs 事先计算好的日志表
 * @return 返回构建好的 Sparse Table 数据结构
 */
template <typename T>
std::vector<std::vector<T> > buildTable(const std::vector<T>& A,
                                        const std::vector<T>& logs) {
    int n = A.size();
    std::vector<std::vector<T> > table(20, std::vector<T>(n + 5, 0));
    int curLen = 0;
    // 对于每个可能的区间长度 1, 2, 4, 8, ..., 进行处理
    for (int i = 0; i <= logs[n]; i++) {
        curLen = 1 << i;  // 当前长度是 2^i
        for (int j = 0; j + curLen < n; j++) {
            if (curLen == 1) {
                table[i][j] = A[j];  // 只有一个元素时，直接赋值
            } else {
                // 否则，取左半部分和右半部分的最小值
                table[i][j] =
                    std::min(table[i - 1][j], table[i - 1][j + curLen / 2]);
            }
        }
    }
    return table;
}

/**
 * 该函数用于查询区间 [beg, end] 的最小值。
 * @param beg 查询范围的起始索引
 * @param end 查询范围的结束索引
 * @param logs 事先计算好的日志表
 * @param table Sparse Table 数据结构
 * @return 返回区间 [beg, end] 的最小值
 */
template <typename T>
int getMinimum(int beg, int end, const std::vector<T>& logs,
               const std::vector<std::vector<T> >& table) {
    int p = logs[end - beg + 1];  // 计算区间长度的日志值
    int pLen = 1 << p;  // 计算区间长度的实际值
    return std::min(table[p][beg], table[p][end - pLen + 1]);  // 返回最小值
}
}  // namespace sparse_table
}  // namespace range_queries

/**
 * 主函数
 */
int main() {
    // 初始化输入数组 A
    std::vector<int> A{1, 2, 0, 3, 9};
    
    // 计算日志表
    std::vector<int> logs = range_queries::sparse_table::computeLogs(A);
    
    // 构建 Sparse Table 数据结构
    std::vector<std::vector<int> > table =
        range_queries::sparse_table::buildTable(A, logs);
    
    // 进行一些查询，并通过断言检查结果
    assert(range_queries::sparse_table::getMinimum(0, 0, logs, table) == 1);  // 查询区间 [0, 0] 的最小值
    assert(range_queries::sparse_table::getMinimum(0, 4, logs, table) == 0);  // 查询区间 [0, 4] 的最小值
    assert(range_queries::sparse_table::getMinimum(2, 4, logs, table) == 0);  // 查询区间 [2, 4] 的最小值

    return 0;
}
