// 你有 k 个 非递减排列 的整数列表。找到一个 最小 区间，使得 k 个列表中的每个列表至少有一个数包含在其中。

// 我们定义如果 b-a < d-c 或者在 b-a == d-c 时 a < c，则区间 [a,b] 比 [c,d] 小。
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
// 堆节点结构
typedef struct {
    int value; // 当前数值
    int listIdx; // 该数属于哪个列表
    int elemIdx; // 数值在列表中的索引
} HeapNode;

// 最小堆结构
typedef struct {
    HeapNode *nodes;
    int size;
} MinHeap;

// 交换两个堆节点
void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// 堆化操作
void heapify(MinHeap *heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->nodes[left].value < heap->nodes[smallest].value) {
        smallest = left;
    }
    if (right < heap->size && heap->nodes[right].value < heap->nodes[smallest].value) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&heap->nodes[i], &heap->nodes[smallest]);
        heapify(heap, smallest);
    }
}

// 弹出堆顶
HeapNode popMin(MinHeap *heap) {
    HeapNode root = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
    return root;
}

// 插入元素到堆
void insertHeap(MinHeap *heap, HeapNode node) {
    heap->nodes[heap->size] = node;
    int i = heap->size;
    heap->size++;

    while (i != 0 && heap->nodes[(i - 1) / 2].value > heap->nodes[i].value) {
        swap(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int* smallestRange(int** nums, int numsSize, int* numsColSize, int* returnSize) {
    // 初始化堆
    int** lists= nums;
    int* sizes = numsColSize;
    int k  = numsSize;
    MinHeap heap;
    heap.nodes = (HeapNode *)malloc(k * sizeof(HeapNode));
    heap.size = 0;

    int maxInHeap = INT_MIN;

    // 初始化堆，插入每个列表的第一个元素
    for (int i = 0; i < k; i++) {
        HeapNode node = {lists[i][0], i, 0};
        insertHeap(&heap, node);
        if (lists[i][0] > maxInHeap) {
            maxInHeap = lists[i][0];
        }
    }

    // 初始化最小区间
    int rangeStart = 0;
    int rangeEnd = INT_MAX;

    // 不断弹出堆顶并更新区间
    while (1) {
        // 获取最小元素
        HeapNode minNode = popMin(&heap);
        int minValue = minNode.value;

        // 更新最小区间
        if (maxInHeap - minValue < rangeEnd - rangeStart || 
            (maxInHeap - minValue == rangeEnd - rangeStart && minValue < rangeStart)) {
            rangeStart = minValue;
            rangeEnd = maxInHeap;
        }

        // 如果该列表已结束，退出循环
        if (minNode.elemIdx + 1 >= sizes[minNode.listIdx]) {
            break;
        }

        // 插入该列表的下一个元素
        int nextValue = lists[minNode.listIdx][minNode.elemIdx + 1];
        HeapNode nextNode = {nextValue, minNode.listIdx, minNode.elemIdx + 1};
        insertHeap(&heap, nextNode);

        // 更新当前最大值
        if (nextValue > maxInHeap) {
            maxInHeap = nextValue;
        }
    }
    int* ans = malloc(sizeof(int) * 2);
    *returnSize = 2;
    ans[0] = rangeStart;
    ans[1] = rangeEnd;
    // 释放堆内存
    free(heap.nodes);
    return ans;
}