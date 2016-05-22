#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<cstdio>
#define M 40
using namespace std;
int main(void){
  int t,n,g,m[M],now,count[M],s,v;
  scanf("%d",&t);
  for(int C=1;C<=t;++C){
    scanf("%d%d",&g,&n);
    for(int i=0;i<n;++i)
      scanf("%d",&m[i]);
    sort(m, m+n);
    /*s=0; v=1;
    for(int i=1;i<n;++i){
      if(m[i]==m[i-1])
        ++v;
      else{
        count[s++]=v;
        v=1;
      }
    }
    count[s++]=v;*/
    map< vector<int> , double > dp[g+1];
    queue< vector<int> > q[2];
    vector<int> init,final;
    for(int i=0;i<n;++i) init.push_back(0);    
    for(int i=0;i<n;++i) final.push_back(m[i]);
    dp[0][init] = 1;
    now=0;
    q[now].push(init);
    for(int i=0;i<g;++i,now=1-now){
      while(!q[now].empty()){
        vector<int> tmp = q[now].front();
        q[now].pop();
        double val = dp[i][tmp];
        for(int j=0;j<n;++j){
          vector<int> tmp2 = tmp;
          if(tmp2[j]<m[j]) ++tmp2[j];
          sort(tmp2.begin(),tmp2.end());
          if(dp[i+1].find(tmp2)==dp[i+1].end())
            q[1-now].push(tmp2);
          dp[i+1][tmp2] += val * 1.0/n;
        }
      }
    }
    printf("Case #%d: %.6lf\n",C,dp[g][final]*100);
  }
  return 0;
}
