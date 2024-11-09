/**
 * @file
 * @brief 实现了二叉搜索树的[中序后继](https://www.youtube.com/watch?v=5cPbNCrdotA)的查找
 * 二叉树节点的中序后继是中序遍历中紧接着该节点的下一个节点。
 * 对于中序遍历中的最后一个节点，其中序后继为NULL。
 * @details
 * ### 情况 1: 给定节点有右子树
 *      * 在这种情况下，右子树中最左的最深的节点将紧接在给定节点之后。
 *      - 也可以说，在二叉搜索树中，找到该节点右子树中的最小节点。
 *
 * ### 情况 2: 给定节点没有右子树
 * #### 方法 1: 使用父指针（存储父节点的地址）
 *      * 如果节点没有右子树，并且我们已经访问过该节点本身，则中序后继将是它的父节点。
 *      * 换句话说，返回给定节点的最接近的祖先节点，它是给定节点的左子树。
 *
 * #### 方法 2: 从根节点开始查找
 *      * 如果没有父节点的链接，必须从根节点开始遍历树，经过每一个祖先节点。
 *      * 中序后继是路径中最深的一个节点，它的左子树包含给定节点。
 *
 * @author [Nitin Sharma](https://github.com/foo290)
 * */

#include <cassert>   ///  用于assert
#include <iostream>  ///  用于输入输出操作
#include <vector>    ///  用于std::vector

/**
 * @namespace operations_on_datastructures
 * @brief 数据结构操作
 */
namespace operations_on_datastructures {

/**
 * @namespace inorder_successor_of_bst
 * @brief 二叉搜索树的[中序后继](https://www.youtube.com/watch?v=5cPbNCrdotA)实现
 */
namespace inorder_traversal_of_bst {

/**
 * @brief 代表二叉搜索树中单个节点的结构体
 */
class Node {
 public:
    int64_t data;  ///< 节点的值
    Node *left;    ///< 左子节点的指针
    Node *right;   ///< 右子节点的指针
};

/**
 * @brief 在堆上为给定数据分配一个新节点，并返回其指针。
 * @param data 节点的数据。
 * @returns 返回新分配的节点的指针。
 * */
Node *makeNode(int64_t data) {
    Node *node = new Node();
    node->data = data;      ///< 设置节点数据
    node->left = nullptr;   ///< 设置左子节点为NULL
    node->right = nullptr;  ///< 设置右子节点为NULL
    return node;
}

/**
 * @brief 在二叉搜索树中插入给定数据，同时保持二叉搜索树的属性。
 * @param root 指向二叉搜索树根节点的指针
 * @param data 要插入的数据。
 * @returns 返回指向根节点的指针。
 * */
Node *Insert(Node *root, int64_t data) {
    if (root == nullptr) {
        root = makeNode(data);
    } else if (data <= root->data) {
        root->left = Insert(root->left, data);
    } else {
        root->right = Insert(root->right, data);
    }
    return root;
}

/**
 * @brief 在二叉搜索树中搜索给定数据并返回包含该数据的节点指针。
 * @param root 指向二叉搜索树根节点的指针
 * @param data 要搜索的数据。
 * @returns 返回指向找到的节点的指针
 * */
Node *getNode(Node *root, int64_t data) {
    if (root == nullptr) {
        return nullptr;
    } else if (root->data == data) {
        return root;  /// 找到了节点!
    } else if (data > root->data) {
        /// 如果给定数据大于根节点的值，则递归搜索右子树。
        return getNode(root->right, data);
    } else {
        /// 如果给定数据小于根节点的值，则递归搜索左子树。
        return getNode(root->left, data);
    }
}

/**
 * @brief 查找二叉搜索树中的最小节点。
 * @param root 指向根节点的指针。
 * @returns 返回找到的最小节点的指针
 * */
Node *findMinNode(Node *root) {
    if (root == nullptr) {
        return root;
    }
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

/**
 * @brief 使用递归的方式打印二叉搜索树的中序遍历。
 * @param root 指向二叉搜索树根节点的指针。
 * @returns void
 * */
void printInorder(Node *root) {
    if (root == nullptr) {
        return;
    }

    printInorder(root->left);  /// 递归调用左子树
    std::cout << root->data << " ";
    printInorder(root->right);  /// 递归调用右子树
}

/**
 * @brief 用于快速创建包含大数据的二叉搜索树的函数。
 * @param root 指向根节点的指针。
 * @param data 一个包含整数值的向量，这些值将作为节点插入二叉搜索树。
 * @returns 返回指向根节点的指针。
 * */
Node *makeBST(Node *root, const std::vector<int64_t> &data) {
    for (int64_t values : data) {
        root = Insert(root, values);
    }
    return root;
}

/**
 * @brief 查找并返回给定数据的中序后继节点。
 * @details 从根节点开始搜索，遍历树，访问给定节点的每个祖先节点。中序后继是路径中最深的节点，它的左子树包含给定节点。
 * @param root 指向二叉搜索树根节点的指针
 * @param data 要查找中序后继的节点的数据。
 * @returns 返回中序后继节点的指针。
 * */
Node *getInorderSuccessor(Node *root, int64_t data) {
    Node *current = getNode(root, data);
    if (current == nullptr) {
        return nullptr;
    }

    // 情况 1: 当前节点有右子树
    if (current->right != nullptr) {
        return findMinNode(current->right);
    }
    // 情况 2: 当前节点没有右子树
    else {
        Node *successor = nullptr;
        Node *ancestor = root;

        while (ancestor != current && ancestor != nullptr) {
            // 如果当前节点在根节点的左子树中
            if (current->data < ancestor->data) {
                successor = ancestor;
                ancestor = ancestor->left;  // 继续向左子树遍历
            } else {
                ancestor = ancestor->right;
            }
        }
        return successor;  // 最大值节点没有中序后继
    }
}

/**
 * @brief 清理内存，递归释放整个树的内存。
 * @param rootNode 树的根节点。
 * @returns void
 * */
void deallocate(Node *rootNode) {
    if (rootNode == nullptr) {
        return;
    }
    deallocate(rootNode->left);
    deallocate(rootNode->right);
    delete (rootNode);
}

}  // namespace inorder_traversal_of_bst
}  // namespace operations_on_datastructures

/**
 * @brief 测试用例封装类
 */
class TestCases {
 private:
    /**
     * @brief 打印给定的消息
     * @tparam T 消息的类型。
     * @returns void
     * */
    template <typename T>
    void log(T msg) {
        std::cout << "[测试] : ---> " << msg << std::endl;
    }

