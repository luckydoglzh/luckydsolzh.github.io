// 来源：https://www.geeksforgeeks.org/bitonic-sort/

/* C++ 程序实现 Bitonic 排序。注意，该程序
   仅在输入数组的大小是 2 的幂时有效。 */

#include <algorithm>
#include <iostream>

/* 参数 dir 表示排序方向，升序（ASCENDING）或降序（DESCENDING）；
   如果 (a[i] > a[j]) 与方向一致，则交换 a[i] 和 a[j]。 */
void compAndSwap(int a[], int i, int j, int dir) {
    if (dir == (a[i] > a[j]))
        std::swap(a[i], a[j]);
}

/* 递归地按升序（如果 dir = 1）或按降序（如果 dir = 0）排序一个 Bitonic 序列。
   要排序的序列从低索引位置开始，参数 cnt 表示要排序的元素数量。*/
void bitonicMerge(int a[], int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;  // 将序列分成两部分
        // 对于当前区间的前半部分和后半部分进行比较并交换
        for (int i = low; i < low + k; i++) compAndSwap(a, i, i + k, dir);

        // 递归地对前半部分和后半部分分别进行 bitonicMerge
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low + k, k, dir);
    }
}

/* 该函数首先通过递归地排序序列的两部分（分别采用相反的排序方式），
   来生成一个 Bitonic 序列，然后调用 bitonicMerge 将这两部分合并成相同排序的序列。*/
void bitonicSort(int a[], int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;  // 将序列分成两部分

        // 先按升序排序前半部分（因为 dir 这里是 1）
        bitonicSort(a, low, k, 1);

        // 按降序排序后半部分（因为 dir 这里是 0）
        bitonicSort(a, low + k, k, 0);

        // 合并整个序列，确保按照升序（因为 dir=1）进行排序
        bitonicMerge(a, low, cnt, dir);
    }
}

/* 调用 bitonicSort 来排序整个长度为 N 的数组，按升序排序 */
void sort(int a[], int N, int up) { bitonicSort(a, 0, N, up); }

// 主程序
int main() {
    int a[] = {3, 7, 4, 8, 6, 2, 1, 5};
    int N = sizeof(a) / sizeof(a[0]);  // 获取数组大小

    int up = 1;  // 设定升序排序
    sort(a, N, up);  // 调用排序函数

    std::cout << "排序后的数组: \n";
    for (int i = 0; i < N; i++) std::cout << a[i] << " ";  // 输出排序后的数组
    return 0;
}
