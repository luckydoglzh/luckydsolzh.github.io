/**
 * @file
 * @brief 实现 [反转二叉树](https://www.geeksforgeeks.org/reverse-tree-path/) 的递归算法。
 * @details 二叉树可以通过在每个节点上交换左右子节点的方式反转，反转从根节点开始，逐层传递。此解决方案提供了一个递归反转二叉树的实现。
 * @author [Alvin](https://github.com/polarvoid)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作
#include <queue>     /// 用于 std::queue
#include <vector>    /// 用于 std::vector

/**
 * @namespace operations_on_datastructures
 * @brief 数据结构上的操作
 */
namespace operations_on_datastructures {

/// @namespace reverse_binary_tree
/// @brief 实现 [反转二叉树](https://www.geeksforgeeks.org/reverse-tree-path/) 的相关功能
namespace reverse_binary_tree {

/**
 * @brief 表示二叉树单个节点的结构体
 */
struct Node {
    int64_t data;  ///< 节点的值
    Node* left;    ///< 左子节点指针
    Node* right;   ///< 右子节点指针
    /**
     * @brief 创建一个新节点，并初始化数据
     */
    explicit Node(int64_t _data) {
        data = _data;     ///< 设置节点的值
        left = nullptr;   ///< 初始化左子节点为空
        right = nullptr;  ///< 初始化右子节点为空
    }
};

/**
 * @brief 二叉树类，实现了一个二叉搜索树（BST）
 */
class BinaryTree {
 private:
    Node* root;  ///< 二叉树的根节点指针
    /**
     * @brief 插入节点到二叉树中，行为类似于二叉搜索树
     * @details 小于等于当前节点值的节点插入到左子树，大于当前节点值的节点插入到右子树。时间复杂度：O(log(n))
     * @param data 要插入的节点值
     * @param pivot 当前子树的根节点指针
     * @returns 当前子树的根节点指针
     */
    Node* insert(int64_t data, Node* pivot) {
        if (pivot == nullptr) {
            return new Node(data);  ///< 创建新节点并返回
        }
        if (data <= pivot->data) {
            pivot->left =
                insert(data, pivot->left);  ///< 向左子树插入节点
        } else {
            pivot->right =
                insert(data, pivot->right);  ///< 向右子树插入节点
        }
        return pivot;
    }

    /**
     * @brief 递归反转二叉树，通过交换左右子树及其子节点来实现反转
     * @param pivot 当前子树的根节点指针
     * @returns 反转后的子树根节点指针
     */
    Node* reverseBinaryTree(Node* pivot) {
        if (pivot == nullptr) {
            return pivot;  ///< 基本情况：为空时直接返回
        }
        Node* temp = pivot->left;  ///< 保存左子树的指针
        pivot->left = reverseBinaryTree(pivot->right);  ///< 递归交换左右子树
        pivot->right = reverseBinaryTree(temp);         ///< 递归交换左右子树
        return pivot;
    }

    // 禁用拷贝构造函数和赋值运算符
    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

 public:
    /**
     * @brief 创建一个空的二叉树，根节点指针为空
     */
    BinaryTree() { root = nullptr; }
    /**
     * @brief 创建一个二叉树，根节点带初始值
     */
    explicit BinaryTree(int64_t data) { root = new Node(data); }

    /**
     * @brief 析构函数，销毁二叉树，释放内存
     */
    ~BinaryTree() {
        std::vector<Node*> nodes;
        nodes.emplace_back(root);
        while (!nodes.empty()) {
            const auto cur_node = nodes.back();
            nodes.pop_back();
            if (cur_node) {
                nodes.emplace_back(cur_node->left);
                nodes.emplace_back(cur_node->right);
                delete cur_node;
            }
        }
    }

    /**
     * @brief 向二叉树中添加新节点
     */
    void add(int64_t data) { root = insert(data, root); }

    /**
     * @brief 反转二叉树
     */
    void reverse() { root = reverseBinaryTree(root); }

