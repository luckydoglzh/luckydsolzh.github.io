/**
 * @file
 * @brief [旅行商问题]
 * (https://en.wikipedia.org/wiki/Travelling_salesman_problem) 的实现
 *
 * @author [Mayank Mamgain](http://github.com/Mayank17M)
 *
 * @details
 * 旅行商问题的提问是：
 * 给定一组城市及每对城市之间的距离，什么是
 * 最短的可能路径，能够访问每个城市一次并返回到
 * 起始城市？
 * TSP 可以被建模为一个无向加权图，其中城市是
 * 图的顶点，路径是图的边，路径的距离是边的
 * 权重。它是一个最小化问题，要求在访问
 * 每个其他顶点恰好一次后，从指定的顶点
 * 开始和结束。
 * 这是该问题的简单实现。
 */

#include <algorithm>  /// 用于 std::min
#include <cassert>    /// 用于 assert
#include <iostream>   /// 用于输入输出操作
#include <limits>     /// 用于整数类型的极限
#include <vector>     /// 用于 std::vector

/**
 * @namespace graph
 * @brief 图算法
 */
namespace graph {
/**
 * @brief 函数计算从源点开始覆盖所有城市的最小路径距离。
 *
 * @param cities 城市的矩阵表示
 * @param src 销售员的起始点
 * @param V 图中顶点的数量
 *
 */
int TravellingSalesmanProblem(std::vector<std::vector<uint32_t>> *cities,
                              int32_t src, uint32_t V) {
    //// vtx 存储图的顶点
    std::vector<uint32_t> vtx;
    for (uint32_t i = 0; i < V; i++) {
        if (i != src) {
            vtx.push_back(i); // 将非源点的城市加入 vtx
        }
    }

    //// 存储最小权重哈密尔顿回路。
    int32_t min_path = 2147483647; // 初始化最小路径为一个很大的值
    do {
        //// 存储当前路径权重（成本）
        int32_t curr_weight = 0;

        //// 计算当前路径的权重
        int k = src; // 从源点开始
        for (int i : vtx) {
            curr_weight += (*cities)[k][i]; // 累加路径上的权重
            k = i; // 移动到下一个城市
        }
        curr_weight += (*cities)[k][src]; // 回到源点

        //// 更新最小值
        min_path = std::min(min_path, curr_weight); // 更新最小路径

    } while (next_permutation(vtx.begin(), vtx.end())); // 生成下一个排列

    return min_path; // 返回最小路径
}
}  // namespace graph

/**
 * @brief 自我测试实现
 * @returns void
 */
static void tests() {
    std::cout << "开始预定义测试..." << std::endl;
    std::cout << "开始测试 1..." << std::endl;
    std::vector<std::vector<uint32_t>> cities = {
        {0, 20, 42, 35}, {20, 0, 30, 34}, {42, 30, 0, 12}, {35, 34, 12, 0}};
    uint32_t V = cities.size();
    assert(graph::TravellingSalesmanProblem(&cities, 0, V) == 97); // 验证结果
    std::cout << "第 1 个测试通过..." << std::endl;

    std::cout << "开始测试 2..." << std::endl;
    cities = {{0, 5, 10, 15}, {5, 0, 20, 30}, {10, 20, 0, 35}, {15, 30, 35, 0}};
    V = cities.size();
    assert(graph::TravellingSalesmanProblem(&cities, 0, V) == 75); // 验证结果
    std::cout << "第 2 个测试通过..." << std::endl;

    std::cout << "开始测试 3..." << std::endl;
    cities = {
        {0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
    V = cities.size();
    assert(graph::TravellingSalesmanProblem(&cities, 0, V) == 80); // 验证结果
    std::cout << "第 3 个测试通过..." << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 正常退出
 */
int main() {
    tests();  // 运行自我测试
    std::vector<std::vector<uint32_t>> cities = {
        {0, 5, 10, 15}, {5, 0, 20, 30}, {10, 20, 0, 35}, {15, 30, 35, 0}};
    uint32_t V = cities.size();
    std::cout << graph::TravellingSalesmanProblem(&cities, 0, V) << std::endl; // 输出结果
    return 0;
}
