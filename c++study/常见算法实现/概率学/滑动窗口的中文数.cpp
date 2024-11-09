/**
 * @file
 * @brief 实现一个滑动窗口的中位数计算
 *
 * @details
 * 给定一个整数流，算法计算固定大小窗口的中位数。该算法的主要时间复杂度为 O(log(N))，灵感来自已知的[从（无限）数据流中寻找中位数](https://www.tutorialcup.com/interview/algorithm/find-median-from-data-stream.htm)算法，并经过适当修改以考虑到有限窗口大小的要求。
 *
 * ### 算法
 * 滑动窗口由一个列表管理，确保插入和弹出操作的时间复杂度为 O(1)。每个新值都被推入窗口的末尾，同时窗口前端的值被弹出。此外，算法使用一个多值二叉搜索树（BST）来管理窗口内的有序值，使用 `std::multiset` 来实现。每次插入新值时，它也会被插入到 BST 中。弹出窗口的值时，也会从 BST 中删除相应的值。插入和删除操作的时间复杂度为 O(logN)，其中 N 为窗口的大小。最后，算法保持一个指向 BST 根节点的指针，并在每次插入或删除时更新该指针。BST 的根节点即为中位数！因此，中位数的获取操作始终是 O(1)。
 *
 * 时间复杂度: O(logN)，空间复杂度: O(N)，N 为窗口的大小。
 * @author [Yaniv Hollander](https://github.com/YanivHollander)
 */
#include <cassert>  /// 用于断言
#include <cstdlib>  /// 用于 std::rand - 在测试中需要
#include <ctime>    /// 用于 std::time - 在测试中需要
#include <list>     /// 用于 std::list - 用于管理滑动窗口
#include <set>      /// 用于 std::multiset - 用于管理多值排序的滑动窗口值
#include <vector>   /// 用于 std::vector - 在测试中需要

/**
 * @namespace probability
 * @brief 概率算法
 */
namespace probability {
/**
 * @namespace windowed_median
 * @brief 滑动窗口中位数算法实现
 */
namespace windowed_median {
using Window = std::list<int>;  ///< 滑动窗口类型
using size_type = Window::size_type;  ///< 滑动窗口大小类型

/**
 * @class WindowedMedian
 * @brief 计算数据流中固定大小滑动窗口的中位数
 */
class WindowedMedian {
    const size_type _windowSize;  ///< 滑动窗口大小
    Window _window;  ///< 滑动窗口中的整数值
    std::multiset<int> _sortedValues;  ///< 用于表示平衡的多值二叉搜索树（BST）的数据结构
    std::multiset<int>::const_iterator
        _itMedian;  ///< 指向多值 BST 根节点的迭代器，根节点即为中位数

    /**
     * @brief 将一个值插入到有序的多值 BST 中
     * @param value 要插入的值
     */
    void insertToSorted(int value) {
        _sortedValues.insert(value);  /// 将值插入到 BST 中 - O(logN)
        const auto sz = _sortedValues.size();
        if (sz == 1) {  /// 如果是第一个值，设置中位数迭代器为 BST 根节点
            _itMedian = _sortedValues.begin();
            return;
        }

        /// 如果新值进入左子树且元素个数为偶数，新的中位数为当前中位数的左子节点
        if (value < *_itMedian && sz % 2 == 0) {
            --_itMedian;  // O(1) - 向左子节点移动一步
        }

        /// 如果新值进入右子树且元素个数为奇数，新的中位数为当前中位数的右子节点
        else if (value >= *_itMedian && sz % 2 != 0) {
            ++_itMedian;  /// O(1) - 向右子节点移动一步
        }
    }

    /**
     * @brief 从有序的多值 BST 中删除一个值
     * @param value 要删除的值
     */
    void eraseFromSorted(int value) {
        const auto sz = _sortedValues.size();

        /// 如果删除的值位于左子树或当前中位数，并且元素个数为偶数，新的中位数将是当前中位数的右子节点
        if (value <= *_itMedian && sz % 2 == 0) {
            ++_itMedian;  /// O(1) - 向右子节点移动一步
        }

        /// 如果删除的值位于右子树或当前中位数，并且元素个数为奇数，新的中位数将是当前中位数的左子节点
        else if (value >= *_itMedian && sz % 2 != 0) {
            --_itMedian;  // O(1) - 向左子节点移动一步
        }

        /// 找到要删除的值的第一个位置，并删除
        const auto it = _sortedValues.find(value);  // O(logN)
        _sortedValues.erase(it);                    // O(logN)
    }

