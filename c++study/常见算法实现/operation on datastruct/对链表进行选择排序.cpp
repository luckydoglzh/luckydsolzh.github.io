#include <iostream>
using namespace std;

// 定义节点类
class node {
 public:
    int data;  // 节点的数据部分
    node *link;  // 指向下一个节点的指针
    node(int d) {  // 构造函数，初始化节点数据并将指针设置为NULL
        data = d;
        link = NULL;
    }
};

// 打印链表
void print(node *head) {
    node *current = head;  // 从链表头开始遍历
    while (current != NULL) {
        cout << current->data << " ";  // 输出当前节点的数据
        current = current->link;  // 移动到下一个节点
    }
    cout << endl;  // 输出换行
}

// 创建链表，接受n个节点
node *createlist(int n) {
    node *head = NULL;  // 初始化链表头指针
    node *t = NULL;     // 用于指向链表的最后一个节点
    for (int i = 0; i < n; i++) {
        node *temp = NULL;  // 创建一个临时节点
        int num;            // 输入数据
        cin >> num;
        temp = new node(num);  // 为节点分配内存并初始化数据
        if (head == NULL) {
            head = temp;  // 如果链表为空，则将新节点设置为头节点
            t = temp;     // 让t指向新的头节点
            continue;     // 继续下一次循环
        }
        if (t->link == NULL)
            t->link = temp;  // 如果当前链表的最后一个节点没有指向其他节点，将新节点连接到最后
        t = temp;  // 更新t为链表的最后一个节点
    }
    return head;  // 返回链表头指针
}

// 对链表执行选择排序
void my_selection_sort_linked_list(node *&head) {
    node *min = head;  // min指向当前链表中的最小节点
    node *current = min->link;  // current指向min之后的节点
    node *previous = min;  // previous指向当前节点的前一个节点
    node *temp = NULL;  // temp指向排序部分的最后一个节点

    while (min->link != NULL) {  // 当链表中还有未排序部分时继续循环
        // 从未排序部分选出最小节点，假设第一个节点为最小值，开始从下一个节点扫描
        while (current != NULL) {
            if (current->data < min->data) {  // 如果当前节点的数据小于min节点的数据
                if (temp == NULL) {  // 如果是第一次扫描
                    if (previous == min) {  // 如果previous指向min节点
                        // 更新指针，将当前节点插入到min节点之前
                        head = current;  // 更新头节点为当前节点
                        min->link = current->link;  // min节点的link指向当前节点的下一个节点
                        current->link = previous;  // 当前节点的link指向previous节点
                        min = current;  // 更新min为当前节点
                        current = previous->link;  // 更新current为previous的下一个节点
                    } else {  // 如果previous不指向min节点
                        // 更新指针，将当前节点插入到min节点之前
                        head = current;  // 更新头节点为当前节点
                        previous->link = current->link;  // previous指向current的下一个节点
                        current->link = min;  // 当前节点的link指向min节点
                        min = current;  // 更新min为当前节点
                        current = previous->link;  // 更新current为previous的下一个节点
                    }
                } else {  // 如果不是第一次扫描
                    temp->link = current;  // 将temp的link指向当前节点
                    previous->link = current->link;  // 将previous的link指向current的下一个节点
                    current->link = min;  // 当前节点的link指向min
                    min = current;  // 更新min为当前节点
                    current = previous->link;  // 更新current为previous的下一个节点
                }
            } else {  // 如果当前节点的数据大于min节点的数据，继续扫描
                previous = previous->link;
                current = current->link;
            }
        }

        // 更新指针，设置temp为当前排序部分的最后一个节点
        temp = min;
        min = min->link;  // 更新min为下一个节点
        previous = min;  // 更新previous为新的min节点
        current = min->link;  // 更新current为新的min节点的下一个节点
    }
}

// 测试用例：

// 输入节点数量: 5
// 输入数据: 8 9 3 1 4
// 输出链表: 8 9 3 1 4
// 排序后的链表: 1 3 4 8 9

// 输入节点数量: 3
// 输入数据: -1 -2 -3
// 输出链表: -1 -2 -3
// 排序后的链表: -3 -2 -1

// 输入节点数量: 8
// 输入数据: 8 7 6 5 4 3 2 1
// 输出链表: 8 7 6 5 4 3 2 1
// 排序后的链表: 1 2 3 4 5 6 7 8

// 输入节点数量: 6
// 输入数据: 5 3 4 1 -2 -4
// 输出链表: 5 3 4 1 -2 -4
// 排序后的链表: -4 -2 1 3 4 5

int main() {
    node *head = NULL;  // 链表头指针
    int n;
    cout << "请输入节点数量: ";  // 提示输入节点数量
    cin >> n;
    if (n == 0)  // 如果输入节点数量为0，直接退出
        return 0;
    head = createlist(n);  // 创建链表
    cout << "原始链表: ";
    print(head);  // 打印原始链表
    my_selection_sort_linked_list(head);  // 对链表进行选择排序
    cout << "排序后的链表: ";
    print(head);  // 打印排序后的链表
    return 0;
}
