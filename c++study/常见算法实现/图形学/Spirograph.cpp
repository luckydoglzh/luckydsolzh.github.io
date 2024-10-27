/**
 * @file
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief 实现
 * [Spirograph](https://en.wikipedia.org/wiki/Spirograph)
 *
 * @details
 * 程序的实现基于下图所示的几何形状：
 *
 * <a
 * href="https://commons.wikimedia.org/wiki/File:Resonance_Cascade.svg"><img
 * src="https://upload.wikimedia.org/wikipedia/commons/3/39/Resonance_Cascade.svg"
 * alt="Spirograph geometry from Wikipedia" style="width: 250px"/></a>
 */
#ifdef USE_GLUT
#ifdef __APPLE__
#include <GLUT/glut.h>  // 在Mac上的包含路径不同
#else
#include <GL/glut.h>
#endif  // __APPLE__
#endif
#define _USE_MATH_DEFINES /**< MSVC编译器所需 */
#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#ifdef _OPENMP
#include <omp.h>
#endif

/**
 * @namespace spirograph 与 spirograph.cpp 相关的函数
 */
namespace spirograph {
/** 
 * 生成 spirograph 曲线到数组 `x` 和 `y`，使得第 i 个点在 2D 中由 `(x[i],y[i])` 表示。生成函数由以下公式给出：
 * \f{eqnarray*}{
 * x &=& R\left[ (1-k) \cos (t) + l\cdot k\cdot\cos \left(\frac{1-k}{k}t\right)
 * \right]\\
 * y &=& R\left[ (1-k) \sin (t) - l\cdot k\cdot\sin \left(\frac{1-k}{k}t\right)
 * \right] \f}
 * 其中
 * * \f$R\f$ 是缩放参数，我们将其考虑为 \f$=1\f$
 * * \f$l=\frac{\rho}{r}\f$ 是标记从内圆心的相对距离，且 \f$0\le l\le1\f$
 * * \f$\rho\f$ 是标记从内圆心的物理距离
 * * \f$r\f$ 是内圆的半径
 * * \f$k=\frac{r}{R}\f$ 是内圆半径与外圆半径的比率，且 \f$0<k<1\f$
 * * \f$R\f$ 是外圆的半径
 * * \f$t\f$ 是点的旋转角度，即表示时间参数
 *
 * 由于我们考虑的是比率，\f$r\f$ 和 \f$R\f$ 的实际值无关紧要。
 *
 * @tparam N 点的数量 = 数组的大小
 * @param [out] points 作为 std::pair 表示的 2D 点数组
 * @param l 从内圆心到标记的相对距离，且 \f$0\le l\le1\f$
 * @param k 内圆半径与外圆半径的比率，且 \f$0<k<1\f$
 * @param rot 执行的旋转次数（可以是小数值）
 */
template <std::size_t N>
void spirograph(std::array<std::pair<double, double>, N> *points, double l,
                double k, double rot) {
    double dt = rot * 2.f * M_PI / N;  // 每个点的时间间隔
    double R = 1.f;                     // 外圆半径
    const double k1 = 1.f - k;          // 计算 k1
    int32_t step = 0;

#ifdef _OPENMP
#pragma omp for
#endif
    for (step = 0; step < N; step++) {
        double t = dt * step;  // 计算当前点的时间
        double first = R * (k1 * std::cos(t) + l * k * std::cos(k1 * t / k));
        double second = R * (k1 * std::sin(t) - l * k * std::sin(k1 * t / k));
        points[0][step].first = first;    // 存储 x 坐标
        points[0][step].second = second;  // 存储 y 坐标
    }
}

/**
 * @brief 测试函数，将结果点保存到 CSV 文件中。
 *
 */
void test() {
    const size_t N = 500;  // 点的数量
    double l = 0.3, k = 0.75, rot = 10.;  // 定义 l、k 和旋转次数
    std::stringstream fname;
    fname << std::setw(3) << "spirograph_" << l << "_" << k << "_" << rot
          << ".csv";  // 文件名格式
    std::ofstream fp(fname.str());
    if (!fp.is_open()) {
        perror(fname.str().c_str());  // 打印错误
        exit(EXIT_FAILURE);
    }

    std::array<std::pair<double, double>, N> points;  // 点数组

    spirograph(&points, l, k, rot);  // 生成 spirograph 曲线

    for (size_t i = 0; i < N; i++) {
        fp << points[i].first << "," << points[i].second;  // 写入 CSV 文件
        if (i < N - 1) {
            fp << '\n';
        }
    }

    fp.close();  // 关闭文件
}

#ifdef USE_GLUT
static bool paused = 0;  /**< 暂停/恢复动画的标志 */
static const int animation_speed = 25;  /**< 动画延迟，单位：毫秒 */

static const double step = 0.01;  /**< 动画步长 */
static double l_ratio = step * 10;  /**< 文档中定义的 l 比率 */
static double k_ratio = step;  /**< k 比率 */
static const double num_rot = 20.;  /**< 要模拟的旋转次数 */

/** 
 * GLUT 中一个在所有实现中不可用的包装。
 */
static inline void glutBitmapString(void *font, char *message) {
    for (char *ch = message; *ch != '\0'; ch++) glutBitmapCharacter(font, *ch);
}

/**
 * @brief 在 OpenGL 图形窗口中绘制 (x,y) 点。
 *
 * @tparam N 点的数量 = 数组的大小
 * @param [in] points 作为 std::pair 表示的 2D 点数组
 * @param l 从内圆心到标记的相对距离，且 \f$0\le l\le1\f$ 以显示信息
 * @param k 内圆半径与外圆半径的比率，且 \f$0<k<1\f$ 以显示信息
 */
template <size_t N>
void display_graph(const std::array<std::pair<double, double>, N> &points,
                   double l, double k) {
    glClearColor(1.0f, 1.0f, 1.0f,
                 0.0f);            // 设置背景颜色为白色并不透明
    glClear(GL_COLOR_BUFFER_BIT);  // 清除颜色缓冲区（背景）

    glBegin(GL_LINES);         // 开始绘制线段
    glColor3f(0.f, 0.f, 1.f);  // 颜色设置为蓝色
    glPointSize(2.f);          // 点的大小（像素）

    for (size_t i = 1; i < N; i++) {
        glVertex2f(points[i - 1].first, points[i - 1].second);  // 从前一个点绘制线
        glVertex2f(points[i].first, points[i].second);          // 到当前点
    }
    glEnd();

    glColor3f(0.f, 0.f, 0.f);  // 字体颜色为黑色
    std::stringstream buffer;
    buffer << std::setw(3) << "l = " << l;
    glRasterPos2f(-.85, .85);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,
                     const_cast<char *>(buffer.str().c_str()));
    buffer.str("");
    buffer.clear();
    buffer << std::setw(3) << "k = " << k;
    glRasterPos2f(-.85, .70);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,
                     const_cast<char *>(buffer.str().c_str()));

    glutSwapBuffers();  // 交换前后缓冲区
}

