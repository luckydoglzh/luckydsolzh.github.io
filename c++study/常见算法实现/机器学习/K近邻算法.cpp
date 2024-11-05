/**
 * @file
 * @brief [K近邻算法](https://en.wikipedia.org/wiki/K-nearest_neighbors_algorithm) 的实现
 * @author [Luiz Carlos Cosmi Filho](https://github.com/luizcarloscf)
 * @details K近邻算法（K-Nearest Neighbors, 简称 KNN）是一种监督学习分类器，利用样本之间的接近度进行分类。
 * 该实现使用欧几里得距离作为距离度量来寻找 K 个最近邻。
 */

#include <algorithm>      /// 用于 std::transform 和 std::sort
#include <cassert>        /// 用于 assert
#include <cmath>          /// 用于 std::pow 和 std::sqrt
#include <iostream>       /// 用于 std::cout
#include <numeric>        /// 用于 std::accumulate
#include <unordered_map>  /// 用于 std::unordered_map
#include <vector>         /// 用于 std::vector

/**
 * @namespace machine_learning
 * @brief 机器学习算法
 */
namespace machine_learning {

/**
 * @namespace k_nearest_neighbors
 * @brief [K近邻算法](https://en.wikipedia.org/wiki/K-nearest_neighbors_algorithm) 的实现函数
 */
namespace k_nearest_neighbors {

/**
 * @brief 计算两个向量之间的欧几里得距离
 *
 * @tparam T 向量的类型
 * @param a 第一个一维向量
 * @param b 第二个一维向量
 * @return double 表示两个向量间的欧几里得距离的标量值
 */
template <typename T>
double euclidean_distance(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<double> aux;
    std::transform(a.begin(), a.end(), b.begin(), std::back_inserter(aux),
                   [](T x1, T x2) { return std::pow((x1 - x2), 2); });
    aux.shrink_to_fit();
    return std::sqrt(std::accumulate(aux.begin(), aux.end(), 0.0));
}

/**
 * @brief K近邻（Knn）类，使用欧几里得距离作为距离度量
 */
class Knn {
 private:
    std::vector<std::vector<double>> X_{};  ///< 属性向量
    std::vector<int> Y_{};                  ///< 标签向量

 public:
    /**
     * @brief 构造一个新的 Knn 对象
     * @details 使用懒学习方法，仅在内存中保留数据集
     * @param X 属性向量
     * @param Y 标签向量
     */
    explicit Knn(std::vector<std::vector<double>>& X, std::vector<int>& Y)
        : X_(X), Y_(Y){};

    /**
     * 拷贝构造函数
     *
     * @param model 要拷贝的类实例
     */
    Knn(const Knn& model) = default;

    /**
     * 拷贝赋值运算符
     */
    Knn& operator=(const Knn& model) = default;

    /**
     * 移动构造函数
     */
    Knn(Knn&&) = default;

    /**
     * 移动赋值运算符
     */
    Knn& operator=(Knn&&) = default;

    /**
     * @brief 销毁 Knn 对象
     */
    ~Knn() = default;

    /**
     * @brief 对样本进行分类
     * @param sample 样本
     * @param k 邻居的数量
     * @return int 返回邻居中最频繁的标签
     */
    int predict(std::vector<double>& sample, int k) {
        std::vector<int> neighbors;
        std::vector<std::pair<double, int>> distances;
        for (size_t i = 0; i < this->X_.size(); ++i) {
            auto current = this->X_.at(i);
            auto label = this->Y_.at(i);
            auto distance = euclidean_distance(current, sample);
            distances.emplace_back(distance, label);
        }
        std::sort(distances.begin(), distances.end());
        for (int i = 0; i < k; i++) {
            auto label = distances.at(i).second;
            neighbors.push_back(label);
        }
        std::unordered_map<int, int> frequency;
        for (auto neighbor : neighbors) {
            ++frequency[neighbor];
        }
        std::pair<int, int> predicted;
        predicted.first = -1;
        predicted.second = -1;
        for (auto& kv : frequency) {
            if (kv.second > predicted.second) {
                predicted.second = kv.second;
                predicted.first = kv.first;
            }
        }
        return predicted.first;
    }
};
}  // namespace k_nearest_neighbors
}  // namespace machine_learning

/**
 * @brief 自测函数
 * @returns void
 */
static void test() {
    std::cout << "------- 测试 1 -------" << std::endl;
    std::vector<std::vector<double>> X1 = {{0.0, 0.0}, {0.25, 0.25},
                                           {0.0, 0.5}, {0.5, 0.5},
                                           {1.0, 0.5}, {1.0, 1.0}};
    std::vector<int> Y1 = {1, 1, 1, 1, 2, 2};
    auto model1 = machine_learning::k_nearest_neighbors::Knn(X1, Y1);
    std::vector<double> sample1 = {1.2, 1.2};
    std::vector<double> sample2 = {0.1, 0.1};
    std::vector<double> sample3 = {0.1, 0.5};
    std::vector<double> sample4 = {1.0, 0.75};
    assert(model1.predict(sample1, 2) == 2);
    assert(model1.predict(sample2, 2) == 1);
    assert(model1.predict(sample3, 2) == 1);
    assert(model1.predict(sample4, 2) == 2);
    std::cout << "... 测试通过" << std::endl;
    std::cout << "------- 测试 2 -------" << std::endl;
    std::vector<std::vector<double>> X2 = {
        {0.0, 0.0, 0.0}, {0.25, 0.25, 0.0}, {0.0, 0.5, 0.0}, {0.5, 0.5, 0.0},
        {1.0, 0.5, 0.0}, {1.0, 1.0, 0.0},   {1.0, 1.0, 1.0}, {1.5, 1.5, 1.0}};
    std::vector<int> Y2 = {1, 1, 1, 1, 2, 2, 3, 3};
    auto model2 = machine_learning::k_nearest_neighbors::Knn(X2, Y2);
    std::vector<double> sample5 = {1.2, 1.2, 0.0};
    std::vector<double> sample6 = {0.1, 0.1, 0.0};
    std::vector<double> sample7 = {0.1, 0.5, 0.0};
    std::vector<double> sample8 = {1.0, 0.75, 1.0};
    assert(model2.predict(sample5, 2) == 2);
    assert(model2.predict(sample6, 2) == 1);
    assert(model2.predict(sample7, 2) == 1);
    assert(model2.predict(sample8, 2) == 3);
    std::cout << "... 测试通过" << std::endl;
    std::cout << "------- 测试 3 -------" << std::endl;
    std::vector<std::vector<double>> X3 = {{0.0}, {1.0}, {2.0}, {3.0},
                                           {4.0}, {5.0}, {6.0}, {7.0}};
    std::vector<int> Y3 = {1, 1, 1, 1, 2, 2, 2, 2};
    auto model3 = machine_learning::k_nearest_neighbors::Knn(X3, Y3);
    std::vector<double> sample9 = {0.5};
    std::vector<double> sample10 = {2.9};
    std::vector<double> sample11 = {5.5};
    std::vector<double> sample12 = {7.5};
    assert(model3.predict(sample9, 3) == 1);
    assert(model3.predict(sample10, 3) == 1);
    assert(model3.predict(sample11, 3) == 2);
    assert(model3.predict(sample12, 3) == 2);
    std::cout << "... 测试通过" << std::endl;
}

/**
 * @brief 主函数
 * @param argc 命令行参数数量（忽略）
 * @param argv 命令行参数数组（忽略）
 * @return int 退出时返回 0
 */
int main(int argc, char* argv[]) {
    test();  // 运行自测
    return 0;
}
