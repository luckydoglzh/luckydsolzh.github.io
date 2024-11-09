// 使用通用算法对字符串集合进行排序时，结果是按字母数字顺序排序的。
// 如果字符串是数字字符串，它会导致不自然的排序结果。

// 例如，一个字符串数组：1,10,100,2,20,200,3,30,300
// 使用常规排序会得到 1,10,100,2,20,200,3,30,300，
// 即使我们知道正确的排序顺序应该是 1,2,3,10,20,30,100,200,300。

// 这个程序使用了一个比较器来按数字顺序而不是字母数字顺序对数组进行排序。

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// 定义比较器函数，用于按数字顺序排序
bool NumericSort(std::string a, std::string b) {
    // 去掉前导零
    while (a[0] == '0') {
        a.erase(a.begin());
    }
    while (b[0] == '0') {
        b.erase(b.begin());
    }

    int n = a.length();  // 获取字符串 a 的长度
    int m = b.length();  // 获取字符串 b 的长度

    // 如果两个字符串长度相等，则按字典顺序排序
    if (n == m)
        return a < b;

    // 否则按字符串的长度排序，长度短的排在前面
    return n < m;
}

int main() {
    int n;

    // 输入需要排序的元素个数
    std::cout << "请输入需要按数字顺序排序的元素个数：\n";
    std::cin >> n;

    // 创建一个字符串向量来存储输入的数字字符串
    std::vector<std::string> v(n);

    // 输入字符串数组
    std::cout << "请输入数字字符串：\n";
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }

    // 使用默认排序（按字母数字顺序排序）
    std::sort(v.begin(), v.end());
    std::cout << "按字母数字顺序排序后的结果：\n";
    for (int i = 0; i < n; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";

    // 使用自定义比较器进行按数字顺序排序
    std::sort(v.begin(), v.end(), NumericSort);
    std::cout << "按数字顺序排序后的结果：\n";
    for (int i = 0; i < n; i++) {
        std::cout << v[i] << " ";
    }

    return 0;
}
