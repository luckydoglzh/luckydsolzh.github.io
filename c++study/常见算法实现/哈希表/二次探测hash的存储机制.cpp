/**
 * @file
 * @author [achance6](https://github.com/achance6)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief 使用[二次探测哈希](https://en.wikipedia.org/wiki/Quadratic_probing)的存储机制。
 * @note 该实现可以通过使用面向对象编程风格进行优化。
 */
#include <cmath>
#include <iostream>
#include <vector>

/**
 * @addtogroup open_addressing 开放寻址
 * @{
 * @namespace quadratic_probing
 * @brief 使用[二次探测](https://en.wikipedia.org/wiki/Quadratic_probing)算法的哈希表实现。
 */
namespace quadratic_probing {
// 前向声明
using Entry = struct Entry;
bool putProber(const Entry& entry, int key);
bool searchingProber(const Entry& entry, int key);
void add(int key);

// 全局变量
int notPresent;  ///< 表示未找到的状态
std::vector<Entry> table;  ///< 哈希表
int totalSize;  ///< 表示哈希表的总大小
int tomb = -1;  ///< 表示墓碑状态
int size;  ///< 表示当前元素数量
bool rehashing;  ///< 是否正在进行再哈希

/** 节点，保存键值
 */
struct Entry {
    explicit Entry(int key = notPresent) : key(key) {}  ///< 构造函数
    int key;  ///< 键值
};

/** 哈希一个键
 * @param key 需要哈希的键值
 * @returns 键值的哈希
 */
size_t hashFxn(int key) {
    std::hash<int> hash;
    return hash(key);
}

/** 执行二次探测以解决冲突
 * @param key 需要搜索/探测的键值
 * @param searching `true` 表示仅搜索，`false` 表示分配
 * @returns `notPresent`的值。
 */
int quadraticProbe(int key, bool searching) {
    int hash = static_cast<int>(hashFxn(key));
    int i = 0;
    Entry entry;
    do {
        size_t index =
            (hash + static_cast<size_t>(std::round(std::pow(i, 2)))) %
            totalSize;
        entry = table[index];
        if (searching) {
            if (entry.key == notPresent) {
                return notPresent;  // 未找到
            }
            if (searchingProber(entry, key)) {
                std::cout << "找到键!" << std::endl;
                return index;  // 找到键
            }
            std::cout << "找到墓碑或相等的哈希，检查下一个" << std::endl;
            i++;
        } else {
            if (putProber(entry, key)) {
                if (!rehashing) {
                    std::cout << "找到位置!" << std::endl;
                }
                return index;  // 找到空位
            }
            if (!rehashing) {
                std::cout << "位置被占用，查看下一个 (下一个索引 = "
                          << (hash + static_cast<size_t>(
                                         std::round(std::pow(i + 1, 2)))) %
                                 totalSize
                          << std::endl;
            }
            i++;
        }
        if (i == totalSize * 100) {
            std::cout << "二次探测失败（无限循环）" << std::endl;
            return notPresent;  // 超过限制
        }
    } while (entry.key != notPresent);
    return notPresent;  // 未找到
}

/** 查找空位置
 * @param entry 表示表项的实例
 * @param key 需要搜索的键值
 * @returns `true` 如果键存在
 * @returns `false` 如果键不存在
 */
bool putProber(const Entry& entry, int key) {
    if (entry.key == notPresent || entry.key == tomb) {
        return true;  // 找到空位或墓碑
    }
    return false;
}

/** 查找匹配的键
 * @param entry 表示表项的实例
 * @param key 需要搜索的键值
 * @returns `true` 如果键与条目匹配
 * @returns `false` 如果键不匹配
 */
bool searchingProber(const Entry& entry, int key) {
    return entry.key == key;  // 比较键
}

/** 获取与键对应的条目实例
 * @param key 需要搜索的键值
 * @returns 如果存在，返回条目实例
 * @returns 如果不存在，返回一个新实例
 */
Entry find(int key) {
    int index = quadraticProbe(key, true);
    if (index == notPresent) {
        return Entry();  // 返回未找到实例
    }
    return table[index];  // 返回找到的条目
}

/** 显示哈希表
 * @returns 无
 */
void display() {
    for (int i = 0; i < totalSize; i++) {
        if (table[i].key == notPresent) {
            std::cout << " 空 ";
        } else if (table[i].key == tomb) {
            std::cout << " 墓 ";
        } else {
            std::cout << " " << table[i].key << " ";
        }
    }
    std::cout << std::endl;
}

/** 将哈希表重新哈希为更大的表
 * @returns 无
 */
void rehash() {
    // 必要时，避免在添加信息时打印所有信息
    rehashing = true;
    int oldSize = totalSize;
    std::vector<Entry> oldTable(table);
    // 这应该使用比totalSize * 2更大的下一个质数
    totalSize *= 2;
    table = std::vector<Entry>(totalSize);
    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i].key != -1 && oldTable[i].key != notPresent) {
            size--;  // 大小保持不变（添加时递增大小）
            add(oldTable[i].key);  // 重新添加旧表中的元素
        }
    }
    // delete[] oldTable;  // 不再需要旧表
    rehashing = false;
    std::cout << "表已重新哈希，新大小为: " << totalSize << std::endl;
}

