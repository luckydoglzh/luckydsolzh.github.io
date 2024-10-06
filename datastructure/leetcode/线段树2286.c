//线段树本质上是使用平衡二叉树的思想来解决区间类问题
//区间求和啦，  区间查询啦， 区间更新值等等，这个需要多练练才能找到感觉


//leetcode 2286
//一个音乐会总共有 n 排座位，编号从 0 到 n - 1 ，每一排有 m 个座椅，编号为 0 到 m - 1 。你需要设计一个买票系统，针对以下情况进行座位安排：

// 同一组的 k 位观众坐在 同一排座位，且座位连续 。
// k 位观众中 每一位 都有座位坐，但他们 不一定 坐在一起。
// 由于观众非常挑剔，所以：

// 只有当一个组里所有成员座位的排数都 小于等于 maxRow ，这个组才能订座位。每一组的 maxRow 可能 不同 。
// 如果有多排座位可以选择，优先选择 最小 的排数。如果同一排中有多个座位可以坐，优先选择号码 最小 的。
// 请你实现 BookMyShow 类：

// BookMyShow(int n, int m) ，初始化对象，n 是排数，m 是每一排的座位数。
// int[] gather(int k, int maxRow) 返回长度为 2 的数组，表示 k 个成员中 第一个座位 的排数和座位编号，这 k 位成员必须坐在 同一排座位，且座位连续 。换言之，返回最小可能的 r 和 c 满足第 r 排中 [c, c + k - 1] 的座位都是空的，且 r <= maxRow 。如果 无法 安排座位，返回 [] 。
// boolean scatter(int k, int maxRow) 如果组里所有 k 个成员 不一定 要坐在一起的前提下，都能在第 0 排到第 maxRow 排之间找到座位，那么请返回 true 。这种情况下，每个成员都优先找排数 最小 ，然后是座位编号最小的座位。如果不能安排所有 k 个成员的座位，请返回 false 。

//用这道题来体验一下线段树



typedef struct {
    int n;
    int m;
    int* mintree;
    long long* sumtree;
} BookMyShow;

// 查询满足要求的最小行号
int queryMin(BookMyShow* obj, int i, int l, int r,int val) {
    if(l == r){
        //已经到叶子节点了
        if(obj->mintree[i] > val){
            return obj->n;
        }
        return l;
    }
    int mid = (l + r)/2;
    //左节点存在
    if(obj->mintree[i * 2] <= val){
        return queryMin(obj, i*2, l, mid, val);
    }else{
        return queryMin(obj, i*2 + 1, mid+1, r, val);
    }
}

// 查询区间和
long long querySum(BookMyShow* obj, int i, int l, int r, int l2, int r2) {
    if(l2 > r || r2 < l){
        return 0;
    }
    if(l2 <= l && r2 >= r){
        return obj->sumtree[i];
    }
    int mid = (l + r)/2;
    return querySum(obj, i * 2, l, mid, l2, r2) + querySum(obj, i*2 + 1, mid+1, r, l2, r2);
}
void update(BookMyShow* obj, int i, int l, int r, int index, int val){
    if(l == r){
        obj->mintree[i] = val;
        obj->sumtree[i] = val;
        return;
    }
    int mid = (l + r)/2;
    if(index <= mid){
        update(obj, i * 2, l, mid, index, val);
    }else{
        update(obj, i * 2 +1, mid+1,r,index, val);
    }
    obj->mintree[i] = obj->mintree[i * 2] < obj->mintree[i * 2 + 1] ? obj->mintree[i * 2] : obj->mintree[i * 2 + 1];
    obj->sumtree[i] = obj->sumtree[i*2] + obj->sumtree[i*2+1];
}
BookMyShow* bookMyShowCreate(int n, int m) {
    BookMyShow* obj = malloc(sizeof(BookMyShow));
    obj->mintree = malloc(sizeof(int) * 4 * n);
    obj->sumtree = malloc(sizeof(long long) * 4 * n);
    memset(obj->mintree, 0, sizeof(int) * 4 * n);
    memset(obj->sumtree, 0, sizeof(long long) * 4 * n);
    obj->n = n;
    obj->m = m;
    return obj;
}

int* bookMyShowGather(BookMyShow* obj, int k, int maxRow, int* retSize) {
    
    int raw = queryMin(obj, 1, 0, obj->n-1, obj->m - k);
    if(raw > maxRow){
        return NULL;
    }
    int used = querySum(obj, 1, 0, obj->n - 1, raw, raw);
    update( obj, 1, 0, obj->n-1, raw, used + k);
    int* ans = malloc(sizeof(int)*2);
    ans[0] = raw;
    ans[1] = used;
    *retSize = 2;
    
    return ans;
}

bool bookMyShowScatter(BookMyShow* obj, int k, int maxRow) {
    long long sumnum = querySum( obj, 1, 0, obj->n-1, 0, maxRow);
    if((1ll + maxRow) * obj->m - sumnum < k){
        return false;
    }
    int minraw = queryMin(obj, 1, 0, obj->n-1, obj->m - 1);
    while(true){
        int used =  querySum( obj, 1, 0, obj->n-1, minraw, minraw);
        if(k > (obj->m - used)){
            k -= (obj->m - used);
            update(obj, 1, 0, obj->n-1, minraw, obj->m);
        }else{
            update(obj, 1, 0, obj->n -1, minraw, used + k);
            break;
        }
        minraw++;
    }
    return true;
}

void bookMyShowFree(BookMyShow* obj) {
    free(obj->mintree);
    free(obj->sumtree);
    free(obj);
}

/**
 * Your BookMyShow struct will be instantiated and called as such:
 * BookMyShow* obj = bookMyShowCreate(n, m);
 * int* param_1 = bookMyShowGather(obj, k, maxRow, retSize);
 
 * bool param_2 = bookMyShowScatter(obj, k, maxRow);
 
 * bookMyShowFree(obj);
*/