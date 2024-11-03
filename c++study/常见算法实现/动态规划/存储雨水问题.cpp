/**
 * @file
 * @brief 实现 [被困雨水问题] (https://www.geeksforgeeks.org/trapping-rain-water/)
 * @details
 * 该实现计算在墙壁之间可以储存的雨水量，墙壁由高度数组表示。
 * @author [SOZEL](https://github.com/TruongNhanNguyen)
 */

#include <algorithm>  /// 用于 std::min 和 std::max
#include <cassert>    /// 用于 assert
#include <cstddef>    /// 用于 std::size_t
#include <cstdint>    /// 用于整数类型定义
#include <vector>     /// 用于 std::vector

/*
 * @namespace
 * @brief 动态规划算法
 */
namespace dynamic_programming {

/**
 * @brief 计算被困的雨水量
 * @param heights 表示墙壁高度的数组
 * @return 可以储存的雨水量
 */
uint32_t trappedRainwater(const std::vector<uint32_t>& heights) {
    std::size_t n = heights.size();
    if (n <= 2)
        return 0;  // 少于 3 个墙壁无法储存雨水

    std::vector<uint32_t> leftMax(n), rightMax(n);

    // 计算每个墙壁左侧的最大高度
    leftMax[0] = heights[0];
    for (std::size_t i = 1; i < n; ++i) {
        leftMax[i] = std::max(leftMax[i - 1], heights[i]);
    }

    // 计算每个墙壁右侧的最大高度
    rightMax[n - 1] = heights[n - 1];
    for (std::size_t i = n - 2; i < n; --i) {
        rightMax[i] = std::max(rightMax[i + 1], heights[i]);
    }

    // 计算墙壁之间的被困雨水量
    uint32_t trappedWater = 0;
    for (std::size_t i = 0; i < n; ++i) {
        trappedWater +=
            std::max(0u, std::min(leftMax[i], rightMax[i]) - heights[i]);
    }

    return trappedWater;
}

}  // namespace dynamic_programming

/**
 * @brief 自我测试实现
 * @returns void
 */
static void test() {
    std::vector<uint32_t> test_basic = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    assert(dynamic_programming::trappedRainwater(test_basic) == 6);

    std::vector<uint32_t> test_peak_under_water = {3, 0, 2, 0, 4};
    assert(dynamic_programming::trappedRainwater(test_peak_under_water) == 7);

    std::vector<uint32_t> test_bucket = {5, 1, 5};
    assert(dynamic_programming::trappedRainwater(test_bucket) == 4);

    std::vector<uint32_t> test_skewed_bucket = {4, 1, 5};
    assert(dynamic_programming::trappedRainwater(test_skewed_bucket) == 3);

    std::vector<uint32_t> test_empty = {};
    assert(dynamic_programming::trappedRainwater(test_empty) == 0);

    std::vector<uint32_t> test_flat = {0, 0, 0, 0, 0};
    assert(dynamic_programming::trappedRainwater(test_flat) == 0);

    std::vector<uint32_t> test_no_trapped_water = {1, 1, 2, 4, 0, 0, 0};
    assert(dynamic_programming::trappedRainwater(test_no_trapped_water) == 0);

    std::vector<uint32_t> test_single_elevation = {5};
    assert(dynamic_programming::trappedRainwater(test_single_elevation) == 0);

    std::vector<uint32_t> test_two_point_elevation = {5, 1};
    assert(dynamic_programming::trappedRainwater(test_two_point_elevation) == 0);

    std::vector<uint32_t> test_large_elevation_map_difference = {5, 1, 6, 1,
                                                                 7, 1, 8};
    assert(dynamic_programming::trappedRainwater(
               test_large_elevation_map_difference) == 15);
}

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main() {
    test();  // 运行自我测试实现
    return 0;
}
