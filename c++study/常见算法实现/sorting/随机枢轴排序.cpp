/**
 * @file
 * @brief 实现 [随机枢轴快速排序](https://www.sanfoundry.com/cpp-program-implement-quick-sort-using-randomisation) 算法
 * @details
 *          * 随机枢轴快速排序算法与传统的快速排序非常相似，唯一的区别在于如何选择枢轴元素。
 *          * 快速排序本身速度很快，但在最坏情况下，时间复杂度可能达到 O(n^2)。
 *          * 为了避免最坏情况下的 O(n^2) 时间复杂度，我们使用随机选择枢轴的方式。
 *
 *          ### 逻辑
 *              * 逻辑非常简单，唯一的改变是在分区算法中，选择枢轴元素。
 *              * 与其选择数组的最后一个或第一个元素作为枢轴，我们使用一个随机索引来选择枢轴元素。
 *              * 这种方法能够避免实际使用中出现 O(n^2) 的最坏情况。
 *
 *       ### 分区逻辑
 *           * 数字小于“枢轴”元素的部分将排列在“枢轴”元素的左侧，而大于“枢轴”元素的部分将排列在数组的右侧。
 *
 *       ### 算法
 *           * 使用 `getRandomIndex()` 函数从数组中随机选择枢轴元素。
 *           * 初始化分区索引 pInd 为数组的起始位置。
 *           * 从数组的开始位置循环到结束位置。在每次循环中：
 *                   * 检查当前元素（arr[i]）是否小于枢轴元素。
 *                   * 如果当前元素小于枢轴元素，就交换当前元素和分区索引位置的元素，并将分区索引增加1。
 *           * 循环结束后，将枢轴元素与分区索引位置的元素交换。
 *           * 返回分区索引。
 *
 * @author [Nitin Sharma](https://github.com/foo290)
 */

#include <algorithm>  /// 用于 std::is_sorted(), std::swap()
#include <array>      /// 用于 std::array
#include <cassert>    /// 用于 assert
#include <ctime>      /// 用于初始化随机数生成器
#include <iostream>   /// 用于输入输出操作
#include <tuple>      /// 用于从函数返回多个值

/**
 * @namespace sorting
 * @brief 排序算法
 */
namespace sorting {
/**
 * @brief [随机枢轴快速排序](https://www.sanfoundry.com/cpp-program-implement-quick-sort-using-randomisation) 实现的函数
 * @namespace random_pivot_quick_sort
 */
namespace random_pivot_quick_sort {
/**
 * @brief 用于打印数组的工具函数
 * @tparam T 数组的大小
 * @param arr 要打印的数组
 * @returns void
 */
template <size_t T>
void showArray(std::array<int64_t, T> arr) {
    for (int64_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief 获取数组中指定范围内的随机索引
 * @param start 数组的起始索引
 * @param end 数组的结束索引
 * @returns int64_t 返回起始索引到结束索引之间的随机整数
 */
int64_t getRandomIndex(int64_t start, int64_t end) {
    srand(time(nullptr));  // 初始化随机数生成器
    int64_t randomPivotIndex = start + rand() % (end - start + 1);
    return randomPivotIndex;
}

/**
 * @brief 快速排序的分区函数
 * @tparam size 数组的大小
 * @param start 数组的起始索引
 * @param end 数组的结束索引
 * @returns std::tuple<int64_t , std::array<int64_t , size>> 返回枢轴元素的索引和排序后的数组
 */
template <size_t size>
std::tuple<int64_t, std::array<int64_t, size>> partition(
    std::array<int64_t, size> arr, int64_t start, int64_t end) {
    int64_t pivot = arr[end];  // 选择最后一个元素作为枢轴
    int64_t pInd = start;

    // 遍历数组，按大小对元素进行分区
    for (int64_t i = start; i < end; i++) {
        if (arr[i] <= pivot) {
            std::swap(arr[i], arr[pInd]);  // 交换当前元素和分区索引位置的元素
            pInd++;
        }
    }
    std::swap(arr[pInd], arr[end]);  // 将枢轴元素放到正确的位置
    return std::make_tuple(pInd, arr);  // 返回分区索引和排序后的数组
}

/**
 * @brief 随机枢轴快速排序函数
 * @tparam size 数组的大小
 * @param start 数组的起始索引
 * @param end 数组的结束索引
 * @returns std::array<int64_t , size> 返回排序后的数组
 */
template <size_t size>
std::array<int64_t, size> quickSortRP(std::array<int64_t, size> arr,
                                      int64_t start, int64_t end) {
    if (start < end) {
        int64_t randomIndex = getRandomIndex(start, end);

        // 将枢轴与数组的最后一个元素交换
        std::swap(arr[end], arr[randomIndex]);

        int64_t pivotIndex = 0;
        // 获取枢轴索引和排序后的数组
        std::tie(pivotIndex, arr) = partition(arr, start, end);

        // 递归调用对左右子数组进行排序
        std::array<int64_t, arr.size()> rightSortingLeft =
            quickSortRP(arr, start, pivotIndex - 1);
        std::array<int64_t, arr.size()> full_sorted =
            quickSortRP(rightSortingLeft, pivotIndex + 1, end);
        arr = full_sorted;
    }
    return arr;
}

/**
 * @brief 用于生成指定大小和范围的无序数组
 * @tparam size 输出数组的大小
 * @param from 数字范围的起始值
 * @param to 数字范围的结束值
 * @returns std::array<int64_t , size> 生成的无序数组
 */
template <size_t size>
std::array<int64_t, size> generateUnsortedArray(int64_t from, int64_t to) {
    srand(time(nullptr));
    std::array<int64_t, size> unsortedArray{};
    assert(from < to);
    int64_t i = 0;
    while (i < size) {
        int64_t randomNum = from + rand() % (to - from + 1);
        if (randomNum) {
            unsortedArray[i] = randomNum;
            i++;
        }
    }
    return unsortedArray;
}

}  // namespace random_pivot_quick_sort
}  // namespace sorting

/**
 * @brief 测试用例类
 */
class TestCases {
 private:
    /**
     * @brief 输出给定消息
     * @tparam T 消息的类型
     * @returns void
     */
    template <typename T>
    void log(T msg) {
        // 避免重复编写 cout 和 endl
        std::cout << "[TESTS] : ---> " << msg << std::endl;
    }

