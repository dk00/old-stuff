#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

int dp[50005][2];
vector<int> a[50005];
int u[50005];

void dfs(int x)
{
  u[x] = 1;
  int i;
  dp[x][0] = 0;
  dp[x][1] = 1;
  for(i=0;i < a[x].size();i++)
    if(u[a[x][i]] == 0) {
      dfs(a[x][i]);
      dp[x][0] += dp[a[x][i]][1];
      dp[x][1] += dp[a[x][i]][0];
    }
  if(dp[x][1] < dp[x][0]) dp[x][1] = dp[x][0];
}

int main(void)
{
  int n, i;
  while(scanf("%d", &n)!=EOF) {
    for(i=1;i<n;i++){
      int x, y;
      scanf("%d%d", &x, &y);
      a[x].push_back(y);
      a[y].push_back(x);
    }
    memset(u, 0, sizeof(u));
    memset(dp, 0, sizeof(dp));
    dfs(1);
    printf("%d\n", dp[1][1]);
    for(i=1;i<=n;i++)
      a[i].clear();
  }
  return 0;
}
