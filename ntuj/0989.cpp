#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

int x[12]={-2, -1,  1,  2,  2,  1, -1,  1,  0,  1,  0, -1};
int y[12]={-1, -2, -2, -1,  1,  2,  2,  1, -1,  0,  1,  0};
int R, C;

int w[55][55];
int id[55][55];
int S, T;
vector<int> a[2550];
vector<int> e[2550];
int pos[2550][2550];

int LR[2550];
int u[2550];

int dfs(int x){
  unsigned int i;
  u[x] = 1;
  for(i=0;i<a[x].size();i++){
    if(LR[a[x][i]] == -1) {
      LR[a[x][i]] = x;
      return 1;
    }
  }
  for(i=0;i<a[x].size();i++){
    u[a[x][i]] = 1;
    if(u[LR[a[x][i]]] == 0 && u[a[x][i]] == 0) {
      if(dfs(LR[a[x][i]])) {
        LR[a[x][i]] = x;
        return 1;
      }
    }
  }
  return 0;
}

int main(void)
{
  int i, j, R, C, k, cs=0;
  while(scanf("%d%d",&R,&C)!=EOF)
  {
    ++cs;
    if(R==0 && C==0) break;
    for(i=0;i<R*C;i++){
      a[i].clear();
      e[i].clear();
    }
    S = R*C;
    T = R*C+1;
    for(i=0;i<R;i++)
      for(j=0;j<C;j++){
        scanf("%d",&w[i][j]);
        if(w[i][j]==-1) continue;
        int id = i*C+j;
        for(k=0;k<12;k++){
          if(w[i][j]&(1<<k)){
            int u = y[k]+i, v=x[k]+j;
            if(u<0 || u>=R || v<0 || v>=C || w[u][v]==-1) continue;
            int nid = u*C+v;
            
            pos[id][nid] = a[id].size();
            a[id].push_back(nid);
            pos[nid][id] = a[nid].size();
            a[nid].push_back(id);
            if((i+j)%2==0){
              e[id].push_back(1);
              e[nid].push_back(0);
            } else {
              e[id].push_back(0);
              e[nid].push_back(1);
            }
          }
        }
      }
      memset(u,0,sizeof(u));
      memset(LR, -1, sizeof(LR));
        int ans = 0;
        for(i=0;i<R;i++)
          for(j=0;j<C;j++){
            if((i+j)%2==0 && w[i][j]!=-1){
              if(dfs(i*C+j)) {
                ++ans;
                memset(u, 0, sizeof(u));
              }
            }
          }
    printf("%d. %d\n", cs, ans);
  }
  return 0;
}
