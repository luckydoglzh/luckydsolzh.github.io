// 返回排序后的元素，通过进行鸡尾酒选择排序（Cocktail Selection Sort）
// 这是一种排序算法，通过同时选择数组中的最小和最大元素，并将其交换到最低和最高的可用位置，
// 迭代或递归地进行排序

#include <algorithm>
#include <iostream>
#include <vector>

// 迭代版本的鸡尾酒选择排序
void CocktailSelectionSort(std::vector<int> *vec, int low, int high) {
    // 当 low <= high 时继续执行排序
    while (low <= high) {
        // 初始化最小和最大元素及其索引
        int minimum = (*vec)[low];
        int minimumindex = low;
        int maximum = (*vec)[high];
        int maximumindex = high;

        // 查找最小值和最大值及其索引
        for (int i = low; i <= high; i++) {
            if ((*vec)[i] >= maximum) {
                maximum = (*vec)[i];
                maximumindex = i;
            }
            if ((*vec)[i] <= minimum) {
                minimum = (*vec)[i];
                minimumindex = i;
            }
        }

        // 如果最小元素和最大元素不是在低位和高位，则交换它们到低位和高位
        if (low != maximumindex || high != minimumindex) {
            std::swap((*vec)[low], (*vec)[minimumindex]);
            std::swap((*vec)[high], (*vec)[maximumindex]);
        } else {
            // 如果最小和最大元素已经在正确的位置，则交换低位和高位的元素
            std::swap((*vec)[low], (*vec)[high]);
        }

        // 继续处理剩余的部分
        low++;
        high--;
    }
}

// 递归版本的鸡尾酒选择排序
void CocktailSelectionSort_v2(std::vector<int> *vec, int low, int high) {
    // 递归终止条件
    if (low >= high)
        return;

    // 初始化最小和最大元素及其索引
    int minimum = (*vec)[low];
    int minimumindex = low;
    int maximum = (*vec)[high];
    int maximumindex = high;

    // 查找最小值和最大值及其索引
    for (int i = low; i <= high; i++) {
        if ((*vec)[i] >= maximum) {
            maximum = (*vec)[i];
            maximumindex = i;
        }
        if ((*vec)[i] <= minimum) {
            minimum = (*vec)[i];
            minimumindex = i;
        }
    }

    // 如果最小元素和最大元素不是在低位和高位，则交换它们到低位和高位
    if (low != maximumindex || high != minimumindex) {
        std::swap((*vec)[low], (*vec)[minimumindex]);
        std::swap((*vec)[high], (*vec)[maximumindex]);
    } else {
        // 如果最小和最大元素已经在正确的位置，则交换低位和高位的元素
        std::swap((*vec)[low], (*vec)[high]);
    }

    // 递归处理剩余部分
    CocktailSelectionSort_v2(vec, low + 1, high - 1);
}

// 主函数，选择使用迭代或递归版本
int main() {
    int n;
    std::cout << "请输入元素的数量\n";
    std::cin >> n;
    std::vector<int> v(n);  // 创建一个大小为 n 的整数向量
    std::cout << "请输入所有的元素\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];  // 输入每个元素
    }

    int method;
    std::cout << "选择方法: \n\t0: 迭代方法\n\t1: 递归方法\t";
    std::cin >> method;

    // 根据用户输入选择方法执行排序
    if (method == 0) {
        CocktailSelectionSort(&v, 0, n - 1);  // 使用迭代版本
    } else if (method == 1) {
        CocktailSelectionSort_v2(&v, 0, n - 1);  // 使用递归版本
    } else {
        std::cerr << "未知方法" << std::endl;
        return -1;
    }

    // 输出排序后的元素
    std::cout << "排序后的元素是\n";
    for (int i = 0; i < n; ++i) {
        std::cout << v[i] << " ";  // 输出排序后的每个元素
    }

    return 0;
}
