/**
 * @file
 * @brief 实现 [反转单链表](https://simple.wikipedia.org/wiki/Linked_list)
 * @details 链表是一种用于存储一系列值的数据结构，可以添加、显示、反转或删除值。
 * ### 算法
 * 值可以通过从第一个链接开始迭代到链表的末尾（沿着指针）来添加。指向空的链接被认为是最后一个链接，并指向新的值。
 *
 * 链表可以使用3个指针进行反转：current、previous 和 next_node；我们不断迭代直到最后一个节点。在此过程中，在更改 current 的下一个指针之前，我们将其存储在 next_node 指针中，然后将 prev 指针存储在 next 的 current 中，这里发生实际的反转。然后我们将 prev 和 current 指针向前移动一步。最后，在迭代完成后，头节点被设置为指向最后一个节点（prev 指针）。

 * [图形解释及其背后的操作](https://drive.google.com/file/d/1pM5COF0wx-wermnNy_svtyZquaCUP2xS/view?usp=sharing)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作
#include <new>       /// 用于管理动态存储

/**
 * @namespace data_structures
 * @brief 数据结构算法
 */
namespace data_structures {
/**
 * @namespace linked_list
 * @brief 单链表算法的函数
 */
namespace linked_list {
/**
 * 节点类，包含值和指向下一个链接的指针
 */
class Node {
 public:
    int32_t val;  /// 当前链接的值
    Node* next;   /// 指向链表下一个值的指针
};

/**
 *  @brief 创建从输入节点开始的链表的深拷贝
 *  @param[in] node 指向要复制的链表第一个节点/头节点的指针
 *  @return 指向复制链表第一个节点/头节点的指针，如果为空则返回nullptr
 */
Node* copy_all_nodes(const Node* const node) {
    if (node) {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        Node* res = new Node();
        res->val = node->val;            // 复制当前节点的值
        res->next = copy_all_nodes(node->next);  // 递归复制下一个节点
        return res;
    }
    return nullptr;  // 如果节点为空，返回nullptr
}

/**
 *  @brief 列表类，包含一系列链接
 */
// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class list {
 private:
    Node* head = nullptr;  // 实际第一个元素之前的链接
    void delete_all_nodes();  // 删除所有节点
    void copy_all_nodes_from_list(const list& other);  // 从其他列表复制节点

