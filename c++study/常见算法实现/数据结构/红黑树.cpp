#include<iostream>

using namespace std;

// 节点结构体
struct node
{
    int key;                // 节点的键值
    node *parent;          // 父节点指针
    char color;            // 节点颜色：红色或黑色
    node *left;            // 左子节点指针
    node *right;           // 右子节点指针
};

// 红黑树类
class RBtree
{
    node *root;           // 树的根节点
    node *q;              // 辅助指针
public:
    RBtree()
    {
        q = NULL;
        root = NULL;
    }
    void insert();         // 插入节点
    void insertfix(node *); // 修复插入后的红黑树性质
    void leftrotate(node *); // 左旋
    void rightrotate(node *); // 右旋
    void del();           // 删除节点
    node* successor(node *); // 查找后继节点
    void delfix(node *); // 修复删除后的红黑树性质
    void disp();         // 显示树的结构
    void display(node *); // 递归显示节点
    void search();       // 搜索节点
};

// 插入节点
void RBtree::insert()
{
    int z, i = 0;
    cout << "\nEnter key of the node to be inserted: "; // 输入要插入的节点键值
    cin >> z;
    node *p, *q;
    node *t = new node; // 创建新节点
    t->key = z;
    t->left = NULL;
    t->right = NULL;
    t->color = 'r'; // 新节点初始为红色
    p = root;
    q = NULL;
    if (root == NULL) // 如果树为空
    {
        root = t; // 将新节点设为根
        t->parent = NULL;
    }
    else // 如果树不为空
    {
        while (p != NULL)
        {
            q = p;
            if (p->key < t->key)
                p = p->right; // 向右子树移动
            else
                p = p->left; // 向左子树移动
        }
        t->parent = q; // 设置父节点
        if (q->key < t->key)
            q->right = t; // 将新节点添加到右子树
        else
            q->left = t; // 将新节点添加到左子树
    }
    insertfix(t); // 调用修复函数
}

// 插入后的修复函数
void RBtree::insertfix(node *t)
{
    node *u;
    if (root == t) // 如果插入的是根节点
    {
        t->color = 'b'; // 根节点为黑色
        return;
    }
    while (t->parent != NULL && t->parent->color == 'r') // 如果父节点是红色
    {
        node *g = t->parent->parent; // 祖父节点
        if (g->left == t->parent) // 如果父节点是祖父的左子节点
        {
            if (g->right != NULL)
            {
                u = g->right; // 叔叔节点
                if (u->color == 'r') // 叔叔是红色
                {
                    t->parent->color = 'b'; // 将父节点设为黑色
                    u->color = 'b'; // 将叔叔设为黑色
                    g->color = 'r'; // 将祖父设为红色
                    t = g; // 将当前节点设为祖父节点
                }
            }
            else
            {
                if (t->parent->right == t) // 如果当前节点是父节点的右子节点
                {
                    t = t->parent;
                    leftrotate(t); // 先左旋
                }
                t->parent->color = 'b'; // 将父节点设为黑色
                g->color = 'r'; // 将祖父设为红色
                rightrotate(g); // 右旋
            }
        }
        else // 如果父节点是祖父的右子节点
        {
            if (g->left != NULL)
            {
                u = g->left; // 叔叔节点
                if (u->color == 'r') // 叔叔是红色
                {
                    t->parent->color = 'b'; // 将父节点设为黑色
                    u->color = 'b'; // 将叔叔设为黑色
                    g->color = 'r'; // 将祖父设为红色
                    t = g; // 将当前节点设为祖父节点
                }
            }
            else
            {
                if (t->parent->left == t) // 如果当前节点是父节点的左子节点
                {
                    t = t->parent;
                    rightrotate(t); // 先右旋
                }
                t->parent->color = 'b'; // 将父节点设为黑色
                g->color = 'r'; // 将祖父设为红色
                leftrotate(g); // 左旋
            }
        }
        root->color = 'b'; // 确保根节点始终为黑色
    }
}

// 删除节点
void RBtree::del()
{
    if (root == NULL) // 如果树为空
    {
        cout << "\nEmpty Tree.";
        return;
    }
    int x;
    cout << "\nEnter the key of the node to be deleted: "; // 输入要删除的节点键值
    cin >> x;
    node *p;
    p = root;
    node *y = NULL;
    node *q = NULL;
    int found = 0;
    while (p != NULL && found == 0) // 查找要删除的节点
    {
        if (p->key == x)
            found = 1; // 找到节点
        if (found == 0)
        {
            if (p->key < x)
                p = p->right; // 向右子树移动
            else
                p = p->left; // 向左子树移动
        }
    }
    if (found == 0) // 如果未找到
    {
        cout << "\nElement Not Found.";
        return;
    }
    else // 找到要删除的节点
    {
        cout << "\nDeleted Element: " << p->key;
        cout << "\nColour: ";
        if (p->color == 'b')
            cout << "Black\n"; // 输出颜色
        else
            cout << "Red\n";

        if (p->parent != NULL)
            cout << "\nParent: " << p->parent->key; // 输出父节点
        else
            cout << "\nThere is no parent of the node.  "; // 无父节点
        if (p->right != NULL)
            cout << "\nRight Child: " << p->right->key; // 输出右子节点
        else
            cout << "\nThere is no right child of the node.  "; // 无右子节点
        if (p->left != NULL)
            cout << "\nLeft Child: " << p->left->key; // 输出左子节点
        else
            cout << "\nThere is no left child of the node.  "; // 无左子节点
        cout << "\nNode Deleted.";
        if (p->left == NULL || p->right == NULL)
            y = p; // y是要删除的节点
        else
            y = successor(p); // 获取后继节点
        if (y->left != NULL)
            q = y->left;
        else
        {
            if (y->right != NULL)
                q = y->right; // 设置q为y的孩子
            else
                q = NULL;
        }
        if (q != NULL)
            q->parent = y->parent; // 更新q的父节点
        if (y->parent == NULL)
            root = q; // 更新根节点
        else
        {
            if (y == y->parent->left)
                y->parent->left = q; // 更新父节点的左子树
            else
                y->parent->right = q; // 更新父节点的右子树
        }
        if (y != p) // 如果y不是要删除的节点
        {
            p->color = y->color; // 复制y的颜色
            p->key = y->key; // 复制y的键值
        }
        if (y->color == 'b') // 如果y是黑色
            delfix(q); // 调用删除修复函数
    }
}

