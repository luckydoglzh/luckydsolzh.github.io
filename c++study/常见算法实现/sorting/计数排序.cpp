// C++ 程序：计数排序 (Counting Sort)
#include <iostream>

using namespace std;

// 计数排序函数
void countSort(string arr) {
    string output;  // 用于存储排序后的字符串

    int count[256]; // 假设字符集为 ASCII，最多有 256 个不同字符
    int i;
    
    // 初始化计数数组，所有元素初始为 0
    for (int i = 0; i < 256; i++) count[i] = 0;

    // 统计字符串中每个字符的出现次数
    for (i = 0; arr[i]; ++i) ++count[arr[i]];

    // 计算每个字符的累计频率，count[i] 表示小于等于字符 i 的字符数量
    for (i = 1; i < 256; ++i) count[i] += count[i - 1];

    // 反向填充输出数组，根据字符的累计频率
    for (i = 0; arr[i]; ++i) {
        output[count[arr[i]] - 1] = arr[i];  // 将当前字符放到正确的位置
        --count[arr[i]];  // 更新字符的计数
    }

    // 将排序后的结果复制回原始数组
    for (i = 0; arr[i]; ++i) arr[i] = output[i];

    // 输出排序后的字符数组
    cout << "排序后的字符数组是: " << arr;
}

int main() {
    string arr;  // 输入字符串
    cin >> arr;  // 读取用户输入的字符串

    countSort(arr);  // 调用计数排序函数

    return 0;
}
