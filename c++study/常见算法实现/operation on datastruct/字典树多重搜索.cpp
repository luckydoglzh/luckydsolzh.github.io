#include <algorithm>  /// 用于 std::count
#include <cassert>    /// 用于 assert
#include <cctype>     /// 用于 tolower
#include <cstring>    /// 用于字符串操作
#include <iostream>   /// 用于输入输出操作
#include <queue>      /// 用于 std::priority_queue

/**
 * @namespace operations_on_datastructures
 * @brief 数据结构的操作
 */
namespace operations_on_datastructures {
/**
 * @namespace trie_operations
 * @brief 实现 [Trie 数据结构](https://iq.opengenus.org/autocomplete-using-trie-data-structure/) 的功能
 */
namespace trie_operations {
/**
 * @brief 定义了 trie 节点结构并包含执行操作的方法
 */
class Tnode {
 private:
    static constexpr uint8_t ENGLISH_ALPHABET_SIZE = 26;
    // 指向字母的指针
    std::vector<Tnode *> english;

    // 标记是否为单词的结尾
    bool endOfWord;

    // 存储单词搜索频率
    uint32_t frequency;

 public:
    Tnode() {
        english.resize(ENGLISH_ALPHABET_SIZE, nullptr);
        endOfWord = false;
        frequency = 0;
    }
    // 复制构造函数
    Tnode(const Tnode &node) {
        english = node.english;
        endOfWord = node.endOfWord;
        frequency = node.frequency;
    }

    Tnode &operator=(const Tnode &node) = default;

    Tnode(Tnode &&) = default;

    Tnode &operator=(Tnode &&) = default;

    /**
     * @brief 计算一个节点在 trie 中的子节点数
     * @param node 要计算子节点数的 trie 节点
     * @return 节点的子节点数（最多 26 个）
     */
    inline uint8_t numberOfChildren(Tnode *node) {
        return ENGLISH_ALPHABET_SIZE - std::count(node->english.begin(), node->english.end(), nullptr);
    }

    // 执行 trie 操作的方法
    void Insert(const std::string &entry);
    void Delete(std::string entry);
    void DeleteFrom(Tnode *delete_from, std::string delete_string, int remove_index);
    bool SearchPresence(const std::string &key);
    void SuggestAutocomplete(Tnode *new_root, const std::string &prefix);
    void SearchSuggestions(const std::string &key);
    void SuggestFreqAutocomplete(
        Tnode *new_root, const std::string &prefix,
        std::priority_queue<std::pair<int, std::string>> *suggestions);
    void SearchFreqSuggestions(const std::string &key);
    void SelectionTop_3(
        std::priority_queue<std::pair<int, std::string>> *suggestions);

