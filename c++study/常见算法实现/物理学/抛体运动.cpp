/**
 * @file
 * @brief 地面到地面的[抛体运动](https://en.wikipedia.org/wiki/Projectile_motion)方程实现
 * @details 地面到地面的抛体运动是指抛体的轨迹从地面开始，达到最高点后，再落回地面。
 *
 * @author [Focusucof](https://github.com/Focusucof)
 */

#include <cassert>   /// 用于 assert()
#define _USE_MATH_DEFINES
#include <cmath>     /// 用于 std::pow(), std::sin(), 和 std::cos()
#include <iostream>  /// 用于输入输出操作

/**
 * @namespace physics
 * @brief 物理算法
 */
namespace physics {
/**
 * @namespace ground_to_ground_projectile_motion
 * @brief 地面到地面的[抛体运动](https://en.wikipedia.org/wiki/Projectile_motion)方程函数
 */
namespace ground_to_ground_projectile_motion {
/**
 * @brief 将弧度转换为度
 * @param radian 角度（弧度）
 * @returns 角度（度）
 */
double degrees_to_radians(double degrees){
    double radians = degrees * (M_PI / 180);
    return radians;
}

/**
 * @brief 计算飞行时间
 * @param initial_velocity 抛体的初始速度
 * @param angle 抛体发射的角度（度）
 * @param gravity 重力常数的值
 * @returns 抛体在空中的时间
 */
template <typename T>
T time_of_flight(T initial_velocity, T angle, double gravity = 9.81) {
    double Viy = initial_velocity * (std::sin(degrees_to_radians(angle))); // 计算初始速度的y分量
    return 2.0 * Viy / gravity; // 计算飞行时间
}

/**
 * @brief 计算抛体的水平距离
 * @param initial_velocity 抛体的初始速度
 * @param time 抛体在空中的时间
 * @returns 抛体水平移动的距离
 */
template <typename T>
T horizontal_range(T initial_velocity, T angle, T time) {
    double Vix = initial_velocity * (std::cos(degrees_to_radians(angle))); // 计算初始速度的x分量
    return Vix * time; // 计算水平距离
}

/**
 * @brief 计算抛体的最大高度
 * @param initial_velocity 抛体的初始速度
 * @param angle 抛体发射的角度（度）
 * @param gravity 重力常数的值
 * @returns 抛体达到的最大高度
 */
template <typename T>
T max_height(T initial_velocity, T angle, double gravity = 9.81) {
    double Viy = initial_velocity * (std::sin(degrees_to_radians(angle))); // 计算初始速度的y分量
    return (std::pow(Viy, 2) / (2.0 * gravity)); // 计算最大高度
}
}  // namespace ground_to_ground_projectile_motion
}  // namespace physics

/**
 * @brief 自测实现
 * @returns void
 */
static void test() {
    // 初始输入变量
    double initial_velocity = 5.0;  // 初始速度
    double angle = 40.0;            // 发射角度

    // 第一个测试
    double expected_time_of_flight = 0.655;  // 期望的飞行时间输出
    double flight_time_output =
        std::round(physics::ground_to_ground_projectile_motion::time_of_flight(initial_velocity, angle) * 1000.0) /
        1000.0;  // 将输出四舍五入到三位小数

    std::cout << "抛体飞行时间 (double)" << std::endl;
    std::cout << "输入初始速度: " << initial_velocity << std::endl;
    std::cout << "输入角度: " << angle << std::endl;
    std::cout << "期望输出: " << expected_time_of_flight << std::endl;
    std::cout << "输出: " << flight_time_output << std::endl;
    assert(flight_time_output == expected_time_of_flight);
    std::cout << "测试通过" << std::endl << std::endl;

    // 第二个测试
    double expected_horizontal_range = 2.51; // 期望的水平距离输出
    double horizontal_range_output =
        std::round(physics::ground_to_ground_projectile_motion::horizontal_range(initial_velocity, angle,
                                             flight_time_output) *
                   100.0) /
        100.0;  // 将输出四舍五入到两位小数

    std::cout << "抛体水平距离 (double)" << std::endl;
    std::cout << "输入初始速度: " << initial_velocity << std::endl;
    std::cout << "输入角度: " << angle << std::endl;
    std::cout << "输入飞行时间: " << flight_time_output << std::endl;
    std::cout << "期望输出: " << expected_horizontal_range << std::endl;
    std::cout << "输出: " << horizontal_range_output << std::endl;
    assert(horizontal_range_output == expected_horizontal_range);
    std::cout << "测试通过" << std::endl << std::endl;

    // 第三个测试
    double expected_max_height = 0.526; // 期望的最大高度输出
    double max_height_output =
        std::round(physics::ground_to_ground_projectile_motion::max_height(initial_velocity, angle) * 1000.0) /
        1000.0;  // 将输出四舍五入到三位小数

    std::cout << "抛体最大高度 (double)" << std::endl;
    std::cout << "输入初始速度: " << initial_velocity << std::endl;
    std::cout << "输入角度: " << angle << std::endl;
    std::cout << "期望输出: " << expected_max_height << std::endl;
    std::cout << "输出: " << max_height_output << std::endl;
    assert(max_height_output == expected_max_height);
    std::cout << "测试通过" << std::endl << std::endl;
}

/**
 * @brief 主函数
 * @returns 0 退出时
 */
int main() {
    test();  // 运行自测实现
    return 0;
}