 public:
    /**
     * @brief 执行测试用例
     * @returns void
     */
    void runTests() {
        log("Running Tests...");

        testCase_1();
        testCase_2();
        testCase_3();

        log("Test Cases over!");
        std::cout << std::endl;
    }

    /**
     * @brief 单元素测试用例
     * @returns void
     */
    void testCase_1() {
        const int64_t inputSize = 1;
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("Test case 1: Only one element in the array.");
        std::array<int64_t, inputSize> unsorted_arr{2};

        int64_t start = 0;
        int64_t end = unsorted_arr.size() - 1;

        log("Running the algorithm...");
        std::array<int64_t, unsorted_arr.size()> sorted_arr =
            sorting::random_pivot_quick_sort::quickSortRP(unsorted_arr, start,
                                                          end);
        log("Algorithm finished!");

        log("Checking the result...");
        assert(std::is_sorted(sorted_arr.begin(), sorted_arr.end()));
        log("[PASS] : TEST CASE 1 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }

    /**
     * @brief 大输入测试用例
     * @returns void
     */
    void testCase_2() {
        const int64_t inputSize = 500;
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("Test case 2: Array with 500 elements and repeated values.");
        std::array<int64_t, inputSize> unsorted_arr =
            sorting::random_pivot_quick_sort::generateUnsortedArray<500>(100, 1000);

        int64_t start = 0;
        int64_t end = unsorted_arr.size() - 1;

        log("Running the algorithm...");
        std::array<int64_t, unsorted_arr.size()> sorted_arr =
            sorting::random_pivot_quick_sort::quickSortRP(unsorted_arr, start,
                                                          end);
        log("Algorithm finished!");

        log("Checking the result...");
        assert(std::is_sorted(sorted_arr.begin(), sorted_arr.end()));
        log("[PASS] : TEST CASE 2 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }

    /**
     * @brief 多元素数组测试用例
     * @returns void
     */
    void testCase_3() {
        const int64_t inputSize = 10;
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("Test case 3: Array with multiple elements.");
        std::array<int64_t, inputSize> unsorted_arr{5, 4, 3, 2, 1, 8, 7, 6, 10, 9};

        int64_t start = 0;
        int64_t end = unsorted_arr.size() - 1;

        log("Running the algorithm...");
        std::array<int64_t, unsorted_arr.size()> sorted_arr =
            sorting::random_pivot_quick_sort::quickSortRP(unsorted_arr, start,
                                                          end);
        log("Algorithm finished!");

        log("Checking the result...");
        assert(std::is_sorted(sorted_arr.begin(), sorted_arr.end()));
        log("[PASS] : TEST CASE 3 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }
};

/**
 * @brief 程序入口点
 * @returns 0 程序退出状态
 */
int main() {
    TestCases testCase;
    testCase.runTests();

    return 0;
}
