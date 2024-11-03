/****************************************************************************** 
 * @file
 * @brief 使用 [Graham Scan](https://en.wikipedia.org/wiki/Graham_scan) 实现的 [凸包](https://en.wikipedia.org/wiki/Convex_hull)
 * @details
 * 在几何学中，凸包或凸包闭包是包含一个形状的最小凸集。凸包可以定义为包含给定子集的所有凸集的交集，或等效地定义为子集中所有点的凸组合的集合。对于平面上的一个有界子集，凸包可以想象成一个用橡皮筋围绕子集拉伸而成的形状。
 *
 * Jarvis 算法的最坏时间复杂度是 O(n^2)。使用 Graham 扫描算法，我们可以在 O(nLogn) 时间内找到凸包。
 *
 * ### 实现
 *
 * 排序点
 * 我们首先找到最底部的点。想法是通过根据最底部的点对点进行排序来预处理点。一旦点被排序，它们就形成了一条简单的封闭路径。
 * 排序的标准是使用方向来比较角度，而不实际计算它们（请参见下面的 compare() 函数），因为计算实际角度是低效的，因为三角函数不易评估。
 *
 * 接受或拒绝点
 * 一旦我们有了封闭路径，下一步是遍历路径并使用方向移除该路径上的凹点。排序数组中的前两个点始终是凸包的一部分。对于剩余的点，我们跟踪最近的三个点，并找到它们形成的角度。设三个点为 prev(p)、curr(c) 和 next(n)。如果这些点（按相同顺序考虑）的方向不是逆时针方向，我们将丢弃 c，否则我们保留它。
 *
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 *
 *******************************************************************************/
#include <algorithm>  /// 用于 std::swap
#include <cstdlib>    /// 用于数学和数据类型转换
#include <iostream>   /// 用于输入输出操作
#include <stack>      /// 用于 std::stack
#include <vector>     /// 用于 std::vector

/****************************************************************************** 
 * @namespace geometry
 * @brief 几何算法
 *******************************************************************************/
namespace geometry {

/****************************************************************************** 
 * @namespace graham scan
 * @brief 凸包算法
 *******************************************************************************/
namespace grahamscan {

/****************************************************************************** 
 * @struct Point
 * @brief 坐标的 X 和 Y 值。
 *******************************************************************************/
struct Point {
    int x, y;
};

// 全局点，用于根据第一个点排序
Point p0;

/****************************************************************************** 
 * @brief 实用函数，用于查找栈中的次顶点。
 * @param S 用于处理的栈。
 * @returns @param Point 点的坐标 <int, int>
 *******************************************************************************/
Point nextToTop(std::stack<Point> *S) {
    Point p = S->top();
    S->pop();
    Point res = S->top();
    S->push(p);
    return res;
}

/****************************************************************************** 
 * @brief 返回 p1 和 p2 之间距离的平方。
 * @param p1 点 1 的坐标 <int, int>。
 * @param p2 点 2 的坐标 <int, int>。
 * @returns @param int p1 和 p2 之间的距离。
 *******************************************************************************/
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

/****************************************************************************** 
 * @brief 查找有序三元组 (p, q, r) 的方向。
 * @param p 点 p 的坐标 <int, int>。
 * @param q 点 q 的坐标 <int, int>。
 * @param r 点 r 的坐标 <int, int>。
 * @returns @param int 0 --> p, q 和 r 共线，1 --> 顺时针，2 --> 逆时针
 *******************************************************************************/
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) {
        return 0;  // 共线
    }
    return (val > 0) ? 1 : 2;  // 顺时针或逆时针
}

/****************************************************************************** 
 * @brief 用于库函数 qsort() 的函数，根据第一个点排序点数组
 * @param vp1 点 1 的坐标 <int, int>。
 * @param vp2 点 2 的坐标 <int, int>。
 * @returns @param int 点 p1 和 p2 之间的距离。
 *******************************************************************************/
int compare(const void *vp1, const void *vp2) {
    auto *p1 = static_cast<const Point *>(vp1);
    auto *p2 = static_cast<const Point *>(vp2);

    // 查找方向
    int o = orientation(p0, *p1, *p2);
    if (o == 0) {
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;
    }

    return (o == 2) ? -1 : 1;
}

/****************************************************************************** 
 * @brief 打印一组 n 个点的凸包。
 * @param points Point<int, int> 的向量，包含坐标。
 * @param size 向量的大小。
 * @returns @param vector 包含凸包的向量。
 *******************************************************************************/
std::vector<Point> convexHull(std::vector<Point> points, uint64_t size) {
    // 找到最底部的点
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < size; i++) {
        int y = points[i].y;

        // 选择最底部的点，或者在出现平局时选择最左侧的点
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
            ymin = points[i].y, min = i;
        }
    }

    // 将最底部的点放在第一个位置
    std::swap(points[0], points[min]);

    // 根据第一个点排序 n-1 个点。点 p1 在排序输出中位于 p2 之前，
    // 如果 p2 相对于 p1 具有更大的极坐标角（逆时针方向）。
    p0 = points[0];
    qsort(&points[1], size - 1, sizeof(Point), compare);

    // 如果两个或多个点与 p0 形成相同角度，去除所有点，只保留距离 p0 最远的点
    int m = 1;  // 初始化修改数组的大小
    for (int i = 1; i < size; i++) {
        // 保持去除 i，直到 i 和 i+1 之间的角度与 p0 相同
        while (i < size - 1 && orientation(p0, points[i], points[i + 1]) == 0) {
            i++;
        }

        points[m] = points[i];
        m++;  // 更新修改数组的大小
    }

    // 如果修改后的点数组少于 3 个点，则无法形成凸包
    if (m < 3) {
        return {};
    };

    // 创建一个空栈，并将前三个点压入栈中。
    std::stack<Point> St;
    St.push(points[0]);
    St.push(points[1]);
    St.push(points[2]);

    // 处理剩余的 n-3 个点
    for (int i = 3; i < m; i++) {
        // 保持去除栈顶元素，直到点 next-to-top, top 和 points[i]
        // 形成非左转角度
        while (St.size() > 1 &&
               orientation(nextToTop(&St), St.top(), points[i]) != 2) {
            St.pop();
        }
        St.push(points[i]);
    }

    std::vector<Point> result;
    // 现在栈中包含输出点，将它们压入结果向量中
    while (!St.empty()) {
        Point p = St.top();
        result.push_back(p);
        St.pop();
    }

    return result;  // 返回包含凸包坐标的结果向量。
}
}  // namespace grahamscan
}  // namespace geometry
