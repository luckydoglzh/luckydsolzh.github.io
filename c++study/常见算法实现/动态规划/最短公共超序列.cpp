/**
 * @file
 * @brief SCS 是字符串 Z，它是字符串 X 和 Y 的最短超序列（在 Z 中可能不连续，但顺序保持）。
 *
 * @details
 * 该算法使用与最长公共子序列（LCS）相同的查找表方法。
 * 例如：例 1：
 * X: 'ABCXYZ', Y: 'ABZ'，则 Z 将是 'ABCXYZ'（y 不连续但顺序正确）。
 *
 * 例如：例 2：
 * X: 'AGGTAB', Y: 'GXTXAYB'，则 Z 将是 'AGGXTXAYB'。
 * @author [Ridhish Jain](https://github.com/ridhishjain)
 * @see 更多信息请参考 [SCS](https://en.wikipedia.org/wiki/Shortest_common_supersequence_problem)
 * @see 相关问题 [Leetcode](https://leetcode.com/problems/shortest-common-supersequence/)
*/

// 头文件
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

/**
 * @namespace dynamic_programming
 * @brief 动态规划算法
 */
namespace dynamic_programming {

    /**
    * @namespace shortest_common_supersequence
    * @brief 最短公共超序列算法
    */
    namespace shortest_common_supersequence {
        
        /**
         * 实现最短公共超序列算法，使用查找表方法。
         * @param str1 第一个字符串 'X'
         * @param str2 第二个字符串 'Y'
         * @returns 字符串 'Z'，即 X 和 Y 的超序列 
        */
        std::string scs(const std::string &str1, const std::string &str2) {

            // 边界情况
            // 如果 str1 或 str2 或两者都为空
            if(str1.empty() && str2.empty()) {
                return "";
            }
            else if(str1.empty()) {
                return str2;
            }
            else if(str2.empty()) {
                return str1;
            }

            // 创建查找表
            std::vector <std::vector <int>> lookup(str1.length() + 1, std::vector <int> (str2.length() + 1, 0));
      
            for(int i = 1; i <= str1.length(); i++) {
                for(int j = 1; j <= str2.length(); j++) {
                    if(str1[i - 1] == str2[j - 1]) {
                        lookup[i][j] = lookup[i - 1][j - 1] + 1; // 字符相同
                    }
                    else {
                        lookup[i][j] = std::max(lookup[i - 1][j], lookup[i][j - 1]); // 字符不同
                    }
                }
            }

            // 构建超序列
            // i 和 j 最初指向字符串的末尾
            // 超序列将向后构建
            int i = str1.length();
            int j = str2.length();
            std::string s;
      
            while(i > 0 && j > 0) {
                // 如果 str1 和 str2 的字符相同
                // 只需将它们添加一次到 s
                if(str1[i - 1] == str2[j - 1]) {
                    s.push_back(str1[i - 1]);
                    i--;
                    j--;
                }
                // 否则检查查找表以找出字符的出现
                else {
                    if(lookup[i - 1][j] > lookup[i][j - 1]) {
                        s.push_back(str1[i - 1]);
                        i--;
                    }
                    else {
                        s.push_back(str2[j - 1]);
                        j--;
                    }
                }
            }

            // 复制剩余元素
            // 如果 j 先变为 0
            while(i > 0) {
                s.push_back(str1[i - 1]);
                i--;
            }

            // 如果 i 先变为 0
            while(j > 0) {
                s.push_back(str2[j - 1]);
                j--;
            }

            // 由于超序列是向后构建的
            // 返回前需要反转字符串
            reverse(s.begin(), s.end());
            return s;
        }
    } // namespace shortest_common_supersequence
} // namespace dynamic_programming

/** 
 * 测试函数
 * @return void 
*/
static void test() {
    // 自定义输入向量
    std::vector <std::vector <std::string>> scsStrings {
        {"ABCXYZ", "ABZ"},
        {"ABZ", "ABCXYZ"},
        {"AGGTAB", "GXTXAYB"},
        {"X", "Y"},
    };

    // 使用 scs 函数计算的输出向量
    std::vector <std::string> calculatedOutput(4, "");
    int i = 0;
    for(auto & scsString : scsStrings) {
        calculatedOutput[i] = dynamic_programming::shortest_common_supersequence::scs(
            scsString[0], scsString[1]
        );
        i++;
    }

    // 根据问题描述的预期输出向量
    std::vector <std::string> expectedOutput {
        "ABCXYZ",
        "ABCXYZ",
        "AGGXTXAYB",
        "XY"
    };

    // 使用 assert 函数测试实现
    // 如果任何预期测试失败，将引发错误
    // 否则不做任何事情
    for(int i = 0; i < scsStrings.size(); i++) {
        assert(expectedOutput[i] == calculatedOutput[i]);
    }

    std::cout << "所有测试均成功通过！\n";
    return;
}

/** 主函数（驱动代码）*/
int main() {
    // 测试实现
    test();

    // 用户输入
    std::string s1, s2;
    std::cin >> s1;
    std::cin >> s2;

    std::string ans;

    // 用户输出
    ans = dynamic_programming::shortest_common_supersequence::scs(s1, s2);
    std::cout << ans;
    return 0;
}
