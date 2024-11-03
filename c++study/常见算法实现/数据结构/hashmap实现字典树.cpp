/**
 * @file
 * @author [Venkata Bharath](https://github.com/bharath000)
 * @brief 实现 [Trie](https://en.wikipedia.org/wiki/Trie) 数据结构，使用HashMap来处理不同字符，并基于前缀预测单词的方法。
 * @details Trie数据结构使用unordered map实现，以优化内存，开发了predict_words方法来根据给定前缀推荐单词，同时实现了insert、delete、search、startwith等方法。
 * @see trie_modern.cpp 的差异
 */
#include <cassert>        /// 用于断言
#include <iostream>       /// IO操作
#include <memory>         /// 用于std::shared_ptr
#include <stack>          /// 用于std::stack
#include <unordered_map>  /// 用于std::unordered_map
#include <vector>         /// 用于std::vector

/**
 * @namespace data_structures
 * @brief 数据结构算法
 */
namespace data_structures {

    /**
     * @namespace trie_using_hashmap
     * @brief 使用hashmap实现的Trie数据结构的函数
     */
    namespace trie_using_hashmap {

        /**
         * @brief Trie类，使用hashmap实现的Trie，每个Trie节点的字符类型为char16_t，具有插入、删除、搜索、以某前缀开头及推荐基于给定前缀的单词的方法。
         */
        class Trie {
        private:
            /**
             * @brief 表示Trie节点的结构体
             */
            struct Node {
                std::unordered_map<char16_t, std::shared_ptr<Node>>
                    children;  ///< unordered map，键类型为char16_t，值为Node的shared pointer类型
                bool word_end = false;  ///< 布尔变量，表示节点是否为单词的结尾
            };

            std::shared_ptr<Node> root_node =
                std::make_shared<Node>();  ///< 声明Trie的根节点

        public:
            ///< 构造函数
            Trie() = default;

            /**
             * @brief 将字符串插入到Trie中
             * @param word 要插入的字符串
             */
            void insert(const std::string& word) {
                std::shared_ptr<Node> curr = root_node;
                for (char ch : word) {
                    if (curr->children.find(ch) == curr->children.end()) {
                        curr->children[ch] = std::make_shared<Node>();
                    }
                    curr = curr->children[ch];
                }

                if (!curr->word_end && curr != root_node) {
                    curr->word_end = true;  // 将当前节点标记为单词结尾
                }
            }

            /**
             * @brief 在Trie中搜索一个单词/字符串
             * @param word 要搜索的字符串
             * @returns `true` 如果找到
             * @returns `false` 如果未找到
             */
            bool search(const std::string& word) {
                std::shared_ptr<Node> curr = root_node;
                for (char ch : word) {
                    if (curr->children.find(ch) == curr->children.end()) {
                        return false;  // 如果当前字符不在子节点中，返回false
                    }
                    curr = curr->children[ch];
                    if (!curr) {
                        return false;  // 如果当前节点为空，返回false
                    }
                }

                return curr->word_end;  // 返回当前节点是否为单词的结尾
            }

            /**
             * @brief 搜索以给定前缀开头的单词/字符串
             * @param prefix 要搜索的前缀
             * @returns `true` 如果找到
             * @returns `false` 如果未找到
             */
            bool startwith(const std::string& prefix) {
                std::shared_ptr<Node> curr = root_node;
                for (char ch : prefix) {
                    if (curr->children.find(ch) == curr->children.end()) {
                        return false;  // 如果当前字符不在子节点中，返回false
                    }
                    curr = curr->children[ch];
                }
                return true;  // 找到前缀，返回true
            }

            /**
             * @brief 从Trie中删除一个单词/字符串
             * @param word 要删除的字符串
             */
            void delete_word(std::string word) {
                std::shared_ptr<Node> curr = root_node;
                std::stack<std::shared_ptr<Node>> nodes;  // 存储路径节点
                int cnt = 0;  // 计数器，用于判断节点是否为单词的结尾
                for (char ch : word) {
                    if (curr->children.find(ch) == curr->children.end()) {
                        return;  // 如果字符不存在，直接返回
                    }
                    if (curr->word_end) {
                        cnt++;  // 如果当前节点为单词的结尾，计数
                    }

                    nodes.push(curr->children[ch]);
                    curr = curr->children[ch];
                }
                // 仅当它是一个单词且它有后续子节点或前缀时才删除
                if (nodes.top()->word_end) {
                    nodes.top()->word_end = false;  // 标记为非单词结尾
                }
                // 仅当它没有后续子节点且没有前缀时才删除
                while (!(nodes.top()->word_end) && nodes.top()->children.empty()) {
                    nodes.pop();
                    nodes.top()->children.erase(word.back());  // 从父节点中删除字符
                    word.pop_back();
                }
            }

            /**
             * @brief 辅助函数，根据给定前缀从前缀节点向下迭代，通过递归获取所有可能的单词
             * @param prefix 字符串前缀
             * @param element 前缀结束时的节点
             * @param results 用于存储所有可能单词的列表
             * @returns 推荐的单词列表
             */
            std::vector<std::string> get_all_words(std::vector<std::string> results,
                                                   const std::shared_ptr<Node>& element,
                                                   std::string prefix) {
                if (element->word_end) {
                    results.push_back(prefix);  // 如果当前节点是单词的结尾，添加到结果中
                }
                if (element->children.empty()) {
                    return results;  // 如果没有子节点，返回结果
                }
                for (auto const& x : element->children) {
                    std::string key = "";
                    key = x.first;
                    prefix += key;  // 追加当前字符到前缀

                    results =
                        get_all_words(results, element->children[x.first], prefix);  // 递归获取子节点的单词

                    prefix.pop_back();  // 移除最后一个字符以便恢复前缀
                }

                return results;  // 返回所有结果
            }

