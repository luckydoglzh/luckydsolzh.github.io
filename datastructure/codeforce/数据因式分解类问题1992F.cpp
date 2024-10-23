// Kmes在他最喜欢的咖啡馆里，再次想尝试"皮衣下的鲱鱼”（一种俄罗斯传统菜肴）。以前，他轻松就
// 能做到，但咖啡馆最近引入了一项新的购买政策。
// 现在，为了进行购买，Kmes需要解决以下问题：
// 在他面前有n张卡片，每张卡片上标有一个价格，第张卡片上的整数为ai。在这些价格中，没有一个
// 正整数x的整倍数。
// Kmes被要求将这些卡片划分为最少数量的不良段（保证每张卡片都属于且仅属于一个段）。一个段
// 被认为是不良的，如果在这个段中不可能选择一个子集，使其元素的乘积等于x。Kmes划分出的所有
// 段都必须是不良段。
// 形式化描述，段(l,r)是不良的，如果不存在索引li1<i2.<ik，使得l≤i1，ik≤r，并且满足ai1
// ai2.... aik = X。
// 帮助Kmes确定将卡片划分为最少数量不良段的方案，这样他就能享用他最喜欢的菜肴。
//思路：1，求x的因子并存储起来（用于后续进行数据处理）
//2，遍历卡片，当成因子存储起来
//3，如果值 == x则遍历结束

#include <iostream>
#include <vector>

using namespace std;

const int A = 1e6 + 1;  // 定义最大值，稍大于问题中的最大数值
bool used[A];           // 标记某个数是否已经被使用
bool divs[A];           // 标记某个数是否是 x 的因子

// 解决每个测试用例的函数
void solve() {
    int n, x;
    cin >> n >> x;  // 读取卡片数量 n 和目标乘积 x
    vector<int> a(n);  // 保存卡片价格的数组
    vector<int> vecDivs;  // 用来存储 x 的所有因子

    // 找出 x 的所有因子并标记
    for (int d = 1; d * d <= x; d++) {
        if (x % d == 0) {
            divs[d] = true;  // d 是 x 的因子
            vecDivs.push_back(d);  // 把 d 加入因子列表
            if (d * d < x) {
                vecDivs.push_back(x / d);  // 同时加入 x / d
                divs[x / d] = true;  // x / d 也是因子
            }
        }
    }

    // 读取卡片的价格
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int ans = 1;  // 最少需要一个不良段
    used[1] = true;  // 标记 1 已经使用（1 是任何数的因子）
    vector<int> cur{ 1 };  // 当前段中有效的因子初始化为 1

    // 遍历所有卡片
    for (int i = 0; i < n; i++) {
        // 如果卡片价格 a[i] 不是 x 的因子，跳过
        if (!divs[a[i]])
            continue;

        vector<int> ncur;  // 新段的有效因子
        bool ok = true;    // 用来检查是否需要分割段

        // 尝试将当前卡片价格与当前段的每个因子相乘，生成新的因子
        for (int d : cur) {
            // 如果新的因子有效且未被使用，则加入新的段
            if (1ll * d * a[i] <= x && divs[d * a[i]] && !used[d * a[i]]) {
                ncur.push_back(d * a[i]);  // 将新生成的因子加入新段
                used[d * a[i]] = true;     // 标记该因子已被使用
                if (d * a[i] == x)         // 如果生成的因子等于 x，表示当前段必须结束
                    ok = false;
            }
        }

        // 把新生成的因子合并到当前段
        for (int d : ncur)
            cur.push_back(d);

        // 如果当前段已经不能继续（即生成了 x）
        if (!ok) {
            ans++;  // 增加不良段的数量
            // 重置当前段的所有因子标记
            for (int d : cur)
                used[d] = false;
            used[1] = true;  // 保持 1 仍然有效
            used[a[i]] = true;  // 当前卡片价格作为新段的第一个元素
            cur = vector<int>{ 1, a[i] };  // 重新初始化当前段
        }
    }

    // 清理 vecDivs 中记录的所有因子的标记，以备下一个测试用例使用
    for (int d : vecDivs) {
        divs[d] = false;
        used[d] = false;
    }

    // 输出当前测试用例的最少不良段数
    cout << ans << '\n';
}

signed main() {
    int T;
    cin >> T;  // 读取测试用例的数量

    // 针对每个测试用例，调用 solve 函数
    while (T--)
        solve();

    return 0;
}
