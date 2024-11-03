/**
 * @file
 * @brief [哈密尔顿循环](https://en.wikipedia.org/wiki/Hamiltonian_path)的动态解决方案实现，适用于顶点数量小于 20。
 * @details
 * 我使用 \f$2^n\times n\f$ 矩阵，针对矩阵中的每个 \f$[i, j]\f$（\f$i < 2^n\f$ 且 \f$j < n\f$），
 * 如果可以到达所有在 `i` 的二进制表示中为 `1` 的顶点，且 \f$j\f$ 是最后一个顶点，则存储为 `true`。
 *
 * 最终，如果 \f$(2^n - 1)^{\mbox{th}}\f$ 行中的任何单元格为 `true`，则存在哈密尔顿循环。
 *
 * @author [vakhokoto](https://github.com/vakhokoto)
 * @author [Krishna Vedala](https://github.com/kvedala)
 */
#include <cassert>
#include <iostream>
#include <vector>

/**
 * 函数用于判断图中是否存在哈密尔顿循环。
 *
 * @param routes nxn 布尔矩阵 \f$[i, j]\f$，其中 \f$[i, j]\f$ 为 `true` 时表示从 \f$i\f$ 到 \f$j\f$ 之间有边。
 * @return 如果图中存在哈密尔顿循环，则返回 `true`。
 * @return 如果图中不存在哈密尔顿循环，则返回 `false`。
 */
bool hamilton_cycle(const std::vector<std::vector<bool>> &routes) {
    const size_t n = routes.size();
    // dp 数组的高度为 2^n
    const size_t height = 1 << n;
    std::vector<std::vector<bool>> dp(height, std::vector<bool>(n, false));

    // 填充 [2^i, i] 单元格为 true
    for (size_t i = 0; i < n; ++i) {
        dp[1 << i][i] = true;
    }
    for (size_t i = 1; i < height; i++) {
        std::vector<size_t> zeros, ones;
        // 查找 1 和 0 的位置并分开
        for (size_t pos = 0; pos < n; ++pos) {
            if ((1 << pos) & i) {
                ones.push_back(pos);
            } else {
                zeros.push_back(pos);
            }
        }

        for (auto &o : ones) {
            if (!dp[i][o]) {
                continue;
            }

            for (auto &z : zeros) {
                if (!routes[o][z]) {
                    continue;
                }
                dp[i + (1 << z)][z] = true;
            }
        }
    }

    bool is_cycle = false;
    for (size_t i = 0; i < n; i++) {
        is_cycle |= dp[height - 1][i];
        if (is_cycle) {  // 如果为 true，后续循环也会为 true，因此可以直接跳出
            break;
        }
    }
    return is_cycle;
}

/**
 * 测试 ::hamilton_cycle 在图 `1 -> 2 -> 3 -> 4` 时返回 `true`
 * @return None
 */
static void test1() {
    std::vector<std::vector<bool>> arr{
        std::vector<bool>({true, true, false, false}),
        std::vector<bool>({false, true, true, false}),
        std::vector<bool>({false, false, true, true}),
        std::vector<bool>({false, false, false, true})};

    bool ans = hamilton_cycle(arr);
    std::cout << "测试 1... ";
    assert(ans);
    std::cout << "通过\n";
}

/**
 * 测试 ::hamilton_cycle 在图 
 * \n graph:<pre>
 *  1 -> 2 -> 3
 *       |
 *       V
 *       4</pre> 时返回 `false`
 * @return None
 */
static void test2() {
    std::vector<std::vector<bool>> arr{
        std::vector<bool>({true, true, false, false}),
        std::vector<bool>({false, true, true, true}),
        std::vector<bool>({false, false, true, false}),
        std::vector<bool>({false, false, false, true})};

    bool ans = hamilton_cycle(arr);

    std::cout << "测试 2... ";
    assert(!ans);  // 不是一个循环
    std::cout << "通过\n";
}

/**
 * 测试 ::hamilton_cycle 在 4 个顶点的完全图中返回 `true`
 * @return None
 */
static void test3() {
    std::vector<std::vector<bool>> arr{
        std::vector<bool>({true, true, true, true}),
        std::vector<bool>({true, true, true, true}),
        std::vector<bool>({true, true, true, true}),
        std::vector<bool>({true, true, true, true})};

    bool ans = hamilton_cycle(arr);

    std::cout << "测试 3... ";
    assert(ans);
    std::cout << "通过\n";
}

/**
 * 主函数
 *
 * @param argc 命令行参数计数（忽略）
 * @param argv 命令行参数数组（忽略）
 */
int main(int argc, char **argv) {
    test1();
    test2();
    test3();
    return 0;
}