    /**
     * @brief 层序遍历二叉树，返回节点数据的向量
     * @details 使用队列来进行节点的添加与删除，从上到下、从左到右地逐层遍历节点
     * @returns 返回一个包含所有节点数据的整数向量
     */
    std::vector<int64_t> get_level_order() {
        std::vector<int64_t> data;  ///< 存储结果的向量
        if (root == nullptr) {
            return data;  ///< 根节点为空时返回空向量
        }
        std::queue<Node*> nodes;  ///< 用于存储节点的队列
        nodes.push(root);         ///< 将根节点入队
        while (!nodes.empty()) {
            Node* temp = nodes.front();  ///< 获取队列中的第一个元素
            data.push_back(temp->data);  ///< 将节点的数据加入结果向量
            nodes.pop();                 ///< 从队列中删除该元素
            if (temp->left != nullptr) {
                nodes.push(temp->left);  ///< 如果有左子节点，入队
            }
            if (temp->right != nullptr) {
                nodes.push(temp->right);  ///< 如果有右子节点，入队
            }
        }  /// 继续遍历直到队列为空
        return data;
    }

    /**
     * @brief 打印树中所有元素，按层级打印
     * @returns void
     */
    void print() {
        for (int i : get_level_order()) {
            std::cout << i << " ";  /// 打印树中的每个元素
        }
        std::cout << "\n";  /// 打印换行符
    }
};

}  // namespace reverse_binary_tree
}  // namespace operations_on_datastructures

/**
 * @namespace tests
 * @brief 测试用例，检查二叉树反转的正确性
 */
namespace tests {
using operations_on_datastructures::reverse_binary_tree::BinaryTree;  ///< 使用二叉树

/**
 * @brief 测试边界情况（单一元素的反转）
 */
void test1() {
    BinaryTree bst;
    std::vector<int64_t> pre_reversal, post_reversal;
    std::cout << "TEST CASE 1\n";
    std::cout << "初始化树，单一元素 (5)\n";
    bst.add(5);
    pre_reversal = bst.get_level_order();
    std::cout << "反转前: ";
    bst.print();
    std::cout << "反转后: ";
    bst.reverse();
    post_reversal = bst.get_level_order();
    assert(pre_reversal.size() == post_reversal.size());  ///< 检查大小是否相等
    assert(pre_reversal.size() == 1);  ///< 确保只有一个元素
    assert(pre_reversal[0] == post_reversal[0]);  ///< 确保反转前后相同
    bst.print();
    std::cout << "TEST PASSED!\n\n";
}

/**
 * @brief 测试边界情况（空树的反转）
 */
void test2() {
    BinaryTree bst;
    std::vector<int64_t> pre_reversal, post_reversal;
    std::cout << "TEST CASE 2\n";
    std::cout << "创建空树（根节点为NULL）\n";
    pre_reversal = bst.get_level_order();
    std::cout << "反转前: ";
    bst.print();
    std::cout << "反转后: ";
    bst.reverse();
    post_reversal = bst.get_level_order();
    assert(pre_reversal.size() == post_reversal.size());  ///< 检查大小是否相等
    assert(pre_reversal.size() == 0);  ///< 确保为空树
    bst.print();
    std::cout << "TEST PASSED!\n\n";
}

/**
 * @brief 测试二叉树的正确反转
 */
void test3() {
    BinaryTree bst;
    std::vector<int64_t> pre_reversal, post_reversal;
    std::vector<int64_t> pre_res = {4, 3, 6, 2, 5, 7, 1};
    std::vector<int64_t> post_res = {4, 6, 3, 7, 5, 2, 1};
    std::cout << "TEST CASE 3\n";
    std::cout << "创建树 (4, 6, 3, 2, 5, 7, 1)\n";
    bst.add(4);
    bst.add(6);
    bst.add(3);
    bst.add(2);
    bst.add(5);
    bst.add(7);
    bst.add(1);
    pre_reversal = bst.get_level_order();
    assert(pre_reversal == pre_res);  ///< 检查预期值
    std::cout << "反转前: ";
    bst.print();
    std::cout << "反转后: ";
    bst.reverse();
    post_reversal = bst.get_level_order();
    assert(post_reversal == post_res);  ///< 检查反转后的结果
    bst.print();
    std::cout << "TEST PASSED!\n\n";
}

}  // namespace tests

/**
 * @brief 用于测试二叉树反转的正确性
 */
static void test() {
    tests::test1();  ///< 测试单一元素
    tests::test2();  ///< 测试空树
    tests::test3();  ///< 测试正确反转
}

/**
 * @brief 主函数
 * @returns 0
 */
int main() {
    test();  // 运行自测试
    return 0;
}
