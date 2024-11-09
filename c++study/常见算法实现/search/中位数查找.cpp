/**
 * @file median_search.cpp
 * @brief 实现 [中位数查找算法](https://en.wikipedia.org/wiki/Median_of_medians)
 * @cases 来自 [这里](https://brilliant.org/wiki/median-finding-algorithm/)
 *
 * @details
 * 给定一个数组 A[1,...,n] 和一个索引 i，其中 1 ≤ i ≤ n，查找 A 中第 i 小的元素。
 * median_of_medians(A, i):
 *  # 将 A 分成大小为 5 的子数组
 *  sublists = [A[j:j+5] for j in range(0, len(A), 5)]
 *  medians = [sorted(sublist)[len(sublist)/2] for sublist in sublists]
 *  如果 medians 的长度 ≤ 5:
 *      pivot = sorted(medians)[len(medians)/2]
 *  否则:
 *      # pivot 是 medians 的中位数
 *      pivot = median_of_medians(medians, len(medians)/2)
 *  # 分区步骤
 *  low = [j for j in A if j < pivot]
 *  high = [j for j in A if j > pivot]
 *  k = len(low)
 *   如果 i < k:
 *      return median_of_medians(low, i)
 *   elif i > k:
 *      return median_of_medians(high, i-k-1)
 *  else: #pivot == k
 *       return pivot
 *
 * \note 本算法仅适用于包含唯一元素的数组
 *
 * 下面是一些可以用来测试算法的示例列表：
 * A = [1,2,3,4,5,1000,8,9,99]（包含唯一元素）
 * B = [1,2,3,4,5,6]（包含唯一元素）
 * print median_of_medians(A, 0)  #应为 1
 * print median_of_medians(A, 7)  #应为 99
 * print median_of_medians(B, 4)  #应为 5
 *
 * @author Unknown author
 * @author [Sushil Kumar](https://github.com/Rp-sushil)
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

/**
 * @namespace search
 * @brief 搜索算法
 */
namespace search {
/**
 * @namespace median_search
 * @brief [中位数查找](https://en.wikipedia.org/wiki/Median_search) 算法的函数
 */
namespace median_search {
/**
 * 该函数根据给定的索引在数组中查找元素。
 * @param A 存储数字的数组
 * @param idx 当前索引
 * @returns 返回我们要查找的相应元素。
 */  
int median_of_medians(const std::vector<int>& A,  const int& idx) {
    int pivot = 0;  // 初始化pivot为0
    std::vector<int> a(A.begin(), A.end());  // 复制数组 A
    std::vector<int> m;  // 存储中位数的数组
    int r = a.size();  // 数组大小
    for(int i = 0; i < r; i += 5){
        // 将每个子数组按升序排序
        std::sort(a.begin() + i, a.begin() + std::min(r, i + 5));
        int mid = (i + std::min(r, i + 5)) / 2;  // 计算子数组的中位数
        m.push_back(a[mid]);  // 将中位数添加到中位数数组 m 中
    }
    int sz = int(m.size());  // 中位数数组的大小
    if(sz <= 5){
        // 如果中位数数组的大小 <= 5，直接排序并选择中位数作为pivot
        std::sort(m.begin(), m.end());
        pivot = m[(sz - 1) / 2];
    }
    else{
        // 否则，递归调用 median_of_medians 查找中位数的中位数
        pivot = median_of_medians(m, idx);
    }

    std::vector<int> low;  // 存储小于pivot的元素
    std::vector<int> high;  // 存储大于pivot的元素
    for(int i = 0; i < r; i++){
        if(a[i] < pivot){
            low.push_back(a[i]);  // 将小于pivot的元素添加到 low
        }
        else if(a[i] > pivot){
            high.push_back(a[i]);  // 将大于pivot的元素添加到 high
        }
    }

    int k = int(low.size());  // low中元素的数量
    if(idx < k){
        // 如果查找的索引小于 low 的大小，递归查找 low 中的元素
        return median_of_medians(low, idx);
    }
    else if(idx > k){
        // 如果查找的索引大于 low 的大小，递归查找 high 中的元素
        return median_of_medians(high, idx - k - 1);
    }
    else{
        // 如果 idx 等于 k，说明找到了pivot
        return pivot;
    }
}
}  // namespace median_search
}  // namespace search

/**
 * 测试该算法的函数
 */
void test(){
    std::vector<int> A{25,21,98,100,76,22,43,60,89,87};
    int i = 3;
    assert(A[6] == search::median_search::median_of_medians(A, i));  // A[6] = 43，是第四小的元素
    std::cout << "测试案例 1 通过\n";
    
    std::vector<int> B{1,2,3,4,5,6};
    int j = 4;
    assert(B[4] == search::median_search::median_of_medians(B, j));  // B[4] = 5，是第五小的元素
    std::cout << "测试案例 2 通过\n";
    
    std::vector<int> C{1,2,3,4,5,1000,8,9,99};
    int k = 3;
    assert(C[3] == search::median_search::median_of_medians(C, k));  // C[3] = 4，是第四小的元素
    std::cout << "测试案例 3 通过\n";
    std::cout << "--所有测试通过--\n";
}

/**
 * 主函数
 */
int main()
{
    test();  // 执行测试

    int n = 0;
    std::cout << "请输入数组大小: ";
    std::cin >> n;  // 输入数组大小

    std::vector<int> a(n);
    std::cout << "请输入数组元素: ";
    for(int i = 0; i < n; i++){
        std::cin >> a[i];  // 输入数组元素
    }

    std::cout << "中位数: ";  // 中位数定义：https://en.wikipedia.org/wiki/Median
    int x = search::median_search::median_of_medians(a,  (n - 1) / 2);  // 查找中位数
    if(n % 2 == 0){
        int y = search::median_search::median_of_medians(a, n / 2);  // 查找数组中间的第二个元素（偶数长度时）
        std::cout << (float(x) + float(y)) / 2.0;  // 输出中位数（偶数个元素时为两个中间值的平均数）
    }
    else{
        std::cout << x;  // 输出中位数（奇数个元素时为中间元素）
    }

    std::cout << "\n查找第 i 小的元素 ";
    std::cout << "\n请输入 i: ";
    int idx = 0;
    std::cin >> idx;
    idx--;  // 索引从 0 开始
    std::cout << idx + 1 << "-th 最小的元素: " << search::median_search::median_of_medians(a, idx) << '\n';
    return 0;
}
