/**
 * \file
 * \brief 一个 C++ 程序，用于演示二叉堆的常见操作
 */
#include <climits>
#include <iostream>
#include <utility>

/** 最小堆类 */
class MinHeap {
    int *harr;      ///< 指向堆中元素数组的指针
    int capacity;   ///< 最小堆的最大可能大小
    int heap_size;  ///< 当前堆中元素的数量

 public:
    /** 构造函数：从给定大小的数组构建一个堆
     * \param[in] capacity 初始堆容量
     */
    explicit MinHeap(int cap) {
        heap_size = 0;
        capacity = cap;
        harr = new int[cap];
    }

    /** 堆化给定索引处的子树 */
    void MinHeapify(int);

    int parent(int i) { return (i - 1) / 2; }

    /** 获取索引 i 的左子节点的索引 */
    int left(int i) { return (2 * i + 1); }

    /** 获取索引 i 的右子节点的索引 */
    int right(int i) { return (2 * i + 2); }

    /** 提取根节点（即最小元素） */
    int extractMin();

    /** 将索引 i 处的键值减少为 new_val */
    void decreaseKey(int i, int new_val);

    /** 返回最小键（根节点的键） */
    int getMin() { return harr[0]; }

    /** 删除存储在索引 i 处的键 */
    void deleteKey(int i);

    /** 插入新键 'k' */
    void insertKey(int k);

    ~MinHeap() { delete[] harr; }
};

// 插入新键 'k'
void MinHeap::insertKey(int k) {
    if (heap_size == capacity) {
        std::cout << "\n溢出：无法插入键\n";
        return;
    }

    // 首先将新键插入到末尾
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    // 如果最小堆属性被破坏，则进行修复
    while (i != 0 && harr[parent(i)] > harr[i]) {
        std::swap(harr[i], harr[parent(i)]);
        i = parent(i);
    }
}

/** 将索引 'i' 处的键值减少为 new_val。假设 new_val 小于 harr[i]。 */
void MinHeap::decreaseKey(int i, int new_val) {
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] > harr[i]) {
        std::swap(harr[i], harr[parent(i)]);
        i = parent(i);
    }
}

// 删除最小元素（或根节点）的方法
int MinHeap::extractMin() {
    if (heap_size <= 0)
        return INT_MAX;
    if (heap_size == 1) {
        heap_size--;
        return harr[0];
    }

    // 存储最小值，并将其从堆中移除
    int root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;
    MinHeapify(0);

    return root;
}

/** 此函数删除索引 i 处的键。首先将值减小到负无穷大，然后调用 extractMin() */
void MinHeap::deleteKey(int i) {
    decreaseKey(i, INT_MIN);
    extractMin();
}

/** 递归方法，用于堆化根节点位于给定索引的子树
 *  此方法假设子树已经堆化
 */
void MinHeap::MinHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i) {
        std::swap(harr[i], harr[smallest]);
        MinHeapify(smallest);
    }
}

// 主函数，用于测试上述函数
int main() {
    MinHeap h(11);
    h.insertKey(3);
    h.insertKey(2);
    h.deleteKey(1);
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);
    std::cout << h.extractMin() << " ";
    std::cout << h.getMin() << " ";
    h.decreaseKey(2, 1);
    std::cout << h.getMin();
    return 0;
}
