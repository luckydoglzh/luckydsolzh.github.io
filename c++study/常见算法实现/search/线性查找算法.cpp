/**
 * \file
 * \brief [线性查找算法](https://en.wikipedia.org/wiki/Linear_search)
 *
 * @author Unknown author
 * @author [Ritika Mukherjee](https://github.com/ritikaa17)
 */

#include <cassert>   /// 用于断言
#include <iostream>  /// 用于输入输出操作

/**
 * \brief 线性查找算法的实现
 * 
 * @param [in] array 待查找的数组
 * @param [in] size 数组的长度
 * @param [in] key 要查找的键值
 * @returns 如果找到键值，返回其在数组中的索引
 * @returns 如果没有找到，返回 -1
 */
int LinearSearch(int *array, int size, int key) {
    for (int i = 0; i < size; ++i) {  // 遍历整个数组
        if (array[i] == key) {  // 如果当前元素与目标值相等
            return i;  // 返回当前索引
        }
    }

    /* 如果循环结束说明目标值不在数组中，返回 -1 表示未找到 */
    return -1;
}

/**
 * @brief 自测函数
 * @returns void
 */
static void tests() {
    int size = 4;
    int *array = new int[size];  // 动态分配内存
    for (int i = 0; i < size; i++) {
        array[i] = i;  // 数组初始化为 0, 1, 2, 3
    }

    // 进行测试
    assert(LinearSearch(array, size, 0) == 0);  // 查找 0，期望返回 0
    assert(LinearSearch(array, size, 1) == 1);  // 查找 1，期望返回 1
    assert(LinearSearch(array, size, 2) == 2);  // 查找 2，期望返回 2

    size = 6;
    for (int i = 0; i < size; i++) {
        array[i] = i;  // 数组初始化为 0, 1, 2, 3, 4, 5
    }

    // 进行更多测试
    assert(LinearSearch(array, size, 3) == 3);  // 查找 3，期望返回 3
    assert(LinearSearch(array, size, 1) == 1);  // 查找 1，期望返回 1
    assert(LinearSearch(array, size, 5) == 5);  // 查找 5，期望返回 5

    std::cout << "所有测试成功通过！\n";
    delete[] array;  // 释放动态分配的内存
}

/**
 * @brief 主函数
 * @returns 程序退出时返回 0
 */
int main() {
    int mode = 0;

    std::cout << "选择模式\n";
    std::cout << "自测模式 (1)，交互模式 (2): ";

    std::cin >> mode;  // 用户选择模式

    if (mode == 2) {  // 交互模式
        int size = 0;
        std::cout << "\n请输入数组的大小 [范围 1-30 ]: ";
        std::cin >> size;

        // 确保输入的数组大小合法
        while (size <= 0 || size > 30) {
            std::cout << "大小只能在 1-30 范围内。请输入一个新的值: ";
            std::cin >> size;
        }

        int *array = new int[size];  // 动态分配内存用于存储数组
        int key = 0;

        // 输入数组元素
        std::cout << "请输入 " << size << " 个数组元素: ";
        for (int i = 0; i < size; i++) {
            std::cin >> array[i];
        }

        std::cout << "\n请输入要查找的数字: ";
        std::cin >> key;  // 输入要查找的数字

        // 调用线性查找函数
        int index = LinearSearch(array, size, key);
        if (index != -1) {
            std::cout << "数字找到，位于索引: " << index << "\n";  // 输出找到的索引
        } else {
            std::cout << "数组中未找到该元素\n";  // 输出未找到的提示
        }
        delete[] array;  // 释放动态分配的内存
    } else {
        tests();  // 运行自测函数
    }
    return 0;
}

/**
 * 中文注释：
 * 1. `LinearSearch` 函数：实现了线性查找算法，遍历数组查找指定元素。
 * 2. 如果找到目标元素，返回目标元素在数组中的索引，否则返回 -1。
 * 3. `tests` 函数：执行一系列自定义的测试用例，验证 `LinearSearch` 函数的正确性。
 * 4. `main` 函数：提供了两种模式：
 *    - **自测模式**：运行预设的测试用例。
 *    - **交互模式**：允许用户输入数组和目标值，并输出查找结果。
 */
