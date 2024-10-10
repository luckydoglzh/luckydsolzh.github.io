#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//chatgpt生成的的，key和value值可以随便玩，本质就是通过映射f(x)来将key和value一一对应放到hash表内
//hash值是具有唯一性的哦~
#define TABLE_SIZE 100 // 哈希表的大小

// 键值对的节点结构
typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

// 哈希表结构
typedef struct HashTable {
    Node** buckets; // 存储每个链表的头指针
} HashTable;

// 简单的哈希函数：将字符串键映射为哈希表中的索引
unsigned int hash(const char* key) {
    unsigned int hashValue = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashValue += key[i];  // 根据键的ASCII值生成哈希
        hashValue = (hashValue * key[i]) % TABLE_SIZE; // 防止溢出
    }
    return hashValue % TABLE_SIZE; // 将结果映射到哈希表的大小范围内
}

// 初始化哈希表
HashTable* createHashTable() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->buckets = (Node**)malloc(TABLE_SIZE * sizeof(Node*));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}
// 创建一个新的节点
Node* createNode(const char* key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key); // 复制键
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// 插入键值对
void insert(HashTable* table, const char* key, int value) {
    unsigned int index = hash(key); // 计算哈希值，找到索引
    Node* newNode = createNode(key, value);

    // 插入到链表头部（链地址法）
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}
// 查找键对应的值
int search(HashTable* table, const char* key) {
    unsigned int index = hash(key); // 计算哈希值，找到索引
    Node* current = table->buckets[index];

    // 遍历链表，查找键
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value; // 找到对应的值
        }
        current = current->next;
    }

    return -1; // 没有找到键，返回 -1 表示未找到
}
// 删除键值对
void delete(HashTable* table, const char* key) {
    unsigned int index = hash(key); // 计算哈希值，找到索引
    Node* current = table->buckets[index];
    Node* prev = NULL;

    // 遍历链表，查找键
    while (current != NULL && strcmp(current->key, key) != 0) {
        prev = current;
        current = current->next;
    }

    // 如果找到了要删除的节点
    if (current != NULL) {
        if (prev == NULL) {
            // 如果要删除的是第一个节点
            table->buckets[index] = current->next;
        } else {
            prev->next = current->next;
        }
        free(current->key);
        free(current);
    }
}
// 销毁哈希表，释放内存
void freeHashTable(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = table->buckets[i];
        while (current != NULL) {
            Node* next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(table->buckets);
    free(table);
}
int main() {
    HashTable* table = createHashTable();

    insert(table, "apple", 100);
    insert(table, "banana", 200);
    insert(table, "orange", 300);

    printf("Value for key 'apple': %d\n", search(table, "apple"));
    printf("Value for key 'banana': %d\n", search(table, "banana"));
    printf("Value for key 'grape': %d\n", search(table, "grape"));

    delete(table, "banana");

    printf("Value for key 'banana' after deletion: %d\n", search(table, "banana"));

    freeHashTable(table);
    return 0;
}
