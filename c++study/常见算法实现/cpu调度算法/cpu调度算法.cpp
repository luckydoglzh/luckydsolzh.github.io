/**
 * @file
 * @brief FCFS CPU调度算法的实现
 * @details
 * FCFS是一种非抢占式的CPU调度算法，按照到达顺序执行进程。如果两个或多个进程同时到达，则优先执行进程ID较小的进程。
 * @link https://bit.ly/3ABNXOC
 * @author [Pratyush Vatsa](https://github.com/Pratyush219)
 */

#include <algorithm>      /// 用于排序
#include <cassert>        /// 用于断言
#include <cstdlib>        /// 随机数生成
#include <ctime>          /// 用于时间
#include <iomanip>        /// 用于格式化输出
#include <iostream>       /// 用于输入输出操作
#include <queue>          /// 用于优先队列
#include <unordered_set>  /// 用于无序集合
#include <vector>         /// 用于向量

using std::cin;
using std::cout;
using std::endl;
using std::get;
using std::left;
using std::make_tuple;
using std::priority_queue;
using std::rand;
using std::srand;
using std::tuple;
using std::unordered_set;
using std::vector;

/**
 * @brief 排序比较函数
 * @tparam S 进程ID的数据类型
 * @tparam T 到达时间的数据类型
 * @tparam E 运行时间的数据类型
 * @param t1 第一个元组
 * @param t2 第二个元组
 * @returns 如果t1和t2的顺序正确返回true，反之返回false
 */
template <typename S, typename T, typename E>
bool sortcol(tuple<S, T, E>& t1, tuple<S, T, E>& t2) {
    if (get<1>(t1) < get<1>(t2)) {
        return true;  // 如果t1的到达时间早于t2，返回true
    } else if (get<1>(t1) == get<1>(t2) && get<0>(t1) < get<0>(t2)) {
        return true;  // 如果到达时间相同，按照进程ID排序
    }
    return false;  // 否则返回false
}

/**
 * @class Compare
 * @brief 优先队列的比较类
 * @tparam S 进程ID的数据类型
 * @tparam T 到达时间的数据类型
 * @tparam E 运行时间的数据类型
 */
template <typename S, typename T, typename E>
class Compare {
 public:
    /**
     * @param t1 第一个元组
     * @param t2 第二个元组
     * @brief 比较函数，用于决定两个元组是否需要交换。
     * @link 参考
     * https://www.geeksforgeeks.org/comparator-class-in-c-with-examples/ 以获取比较器的详细描述
     * @returns 如果元组需要交换返回true，反之返回false
     */
    bool operator()(tuple<S, T, E, double, double, double>& t1,
                    tuple<S, T, E, double, double, double>& t2) {
        // 比较到达时间
        if (get<1>(t2) < get<1>(t1)) {
            return true;  // 如果t2的到达时间早于t1，返回true
        }
        // 如果到达时间相同，比较进程ID
        else if (get<1>(t2) == get<1>(t1)) {
            return get<0>(t2) < get<0>(t1);
        }
        return false;  // 否则返回false
    }
};

/**
 * @class FCFS
 * @brief 实现FCFS调度算法的类
 * @tparam S 进程ID的数据类型
 * @tparam T 到达时间的数据类型
 * @tparam E 运行时间的数据类型
 */
template <typename S, typename T, typename E>
class FCFS {
    /**
     * 进程的优先队列（以元组存储调度信息）。
     * 每个元组包含：
     * 1st element: 进程ID
     * 2nd element: 到达时间
     * 3rd element: 运行时间
     * 4th element: 完成时间
     * 5th element: 周转时间
     * 6th element: 等待时间
     */
    priority_queue<tuple<S, T, E, double, double, double>,
                   vector<tuple<S, T, E, double, double, double>>,
                   Compare<S, T, E>>
        schedule;

    // 存储所有进程执行完成后的最终状态
    vector<tuple<S, T, E, double, double, double>> result;

    // 存储进程ID，用于确认在添加进程时是否存在重复
    unordered_set<S> idList;

 public:
    /**
     * @brief 添加进程到就绪队列，如果进程不在其中
     * @param id 进程ID
     * @param arrival 进程的到达时间
     * @param burst 进程的运行时间
     * @returns void
     */
    void addProcess(S id, T arrival, E burst) {
        // 如果进程ID不在idList中，则添加进程
        if (idList.find(id) == idList.end()) {
            tuple<S, T, E, double, double, double> t =
                make_tuple(id, arrival, burst, 0, 0, 0);
            schedule.push(t);  // 将新进程添加到调度队列中
            idList.insert(id);  // 将进程ID添加到idList中
        }
    }

    /**
     * @brief 根据先来先服务(FCFS)调度算法调度CPU进程的算法。
     *
     * @details FCFS是一种非抢占式算法，最先到达的进程最先执行。如果两个或多个进程同时到达，则进程ID较小的先执行（每个进程都有唯一的进程ID）。
     *
     * 我使用了一个最小优先队列的元组来实现此任务。进程按到达时间排序。如果一些进程的到达时间相同，则按进程ID排序。
     *
     * @returns void
     */
    vector<tuple<S, T, E, double, double, double>> scheduleForFcfs() {
        // 用于跟踪迄今为止经过的时间
        double timeElapsed = 0;

        while (!schedule.empty()) {
            tuple<S, T, E, double, double, double> cur = schedule.top();  // 获取队列顶端的当前进程

            // 如果当前进程的到达时间大于已消耗时间
            if (get<1>(cur) > timeElapsed) {
                timeElapsed += get<1>(cur) - timeElapsed;  // 更新时间
            }

            // 将运行时间加到已消耗时间上
            timeElapsed += get<2>(cur);

            // 当前进程的完成时间等于到目前为止的时间
            get<3>(cur) = timeElapsed;

            // 周转时间 = 完成时间 - 到达时间
            get<4>(cur) = get<3>(cur) - get<1>(cur);

            // 等待时间 = 周转时间 - 运行时间
            get<5>(cur) = get<4>(cur) - get<2>(cur);

            result.push_back(cur);  // 将当前进程信息添加到结果中
            schedule.pop();  // 移除已处理的进程
        }
        return result;  // 返回所有进程的调度结果
    }

    /**
     * @brief 用于打印每个进程执行后的状态的工具函数
     * @returns void
     */
    void printResult() {
        cout << "所有进程执行完成后的状态如下:" << endl;

        cout << std::setw(17) << left << "进程ID" << std::setw(17) << left
             << "到达时间" << std::setw(17) << left << "运行时间"
             << std::setw(17) << left << "完成时间" << std::setw(17)
             << left << "周转时间" << std::setw(17) << left
             << "等待时间" << endl;

        for (size_t i{}; i < result.size(); i++) {
            cout << std::setprecision(2) << std::fixed << std::setw(17) << left
                 << get<0>(result[i]) << std::setw(17) << left
                 << get<1>(result[i]) << std::setw(17) << left
                 << get<2>(result[i]) << std::setw(17) << left
                 << get<3>(result[i]) << std::setw(17) << left
                 << get<4>(result[i]) << std::setw(17) << left
                 << get<5>(result[i]) << endl;  // 打印进程信息
        }
    }
};

/
