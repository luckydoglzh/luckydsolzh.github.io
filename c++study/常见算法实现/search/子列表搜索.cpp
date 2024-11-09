/**
 * @file
 * @brief 实现了 [子列表搜索算法](https://www.geeksforgeeks.org/sublist-search-search-a-linked-list-in-another-list)
 * @details
 *
 * ### 算法
 *
 *  * 子列表搜索用于检测一个列表是否出现在另一个列表中。
 *  * 假设我们有一个单节点列表（假设为第一个列表），然后我们想确保该列表在另一个列表（假设为第二个列表）中存在，
 *    那么我们可以执行子列表搜索来查找它。
 *
 *  * 例如，第一个列表包含这些元素：23 -> 30 -> 41，
 *    第二个列表包含这些元素：10 -> 15 -> 23 -> 30 -> 41 -> 49。我们可以看到第一个列表出现在第二个列表中。
 *
 * ### 工作原理
 *
 *  * 子列表搜索算法通过将第一个列表的第一个元素与第二个列表的第一个元素进行比较来工作。
 *  * 如果两个值不匹配，它将移动到第二个列表的下一个元素，直到两个值匹配。
 *
 * @author [Nitin Sharma](https://github.com/foo290)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于std::vector

/**
 * @namespace search
 * @brief 搜索算法
 */
namespace search {
/**
 * @namespace sublist_search
 * @brief 实现 [子列表搜索](https://www.geeksforgeeks.org/sublist-search-search-a-linked-list-in-another-list) 的函数
 */
namespace sublist_search {
/**
 * @brief 一个表示单链表节点的结构体
 */
struct Node {
    uint32_t data = 0;  ///< 节点的值
    Node *next{};       ///< 指向下一个节点的指针
};

/**
 * @brief 打印链表的简单函数
 * @param start 链表的头指针
 * @returns void
 */
void printLinkedList(Node *start) {
    while (start != nullptr) {
        std::cout << "->" << start->data;
        start = start->next;
    }
    std::cout << std::endl;
}

/**
 * @brief 给定一个数据的向量，
 * 将每个元素添加到链表中并返回链表的头指针
 * @param data 一个包含要存储在链表节点中的数据的整数向量
 * @returns Node* 链表的头指针
 */
Node *makeLinkedList(const std::vector<uint64_t> &data) {
    Node *head = nullptr;
    Node *tail = nullptr;
    for (int i : data) {
        Node *node = new Node;
        node->data = i;
        node->next = nullptr;
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = tail->next;
        }
    }
    return head;
}

/**
 * @brief 递归删除链表的所有节点
 * @param room 链表的根/头节点
 * @warning 请注意，每个节点的内存必须使用 new 分配。
 */
void deleteList(Node *const root) {
    if (root != NULL) {
        deleteList(root->next);
        delete root;
    }
}

/**
 * @brief 主搜索函数
 * @param sublist 要在主列表中搜索的子链表
 * @param mainList 主链表
 * @returns 如果子链表被找到，返回true
 * @returns 如果子链表没有找到，返回false
 */
bool sublistSearch(Node *sublist, Node *mainList) {
    if (sublist == nullptr || mainList == nullptr) {
        return false;
    }

    // 初始化目标指针指向子链表的头节点
    Node *target_ptr = sublist;

    while (mainList != nullptr) {
        // 初始化主链表指针指向当前主链表节点
        Node *main_ptr = mainList;

        while (target_ptr != nullptr) {
            if (main_ptr == nullptr) {
                return false;
            } else if (main_ptr->data == target_ptr->data) {
                // 如果主链表节点和子链表节点的数据相等，则同时移动两个指针到下一个节点
                target_ptr = target_ptr->next;
                main_ptr = main_ptr->next;
            } else {
                break;
            }
        }

        if (target_ptr == nullptr) {
            // 如果目标指针为null，说明已经遍历完整个子链表且没有返回false，表示找到了子链表
            return true;
        }

        // 重置目标指针到子链表的头节点
        target_ptr = sublist;

        // 将主链表指针移动到下一个节点，继续重复上述过程
        mainList = mainList->next;
    }

    // 如果遍历完整个主链表仍未找到子链表，则返回false
    return false;
}

}  // namespace sublist_search
}  // namespace search

