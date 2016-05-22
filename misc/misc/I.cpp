#include<iostream>
#include<cstring>
#define B 0
#define G 1
#define M 2
#define NM 3
#define NG 4
#define MOD 10000000
using namespace std;
int dp[1005][1005][12][5];
int count=0;
inline long long dfs(int p,int q, int r, int l){
  int val=1;
  //if(p > 30)
  if(p<0 || q<0 || r<0) {
    return 0;
  }
  if(dp[p][q][r][l]>=0)
    return dp[p][q][r][l];
  if(l==B && p==0)
    return 0;
  if(l==G && (((p==0&&r==0)||q==0)))
    return 0;
  if(l==M && (r==0 || (p==0&&q==0)))
    return 0;
  if(l==NG && q==0)
    return 0;
  if(l==NM && r==0)
    return 0;
  //++count;
  //cout << "p=" << p << " q=" << q << " r=" << r << " l=" << l << endl;
  dp[p][q][r][l] = val;
  if(l==B)
    val = (dfs(p-1,q,r,B) + dfs(p-1,q,r,G) + dfs(p-1,q,r,NG) + dfs(p-1,q,r,M) + dfs(p-1,q,r,NM)) % MOD;
  else if(l==G)
    val = (dfs(p,q-1,r,B) + dfs(p,q-1,r,M) + dfs(p,q-1,r,NM)) % MOD;
  else if(l==NG)
    val = dfs(p,q-1,r,G) % MOD;
  else if(l==M)
    val = (dfs(p,q,r-1,B) + dfs(p,q,r-1,G) + dfs(p,q,r-1,NG)) % MOD;
  else if(l==NM)
    val = dfs(p,q,r-1,M) % MOD;
  dp[p][q][r][l] = val;
  return val;
}
int main(void){
  int t,p,q,r;
  memset(dp,-1,sizeof(dp));
  dp[1][0][0][B]=1;
  dp[1][1][0][G]=1;
  dp[0][1][0][NG]=1;
  dp[1][0][1][M]=1;
  dp[0][0][1][NM]=1;
  for(int k=0;k<=10;++k)  //M
    for(int i=0;i<=1000;++i)    //B
      //for(int j=0;j<=100;++j,cout<<k<<" "<<i<<" "<<j<<" "<<count<<endl)  //G
      for(int j=0;j<=1000;++j)
        for(int l=0;l<5;++l)
          if(dp[i][j][k][l]<0)
            dp[i][j][k][l]=dfs(i,j,k,l);
  for(cin>>t;t>0;--t){
    cin>>p>>q>>r;
//    cout<<dp[p][q][r][B]+dp[p][q][r][G]+dp[p][q][r][M]<<endl;
    cout<<(dfs(p,q,r,B)+dfs(p,q,r,G)+dfs(p,q,r,M)) % MOD<<endl;
  }
  return 0;
}
