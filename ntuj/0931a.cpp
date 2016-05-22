#include<iostream>
#include<cstring>
#include<cstdio>
#include<list>
#include<queue>
#include<map>
#define SIZE 20005
using namespace std;
int n,m, dist[SIZE];
map<int,int> c[SIZE], f[SIZE];
vector<int> edge[SIZE];
list<int> seq;
inline void bfs(){
  queue<int> que;
  dist[0] = 0;
  que.push(0);
  while(!que.empty()){
    int t=que.front();
    que.pop();
    for(int i=0;i<edge[t].size();++i)
      if(dist[edge[t][i]]<0 && f[t][edge[t][i]]<c[t][edge[t][i]]){
        dist[edge[t][i]]=dist[t]+1;
        que.push(edge[t][i]);
      }
  }
}
inline int dfs(int x){
  int sum=0;
  if(x==n+m+1)
    return 1;
  for(int i=0;i<edge[x].size();++i){
    int j = edge[x][i];
    if(dist[j] == dist[x]+1 && f[x][j] < c[x][j]) {
      ++f[x][j];
      if(dfs(j)) {
        --f[j][x];
        ++sum;
        if(x!=0) break;
      }
      else --f[x][j];
    }
  }
  return sum;
}
inline int dinitz(){
  int res=0;
  for(int i=0;i<n+m+2;++i)
    f[i].clear();
  while(1){
    memset(dist,-1,sizeof(dist));    
    bfs();
    if(dist[n+m+1]<0)
      return res;
    res += dfs(0);
  }
}
inline bool check(int k){
  for(int i=1;i<=n;++i)
    c[m+i][m+n+1] = k;
  if(dinitz() == m)
    return true;
  else 
    return false;
}
int main(void){
  int t;
  //cin.sync_with_stdio(false);
  for(scanf("%d",&t);t>0;--t){
    //cin>>n>>m;
    scanf("%d %d",&n,&m);
    for(int i=0;i<n+m+2;++i){
      c[i].clear();
      edge[i].clear();
    }
    for(int i=1;i<=m;++i){
      int ta,tb;
      c[0][i] = 1;
      edge[0].push_back(i); edge[i].push_back(0);
      //cin>>ta>>tb;
      scanf("%d %d",&ta,&tb);
      c[i][m+ta]=1;
      c[i][m+tb]=1;
      edge[i].push_back(m+ta); edge[m+ta].push_back(i);
      edge[i].push_back(m+tb); edge[m+tb].push_back(i);
    }
    for(int i=1;i<=n;++i)
      edge[m+i].push_back(n+m+1);
    int lo=0, hi=(m+1)/2;
    while(hi-lo>0){
      int mid=(hi+lo)/2;
      if(check(mid))
        hi=mid;
      else
        lo=mid+1;
    }
    //cout<<lo<<endl;
    printf("%d\n",lo);
  }
  return 0;
}
