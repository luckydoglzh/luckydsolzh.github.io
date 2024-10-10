#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE sizeof(MemoryBlock)

// 内存块结构
typedef struct MemoryBlock {
    size_t size;               // 当前块的大小
    struct MemoryBlock* next;  // 指向下一个内存块
    int free;                 // 标记该块是否空闲
} MemoryBlock;

MemoryBlock* freeList = NULL; // 空闲块链表的头指针
// 自定义malloc函数
void* my_malloc(size_t size) {
    if (size <= 0) {
        return NULL; // 请求大小无效
    }

    MemoryBlock* current = freeList;
    MemoryBlock* previous = NULL;

    // 遍历空闲块链表寻找合适的块
    while (current != NULL) {
        if (current->free && current->size >= size) {
            // 找到一个合适的空闲块
            current->free = 0; // 标记为已分配
            return (void*)(current + 1); // 返回块数据部分的指针
        }
        previous = current;
        current = current->next;
    }

    // 如果没有合适的块，分配新的内存
    MemoryBlock* newBlock = (MemoryBlock*)malloc(BLOCK_SIZE + size);
    if (newBlock == NULL) {
        return NULL; // 内存分配失败
    }

    newBlock->size = size;
    newBlock->free = 0; // 标记为已分配
    newBlock->next = NULL;

    // 将新的块添加到空闲块链表中
    if (previous != NULL) {
        previous->next = newBlock; // 将新块链接到链表
    } else {
        freeList = newBlock; // 更新空闲链表的头指针
    }

    return (void*)(newBlock + 1); // 返回块数据部分的指针
}
// 自定义malloc函数
void* my_malloc(size_t size) {
    if (size <= 0) {
        return NULL; // 请求大小无效
    }

    MemoryBlock* current = freeList;
    MemoryBlock* previous = NULL;

    // 遍历空闲块链表寻找合适的块
    while (current != NULL) {
        if (current->free && current->size >= size) {
            // 找到一个合适的空闲块
            current->free = 0; // 标记为已分配
            return (void*)(current + 1); // 返回块数据部分的指针
        }
        previous = current;
        current = current->next;
    }

    // 如果没有合适的块，分配新的内存
    MemoryBlock* newBlock = (MemoryBlock*)malloc(BLOCK_SIZE + size);
    if (newBlock == NULL) {
        return NULL; // 内存分配失败
    }

    newBlock->size = size;
    newBlock->free = 0; // 标记为已分配
    newBlock->next = NULL;

    // 将新的块添加到空闲块链表中
    if (previous != NULL) {
        previous->next = newBlock; // 将新块链接到链表
    } else {
        freeList = newBlock; // 更新空闲链表的头指针
    }

    return (void*)(newBlock + 1); // 返回块数据部分的指针
}
int main() {
    // 测试自定义内存管理器
    int* arr1 = (int*)my_malloc(10 * sizeof(int));
    if (arr1 != NULL) {
        for (int i = 0; i < 10; i++) {
            arr1[i] = i + 1;
            printf("%d ", arr1[i]);
        }
        printf("\n");
    }

    my_free(arr1);

    // 重新分配内存
    int* arr2 = (int*)my_malloc(20 * sizeof(int));
    if (arr2 != NULL) {
        for (int i = 0; i < 20; i++) {
            arr2[i] = (i + 1) * 2;
            printf("%d ", arr2[i]);
        }
        printf("\n");
    }

    my_free(arr2);

    return 0;
}
