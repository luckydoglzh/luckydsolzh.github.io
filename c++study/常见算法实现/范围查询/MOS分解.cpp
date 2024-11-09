#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

// 最大数组长度 N
const int N = 1e6 + 5;

// 数组 a 存储原始数据，bucket 存储每个查询的结果，cnt 记录每个元素出现的次数
int a[N], bucket[N], cnt[N];
int bucket_size;  // bucket_size 表示每个块的大小

// 定义一个查询结构体
struct query {
    int l, r, i;  // l 是左端点，r 是右端点，i 是查询的索引
} q[N];

int ans = 0;  // 用于记录当前区间内的不同元素个数

// 添加一个元素的操作
void add(int index) {
    cnt[a[index]]++;  // 增加该元素的出现次数
    if (cnt[a[index]] == 1)  // 如果这是该元素第一次出现，更新不同元素的个数
        ans++;
}

// 删除一个元素的操作
void remove(int index) {
    cnt[a[index]]--;  // 减少该元素的出现次数
    if (cnt[a[index]] == 0)  // 如果该元素的出现次数变为0，更新不同元素的个数
        ans--;
}

// 自定义比较函数，用于排序查询
// 按照块的编号（l / bucket_size）排序，块内按照右端点 r 排序
bool mycmp(query x, query y) {
    if (x.l / bucket_size != y.l / bucket_size)  // 如果在不同的块，按块排序
        return x.l / bucket_size < y.l / bucket_size;
    return x.r < y.r;  // 否则按右端点排序
}

int main() {
    int n, t, i, j, k = 0;
    
    // 输入数组大小 n
    scanf("%d", &n);
    
    // 输入数组元素 a
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    
    // 计算块的大小，通常取 sqrt(n)
    bucket_size = ceil(sqrt(n));
    
    // 输入查询个数 t
    scanf("%d", &t);
    
    // 输入每个查询的 l 和 r
    for (i = 0; i < t; i++) {
        scanf("%d %d", &q[i].l, &q[i].r);
        q[i].l--;  // 转换为 0-based 索引
        q[i].r--;  // 转换为 0-based 索引
        q[i].i = i;  // 保存查询的原始索引
    }
    
    // 按照自定义规则对查询进行排序
    sort(q, q + t, mycmp);
    
    // 初始化左右端点
    int left = 0, right = 0;
    
    // 对每个查询进行处理
    for (i = 0; i < t; i++) {
        int L = q[i].l, R = q[i].r;
        
        // 调整左端点，使其匹配当前查询的左端点
        while (left < L) {
            remove(left);  // 左端点右移，移除当前左端点的元素
            left++;
        }
        while (left > L) {
            add(left - 1);  // 左端点左移，添加新的左端点的元素
            left--;
        }
        
        // 调整右端点，使其匹配当前查询的右端点
        while (right <= R) {
            add(right);  // 右端点右移，添加新的右端点的元素
            right++;
        }
        while (right > R + 1) {
            remove(right - 1);  // 右端点左移，移除当前右端点的元素
            right--;
        }
        
        // 保存当前查询的结果
        bucket[q[i].i] = ans;
    }
    
    // 输出每个查询的结果
    for (i = 0; i < t; i++) printf("%d\n", bucket[i]);
    
    return 0;
}
