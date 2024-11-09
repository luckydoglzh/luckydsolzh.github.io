/**
 * Copyright 2020 @author Albirair
 * @file
 *
 * 一个非递归归并排序的通用实现。
 */
#include <cstddef>  // for size_t
#include <iostream>
#include <utility>  // for std::move & std::remove_reference_t

namespace sorting {
    // 声明merge函数，用于合并两个已排序的子数组
    template <class Iterator>
    void merge(Iterator, Iterator, const Iterator, char[]);

    /// 非递归归并排序算法，通过逐步合并相邻的已排序子数组，排序元素
    /**
     * 通过将数组分解为小段，合并相邻的段，接着将段的大小乘以2再合并，最后重复此过程直到排序完成。
     * 最佳情况和最差情况的时间复杂度均为 O(n log(n))
     * @param first 指向数组的第一个元素
     * @param last 指向数组末尾元素的下一个位置
     * @param n 数组中的元素个数
     */
    template <class Iterator>
    void non_recursive_merge_sort(const Iterator first, const Iterator last,
                                  const size_t n) {
        // 创建一个足够大的缓冲区用于存储所有元素
        // 动态分配以遵循cpplint的要求
        char* buffer = new char[n * sizeof(*first)];
        
        // 缓冲区大小可以优化为小于n的最大2的幂
        // 将容器分为等大小的段，段的长度从1开始，逐步翻倍
        for (size_t length(1); length < n; length <<= 1) {
            // 合并相邻的段，段的数量为 n / (length * 2)
            Iterator left(first);
            for (size_t counter(n / (length << 1)); counter; --counter) {
                Iterator right(left + length), end(right + length);
                merge(left, right, end, buffer);
                left = end;
            }
            // 如果剩余元素的数量大于一个段的大小，合并剩余部分
            if ((n & ((length << 1) - 1)) > length)
                merge(left, left + length, last, buffer);
        }
        delete[] buffer;  // 释放缓冲区
    }

    /// 合并两个已排序的相邻子数组为一个更大的已排序子数组
    /**
     * 最佳情况和最差情况的时间复杂度均为 O(n)
     * @param l 指向左部分的迭代器
     * @param r 指向右部分的迭代器，即左部分的结束位置
     * @param e 指向右部分结束位置的迭代器
     * @param b 指向缓冲区的指针
     */
    template <class Iterator>
    void merge(Iterator l, Iterator r, const Iterator e, char b[]) {
        // 创建两个指针指向缓冲区
        auto p(reinterpret_cast<std::remove_reference_t<decltype(*l)>*>(b)), c(p);
        
        // 将左部分的元素移动到缓冲区
        for (Iterator t(l); r != t; ++t) *p++ = std::move(*t);
        
        // 当缓冲区和右部分都没有被耗尽时
        // 将两个部分中的最小元素移回到原数组
        while (e != r && c != p) *l++ = std::move(*r < *c ? *r++ : *c++);
        
        // 如果右部分还没有耗尽，移动右部分剩余的元素
        while (e != r) *l++ = std::move(*r++);
        
        // 如果缓冲区还有元素，移动缓冲区的剩余元素
        while (c != p) *l++ = std::move(*c++);
    }

    /// 非递归归并排序函数，排序元素
    /**
     * @param first 指向数组的第一个元素
     * @param n 数组中元素的数量
     */
    template <class Iterator>
    void non_recursive_merge_sort(const Iterator first, const size_t n) {
        non_recursive_merge_sort(first, first + n, n);
    }

    /// 非递归归并排序函数，排序元素
    /**
     * @param first 指向数组的第一个元素
     * @param last 指向数组末尾元素的下一个位置
     */
    template <class Iterator>
    void non_recursive_merge_sort(const Iterator first, const Iterator last) {
        non_recursive_merge_sort(first, last, last - first);
    }

}  // namespace sorting

using sorting::non_recursive_merge_sort;

int main(int argc, char** argv) {
    int size;
    std::cout << "请输入数组元素的数量 : ";
    std::cin >> size;
    
    // 动态分配数组
    int* arr = new int[size];
    
    // 输入数组元素
    for (int i = 0; i < size; ++i) {
        std::cout << "arr[" << i << "] = ";
        std::cin >> arr[i];
    }

    // 调用非递归归并排序函数
    non_recursive_merge_sort(arr, size);

    // 输出排序后的数组
    std::cout << "排序后的数组\n";
    for (int i = 0; i < size; ++i)
        std::cout << "arr[" << i << "] = " << arr[i] << '\n';
    
    // 释放内存
    delete[] arr;
    return 0;
}
