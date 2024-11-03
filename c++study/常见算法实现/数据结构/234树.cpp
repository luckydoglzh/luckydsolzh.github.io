/**
 * @file
 * @brief 2-3-4 树实现的示例
 * @details
 * 2-3-4 树是一种自平衡数据结构，是红黑树的同构。虽然我们在实践中很少使用它们，但我们学习它们是为了理解红黑树背后的理论。请阅读以下链接以获取更多信息。
 * [2-3-4 树](https://en.wikipedia.org/wiki/2%E2%80%933%E2%80%934_tree)
 * [2-3-4 树：视觉介绍](https://www.educative.io/page/5689413791121408/80001)
 * 本示例中仅实现一些基本和复杂的操作，其他操作应易于添加。
 * @author [liuhuan](https://github.com/fedom)
 */
#include <array>     /// 用于 std::array
#include <cassert>   /// 用于 assert
#include <fstream>   /// 用于 std::ofstream
#include <iostream>  /// 用于 std::cout
#include <memory>    /// 用于 std::unique_ptr
#include <queue>     /// 用于 std::queue
#include <string>    /// 用于 std::to_string

/**
 * @namespace data_structures
 * @brief 数据结构相关算法
 */
namespace data_structures {
/**
 * @namespace tree_234
 * @brief 2-3-4 树的功能
 */
namespace tree_234 {
/** @brief 2-3-4 树节点类 */
class Node {
 public:
    /**
     * @brief 节点构造函数
     * @param item 插入到节点的第一个值
     */
    explicit Node(int64_t item)
        : count(1),
          items({{item, 0, 0}}),
          children({{nullptr, nullptr, nullptr, nullptr}}) {}

    /**
     * @brief 获取当前节点中的项数量
     * @return 项数量
     */
    int8_t GetCount() { return count; }

    /**
     * @brief 设置节点的项数量
     *
     * 仅在分裂和合并节点时手动操作。插入和删除操作中，计数会自动维护。
     *
     * @param c 要设置的数量
     */
    void SetCount(int8_t c) { count = c; }

    /**
     * @brief 检查节点是否是叶子节点
     * @return 如果是叶子节点则返回真，否则返回假
     */
    bool IsLeaf() { return children[0] == nullptr; }

    /**
     * @brief 检查节点是否是满节点（4-节点）
     * @return 如果是满节点（4-节点）则返回真，否则返回假
     */
    bool IsFull() { return count == 3; }

    /**
     * @brief 检查节点是否是2-节点
     * @return 如果是2-节点则返回真，否则返回假
     */
    bool Is2Node() { return count == 1; }

    /** @brief 检查节点是否是3-节点或4-节点，这在从2-3-4树中删除项时很有用
     * @return 如果是3-节点或4-节点则返回真，否则返回假
     */
    bool Is34Node() { return count == 2 || count == 3; }

