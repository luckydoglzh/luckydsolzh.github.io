/**
 * @file
 * @author [Deep Raval](https://github.com/imdeep2905)
 *
 * @brief 多层感知器（Multilayer Perceptron）的实现
 * (https://en.wikipedia.org/wiki/Multilayer_perceptron)。
 *
 * @details
 * 多层感知器（MLP）是一类前馈人工神经网络（ANN）。MLP这个术语有时模糊地用于指代任何前馈ANN，有时严格地指代由多层感知器（具有阈值激活）构成的网络。多层感知器有时被通俗地称为“香草”神经网络，尤其是当它们只有一个隐藏层时。
 *
 * MLP至少由三层节点组成：输入层、隐藏层和输出层。除了输入节点外，每个节点都是一个使用非线性激活函数的神经元。MLP利用一种称为反向传播的监督学习技术进行训练。其多层结构和非线性激活函数将MLP与线性感知器区分开来。它能够区分非线性可分的数据。
 *
 * 参见 [反向传播](https://en.wikipedia.org/wiki/Backpropagation) 了解训练算法。
 *
 * \note 此实现使用小批量梯度下降作为优化器，并使用均方误差（MSE）作为损失函数。偏置也没有包含在内。
 */

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <valarray>
#include <vector>

#include "vector_ops.hpp"  // 自定义的向量操作头文件

/** \namespace machine_learning
 * \brief 机器学习算法
 */
namespace machine_learning {
/** \namespace neural_network
 * \brief 神经网络或多层感知器
 */
namespace neural_network {
/** \namespace activations
 * \brief 神经网络中使用的各种激活函数
 */
namespace activations {
/**
 * Sigmoid 函数
 * @param X 值
 * @return 返回 sigmoid(x)
 */
double sigmoid(const double &x) { return 1.0 / (1.0 + std::exp(-x)); }

/**
 * Sigmoid 函数的导数
 * @param X 值
 * @return 返回 sigmoid(x) 的导数
 */
double dsigmoid(const double &x) { return x * (1 - x); }

/**
 * ReLU 函数
 * @param X 值
 * @returns relu(x)
 */
double relu(const double &x) { return std::max(0.0, x); }

/**
 * ReLU 函数的导数
 * @param X 值
 * @returns 返回 relu(x) 的导数
 */
double drelu(const double &x) { return x >= 0.0 ? 1.0 : 0.0; }

/**
 * Tanh 函数
 * @param X 值
 * @return 返回 tanh(x)
 */
double tanh(const double &x) { return 2 / (1 + std::exp(-2 * x)) - 1; }

/**
 * Tanh 函数的导数
 * @param X 值
 * @return 返回 tanh(x) 的导数
 */
double dtanh(const double &x) { return 1 - x * x; }
}  // namespace activations

/** \namespace util_functions
 * \brief 神经网络中使用的各种实用函数
 */
namespace util_functions {
/**
 * 平方函数
 * @param X 值
 * @return 返回 x * x
 */
double square(const double &x) { return x * x; }

/**
 * 恒等函数
 * @param X 值
 * @return 返回 x
 */
double identity_function(const double &x) { return x; }
}  // namespace util_functions

/** \namespace layers
 * \brief 此命名空间包含 MLP 中使用的层。
 */
class DenseLayer {

public:
    // 存储激活函数及其导数
    double (*activation_function)(const double &);
    double (*dactivation_function)(const double &);
    int neurons;             // 存储神经元数量（用于摘要）
    std::string activation;  // 存储激活名称（用于摘要）
    std::vector<std::valarray<double>> kernel;  // 存储权重（即内核）

