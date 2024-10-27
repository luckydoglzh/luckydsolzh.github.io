/**
 * \file
 * \brief 使用节点的简单树实现
 *
 * \todo 更新代码以使用 C++ STL 库功能和面向对象结构
 * \warning 此程序实现较差，并未利用任何 C++ STL 特性。
 */
#include <algorithm>  /// 用于 std::max
#include <iostream>   /// 用于 std::cout
#include <queue>      /// 用于 std::queue

using node = struct node {
    int data;           ///< 节点存储的数据
    int height;        ///< 节点的高度
    struct node *left;  ///< 左子节点指针
    struct node *right; ///< 右子节点指针
};

/**
 * @brief 创建并返回一个新节点
 * @param[in] data 节点中存储的值
 * @return 新创建的节点
 */
node *createNode(int data) {
    node *nn = new node();   // 创建新节点
    nn->data = data;         // 设置数据
    nn->height = 0;          // 初始高度为 0
    nn->left = nullptr;      // 左子节点为空
    nn->right = nullptr;     // 右子节点为空
    return nn;               // 返回新节点
}

/**
 * @param[in] root 树的根节点
 * @return 树的高度
 */
int height(node *root) {
    if (root == nullptr) {
        return 0;  // 如果树为空，高度为 0
    }
    return 1 + std::max(height(root->left), height(root->right)); // 递归计算高度
}

/**
 * @param[in] root 树的根节点
 * @return 左右子树高度的差值
 */
int getBalance(node *root) {
    return height(root->left) - height(root->right); // 计算平衡因子
}

/**
 * @param root 要旋转的树的根节点
 * @return 右旋后的节点
 */
node *rightRotate(node *root) {
    node *t = root->left;         // t 为当前根的左子节点
    node *u = t->right;           // u 为 t 的右子节点
    t->right = root;              // 将当前根节点变为 t 的右子节点
    root->left = u;               // 将 u 作为当前根的左子节点
    return t;                     // 返回新的根节点
}

/**
 * @param root 要旋转的树的根节点
 * @return 左旋后的节点
 */
node *leftRotate(node *root) {
    node *t = root->right;        // t 为当前根的右子节点
    node *u = t->left;            // u 为 t 的左子节点
    t->left = root;               // 将当前根节点变为 t 的左子节点
    root->right = u;              // 将 u 作为当前根的右子节点
    return t;                     // 返回新的根节点
}

/**
 * @param root 树的根节点
 * @return 树中最小值的节点
 */
node *minValue(node *root) {
    if (root->left == nullptr) {
        return root;  // 如果左子节点为空，返回当前节点
    }
    return minValue(root->left); // 递归查找最小值
}

/**
 * @brief 将新元素插入到 AVL 树中
 * @param root 树的根节点
 * @param[in] item 要插入到树中的元素
 * @return 更新后的树的根节点
 */
node *insert(node *root, int item) {
    if (root == nullptr) {
        return createNode(item); // 如果树为空，创建新节点
    }
    if (item < root->data) {
        root->left = insert(root->left, item); // 递归插入左子树
    } else {
        root->right = insert(root->right, item); // 递归插入右子树
    }
    int b = getBalance(root); // 获取平衡因子
    // 平衡处理
    if (b > 1) {
        if (getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);  // 左-右旋转情况
        }
        return rightRotate(root);  // 左-左旋转情况
    } else if (b < -1) {
        if (getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);  // 右-左旋转情况
        }
        return leftRotate(root);  // 右-右旋转情况
    }
    return root; // 返回更新后的根节点
}

/**
 * @brief 从 AVL 树中删除指定元素
 * @param root 树的根节点
 * @param[in] element 要从树中删除的元素
 * @return 更新后的树的根节点
 */
node *deleteNode(node *root, int element) {
    if (root == nullptr) {
        return root; // 如果树为空，返回
    }
    if (element < root->data) {
        root->left = deleteNode(root->left, element); // 递归删除左子树
    } else if (element > root->data) {
        root->right = deleteNode(root->right, element); // 递归删除右子树
    } else {
        // 要删除的节点是叶子节点或只有一个子节点
        if (!root->right || !root->left) {
            node *temp = !root->right ? root->left : root->right; // 获取子节点
            delete root; // 删除当前节点
            return temp; // 返回子节点
        }
        // 要删除的节点有左右子树
        node *temp = minValue(root->right); // 找到右子树的最小节点
        root->data = temp->data; // 替换当前节点的数据
        root->right = deleteNode(root->right, temp->data); // 删除右子树的最小节点
    }
    // 删除后进行平衡
    return root;
}

/**
 * @brief 调用 delete 删除每个节点
 * @param root 树的根节点
 */
void deleteAllNodes(const node *const root) {
    if (root) {
        deleteAllNodes(root->left); // 删除左子树
        deleteAllNodes(root->right); // 删除右子树
        delete root; // 删除当前节点
    }
}

/**
 * @brief 按层次打印给定的树
 * @param[in] root 树的根节点
 */
void levelOrder(node *root) {
    std::queue<node *> q; // 创建队列用于层次遍历
    q.push(root); // 将根节点加入队列
    while (!q.empty()) {
        root = q.front(); // 取出队首元素
        std::cout << root->data << " "; // 输出当前节点数据
        q.pop(); // 删除队首元素
        if (root->left) {
            q.push(root->left); // 将左子节点加入队列
        }
        if (root->right) {
            q.push(root->right); // 将右子节点加入队列
        }
    }
}

/**
 * @brief 主函数
 * @returns 0 退出
 */
int main() {
    // 测试 AVL 树
    node *root = nullptr; // 初始化根节点为空
    int i = 0;
    for (i = 1; i <= 7; i++) root = insert(root, i); // 插入节点
    std::cout << "LevelOrder: "; // 打印层次遍历
    levelOrder(root);
    root = deleteNode(root, 1);  // 删除值为 1 的节点
    std::cout << "\nLevelOrder: "; // 打印层次遍历
    levelOrder(root);
    root = deleteNode(root, 4);  // 删除值为 4 的节点
    std::cout << "\nLevelOrder: "; // 打印层次遍历
    levelOrder(root);
    deleteAllNodes(root); // 删除所有节点
    return 0; // 程序结束
}
