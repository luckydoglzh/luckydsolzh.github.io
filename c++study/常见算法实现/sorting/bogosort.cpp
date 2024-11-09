/**
 * @file
 * @brief [Bogosort 算法的实现](https://en.wikipedia.org/wiki/Bogosort)
 *
 * @details
 *      在计算机科学中，bogosort（也称为排列排序、傻排序、慢排序、散弹排序、随机排序、猴子排序、bobosort 或洗牌排序）是一种极其低效的排序算法，基于生成与测试的范式。该算法有两种版本：一个是确定性版本，它会枚举所有排列，直到找到一个已排序的排列；另一个是随机版本，它随机排列输入。这里实现的是随机版本。
 *
 * ### 算法
 * 一直随机打乱数组，直到数组被排序。
 *
 * @author [Deep Raval](https://github.com/imdeep2905)
 */
#include <iostream>
#include <algorithm>
#include <array>
#include <cassert>
#include <random>


/**
 * @namespace sorting
 * @brief 排序算法
 */
namespace sorting {

/**
 * 用于洗牌数组中元素的函数。（供参考）
 * @tparam T 数组的类型
 * @tparam N 数组的长度
 * @param arr 要洗牌的数组
 * @returns 洗牌后的新数组
 */
template <typename T, size_t N>
std::array <T, N> shuffle (std::array <T, N> arr) {
    for (int i = 0; i < N; i++) {
        // 将第 i 个索引的元素与一个随机索引（小于数组大小）交换
        std::swap(arr[i], arr[std::rand() % N]);
    }
    return arr;
}

/**
 * 实现随机化的 Bogosort 算法并对给定数组中的元素进行排序。
 * @tparam T 数组的类型
 * @tparam N 数组的长度
 * @param arr 要排序的数组
 * @returns 排序后的新数组
 */
template <typename T, size_t N>
std::array <T, N> randomized_bogosort (std::array <T, N> arr) {
    // 直到数组排序完成
    std::random_device random_device; // 获取随机设备
    std::mt19937 generator(random_device()); // 生成随机数生成器
    while (!std::is_sorted(arr.begin(), arr.end())) {
        std::shuffle(arr.begin(), arr.end(), generator); // 使用随机生成器对数组进行洗牌
    }
    return arr;
}

}  // namespace sorting

/**
 * 显示数组的函数
 * @tparam T 数组的类型
 * @tparam N 数组的长度
 * @param arr 要显示的数组
 */
template <typename T, size_t N>
void show_array (const std::array <T, N> &arr) {
    for (int x : arr) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

/**
 * 测试上述算法的函数
 */
void test() {
    // 测试 1
    std::array <int, 5> arr1;
    for (int &x : arr1) {
        x = std::rand() % 100; // 随机生成数组元素
    }
    std::cout << "原始数组 : ";
    show_array(arr1);
    arr1 = sorting::randomized_bogosort(arr1); // 对数组进行 Bogosort 排序
    std::cout << "排序后的数组 : ";
    show_array(arr1);
    assert(std::is_sorted(arr1.begin(), arr1.end())); // 确保数组已排序
    // 测试 2
    std::array <int, 5> arr2;
    for (int &x : arr2) {
        x = std::rand() % 100; // 随机生成数组元素
    }
    std::cout << "原始数组 : ";
    show_array(arr2);
    arr2 = sorting::randomized_bogosort(arr2); // 对数组进行 Bogosort 排序
    std::cout << "排序后的数组 : ";
    show_array(arr2);
    assert(std::is_sorted(arr2.begin(), arr2.end())); // 确保数组已排序
}

/** 主程序 */
int main() {
    // 测试
    test();
    // 示例用法
    std::array <int, 5> arr = {3, 7, 10, 4, 1}; // 定义一个要排序的数组
    std::cout << "原始数组 : ";
    show_array(arr);
    arr = sorting::randomized_bogosort(arr); // 调用 bogo 排序
    std::cout << "排序后的数组 : ";
    show_array(arr); // 打印排序后的数组
    return 0;
}