    /**
     * neural_network::layers::DenseLayer 类的构造函数
     * @param neurons 神经元数量
     * @param activation 层的激活函数
     * @param kernel_shape 内核形状
     * @param random_kernel 是否随机初始化内核的标志
     */
    DenseLayer(const int &neurons, const std::string &activation,
               const std::pair<size_t, size_t> &kernel_shape,
               const bool &random_kernel) {
        // 选择激活函数（及其导数）
        if (activation == "sigmoid") {
            activation_function = neural_network::activations::sigmoid;
            dactivation_function = neural_network::activations::sigmoid;
        } else if (activation == "relu") {
            activation_function = neural_network::activations::relu;
            dactivation_function = neural_network::activations::drelu;
        } else if (activation == "tanh") {
            activation_function = neural_network::activations::tanh;
            dactivation_function = neural_network::activations::dtanh;
        } else if (activation == "none") {
            // 如果未提供激活，则设置为恒等函数
            activation_function =
                neural_network::util_functions::identity_function;
            dactivation_function =
                neural_network::util_functions::identity_function;
        } else {
            // 如果提供的激活无效
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "无效的参数。期望 {none, sigmoid, relu, "
                         "tanh} 得到 ";
            std::cerr << activation << std::endl;
            std::exit(EXIT_FAILURE);
        }
        this->activation = activation;  // 设置激活名称
        this->neurons = neurons;        // 设置神经元数量
        // 根据标志初始化内核
        if (random_kernel) {
            uniform_random_initialization(kernel, kernel_shape, -1.0, 1.0);
        } else {
            unit_matrix_initialization(kernel, kernel_shape);
        }
    }

    /**
     * neural_network::layers::DenseLayer 类的构造函数
     * @param neurons 神经元数量
     * @param activation 层的激活函数
     * @param kernel 内核的值（用于加载模型）
     */
    DenseLayer(const int &neurons, const std::string &activation,
               const std::vector<std::valarray<double>> &kernel) {
        // 选择激活函数（及其导数）
        if (activation == "sigmoid") {
            activation_function = neural_network::activations::sigmoid;
            dactivation_function = neural_network::activations::sigmoid;
        } else if (activation == "relu") {
            activation_function = neural_network::activations::relu;
            dactivation_function = neural_network::activations::drelu;
        } else if (activation == "tanh") {
            activation_function = neural_network::activations::tanh;
            dactivation_function = neural_network::activations::dtanh;
        } else if (activation == "none") {
            // 如果未提供激活，则设置为恒等函数
            activation_function =
                neural_network::util_functions::identity_function;
            dactivation_function =
                neural_network::util_functions::identity_function;
        } else {
            // 如果提供的激活无效
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "无效的参数。期望 {none, sigmoid, relu, "
                         "tanh} 得到 ";
            std::cerr << activation << std::endl;
            std::exit(EXIT_FAILURE);
        }
        this->activation = activation;  // 设置激活名称
        this->neurons = neurons;        // 设置神经元数量
        this->kernel = kernel;          // 设置提供的内核值
    }

    /**
     * DenseLayer 类的拷贝构造函数。
     *
     * @param model 要拷贝的类的实例。
     */
    DenseLayer(const DenseLayer &layer) = default;

    /**
     * DenseLayer 类的析构函数。
     */
    ~DenseLayer() = default;

    /**
     * DenseLayer 类的拷贝赋值运算符
     */
    DenseLayer &operator=(const DenseLayer &layer) = default;

    /**
     * DenseLayer 类的移动构造函数
     */
    DenseLayer(DenseLayer &&) = default;

    /**
     * DenseLayer 类的移动赋值运算符
     */
    DenseLayer &operator=(DenseLayer &&) = default;
};
}  // namespace layers

/**
 * NeuralNetwork 类实现了多层感知机（MLP）。该类
 * 用于实际用户创建和训练网络。
 *
 */
class NeuralNetwork {
 private:
    std::vector<neural_network::layers::DenseLayer> layers;  // 存储层

    /**
     * NeuralNetwork 类的私有构造函数。此构造函数
     * 用于内部加载模型。
     * @param config 包含对（神经元，激活）对的向量
     * @param kernels 包含所有预训练内核的向量
     */
    NeuralNetwork(
        const std::vector<std::pair<int, std::string>> &config,
        const std::vector<std::vector<std::valarray<double>>> &kernels) {
        // 第一层不能有激活
        if (config.begin()->second != "none") {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr
                << "第一层不能有激活，除了none，得到 "
                << config.begin()->second;
            std::cerr << std::endl;
            std::exit(EXIT_FAILURE);
        }
        // 网络至少应有两层
        if (config.size() <= 1) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "网络大小无效，";
            std::cerr << "至少需要两层";
            std::exit(EXIT_FAILURE);
        }
        // 重构所有预训练层
        for (size_t i = 0; i < config.size(); i++) {
            layers.emplace_back(neural_network::layers::DenseLayer(
                config[i].first, config[i].second, kernels[i]));
        }
        std::cout << "INFO: 网络成功构建" << std::endl;
    }

