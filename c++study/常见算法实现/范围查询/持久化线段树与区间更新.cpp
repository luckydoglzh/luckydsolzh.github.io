/**
 * @file
 * @brief [持久化线段树与区间更新（懒传播）](https://en.wikipedia.org/wiki/Persistent_data_structure)
 *
 * @details
 * 一般的线段树能够在对某个点进行更新或查询时以对数时间复杂度进行操作。懒传播使得在进行区间更新时也能保持对数时间复杂度。因此，带有懒传播的线段树可以高效地进行区间更新与区间查询，但它不保存每次更新前的状态。而持久化数据结构在每次修改时都会保存数据结构的旧版本。也就是说，持久化线段树在每次更新后都会生成新的版本，并保存所有的历史版本，这样就可以在任何版本上进行查询。虽然这会占用更多内存，但对数时间复杂度依然得以保留，因为新的版本只会复制受更新影响的节点和它们的祖先。其他不受影响的节点将通过懒传播在后续查询时被复制，从而保持对数时间复杂度。
 *
 * @author [Magdy Sedra](https://github.com/MSedra)
 */
#include <iostream>  /// IO 操作
#include <memory>    /// 动态内存管理
#include <vector>    /// std::vector 容器

/**
 * @namespace range_queries
 * @brief 区间查询算法
 */
namespace range_queries {

/**
 * @brief 这里的区间查询是区间和，但代码可以修改为处理其他类型的查询，比如区间最大值或最小值。
 */
class perSegTree {
 private:
    class Node {
     public:
        std::shared_ptr<Node> left = nullptr;   /// 左子树的指针
        std::shared_ptr<Node> right = nullptr;  /// 右子树的指针
        int64_t val = 0,  /// 节点的值（这里是该节点所代表区间的叶子节点的和）
                prop = 0;  /// 懒传播的值，将会加到该节点所有子节点的值上
    };

    uint32_t n = 0;  /// 线段树中元素（叶子节点）的数量
    std::vector<std::shared_ptr<Node>> ptrs{};  /// ptrs[i] 存储了在第 i 次更新后线段树的根指针，ptrs[0] 存储的是原始版本的根指针
    std::vector<int64_t> vec{};  /// 存储构建线段树的叶子节点的值

    /**
     * @brief 创建一个新的节点，它将复制当前节点的所有值
     * @param curr 当前节点
     * @returns 新的节点
     */
    std::shared_ptr<Node> newKid(std::shared_ptr<Node> const &curr) {
        auto newNode = std::make_shared<Node>(Node());
        newNode->left = curr->left;
        newNode->right = curr->right;
        newNode->prop = curr->prop;
        newNode->val = curr->val;
        return newNode;
    }

    /**
     * @brief 如果当前节点有懒传播的值，则将该值加到节点上，并将传播值应用到其子节点
     * @param i 当前节点的左边界
     * @param j 当前节点的右边界
     * @param curr 当前节点
     * @returns void
     */
    void lazy(const uint32_t &i, const uint32_t &j, std::shared_ptr<Node> const &curr) {
        if (!curr->prop) {
            return;  // 如果没有传播的值，则直接返回
        }
        curr->val += (j - i + 1) * curr->prop;  // 加上懒传播的值
        if (i != j) {
            curr->left = newKid(curr->left);
            curr->right = newKid(curr->right);
            curr->left->prop += curr->prop;  // 将传播值添加到子节点
            curr->right->prop += curr->prop;
        }
        curr->prop = 0;  // 清除当前节点的传播值
    }

    /**
     * @brief 使用给定的向量构建线段树，每个节点保存一个区间的和
     * @param i 左边界
     * @param j 右边界
     * @returns 新创建的节点
     */
    std::shared_ptr<Node> construct(const uint32_t &i, const uint32_t &j) {
        auto newNode = std::make_shared<Node>(Node());
        if (i == j) {
            newNode->val = vec[i];  // 叶子节点的值等于原数组的值
        } else {
            uint32_t mid = i + (j - i) / 2;  // 计算中间位置
            auto leftt = construct(i, mid);   // 左子树
            auto right = construct(mid + 1, j);  // 右子树
            newNode->val = leftt->val + right->val;  // 当前节点的值等于左右子树的和
            newNode->left = leftt;
            newNode->right = right;
        }
        return newNode;
    }

