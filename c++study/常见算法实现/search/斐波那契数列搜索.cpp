/**
 * @author sprintyaf
 * @file fibonacci_search.cpp
 * @brief [斐波那契搜索算法](https://en.wikipedia.org/wiki/Fibonacci_search_technique)
 */

#include <iostream>
#include <vector> // 使用 std::vector 类
#include <cassert> // 使用 assert 进行断言
#include <cstdlib> // 用于生成随机数
#include <algorithm> // 用于排序


/**
 * @brief 使用斐波那契搜索算法在排序数组中查找给定元素的索引
 * 
 * @param arr 排序后的数组
 * @param value 需要查找的值
 * @returns 如果数组包含该值，返回该元素的索引，否则返回 -1。
 */
int fibonacci_search(const std::vector<int> &arr, int value){
    // 初始化斐波那契数列中的两个成员
    int last = 0, current = 1;
    int length = arr.size(); // 数组的大小
    // 计算出大于等于数组长度的最小的斐波那契数
    int next = last + current; 

    // 找到最小的斐波那契数，使其大于或等于数组长度
    while(next < length){
        last = current;
        current = next;
        next = last + current;
    }

    // "offset" 是已消除的范围的起始位置
    int offset = -1, index;
    // 当 "next" 大于 1 时继续循环，直到所有元素都被检查过
    // 当 "next" 等于 1 时，"last" 变为 0，搜索结束
    while(next > 1){
        // 检查 "last" 是否为有效的位置
        index = std::min(offset + last, length-1);
        // 如果目标值大于 "index" 处的值，消除 "offset" 到 "index" 之间的子数组
        if(arr[index] < value){
            next = current;
            current = last;
            last = next - current;
            offset = index;
        // 如果目标值小于 "index" 处的值，消除 "index+1" 之后的子数组
        } else if(arr[index] > value){
            next = last;
            current = current - last;
            last = next - current;
        // 如果目标值等于 "index" 处的值，返回该位置
        } else {
            return index;
        }
    }
    // 比较最后一个元素
    if(current && !arr.empty() && arr[offset+1] == value){
        return offset+1;
    }
    // 如果目标值没有找到，返回 -1
    return -1;
}

/**
 * @brief 随机测试，用于检查当数组中不包含目标元素时的性能
 */
bool no_occurence_tests(){
    bool passed = true;
    int rand_num, rand_value, index, num_tests = 1000;
    std::vector<int> arr;
    while(num_tests--){
        arr.clear();
        for(int i = 0; i < 100; i++){
            rand_num = std::rand() % 1000;
            arr.push_back(rand_num);
        }
        rand_value = std::rand() % 1000;
        // 确保数组中没有包含目标值
        while(std::find(arr.begin(), arr.end(), rand_value) != arr.end()){
            std::remove(arr.begin(), arr.end(), rand_value);
        }
        std::sort(arr.begin(), arr.end());
        index = fibonacci_search(arr, rand_value);
        passed = passed && (index == -1); // 检查是否返回 -1，表示未找到目标值
    }
    return passed;
}

/**
 * @brief 随机测试，检查当目标值在数组中出现一次、多次或不出现时的情况
 */
bool random_tests(){
    bool passed = true;
    int rand_num, rand_value, index, real_value, num_tests = 10000;
    std::vector<int> arr;
    while(num_tests--){
        arr.clear();
        for(int i = 0; i < 100; i++){
            rand_num = std::rand() % 1000;
            arr.push_back(rand_num);
        }
        rand_value = std::rand() % 1000;
        std::sort(arr.begin(), arr.end());
        index = fibonacci_search(arr, rand_value);
        if(index != -1){
            real_value = arr[index];
            passed = passed && (real_value == rand_value); // 确认返回的元素值是否正确
        } else {
            passed = passed && (std::find(arr.begin(), arr.end(), rand_value) == arr.end()); // 确认未找到目标值
        }
    }
    return passed;
}

/**
 * 主函数
 * 用于测试斐波那契搜索算法
 */
int main() {
    assert(no_occurence_tests());  // 运行没有目标元素的测试
    assert(random_tests());        // 运行随机测试
    return 0;
}
