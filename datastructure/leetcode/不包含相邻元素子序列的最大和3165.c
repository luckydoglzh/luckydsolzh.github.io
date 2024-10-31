// 给你一个整数数组 nums 和一个二维数组 queries，其中 queries[i] = [posi, xi]。

// 对于每个查询 i，首先将 nums[posi] 设置为 xi，然后计算查询 i 的答案，该答案为 nums 中 不包含相邻元素 的 
// 子序列
//  的 最大 和。

// 返回所有查询的答案之和。

// 由于最终答案可能非常大，返回其对 109 + 7 取余 的结果。

// 子序列 是指从另一个数组中删除一些或不删除元素而不改变剩余元素顺序得到的数组。


// 思路：
// 在线段树中，对于每个节点 t(l,r)
//  ，它表示的区间为 [l,r]，对应 nums[l] 到 nums[r] 这个子数组。我们需要存储四个值：t(l,r)
//  (x,y)，其中 x,y 的取值为 0 或 1：

// x 表示左边界的选择情况；
// y 表示右边界的选择情况；
// 0 表示对应的边界元素一定没有被选择；
// 1 表示对应的边界元素可能被选择，也就是没有任何要求。
// 接下来我们考虑如何计算这四个值。如果 l=r，那么 x=0 或者 y=0 时没有元素被选择，它们的值均为 0；当 x=y=1 时，可以选择 nums[l]，也可以不选择，值为 max{nums[l],0}。
// t(0,0) = max(L(0,0)+R(1,0), L(0,1) + R(0,0))
// t(0,1) = max(L(0,0)+R(1,1), L(0,1) + R(0,1))
// t(1,0) = max(L(1,1)+R(0,0), L(1,0) + R(1,0))
// t(1,1) = max(L(1,1)+R(0,1), L(1,0) + R(1,1))
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MOD 1000000007

// 定义结构体 SegNode，用于存储线段树的节点数据
typedef struct SegNode {
    long long v00, v01, v10, v11;
} SegNode;

// 创建一个新的线段树节点，并初始化所有值为0
SegNode* segNodeCreate() {
    SegNode* node = (SegNode*)malloc(sizeof(SegNode));
    node->v00 = node->v01 = node->v10 = node->v11 = 0;
    return node;
}

// 设置节点的初始值，v11 用于记录可能的最大值，其他值设为 0
void setSegNode(SegNode* node, long long v) {
    node->v00 = node->v01 = node->v10 = 0;
    node->v11 = fmax(v, 0LL);  // v11 代表不包含相邻元素子序列的最大和
}

// 返回当前节点的最大和（不包含相邻元素的最大子序列和）
long long bestSegNode(SegNode* node) {
    return node->v11;
}

// 定义结构体 SegTree，表示线段树
typedef struct SegTree {
    int n;           // 线段树的节点总数
    SegNode** tree;  // 节点数组，用指针数组表示所有节点
} SegTree;

// 创建一个新的线段树
SegTree* segTreeCreate(int n) {
    SegTree* tree = (SegTree*)malloc(sizeof(SegTree));
    tree->n = n;
    tree->tree = (SegNode**)malloc((n * 4 + 1) * sizeof(SegNode*));  // 分配足够空间存储节点
    for (int i = 0; i < n * 4 + 1; i++) {
        tree->tree[i] = segNodeCreate();  // 初始化每个节点
    }
    return tree;
}

// 释放线段树的所有内存
void freeSegTree(SegTree* tree) {
    for (int i = 0; i <= tree->n * 4; i++) {
        free(tree->tree[i]);
    }
    free(tree->tree);
    free(tree);
}

// 初始化线段树，根据初始数组 nums 建立树
void initSegTree(SegTree* tree, int* nums) {
    internalInit(tree, nums, 1, 1, tree->n);  // 从根节点递归构建
}

