/**
 * @file double_hash_hash_table.cpp
 * @author [achance6](https://github.com/achance6)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief 使用 [双重哈希键](https://en.wikipedia.org/wiki/Double_hashing) 的存储机制。
 * @note 此实现可以通过使用面向对象编程风格进行优化。
 */
#include <iostream>
#include <memory>
#include <vector>

/**
 * @addtogroup open_addressing 开放地址法
 * @{
 * @namespace double_hashing
 * @brief 使用 [双重哈希](https://en.wikipedia.org/wiki/Double_hashing) 算法实现哈希表。
 */
namespace double_hashing {
// 前向声明
using Entry = struct Entry;
bool putProber(const Entry& entry, int key);
bool searchingProber(const Entry& entry, int key);
void add(int key);

// 未记录的全局变量
int notPresent;          // 表示未找到的键
std::vector<Entry> table; // 哈希表
int totalSize;          // 哈希表的总大小
int tomb = -1;         // 表示删除的键
int size;              // 当前键的数量
bool rehashing;        // 是否正在重新哈希

/** 存储键的节点对象 */
struct Entry {
    explicit Entry(int key = notPresent) : key(key) {}  ///< 构造函数
    int key;                                            ///< 键值
};

/**
 * @brief 哈希一个键。使用 STL 库的 `std::hash()` 函数。
 *
 * @param key 要哈希的值
 * @return 键的哈希值
 */
size_t hashFxn(int key) {
    std::hash<int> hash;
    return hash(key);
}

/**
 * @brief 用于第二个哈希函数
 *
 * @param key 要哈希的键值
 * @return 键的哈希值
 */
size_t otherHashFxn(int key) {
    std::hash<int> hash;
    return 1 + (7 - (hash(key) % 7));
}

/**
 * @brief 执行双重哈希以解决冲突
 *
 * @param key 要应用双重哈希的键值
 * @param searching `true` 表示检查冲突
 * @return 如果找到，返回键的索引；如果没有冲突，返回新的哈希
 */
int doubleHash(int key, bool searching) {
    int hash = static_cast<int>(hashFxn(key));
    int i = 0;
    Entry entry;
    do {
        int index =
            static_cast<int>(hash + (i * otherHashFxn(key))) % totalSize;
        entry = table[index];
        if (searching) {
            if (entry.key == notPresent) {
                return notPresent;
            }
            if (searchingProber(entry, key)) {
                std::cout << "找到键！" << std::endl;
                return index;
            }
            std::cout << "找到墓碑或相等的哈希，检查下一个" << std::endl;
            i++;
        } else {
            if (putProber(entry, key)) {
                if (!rehashing) {
                    std::cout << "找到位置！" << std::endl;
                }
                return index;
            }
            if (!rehashing) {
                std::cout << "位置已被占用，查找下一个（下一个索引："
                          << " "
                          << static_cast<int>(hash + (i * otherHashFxn(key))) % 
                                 totalSize
                          << ")" << std::endl;
            }
            i++;
        }
        if (i == totalSize * 100) {
            std::cout << "双重哈希探测失败" << std::endl;
            return notPresent;
        }
    } while (entry.key != notPresent);
    return notPresent;
}

/** 在向量中查找空位
 * @param entry 要搜索的向量
 * @param key 要搜索的键
 * @returns 如果键不存在或是墓碑，则返回 `true`
 * @returns 如果已经占用，则返回 `false`
 */
bool putProber(const Entry& entry, int key) {
    if (entry.key == notPresent || entry.key == tomb) {
        return true;
    }
    return false;
}

/** 查找匹配的键
 * @param entry 要搜索的向量
 * @param key 要搜索的键值
 * @returns 如果找到，返回 `true`
 * @returns 如果未找到，返回 `false`
 */
bool searchingProber(const Entry& entry, int key) {
    if (entry.key == key) {
        return true;
    }
    return false;
}

/** 显示哈希表
 * @returns 无
 */
void display() {
    for (int i = 0; i < totalSize; i++) {
        if (table[i].key == notPresent) {
            std::cout << " 空 ";
        } else if (table[i].key == tomb) {
            std::cout << " 墓碑 ";
        } else {
            std::cout << " ";
            std::cout << table[i].key;
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

/** 将表重新哈希到更大的表
 * @returns 无
 */
void rehash() {
    // 必要的以避免一次性打印添加信息
    rehashing = true;
    int oldSize = totalSize;
    std::vector<Entry> oldTable(table);
    // 这应该使用大于 totalSize * 2 的下一个质数
    table = std::vector<Entry>(totalSize * 2);
    totalSize *= 2;
    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i].key != -1 && oldTable[i].key != notPresent) {
            size--;  // 大小保持不变（添加时递增）
            add(oldTable[i].key);
        }
    }

    rehashing = false;
    std::cout << "表已重新哈希，新的大小为： " << totalSize << std::endl;
}

/** 检查加载因子
 * @param key 要添加到表中的键值
 */
void add(int key) {
    int index = doubleHash(key, false);
    table[index].key = key;
    // 加载因子大于 0.5 时导致调整大小
    if (++size / static_cast<double>(totalSize) >= 0.5) {
        rehash();
    }
}

/** 移除键。移除后留下墓碑。
 * @param key 要移除的键值
 */
void remove(int key) {
    int index = doubleHash(key, true);
    if (index == notPresent) {
        std::cout << "未找到键" << std::endl;
    }
    table[index].key = tomb;
    std::cout << "删除成功，留下墓碑" << std::endl;
    size--;
}

/** 添加过程的信息
 * @param key 要添加到表中的键值
 */
void addInfo(int key) {
    std::cout << "初始表： ";
    display();
    std::cout << std::endl;
    std::cout << key << " 的哈希值是 " << hashFxn(key) << " % "
              << totalSize << " == " << hashFxn(key) % totalSize;
    std::cout << std::endl;
    add(key);
    std::cout << "新表： ";
    display();
}

/** 删除过程的信息
 * @param key 要从表中移除的键值
 */
void removalInfo(int key) {
    std::cout << "初始表： ";
    display();
    std::cout << std::endl;
    std::cout << key << " 的哈希值是 " << hashFxn(key) << " % "
              << totalSize << " == " << hashFxn(key) % totalSize;
    std::cout << std::endl;
    remove(key);
    std::cout << "新表： ";
    display();
}
}  // namespace double_hashing
/**
 * @}
 */