    // 释放动态分配的对象
    ~Tnode() {
        int i = 0;
        for (i = 0; i < ENGLISH_ALPHABET_SIZE; i++) {
            if (english[i]) {
                delete english[i];
            }
        }
    }
};

/**
 * @brief 在 trie 中插入一个单词
 * @param entry 要插入的字符串
 */
void Tnode::Insert(const std::string &entry) {
    Tnode *cur_pos = this;
    int letter_index = 0;

    for (auto &i : entry) {
        // 忽略大小写
        letter_index = tolower(i) - 97;

        // 如果字符对应的节点不存在，则为每个字符分配一个新节点
        if (cur_pos->english[letter_index] == nullptr) {
            cur_pos->english[letter_index] = new Tnode();
        }

        cur_pos = cur_pos->english[letter_index];
    }
    // 当前节点指向最后一个字符，将其标记为单词的结尾
    cur_pos->endOfWord = true;
}

/**
 * @brief 递归地从给定的节点删除指定的单词
 * @param delete_from 当前要删除的节点
 * @param delete_string 要删除的字符串
 * @param remove_index 删除操作的起始索引
 */
void Tnode::DeleteFrom(Tnode *delete_from, std::string delete_string, int remove_index) {
    if (delete_string.size() == remove_index) {
        int letter_index = tolower(delete_string[remove_index]) - 97;

        DeleteFrom(delete_from->english[letter_index], delete_string, remove_index + 1);

        delete delete_from;
    }
}

/**
 * @brief 从 trie 中删除一个单词
 * @param entry 要删除的字符串
 */
void Tnode::Delete(std::string entry) {
    Tnode *cur_pos = this, *delete_from = this;
    int letter_index = 0, delete_from_index = 0, i = 0, n = entry.size();

    for (i = 0; i < n; i++) {
        // 忽略大小写
        letter_index = tolower(entry[i]) - 97;

        // 如果字符对应的节点不存在，返回 "Entry not Found"
        if (cur_pos->english[letter_index] == nullptr) {
            std::cout << "Entry not Found" << std::endl;
            return;
        }

        // 如果当前节点是单词结尾或有多个子节点，则不能删除
        if (numberOfChildren(cur_pos) > 1 || cur_pos->endOfWord) {
            delete_from = cur_pos;
            delete_from_index = i - 1;
        }

        cur_pos = cur_pos->english[letter_index];
    }

    // 如果 cur_pos 指向的节点不是单词的结尾，表示未找到该单词
    if (!cur_pos->endOfWord) {
        std::cout << "Entry not Found" << std::endl;
        return;
    }

    // 如果 cur_pos 是叶节点，解除标记并清除频率
    if (numberOfChildren(cur_pos)) {
        cur_pos->endOfWord = false;
        cur_pos->frequency = 0;
        return;
    }

    // 删除操作
    letter_index = tolower(entry[delete_from_index + 1]) - 97;
    cur_pos = delete_from->english[letter_index];
    delete_from->english[letter_index] = nullptr;

    if (n > delete_from_index + 2) {
        DeleteFrom(cur_pos, entry, delete_from_index + 2);
    } else {
        delete cur_pos;
    }
}

/**
 * @brief 检查一个单词在 trie 中是否存在
 * @param key 要搜索的字符串
 * @return 如果找到了返回 true，找不到返回 false
 */
bool Tnode::SearchPresence(const std::string &key) {
    Tnode *cur_pos = this;
    int letter_index = 0;

    for (auto &i : key) {
        letter_index = tolower(i) - 97;
        // 如果字符对应的节点不存在，返回 false
        if (cur_pos->english[letter_index] == nullptr) {
            return false;
        }
        cur_pos = cur_pos->english[letter_index];
    }
    // 如果当前节点是单词的结尾，则说明找到了该单词
    if (cur_pos->endOfWord) {
        (cur_pos->frequency)++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief 根据给定前缀递归地查找所有符合条件的单词
 * @param new_root 当前节点
 * @param prefix 给定的前缀
 */
void Tnode::SuggestAutocomplete(Tnode *new_root, const std::string &prefix) {
    for (int i = 0; i < ENGLISH_ALPHABET_SIZE; i++) {
        if (new_root->english[i] != nullptr) {
            // 只有当节点是单词结尾时才进行打印
            if (new_root->english[i]->endOfWord) {
                std::cout << prefix + char(i + 97) << std::endl;
            }

            SuggestAutocomplete(new_root->english[i], prefix + char(i + 97));
        }
    }
}

/**
 * @brief 列出所有与给定前缀相匹配的单词
 * @param key 给定的字符串
 */
void Tnode::SearchSuggestions(const std::string &key) {
    Tnode *cur_pos = nullptr, *prev_pos = nullptr;
    cur_pos = prev_pos = this;  // 用两个指针来保持当前状态
    int letter_index = 0;
    std::string prefix = "";  // 用于存储最长的公共前缀

    for (auto &i : key) {
        letter_index = tolower(i) - 97;
        prev_pos = cur_pos;  // 更新前一个节点为当前最长公共前缀的结尾节点

        // 如果当前节点不存在，则返回当前最长公共前缀的建议
        if (cur_pos->english[letter_index] == nullptr) {
            SuggestAutocomplete(prev_pos, prefix);
            std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - "
                      << std::endl;
            return;
        }
        prefix += char(tolower(i));
        cur_pos = cur_pos->english[letter_index];
    }
    SuggestAutocomplete(cur_pos, prefix);
}

/**
 * @brief 根据给定前缀和频率输出可能的建议
 * @param new_root 当前节点
 * @param prefix 给定的前缀
 * @param suggestions 优先队列存储
 */
void Tnode::SuggestFreqAutocomplete(
    Tnode *new_root, const std::string &prefix,
    std::priority_queue<std::pair<int, std::string>> *suggestions) {
    for (int i = 0; i < ENGLISH_ALPHABET_SIZE; i++) {
        if (new_root->english[i] != nullptr) {
            // 如果是单词结尾
            if (new_root->english[i]->endOfWord) {
                suggestions->push(
                    std::make_pair(new_root->english[i]->frequency, prefix + char(i + 97)));
            }
            SuggestFreqAutocomplete(new_root->english[i], prefix + char(i + 97), suggestions);
        }
    }
}

/**
 * @brief 获取与给定前缀匹配的所有单词，并按频率返回建议
 * @param key 给定的前缀
 */
void Tnode::SearchFreqSuggestions(const std::string &key) {
    Tnode *cur_pos = nullptr, *prev_pos = nullptr;
    cur_pos = prev_pos = this;
    int letter_index = 0;
    std::string prefix = "";

    for (auto &i : key) {
        letter_index = tolower(i) - 97;
        prev_pos = cur_pos;

        if (cur_pos->english[letter_index] == nullptr) {
            SuggestFreqAutocomplete(prev_pos, prefix, nullptr);
            return;
        }
        prefix += char(tolower(i));
        cur_pos = cur_pos->english[letter_index];
    }
    std::priority_queue<std::pair<int, std::string>> suggestions;
    SuggestFreqAutocomplete(cur_pos, prefix, &suggestions);
    SelectionTop_3(&suggestions);
}

/**
 * @brief 获取前三个建议
 * @param suggestions 优先队列
 */
void Tnode::SelectionTop_3(
    std::priority_queue<std::pair<int, std::string>> *suggestions) {
    for (int i = 0; i < 3; i++) {
        if (!suggestions->empty()) {
            std::cout << suggestions->top().second << " (" << suggestions->top().first << ")"
                      << std::endl;
            suggestions->pop();
        }
    }
}

}  // namespace trie_operations
}  // namespace operations_on_datastructures

int main() {
    using namespace operations_on_datastructures::trie_operations;

    // 创建 Trie 根节点
    Tnode *trie = new Tnode();

    // 插入示例单词
    trie->Insert("hello");
    trie->Insert("hell");
    trie->Insert("heaven");

    // 搜索示例单词
    std::cout << "Presence of 'hell': " << trie->SearchPresence("hell") << std::endl;

    // 获取和显示建议
    trie->SearchSuggestions("he");
    delete trie;
    return 0;
}