    /**
     * 私有函数以获取详细预测（即
     * 激活的神经元值）。此函数在
     * 反向传播、单预测和批预测中使用。
     * @param X 输入向量
     */
    std::vector<std::vector<std::valarray<double>>>
    __detailed_single_prediction(const std::vector<std::valarray<double>> &X) {
        std::vector<std::vector<std::valarray<double>>> details;
        std::vector<std::valarray<double>> current_pass = X;
        details.emplace_back(X);
        for (const auto &l : layers) {
            current_pass = multiply(current_pass, l.kernel);
            current_pass = apply_function(current_pass, l.activation_function);
            details.emplace_back(current_pass);
        }
        return details;
    }

 public:
    /**
     * NeuralNetwork 类的默认构造函数。该构造函数
     * 用于创建空的 NeuralNetwork 类型变量。
     */
    NeuralNetwork() = default;

    /**
     * NeuralNetwork 类的构造函数。该构造函数
     * 用户使用。
     * @param config 包含对（神经元，激活）对的向量
     */
    explicit NeuralNetwork(
        const std::vector<std::pair<int, std::string>> &config) {
        // 第一层不能有激活
        if (config.begin()->second != "none") {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr
                << "第一层不能有激活，除了none，得到 "
                << config.begin()->second;
            std::cerr << std::endl;
            std::exit(EXIT_FAILURE);
        }
        // 网络至少应有两层
        if (config.size() <= 1) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "网络大小无效，";
            std::cerr << "至少需要两层";
            std::exit(EXIT_FAILURE);
        }
        // 单独创建第一层，以便它可以有单位矩阵
        // 作为内核。
        layers.push_back(neural_network::layers::DenseLayer(
            config[0].first, config[0].second,
            {config[0].first, config[0].first}, false));
        // 创建其余层
        for (size_t i = 1; i < config.size(); i++) {
            layers.push_back(neural_network::layers::DenseLayer(
                config[i].first, config[i].second,
                {layers[i - 1].neurons, config[i].first}, true));
        }
    }
    /**
 * 从CSV文件中拟合模型的函数
 * @param file_name CSV文件名
 * @param last_label 是否最后一列是标签的标志
 * @param epochs 训练的轮数
 * @param learning_rate 学习率
 * @param normalize 是否对数据进行归一化的标志
 * @param slip_lines 跳过的行数
 * @param batch_size 梯度下降的批量大小（默认 = 32）
 * @param shuffle 是否打乱数据的标志（默认 = true）
 */
void fit_from_csv(const std::string &file_name, const bool &last_label,
                  const int &epochs, const double &learning_rate,
                  const bool &normalize, const int &slip_lines = 1,
                  const size_t &batch_size = 32,
                  const bool &shuffle = true) {
    // 从CSV文件中获取训练数据
    auto data =
        this->get_XY_from_csv(file_name, last_label, normalize, slip_lines);
    // 在训练数据上拟合模型
    this->fit(data.first, data.second, epochs, learning_rate, batch_size,
              shuffle);
    return;
}

/**
 * 在提供的数据上评估模型的函数
 * @param X 特征向量数组（输入数据）
 * @param Y 目标值数组（标签）
 */
