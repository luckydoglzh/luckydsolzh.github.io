/**
 * @file
 * @author [@Arctic2333](https://github.com/Arctic2333)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief 实现小写字母的 [Trie](https://en.wikipedia.org/wiki/Trie) 数据结构。
 * @note 函数 ::data_structure::trie::deleteString 可能存在错误。
 * @see trie_modern.cpp
 */
#include <array>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/** \namespace data_structures
 * \brief 数据结构算法
 */
namespace data_structures {
/**
 * @brief 小写字母 `a-z` 的 [Trie](https://en.wikipedia.org/wiki/Trie) 实现
 */
class trie {
 private:
    static constexpr uint8_t NUM_CHARS = 26;  ///< 字母表的字符数量
    /** @brief 递归树节点的共享指针数组 */
    std::array<std::shared_ptr<trie>, NUM_CHARS << 1> arr; // 使用数组存储字符指针
    bool isEndofWord = false;  ///< 标识节点是否为终止节点

    /**
     * @brief 将字符转换为用于索引的整数
     *
     * @param ch 要索引的字符
     * @return 无符号整数索引
     */
    uint8_t char_to_int(const char& ch) const {
        if (ch >= 'A' && ch <= 'Z') {
            return ch - 'A'; // 大写字母的索引
        } else if (ch >= 'a' && ch <= 'z') {
            return ch - 'a' + NUM_CHARS; // 小写字母的索引
        }

        std::cerr << "存在无效字符。正在退出...";
        std::exit(EXIT_FAILURE); // 无效字符处理
        return 0;
    }

    /** 在给定的根 trie 中搜索字符串是否存在
     * @param str 要搜索的字符串
     * @param index 开始搜索的索引
     * @returns `true` 如果找到
     * @returns `false` 如果未找到
     */
    bool search(const std::shared_ptr<trie>& root, const std::string& str,
                int index) {
        if (index == str.length()) {
            if (!root->isEndofWord) {
                return false; // 如果不是单词的结尾，返回 false
            }
            return true; // 找到单词
        }
        int j = char_to_int(str[index]); // 获取字符的索引
        if (!root->arr[j]) {
            return false; // 如果没有找到该字符，返回 false
        }
        return search(root->arr[j], str, index + 1); // 递归搜索下一个字符
    }

 public:
    trie() = default;  ///< 类的默认构造函数

    /** 将字符串插入到字典树中
     * @param str 要插入的字符串
     */
    void insert(const std::string& str) {
        std::shared_ptr<trie> root(nullptr); // 初始化根指针

        for (const char& ch : str) {
            int j = char_to_int(ch); // 获取字符的索引
            if (root) {
                if (root->arr[j]) {
                    root = root->arr[j]; // 如果节点已存在，移动到该节点
                } else {
                    std::shared_ptr<trie> temp(new trie()); // 创建新节点
                    root->arr[j] = temp; // 将新节点添加到数组
                    root = temp; // 移动到新节点
                }
            } else if (arr[j]) {
                root = arr[j]; // 如果根节点已存在，移动到该节点
            } else {
                std::shared_ptr<trie> temp(new trie()); // 创建新节点
                arr[j] = temp; // 将新节点添加到根数组
                root = temp; // 移动到新节点
            }
        }
        root->isEndofWord = true; // 设置为单词的结尾
    }

    /** 在字典树中搜索字符串是否存在
     * @param str 要搜索的字符串
     * @param index 开始搜索的索引
     * @returns `true` 如果找到
     * @returns `false` 如果未找到
     */
    bool search(const std::string& str, int index) {
        if (index == str.length()) {
            if (!isEndofWord) {
                return false; // 如果不是单词的结尾，返回 false
            }
            return true; // 找到单词
        }
        int j = char_to_int(str[index]); // 获取字符的索引
        if (!arr[j]) {
            return false; // 如果没有找到该字符，返回 false
        }
        return search(arr[j], str, index + 1); // 递归搜索下一个字符
    }

    /**
     * 删除字符串，如果它不是任何其他字符串的前缀，则删除它。
     * 如果是前缀，则将 ::data_structure::trie::isEndofWord 设置为 false。
     * @note 函数 ::data_structure::trie::deleteString 可能存在错误
     * @todo 检查函数 ::data_structure::trie::deleteString 及其注释行
     * @param str 要删除的字符串
     * @param index 要删除的索引
     * @returns `true` 如果成功
     * @returns `false` 如果失败
     */
    bool deleteString(const std::string& str, int index) {
        if (index == str.length()) {
            if (!isEndofWord) {
                return false; // 如果不是单词的结尾，返回 false
            }
            isEndofWord = false; // 设置为不是单词的结尾
            // 下面的代码行 - 可能的错误来源？
            // for (int i = 0; i < NUM_CHARS; i++)
            //     if (!arr[i])
            //         return false;
            return true; // 删除成功
        }
        int j = char_to_int(str[index]); // 获取字符的索引
        if (!arr[j]) {
            return false; // 如果没有找到该字符，返回 false
        }
        bool var = deleteString(str, index + 1); // 递归删除下一个字符
        if (var) {
            arr[j].reset(); // 重置指针
            if (isEndofWord) {
                return false; // 如果是单词结尾，返回 false
            } else {
                int i = 0;
                for (i = 0; i < NUM_CHARS; i++) {
                    if (arr[i]) {
                        return false; // 如果还有子节点，返回 false
                    }
                }
                return true; // 删除成功
            }
        }

        /* 不应该在这里返回 */
        std::cout << __func__ << ":" << __LINE__
                  << "不应该到达此行\n";
        return false; // 错误处理
    }
};
}  // namespace data_structures

/**
 * @brief 测试函数
 * @returns void
 */
static void test() {
    data_structures::trie root; // 创建字典树
    root.insert("Hello"); // 插入 "Hello"
    root.insert("World"); // 插入 "World"

    assert(!root.search("hello", 0)); // 查找 "hello"
    std::cout << "hello - " << root.search("hello", 0) << "\n";

    assert(root.search("Hello", 0)); // 查找 "Hello"
    std::cout << "Hello - " << root.search("Hello", 0) << "\n";

    assert(!root.search("Word", 0)); // 查找 "Word"
    std::cout << "Word - " << root.search("Word", 0) << "\n";

    assert(root.search("World", 0)); // 查找 "World"
    std::cout << "World - " << root.search("World", 0) << "\n";

    // 以下代码行给出错误的输出
    // root.deleteString("hello", 0); // 删除 "hello"
    // assert(!root.search("hello", 0)); // 再次查找 "hello"
    // std::cout << "hello - " << root.search("world", 0) << "\n"; // 查找 "world"
}

/**
 * @brief 主函数
 * @return 0 表示正常退出
 */
int main() {
    test(); // 运行测试

    return 0; // 正常退出
}
