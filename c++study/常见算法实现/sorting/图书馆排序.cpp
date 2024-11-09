#include <algorithm>
#include <iostream>

/**
 * \brief 图书馆排序（Library Sort）算法
 * 
 * 图书馆排序是一种基于插入排序的变种算法，通常用于对需要动态排序的数据进行排序，算法通过将元素插入到合适的位置来保持元素的有序性。
 * 它通过两个数组（或“图书馆”）来分别存储已排序和未排序的元素，并在每次插入时维护元素的正确顺序。
 *
 * @param index 输入的待排序数组
 * @param n 数组的大小
 */
void librarySort(int *index, int n) {
    int lib_size, index_pos,
        *gaps,        // 用来存储未排序元素的数组
        *library[2];  // 用两个数组（图书馆）来存储排序的元素

    bool target_lib, *numbered;

    // 动态分配两个数组（图书馆）和其他辅助数组
    for (int i = 0; i < 2; i++) library[i] = new int[n];

    gaps = new int[n + 1];       // 存储未排序元素的位置
    numbered = new bool[n + 1];  // 标记哪些位置已经被占用

    lib_size = 1;                // 当前已排序图书馆的大小
    index_pos = 1;               // 当前待插入的元素索引
    target_lib = 0;              // 当前目标图书馆（0 或 1）
    library[target_lib][0] = index[0];  // 将第一个元素放入目标图书馆

    while (index_pos < n) {  // 当待排序的元素没有全部插入时，继续
        // 二分查找：找到当前待插入元素的插入位置
        int insert = std::distance(
            library[target_lib],
            std::lower_bound(library[target_lib],
                             library[target_lib] + lib_size, index[index_pos]));

        // 如果插入位置已被占用，说明插入会发生冲突
        if (numbered[insert] == true) {
            int prov_size = 0, next_target_lib = !target_lib;

            // 更新图书馆内容并清空gaps
            for (int i = 0; i <= n; i++) {
                if (numbered[i] == true) {
                    library[next_target_lib][prov_size] = gaps[i];  // 将占用位置的元素移到下一个图书馆
                    prov_size++;
                    numbered[i] = false;  // 清除已占用标记
                }

                if (i <= lib_size) {
                    library[next_target_lib][prov_size] = library[target_lib][i];  // 将已排序元素放入下一个图书馆
                    prov_size++;
                }
            }

            target_lib = next_target_lib;  // 切换目标图书馆
            lib_size = prov_size - 1;      // 更新当前图书馆的大小
        } else {
            numbered[insert] = true;  // 标记当前位置已被占用
            gaps[insert] = index[index_pos];  // 将当前元素插入到gaps
            index_pos++;  // 处理下一个元素
        }
    }

    // 输出最终排序后的数组
    int index_pos_for_output = 0;
    for (int i = 0; index_pos_for_output < n; i++) {
        if (numbered[i] == true) {
            index[index_pos_for_output] = gaps[i];  // 将gaps中的元素放入最终数组
            index_pos_for_output++;
        }

        if (i < lib_size) {
            index[index_pos_for_output] = library[target_lib][i];  // 将图书馆中的元素放入最终数组
            index_pos_for_output++;
        }
    }

    // 释放动态分配的内存
    delete[] numbered;
    delete[] gaps;
    for (int i = 0; i < 2; ++i) {
        delete[] library[i];
    }
}

int main() {
    // 示例数据
    int index_ex[] = {-6, 5, 9, 1, 9, 1, 0, 1, -8, 4, -12};
    int n_ex = sizeof(index_ex) / sizeof(index_ex[0]);

    // 调用图书馆排序函数
    librarySort(index_ex, n_ex);

    // 输出排序后的数组
    std::cout << "排序后的数组：" << std::endl;
    for (int i = 0; i < n_ex; i++) std::cout << index_ex[i] << " ";
    std::cout << std::endl;

    /* -- 输出 --
    排序后的数组：
    -12 -8 -6 0 1 1 1 4 5 9 9
    */
}