void evaluate(const std::vector<std::vector<std::valarray<double>>> &X,
              const std::vector<std::vector<std::valarray<double>>> &Y) {
    std::cout << "INFO: Evaluation Started" << std::endl;
    double acc = 0, loss = 0;  // 初始化性能指标为零
    for (size_t i = 0; i < X.size(); i++) {  // 对于输入中的每个样本
        // 获取预测值
        std::vector<std::valarray<double>> pred =
            this->single_predict(X[i]);
        // 如果预测的类别是正确的
        if (argmax(pred) == argmax(Y[i])) {
            acc += 1;  // 增加准确率
        }
        // 计算损失 - 均方误差
        loss += sum(apply_function((Y[i] - pred),
                                   neural_network::util_functions::square) *
                    0.5);
    }
    acc /= X.size();   // 计算平均准确率
    loss /= X.size();  // 计算平均损失
    // 打印模型的性能
    std::cout << "Evaluation: Loss: " << loss;
    std::cout << ", Accuracy: " << acc << std::endl;
    return;
}

/**
 * 在CSV文件中评估模型的函数
 * @param file_name CSV文件名
 * @param last_label 是否最后一列是标签的标志
 * @param normalize 是否对数据进行归一化的标志
 * @param slip_lines 跳过的行数
 */
void evaluate_from_csv(const std::string &file_name, const bool &last_label,
                       const bool &normalize, const int &slip_lines = 1) {
    // 从CSV文件中获取训练数据
    auto data =
        this->get_XY_from_csv(file_name, last_label, normalize, slip_lines);
    // 评估模型
    this->evaluate(data.first, data.second);
    return;
}

/**
 * 保存当前模型的函数。
 * @param file_name 保存模型的文件名 (*.model)
 */
void save_model(const std::string &_file_name) {
    std::string file_name = _file_name;
    // 如果文件名中没有“.model”扩展名，则添加
    if (file_name.find(".model") == file_name.npos) {
        file_name += ".model";
    }
    std::ofstream out_file;  // 用于写入文件的ofstream
    // 以out|trunc模式打开文件
    out_file.open(file_name.c_str(),
                  std::ofstream::out | std::ofstream::trunc);
    // 如果打开文件时有任何问题
    if (!out_file.is_open()) {
        std::cerr << "ERROR (" << __func__ << ") : ";
        std::cerr << "无法打开文件: " << file_name << std::endl;
        std::exit(EXIT_FAILURE);
    }
    /**
        模型保存的格式：

        total_layers
        neurons(第1层的neural_network::layers::DenseLayer) activation_name(第1层的neural_network::layers::DenseLayer) kernel_shape(第1层的neural_network::layers::DenseLayer) kernel_values
        .
        .
        .
        neurons(第N层的neural_network::layers::DenseLayer) activation_name(第N层的neural_network::layers::DenseLayer) kernel_shape(第N层的neural_network::layers::DenseLayer) kernel_value

        例如，具有3层的预训练模型：
        <pre>
        3
        4 none
        4 4
        1 0 0 0
        0 1 0 0
        0 0 1 0
        0 0 0 1
        6 relu
        4 6
        -1.88963 -3.61165 1.30757 -0.443906 -2.41039 -2.69653
        -0.684753 0.0891452 0.795294 -2.39619 2.73377 0.318202
        -2.91451 -4.43249 -0.804187 2.51995 -6.97524 -1.07049
        -0.571531 -1.81689 -1.24485 1.92264 -2.81322 1.01741
        3 sigmoid
        6 3
        0.390267 -0.391703 -0.0989607
        0.499234 -0.564539 -0.28097
        0.553386 -0.153974 -1.92493
        -2.01336 -0.0219682 1.44145
        1.72853 -0.465264 -0.705373
        -0.908409 -0.740547 0.376416
        </pre>
    */
    // 以相同的格式保存模型
    out_file << layers.size();
    out_file << std::endl;
    for (const auto &layer : this->layers) {
        out_file << layer.neurons << ' ' << layer.activation << std::endl;
        const auto shape = get_shape(layer.kernel);
        out_file << shape.first << ' ' << shape.second << std::endl;
        for (const auto &row : layer.kernel) {
            for (const auto &val : row) {
                out_file << val << ' ';
            }
            out_file << std::endl;
        }
    }
    std::cout << "INFO: 模型成功保存，名称: ";
    std::cout << file_name << std::endl;
    out_file.close();  // 关闭文件
    return;
}

