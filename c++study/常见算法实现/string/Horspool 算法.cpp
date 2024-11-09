/**
 * @file
 * @brief Horspool 算法，用于查找字符串是否包含子字符串 (https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore%E2%80%93Horspool_algorithm)
 * @author [Harry Kontakis](https://github.com/ckontakis)
 */

#include <iostream>
#include <unordered_map>
#include <cassert>

/**
 * @namespace strings
 * @brief 字符串处理算法
 */
namespace strings {
/**
 * @namespace horspool
 * @brief [Horspool 算法](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore%E2%80%93Horspool_algorithm)相关函数
 */
namespace horspool {
/**
 * 一个函数，用于生成给定模式字符串的移动表（Shift Table），这是 Horspool 算法的一部分。
 * @param prototype 是我们用来构建移动表的子字符串
 * @return 返回 Horspool 算法的移动表
 */
std::unordered_map<char, int> findShiftTable(const std::string &prototype) {
    std::unordered_map<char, int>
        shiftTable;  // 用哈希表存储字符和对应的移动步数

    for (int i = 0; i < prototype.size();
         i++) {  // 遍历模式字符串的所有字符
        if (shiftTable.find(prototype[i]) == 
            shiftTable.end()) {  // 如果字符不在哈希表中
            if (i != prototype.size() - 1) {
                shiftTable.insert(std::make_pair(
                    prototype[i], prototype.size() - i - 1));  // 插入字符和对应的移动步数
            } else {
                shiftTable.insert(std::make_pair(
                    prototype[i],
                    prototype.size()));  // 对于最后一个字符，移动步数为模式字符串的长度
            }
        } else {
            if (i != prototype.size() - 1) {
                shiftTable[prototype[i]] = prototype.size() - i - 1;  // 更新已有字符的移动步数
            }
        }
    }
    return shiftTable;  // 返回生成的移动表
}

/**
 * 实现 Horspool 算法，用于在文本中查找子字符串。
 * @param text 是要搜索的字符串
 * @param prototype 是要查找的子字符串
 * @returns 如果文本中包含子字符串，则返回 true；否则返回 false
 */
bool horspool(const std::string &text, const std::string &prototype) {
    std::unordered_map<char, int> shiftTable = findShiftTable(prototype);  // 获取模式字符串的移动表

    int i = static_cast<int>(
        prototype.size() - 1);  // 设置文本中当前对比位置的索引
    while (i < text.size()) {
        int j = i, k = 0;
        bool flag = true;

        for (int z = static_cast<int>(prototype.size() - 1); z >= 0 && flag;
             z--) {  // 从后向前逐个检查模式字符串和文本中的字符是否匹配
            if (text[j] == prototype[z]) {
                k++;
                j--;  // 如果字符匹配，继续向前移动
            } else {
                flag = false;  // 如果字符不匹配，设置 flag 为 false，跳出循环
            }
        }

        if (k == prototype.size()) {  // 如果所有字符都匹配，说明找到了子字符串
            return true;
        } else {
            if (shiftTable.find(text[i]) != shiftTable.end()) {
                i += shiftTable[text[i]];  // 如果移动表中包含该字符，则根据移动表的值移动
            } else {
                i += prototype.size();  // 如果字符不在移动表中，则移动整个模式字符串的长度
            }
        }
    }
    return false;  // 如果没有找到匹配的子字符串，返回 false
}
} // namespace horspool
} // namespace strings

/**
 * @brief Horspool 算法的测试用例函数
 * @returns void
 */
static void test(){
    assert(strings::horspool::horspool("Hello World","World") == true);  // 测试文本包含子字符串
    assert(strings::horspool::horspool("Hello World"," World") == true);  // 测试文本包含带空格的子字符串
    assert(strings::horspool::horspool("Hello World","ello") == true);    // 测试模式字符串在文本中间
    assert(strings::horspool::horspool("Hello World","rld") == true);     // 测试模式字符串在文本末尾
    assert(strings::horspool::horspool("Hello","Helo") == false);         // 测试不匹配的情况
    assert(strings::horspool::horspool("c++_algorithms","c++_algorithms") == true);  // 测试完全匹配
    assert(strings::horspool::horspool("c++_algorithms","c++_") == true);  // 测试部分匹配
    assert(strings::horspool::horspool("Hello","Hello World") == false);  // 测试模式字符串比文本短
    assert(strings::horspool::horspool("c++_algorithms","") == false);     // 测试空子字符串
    assert(strings::horspool::horspool("c++","c") == true);               // 测试匹配单个字符
    assert(strings::horspool::horspool("3458934793","4793") == true);     // 测试数字串匹配
    assert(strings::horspool::horspool("3458934793","123") == false);    // 测试不匹配数字串
}

/**
 * @brief 主函数，调用测试函数
 * @returns 0 程序退出时返回 0
 */
int main(){
    test();  // 运行测试函数
    return 0;
}