// 删除后的修复函数
void RBtree::delfix(node *p)
{
    node *s;
    while (p != root && p->color == 'b') // 当p不是根且颜色是黑色
    {
        if (p->parent->left == p) // 如果p是父节点的左子节点
        {
            s = p->parent->right; // 兄弟节点
            if (s->color == 'r') // 兄弟是红色
            {
                s->color = 'b'; // 将兄弟设为黑色
                p->parent->color = 'r'; // 将父节点设为红色
                leftrotate(p->parent); // 左旋
                s = p->parent->right; // 更新兄弟节点
            }
            if (s->left->color == 'b' && s->right->color == 'b') // 兄弟的两个子节点都是黑色
            {
                s->color = 'r'; // 将兄弟设为红色
                p = p->parent; // 更新p
            }
            else
            {
                if (s->right->color == 'b') // 兄弟的右子节点是黑色
                {
                    s->left->color = 'b'; // 将兄弟的左子节点设为黑色
                    s->color = 'r'; // 将兄弟设为红色
                    rightrotate(s); // 右旋
                    s = p->parent->right; // 更新兄弟节点
                }
                s->color = p->parent->color; // 将兄弟颜色设为父节点颜色
                p->parent->color = 'b'; // 将父节点设为黑色
                s->right->color = 'b'; // 将兄弟的右子节点设为黑色
                leftrotate(p->parent); // 左旋
                p = root; // 更新p为根节点
            }
        }
        else // 如果p是父节点的右子节点
        {
            s = p->parent->left; // 兄弟节点
            if (s->color == 'r') // 兄弟是红色
            {
                s->color = 'b'; // 将兄弟设为黑色
                p->parent->color = 'r'; // 将父节点设为红色
                rightrotate(p->parent); // 右旋
                s = p->parent->left; // 更新兄弟节点
            }
            if (s->right->color == 'b' && s->left->color == 'b') // 兄弟的两个子节点都是黑色
            {
                s->color = 'r'; // 将兄弟设为红色
                p = p->parent; // 更新p
            }
            else
            {
                if (s->left->color == 'b') // 兄弟的左子节点是黑色
                {
                    s->right->color = 'b'; // 将兄弟的右子节点设为黑色
                    s->color = 'r'; // 将兄弟设为红色
                    leftrotate(s); // 左旋
                    s = p->parent->left; // 更新兄弟节点
                }
                s->color = p->parent->color; // 将兄弟颜色设为父节点颜色
                p->parent->color = 'b'; // 将父节点设为黑色
                s->left->color = 'b'; // 将兄弟的左子节点设为黑色
                rightrotate(p->parent); // 右旋
                p = root; // 更新p为根节点
            }
        }
    }
    p->color = 'b'; // 确保p是黑色
}

// 查找后继节点
node* RBtree::successor(node *p)
{
    p = p->right; // 移动到右子树
    while (p->left != NULL) // 找到最左节点
        p = p->left;
    return p; // 返回后继节点
}

// 显示树的结构
void RBtree::disp()
{
    if (root == NULL) // 如果树为空
    {
        cout << "Tree is empty"; // 输出空树信息
        return;
    }
    display(root); // 调用递归显示函数
}

// 递归显示节点
void RBtree::display(node *p)
{
    if (p != NULL)
    {
        display(p->left); // 先显示左子树
        cout << p->key << "(" << p->color << ") "; // 输出节点信息
        display(p->right); // 再显示右子树
    }
}

// 搜索节点
void RBtree::search()
{
    if (root == NULL) // 如果树为空
    {
        cout << "\nEmpty Tree.";
        return;
    }
    int x;
    cout << "\nEnter the key of the node to be searched: "; // 输入要查找的节点键值
    cin >> x;
    node *p = root;
    int found = 0;
    while (p != NULL && found == 0) // 查找节点
    {
        if (p->key == x)
            found = 1; // 找到节点
        if (found == 0)
        {
            if (p->key < x)
                p = p->right; // 向右子树移动
            else
                p = p->left; // 向左子树移动
        }
    }
    if (found == 0) // 如果未找到
        cout << "\nElement Not Found.";
    else
        cout << "\nElement Found.";
}

int main()
{
    RBtree rbt;
    int ch;
    while (1)
    {
        cout << "\n1. Insert";
        cout << "\n2. Delete";
        cout << "\n3. Display";
        cout << "\n4. Search";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            rbt.insert(); // 调用插入函数
            break;
        case 2:
            rbt.del(); // 调用删除函数
            break;
        case 3:
            rbt.disp(); // 调用显示函数
            break;
        case 4:
            rbt.search(); // 调用查找函数
            break;
        case 5:
            exit(0); // 退出
        default:
            cout << "\nInvalid Choice"; // 无效选择
        }
    }
    return 0;
}
