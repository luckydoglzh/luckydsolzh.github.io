/**
 * @file
 * @brief 实现一个 [循环链表](https://www.geeksforgeeks.org/circular-linked-list/)。
 * @details 循环链表是常规链表的变种，其中最后一个节点指向第一个节点，从而形成一个完整的圆圈。因此，任何节点都可以作为链表的起始节点。
 * @author [Alvin](https://github.com/polarvoid)
 */

#include <cassert>   /// 用于 assert
#include <iostream>  /// 用于输入输出操作
#include <vector>    /// 用于 std::vector

/**
 * @namespace operations_on_datastructures
 * @brief 数据结构操作
 */
namespace operations_on_datastructures {

/// @namespace circular_linked_list
/// @brief 循环链表实现的函数
namespace circular_linked_list {

/**
 * @brief Node 结构体，表示二叉树中的一个节点
 */
struct Node {
    int64_t data;  ///< 节点的值
    Node* next;    ///< 节点的后继节点
    /**
     * @brief 创建一个新的节点，并赋初值
     * @param _data 节点的值
     */
    explicit Node(int64_t _data) {
        data = _data;    ///< 设置节点数据
        next = nullptr;  ///< 初始化后继指针为 null
    }
    /**
     * @brief 创建一个新的节点，并赋初值和后继节点
     * @param _data 节点的值
     * @param _next 指向下一个节点的指针
     */
    explicit Node(int64_t _data, Node* _next) {
        data = _data;  ///< 设置节点数据
        next = _next;  ///< 设置节点的后继节点
    }
};

/**
 * @brief 实现循环链表的类
 */
class CircularLinkedList {
 private:
    Node* root;   ///< 指向根节点的指针
    Node* end{};  ///< 指向最后一个节点的指针

 public:
    /**
     * @brief 创建一个空的循环链表
     */
    CircularLinkedList() {
        root = nullptr;
        end = nullptr;
    }
    /**
     * @brief 循环链表的复制构造函数
     */
    CircularLinkedList(const CircularLinkedList& copy) {
        erase();
        root = nullptr;
        Node* node = copy.root;
        while (node != nullptr) {
            insert(node->data);
            node = node->next;
        }
    }
    /**
     * @brief 循环链表的移动构造函数
     * @param source rvalue 引用，指向另一个循环链表
     */
    CircularLinkedList(CircularLinkedList&& source) noexcept {
        root = source.root;
        end = source.end;
        source.root = nullptr;
        source.end = nullptr;
    }
    /**
     * @brief 复制赋值运算符
     * @param other 循环链表的引用
     * @returns 循环链表的引用
     */
    CircularLinkedList& operator=(const CircularLinkedList& other) {
        erase();
        root = nullptr;
        Node* node = other.root;
        while (node != nullptr) {
            insert(node->data);
            node = node->next;
        }
        return *this;
    }
    /**
     * @brief 移动赋值运算符
     * @param other rvalue 引用，指向另一个循环链表
     * @returns 循环链表的引用
     */
    CircularLinkedList& operator=(CircularLinkedList&& other) noexcept {
        root = other.root;
        end = other.end;
        other.root = nullptr;
        other.end = nullptr;
        return *this;
    }
    /**
     * @brief 析构函数，清理内存
     */
    ~CircularLinkedList() { erase(); }
    /**
     * @brief 迭代地释放循环链表中的每个节点
     */
    void erase() {
        if (root == nullptr) {
            return;
        }
        Node* node = root;
        do {
            Node* temp = node;
            node = node->next;
            delete (temp);
        } while (node != root);
        root = nullptr;
        end = nullptr;
    }
    /**
     * @brief 将一个整数数组中的所有值插入到循环链表中
     * @details 按顺序遍历数组中的每个元素，将它们插入链表
     * @param values 需要插入的整数值的数组
     * @returns void
     */
    void insert(const std::vector<int64_t>& values) {
        for (int64_t value : values) {
            insert(value);
        }
    }
    /**
     * @brief 将一个整数值插入到循环链表中
     * @details 创建一个新的节点，并指向根节点，将其插入链表
     * @param data 需要插入的整数值
     * @returns void
     */
    void insert(int64_t data) {
        Node* node = new Node(data, root);
        insert(node);
    }
    /**
     * @brief 将给定的节点插入到循环链表中
     * @details 检查链表是否为空，如果为空，则插入节点，并设置根节点和尾节点
     * @param node 需要插入的节点
     * @returns void
     */
    void insert(Node* node) {
        if (root == nullptr) {
            root = node;        ///< 设置节点为根节点
            node->next = root;  ///< 节点指向自己，形成环
            end = root;         ///< 设置尾节点为根节点
        } else {
            end->next = node;   ///< 将节点添加到链表尾部
            node->next = root;  ///< 设置节点的下一个指针指向根节点
            end = node;         ///< 更新尾节点
        }
    }
    /**
     * @brief 打印循环链表的所有值，从根节点开始
     * @details 遍历链表中的每个节点，按顺序打印节点的数据
     * @returns void
     */
    void print() { print(root); }
    /**
     * @brief 打印循环链表的所有值，从指定的节点开始
     * @details 从给定节点开始，遍历链表并打印所有节点的值。如果链表为空，打印“空链表！”
     * @param root 起始节点
     * @returns void
     */
    void print(Node* root) {
        Node* temp = root;
        if (root == nullptr) {
            std::cout << "空链表！\n";
            return;
        }
        do {
            std::cout << temp->data << " ";
            temp = temp->next;
        } while (temp != root);
        std::cout << "\n";
    }
    /**
     * @brief 返回一个包含循环链表所有值的 std::vector
     * @details 从根节点开始，遍历链表，将每个节点的值存入一个 std::vector 中并返回
     * @returns 包含链表值的 std::vector
     */
    std::vector<int64_t> values() { return values(root); }
    /**
     * @brief 返回一个包含循环链表所有值的 std::vector，从指定的节点开始
     * @details 从指定节点开始，遍历链表，将每个节点的值存入一个 std::vector 中并返回
     * @param root 起始节点
     * @returns 包含链表值的 std::vector
     */
    std::vector<int64_t> values(Node* root) {
        std::vector<int64_t> res;
        if (root == nullptr) {
            return res;  ///< 如果链表为空，返回空向量
        }
        Node* temp = root;
        do {
            res.push_back(temp->data);
            temp = temp->next;
        } while (temp != root);
        return res;
    }
};

}  // namespace circular_linked_list

}  // namespace operations_on_datastructures