/**
 * @brief 包含必要测试用例的类
 */
class TestCases {
 private:
    /**
     * @brief 打印给定的消息
     * @tparam T 消息类型
     * @returns void
     */
    template <typename T>
    void log(T msg) {
        std::cout << "[TESTS] : ---> " << msg << std::endl;
    }

 public:
    /**
     * @brief 执行所有测试用例
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
     * @brief 测试用例1，包含边界情况，仅包含一个元素
     * @returns void
     */
    void testCase_1() {
        const bool expectedOutput = true;  ///< 期望的输出

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("这是子列表搜索算法的测试用例1：");
        log("描述:");
        log("   边界情况：仅包含一个元素");

        std::vector<uint64_t> sublistData = {6};  ///< 子链表数据
        std::vector<uint64_t> mainlistData = {2, 5, 6, 7, 8};  ///< 主链表数据

        search::sublist_search::Node *sublistLL = search::sublist_search::makeLinkedList(sublistData);
        search::sublist_search::Node *mainlistLL = search::sublist_search::makeLinkedList(mainlistData);

        bool exists = search::sublist_search::sublistSearch(sublistLL, mainlistLL);

        log("检查断言表达式...");
        assert(exists == expectedOutput);
        log("断言检查通过!");

        log("[PASS] : 测试用例1通过!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");

        deleteList(mainlistLL);
        deleteList(sublistLL);
    }

    /**
     * @brief 测试用例2，主链表包含100个元素，子链表包含20个元素
     * @returns void
     */
    void testCase_2() {
        const bool expectedOutput = true;  ///< 期望的输出

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("这是子列表搜索算法的测试用例2：");
        log("描述:");
        log("   主链表包含100个元素，子链表包含20个元素");

        std::vector<uint64_t> sublistData(20);  ///< 子链表数据
        std::vector<uint64_t> mainlistData(100);  ///< 主链表数据

        for (int i = 0; i < 100; i++) {
            mainlistData[i] = i + 1;  ///< 将100个元素添加到主链表中
        }

        int temp = 0;
        for (int i = 45; i < 65; i++) {
            sublistData[temp] = i + 1;  ///< 将20个元素添加到子链表中
            temp++;
        }

        search::sublist_search::Node *sublistLL = search::sublist_search::makeLinkedList(sublistData);
        search::sublist_search::Node *mainlistLL = search::sublist_search::makeLinkedList(mainlistData);

        bool exists = search::sublist_search::sublistSearch(sublistLL, mainlistLL);

        log("检查断言表达式...");
        assert(exists == expectedOutput);
        log("断言检查通过!");

        log("[PASS] : 测试用例2通过!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");

        deleteList(mainlistLL);
        deleteList(sublistLL);
    }

    /**
     * @brief 测试用例3，主链表包含50个元素，子链表包含20个元素
     * @returns void
     */
    void testCase_3() {
        const bool expectedOutput = false;  ///< 期望的输出

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("这是子列表搜索算法的测试用例3：");
        log("描述:");
        log("   主链表包含50个元素，子链表包含20个元素");

        std::vector<uint64_t> sublistData(20);  ///< 子链表数据
        std::vector<uint64_t> mainlistData(50);  ///< 主链表数据

        for (int i = 0; i < 50; i++) {
            mainlistData[i] = i + 1;  ///< 将50个元素添加到主链表中
        }

        int temp = 0;
        for (int i = 25; i < 45; i++) {
            sublistData[temp] = i + 1;  ///< 将20个元素添加到子链表中
            temp++;
        }

        search::sublist_search::Node *sublistLL = search::sublist_search::makeLinkedList(sublistData);
        search::sublist_search::Node *mainlistLL = search::sublist_search::makeLinkedList(mainlistData);

        bool exists = search::sublist_search::sublistSearch(sublistLL, mainlistLL);

        log("检查断言表达式...");
        assert(exists == expectedOutput);
        log("断言检查通过!");

        log("[PASS] : 测试用例3通过!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");

        deleteList(mainlistLL);
        deleteList(sublistLL);
    }
};

/**
 * @brief 入口函数
 * @returns int 执行状态
 */
int main() {
    TestCases tests;
    tests.runTests();
    return 0;
}