/**
 * @brief 带动画的测试函数
 *
 */
void test2() {
    const size_t N = 5000;  // 样本数量

    static bool direction1 = true;  // 如果为真则增加，否则减少
    static bool direction2 = true;  // 如果为真则增加，否则减少

    std::array<std::pair<double, double>, N> points;

    spirograph(&points, l_ratio, k_ratio, num_rot);  // 生成 spirograph 曲线
    display_graph(points, l_ratio, k_ratio);  // 绘制图形

    if (paused)
        // 如果暂停，则不更新 l_ratio 和 k_ratio
        return;

    if (direction1) {                 // 增加 k_ratio
        if (k_ratio >= (1.f - step))  // 最大限制
            direction1 = false;       // 反转 k_ratio 的方向
        else
            k_ratio += step;          // 增加 k_ratio
    } else {                    // 减少 k_ratio
        if (k_ratio <= step) {  // 最小限制
            direction1 = true;  // 反转 k_ratio 的方向

            if (direction2) {                 // 增加 l_ratio
                if (l_ratio >= (1.f - step))  // l_ratio 的最大限制
                    direction2 = false;       // 反转 l_ratio 的方向
                else
                    l_ratio += step;  // 增加 l_ratio
            } else {                    // 减少 l_ratio
                if (l_ratio <= step)    // l_ratio 的最小限制
                    direction2 = true;  // 反转 l_ratio 的方向
                else
                    l_ratio -= step;  // 减少 l_ratio
            }
        } else {  // k_ratio 没有最小限制
            k_ratio -= step;  // 减少 k_ratio
        }
    }
}

/**
 * @brief GLUT 定时器回调函数以添加动画延迟。
 */
void timer_cb(int t) {
    glutTimerFunc(animation_speed, timer_cb, 0);
    glutPostRedisplay();  // 请求重新绘制
}

/**
 * @brief 按键事件回调函数。
 *
 * @param key 按键 ID
 * @param x 鼠标指针在事件中的位置
 * @param y 鼠标指针在事件中的位置
 */
void keyboard_cb(unsigned char key, int x, int y) {
    switch (key) {
        case ' ':              // 空格键切换暂停
            paused = !paused;  // 切换
            break;
        case GLUT_KEY_UP:
        case '+':  // 上箭头键
            k_ratio += step;  // 增加 k_ratio
            break;
        case GLUT_KEY_DOWN:
        case '_':  // 下箭头键
            k_ratio -= step;  // 减少 k_ratio
            break;
        case GLUT_KEY_RIGHT:
        case '=':  // 右箭头键
            l_ratio += step;  // 增加 l_ratio
            break;
        case GLUT_KEY_LEFT:
        case '-':  // 左箭头键
            l_ratio -= step;  // 减少 l_ratio
            break;
        case 0x1B:  // ESC 键退出
            exit(EXIT_SUCCESS);
        default:
            return;  // 其他按键不做处理
    }
}
#endif
}  // namespace spirograph

/** 主函数 */
int main(int argc, char **argv) {
    spirograph::test();  // 测试函数

#ifdef USE_GLUT
    glutInit(&argc, argv);  // 初始化 GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);  // 初始化显示模式
    glutCreateWindow("Spirograph");  // 创建窗口
    glutInitWindowSize(400, 400);  // 设置窗口大小
    // glutIdleFunc(glutPostRedisplay);
    glutTimerFunc(spirograph::animation_speed, spirograph::timer_cb, 0);  // 设置定时器
    glutKeyboardFunc(spirograph::keyboard_cb);  // 注册键盘回调函数
    glutDisplayFunc(spirograph::test2);  // 注册显示回调函数
    glutMainLoop();  // 进入 GLUT 主循环
#endif

    return 0;  // 程序结束
}
