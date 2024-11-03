// C++ 程序实现霍夫曼编码
#include <iostream>
#include <queue>
using namespace std;

// 霍夫曼树节点
struct MinHeapNode {
    // 输入字符
    char data;

    // 字符的频率
    unsigned freq;

    // 左右子节点
    MinHeapNode *left, *right;

    // 构造函数
    MinHeapNode(char data, unsigned freq) {
        left = right = NULL; // 初始化左右子节点为空
        this->data = data;   // 设置字符
        this->freq = freq;   // 设置频率
    }
};

// 递归删除所有节点
void deleteAll(const MinHeapNode* const root) {
    if (root) {
        deleteAll(root->left);  // 删除左子树
        deleteAll(root->right); // 删除右子树
        delete root;            // 删除当前节点
    }
}

// 比较两个堆节点（用于最小堆）
struct compare {
    bool operator()(const MinHeapNode* const l, const MinHeapNode* const r) const {
        return l->freq > r->freq; // 按频率升序比较
    }
};

// 从霍夫曼树的根节点打印霍夫曼编码
void printCodes(struct MinHeapNode* root, const string& str) {
    if (!root) // 如果节点为空，返回
        return;

    // 如果是叶子节点，打印字符及其编码
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";

    // 递归遍历左子树和右子树
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// 主函数，构建霍夫曼树并通过遍历打印编码
void HuffmanCodes(const char data[], const int freq[], int size) {
    struct MinHeapNode *left, *right;

    // 创建一个最小堆并插入所有字符和其频率
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    // 当堆的大小不等于 1 时进行迭代
    while (minHeap.size() != 1) {
        // 从最小堆中提取频率最小的两个节点
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // 创建一个新的内部节点，其频率为两个节点频率之和
        // 将提取的节点作为新节点的左子和右子节点
        auto* const top = new MinHeapNode('$', left->freq + right->freq);

        top->left = left;   // 左子节点
        top->right = right; // 右子节点

        minHeap.push(top); // 将新节点加入最小堆
    }

    // 打印霍夫曼编码
    printCodes(minHeap.top(), "");
    deleteAll(minHeap.top()); // 删除构建的霍夫曼树
}

// 驱动程序，测试上述函数
int main() {
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};

    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCodes(arr, freq, size); // 调用霍夫曼编码函数

    return 0;
}
