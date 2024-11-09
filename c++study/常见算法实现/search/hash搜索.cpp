/**
 * \file
 * \brief 哈希搜索算法 - 最佳时间复杂度 Ω(1)
 *
 * \copyright 2020 Arctic2333
 *
 * 本算法使用除法和保留余数的方法构建哈希函数，并使用链地址法来解决冲突，即在数据后面链接一个链表，
 * 将所有关键字相同的记录存储在同一个线性链表中。
 *
 * @warning 本程序仅用于教学目的。由于在内存管理方面实现有严重缺陷，可能导致大量内存泄漏。
 * @todo 修复内存泄漏并改进程序结构，使用 C++ 风格而非 C 风格。
 */
#include <cstdlib>
#include <iostream>

#define MAX 6      ///< 数据量的大小
#define HASHMAX 5  ///< 哈希表的长度

int data[MAX] = {1, 10, 15, 5, 8, 7};  //!< 测试数据

/**
 * 单向链表
 */
typedef struct list {
    int key;            //!< 节点的键值
    struct list* next;  //!< 指向链表中下一个节点的指针
} node,                 /**< 定义 node 作为链表的一项 */
    *link;              ///< 链表节点的指针

node hashtab[HASHMAX];  ///< 哈希表的节点数组

// int counter = 1;

/**
 * 哈希检测方式：
 * 除法法
 * \param [in] key 需要哈希的键
 * \returns 返回该键的哈希值
 */
int h(int key) { return key % HASHMAX; }

/**
 * 对相同余数的元素进行链式插入，避免冲突，使用 zipper 方法
 * 将元素插入到链表的头部
 * \param [in] key 需要插入链表的键
 * \warning `n` 动态分配的内存从未释放，存在内存泄漏问题。
 * \todo 修复内存泄漏
 */
void create_list(int key) {  // 构建哈希表
    link p, n;
    int index;
    n = (link)malloc(sizeof(node));  // 分配新的节点
    n->key = key;  // 设置节点的键值
    n->next = NULL;  // 设置下一节点为 NULL
    index = h(key);  // 计算键的哈希值
    p = hashtab[index].next;  // 获取当前位置链表的头指针
    if (p != NULL) {
        n->next = p;  // 将新节点插入到链表的头部
        hashtab[index].next = n;
    } else {
        hashtab[index].next = n;  // 如果链表为空，直接将新节点作为链表的头节点
    }
}

/**
 * 输入需要查找的键，首先通过哈希函数 H(int key) 获取哈希头部位置，
 * 然后进行线性查找。如果找到则返回元素的深度和查找次数；如果未找到，则返回 -1。
 */
int hash_search(int key, int* counter) {  // 哈希查找函数
    link pointer;
    int index;

    *counter = 0;  // 初始化查找次数为 0
    index = h(key);  // 获取哈希值
    pointer = hashtab[index].next;  // 获取链表头部

    std::cout << "data[" << index << "]:";

    // 进行线性查找
    while (pointer != NULL) {
        counter[0]++;  // 每找到一个元素，查找次数加 1
        std::cout << "data[" << pointer->key << "]:";  // 输出当前节点的键值
        if (pointer->key == key)  // 如果找到目标元素，返回 1
            return 1;
        else
            pointer = pointer->next;  // 否则继续查找下一个节点
    }

    return 0;  // 没有找到元素，返回 0
}

/** 主函数 */
int main() {
    link p;
    int key, index, i, counter;  // key 是要查找的键
    index = 0;

    // 构建哈希表
    while (index < MAX) {
        create_list(data[index]);  // 插入数据到哈希表
        index++;
    }

    // 输出哈希表的内容
    for (i = 0; i < HASHMAX; i++) {
        std::cout << "hashtab [" << i << "]\n";  // 输出当前哈希表的索引

        p = hashtab[i].next;  // 获取当前索引下链表的头部

        while (p != NULL) {  // 遍历链表
            std::cout << "please int key:";
            if (p->key > 0)  // 如果节点的键值大于 0，则输出该键值
                std::cout << "[" << p->key << "]";
            p = p->next;  // 继续查找下一个节点
        }
        std::cout << std::endl;
    }

    // 查找测试
    while (key != -1) {
        // 测试键值为 10
        key = 10;
        if (hash_search(key, &counter))  // 执行哈希查找
            std::cout << "search time = " << counter << std::endl;  // 输出查找次数
        else
            std::cout << "no found!\n";  // 如果未找到
        key = -1;  // 退出测试
        /* 测试结果为：
         * data[0]:data[5]:data[15]:data[10]:search time = 3 查找成功，数据中存在 10
         */
    }

    return 0;
}