/** 检查负载因子
 * @param key 需要哈希并添加到表中的键值
 */
void add(int key) {
    int index = quadraticProbe(key, false);
    table[index].key = key;  // 添加键值
    // 负载因子大于0.5会导致重新调整大小
    if (++size / static_cast<double>(totalSize) >= 0.5) {
        rehash();  // 进行再哈希
    }
}

/** 移除键。移除后留下墓碑。
 * @param key 需要哈希并从表中移除的键值
 */
void remove(int key) {
    int index = quadraticProbe(key, true);
    if (index == notPresent) {
        std::cout << "键未找到" << std::endl;
        return;
    }
    table[index].key = tomb;  // 标记为墓碑
    std::cout << "移除成功，留下墓碑" << std::endl;
    size--;  // 大小递减
}

/** 添加过程的信息
 * @param key 需要哈希并添加到表中的键值
 */
void addInfo(int key) {
    std::cout << "初始表: ";
    display();
    std::cout << std::endl;
    std::cout << "键 " << key << " 的哈希为 " << hashFxn(key) << " % "
              << totalSize << " == " << hashFxn(key) % totalSize;
    std::cout << std::endl;
    add(key);
    std::cout << "新表: ";
    display();
}

/** 移除过程的信息
 * @param key 需要哈希并从表中移除的键值
 */
void removalInfo(int key) {
    std::cout << "初始表: ";
    display();
    std::cout << std::endl;
    std::cout << "键 " << key << " 的哈希为 " << hashFxn(key) << " % "
              << totalSize << " == " << hashFxn(key) % totalSize;
    std::cout << std::endl;
    remove(key);
    std::cout << "新表: ";
    display();
}

}  // namespace quadratic_probing
/**
 * @}
 */

using quadratic_probing::Entry;
using quadratic_probing::table;
using quadratic_probing::totalSize;

/** 主函数
 * @returns 无
 */
int main() {
    int cmd = 0, hash = 0, key = 0;
    std::cout << "请输入哈希表的初始大小: ";
    std::cin >> totalSize;
    table = std::vector<Entry>(totalSize);  // 初始化哈希表
    bool loop = true;
    while (loop) {
        std::cout << std::endl;
        std::cout << "请选择 -" << std::endl;
        std::cout << "1. 添加键。 (仅限数字)" << std::endl;
        std::cout << "2. 移除键。" << std::endl;
        std::cout << "3. 查找键。" << std::endl;
        std::cout << "4. 生成哈希。 (仅限数字)" << std::endl;
        std::cout << "5. 显示哈希表。" << std::endl;
        std::cout << "6. 退出。" << std::endl;
        std::cin >> cmd;
        switch (cmd) {
            case 1:
                std::cout << "请输入要添加的键 = ";
                std::cin >> key;
                quadratic_probing::addInfo(key);
                break;
            case 2:
                std::cout << "请输入要移除的键 = ";
                std::cin >> key;
                quadratic_probing::removalInfo(key);
                break;
            case 3: {
                std::cout << "请输入要搜索的键 = ";
                std::cin >> key;
                quadratic_probing::Entry entry =
                    quadratic_probing::table[quadratic_probing::quadraticProbe(
                        key, true)];
                if (entry.key == quadratic_probing::notPresent) {
                    std::cout << "键未存在";
                }
                break;
            }
            case 4:
                std::cout << "请输入要生成哈希的元素 = ";
                std::cin >> key;
                std::cout << "键 " << key
                          << " 的哈希为 = " << quadratic_probing::hashFxn(key);
                break;
            case 5:
                quadratic_probing::display();  // 显示哈希表
                break;
            default:
                loop = false;  // 退出循环
                break;
        }
        std::cout << std::endl;
    }
    return 0;
}