 public:
    bool isEmpty() const;  // 检查列表是否为空
    void insert(int32_t new_elem);  // 在列表末尾插入新元素
    void reverseList();  // 反转链表
    void display() const;  // 显示链表内容
    int32_t top() const;  // 获取链表的第一个元素
    int32_t last() const;  // 获取链表的最后一个元素
    int32_t traverse(int32_t index) const;  // 获取链表第i个元素
    ~list();  // 析构函数
    list() = default;  // 默认构造函数
    list(const list& other);  // 拷贝构造函数
    list& operator=(const list& other);  // 赋值操作符重载
};

/**
 * @brief 检查列表是否为空的实用函数
 * @returns 如果列表为空返回true
 * @returns 如果列表不为空返回false
 */
bool list::isEmpty() const { return head == nullptr; }

/**
 * @brief 在列表末尾添加新元素的实用函数
 * @param new_elem 要添加到列表末尾的元素
 */
void list::insert(int32_t n) {
    try {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        Node* new_node = new Node();  // 创建新节点
        Node* temp = nullptr;          // 临时节点指针
        new_node->val = n;             // 设置新节点的值
        new_node->next = nullptr;      // 新节点的下一个指针设置为空
        if (isEmpty()) {               // 如果列表为空
            head = new_node;           // 头指针指向新节点
        } else {
            temp = head;               // 从头节点开始迭代
            while (temp->next != nullptr) {  // 遍历到链表末尾
                temp = temp->next;
            }
            temp->next = new_node;     // 将新节点添加到链表末尾
        }
    } catch (std::bad_alloc& exception) {
        std::cerr << "bad_alloc detected: " << exception.what() << "\n";  // 捕获内存分配异常
    }
}

/**
 * @brief 反转链表的实用函数
 * @brief 使用当前、前一个和下一个指针。
 * @returns void
 */
void list::reverseList() {
    Node* curr = head;      // 当前节点指针
    Node* prev = nullptr;   // 前一个节点指针
    Node* next_node = nullptr; // 下一个节点指针
    while (curr != nullptr) {  // 迭代直到当前节点为空
        next_node = curr->next;  // 保存下一个节点
        curr->next = prev;      // 反转当前节点的指针
        prev = curr;            // 移动前一个节点指针
        curr = next_node;       // 移动当前节点指针
    }
    head = prev;               // 更新头指针指向新的头节点
}

/**
 * @brief 获取列表的第一个元素
 * @returns 列表的第一个元素
 */
int32_t list::top() const {
    if (!isEmpty()) {
        return head->val;  // 返回头节点的值
    } else {
        throw std::logic_error("List is empty");  // 如果列表为空，抛出异常
    }
}

/**
 *  @brief 获取列表的最后一个元素
 *  @returns 列表的最后一个元素
 */
int32_t list::last() const {
    if (!isEmpty()) {
        Node* t = head;   // 临时指针从头节点开始
        while (t->next != nullptr) {  // 遍历到链表末尾
            t = t->next;
        }
        return t->val;     // 返回最后一个节点的值
    } else {
        throw std::logic_error("List is empty");  // 如果列表为空，抛出异常
    }
}

/**
 *  @brief 获取链表的第i个元素
 *  @returns 第i个元素
 */
int32_t list::traverse(int32_t index) const {
    Node* current = head;  // 当前节点从头节点开始
    int count = 0;         // 计数器初始化
    while (current != nullptr) {  // 遍历链表
        if (count == index) {  // 如果计数器等于索引
            return (current->val);  // 返回当前节点的值
        }
        count++;
        current = current->next;  // 移动到下一个节点
    }

    // 如果到达此行，表示请求了不存在的元素，故断言失败
    exit(1);
}

/**
 *  @brief 删除链表中每个节点
 */
void list::delete_all_nodes() {
    while (head != nullptr) {
        const auto tmp_node = head->next;  // 保存下一个节点
        delete head;                        // 删除当前头节点
        head = tmp_node;                    // 更新头指针
    }
}

list::~list() { delete_all_nodes(); }  // 析构函数实现，调用删除所有节点的函数

void list::copy_all_nodes_from_list(const list& other) {
    assert(isEmpty());  // 确保当前列表为空
    head = copy_all_nodes(other.head);  // 从其他列表复制节点
}

/**
 *  @brief 拷贝构造函数，创建输入链表每个节点的深拷贝
 */
list::list(const list& other) { copy_all_nodes_from_list(other); }

/**
 *  @brief 赋值操作符重载，创建输入链表每个节点的深拷贝
 */
list& list::operator=(const list& other) {
    if (this == &other) {  // 如果是自我赋值
        return *this;      // 直接返回
    }
    delete_all_nodes();   // 删除当前链表的所有节点
    copy_all_nodes_from_list(other);  // 从其他列表复制节点
    return *this;         // 返回当前对象
}

}  // namespace linked_list
}  // namespace data_structures

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    data_structures::linked_list::list L;  // 创建一个链表实例
    // 第一个测试
    L.insert(11);
    L.insert(12);
    L.insert(15);
    L.insert(10);
    L.insert(-12);
    L.insert(-20);
    L.insert(18);
    assert(L.top() == 11);  // 检查第一个元素
    assert(L.last() == 18);  // 检查最后一个元素
    L.reverseList();  // 反转链表
    // 反转测试
    assert(L.top() == 18);  // 检查反转后的第一个元素
    assert(L.traverse(1) == -20);  // 检查反转后的第二个元素
    assert(L.traverse(2) == -12);  // 检查反转后的第三个元素
    assert(L.traverse(3) == 10);   // 检查反转后的第四个元素
    assert(L.traverse(4) == 15);   // 检查反转后的第五个元素
    assert(L.traverse(5) == 12);   // 检查反转后的第六个元素
    assert(L.last() == 11);  // 检查反转后的最后一个元素
    std::cout << "所有测试都成功通过!" << std::endl;  // 输出测试成功信息
}

void test_copy_constructor() {
    data_structures::linked_list::list L;  // 创建一个链表实例
    L.insert(10);
    L.insert(20);
    L.insert(30);
    data_structures::linked_list::list otherList(L);  // 使用拷贝构造函数创建另一个链表
    otherList.insert(40);  // 向复制的链表中插入元素

    L.insert(400);  // 向原始链表中插入元素

    assert(L.top() == 10);  // 检查第一个元素
    assert(otherList.top() == 10);  // 检查复制链表的第一个元素
    assert(L.traverse(1) == 20);  // 检查第二个元素
    assert(otherList.traverse(1) == 20);  // 检查复制链表的第二个元素

    assert(L.traverse(2) == 30);  // 检查第三个元素
    assert(otherList.traverse(2) == 30);  // 检查复制链表的第三个元素

    assert(L.last() == 400);  // 检查最后一个元素
    assert(otherList.last() == 40);  // 检查复制链表的最后一个元素
}

void test_assignment_operator() {
    data_structures::linked_list::list L;  // 创建一个链表实例
    data_structures::linked_list::list otherList;  // 创建另一个链表实例
    L.insert(10);
    L.insert(20);
    L.insert(30);
    otherList = L;  // 赋值操作

    otherList.insert(40);  // 向复制的链表中插入元素
    L.insert(400);  // 向原始链表中插入元素

    assert(L.top() == 10);  // 检查第一个元素
    assert(otherList.top() == 10);  // 检查复制链表的第一个元素
    assert(L.traverse(1) == 20);  // 检查第二个元素
    assert(otherList.traverse(1) == 20);  // 检查复制链表的第二个元素

    assert(L.traverse(2) == 30);  // 检查第三个元素
    assert(otherList.traverse(2) == 30);  // 检查复制链表的第三个元素

    assert(L.last() == 400);  // 检查最后一个元素
    assert(otherList.last() == 40);  // 检查复制链表的最后一个元素
}

/**
 * @brief 主函数
 * @returns 0 正常退出
 */
int main() {
    test();  // 运行自测实现
    test_copy_constructor();  // 测试拷贝构造函数
    test_assignment_operator();  // 测试赋值操作符
    return 0;  // 返回成功
}