// 更新线段树节点，处理单点更新
void updateSegTree(SegTree* tree, int x, int v) {
    internalUpdate(tree, 1, 1, tree->n, x + 1, v);  // 更新节点的值
}

// 查询当前线段树的最大和
long long querySegTree(SegTree* tree) {
    return bestSegNode(tree->tree[1]);  // 根节点存储整个范围的最大和
}

// 递归初始化线段树
void internalInit(SegTree* tree, int* nums, int x, int l, int r) {
    if (l == r) {  // 叶节点，直接赋值
        setSegNode(tree->tree[x], nums[l - 1]);
        return;
    }
    int mid = (l + r) / 2;
    internalInit(tree, nums, x * 2, l, mid);         // 递归初始化左子树
    internalInit(tree, nums, x * 2 + 1, mid + 1, r); // 递归初始化右子树
    pushup(tree, x);  // 合并左右子树的值
}

// 递归更新线段树节点
void internalUpdate(SegTree* tree, int x, int l, int r, int pos, int v) {
    if (l > pos || r < pos) {  // 当前范围不包含更新位置，返回
        return;
    }
    if (l == r) {  // 叶节点，更新值
        setSegNode(tree->tree[x], v);
        return;
    }
    int mid = (l + r) / 2;
    internalUpdate(tree, x * 2, l, mid, pos, v);         // 递归更新左子树
    internalUpdate(tree, x * 2 + 1, mid + 1, r, pos, v); // 递归更新右子树
    pushup(tree, x);  // 合并更新后的左右子树
}

// 合并两个子节点的值到父节点
void pushup(SegTree* tree, int x) {
    int l = x * 2, r = x * 2 + 1;  // 左右子树节点索引
    tree->tree[x]->v00 = fmax(tree->tree[l]->v00 + tree->tree[r]->v10, tree->tree[l]->v01 + tree->tree[r]->v00);
    tree->tree[x]->v01 = fmax(tree->tree[l]->v00 + tree->tree[r]->v11, tree->tree[l]->v01 + tree->tree[r]->v01);
    tree->tree[x]->v10 = fmax(tree->tree[l]->v10 + tree->tree[r]->v10, tree->tree[l]->v11 + tree->tree[r]->v00);
    tree->tree[x]->v11 = fmax(tree->tree[l]->v10 + tree->tree[r]->v11, tree->tree[l]->v11 + tree->tree[r]->v01);
}

// t(0,0) = max(L(0,0)+R(1,0), L(0,1) + R(0,0))
// t(0,1) = max(L(0,0)+R(1,1), L(0,1) + R(0,1))
// t(1,0) = max(L(1,1)+R(0,0), L(1,0) + R(1,0))
// t(1,1) = max(L(1,1)+R(0,1), L(1,0) + R(1,1))
// 主函数：计算最大和子序列
int maximumSumSubsequence(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    SegTree* tree = segTreeCreate(numsSize);  // 创建线段树
    initSegTree(tree, nums);  // 初始化线段树

    long long ans = 0;
    for (int i = 0; i < queriesSize; i++) {
        // 每次查询更新树并累加结果
        updateSegTree(tree, queries[i][0], queries[i][1]);
        ans = (ans + querySegTree(tree)) % MOD;
    }
    freeSegTree(tree);  // 释放线段树内存
    return (int)ans;
}

int main() {
    // 示例输入
    int nums[] = {1, 2, 3, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int queriesArray[][2] = {{1, 5}, {0, 2}, {3, 6}};
    int queriesSize = sizeof(queriesArray) / sizeof(queriesArray[0]);
    int* queries[queriesSize];
    for (int i = 0; i < queriesSize; i++) {
        queries[i] = queriesArray[i];
    }

    // 调用函数并输出结果
    int result = maximumSumSubsequence(nums, numsSize, queries, queriesSize, NULL);
    printf("Total Sum Modulo 10^9 + 7: %d\n", result);

    return 0;
}