 public:
    /**
     * @brief 执行测试用例
     * @returns void
     * */
    void runTests() {
        log("运行测试...");

        testCase_1();
        testCase_2();
        testCase_3();

        log("测试结束！");
        std::cout << std::endl;
    }

    /**
     * @brief 测试用例1：测试最后一个节点的中序后继。
     * @returns void
     * */
    void testCase_1() {
        const operations_on_datastructures::inorder_traversal_of_bst::Node
            *expectedOutput = nullptr;  ///< 预期输出

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("测试用例1 : ");
        log("描述:");
        log("   边界情况：打印最后一个节点的中序后继，输出应为NULL。");

        operations_on_datastructures::inorder_traversal_of_bst::Node *root =
            nullptr;
        std::vector<int64_t> node_data{
            20, 3, 5, 6, 2, 23, 45, 67, 54, 12};

        root =
            operations_on_datastructures::inorder_traversal_of_bst::makeBST(root, node_data);

        operations_on_datastructures::inorder_traversal_of_bst::Node *output = operations_on_datastructures::inorder_traversal_of_bst::getInorderSuccessor(root, 67);
        assert(output == expectedOutput);

        log("测试通过!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    /**
     * @brief 测试用例2：测试节点有右子树的情况
     * @returns void
     * */
    void testCase_2() {
        const operations_on_datastructures::inorder_traversal_of_bst::Node
            *expectedOutput = nullptr;  ///< 预期输出

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("测试用例2 : ");
        log("描述:");
        log("   节点有右子树，按规则找到中序后继节点");

        operations_on_datastructures::inorder_traversal_of_bst::Node *root =
            nullptr;
        std::vector<int64_t> node_data{
            20, 3, 5, 6, 2, 23, 45, 67, 54, 12};

        root =
            operations_on_datastructures::inorder_traversal_of_bst::makeBST(root, node_data);

        operations_on_datastructures::inorder_traversal_of_bst::Node *output = operations_on_datastructures::inorder_traversal_of_bst::getInorderSuccessor(root, 45);
        assert(output != expectedOutput); // Expected non-null output.

        log("测试通过!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    /**
     * @brief 测试用例3：测试树为空时的情况
     * @returns void
     * */
    void testCase_3() {
        const operations_on_datastructures::inorder_traversal_of_bst::Node
            *expectedOutput = nullptr;  ///< 预期输出

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("测试用例3 : ");
        log("描述:");
        log("   输入空树时，中序后继应为空。");

        operations_on_datastructures::inorder_traversal_of_bst::Node *root = nullptr;

        operations_on_datastructures::inorder_traversal_of_bst::Node *output = operations_on_datastructures::inorder_traversal_of_bst::getInorderSuccessor(root, 10);
        assert(output == expectedOutput);

        log("测试通过!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }
};

int main() {
    TestCases tests;  ///< 创建测试用例
    tests.runTests();  ///< 运行测试
}
