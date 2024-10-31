/**
 * \file
 * \brief 用结构化节点实现的简单树结构
 *
 * \todo 更新代码以使用C++ STL库特性并实现面向对象结构
 * \warning 本程序是一个低效的实现——C风格——没有使用任何C++ STL特性
 */

#include <iostream>

struct node {
    int val;       // 节点的值
    node *left;    // 左子节点指针
    node *right;   // 右子节点指针
};

struct Queue {
    node *t[100];  // 队列数组，存储节点指针
    int front;     // 队列头部索引
    int rear;      // 队列尾部索引
};

Queue queue;  // 定义队列

// 将节点加入队列
void enqueue(node *n) { queue.t[queue.rear++] = n; }

// 从队列中取出节点
node *dequeue() { return queue.t[queue.front++]; }

// 插入一个新值到树中
void Insert(node *n, int x) {
    if (x < n->val) {  // 如果新值小于当前节点值，插入左子树
        if (n->left == NULL) {  // 如果左子节点为空，直接插入
            node *temp = new node;
            temp->val = x;
            temp->left = NULL;
            temp->right = NULL;
            n->left = temp;
        } else {
            Insert(n->left, x);  // 否则递归插入到左子树
        }
    } else {  // 如果新值大于等于当前节点值，插入右子树
        if (n->right == NULL) {  // 如果右子节点为空，直接插入
            node *temp = new node;
            temp->val = x;
            temp->left = NULL;
            temp->right = NULL;
            n->right = temp;
        } else {
            Insert(n->right, x);  // 否则递归插入到右子树
        }
    }
}

// 查找左子树中的最大值，用于删除操作中的节点替换
int findMaxInLeftST(node *n) {
    while (n->right != NULL) {  // 向右遍历直到找到最大值
        n = n->right;
    }
    return n->val;  // 返回最大值
}

// 删除树中值为x的节点
void Remove(node *p, node *n, int x) {
    if (n->val == x) {  // 如果找到要删除的节点
        if (n->right == NULL && n->left == NULL) {  // 叶子节点情况
            if (x < p->val) {
                p->right = NULL;
            } else {
                p->left = NULL;
            }
        } else if (n->right == NULL) {  // 只有左子节点
            if (x < p->val) {
                p->right = n->left;
            } else {
                p->left = n->left;
            }
        } else if (n->left == NULL) {  // 只有右子节点
            if (x < p->val) {
                p->right = n->right;
            } else {
                p->left = n->right;
            }
        } else {  // 有两个子节点的情况
            int y = findMaxInLeftST(n->left);  // 找到左子树最大值
            n->val = y;                        // 用该值替换当前节点值
            Remove(n, n->right, y);            // 删除被替换的节点
        }
    } else if (x < n->val) {  // 如果值小于当前节点，继续搜索左子树
        Remove(n, n->left, x);
    } else {  // 如果值大于当前节点，继续搜索右子树
        Remove(n, n->right, x);
    }
}

// 广度优先遍历
void BFT(node *n) {
    if (n != NULL) {
        std::cout << n->val << "  ";
        enqueue(n->left);  // 左子节点入队
        enqueue(n->right); // 右子节点入队
        BFT(dequeue());    // 递归遍历队列中的下一个节点
    }
}

// 前序遍历
void Pre(node *n) {
    if (n != NULL) {
        std::cout << n->val << "  ";
        Pre(n->left);
        Pre(n->right);
    }
}

// 中序遍历
void In(node *n) {
    if (n != NULL) {
        In(n->left);
        std::cout << n->val << "  ";
        In(n->right);
    }
}

// 后序遍历
void Post(node *n) {
    if (n != NULL) {
        Post(n->left);
        Post(n->right);
        std::cout << n->val << "  ";
    }
}

int main() {
    queue.front = 0;  // 初始化队列头部
    queue.rear = 0;   // 初始化队列尾部
    int value;
    int ch;
    node *root = new node;  // 创建根节点
    std::cout << "\nEnter the value of root node :";
    std::cin >> value;
    root->val = value;
    root->left = NULL;
    root->right = NULL;
    do {
        std::cout << "\n1. Insert"
                  << "\n2. Delete"
                  << "\n3. Breadth First"
                  << "\n4. Preorder Depth First"
                  << "\n5. Inorder Depth First"
                  << "\n6. Postorder Depth First";

        std::cout << "\nEnter Your Choice : ";
        std::cin >> ch;
        int x;
        switch (ch) {
        case 1:
            std::cout << "\nEnter the value to be Inserted : ";
            std::cin >> x;
            Insert(root, x);
            break;
        case 2:
            std::cout << "\nEnter the value to be Deleted : ";
            std::cin >> x;
            Remove(root, root, x);
            break;
        case 3:
            BFT(root);
            break;
        case 4:
            Pre(root);
            break;
        case 5:
            In(root);
            break;
        case 6:
            Post(root);
            break;
        }
    } while (ch != 0);

    return 0;
}
