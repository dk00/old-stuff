#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
bool cmp(int a,int b){
  return a>b;
}
int main(void){
  //cin.sync_with_stdio(false);
  int t,n,w,p[105],dp[105][105],sum[105];
  for(cin>>t;t>0;--t){
    cin>>n>>w;
    for(int i=1;i<=n;++i)
      cin>>p[i];
    sort(p+1,p+(n+1),cmp);
    sum[0] = 0;
    for(int i=1;i<=n;++i)
      sum[i] = sum[i-1] + p[i];
    //dp[n][w]
    for(int i=1;i<=n;++i)
      dp[i][1] = i * sum[i];
    for(int j=2;j<=w;++j){
      //i==j's case
      dp[j][j]=0;
      for(int i=1;i<=j;++i)
        dp[j][j] += i*p[i];

      for(int i=j+1;i<=n;++i){
        dp[i][j] = dp[i-1][j-1]+i*p[i];
        for(int k=2;i-k>0 && i-k>=j-1;++k){
          dp[i][j] = min(dp[i][j], dp[i-k][j-1]+i*(sum[i]-sum[i-k]));
        }
      }
    }
    printf("%.4lf\n",(double)dp[n][w]/sum[n]);
  }
  return 0;
}
