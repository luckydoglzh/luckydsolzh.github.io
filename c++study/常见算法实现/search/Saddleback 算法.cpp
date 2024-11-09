/**
 * @file
 * @brief 实现了 [Saddleback 算法](https://www.geeksforgeeks.org/saddleback-search-algorithm-in-a-2d-array) 用于二维数组查找。
 *
 * @details
 * Saddleback 算法是一种在二维数组中以线性时间 (即 O(m + n)，其中 m 为行数，n 为列数) 查找元素的算法。
 * 该算法要求矩阵的每行和每列都已经排序。
 *
 * @author [Hashir Niazi](https://github.com/HashirGJ8842)
 */
#include <cassert>      /// 用于断言
#include <iostream>     /// 用于输入输出操作，和 std::pair
#include <vector>       /// 用于 std::vector

/** \namespace search
 * \brief 搜索算法
 */
namespace search {
/** \namespace saddleback
 * \brief 实现 [Saddleback 算法](https://www.geeksforgeeks.org/saddleback-search-algorithm-in-a-2d-array) 的函数
 */
namespace saddleback {
/**
 * 该函数实现了 [Saddleback 算法](https://www.geeksforgeeks.org/saddleback-search-algorithm-in-a-2d-array)，
 * 用于在已排序的二维数组中查找目标元素的位置
 * @param matrix 已按行和列排序的二维矩阵
 * @param element 需要查找的元素
 * @return 如果找到元素，返回包含行和列的 std::pair
 * @return 如果未找到元素，返回 std::pair(0, 0)
 */
std::pair<uint32_t, uint32_t> saddleback(std::vector<std::vector<int32_t>> matrix,
                               int32_t element) {
    uint32_t left_index = 0;
    uint32_t right_index = matrix[0].size() - 1;  // 从右上角开始查找
    while (left_index < matrix.size()) {  // 当行索引有效时继续查找
        if (element ==
            matrix[left_index]
                  [right_index]) {  // 如果当前元素等于目标值，返回当前的行列索引
            return std::make_pair(left_index + 1, right_index + 1);  // 注意返回的是 1 基索引
        } else if (element >
                   matrix[left_index]
                         [right_index]) {  // 如果当前元素小于目标值，向下移动
            ++left_index;
        } else if (element <
                   matrix[left_index]
                         [right_index]) {  // 如果当前元素大于目标值，向左移动
            if (!right_index)  // 如果已经到达第一列，停止查找
                break;
            else --right_index;
        }
    }
    return std::make_pair(0, 0);  // 如果找不到元素，返回 (0, 0)
}
}  // namespace saddleback
}  // namespace search

/**
 * @brief 测试实现
 * @returns void
 */
static void test() {
    // 创建一个 5x5 的二维矩阵
    std::vector<std::vector<int32_t>> matrix = {{1, 10, 100, 1000, 10000},
                                            {2, 20, 200, 2000, 20000},
                                            {3, 30, 300, 3000, 30000},
                                            {4, 40, 400, 4000, 40000},
                                            {5, 50, 500, 5000, 50000}};

    // 定义目标值未找到时的返回值 (0, 0)
    std::pair<uint32_t, uint32_t> not_found = std::make_pair(0, 0);
    std::pair<uint32_t, uint32_t> test_answer;

    // 测试 1：查找 123，未找到
    std::pair<uint32_t, uint32_t> answer1 = search::saddleback::saddleback(matrix, 123);
    assert(not_found == answer1);

    // 测试 2：查找 0，未找到
    answer1 = search::saddleback::saddleback(matrix, 0);
    assert(not_found == answer1);

    // 测试 3：查找 1，找到 (1, 1)
    answer1 = search::saddleback::saddleback(matrix, 1);
    test_answer = std::make_pair(1, 1);
    assert(test_answer == answer1);

    // 测试 4：查找 50000，找到 (5, 5)
    answer1 = search::saddleback::saddleback(matrix, 50000);
    test_answer = std::make_pair(5, 5);
    assert(test_answer == answer1);

    // 测试 5：查找 300，找到 (3, 3)
    answer1 = search::saddleback::saddleback(matrix, 300);
    test_answer = std::make_pair(3, 3);
    assert(test_answer == answer1);
}

/**
 * @brief 主函数
 * @returns 0
 */
int main() {
    test();     // 执行测试
    return 0;
}
