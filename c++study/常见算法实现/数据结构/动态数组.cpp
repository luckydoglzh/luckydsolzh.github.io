/**
 * @file
 * @brief [动态数组](https://en.wikipedia.org/wiki/Dynamic_array)
 *
 * @details
 * list_array 是使用数组实现的列表。
 * 我们可以执行基本的 CRUD 操作，以及其他操作如排序等。
 *
 * ### 算法
 * 它实现了插入、排序、搜索等方法。
 * 您可以选择操作，方法将自动执行任务。
 * 可以插入元素、按顺序排序、有效地搜索、删除值和打印列表。
 */

#include <iostream>  ///< 用于输入输出操作
#include <array>     ///< 用于 std::array
#include <cassert>   ///< 用于断言操作

/**
 * @namespace data_structures
 * @brief 包含数据结构相关算法
 */
namespace data_structures {
/**
 * @namespace list_array
 * @brief [动态数组](https://en.wikipedia.org/wiki/Dynamic_array) 算法的函数
 */
namespace list_array {
    /**
     * @brief 列表结构，包含支持的方法
     */
    template <uint64_t N>
    struct list {
        std::array<uint64_t, N> data{};  // 用于实现列表的数组
        uint64_t top = 0;                // 指向最后一个元素的指针
        bool isSorted = false;           // 是否已排序的标志

        /**
         * @brief 使用二分搜索在列表中查找元素
         * @param dataArr 列表
         * @param first 剩余列表中的第一个元素的指针
         * @param last 剩余列表中的最后一个元素的指针
         * @param val 要搜索的元素
         * @return 列表中元素的索引，如果不存在则返回 -1
         */
        uint64_t BinarySearch(const std::array<uint64_t, N> &dataArr, const uint64_t &first, const uint64_t &last,
                              const uint64_t &val) {
            // 如果两个指针交叉，说明列表中没有该元素
            if (last < first) {
                return -1;
            }
            uint64_t mid = (first + last) / 2;
            // 检查当前中间指针的值是否等于元素
            if (dataArr[mid] == val)
                return mid;
            else if (val < dataArr[mid])
                return (BinarySearch(dataArr, first, mid - 1, val)); // 在前半部分搜索
            else if (val > dataArr[mid])
                return (BinarySearch(dataArr, mid + 1, last, val));  // 在后半部分搜索

            std::cerr << __func__ << ":" << __LINE__ << ": 未定义的情况\n";
            return -1;
        }

        /**
         * @brief 使用线性搜索查找元素
         * @param dataArr 列表
         * @param val 要搜索的元素
         * @return 列表中元素的索引，如果不存在则返回 -1
         */
        uint64_t LinearSearch(const std::array<uint64_t, N> &dataArr, const uint64_t &val) const {
            // 遍历列表中的每个元素
            for (uint64_t i = 0; i < top; i++) {
                if (dataArr[i] == val) {
                    return i; // 找到元素，返回索引
                }
            }
            return -1; // 元素不存在于列表中
        }

        /*
         * @brief 二分搜索和线性搜索的父函数
         * @param val 要搜索的元素
         * @return 列表中元素的索引，如果不存在则返回 -1
         */
        uint64_t search(const uint64_t &val) {
            uint64_t pos; // 用于存储元素索引的变量
            if (isSorted) {
                pos = BinarySearch(data, 0, top - 1, val); // 如果列表已排序，使用二分搜索
            } else {
                pos = LinearSearch(data, val); // 否则使用线性搜索
            }
            if (pos != -1) {
                std::cout << "\n元素位于位置：" << pos;
            } else {
                std::cout << "\n未找到元素";
            }
            return pos; // 返回元素的索引或 -1
        }

        /**
         * @brief 对列表进行排序
         */
        void sort() {
            for (uint64_t i = 0; i < top; i++) {
                uint64_t min_idx = i; // 初始化最小值索引
                for (uint64_t j = i + 1; j < top; j++) {
                    if (data[j] < data[min_idx]) {
                        min_idx = j; // 更新最小值索引
                    }
                }
                std::swap(data[min_idx], data[i]); // 交换最小值和当前位置的元素
            }
            isSorted = true; // 标记列表为已排序
        }

        /**
         * @brief 向列表中插入新元素
         * @param val 要插入的元素
         */
        void insert(const uint64_t &val) {
            if (top == N) {
                std::cout << "\n溢出";
                return;
            }
            if (!isSorted) {
                data[top] = val;
                top++;
            } else {
                uint64_t pos = 0; // 初始化插入位置索引
                for (uint64_t i = 0; i < top - 1; i++) {
                    if (data[i] <= val && val <= data[i + 1]) {
                        pos = i + 1;
                        break;
                    }
                }
                if (pos == 0) {
                    pos = top - 1;
                }
                for (uint64_t i = top; i > pos; i--) {
                    data[i] = data[i - 1];
                }
                top++;
                data[pos] = val;
            }
        }

        /**
         * @brief 从列表中删除元素
         * @param val 要删除的元素
         */
        void remove(const uint64_t &val) {
            uint64_t pos = search(val); // 搜索元素的索引
            if (pos == -1) {
                std::cout << "\n元素不在列表中";
                return;
            }
            std::cout << "\n已删除：" << data[pos];
            for (uint64_t i = pos; i < top; i++) {
                data[i] = data[i + 1];
            }
            top--;
        }

        /**
         * @brief 打印数组的实用函数
         */
        void show() {
            std::cout << '\n';
            for (uint64_t i = 0; i < top; i++) {
                std::cout << data[i] << " ";
            }
        }
    }; // 结构 list
} // namespace list_array
} // namespace data_structures

/**
 * @brief 测试实现
 */
static void test() {
    data_structures::list_array::list<50> L;

    // 插入测试
    L.insert(11);
    L.insert(12);
    assert(L.top == 2);
    L.insert(15);
    L.insert(10);
    L.insert(12);
    L.insert(20);
    L.insert(18);
    assert(L.top == 7);
    L.show(); // 打印数组

    // 删除测试
    L.remove(12); // 删除列表中的重复值
    L.remove(15); // 删除列表中存在的值
    assert(L.top == 5);
    L.remove(50); // 尝试删除列表中不存在的值
    assert(L.top == 5);

    // 线性搜索测试
    assert(L.search(11) == 0); // 搜索存在的元素
    assert(L.search(12) == 2);
    assert(L.search(50) == -1); // 搜索不存在的元素

    // 排序测试
    L.sort();
    assert(L.isSorted == true);
    L.show();

    // 二分搜索测试
    assert(L.search(11) == 1); // 搜索存在的元素
    assert(L.search(12) == 2);
    assert(L.search(50) == -1); // 搜索不存在的元素
}

/**
 * @brief 主函数
 */
int main() {
    test(); // 执行测试
    return 0;
}
