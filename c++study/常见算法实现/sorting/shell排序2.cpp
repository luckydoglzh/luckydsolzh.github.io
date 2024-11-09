/**
 * \file
 * \brief [Shell sort](https://en.wikipedia.org/wiki/Shell_sort) 算法实现
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <utility>  // for std::swap
#include <vector>

/** 
 * 打印数组
 * \param[in] arr 需要打印的数组
 * \param[in] LEN 数组的长度
 */
template <class T>
void show_data(T *arr, size_t LEN) {
    size_t i;

    for (i = 0; i < LEN; i++) {
        std::cout << arr[i] << ", ";  // 输出数组元素
    }
    std::cout << std::endl;
}

/** 
 * 打印数组
 * \param[in] arr 需要打印的数组
 * \param[in] N 数组的长度
 */
template <typename T, size_t N>
void show_data(T (&arr)[N]) {
    show_data(arr, N);
}

/** 
 * \namespace sorting
 * \brief 排序算法
 */
namespace sorting {
/**
 * 优化版的Shell排序算法，利用Mar方法减少排序时间
 **/
template <typename T>
void shell_sort(T *arr, size_t LEN) {
    const unsigned int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};  // 间隔序列
    const unsigned int gap_len = 8;  // 间隔序列的长度
    size_t i, j, g;

    // 遍历间隔序列
    for (g = 0; g < gap_len; g++) {
        unsigned int gap = gaps[g];
        // 按间隔大小遍历数组
        for (i = gap; i < LEN; i++) {
            T tmp = arr[i];  // 临时保存当前元素

            // 使用插入排序的方式，将元素插入到正确位置
            for (j = i; j >= gap && (arr[j - gap] - tmp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }

            arr[j] = tmp;  // 将元素插入正确的位置
        }
    }
}

/** 函数重载 - 针对已知长度的数组类型 */
template <typename T, size_t N>
void shell_sort(T (&arr)[N]) {
    shell_sort(arr, N);
}

/** 函数重载 - 当输入数组是std::vector时，直接将数据和长度传递给上面的函数 */
template <typename T>
void shell_sort(std::vector<T> *arr) {
    shell_sort(arr->data(), arr->size());
}

}  // namespace sorting

using sorting::shell_sort;

/**
 * 用于比较自定义排序和stdlib的qsort的排序结果
 **/
template <typename T>
int compare(const void *a, const void *b) {
    T arg1 = *static_cast<const T *>(a);
    T arg2 = *static_cast<const T *>(b);

    if (arg1 < arg2)
        return -1;  // 如果arg1小于arg2，返回负值
    if (arg1 > arg2)
        return 1;   // 如果arg1大于arg2，返回正值
    return 0;  // 如果arg1等于arg2，返回0

    // 可以使用更简洁的方式：return (arg1 > arg2) - (arg1 < arg2);
}

/**
 * 使用Shell排序对整数数组进行测试，并与std::qsort进行比较
 **/
void test_int(const int NUM_DATA) {
    // 创建两个整数数组
    int *data = new int[NUM_DATA];
    int *data2 = new int[NUM_DATA];
    int range = 1800;  // 随机数范围

    // 初始化数组，生成随机数
    for (int i = 0; i < NUM_DATA; i++)
        data[i] = data2[i] = (std::rand() % range) - (range >> 1);

    // 使用自定义Shell排序算法进行排序
    std::clock_t start = std::clock();
    shell_sort(data, NUM_DATA);
    std::clock_t end = std::clock();
    double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "使用Shell排序耗时: " << elapsed_time << "秒\n";

    // 使用std::qsort进行排序
    start = std::clock();
    std::qsort(data2, NUM_DATA, sizeof(data2[0]), compare<int>);
    end = std::clock();

    elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "使用std::qsort耗时: " << elapsed_time << "秒\n";

    // 比较两个排序结果是否一致
    for (int i = 0; i < NUM_DATA; i++) {
        assert(data[i] == data2[i]);  // 确保自定义排序和qsort的结果一致
    }

    // 释放动态分配的内存
    delete[] data;
    delete[] data2;
}

/**
 * 使用Shell排序对浮点数数组进行测试，并与std::qsort进行比较
 **/
void test_f(const int NUM_DATA) {
    // 创建两个浮点数数组
    float *data = new float[NUM_DATA];
    float *data2 = new float[NUM_DATA];
    int range = 1000;  // 随机数范围

    // 初始化数组，生成随机数
    for (int i = 0; i < NUM_DATA; i++) {
        data[i] = data2[i] = ((std::rand() % range) - (range >> 1)) / 100.0f;
    }

    // 使用自定义Shell排序算法进行排序
    std::clock_t start = std::clock();
    shell_sort(data, NUM_DATA);
    std::clock_t end = std::clock();
    double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "使用Shell排序耗时: " << elapsed_time << "秒\n";

    // 使用std::qsort进行排序
    start = std::clock();
    std::qsort(data2, NUM_DATA, sizeof(data2[0]), compare<float>);
    end = std::clock();

    elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "使用std::qsort耗时: " << elapsed_time << "秒\n";

    // 比较两个排序结果是否一致
    for (int i = 0; i < NUM_DATA; i++) {
        assert(data[i] == data2[i]);  // 确保自定义排序和qsort的结果一致
    }

    // 释放动态分配的内存
    delete[] data;
    delete[] data2;
}

/** 主函数 */
int main(int argc, char *argv[]) {
    // 初始化随机数生成器
    std::srand(std::time(NULL));

    // 对100、1000、10000个整数进行测试
    test_int(100);
    std::cout << "Test 1 - 100个整数 - 通过。\n";
    test_int(1000);
    std::cout << "Test 2 - 1000个整数 - 通过。\n";
    test_int(10000);
    std::cout << "Test 3 - 10000个整数 - 通过。\n";

    // 对100、1000、10000个浮点数进行测试
    test_f(100);
    std::cout << "Test 1 - 100个浮点数 - 通过。\n";
    test_f(1000);
    std::cout << "Test 2 - 1000个浮点数 - 通过。\n";
    test_f(10000);
    std::cout << "Test 3 - 10000个浮点数 - 通过。\n";

    int i, NUM_DATA;

    if (argc == 2)
        NUM_DATA = atoi(argv[1]);  // 从命令行参数获取数据量
    else
        NUM_DATA = 200;  // 默认数据量为200

    // 创建整数数组
    int *data = new int[NUM_DATA];
    int range = 1800;  // 随机数范围

    // 初始化数组，生成随机数
    std::srand(time(NULL));
    for (i = 0; i < NUM_DATA; i++) {
        data[i] = (std::rand() % range) - (range >> 1);
    }

    std::cout << "原始数据（未排序）: " << std::endl;
    show_data(data, NUM_DATA);  // 打印未排序的数组
    std::clock_t start = std::clock();
    shell_sort(data, NUM_DATA);  // 使用Shell排序进行排序
    std::clock_t end = std::clock();

    std::cout << std::endl
              << "使用自定义实现排序后的数据: " << std::endl;
    show_data(data, NUM_DATA);  // 打印排序后的数组

    // 输出排序所需时间
    double elapsed_time = (end - start) * 1.f / CLOCKS_PER_SEC;
    std::cout << "排序耗时: " << elapsed_time << "秒\n" << std::endl;

    // 释放动态分配的内存
    delete[] data;
    return 0;
}