    /**
     * @brief 进行区间更新，检查每个节点是否有懒传播的值。受影响的节点会被复制并加上传播值
     * @param i 当前节点的左边界
     * @param j 当前节点的右边界
     * @param l 区间的左边界
     * @param r 区间的右边界
     * @param value 要加到区间的值
     * @param curr 当前节点
     * @returns 更新后的节点
     */
    std::shared_ptr<Node> update(const uint32_t &i, const uint32_t &j,
                                 const uint32_t &l, const uint32_t &r,
                                 const int64_t &value,
                                 std::shared_ptr<Node> const &curr) {
        lazy(i, j, curr);  // 先进行懒传播
        if (i >= l && j <= r) {
            std::shared_ptr<Node> newNode = newKid(curr);
            newNode->prop += value;  // 加上传播的值
            lazy(i, j, newNode);  // 进行懒传播
            return newNode;
        }
        if (i > r || j < l) {
            return curr;  // 如果当前节点完全不在更新区间内，返回原节点
        }
        auto newNode = std::make_shared<Node>(Node());
        uint32_t mid = i + (j - i) / 2;
        newNode->left = update(i, mid, l, r, value, curr->left);
        newNode->right = update(mid + 1, j, l, r, value, curr->right);
        newNode->val = newNode->left->val + newNode->right->val;
        return newNode;
    }

    /**
     * @brief 查询区间和，检查每个节点是否有懒传播的值。返回完全包含在查询区间内的节点的和
     * @param i 当前节点的左边界
     * @param j 当前节点的右边界
     * @param l 查询区间的左边界
     * @param r 查询区间的右边界
     * @param curr 当前节点
     * @returns 区间和
     */
    int64_t query(const uint32_t &i, const uint32_t &j, const uint32_t &l,
                  const uint32_t &r, std::shared_ptr<Node> const &curr) {
        lazy(i, j, curr);  // 先进行懒传播
        if (j < l || r < i) {
            return 0;  // 当前区间不在查询范围内，返回 0
        }
        if (i >= l && j <= r) {
            return curr->val;  // 当前区间完全在查询范围内，返回该区间的和
        }
        uint32_t mid = i + (j - i) / 2;
        return query(i, mid, l, r, curr->left) +
               query(mid + 1, j, l, r, curr->right);  // 查询左右子树
    }

 public:
    /**
     * @brief 使用给定的向量构建线段树。构建后，根节点指针会被存储在 ptrs 向量中
     * @param vec 存储初始值的向量
     * @returns void
     */
    void construct(const std::vector<int64_t> &vec) {
        if (vec.empty()) {
            return;
        }
        n = vec.size();
        this->vec = vec;
        auto root = construct(0, n - 1);  // 构建线段树
        ptrs.push_back(root);
    }

    /**
     * @brief 执行一次区间更新
     * @param l 区间的左边界
     * @param r 区间的右边界
     * @param value 加到该区间的值
     * @returns void
     */
    void update(uint32_t l, uint32_t r, int64_t value) {
        auto root = update(0, n - 1, l, r, value, ptrs.back());
        ptrs.push_back(root);  // 保存更新后的根节点
    }

    /**
     * @brief 执行一次区间查询
     * @param l 查询区间的左边界
     * @param r 查询区间的右边界
     * @returns 区间和
     */
    int64_t query(uint32_t l, uint32_t r) const {
        return query(0, n - 1, l, r, ptrs.back());  // 查询最新版本的线段树
    }
};

}  // namespace range_queries

int main() {
    using namespace range_queries;

    perSegTree tree;  // 创建线段树对象

    tree.construct({1, 2, 3, 4, 5});  // 构建线段树
    std::cout << "Original Sum (0, 2): " << tree.query(0, 2) << "\n";  // 查询区间和

    tree.update(1, 3, 2);  // 对区间 [1, 3] 进行更新
    std::cout << "Updated Sum (0, 2): " << tree.query(0, 2) << "\n";  // 查询更新后的区间和

    tree.update(2, 4, 3);  // 对区间 [2, 4] 进行更新
    std::cout << "Updated Sum (0, 2): " << tree.query(0, 2) << "\n";  // 查询更新后的区间和

    return 0;
}
