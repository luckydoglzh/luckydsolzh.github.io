/**
 * @file
 * @brief [二叉搜索树](https://en.wikipedia.org/wiki/Binary_search_tree)的通用实现
 * 你可以在这里找到有关此算法的更多信息：[Scaler - Binary Search tree](https://www.scaler.com/topics/data-structures/binary-search-tree/)
 * @see binary_search_tree.cpp
 */

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

/**
 * @brief 二叉搜索树类
 *
 * @tparam T 二叉搜索树键的类型
 */
template <class T>
class binary_search_tree {
 private:
    /**
    * @brief 表示二叉搜索树节点的结构体
    */
    struct bst_node {
        T value; /**< 节点的值/键 */
        std::unique_ptr<bst_node> left; /**< 指向左子树的指针 */
        std::unique_ptr<bst_node> right; /**< 指向右子树的指针 */

        /**
        * @brief bst_node的构造函数，用于简化节点构造和智能指针构造
        * @param _value 构造节点的值
        */
        explicit bst_node(T _value) {
            value = _value;
            left = nullptr;
            right = nullptr;
        }
    };

    std::unique_ptr<bst_node> root_; /**< 指向BST根节点的指针 */
    std::size_t size_ = 0; /**< BST中的元素/节点数量 */

    /**
     * @brief 递归查找BST中的最大值
     *
     * @param node 搜索的起始节点
     * @param ret_value 存储最大值的变量
     * @return true 如果成功找到最大值
     * @return false 否则
     */
    bool find_max(std::unique_ptr<bst_node>& node, T& ret_value) {
        if (!node) {
            return false;
        } else if (!node->right) {
            ret_value = node->value;
            return true;
        }
        return find_max(node->right, ret_value);
    }

    /**
     * @brief 递归查找BST中的最小值
     *
     * @param node 搜索的起始节点
     * @param ret_value 存储最小值的变量
     * @return true 如果成功找到最小值
     * @return false 否则
     */
    bool find_min(std::unique_ptr<bst_node>& node, T& ret_value) {
        if (!node) {
            return false;
        } else if (!node->left) {
            ret_value = node->value;
            return true;
        }
        return find_min(node->left, ret_value);
    }

    /**
     * @brief 递归向BST插入一个值
     *
     * @param node 搜索的起始节点
     * @param new_value 要插入的值
     * @return true 如果插入操作成功
     * @return false 否则
     */
    bool insert(std::unique_ptr<bst_node>& node, T new_value) {
        if (root_ == node && !root_) {
            root_ = std::unique_ptr<bst_node>(new bst_node(new_value));
            return true;
        }

        if (new_value < node->value) {
            if (!node->left) {
                node->left = std::unique_ptr<bst_node>(new bst_node(new_value));
                return true;
            } else {
                return insert(node->left, new_value);
            }
        } else if (new_value > node->value) {
            if (!node->right) {
                node->right =
                    std::unique_ptr<bst_node>(new bst_node(new_value));
                return true;
            } else {
                return insert(node->right, new_value);
            }
        } else {
            return false;
        }
    }

    /**
     * @brief 递归从BST中删除一个值
     *
     * @param parent 父节点
     * @param node 搜索的起始节点
     * @param rm_value 要删除的值
     * @return true 如果删除操作成功
     * @return false 否则
     */
    bool remove(std::unique_ptr<bst_node>& parent,
                std::unique_ptr<bst_node>& node, T rm_value) {
        if (!node) {
            return false;
        }

        if (node->value == rm_value) {
            if (node->left && node->right) {
                T successor_node_value{};
                find_max(node->left, successor_node_value);
                remove(root_, root_, successor_node_value);
                node->value = successor_node_value;
                return true;
            } else if (node->left || node->right) {
                std::unique_ptr<bst_node>& non_null =
                    (node->left ? node->left : node->right);

                if (node == root_) {
                    root_ = std::move(non_null);
                } else if (rm_value < parent->value) {
                    parent->left = std::move(non_null);
                } else {
                    parent->right = std::move(non_null);
                }
                return true;
            } else {
                if (node == root_) {
                    root_.reset(nullptr);
                } else if (rm_value < parent->value) {
                    parent->left.reset(nullptr);
                } else {
                    parent->right.reset(nullptr);
                }
                return true;
            }
        } else if (rm_value < node->value) {
            return remove(node, node->left, rm_value);
        } else {
            return remove(node, node->right, rm_value);
        }
    }

    /**
     * @brief 递归检查值是否在BST中
     *
     * @param node 搜索的起始节点
     * @param value 要查找的值
     * @return true 如果值存在
     * @return false 否则
     */
    bool contains(std::unique_ptr<bst_node>& node, T value) {
        if (!node) {
            return false;
        }

        if (value < node->value) {
            return contains(node->left, value);
        } else if (value > node->value) {
            return contains(node->right, value);
        } else {
            return true;
        }
    }

    /**
     * @brief 递归以中序遍历BST
     *
     * @param callback 处理值的函数
     * @param node 遍历的起始节点
     */
    void traverse_inorder(std::function<void(T)> callback,
                          std::unique_ptr<bst_node>& node) {
        if (!node) {
            return;
        }

        traverse_inorder(callback, node->left);
        callback(node->value);
        traverse_inorder(callback, node->right);
    }

    // 其余代码省略以适配字符数限制...

 public:
    /**
     * @brief 创建一个新的二叉搜索树对象
     */
    binary_search_tree() {
        root_ = nullptr;
        size_ = 0;
    }

    /**
     * @brief 向BST中插入一个新值
     * @param new_value 要插入的值
     * @return true 如果插入成功
     * @return false 否则
     */
    bool insert(T new_value) {
        bool result = insert(root_, new_value);
        if (result) {
            size_++;
        }
        return result;
    }

    // 其他公开成员函数代码...
};
