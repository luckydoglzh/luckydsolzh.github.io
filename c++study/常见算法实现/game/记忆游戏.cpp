/**
 * @file
 * @brief 一个简单的[记忆游戏](https://en.wikipedia.org/wiki/Matching_game)
 * 具有 **3 种不同的大小** 和多个字母。
 * @details
 * 游戏的目标是找到 **所有给定字母的配对**，具体取决于表格大小。
 * 一旦找到所有实例，游戏将结束，并询问您是否想再次玩。
 *
 * 提供 **3 种不同的大小**，用户可以选择 (4x2, 5x2, 7x2)。7x2 是最大的表格大小，也是最难的模式。表格越大，**可用的字母越多**。
 *
 * @author [David Leal](https://github.com/Panquesito7)
 */

#include <algorithm>  /// 用于随机打乱元素 std::shuffle()
#include <cstdlib>    /// 用于随机数生成 std::srand()
#include <ctime>      /// 获取当前时间 std::time()
#include <iostream>   /// 输入输出操作
#include <random>     /// 随机数引擎 std::mt19937
#include <vector>     /// 向量容器 std::vector

// `Sleep` 只在 Windows 中以毫秒为单位可用。
// 然而，在 Unix/Linux 系统中使用的是 `sleep`，以秒为单位。
#ifdef _WIN32
#include <Windows.h>  /// Windows 系统下的 Sleep 函数
template <typename T>
constexpr typename std::enable_if<std::is_integral<T>::value, void>::type SLEEP(
    T milliseconds) {
    Sleep(milliseconds * 1000);  // 将毫秒转换为秒
}
#else
#include <unistd.h>  /// Unix/Linux 系统下的 sleep 函数
template <typename T>
constexpr T SLEEP(T seconds) {
    return sleep(seconds);  // 以秒为单位的睡眠
}
#endif

/**
 * @namespace
 * @brief (迷你)游戏实现。
 */
namespace games {
/**
 * @namespace
 * @brief [记忆游戏](https://en.wikipedia.org/wiki/Matching_game) 实现的函数
 */
namespace memory_game {
/**
 * @brief 工具函数，用于验证给定输入是否为数字。
 * 这对于防止程序陷入循环非常有用。
 * @tparam T 输入的类型
 * @param input 要检查的输入。
 * @returns 如果输入为空或包含非数字字符，则返回 false
 * @returns 如果输入非空且仅包含数字字符，则返回 true
 */
template <typename T>
bool is_number(const T &input) {
    if (std::cin.fail()) {  // 检查输入是否失败
        std::cin.clear();   // 清除失败状态
        std::cin.ignore(256, '\n');  // 忽略错误输入

        return false;  // 输入无效
    }

    return true;  // 输入有效
}

/**
 * @brief 初始化表格并填充字母。
 * @tparam T 表格的类型。
 * @param table 要初始化的表格。
 * @returns void
 */
template <typename T>
void init(std::vector<T> *table) {
    std::vector<char> letters(7);  // 存储字母的容器

    // 根据大小减少/增加字母的数量。
    if ((*table).size() == 10) {  // 5x2
        letters = {'A', 'E', 'Z', 'P', 'D'};
    } else if ((*table).size() == 8) {  // 4x2
        letters = {'A', 'E', 'Z', 'D'};
    } else if ((*table).size() == 14) {  // 7x2
        letters = {'A', 'E', 'Z', 'P', 'D', 'B', 'M'};
    }

    std::vector<char> pairs;  // 存储成对字母
    for (char letter : letters) {
        pairs.push_back(letter);   // 添加字母
        pairs.push_back(letter);    // 添加成对字母
    }

    std::shuffle(pairs.begin(), pairs.end(),
                 std::mt19937(std::random_device()()));  // 随机打乱字母

    for (int i = 0; i < (*table).size(); i++) {
        (*table)[i] = pairs[i];  // 初始化表格
    }

    std::cout << "所有可用的字母类型为: ";  // 打印可用字母类型

    for (int i = 0; i < letters.size(); i++) {
        if (i == letters.size() - 1) {
            std::cout << "和 " << letters[i] << "。\n\n";  // 最后一个字母的输出
        } else {
            std::cout << letters[i] << ", ";  // 其他字母的输出
        }
    }
}

/**
 * @brief 工具函数，用于打印表格。
 * @tparam T 表格的类型。
 * @param table 要打印的表格。
 * @returns void
 */
template <typename T>
void print_table(const std::vector<T> &table) {
    std::cout << "| ";
    std::vector<T> table_print(table.size());  // 临时表格用于打印

    for (int i = 0; i < table.size(); i++) {
        table_print[i] = ' ';  // 初始化打印表格

        if (table[i] != 0) {
            table_print[i] = table[i];  // 将已找到的字母放入打印表格
        }
    }

    for (int i = 0; i < table.size(); i++) {
        if (i % 5 == 0 && i != 0) {
            std::cout << "\n| ";  // 每5个字母换行
        }

        std::cout << table_print[i] << " | ";  // 打印字母
    }
}

// 函数原型。由于 `ask_data` 调用 `reset_data`，而 `reset_data` 调用 `ask_data`，
// 因此需要声明此函数。
template <typename T>
void reset_data(const std::vector<T> &, int *, int *, int *);

/**
 * @brief 函数询问用户在之前选择的表格中输入数据。
 * @tparam T 表格的类型。
 * @param table 用于获取用户输入和数据的表格。
 * @param answer 用户的答案。
 * @param old_answer 用户的上一个答案。
 * @param memory_count 用于检查用户是否已经回答了两个值的计数器。
 * @returns void
 */
template <typename T>
void ask_data(const std::vector<T> &table, int *answer, int *old_answer,
              int *memory_count) {
    (*old_answer) = (*answer);  // 记录上一个答案
    print_table(table);  // 打印表格

    std::cout << "\n\n在这里输入您的回答（索引号）：\n";  // 提示用户输入
    std::cin >> (*answer);  // 获取用户输入

    if (!is_number((*answer))) {  // 验证输入是否为数字
        std::cout << "\n您必须输入一个有效的数字。\n\n";  // 提示用户输入无效
        reset_data(table, answer, old_answer, memory_count);  // 重置数据并重新获取输入
    }

    // 增加内存计数，以检查用户是否已回答两个值。
    (*memory_count)++;

    if (((*answer) > table.size()) || ((*answer) < 1)) {  // 检查输入范围
        std::cout << "\n您无法检查不存在的值（或无效的数字）。\n\n";  // 提示用户输入无效
        reset_data(table, answer, old_answer, memory_count);  // 重置数据并重新获取输入
    }

    if ((*old_answer) == (*answer)) {  // 检查用户是否重复选择相同的值
        std::cout << "\n您不能检查相同的值两次。\n\n";  // 提示用户无法重复选择
        reset_data(table, answer, old_answer, memory_count);  // 重置数据并重新获取输入
    }

    // 如果已经回答了两个匹配值，但用户检查了未回答的值和已回答的值，则程序将标记为不匹配，但我们
    // 必须不允许用户重复检查相同的值。
    if ((table[(*answer) - 1] != 0) &&
        ((table[(*old_answer)] == 0) || (table[(*old_answer)] != 0))) {
        std::cout << "\n您不能检查相同的值两次。\n\n";  // 提示用户无法重复选择
        reset_data(table, answer, old_answer, memory_count);  // 重置数据并重新获取输入
    }
}

/**
 * @brief 工具函数，用于在用户输入无效值时重置数据。
 * @tparam T 表格的类型。
 * @param table 要显示的表格。
 * @param answer 用户
