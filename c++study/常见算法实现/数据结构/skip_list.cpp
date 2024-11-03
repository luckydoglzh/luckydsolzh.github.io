/**
 * @file skip_list.cpp
 * @brief 用于快速搜索和插入的数据结构，时间复杂度为 \f$O(\log n)\f$
 * @details
 * 跳表是一种用于存储已排序项目的结构，利用层次化的链表连接项目的稀疏子序列
 *
 * 参考资料：[GeeksForGeek](https://www.geeksforgeeks.org/skip-list/),
 * [OpenGenus](https://iq.opengenus.org/skip-list) 的伪代码和代码
 * @author [enqidu](https://github.com/enqidu)
 * @author [Krishna Vedala](https://github.com/kvedala)
 */

#include <array>
#include <cstring>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

/** \namespace data_structures
 * \brief 数据结构算法
 */
namespace data_structures {
constexpr int MAX_LEVEL = 2;        ///< 跳表的最大层数
constexpr float PROBABILITY = 0.5;  ///< “抛硬币”的概率

/**
 * 节点结构 [Key][Node*, Node*...]
 */
struct Node {
    int key;      ///< 键值
    void* value;  ///< 值的指针
    std::vector<std::shared_ptr<Node>> forward;  ///< 在所有层次上的后续节点

    /**
     * 创建具有给定键、层次和值的节点
     * @param key 用于比较的数字
     * @param level 节点的最大层次
     */
    Node(int key, int level, void* value = nullptr) : key(key), value(value) {
        // 初始化 forward 向量
        for (int i = 0; i < (level + 1); i++) {
            forward.push_back(nullptr);
        }
    }
};

/**
 * 跳表类实现基本方法
 */
class SkipList {
    int level;                     ///< 跳表的最大层数
    std::shared_ptr<Node> header;  ///< 指向头节点的指针

 public:
    /**
     * 跳表构造函数。初始化头节点，作为搜索的起始节点
     */
    SkipList() {
        level = 0;
        // 初始化头节点
        header = std::make_shared<Node>(-1, MAX_LEVEL);
    }

    /**
     * 返回跳表的随机层次。
     * 每一层的概率是上一层的二分之一。
     * @return 跳表的随机层次
     */
    int randomLevel() {
        int lvl = 0;
        // 通过随机数决定当前层次
        while (static_cast<float>(std::rand()) / RAND_MAX < PROBABILITY &&
               lvl < MAX_LEVEL) {
            lvl++;
        }
        return lvl;
    }

    /**
     * 插入具有给定键和值的元素；
     * 其层次由 randomLevel() 函数计算得出。
     * @param key 用于比较的数字
     * @param value 值的指针，可以是任何类型
     */
    void insertElement(int key, void* value) {
        std::cout << "Inserting " << key << "...";
        std::shared_ptr<Node> x = header;
        std::array<std::shared_ptr<Node>, MAX_LEVEL + 1> update;
        update.fill(nullptr);

        // 从当前层开始向下搜索
        for (int i = level; i >= 0; i--) {
            while (x->forward[i] != nullptr && x->forward[i]->key < key) {
                x = x->forward[i];
            }
            update[i] = x;  // 更新指针
        }

        x = x->forward[0];  // 移动到下一层的节点

        bool doesnt_exist = (x == nullptr || x->key != key);  // 检查节点是否存在
        if (doesnt_exist) {
            int rlevel = randomLevel();  // 随机生成新的层次

            // 如果新层次大于当前最大层次，更新当前层次
            if (rlevel > level) {
                for (int i = level + 1; i < rlevel + 1; i++) update[i] = header;
                level = rlevel;  // 更新最大层数
            }

            // 创建新节点并插入
            std::shared_ptr<Node> n = std::make_shared<Node>(key, rlevel, value);
            for (int i = 0; i <= rlevel; i++) {
                n->forward[i] = update[i]->forward[i];  // 更新指针
                update[i]->forward[i] = n;  // 连接新节点
            }
            std::cout << "Inserted" << std::endl;

        } else {
            std::cout << "Exists" << std::endl;  // 节点已存在
        }
    }

    /**
     * 通过键删除元素，并打印是否成功删除
     * @param key 用于比较的数字
     */
    void deleteElement(int key) {
        std::shared_ptr<Node> x = header;
        std::array<std::shared_ptr<Node>, MAX_LEVEL + 1> update;
        update.fill(nullptr);

        // 从当前层开始向下搜索
        for (int i = level; i >= 0; i--) {
            while (x->forward[i] != nullptr && x->forward[i]->key < key) {
                x = x->forward[i];
            }
            update[i] = x;  // 更新指针
        }

        x = x->forward[0];  // 移动到下一层的节点

        bool doesnt_exist = (x == nullptr || x->key != key);  // 检查节点是否存在

        if (!doesnt_exist) {
            // 删除节点
            for (int i = 0; i <= level; i++) {
                if (update[i]->forward[i] != x) {
                    break;  // 如果指针不指向要删除的节点，则退出
                }
                update[i]->forward[i] = x->forward[i];  // 连接到后续节点
            }
            /* 移除空层 */
            while (level > 0 && header->forward[level] == nullptr) level--;
            std::cout << "Deleted" << std::endl;  // 输出删除成功信息
        } else {
            std::cout << "Doesn't exist" << std::endl;  // 节点不存在
        }
    }

    /**
     * 在跳表结构中搜索元素
     * @param key 用于比较的数字
     * @return 节点值的指针
     */
    void* searchElement(int key) {
        std::shared_ptr<Node> x = header;
        std::cout << "Searching for " << key << std::endl;

        // 从当前层开始向下搜索
        for (int i = level; i >= 0; i--) {
            while (x->forward[i] && x->forward[i]->key < key) {
                x = x->forward[i];
            }
        }

        x = x->forward[0];  // 移动到下一层的节点
        if (x && x->key == key) {
            std::cout << "Found" << std::endl;  // 找到节点
            return x->value;  // 返回节点的值
        } else {
            std::cout << "Not Found" << std::endl;  // 节点未找到
            return nullptr;
        }
    }

    /**
     * 显示跳表的层次结构
     */
    void displayList() {
        std::cout << "Displaying list:\n";
        for (int i = 0; i <= level; i++) {
            std::shared_ptr<Node> node = header->forward[i];
            std::cout << "Level " << (i) << ": ";
            while (node != nullptr) {
                std::cout << node->key << " ";  // 输出当前层次的所有节点
                node = node->forward[i];
            }
            std::cout << std::endl;
        }
    }
};

}  // namespace data_structures

/**
 * 主函数：
 * 创建并插入随机的 2^[层数] 个元素到跳表中，然后显示它
 */
int main() {
    std::srand(std::time(nullptr));  // 设置随机数种子

    data_structures::SkipList lst;  // 创建跳表实例

    // 插入随机元素到跳表
    for (int j = 0; j < (1 << (data_structures::MAX_LEVEL + 1)); j++) {
        int k = (std::rand() % (1 << (data_structures::MAX_LEVEL + 2)) + 1);
        lst.insertElement(k, &j);
    }

    lst.displayList();  // 显示跳表

    return 0;  // 返回成功
}