using double_hashing::Entry;
using double_hashing::table;
using double_hashing::totalSize;

/** 主程序
 * @returns 成功时返回 0
 */
int main() {
    int cmd = 0, hash = 0, key = 0;
    std::cout << "Enter the initial size of Hash Table. = ";
    std::cin >> totalSize;
    table = std::vector<Entry>(totalSize);
    bool loop = true;
    while (loop) {
        std::cout << std::endl;
        std::cout << "PLEASE CHOOSE -" << std::endl;
        std::cout << "1. Add key. (Numeric only)" << std::endl;
        std::cout << "2. Remove key." << std::endl;
        std::cout << "3. Find key." << std::endl;
        std::cout << "4. Generate Hash. (Numeric only)" << std::endl;
        std::cout << "5. Display Hash table." << std::endl;
        std::cout << "6. Exit." << std::endl;
        std::cin >> cmd;
        switch (cmd) {
            case 1:
                std::cout << "Enter key to add = ";
                std::cin >> key;
                double_hashing::addInfo(key);
                break;
            case 2:
                std::cout << "Enter key to remove = ";
                std::cin >> key;
                double_hashing::removalInfo(key);
                break;
            case 3: {
                std::cout << "Enter key to search = ";
                std::cin >> key;
                Entry entry = table[double_hashing::doubleHash(key, true)];
                if (entry.key == double_hashing::notPresent) {
                    std::cout << "Key not present";
                }
                break;
            }
            case 4:
                std::cout << "Enter element to generate hash = ";
                std::cin >> key;
                std::cout << "Hash of " << key
                          << " is = " << double_hashing::hashFxn(key);
                break;
            case 5:
                double_hashing::display();
                break;
            default:
                loop = false;
                break;
                // delete[] table;
        }
        std::cout << std::endl;
    }
    return 0;
}