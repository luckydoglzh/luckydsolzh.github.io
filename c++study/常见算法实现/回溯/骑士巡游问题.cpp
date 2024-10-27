// 骑士巡游问题是一个经典的棋盘问题，目标是让国际象棋中的骑士（Knight）在一个给定大小的棋盘上移动，要求骑士访问每一个格子一次且仅一次。
// 若骑士在完成所有格子的移动后能返回到起始格子并且仍然满足骑士的移动规则，则称之为“闭合巡游”，否则为“开放巡游”。
#include <array>     /// for std::array
#include <iostream>  /// for IO operations

/**
 * @namespace backtracking
 * @brief 回溯算法命名空间
 */
namespace backtracking {
/**
 * @namespace knight_tour
 * @brief 骑士巡游算法命名空间
 */
namespace knight_tour {
/**
 * @brief 检查给定位置 (x, y) 是否在棋盘上有效
 * @tparam V 数组中的顶点数量
 * @param x 当前行索引
 * @param y 当前列索引
 * @param sol 保存骑士访问情况的矩阵
 * @returns 如果位置有效返回 `true`，否则返回 `false`
 */
template <size_t V>
bool issafe(int x, int y, const std::array<std::array<int, V>, V> &sol) {
    return (x < V && x >= 0 && y < V && y >= 0 && sol[x][y] == -1);
}

/**
 * @brief 骑士巡游算法
 * @tparam V 数组中的顶点数量
 * @param x 当前行索引
 * @param y 当前列索引
 * @param mov 当前移动步数
 * @param sol 保存骑士访问情况的矩阵
 * @param xmov 骑士可能的 x 移动
 * @param ymov 骑士可能的 y 移动
 * @returns 如果存在解决方案返回 `true`，否则返回 `false`
 */
template <size_t V>
bool solve(int x, int y, int mov, std::array<std::array<int, V>, V> &sol,
           const std::array<int, V> &xmov, std::array<int, V> &ymov) {
    int k = 0, xnext = 0, ynext = 0;

    // 如果移动步数等于棋盘上的格子数，说明巡游完成
    if (mov == V * V) {
        return true;
    }

    // 尝试每一个可能的移动
    for (k = 0; k < V; k++) {
        xnext = x + xmov[k];  // 计算下一个 x 位置
        ynext = y + ymov[k];  // 计算下一个 y 位置

        // 如果下一个位置有效，则进行移动
        if (issafe<V>(xnext, ynext, sol)) {
            sol[xnext][ynext] = mov;  // 标记访问状态

            // 递归调用尝试下一个位置
            if (solve<V>(xnext, ynext, mov + 1, sol, xmov, ymov) == true) {
                return true;  // 如果找到解决方案，返回 true
            } else {
                sol[xnext][ynext] = -1;  // 回溯，重置状态
            }
        }
    }
    return false;  // 没有找到有效的解决方案
}
}  // namespace knight_tour
}  // namespace backtracking

/**
 * @brief 主函数
 * @returns 0 正常退出
 */
int main() {
    const int n = 8;  // 棋盘大小
    std::array<std::array<int, n>, n> sol = {0};  // 访问状态矩阵

    // 初始化访问状态矩阵
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            sol[i][j] = -1;  // -1 表示未访问
        }
    }

    // 定义骑士的移动方向
    std::array<int, n> xmov = {2, 1, -1, -2, -2, -1, 1, 2};  // x 坐标移动
    std::array<int, n> ymov = {1, 2, 2, 1, -1, -2, -2, -1};  // y 坐标移动

    sol[0][0] = 0;  // 从棋盘的左上角开始

    // 开始解决骑士巡游问题
    bool flag = backtracking::knight_tour::solve<n>(0, 0, 1, sol, xmov, ymov);
    if (flag == false) {
        std::cout << "错误：解决方案不存在\n";
    } else {
        // 打印访问状态矩阵
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                std::cout << sol[i][j] << "  ";  // 输出每个位置的访问步数
            }
            std::cout << "\n";  // 换行
        }
    }
    return 0;
}