    /**
     * @brief 检查项是否在节点中
     * @param item 要检查的项
     * @return 如果项在节点中则返回真，否则返回假
     */
    bool Contains(int64_t item) {
        for (int8_t i = 0; i < count; i++) {
            if (item == items[i]) {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief 获取节点中项的索引，基于0
     * @param item 要检查的项
     * @return 节点中项的基于0的索引，如果不在节点中则返回 -1
     */
    int8_t GetItemIndex(int64_t item) {
        for (int8_t i = 0; i < count; i++) {
            if (items[i] == item) {
                return i;
            }
        }
        return -1;
    }

    /**
     * @brief 获取当前节点中的最大项（最右边的项）
     * @return 最大项
     */
    int64_t GetMaxItem() { return items[count - 1]; }

    /**
     * @brief 获取当前节点中的最小项（最左边的项）
     * @return 最小项
     */
    int64_t GetMinItem() { return items[0]; }

    /**
     * @brief 获取指定索引位置的项
     * @param index 要获取的项的索引
     * @return 该项的值
     */
    int64_t GetItem(int8_t index) { return items[index]; }

    /**
     * @brief 设置索引位置的项值
     * @param index 要设置的项的索引
     * @param new_item 新的项值
     */
    void SetItem(int8_t index, int64_t new_item) {
        assert(index >= 0 && index <= 2);

        items[index] = new_item;
    }

    /**
     * @brief 将项插入到节点的正确位置并返回位置索引。
     *
     * 这是在插入过程中使用的辅助函数。请注意，当插入项时，我们还需要处理两个子指针。
     * 一个是插入位置的原始子指针，它可以作为新项的左子节点或右子节点。
     * 另一个是应该添加的新子节点。对于我们这里的特定情况，我们选择使用原始子节点作为新项的左子节点，并在右子节点添加一个空指针。
     * 因此，使用此函数后，请手动更新这两个子节点指针。
     *
     * @param item 要插入到节点的值
     * @return 插入项的索引，调用者可以使用此索引更新其左和右子节点
     */
    int InsertItem(int item) {
        assert(!IsFull());

        if (Contains(item)) {
            return -1;  // 如果节点中已存在该项，则返回 -1
        }

        int8_t i = 0;
        for (i = 0; i < count; i++) {
            if (items[i] > item) {
                break;
            }
        }

        InsertItemByIndex(i, item, nullptr, true);
        return i;
    }

    /**
     * @brief 在指定索引位置插入值
     * @param index 要插入项的索引
     * @param item 要插入的值
     * @param with_child 新添加的子指针
     * @param to_left 为真表示将 with_child 添加到新项的左子节点，否则添加到右子节点
     */
    void InsertItemByIndex(int8_t index, int64_t item, Node *with_child,
                           bool to_left = true) {
        assert(count < 3 && index >= 0 && index < 3);

        for (int8_t i = count - 1; i >= index; i--) {
            items[i + 1] = items[i];  // 将项向右移动
        }

        items[index] = item;  // 插入新项

        int8_t start_index = to_left ? index : index + 1;

        for (int8_t i = count; i >= start_index; i--) {
            children[i + 1] = children[i];  // 将子节点向右移动
        }

        children[start_index] = with_child;  // 更新子节点指针

        count++;  // 增加项计数
    }

    /**
     * @brief 按索引位置移除项
     * @param index 要移除的项的索引
     * @param keep_left 保留项的左子节点，真保留左子节点，假保留右子节点
     * @return 被移除的子指针
     */
    Node *RemoveItemByIndex(int8_t index, bool keep_left) {
        assert(index >= 0 && index < count);
        Node *removed_child = keep_left ? children[index + 1] : children[index];  // 确定被移除的子节点
        for (int8_t i = index; i < count - 1; i++) {
            items[i] = items[i + 1];  // 向左移动项
        }

        for (int8_t i = keep_left ? index + 1 : index; i < count; i++) {
            children[i] = children[i + 1];  // 向左移动子节点
        }

        count--;  // 减少项计数
        return removed_child;  // 返回被移除的子节点
    }

    /**
     * @brief 获取子指针在子指针数组中的索引
     * @param child 要获取索引的子指针
     * @return 子指针的索引
     */
    int8_t GetChildIndex(Node *child) {
        for (int8_t i = 0; i <= count; i++) {
            if (children[i] == child) {
                return i;
            }
        }

        return -1;  // 未找到
    }

    /** @brief 2-3-4 树的项 */
    std::array<int64_t, 3> items;     ///< 节点的项
    std::array<Node *, 4> children;    ///< 节点的子指针
    int8_t count;                      ///< 节点中的项数量
};

/** @brief 2-3-4 树类 */
class Tree234 {
 public:
    /** @brief 2-3-4 树构造函数 */
    Tree234() : root(nullptr) {}

    /**
     * @brief 检查树中是否包含项
     * @param item 要检查的项
     * @return 如果项在树中则返回真，否则返回假
     */
    bool Contains(int64_t item) {
        return Contains(root, item);
    }

    /**
     * @brief 插入项
     * @param item 要插入的项
     */
    void Insert(int64_t item) {
        if (root == nullptr) {
            root = std::make_unique<Node>(item);
            return;
        }

        if (root->IsFull()) {
            auto new_root = std::make_unique<Node>(0);
            new_root->children[0] = root.release();  // 释放旧根节点
            SplitChild(new_root.get(), 0);  // 将旧根分裂
            root = std::move(new_root);  // 更新根节点
        }

        InsertNonFull(root.get(), item);  // 将项插入到非满节点
    }

    /**
     * @brief 输出树的内容
     * @param filename 输出到的文件名
     */
    void DumpToFile(const std::string &filename) {
        std::ofstream out_file(filename);
        if (out_file.is_open()) {
            DumpNode(root.get(), out_file, 0);
            out_file.close();
        }
    }

 private:
    std::unique_ptr<Node> root;  ///< 树的根节点

    /**
     * @brief 递归查找树中是否包含项
     * @param node 当前节点
     * @param item 要检查的项
     * @return 如果项在树中则返回真，否则返回假
     */
    bool Contains(Node *node, int64_t item) {
        if (node == nullptr) {
            return false;  // 找不到项
        }

        for (int8_t i = 0; i < node->GetCount(); i++) {
            if (item == node->GetItem(i)) {
                return true;  // 找到项
            } else if (item < node->GetItem(i)) {
                return Contains(node->children[i], item);  // 递归查找左子树
            }
        }
        return Contains(node->children[node->GetCount()], item);  // 查找右子树
    }

    /**
     * @brief 在非满节点中插入项
     * @param node 当前节点
     * @param item 要插入的项
     */
    void InsertNonFull(Node *node, int64_t item) {
        int8_t index = node->InsertItem(item);  // 尝试插入项
        if (index >= 0) {
            return;  // 插入成功
        }

        // 项已存在，无法插入
        std::cout << item << " already exists in the tree." << std::endl;
    }

    /**
     * @brief 将子节点分裂成两个子节点并更新父节点
     * @param parent 父节点
     * @param child_index 子节点在父节点中的索引
     */
    void SplitChild(Node *parent, int8_t child_index) {
        auto full_child = parent->children[child_index];  // 获取满的子节点
        auto new_child = std::make_unique<Node>(full_child->GetMaxItem());  // 创建新子节点
        parent->InsertItem(full_child->GetMinItem());  // 将最大项提升到父节点
        parent->children[child_index + 1] = new_child.get();  // 将新子节点添加到父节点

        for (int8_t i = 0; i < 2; i++) {
            new_child->InsertItem(full_child->GetItem(1));  // 移动项到新子节点
        }

        // 更新子节点指针
        if (!full_child->IsLeaf()) {
            for (int8_t i = 0; i < 2; i++) {
                new_child->children[i] = full_child->children[2];  // 更新新子节点的子指针
            }
        }

        full_child->SetCount(1);  // 更新满子节点的项数量
    }

    /**
     * @brief 递归输出节点内容
     * @param node 当前节点
     * @param out_file 输出流
     * @param level 当前树的层级
     */
    void DumpNode(Node *node, std::ofstream &out_file, int8_t level) {
        if (node == nullptr) {
            return;
        }

        for (int8_t i = 0; i < node->GetCount(); i++) {
            DumpNode(node->children[i], out_file, level + 1);  // 递归输出子节点
            out_file << std::string(level * 2, ' ') << node->GetItem(i) << std::endl;  // 输出当前节点的项
        }
        DumpNode(node->children[node->GetCount()], out_file, level + 1);  // 输出最后一个子节点
    }
};

}  // namespace tree_234
Tree234::~Tree234() { DeleteNode(root_); }

/**
 * @brief 递归释放树
 * @param tree 要删除的树的根节点
 */
void Tree234::DeleteNode(Node *tree) {
    if (!tree) {
        return;  // 如果树为空，直接返回
    }
    for (int8_t i = 0; i <= tree->GetCount(); i++) {
        DeleteNode(tree->GetChild(i));  // 递归删除每个子节点
    }
    delete tree;  // 删除当前节点
}

/**
 * @brief 中序遍历树，打印节点项
 * @param tree 要遍历的树
 */
void Tree234::Traverse() {
    Traverse(root_);  // 从根节点开始遍历
    std::cout << std::endl;
}

void Tree234::Traverse(Node *node) {
    if (!node) {
        return;  // 如果节点为空，直接返回
    }

    int8_t i = 0;
    for (i = 0; i < node->GetCount(); i++) {
        Traverse(node->GetChild(i));  // 遍历左子树
        std::cout << node->GetItem(i) << ", ";  // 打印当前节点的项
    }
    Traverse(node->GetChild(i));  // 遍历右子树
}

/**
 * @brief 预拆分的插入实现
 * @param item 要插入的项
 */
void Tree234::InsertPreSplit(int64_t item) {
    if (!root_) {
        root_ = new Node(item);  // 如果树为空，直接创建根节点
        return;
    }

    Node *parent = nullptr;
    Node *node = root_;

    while (true) {
        if (!node) {
            std::unique_ptr<Node> tmp(new Node(item));
            MergeNodeNotFull(parent, tmp.get());  // 合并到父节点
            return;
        }

        if (node->Contains(item)) {
            return;  // 如果节点中已存在该项，则不插入
        }

        if (node->IsFull()) {
            node = SplitNode(node);  // 拆分满节点

            Node *cur_node = nullptr;

            if (item < node->GetItem(0)) {
                cur_node = node->GetChild(0);  // 获取左子节点
            } else {
                cur_node = node->GetChild(1);  // 获取右子节点
            }

            if (!parent) {
                // 对于根节点，parent 为 nullptr，直接将拆分后的节点赋值给 root_
                root_ = node;
            } else {
                // 将拆分后的父节点合并到其原始父节点
                MergeNodeNotFull(parent, node);
            }

            node = cur_node;  // 更新当前节点
        }

        parent = node;  // 更新父节点
        node = parent->GetNextPossibleChild(item);  // 获取下一个可能的子节点
    }
}

/**
 * @brief 后合并的插入实现
 * @param item 要插入的项
 */
void Tree234::InsertPostMerge(int64_t item) {
    if (!root_) {
        root_ = new Node(item);  // 如果树为空，直接创建根节点
        return;
    }

    Node *split_node = Insert(root_, item);  // 在树中插入项

    // 如果根节点已经拆分，则更新根节点
    if (split_node) {
        root_ = split_node;
    }
}

/**
 * @brief 插入项到树
 * @param item 要插入的项
 */
void Tree234::Insert(int64_t item) { InsertPreSplit(item); }

/**
 * @brief 后合并插入的辅助函数
 * @param tree 要插入的树
 * @param item 要插入的项
 * @return 当溢出发生时的分裂节点
 */
Node *Tree234::Insert(Node *tree, int64_t item) {
    assert(tree != nullptr);

    std::unique_ptr<Node> split_node;

    if (tree->Contains(item)) {
        // 返回 nullptr 表示当前节点没有溢出
        return nullptr;
    }

    Node *next_node = tree->GetNextPossibleChild(item);
    if (next_node) {
        split_node.reset(Insert(next_node, item));  // 递归插入
    } else {
        split_node.reset(new Node(item));  // 创建新节点
    }

    if (split_node) {
        return MergeNode(tree, split_node.get());  // 合并节点
    }

    return nullptr;
}

/**
 * @brief 后合并插入的辅助函数
 * 当插入导致溢出时，会将节点拆分为 1 个父节点和 2 个子节点
 * 并在之后合并到其原始父节点
 * 所以参数节点总是 2 节点
 *
 * @param dst_node 目标节点，我们将节点合并到此处，可以是 2 节点、3 节点或 4 节点
 * @param node 源节点，合并来源，类型必须是 2 节点
 * @return 此级别的溢出节点
 */
Node *Tree234::MergeNode(Node *dst_node, Node *node) {
    assert(dst_node != nullptr && node != nullptr);

    if (!dst_node->IsFull()) {
        MergeNodeNotFull(dst_node, node);  // 合并到非满节点
        return nullptr;
    }

    dst_node = SplitNode(dst_node);  // 拆分满节点

    if (node->GetItem(0) < dst_node->GetItem(0)) {
        MergeNodeNotFull(dst_node->GetChild(0), node);  // 合并到左子节点
    } else {
        MergeNodeNotFull(dst_node->GetChild(1), node);  // 合并到右子节点
    }

    return dst_node;  // 返回拆分后的节点
}

/**
 * @brief 合并节点到非满目标节点
 * 因为目标节点不是满的，所以不会发生溢出，因此不需要返回值
 *
 * @param dst_node 目标非满节点，类型为 2 节点或 3 节点，但不是 4 节点
 * @param node 源节点，类型必须是 2 节点
 */
void Tree234::MergeNodeNotFull(Node *dst_node, Node *node) {
    assert(dst_node && node && !dst_node->IsFull() && node->Is2Node());

    int8_t i = dst_node->InsertItem(node->GetItem(0));  // 插入项

    dst_node->SetChild(i, node->GetChild(0));  // 设置左子节点
    dst_node->SetChild(i + 1, node->GetChild(1));  // 设置右子节点
}

/**
 * @brief 将 4 节点拆分为 1 个父节点和 2 个子节点，并返回父节点
 * @param node 要拆分的节点，必须是 4 节点
 * @return 拆分后的父节点
 */
Node *Tree234::SplitNode(Node *node) {
    assert(node->GetCount() == 3);  // 确保是 4 节点

    Node *left = node;

    Node *right = new Node(node->GetItem(2));  // 创建右子节点
    right->SetChild(0, node->GetChild(2));  // 设置右子节点的左子节点
    right->SetChild(1, node->GetChild(3));  // 设置右子节点的右子节点

    Node *parent = new Node(node->GetItem(1));  // 创建父节点
    parent->SetChild(0, left);  // 设置左子节点
    parent->SetChild(1, right);  // 设置右子节点

    left->SetCount(1);  // 更新左节点的计数

    return parent;  // 返回父节点
}

/**
 * @brief 尝试左旋转目标节点的便捷函数
 *
 * 给定两个节点，父节点和目标子节点，左旋转操作是唯一确定的。
 * 源节点必须是目标子节点的右兄弟。如果目标子节点有右兄弟且其右兄弟不是 2 节点，则操作可以成功执行。
 *
 * @param parent 左旋转操作中的父节点
 * @param to_child 左旋转操作的目标子节点。在我们的情况下，这个节点总是 2 节点
 * @return 如果成功左旋转返回 true；否则返回 false
 */
bool Tree234::TryLeftRotate(Node *parent, Node *to_child) {
    int to_child_index = parent->GetChildIndex(to_child);

    // 子节点是最右边的，不能对其进行左旋转
    if (to_child_index >= parent->GetCount()) {
        return false;
    }

    Node *right_sibling = parent->GetChild(to_child_index + 1);

    // 右兄弟是 2 节点，不能左旋转。
    if (right_sibling->Is2Node()) {
        return false;
    }

    // 进行左旋转
    to_child->InsertItem(parent->GetItem(to_child_index));  // 插入父节点的项到目标子节点
    parent->SetItem(to_child_index, right_sibling->GetItem(0));  // 将右兄弟的项移到父节点
    to_child->SetChild(1, to_child->GetChild(0));  // 更新目标子节点的右子节点
    to_child->SetChild(0, right_sibling->GetChild(0));  // 更新目标子节点的左子节点
    right_sibling->SetCount(right_sibling->GetCount() - 1);  // 更新右兄弟的计数
    return true;  // 左旋转成功
}

/**
 * @brief 尝试右旋转目标节点的便捷函数
 *
 * 给定两个节点，父节点和目标子节点，右旋转操作是唯一确定的。
 * 源节点必须是目标子节点的左兄弟。如果目标子节点有左兄弟且其左兄弟不是 2 节点，则操作可以成功执行。
 *
 * @param parent 右旋转操作中的父节点
 * @param to_child 右旋转操作的目标子节点。在我们的情况下，这个节点总是 2 节点
 * @return 如果成功右旋转返回 true；否则返回 false
 */
bool Tree234::TryRightRotate(Node *parent, Node *to_child) {
    int to_child_index = parent->GetChildIndex(to_child);

    // 子节点是最左边的，不能对其进行右旋转
    if (to_child_index <= 0) {
        return false;
    }

    Node *left_sibling = parent->GetChild(to_child_index - 1);

    // 左兄弟是 2 节点，不能右旋转
    if (left_sibling->Is2Node()) {
        return false;
    }

    // 进行右旋转
    to_child->InsertItem(parent->GetItem(to_child_index - 1));  // 将父节点的项插入到目标子节点
    parent->SetItem(to_child_index - 1, left_sibling->GetItem(left_sibling->GetCount() - 1));  // 将左兄弟的项移到父节点
    to_child->SetChild(0, to_child->GetChild(1));  // 更新目标子节点的左子节点
    to_child->SetChild(1, left_sibling->GetChild(left_sibling->GetCount()));  // 更新目标子节点的右子节点
    left_sibling->SetCount(left_sibling->GetCount() - 1);  // 更新左兄弟的计数
    return true;  // 右旋转成功
}
/**
 * @brief 获取树的最大项
 * @param tree 要从中获取项的树
 * @return 树的最大项
 */
int64_t Tree234::GetTreeMaxItem(Node *tree) {
    assert(tree);  // 确保树不为空
    int64_t max = 0;  // 初始化最大值

    while (tree) {
        max = tree->GetMaxItem();  // 获取当前节点的最大项
        tree = tree->GetRightmostChild();  // 继续向右子节点遍历
    }

    return max;  // 返回最大项
}

/**
 * @brief 获取树的最小项
 * @param tree 要从中获取项的树
 * @return 树的最小项
 */
int64_t Tree234::GetTreeMinItem(Node *tree) {
    assert(tree);  // 确保树不为空
    int64_t min = 0;  // 初始化最小值

    while (tree) {
        min = tree->GetMinItem();  // 获取当前节点的最小项
        tree = tree->GetLeftmostChild();  // 继续向左子节点遍历
    }

    return min;  // 返回最小项
}

/**
 * @brief 将树打印到 dot 文件
 * @param file_name 输出文件名，如果为 nullptr 则使用默认 "out.dot"
 */
void Tree234::Print(const char *file_name) {
    if (!file_name) {
        file_name = "out.dot";  // 默认文件名
    }

    std::ofstream ofs;

    ofs.open(file_name);  // 打开输出文件
    if (!ofs) {
        std::cout << "创建树的 dot 文件失败，" << file_name << std::endl;
        return;
    }

    ofs << "digraph G {\n";  // 开始 dot 文件
    ofs << "node [shape=record]\n";  // 节点形状设置为记录

    int64_t index = 0;  // 节点索引

    /** @brief 辅助结构，用于进行层次遍历以打印树 */
    struct NodeInfo {
        Node *node;     ///< 树节点
        int64_t index;  ///< 层次遍历中的节点索引，用于绘制父子节点之间的连接
    };

    std::queue<NodeInfo> q;  // 使用队列进行层次遍历

    if (root_) {
        // 打印根节点
        PrintNode(ofs, root_, -1, index, 0);

        NodeInfo ni{};
        ni.node = root_;  // 设置当前节点为根节点
        ni.index = index;  // 设置索引

        q.push(ni);  // 将根节点信息入队

        while (!q.empty()) {
            NodeInfo node_info = q.front();  // 获取队首节点信息
            q.pop();  // 出队

            assert(node_info.node->GetCount() > 0);  // 确保节点有项

            if (!node_info.node->IsLeaf()) {
                // 如果当前节点不是叶节点
                if (node_info.node->GetCount() > 0) {
                    PrintNode(ofs, node_info.node->GetChild(0), node_info.index,
                              ++index, 0);  // 打印左子节点
                    ni.node = node_info.node->GetChild(0);
                    ni.index = index;
                    q.push(ni);  // 入队

                    PrintNode(ofs, node_info.node->GetChild(1), node_info.index,
                              ++index, 1);  // 打印中间子节点
                    ni.node = node_info.node->GetChild(1);
                    ni.index = index;
                    q.push(ni);  // 入队
                }

                if (node_info.node->GetCount() > 1) {
                    PrintNode(ofs, node_info.node->GetChild(2), node_info.index,
                              ++index, 2);  // 打印右子节点
                    ni.node = node_info.node->GetChild(2);
                    ni.index = index;
                    q.push(ni);  // 入队
                }

                if (node_info.node->GetCount() > 2) {
                    PrintNode(ofs, node_info.node->GetChild(3), node_info.index,
                              ++index, 3);  // 打印右边的节点（如果存在）
                    ni.node = node_info.node->GetChild(3);
                    ni.index = index;
                    q.push(ni);  // 入队
                }
            }
        }
    }

    ofs << "}\n";  // 结束 dot 文件
    ofs.close();  // 关闭文件
}

/**
 * @brief 将树打印到 dot 文件。您可以使用 graphviz 将其转换为图片
 * @param ofs 输出文件流
 * @param node 当前打印的节点
 * @param parent_index 当前节点的父节点索引，用于绘制父子节点之间的连接
 * @param index 当前节点的层次遍历索引，用于在 dot 文件中命名节点
 * @param parent_child_index 当前节点在父节点子节点数组中的索引，范围 [0,4)，
 * 帮助定位节点之间连接的起始位置
 */
void Tree234::PrintNode(std::ofstream &ofs, Node *node, int64_t parent_index,
                        int64_t index, int8_t parent_child_index) {
    assert(node);  // 确保节点不为空

    switch (node->GetCount()) {
        case 1:
            ofs << "node_" << index << " [label=\"<f0> " << node->GetItem(0)
                << "\"]\n";  // 打印 2 节点
            break;
        case 2:
            ofs << "node_" << index << " [label=\"<f0> " << node->GetItem(0)
                << " | <f1> " << node->GetItem(1) << "\"]\n";  // 打印 3 节点
            break;
        case 3:
            ofs << "node_" << index << " [label=\"<f0> " << node->GetItem(0)
                << " | <f1> " << node->GetItem(1) << "| <f2> "
                << node->GetItem(2) << "\"]\n";  // 打印 4 节点
            break;

        default:
            break;
    }

    // 绘制边缘连接
    if (parent_index >= 0) {
        ofs << "node_" << parent_index << ":f"
            << (parent_child_index == 0 ? 0 : parent_child_index - 1) << ":"
            << (parent_child_index == 0 ? "sw" : "se") << " -> node_" << index
            << "\n";  // 连接父节点和当前节点
    }
}
}  // namespace tree_234
}  // namespace data_structures


/** @brief 简单测试，将给定数组插入并删除某些项，然后打印树 */
static void test1() {
    std::array<int16_t, 13> arr = {3, 1, 5, 4, 2, 9, 10, 8, 7, 6, 16, 13, 14};
    data_structures::tree_234::Tree234 tree;

    for (auto i : arr) {
        tree.Insert(i);  // 插入数组中的每个元素
    }

    // tree.Remove(10);  // 可选删除
    tree.Remove(5);  // 删除元素 5
    tree.Print();  // 打印树
}

/**
 * @brief 简单测试，插入连续范围 [0, n)，并打印树
 * @param n 插入的范围上限
 */
static void test2(int64_t n) {
    data_structures::tree_234::Tree234 tree;

    for (int64_t i = 0; i < n; i++) {
        tree.Insert(i);  // 插入从 0 到 n-1 的数字
    }

    tree.Traverse();  // 遍历树
    tree.Print((std::to_string(n) + ".dot").c_str());  // 打印到 dot 文件
}

/**
 * @brief 主函数
 * @param argc 命令行参数计数（被忽略）
 * @param argv 命令行参数数组（被忽略）
 * @returns 0 以退出
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        test1();  // 执行第一个测试
    } else {
        test2(std::stoi(argv[1]));  // 执行第二个测试
    }

    return 0;  // 返回 0
}


