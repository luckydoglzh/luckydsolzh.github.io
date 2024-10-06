//1870
/*
给你一个浮点数 hour ，表示你到达办公室可用的总通勤时间。要到达办公室，你必须按给定次序乘坐 n 趟列车。另给你一个长度为 n 的整数数组 dist ，其中 dist[i] 表示第 i 趟列车的行驶距离（单位是千米）。

每趟列车均只能在整点发车，所以你可能需要在两趟列车之间等待一段时间。

例如，第 1 趟列车需要 1.5 小时，那你必须再等待 0.5 小时，搭乘在第 2 小时发车的第 2 趟列车。
返回能满足你准时到达办公室所要求全部列车的 最小正整数 时速（单位：千米每小时），如果无法准时到达，则返回 -1 。

生成的测试用例保证答案不超过 107 ，且 hour 的 小数点后最多存在两位数字 。
*/
//这题有个地方很有意思
//int temp = dist[i]-1;
//time += (temp/mid + 1);
//遇到可能进位的情况：先减一，在除以，再加1



#define mixlen 100
bool isok(int mid, int* dist, int distSize, long long hour){
    long long time = 0;
    for(int i = 0; i < distSize-1;i++){
        int temp = dist[i]-1;
        time += (temp/mid + 1);
    }
    time *= mid;
    time += dist[distSize-1];
    return time*mixlen <= hour*mid;
    
}
int minSpeedOnTime(int* dist, int distSize, double hour) {
    long long newhour = llround(hour * mixlen);
    if((newhour <= (distSize-1) * mixlen)){
        return -1;
    }
    int left = 1;
    int right = 10000000;
    while(left < right){
        int mid = (left + right)/2;
        if(isok(mid, dist, distSize, newhour)){
            right = mid;
        }else{
            left = mid + 1;
        }
    }
    return left;

}