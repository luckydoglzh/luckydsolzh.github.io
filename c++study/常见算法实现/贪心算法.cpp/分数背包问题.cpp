#include <iostream>
using namespace std;

// 定义物品结构体
struct Item {
    int weight;  // 物品的重量
    int profit;  // 物品的利润
};

// 计算单位利润
float profitPerUnit(Item x) {
    return (float)x.profit / (float)x.weight;  // 返回利润与重量的比值
}

// 快速排序的分区函数
int partition(Item arr[], int low, int high) {
    Item pivot = arr[high];  // 选择最后一个元素作为基准
    int i = (low - 1);       // 较小元素的索引

    for (int j = low; j < high; j++) {
        // 如果当前元素的单位利润小于等于基准元素
        if (profitPerUnit(arr[j]) <= profitPerUnit(pivot)) {
            i++;  // 增加较小元素的索引
            // 交换当前元素和较小元素
            Item temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // 将基准元素放置在正确的位置
    Item temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);  // 返回基准元素的索引
}

// 快速排序函数
void quickSort(Item arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);  // 获取分区点

        // 递归排序基准元素左侧和右侧的部分
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

int main() {
    cout << "\n请输入背包的容量: ";
    float capacity;  // 背包的容量
    cin >> capacity;

    cout << "\n请输入物品的数量: ";
    int n;  // 物品的数量
    cin >> n;
    Item itemArray[n];  // 创建物品数组

    // 输入每个物品的重量和利润
    for (int i = 0; i < n; i++) {
        cout << "\n输入第 " << i + 1 << " 个物品的重量和利润: ";
        cin >> itemArray[i].weight;
        cin >> itemArray[i].profit;
    }

    // 对物品数组按单位利润进行排序
    quickSort(itemArray, 0, n - 1);

    float maxProfit = 0;  // 最大利润
    int i = n;
    // 遍历物品数组，计算最大利润
    while (capacity > 0 && --i >= 0) {
        if (capacity >= itemArray[i].weight) {  // 如果当前物品可以完全放入背包
            maxProfit += itemArray[i].profit;  // 增加物品的利润
            capacity -= itemArray[i].weight;  // 减少背包容量
            cout << "\n\t" << itemArray[i].weight << "\t"
                 << itemArray[i].profit;  // 输出物品的重量和利润
        } else {  // 如果当前物品不能完全放入背包
            maxProfit += profitPerUnit(itemArray[i]) * capacity;  // 计算放入的部分利润
            cout << "\n\t" << capacity << "\t"
                 << profitPerUnit(itemArray[i]) * capacity;  // 输出放入的部分重量和利润
            capacity = 0;  // 背包容量置为 0
            break;
        }
    }

    // 输出最大利润
    cout << "\n最大利润: " << maxProfit;

    return 0;
}
