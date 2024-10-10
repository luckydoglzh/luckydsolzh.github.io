#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构
typedef struct TreeNode {
    int data;                // 节点中的数据
    struct TreeNode* left;   // 指向左子树的指针
    struct TreeNode* right;  // 指向右子树的指针
} TreeNode;
// 创建新节点
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
// 插入节点到二叉搜索树
TreeNode* insert(TreeNode* root, int data) {
    // 如果树为空，创建并返回新节点
    if (root == NULL) {
        return createNode(data);
    }

    // 根据数据大小选择插入到左子树或右子树
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    // 返回更新后的根节点
    return root;
}
// 前序遍历：根节点 -> 左子树 -> 右子树
void preOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}
// 中序遍历：左子树 -> 根节点 -> 右子树
void inOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}
// 后序遍历：左子树 -> 右子树 -> 根节点
void postOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%d ", root->data);
    }
}
// 删除二叉树，释放内存
void deleteTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // 先删除左子树和右子树
    deleteTree(root->left);
    deleteTree(root->right);

    // 删除当前节点
    free(root);
}
int main() {
    TreeNode* root = NULL;

    // 插入节点
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    // 各种遍历方法
    printf("Pre-order traversal: ");
    preOrderTraversal(root);
    printf("\n");

    printf("In-order traversal: ");
    inOrderTraversal(root);
    printf("\n");

    printf("Post-order traversal: ");
    postOrderTraversal(root);
    printf("\n");

    // 删除二叉树
    deleteTree(root);

    return 0;
}
