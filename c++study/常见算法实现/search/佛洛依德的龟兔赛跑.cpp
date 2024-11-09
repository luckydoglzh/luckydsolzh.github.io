/**
 * @file
 * @brief 给定一个链表 L[0,....,n]，找出中间节点。
 *
 * @details 本实现采用了 ["佛洛伊德的龟兔赛跑"](https://en.wikipedia.org/wiki/Cycle_detection#Floyd's_tortoise_and_hare) 方法。
 * 该方法使用两个指针以不同的速度遍历链表。每次迭代中，慢指针移动一步，而快指针移动两步。因为快指针移动速度是慢指针的两倍，
 * 所以当快指针到达链表末尾时，慢指针恰好指向链表的中间节点。
 *
 * 这里有一些示例列表，你可以用来查看算法的工作方式：
 * A = [1,2,3,4,5]
 * B = [1,2,3,4,5,6]
 * print median(A)  # 应该是 3
 * print median(B)  # 应该是 4
 *
 * @author [Benjamin Weiss](https://github.com/weiss-ben)
 * @see median_search.cpp
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作

/**
 * 单链表节点定义
 */
struct ListNode {
    int val{0};               ///< 节点存储的值
    ListNode* next{nullptr};  ///< 指向下一个节点的指针
    ListNode() = default;     ///< 默认构造函数
    explicit ListNode(int x)
        : val(x) {}  ///< 提供值的构造函数
    ListNode(int x, ListNode* next)
        : val(x),
          next(next) {
    }  ///< 提供值和下一个节点指针的构造函数
};

/**
 * @namespace search
 * @brief 搜索算法
 */
namespace search {
/**
 * @namespace median_search2
 * @brief 中位数查找算法实现
 */
namespace median_search2 {
/**
 * 该函数查找链表的中位数节点。
 * @param head 链表的头节点。
 * @returns 链表的中位数节点。
 */
ListNode* middleNode(ListNode* head) {
    if (!head) {
        return nullptr;  // 如果链表为空，返回nullptr
    }

    // 定义快慢指针
    ListNode* fastptr = nullptr;
    ListNode* slowptr = fastptr = head;

    // 快指针每次跳跃两步，慢指针每次跳跃一步
    while (fastptr->next && fastptr->next->next) {
        slowptr = slowptr->next;          // 慢指针向前移动一步
        fastptr = fastptr->next->next;    // 快指针向前移动两步
    }

    // 如果快指针的下一个节点为空，说明链表长度为奇数，慢指针就是中位数
    return (fastptr->next) ? slowptr->next : slowptr;
}

/**
 * 递归删除链表所有节点
 * @param head 链表的头节点
 */
void deleteAll(const ListNode* const head) {
    if (head) {
        deleteAll(head->next);  // 递归删除下一个节点
        delete head;            // 删除当前节点
    }
}
}  // namespace median_search2
}  // namespace search

/**
 * @brief 自我测试实现
 * @returns void
 */
static void test() {
    // 测试案例 1：链表为 [1, 2, 3, 4, 5]
    auto* head1 = new ListNode;
    head1->val = 1;

    ListNode* temp = head1;
    for (int i = 2; i < 6; ++i) {
        // 创建下一个节点并赋值
        auto* temp1 = new ListNode;
        temp1->val = i;

        // 更新链表指向
        temp->next = temp1;
        temp = temp1;
    }
    temp->next = nullptr;  // 最后一个节点的 next 指向 null

    // 查找中位数节点并验证
    const ListNode* const median = search::median_search2::middleNode(head1);
    assert(3 == median->val);  // 3 是链表中位数节点的值
    search::median_search2::deleteAll(head1);  // 删除链表节点
    std::cout << "测试案例 1 通过\n";

    // 测试案例 2：链表为 [1, 2, 3, 4, 5, 6]
    auto* head2 = new ListNode;
    head2->val = 1;

    ListNode* temp2 = head2;
    for (int i = 2; i < 7; ++i) {
        // 创建下一个节点并赋值
        auto* temp3 = new ListNode;
        temp3->val = i;

        // 更新链表指向
        temp2->next = temp3;
        temp2 = temp3;
    }
    temp2->next = nullptr;  // 最后一个节点的 next 指向 null

    // 查找中位数节点并验证
    const ListNode* const median1 = search::median_search2::middleNode(head2);
    assert(4 == median1->val);  // 4 是链表中位数节点的值
    search::median_search2::deleteAll(head2);  // 删除链表节点
    std::cout << "测试案例 2 通过\n";

    std::cout << "--所有测试通过--\n";
}

/**
 * @brief 主函数
 * @returns 0
 */
int main() {
    test();  // 执行自我测试
    return 0;
}
