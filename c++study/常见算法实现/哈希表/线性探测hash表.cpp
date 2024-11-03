/**
 * @file
 * @author [achance6](https://github.com/achance6)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief 使用 [线性探测哈希](https://en.wikipedia.org/wiki/Linear_probing) 的存储机制。
 * @note 此实现可以通过使用面向对象编程风格进行优化。
 */
#include <iostream>
#include <vector>

/**
 * @addtogroup open_addressing 开放地址法
 * @{
 * @namespace linear_probing
 * @brief 使用 [线性探测](https://en.wikipedia.org/wiki/Linear_probing) 算法实现哈希表。
 */
namespace linear_probing {
// 前向声明
using Entry = struct Entry;
bool putProber(const Entry& entry, int key);
bool searchingProber(const Entry& entry, int key);
void add(int key);

// 未记录的全局变量
int notPresent;         // 表示未找到的键
std::vector<Entry> table; // 哈希表
int totalSize;         // 哈希表的总大小
int tomb = -1;        // 表示删除的键
int size;             // 当前键的数量
bool rehashing;       // 是否正在重新哈希

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
 * @brief 执行线性探测以解决冲突
 *
 * @param key 要哈希的键值
 * @param searching `true` 表示检查冲突
 * @return 如果找到，返回键的索引；如果没有冲突，返回新的哈希
 */
int linearProbe(int key, bool searching) {
    int hash = static_cast<int>(hashFxn(key));
    int i = 0;
    Entry entry;
    do {
        int index = static_cast<int>((hash + i) % totalSize);
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
                std::cout << "位置已被占用，查找下一个" << std::endl;
            }
            i++;
        }
        if (i == totalSize) {
            std::cout << "线性探测失败" << std::endl;
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
    totalSize *= 2; // 这里应该使用大于 totalSize * 2 的下一个质数
    table = std::vector<Entry>(totalSize);
    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i].key != -1 && oldTable[i].key != notPresent) {
            size--;  // 大小保持不变（添加时递增）
            add(oldTable[i].key);
        }
    }
    rehashing = false;
    std::cout << "表已重新哈希，新的大小为： " << totalSize << std::endl;
}

/** 使用线性探测添加条目。检查加载因子。
 * @param key 要添加的键值
 */
void add(int key) {
    int index = linearProbe(key, false);
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
    int index = linearProbe(key, true);
    if (index == notPresent) {
        std::cout << "未找到键" << std::endl;
    }
    std::cout << "删除成功，留下墓碑" << std::endl;
    table[index].key = tomb;
    size--;
}

/** 添加过程的信息
 * @param key 要添加的键值
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
}  // namespace linear_probing
/**
 * @}
 */

using linear_probing::Entry;
using linear_probing::table;
using linear_probing::totalSize;

/** 主程序
 * @returns 成功时返回 0
 */
int main() {
    int cmd = 0, hash = 0, key = 0;
    std::cout << "输入哈希表的初始大小: ";
    std::cin >> totalSize;
    table = std::vector<Entry>(totalSize);
    bool loop = true;
    while (loop) {
        std::cout << std::endl;
        std::cout << "请选择 -" << std::endl;
        std::cout << "1. 添加键（仅限数字）" << std::endl;
        std::cout << "2. 删除键" << std::endl;
        std::cout << "3. 查找键" << std::endl;
        std::cout << "4. 生成哈希（仅限数字）" << std::endl;
        std::cout << "5. 显示哈希表" << std::endl;
        std::cout << "6. 退出" << std::endl;
        std::cin >> cmd;
        switch (cmd) {
            case 1:
                std::cout << "输入要添加的键 = ";
                std::cin >> key;
                linear_probing::addInfo(key);
                break;
            case 2:
                std::cout << "输入要删除的键 = ";
                std::cin >> key;
                linear_probing::removalInfo(key);
                break;
            case 3: {
                std::cout << "输入要搜索的键 = ";
                std::cin >> key;
                Entry entry = table[linear_probing::linearProbe(key, true)];
                if (entry.key == linear_probing::notPresent) {
                    std::cout << "键不存在" << std::endl;
                }
                break;
            }
            case 4:
                std::cout << "输入要生成哈希的元素 = ";
                std::cin >> key;
                std::cout << key << " 的哈希值是 = " << linear_probing::hashFxn(key);
                break;
            case 5:
                linear_probing::display();
                break;
            default:
                loop = false;
                break;
        }
        std::cout << std::endl;
    }
    return 0;
}