            /**
             * @brief 预测/推荐以给定前缀开头的单词
             * @param prefix 要搜索的前缀
             * @returns 推荐的单词列表
             */
            std::vector<std::string> predict_words(const std::string& prefix) {
                std::vector<std::string> result;
                std::shared_ptr<Node> curr = root_node;
                // 遍历到给定前缀在Trie中的末尾

                for (char ch : prefix) {
                    if (curr->children.find(ch) == curr->children.end()) {
                        return result;  // 如果字符不存在，返回空结果
                    }

                    curr = curr->children[ch];
                }

                // 如果给定的前缀是唯一的单词并且没有子节点
                if (curr->word_end && curr->children.empty()) {
                    result.push_back(prefix);  // 将前缀添加到结果中
                    return result;
                }

                result = get_all_words(result, curr, prefix);  ///< 迭代和递归获取推荐单词

                return result;  // 返回结果
            }
        };
    }  // namespace trie_using_hashmap
}  // namespace data_structures

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    data_structures::trie_using_hashmap::Trie obj;
    // 使用插入方法将数据插入到Trie中，并用搜索方法进行测试
    obj.insert("app");
    obj.insert("abscond");
    obj.insert("about");
    obj.insert("apps");
    obj.insert("apen");
    obj.insert("apples");
    obj.insert("apple");
    obj.insert("approach");
    obj.insert("bus");
    obj.insert("buses");
    obj.insert("Apple");
    obj.insert("Bounce");

    assert(!obj.search("appy"));
    std::cout << "appy 不是Trie中的单词" << std::endl;

    assert(!obj.search("car"));
    std::cout << "car 不是Trie中的单词" << std::endl;
    assert(obj.search("app"));
    assert(obj.search("apple"));
    assert(obj.search("apples"));
    assert(obj.search("apps"));
    assert(obj.search("apen"));
    assert(obj.search("approach"));
    assert(obj.search("about"));
    assert(obj.search("abscond"));
    assert(obj.search("bus"));
    assert(obj.search("buses"));
    assert(obj.search("Bounce"));
    assert(obj.search("Apple"));

    std::cout << "所有插入的单词都在Trie中" << std::endl;

    // 测试以前缀开头的方法
    assert(!obj.startwith("approachs"));
    assert(obj.startwith("approach"));
    assert(obj.startwith("about"));
    assert(!obj.startwith("appy"));
    assert(obj.startwith("abscond"));
    assert(obj.startwith("bus"));
    assert(obj.startwith("buses"));
    assert(obj.startwith("Bounce"));
    assert(obj.startwith("Apple"));
    assert(obj.startwith("abs"));
    assert(obj.startwith("b"));
    assert(obj.startwith("bus"));
    assert(obj.startwith("Bo"));
    assert(obj.startwith("A"));
    assert(!obj.startwith("Ca"));
    assert(!obj.startwith("C"));

    std::cout << "所有对startwith方法的测试均已通过" << std::endl;

    // 测试predict_words/根据给定前缀推荐单词的方法
    std::vector<std::string> pred_words = obj.predict_words("a");

    for (const std::string& str : obj.predict_words("a")) {
        std::cout << str << std::endl;
    }
    assert(pred_words.size() == 8);
    std::cout << "返回了所有以前缀a开头的单词" << std::endl;
    
    pred_words = obj.predict_words("app");

    for (const std::string& str : pred_words) {
        std::cout << str << std::endl;
    }

    assert(pred_words.size() == 5);
    std::cout << "返回了所有以前缀app开头的单词" << std::endl;
    
    pred_words = obj.predict_words("A");

    for (const std::string& str : pred_words) {
        std::cout << str << std::endl;
    }

    assert(pred_words.size() == 1);
    std::cout << "返回了所有以前缀A开头的单词" << std::endl;
    
    pred_words = obj.predict_words("bu");

    for (const std::string& str : pred_words) {
        std::cout << str << std::endl;
    }

    assert(pred_words.size() == 2);
    std::cout << "返回了所有以前缀bu开头的单词" << std::endl;

    // 删除方法的测试
    obj.delete_word("app");
    assert(!obj.search("app"));
    std::cout << "单词app已成功删除" << std::endl;

    pred_words = obj.predict_words("app");
    for (const std::string& str : pred_words) {
        std::cout << str << std::endl;
    }
    assert(pred_words.size() == 4);
    std::cout << "app已成功删除" << std::endl;

    // 测试中文
    obj.insert("苹果");
    assert(obj.startwith("苹"));
    pred_words = obj.predict_words("h");

    assert(pred_words.size() == 0);
    std::cout << "没有以前缀h开头的单词" << std::endl;

    std::cout << "所有测试均已通过" << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 表示正常退出
 */
int main() {
    test();  // 运行自测实现
    return 0;
}
