/**
 * @file
 *
 * @author Anmol3299
 * \brief 一个基本的字典树（Trie）类实现，用于存储小写字符串。
 */
#include <iostream>  // 输入输出操作
#include <memory>    // 用于std::shared_ptr<>
#include <string>    // 用于std::string类

/**
 * 基本的字典树实现，用于存储小写字符串。
 * 可以通过将 @ ALPHABETS 的值更改为 128 来扩展实现以支持所有 ASCII 字符。
 */
class Trie {
 private:
    static constexpr size_t ALPHABETS = 26; // 字母表大小

    /**
     * 字典树节点的结构。
     * 该结构不需要构造函数，因为我们使用初始化列表进行初始化，
     * 这比使用构造函数更有效。
     */
    struct TrieNode {
        // 一个大小为26的指针数组，指示单词的字符是否存在。
        std::shared_ptr<TrieNode> character[ALPHABETS]{nullptr};
        bool isEndOfWord{false}; // 标记是否为单词的结尾
    };

    /**
     * 检查节点是否有子节点可以形成单词。
     * @param node 要检查的节点。
     * @return 如果找到子节点，则返回 `true`
     * @return 如果没有找到子节点，则返回 `false`
     */
    inline static bool hasChildren(std::shared_ptr<TrieNode> node) {
        for (size_t i = 0; i < ALPHABETS; i++) {
            if (node->character[i]) {
                return true;
            }
        }
        return false;
    }

    /**
     * 递归辅助函数从字典树中删除单词。首先，递归遍历到单词最后一个字符的位置。
     * 如果单词未找到，函数将抛出运行时错误。成功到达单词的最后一个字符后，设置
     * isEndOfWord 为 false，并在没有子节点时删除节点，否则返回当前节点。
     * @param word 需要从字典树中删除的字符串。
     * @param curr 当前节点。
     * @param index 当前单词的索引。
     * @return 如果当前节点有子节点，则返回 @ curr，否则返回 nullptr。
     * @throw 如果 @ word 未在字典树中找到，则抛出运行时错误。
     */
    std::shared_ptr<TrieNode> removeWordHelper(const std::string& word,
                                               std::shared_ptr<TrieNode> curr,
                                               size_t index) {
        if (word.size() == index) {
            if (curr->isEndOfWord) {
                curr->isEndOfWord = false; // 标记不是单词结尾
            }
            if (hasChildren(curr)) {
                return curr; // 如果有子节点，返回当前节点
            }
            return nullptr; // 删除当前节点
        }

        size_t idx = word[index] - 'a'; // 计算字符在数组中的索引

        // 如果没有找到当前字符的节点，抛出运行时错误
        if (!curr->character[idx]) {
            throw std::runtime_error(std::move(std::string("Word not found.")));
        }

        curr->character[idx] =
            removeWordHelper(word, curr->character[idx], index + 1);

        // 检查节点是否有子节点
        if (curr->character[idx] || hasChildren(curr)) {
            return curr; // 如果有子节点，返回当前节点
        }
        return nullptr; // 返回 nullptr
    }

 public:
    /// 构造函数初始化字典树的根节点。
    Trie() : m_root(std::make_shared<TrieNode>()) {}

    /**
     * 将单词插入字典树。
     * @param word 需要插入的单词。
     */
    void insert(const std::string& word) {
        auto curr = m_root;
        for (char ch : word) {
            size_t index = ch - 'a'; // 计算字符在数组中的索引

            // 如果当前字符的节点不存在，则创建一个新节点。
            if (!curr->character[index]) {
                curr->character[index] = std::make_shared<TrieNode>();
            }

            curr = curr->character[index]; // 移动到下一个节点
        }
        curr->isEndOfWord = true; // 标记为单词的结尾
    }

    /**
     * 检查字典树中是否存在某个单词。
     * @param word 需要查找的单词。
     * @return 如果单词在字典树中找到并且 isEndOfWord 为 true，则返回 True。
     * @return 如果单词未找到或 isEndOfWord 为 false，则返回 False。
     */
    bool search(const std::string& word) {
        auto curr = m_root;
        for (char ch : word) {
            size_t index = ch - 'a'; // 计算字符在数组中的索引

            // 如果任何字符的节点未找到，则返回 false。
            if (!curr->character[index]) {
                return false;
            }
            curr = curr->character[index]; // 移动到下一个节点
        }
        return curr->isEndOfWord; // 返回是否为单词结尾
    }

    // 调用辅助函数删除单词
    void removeWord(const std::string& word) {
        m_root = removeWordHelper(word, m_root, 0);
    }

 private:
    // 存储字典树根节点的数据成员。
    std::shared_ptr<TrieNode> m_root;
};

/**
 * 主函数
 */
int main() {
    Trie trie;
    trie.insert("hel"); // 插入单词 "hel"
    trie.insert("hello"); // 插入单词 "hello"
    trie.removeWord("hel"); // 删除单词 "hel"
    std::cout << trie.search("hello") << '\n'; // 查找 "hello"，输出 1（true）

    return 0;
}
