// 题目：你得到了两个长度为 n 的数组 a 和 b。
// 你的任务是统计满足条件的整数对(i,j)的数量，其中 1εij≤ n并且满足 ai·aj=bi+bj。

// 思路：
// 1，分两种情况
// a[i] == a[j]  dp[a[i]][a[i]*a[i]-b[i]]
// a[i] > a[j]  dp[j][j*a[i]-b[i]]
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll NMAX=2e5+5,SQRMAX=635,MOD=1e9+7;

int fr[SQRMAX][NMAX];
ll a[NMAX],b[NMAX];
void tc(){
    ll n,ans=0;
    cin>>n;
    ll lim=sqrt(n*2);
    for(ll i=0;i<n;i++){
        cin>>a[i];
    }
    for(ll i=0;i<n;i++){
        cin>>b[i];
        if(a[i]<=lim)
            fr[a[i]][b[i]]++;
    }
    for(ll i=0;i<n;i++){
        if(a[i]<=lim){
            if(a[i]*a[i]-b[i]>=1 && a[i]*a[i]-b[i]<=n)
                ans+=fr[a[i]][a[i]*a[i]-b[i]];
        }
    }
    for(ll i=2;i<=lim;i+=2)
        ans-=fr[i][i*i/2];
    ans/=2;

    for(ll i=0;i<n;i++){
        for(ll j=1;j<=lim && j<a[i] && j*a[i]<=2*n;j++){
            if(j*a[i]-b[i]>=1 && j*a[i]-b[i]<=n)
                ans+=fr[j][j*a[i]-b[i]];
        }
    }
    for(ll i=0;i<n;i++){
        if(a[i]<=lim)
            fr[a[i]][b[i]]=0;
    }
    cout<<ans<<'\n';
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll t;
    cin>>t;
    while(t--)
        tc();
    return 0;
}