 public:
    /**
     * @brief 构造 WindowedMedian 对象
     * @param windowSize 滑动窗口的大小
     */
    explicit WindowedMedian(size_type windowSize) : _windowSize(windowSize){}; 

    /**
     * @brief 向数据流中插入一个新值
     * @param value 要插入的新值
     */
    void insert(int value) {
        /// 将新值推入滑动窗口的末尾 - O(1)
        _window.push_back(value);
        insertToSorted(value);  // 将值插入到多值 BST 中 - O(logN)
        if (_window.size() > _windowSize) {  /// 如果超过窗口大小，则从左侧弹出
            eraseFromSorted(
                _window.front());  /// 从多值 BST 中删除窗口左侧的值
            _window.pop_front();   /// 从窗口中弹出左侧的值 - O(1)
        }
    }

    /**
     * @brief 获取滑动窗口中的中位数
     * @return 中位数。如果窗口大小为偶数，返回两个中间值的平均值
     */
    float getMedian() const {
        if (_sortedValues.size() % 2 != 0) {
            return *_itMedian;  // O(1)
        }
        return 0.5f * *_itMedian + 0.5f * *next(_itMedian);  /// O(1)
    }

    /**
     * @brief 一种低效的获取滑动窗口中位数的方式。仅用于测试！
     * @return 中位数。如果窗口大小为偶数，返回两个中间值的平均值
     */
    float getMedianNaive() const {
        auto window = _window;
        window.sort();  /// 排序窗口 - O(NlogN)
        auto median =
            *next(window.begin(),
                  window.size() / 2);  /// 查找中间位置的值 - O(N)
        if (window.size() % 2 != 0) {
            return median;
        }
        return 0.5f * median +
               0.5f * *next(window.begin(), window.size() / 2 - 1);  /// O(N)
    }
};
}  // namespace windowed_median
}  // namespace probability

/**
 * @brief 自测实现
 * @param vals 数值流
 * @param windowSize 滑动窗口大小
 */
static void test(const std::vector<int> &vals, int windowSize) {
    probability::windowed_median::WindowedMedian windowedMedian(windowSize);
    for (const auto val : vals) {
        windowedMedian.insert(val);

        /// 比较高效方法与低效方法计算的中位数
        assert(windowedMedian.getMedian() == windowedMedian.getMedianNaive());
    }
}

/**
 * @brief 主函数
 * @param argc 命令行参数个数（忽略）
 * @param argv 命令行参数数组（忽略）
 * @returns 0 退出
 */
int main(int argc, const char *argv[]) {
    /// 一些固定的测试案例
    test({1, 2, 3, 4, 5, 6, 7, 8, 9},
         3);  /// 排序的数值数组，奇数窗口大小
    test({9, 8, 7, 6, 5, 4, 3, 2, 1},
         3);  /// 排序的数值数组，递减；奇数窗口大小
    test({9, 8, 7, 6, 5, 4, 5, 6}, 4);     /// 偶数窗口大小
    test({3, 3, 3, 3, 3, 3, 3, 3, 3}, 3);  /// 重复值的数组
    test({3, 3, 3, 3, 7, 3, 3, 3, 3}, 3);  /// 除一个值外都是相同的值
    test({4, 3, 3, -5, -5, 1, 3, 4, 5},
         5);  /// 包含重复值的数组，包括负数

    /// 包含大值的数组 - 几对数值的和超过了 MAX_INT。窗口大小为偶数，测试计算两个中间值的平均中位数
    test({470211272, 101027544, 1457850878, 1458777923, 2007237709, 823564440,
          1115438165, 1784484492, 74243042, 114807987},
         6);

    /// 随机测试案例
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<int> vals;
    for (int i = 8; i < 100; i++) {
        const auto n =
            1 + std::rand() /
                    ((RAND_MAX + 5u) / 20);  /// 数组大小范围为 [5, 20]
        auto windowSize =
            1 + std::rand() / ((RAND_MAX + 3u) / 10);  /// 窗口大小范围为 [3, 10]
        vals.clear();
        vals.reserve(n);
        for (int i = 0; i < n; i++) {
            vals.push_back(rand() - RAND_MAX);  /// 随机数组值（包括正负数）
        }
        test(vals, windowSize);  /// 测试随机测试案例
    }
    return 0;
}