/**
 * 从早先保存的模型中加载的函数。
 * @param file_name 从中加载模型的文件 (*.model)
 * @return 具有预训练权重的NeuralNetwork类实例
 */
NeuralNetwork load_model(const std::string &file_name) {
    std::ifstream in_file;            // 用于读取文件的ifstream
    in_file.open(file_name.c_str());  // 打开文件
    // 如果打开文件时有任何问题
    if (!in_file.is_open()) {
        std::cerr << "ERROR (" << __func__ << ") : ";
        std::cerr << "无法打开文件: " << file_name << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::vector<std::pair<int, std::string>> config;  // 用于存储配置
    std::vector<std::vector<std::valarray<double>>>
        kernels;  // 用于存储预训练的内核
    // 从保存的文件格式中加载模型
    size_t total_layers = 0;
    in_file >> total_layers;
    for (size_t i = 0; i < total_layers; i++) {
        int neurons = 0;
        std::string activation;
        size_t shape_a = 0, shape_b = 0;
        std::vector<std::valarray<double>> kernel;
        in_file >> neurons >> activation >> shape_a >> shape_b;
        for (size_t r = 0; r < shape_a; r++) {
            std::valarray<double> row(shape_b);
            for (size_t c = 0; c < shape_b; c++) {
                in_file >> row[c];
            }
            kernel.push_back(row);
        }
        config.emplace_back(make_pair(neurons, activation));
        kernels.emplace_back(kernel);
    }
    std::cout << "INFO: 模型成功加载" << std::endl;
    in_file.close();  // 关闭文件
    return NeuralNetwork(
        config, kernels);  // 返回NeuralNetwork类的实例
}

/**
 * 打印网络摘要的函数。
 */
void summary() {
    // 打印摘要
    std::cout
        << "==============================================================="
        << std::endl;
    std::cout << "\t\t+ 模型摘要 +\t\t\n";
    std::cout
        << "==============================================================="
        << std::endl;
    for (size_t i = 1; i <= layers.size(); i++) {  // 对于每一层
        std::cout << i << ")";
        std::cout << " 神经元数 : "
                  << layers[i - 1].neurons;  // 神经元数量
        std::cout << ", 激活函数 : "
                  << layers[i - 1].activation;  // 激活函数
        std::cout << ", 内核形状 : "
                  << get_shape(layers[i - 1].kernel);  // 内核形状
        std::cout << std::endl;
    }
    std::cout
        << "==============================================================="
        << std::endl;
    return;
}
/**
 * 测试神经网络的函数
 * @returns 无返回值
 */
static void test() {
    // 创建一个有3层的神经网络，用于处理"iris.csv"数据集
    machine_learning::neural_network::NeuralNetwork myNN =
        machine_learning::neural_network::NeuralNetwork({
            {4, "none"},  // 第一层有4个神经元，激活函数为"none"
            {6, "relu"},  // 第二层有6个神经元，激活函数为"relu"
            {3, "sigmoid"}  // 第三层有3个神经元，激活函数为"sigmoid"
        });
    
    // 打印模型的摘要
    myNN.summary();
    
    // 训练模型，使用"iris.csv"数据集，最后一列是标签，训练100轮，学习率为0.3，不进行归一化，跳过2行，批量大小为32，数据打乱
    myNN.fit_from_csv("iris.csv", true, 100, 0.3, false, 2, 32, true);
    
    // 测试模型的预测
    assert(machine_learning::argmax(
               myNN.single_predict({{5, 3.4, 1.6, 0.4}})) == 0);  // 测试样本，期望类别为0
    assert(machine_learning::argmax(
               myNN.single_predict({{6.4, 2.9, 4.3, 1.3}})) == 1);  // 测试样本，期望类别为1
    assert(machine_learning::argmax(
               myNN.single_predict({{6.2, 3.4, 5.4, 2.3}})) == 2);  // 测试样本，期望类别为2
    return;
}

/**
 * @brief 主函数
 * @returns 退出时返回0
 */
int main() {
    // 调用测试函数
    test();
    return 0;  // 返回0，表示程序正常退出
}


}