/**
 * @file
 * @brief 实现 [Jarvis](https://en.wikipedia.org/wiki/Gift_wrapping_algorithm) 算法。
 *
 * @details
 * 给定一组平面上的点，凸包是包含所有点的最小凸多边形。
 *
 * ### 算法
 * Jarvis 算法的思路很简单，我们从最左边的点（或 x 坐标值最小的点）开始，
 * 并保持逆时针方向包围点。
 *
 * 这里的思路是使用 orientation()。下一个点是选择能在逆时针方向上
 * 击败其他所有点的点，即，如果对于任何其他点 r，满足“orientation(p, q, r) = 逆时针”，
 * 则下一个点为 q。
 *
 * 例如，
 * 如果 points = {{0, 3}, {2, 2}, {1, 1}, {2, 1},
 *                {3, 0}, {0, 0}, {3, 3}}；
 *
 * 那么凸包为
 * (0, 3), (0, 0), (3, 0), (3, 3)
 *
 * @author [Rishabh Agarwal](https://github.com/rishabh-997)
 */

#include <vector>
#include <cassert>
#include <iostream>

/**
 *  @namespace geometry
 *  @brief 几何算法
 */
namespace geometry {
    /**
     * @namespace jarvis
     * @brief [Jarvis](https://en.wikipedia.org/wiki/Gift_wrapping_algorithm) 算法的函数
     */
    namespace jarvis {
        /**
         * 定义给定点在空间中的 x 和 y 坐标的结构体
         */
        struct Point {
            int x, y;
        };

        /**
         * 可以从主函数调用并在代码中全局可用的类
         */
        class Convexhull {
            std::vector<Point> points; // 存储点的向量
            int size; // 点的数量

        public:
            /**
             * 给定类的构造函数
             *
             * @param pointList 空间中所有点的列表
             * @param n 空间中的点的数量
             */
            explicit Convexhull(const std::vector<Point> &pointList) {
                points = pointList;
                size = points.size();
            }

            /**
             * 创建一组 n 个点的凸包。
             * 至少需要 3 个点才能存在凸包
             *
             * @returns 包含空间中点的向量数组
             *          这些点包围所有给定点，从而形成一个凸包
             */
            std::vector<Point> getConvexHull() const {
                // 初始化结果
                std::vector<Point> hull;

                // 找到最左边的点
                int leftmost_point = 0;
                for (int i = 1; i < size; i++) {
                    if (points[i].x < points[leftmost_point].x) {
                        leftmost_point = i; // 更新最左边的点
                    }
                }

                // 从最左边的点开始，保持逆时针移动
                // 直到再次到达起始点。该循环运行 O(h) 次
                // 其中 h 是结果或输出中的点的数量。
                int p = leftmost_point, q = 0;
                do {
                    // 将当前点添加到结果中
                    hull.push_back(points[p]);

                    // 搜索一个点 'q'，使得 orientation(p, x, q)
                    // 对于所有点 'x' 都是逆时针方向。这个想法是
                    // 追踪最近访问的最逆时针的点 q。如果任何点 'i'
                    // 比 q 更加逆时针，则更新 q。
                    q = (p + 1) % size;
                    for (int i = 0; i < size; i++) {
                        // 如果 i 比当前 q 更加逆时针，则更新 q
                        if (orientation(points[p], points[i], points[q]) == 2) {
                            q = i;
                        }
                    }

                    // 现在 q 是相对于 p 最逆时针的点
                    // 将 p 设置为 q 以进行下一次迭代，
                    // 这样 q 就会添加到结果 'hull' 中
                    p = q;

                } while (p != leftmost_point); // 当我们没有回到第一个点时

                return hull;
            }

            /**
             * 该函数返回空间中三点的几何方向
             * 即，它们是否是线性、顺时针或逆时针
             * @param p 选择的第一个点
             * @param q 相邻的点
             * @param r 相邻的点
             *
             * @returns 0 -> 线性
             * @returns 1 -> 顺时针
             * @returns 2 -> 逆时针
             */
            static int orientation(const Point &p, const Point &q, const Point &r) {
                int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

                if (val == 0) {
                    return 0; // 线性
                }
                return (val > 0) ? 1 : 2; // 顺时针或逆时针
            }

        };

    } // namespace jarvis
} // namespace geometry

/**
 * 测试函数
 * @returns void
 */
static void test() {
    std::vector<geometry::jarvis::Point> points = {{0, 3},
                                                   {2, 2},
                                                   {1, 1},
                                                   {2, 1},
                                                   {3, 0},
                                                   {0, 0},
                                                   {3, 3}
    };
    geometry::jarvis::Convexhull hull(points);
    std::vector<geometry::jarvis::Point> actualPoint;
    actualPoint = hull.getConvexHull();

    std::vector<geometry::jarvis::Point> expectedPoint = {{0, 3},
                                                          {0, 0},
                                                          {3, 0},
                                                          {3, 3}};
    for (int i = 0; i < expectedPoint.size(); i++) {
        assert(actualPoint[i].x == expectedPoint[i].x);
        assert(actualPoint[i].y == expectedPoint[i].y);
    }
    std::cout << "测试实现通过！\n";
}

/** 主程序 */
int main() {
    test();
    return 0;
}
