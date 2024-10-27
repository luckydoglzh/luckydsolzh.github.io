/**
 * @file chaining.cpp
 * @author [vasutomar](https://github.com/vasutomar)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief 实现 [哈希链](https://en.wikipedia.org/wiki/Hash_chain)。
 */

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

/**
 * @brief 哈希链类，具有指定的模数
 */
class hash_chain {
 private:
    /**
     * @brief 定义一个链表节点
     */
    using Node = struct Node {
        int data{};                         ///< 节点中存储的数据
        std::shared_ptr<struct Node> next;  ///< 指向下一个节点的指针
    };

    std::vector<std::shared_ptr<Node>> head;  ///< 节点数组
    int _mod;                                 ///< 类的模数

 public:
    /**
     * @brief 构造一个新的哈希链对象
     *
     * @param mod 哈希链的模数
     */
    explicit hash_chain(int mod) : _mod(mod) {
        while (mod--) head.push_back(nullptr);  // 初始化链表头
    }

    /**
     * @brief 创建并添加一个新节点，给定值和高度
     *
     * @param x 新节点的值
     * @param h 节点的高度
     */
    void add(int x, int h) {
        std::shared_ptr<Node> curr;
        std::shared_ptr<Node> temp(new Node);
        temp->data = x;  // 设置新节点的数据
        temp->next = nullptr;  // 新节点的下一个指针为nullptr

        // 如果当前高度的头节点为空，则直接添加
        if (!head[h]) {
            head[h] = temp;
            curr = head[h];
        } else {
            // 如果头节点不为空，则找到链表的末尾添加新节点
            curr = head[h];
            while (curr->next) curr = curr->next;  // 遍历到链表末尾
            curr->next = temp;  // 添加新节点
        }
    }

    /**
     * @brief 显示哈希链
     */
    void display() {
        std::shared_ptr<Node> temp = nullptr;
        int i = 0;
        for (i = 0; i < _mod; i++) {
            if (!head[i]) {
                std::cout << "键 " << i << " 是空的" << std::endl;  // 如果链表为空
            } else {
                std::cout << "键 " << i << " 有值 = " << std::endl;
                temp = head[i];
                while (temp->next) {
                    std::cout << temp->data << " " << std::endl;  // 显示节点数据
                    temp = temp->next;
                }
                std::cout << temp->data;  // 显示最后一个节点数据
                std::cout << std::endl;
            }
        }
    }

    /**
     * @brief 计算当前链的值的哈希值
     *
     * @param x 计算模数的值
     * @return x 的模数
     * @note 声明为
     * [`virtual`](https://en.cppreference.com/w/cpp/language/virtual)，以便
     * 自定义实现的类可以修改哈希函数。
     */
    virtual int hash(int x) const { return x % _mod; }

    /**
     * @brief 查找值和对应的哈希是否存在
     *
     * @param x 要搜索的值
     * @param h 对应的哈希键
     * @returns `true` 如果元素被找到
     * @returns `false` 如果元素未被找到
     */
    bool find(int x, int h) const {
        std::shared_ptr<Node> temp = head[h];
        if (!head[h]) {
            // 索引不存在
            std::cout << "元素未找到" << std::endl;
            return false;
        }

        // 扫描数据值
        while (temp->data != x && temp->next) temp = temp->next;

        if (temp->next) {
            std::cout << "元素已找到" << std::endl;
            return true;
        }

        // 隐式的else条件
        // 即，temp->next == nullptr
        if (temp->data == x) {
            std::cout << "元素已找到" << std::endl;
            return true;
        }

        // 进一步的隐式else条件
        std::cout << "元素未找到" << std::endl;
        return false;
    }
};

/** 主函数
 * @returns `0` 永远返回0
 */
int main() {
    int c = 0, x = 0, mod = 0, h = 0;
    std::cout << "输入哈希表的大小: " << std::endl;
    std::cin >> mod;

    hash_chain mychain(mod);  // 创建哈希链对象

    bool loop = true;  // 循环标志
    while (loop) {
        std::cout << std::endl;
        std::cout << "请选择 -" << std::endl;
        std::cout << "1. 添加元素。" << std::endl;
        std::cout << "2. 查找元素。" << std::endl;
        std::cout << "3. 生成哈希。" << std::endl;
        std::cout << "4. 显示哈希表。" << std::endl;
        std::cout << "5. 退出。" << std::endl;
        std::cin >> c;  // 用户选择操作
        switch (c) {
            case 1:
                std::cout << "输入要添加的元素: " << std::endl;
                std::cin >> x;
                h = mychain.hash(x);  // 计算哈希值
                h = std::abs(h);  // 取绝对值
                mychain.add(x, h);  // 添加元素
                break;
            case 2:
                std::cout << "输入要查找的元素: " << std::endl;
                std::cin >> x;
                h = mychain.hash(x);  // 计算哈希值
                mychain.find(x, h);  // 查找元素
                break;
            case 3:
                std::cout << "输入要生成哈希的元素: " << std::endl;
                std::cin >> x;
                std::cout << x << " 的哈希值是: " << mychain.hash(x)
                          << std::endl;  // 显示哈希值
                break;
            case 4:
                mychain.display();  // 显示哈希表
                break;
            default:
                loop = false;  // 退出循环
                break;
        }
        std::cout << std::endl;
    }

    return 0;  // 返回0
}
