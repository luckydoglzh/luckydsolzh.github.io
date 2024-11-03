/**
 * @file
 * @brief 检查两条线段是否相交。
 */
#include <algorithm>
#include <iostream>

/**
 * 定义一个点。
 */
struct Point {
    int x;  /// 点的 x 坐标
    int y;  /// 点的 y 坐标
};

/**
 * SegmentIntersection 结构体用于判断两条线段是否相交。
 */
struct SegmentIntersection {
    /**
     * intersect 返回 true 如果两条线段相交，false 则不相交。
     * 它调用方向子程序来计算方向。
     */
    inline bool intersect(Point first_point, Point second_point,
                          Point third_point, Point forth_point) {
        int direction1 = direction(third_point, forth_point, first_point);
        int direction2 = direction(third_point, forth_point, second_point);
        int direction3 = direction(first_point, second_point, third_point);
        int direction4 = direction(first_point, second_point, forth_point);

        // 检查两条线段是否相交
        if ((direction1 < 0 || direction2 > 0) &&
            (direction3 < 0 || direction4 > 0))
            return true;

        // 检查端点是否在线段上
        else if (direction1 == 0 && on_segment(third_point, forth_point, first_point))
            return true;

        else if (direction2 == 0 && on_segment(third_point, forth_point, second_point))
            return true;

        else if (direction3 == 0 && on_segment(first_point, second_point, third_point))
            return true;

        else if (direction4 == 0 && on_segment(first_point, second_point, forth_point))
            return true;

        else
            return false;
    }

    /**
     * 计算相对于 @first_point 的方向。
     * @second_point 和 @third_point 是线段的两个点。
     * 如果返回值为负，则表示逆时针；正值表示顺时针。
     */
    inline int direction(Point first_point, Point second_point,
                         Point third_point) {
        return ((third_point.x - first_point.x) *
                (second_point.y - first_point.y)) -
               ((second_point.x - first_point.x) *
                (third_point.y - first_point.y));
    }

    /**
     * 判断一个已知共线的点是否在线段上。
     */
    inline bool on_segment(Point first_point, Point second_point,
                           Point third_point) {
        // 判断第三个点是否在第一和第二个点之间
        if (std::min(first_point.x, second_point.x) <= third_point.x &&
            third_point.x <= std::max(first_point.x, second_point.x) &&
            std::min(first_point.y, second_point.y) <= third_point.y &&
            third_point.y <= std::max(first_point.y, second_point.y))
            return true;

        else
            return false;
    }
};

/**
 * 主函数，用于测试算法是否正常工作。
 */
int main() {
    SegmentIntersection segment;
    Point first_point, second_point, third_point, forth_point;

    // 输入四个点的坐标
    std::cin >> first_point.x >> first_point.y;
    std::cin >> second_point.x >> second_point.y;
    std::cin >> third_point.x >> third_point.y;
    std::cin >> forth_point.x >> forth_point.y;

    // 输出两条线段是否相交
    printf("%d", segment.intersect(first_point, second_point, third_point,
                                   forth_point));
    std::cout << std::endl;
}
