#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

vector<int> a[10005];
int e[10005][4];
int dp[10005][3];
int u[10005];

inline int getother(int i, int x)
{
  return e[i][0] + e[i][1] - x;
}
inline void update(int *x, int v1, int v2)
{
  if(v1==-1) return;
  if(v2==-1) return;
  if(*x==-1 || *x > v1+v2) *x = v1+v2;
}
inline void update(int *x, int v1, int v2, int v3)
{
  if(v1==-1||v2==-1||v3==-1) return;
  if(*x==-1 || *x > v1+v2+v3) *x = v1+v2+v3;
}
inline int MIN(int x, int y){
  if(x==-1) return y;
  if(y==-1) return x;
  return x<y? x: y;
}
void go(int x)
{
  u[x] = 1;
  dp[x][0] = -1;
  dp[x][1] = -1;
  dp[x][2] = 0;
  int i;
  for(i=0;i<a[x].size();i++){
    int y = getother(a[x][i], x);
    if(!u[y])
    {
      go(y);
      int tmp[3] = {-1, -1, -1};
      int c = e[a[x][i]][3];
      update(&tmp[0], dp[x][0], dp[y][0]);
      update(&tmp[0], dp[x][0], dp[y][1], c);
      update(&tmp[0], dp[x][0], dp[y][2]);
      update(&tmp[0], MIN(dp[x][1], dp[x][2]), c, dp[y][0]);
      update(&tmp[0], MIN(dp[x][1], dp[x][2]), c, dp[y][1]);
      update(&tmp[0], MIN(dp[x][1], dp[x][2]), c, dp[y][2]);
      update(&tmp[1], dp[x][1], dp[y][0]);
      update(&tmp[1], dp[x][1], dp[y][2]);
      if (e[a[x][i]][2]) {  
        //update(&tmp[1], dp[x][2], dp[y][0]);
        update(&tmp[1], dp[x][2], dp[y][2]);
        update(&tmp[2], dp[x][2], dp[y][0]);
      }else{
        update(&tmp[2], dp[x][2], dp[y][2]);
        update(&tmp[2], dp[x][2], dp[y][0]);
      }
      dp[x][0] = tmp[0];
      dp[x][1] = tmp[1];
      dp[x][2] = tmp[2];
    }
//    printf("x=%d, %d,%d,%d\n", x, dp[x][0], dp[x][1], dp[x][2]);
  }
//  printf("x=%d, %d,%d,%d\n", x, dp[x][0], dp[x][1], dp[x][2]);
}

int main(void)
{
  int T, i, j, n;
  scanf("%d", &T);
  while(T--){
    scanf("%d", &n);
    for(i=0;i<n;i++)
      a[i].clear();
    for(i=1;i<n;i++){
      for(j=0;j<4;j++)
        scanf("%d", &e[i][j]);
      a[e[i][0]].push_back(i);
      a[e[i][1]].push_back(i);
    }
    memset(dp, 0, sizeof(dp));
    memset(u, 0, sizeof(u));
    go(0);
    printf("%d\n", MIN(dp[0][0], dp[0][2]));
  }
  return 0;
}
