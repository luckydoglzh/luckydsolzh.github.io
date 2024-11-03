#include <iostream>
#include <queue>

/**************************
    @author shrutisheoran
**************************/

using namespace std;

/**
 * @struct Btree
 * @brief 二叉树节点结构体
 */
struct Btree {
    int data;              // 节点数据
    struct Btree *left;    // 指向左子树的指针
    struct Btree *right;   // 指向右子树的指针
};

/**
 * @brief 插入新节点到二叉树中
 * 
 * @param root 二叉树的根节点的指针的引用
 * @param d 要插入节点的数据
 */
void insert(Btree **root, int d) {
    Btree *nn = new Btree();  // 创建新节点
    nn->data = d;
    nn->left = NULL;
    nn->right = NULL;
    if (*root == NULL) {
        *root = nn;  // 如果根节点为空，则将新节点作为根节点
        return;
    } else {
        queue<Btree *> q;
        q.push(*root);  // 将根节点加入队列
        while (!q.empty()) {
            Btree *node = q.front();
            q.pop();  // 从队列中移除父节点
            if (node->left)
                q.push(node->left);  // 将父节点的左子节点加入队列
            else {
                node->left = nn;  // 如果左子节点为空，则将新节点作为左子节点
                return;
            }
            if (node->right)
                q.push(node->right);  // 将父节点的右子节点加入队列
            else {
                node->right = nn;  // 如果右子节点为空，则将新节点作为右子节点
                return;
            }
        }
    }
}

/**
 * @brief Morris 中序遍历二叉树
 * 
 * Morris 中序遍历是一种不使用额外空间的遍历方法
 * 
 * @param root 二叉树的根节点
 */
void morrisInorder(Btree *root) {
    Btree *curr = root;
    Btree *temp;
    while (curr) {
        if (curr->left == NULL) {
            cout << curr->data << " ";
            curr = curr->right;  // 如果当前节点的左子节点为空，则移到右子节点
        } else {
            temp = curr->left;  // 将左子节点存储在 temp 中
            while (temp->right && temp->right != curr) temp = temp->right;  // 移动到 temp 的最右节点
            if (temp->right == NULL) {
                temp->right = curr;  // 将最右节点的右指针指向当前节点，以便回溯
                curr = curr->left;  // 将当前节点移到其左子节点
            } else if (temp->right == curr) {
                cout << curr->data << " ";
                temp->right = NULL;  // 解除最右节点的右指针，使其恢复为 NULL
                curr = curr->right;  // 将当前节点移到其右子节点
            }
        }
    }
}

/**
 * @brief 删除整个二叉树并释放内存
 * 
 * 递归地删除所有节点
 * 
 * @param root 二叉树的根节点
 */
void deleteAll(const Btree *const root) {
    if (root) {
        deleteAll(root->left);  // 递归删除左子树
        deleteAll(root->right);  // 递归删除右子树
        delete root;  // 删除当前节点
    }
}

/**
 * @brief 主函数
 * 
 * 测试 Morris 中序遍历的实现
 * 
 * @return int 程序结束状态
 */
int main() {
    Btree *root = NULL;
    int i;
    for (i = 1; i <= 7; i++) insert(&root, i);  // 插入节点 1 到 7
    cout << "Morris Inorder: ";
    morrisInorder(root);  // 执行 Morris 中序遍历
    deleteAll(root);  // 删除整个二叉树
    return 0;
}
