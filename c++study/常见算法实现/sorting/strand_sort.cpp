/**
 * @file strand_sort.cpp
 * @brief 实现 [Strand Sort](https://en.wikipedia.org/wiki/Strand_sort) 算法。
 *
 * @details
 * Strand Sort 是一种排序算法，当列表已经排序时，它的时间复杂度是 \f$O(n)\f$，
 * 而在最坏情况下，它的时间复杂度是 \f$O(n^2)\f$。
 * 
 * 它通过遍历待排序的数组，提取升序的（顺序）数字。
 * 在第一次迭代后，顺序的子数组会被放置到一个空的已排序数组中。
 * 主序列会再次遍历并创建一个新的子序列，并按顺序进行合并。
 * 由于已排序数组不再为空，所以新的提取子串会与已排序数组进行合并。
 * 重复执行第3步和第4步，直到子序列和主序列都为空。
 * 
 * @author [Mertcan Davulcu](https://github.com/mertcandav)
 */
#include <iostream>
#include <list>

/**
 * @namespace sorting
 * @brief 排序算法
 */
namespace sorting {
    /**
    * @namespace strand
    * @brief [Strand Sort](https://en.wikipedia.org/wiki/Strand_sort) 算法相关函数
    */
    namespace strand {
        /**
        * @brief 执行排序操作
        * @tparam T 列表元素类型
        * @param lst 要排序的列表
        * @returns 排序后的列表
        */
        template <typename T>
        std::list<T> strand_sort(std::list<T> lst) {
            if (lst.size() < 2) { // 如果列表为空或只有一个元素，直接返回
                return lst; // 返回列表
            }
            std::list<T> result; // 定义一个名为 "result" 的新列表实例
            std::list<T> sorted; // 定义一个名为 "sorted" 的新列表实例
            while(!lst.empty()) /* 如果 lst 不为空 */ {
                sorted.push_back(lst.front()); // 将 "lst" 列表的第一个元素添加到 "sorted" 列表的末尾
                lst.pop_front(); // 从 "lst" 列表中删除第一个元素
                for (auto it = lst.begin(); it != lst.end(); ) { // 遍历 "lst" 列表直到最后一个元素
                    if (sorted.back() <= *it) { // 如果 "sorted" 列表的最后一个元素小于或等于当前迭代器所指向的元素
                        sorted.push_back(*it); // 将当前迭代器所指向的元素添加到 "sorted" 列表
                        it = lst.erase(it); // 删除当前迭代器指向的元素，并将迭代器指向被删除元素的下一个位置
                    } else {
                        it++; // 如果不满足条件，继续迭代
                    }
                }
                result.merge(sorted); // 将 "sorted" 列表合并到 "result" 列表中
            }
            return result; // 返回已排序的列表
        }
    }  // namespace strand
}  // namespace sorting

/**
 * @brief 测试函数
 * @return 无返回值
 */
static void test() {
    std::list<int> lst = { -333, 525, 1, 0, 94, 52, 33 };

    std::cout << "排序前: ";
    for(auto item: lst) {
        std::cout << item << " "; // 输出排序前的列表
    }

    lst = sorting::strand::strand_sort(lst); // 调用 Strand Sort 对列表进行排序

    std::cout << "\n排序后: ";
    for(auto item: lst) {
        std::cout << item << " "; // 输出排序后的列表
    }
}

/**
 * @brief 主函数
 * @returns 0 表示程序正常退出
 */
int main() {
    test(); // 调用测试函数
    return 0;
}