/**
 * @namespace tests
 * @brief 测试用例，检查循环链表的功能
 */
namespace tests {
using operations_on_datastructures::circular_linked_list::CircularLinkedList;
using operations_on_datastructures::circular_linked_list::Node;
/**
 * @brief 测试单个节点的插入
 * @returns void
 */
void test1() {
    std::cout << "测试用例 1\n";
    std::cout << "初始化 a = {2}\n";
    std::cout << "期望结果: {2}\n";
    CircularLinkedList a;
    std::vector<int64_t> res = {2};
    a.insert(2);
    assert(a.values() == res);
    a.print();
    std::cout << "测试通过！\n\n";
}
/**
 * @brief 测试多个节点的插入
 * @returns void
 */
void test2() {
    std::cout << "测试用例 2\n";
    std::cout << "初始化 a = {2, 5, 6}\n";
    std::cout << "期望结果: {2, 5, 6}\n";
    CircularLinkedList a;
    std::vector<int64_t> res = {2, 5, 6};
    a.insert(2);
    a.insert(5);
    a.insert(6);
    assert(a.values() == res);
    a.print();
    std::cout << "测试通过！\n\n";
}
/**
 * @brief 测试输入数组的插入
 * @returns void
 */
void test3() {
    std::cout << "测试用例 3\n";
    std::cout << "初始化 a = {2, 7, 8, 3, 2, 6}\n";
    std::cout << "期望结果: {2, 7, 8, 3, 2, 6}\n";
    CircularLinkedList a;
    std::vector<int64_t> res = {2, 7, 8, 3, 2, 6};
    a.insert({2, 7, 8, 3, 2, 6});
    a.print();
    assert(a.values() == res);
    std::cout << "测试通过！\n\n";
}
/**
 * @brief 测试从指定节点开始打印
 * @returns void
 */
void test4() {
    std::cout << "测试用例 4\n";
    std::cout << "初始化 a = {2, 5}\n";
    std::cout << "期望结果: {5, 2}\n";
    CircularLinkedList a;
    std::vector<int64_t> res = {5, 2};
    a.insert(2);
    Node* start = new Node(5);  ///< 使用指定节点作为起始节点
    a.insert(start);
    assert(a.values(start) == res);
    a.print(start);
    std::cout << "测试通过！\n\n";
}

/**
 * @brief 测试空链表
 * @returns void
 */
void test5() {
    std::cout << "测试用例 5\n";
    std::cout << "初始化 a = {}\n";
    std::cout << "期望结果: 空链表！\n";
    CircularLinkedList a;
    std::vector<int64_t> res = {};
    assert(a.values() == res);
    a.print();
    std::cout << "测试通过！\n\n";
}
}  // namespace tests

/**
 * @brief 测试函数，验证循环链表的正确性
 * @returns void
 */
static void test() {
    tests::test1();
    tests::test2();
    tests::test3();
    tests::test4();
    tests::test5();
}

/**
 * @brief 主函数
 * @returns 0
 */
int main() {
    test();  // 执行测试用例
    return 0;
}
